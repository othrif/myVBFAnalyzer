#!/usr/bin/env python

import os
import sys
import math
import subprocess
import ROOT
from ROOT import *

# usage: python calculateOTFYields.py Z_strong SR
# Valid channels:
# W_EWK, Z_EWK, W_strong, Z_strong
# Valid regions:
# Incl, SRPhiHigh, CRWPhiHigh, CRZPhiHigh, SRPhiLow, CRWPhiLow, CRZPhiLow, SRNjet, CRWNjet, CRZNjet

debug = True
basePath = "./input/theoVariation_300919"
outPath = "./output/theoVariation_300919"

if not os.path.exists(outPath):
    os.makedirs(outPath)

channels = ["W_EWK", "Z_EWK", "W_strong", "Z_strong"]
regions  = ["SR", "CRW", "CRZ"]

outAll = ROOT.TFile(outPath+"/theoUncRW_"+channel+"_"+reg+".root", "recreate")

for channel in channels:
    for region in regions:
        if channel == "W_EWK" and region == "CRZ":
            continue
        if channel == "Z_EWK" and region == "CRW":
            continue
        if channel == "W_strong" and region == "CRZ":
            continue
        if channel == "Z_strong" and region == "CRW":
            continue

        print "\nRunning systs for channel:", channel, region

        # bin1Low, bin2Low, bin3Low, bin1High, bin2High, bin3High, binNjet
        # up, down
        # renofact, pdf, resum, ckkw

        theoUncUp= {     "renofact"     : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "resum"        : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "ckkw"         : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "pdf"          : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]}
        theoUncDown= {   "renofact"     : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "resum"        : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "ckkw"         : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "pdf"          : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]}

        binItrScale = 0
        binItrPDF = 0
        binItr ={}
        binItr["resum"] = 0
        binItr["ckkw"] = 0
        listRegions=[region + "PhiLow", region + "PhiHigh", region + "Njet"]
        if region == "Incl":
            listRegions=[region, region, region]
        for reg in listRegions:
            if (debug): print reg
            variationDict = {"nominal"     : "jj_mass_" + reg + "_nominal",
                             "fac_up"      : "scales/jj_mass_" + reg + "_fac_up",
                             "fac_down"    : "scales/jj_mass_" + reg + "_fac_down",
                             "renorm_up"   : "scales/jj_mass_" + reg + "_renorm_up",
                             "renorm_down" : "scales/jj_mass_" + reg + "_renorm_down",
                             "both_up"     : "scales/jj_mass_" + reg + "_both_up",
                             "both_down"   : "scales/jj_mass_" + reg + "_both_down"}

            pdfString = "PDF/jj_mass_" + reg + "_pdf"

            histDict = {} # scale variations
            pdfDict = {}  # pdf variations
            varDict = {}  # varied samples ckkw, qsf

            inFile = ROOT.TFile.Open(basePath+"/theoVariation_"+channel+".root")
            outFile = ROOT.TFile(outPath+"/variedYields_"+channel+"_"+reg+".root", "recreate")

            # Scale variations
            for scale in variationDict:
        #        print "getting histo ", variationDict[scale]
                thisHist = inFile.Get(variationDict[scale])
                if(len(thisHist.GetSumw2()) == 0):
                    thisHist.Sumw2()
                histDict[scale] = thisHist.Clone("h_" + scale)
                histDict[scale].SetDirectory(0)
                histDict[scale].Write()

                #print variationDict[scale], histDict[scale].Integral()

            # PDF variations
            for i in range(100):
                thisHist = inFile.Get(pdfString + "%i"%i)
                if(len(thisHist.GetSumw2()) == 0):
                    thisHist.Sumw2()
                pdfDict[i] = thisHist.Clone("h_pdf%i"%i)
                pdfDict[i].SetDirectory(0)
                pdfDict[i].Write()
                #print pdfString + "%i"%i, pdfDict[i].Integral()
            inFile.Close()
            outFile.Close()


            # varied samples
            for key in ["qsf025", "qsf4", "ckkw15", "ckkw30"]:
                inFile = ROOT.TFile.Open(basePath+"/theoVariation_"+channel+"_"+key+".root")
                outFile = ROOT.TFile(outPath+"/variedYields_"+channel+"_"+reg+".root", "update")
                thisHist = inFile.Get("jj_mass_" + reg + "_nominal")
                thisHist.Scale(3)
                if(len(thisHist.GetSumw2()) == 0):
                    thisHist.Sumw2()
                varDict[key] = thisHist.Clone("h_" + key)
                varDict[key].SetDirectory(0)
                varDict[key].Write()
                inFile.Close()
                outFile.Close()

            ########################

            nbins    = 4
            mjj_bins = [0.8,1.,1.5,2.]
            mjj_incl = [0.8,1000]
            systs    = ["fac", "renorm", "both"]

            inFile   = ROOT.TFile.Open(outPath+"/variedYields_"+channel+"_"+reg+".root")
            outFile  = ROOT.TFile(outPath+"/reweight_"+channel+"_"+reg+".root", "recreate")

            yieldNom    = [0.,0.,0.,0.]
            largestUp   = [1.,1.,1.,1.]
            largestDown = [1.,1.,1.,1.]
            err_yieldNom    = [0.,0.,0.,0.]
            err_largestUp   = [0.,0.,0.,0.]
            err_largestDown = [0.,0.,0.,0.]
            yieldNomIncl = 0.
            largestUpIncl = 1.
            largestDownIncl = 1.
            err_yieldNomIncl = 0.
            err_largestUpIncl = 1.
            err_largestDownIncl = 1.
            nomHist = inFile.Get("h_nominal")

            for iBin in range(nomHist.GetNbinsX()+1):
                binIndex = 0
                binCenter = nomHist.GetBinCenter(iBin+1)
                if binCenter < mjj_bins[0]:
                    continue
                while binIndex < 3:
                    if binCenter >= mjj_bins[binIndex] and binCenter < mjj_bins[binIndex+1] :
                        break
                    binIndex = binIndex + 1
                yieldNom[binIndex] += nomHist.GetBinContent(iBin+1)
                yieldNomIncl += nomHist.GetBinContent(iBin+1)
                err_yieldNom[binIndex] += nomHist.GetBinError(iBin+1)*nomHist.GetBinError(iBin+1)
                err_yieldNomIncl += nomHist.GetBinError(iBin+1)*nomHist.GetBinError(iBin+1)
            for ibin in range(nbins):
                err_yieldNom[ibin] = math.sqrt(err_yieldNom[ibin])
            err_yieldNomIncl = math.sqrt(err_yieldNomIncl)

            # Scale variations
            for syst in systs :
                yieldU = [0.,0.,0.,0.]
                yieldD = [0.,0.,0.,0.]
                yieldUIncl = 0.
                yieldDIncl = 0.
                err_yieldU = [0.,0.,0.,0.]
                err_yieldD = [0.,0.,0.,0.]
                err_yieldUIncl = 0.
                err_yieldDIncl = 0.
                upHist = inFile.Get("h_" + syst + "_up")
                downHist = inFile.Get("h_" + syst + "_down")

                for iBin in range(upHist.GetNbinsX()+1):
                    binIndex = 0
                    binCenter = upHist.GetBinCenter(iBin+1)
                    if binCenter < mjj_bins[0]:
                        continue
                    while binIndex < 3:
                        if binCenter >= mjj_bins[binIndex] and binCenter < mjj_bins[binIndex+1] :
                            break
                        binIndex = binIndex + 1
                    yieldU[binIndex] += upHist.GetBinContent(iBin+1)
                    yieldD[binIndex] += downHist.GetBinContent(iBin+1)
                    yieldUIncl += upHist.GetBinContent(iBin+1)
                    yieldDIncl += downHist.GetBinContent(iBin+1)
                    err_yieldU[binIndex] += upHist.GetBinError(iBin+1)*upHist.GetBinError(iBin+1)
                    err_yieldD[binIndex] += downHist.GetBinError(iBin+1)*downHist.GetBinError(iBin+1)
                    err_yieldUIncl += upHist.GetBinError(iBin+1)*upHist.GetBinError(iBin+1)
                    err_yieldDIncl += downHist.GetBinError(iBin+1)*downHist.GetBinError(iBin+1)
                for ibin in range(nbins):
                    err_yieldU[ibin] = math.sqrt(err_yieldU[ibin])
                    err_yieldD[ibin] = math.sqrt(err_yieldD[ibin])
                err_yieldUIncl = math.sqrt(err_yieldUIncl)
                err_yieldDIncl = math.sqrt(err_yieldDIncl)
                reweight_up = TH1F(syst + "_up", syst + " up reweight", nbins, 800, 2500)
                reweight_down = TH1F(syst + "_down", syst + " down reweight", nbins, 800, 2500)
                for i in range(nbins) :
                    if yieldNom[i] == 0. :
                        if(debug): print "zero yield in bin %i, skipping." % i
                        continue
                    variationUp   = yieldU[i]/yieldNom[i]
                    variationDown = yieldD[i]/yieldNom[i]
                    err_variationUp   = yieldU[i]/yieldNom[i]*math.sqrt( math.pow(err_yieldU[i]/yieldU[i],2) + math.pow(err_yieldNom[i]/yieldNom[i],2) )
                    err_variationDown = yieldD[i]/yieldNom[i]*math.sqrt( math.pow(err_yieldD[i]/yieldD[i],2) + math.pow(err_yieldNom[i]/yieldNom[i],2) )
                    #print yieldU[i], "+-", err_yieldU[i], " over ", yieldNom[i], "+-", err_yieldNom[i], "=", variationUp, "+-", err_variationUp
                    if(math.fabs(variationUp-1) > math.fabs(largestUp[i]-1)):
                        #print syst + " is now the largest UP variation in bin %i: %f %%" % (i, (variationUp-1)*100)
                        largestUp[i] = variationUp
                        err_largestUp[i] = err_variationUp
                    if(math.fabs(variationDown-1) > math.fabs(largestDown[i]-1)):
                        #print syst + " is now the largest DOWN variation in bin %i: %f %%" % (i, (variationDown-1)*100)
                        largestDown[i] = variationDown
                        err_largestDown[i] = err_variationDown
                    if yieldNom[i] == 0:
                        continue
                    reweight_up.SetBinContent(  i+1, yieldU[i]/yieldNom[i])
                    reweight_down.SetBinContent(i+1, yieldD[i]/yieldNom[i])
                reweight_up.Write()
                reweight_down.Write()
                variationUpIncl   = yieldUIncl/yieldNomIncl
                variationDownIncl = yieldDIncl/yieldNomIncl
                err_variationUpIncl   = yieldUIncl/yieldNomIncl*math.sqrt( math.pow(err_yieldUIncl/yieldUIncl,2) + math.pow(err_yieldNomIncl/yieldNomIncl,2) )
                err_variationDownIncl = yieldDIncl/yieldNomIncl*math.sqrt( math.pow(err_yieldDIncl/yieldDIncl,2) + math.pow(err_yieldNomIncl/yieldNomIncl,2) )
                if(math.fabs(variationUpIncl-1) > math.fabs(largestUpIncl-1)):
                    largestUpIncl = variationUpIncl
                    err_largestUpIncl = err_variationUpIncl
                if(math.fabs(variationDownIncl-1) > math.fabs(largestDownIncl-1)):
                    largestDownIncl = variationDownIncl
                    err_largestDownIncl = err_variationDownIncl

            envelope_up = TH1F("envelope_up", "Envelope up reweight", nbins, 800, 2500)
            envelope_down = TH1F("envelope_down", "Envelope down reweight", nbins, 800, 2500)
            for i in range(nbins):
                if (debug):  print "Largest DOWN variation in bin %i: %f %%" % (i, (largestDown[i]-1)*100)
                envelope_up.SetBinContent(i+1, largestUp[i])
                envelope_up.SetBinError(i+1, err_largestUp[i])
                if (debug):  print "Largest UP variation in bin %i: %f %%" % (i, (largestUp[i]-1)*100)
                envelope_down.SetBinContent(i+1, largestDown[i])
                envelope_down.SetBinError(i+1, err_largestDown[i])
                if binItrScale < 8:
                    theoUncUp["renofact"][binItrScale]=largestUp[i]
                    theoUncDown["renofact"][binItrScale]=largestDown[i]
                    binItrScale = binItrScale+1
            theoUncUp["renofact"][binItrScale]=largestUpIncl
            theoUncDown["renofact"][binItrScale]=largestDownIncl
            envelope_up.Write()
            envelope_down.Write()


            # PDF variations
            avgNormalization = 1./100
            pdfYield = [0.,0.,0.,0.]
            pdfYieldSq = [0.,0.,0.,0.]
            varSafeOld = 0.
            pdfYieldIncl = 0.
            pdfYieldSqIncl = 0.
            err_pdfYield = [0.,0.,0.,0.]
            err_pdfYieldIncl = 0.
            for i in range(100):
                thisHist = inFile.Get("h_pdf%i"%i)
                varSafe = abs(thisHist.Integral()/nomHist.Integral()-1)*100
            #    print i, thisHist.Integral(), varSafe, abs(varSafe-varSafeOld)
                if abs(varSafe-varSafeOld) > 20:
                #if i==63:
                    thisHist = nomHist
                    varSafeOld = 0
                    if(debug): print "REPLACED bin ", i, "with nominal"
                else:
                    varSafeOld = varSafe
                thisYield = [0.,0.,0.,0.]
                thisYieldIncl = 0.
                err_thisYield = [0.,0.,0.,0.]
                err_thisYieldIncl = 0.
                for iBin in range(thisHist.GetNbinsX()+1):
                    binIndex = 0
                    binCenter = thisHist.GetBinCenter(iBin+1)
                    if binCenter < mjj_bins[0]:
                        continue
                    while binIndex < 3:
                        if binCenter >= mjj_bins[binIndex] and binCenter < mjj_bins[binIndex+1] :
                            break
                        binIndex = binIndex + 1
                    thisYield[binIndex] += thisHist.GetBinContent(iBin+1)
                    err_thisYield[binIndex] += thisHist.GetBinError(iBin+1)*thisHist.GetBinError(iBin+1)
                    thisYieldIncl += thisHist.GetBinContent(iBin+1)
                    err_thisYieldIncl += thisHist.GetBinError(iBin+1)*thisHist.GetBinError(iBin+1)
                for j in range(nbins):
                    pdfYield[j]    += avgNormalization * thisYield[j]
                    pdfYieldSq[j]  += avgNormalization * thisYield[j] * thisYield[j]
                    err_pdfYield[j] = avgNormalization * math.sqrt(err_thisYield[binIndex])
                pdfYieldIncl   += avgNormalization * thisYieldIncl
                pdfYieldSqIncl += avgNormalization * thisYieldIncl * thisYieldIncl
                err_pdfYieldIncl = avgNormalization * math.sqrt(err_thisYieldIncl)
            pdf_up   = TH1F("pdf_up",   "PDF up reweight",   nbins, 800, 2500)
            pdf_down = TH1F("pdf_down", "PDF down reweight", nbins, 800, 2500)
            pdfError = [0.,0.,0.,0.]
            tmp_pdfVar=[0.,0.,0.,0.]
            for i in range(nbins) :
                if(pdfYield[i] == 0):
                    if(debug): print "PDF yield is zero for bin %i"%i
                    continue
                pdfError[i] = math.sqrt(pdfYieldSq[i] - (pdfYield[i] * pdfYield[i]))
                tmp_pdfVar[i] = pdfError[i]/pdfYield[i]
                if (debug): print "PDF variation in bin %i: %f %%" % (i, tmp_pdfVar[i]*100)
                pdf_up.SetBinContent(  i+1, 1 + tmp_pdfVar[i])
                pdf_down.SetBinContent(i+1, 1 - tmp_pdfVar[i])
                pdf_up.SetBinError(  i+1, err_pdfYield[i])
                pdf_down.SetBinError(i+1, err_pdfYield[i])
                if binItrPDF < 8:
                    theoUncUp["pdf"][binItrPDF]   = 1 + tmp_pdfVar[i]
                    theoUncDown["pdf"][binItrPDF] = 1 - tmp_pdfVar[i]
                    binItrPDF = binItrPDF+1
            pdfErrorIncl = math.sqrt(pdfYieldSqIncl - (pdfYieldIncl * pdfYieldIncl))
            theoUncUp["pdf"][binItrPDF]   = 1 + pdfErrorIncl/pdfYieldIncl
            theoUncDown["pdf"][binItrPDF] = 1 - pdfErrorIncl/pdfYieldIncl
            pdf_up.Write()
            pdf_down.Write()

            # qsf/ckkw variations
            for wVar in ["resum", "ckkw"]:
                avgNormalization = 1./2
                pdfYield = [0.,0.,0.,0.]
                pdfYieldSq = [0.,0.,0.,0.]
                pdfYieldIncl = 0.
                pdfYieldSqIncl = 0.
                err_pdfYield = [0.,0.,0.,0.]
                err_pdfYieldIncl = 0.
                if wVar == "resum":
                    wList = ["qsf025", "qsf4"]
                elif wVar == "ckkw":
                    wList = ["ckkw15", "ckkw30"]
                for i in wList:
                    thisHist = inFile.Get("h_"+i)
                    thisYield = [0.,0.,0.,0.]
                    err_thisYield = [0.,0.,0.,0.]
                    thisYieldIncl = 0.
                    err_thisYieldIncl = 0.
                    for iBin in range(thisHist.GetNbinsX()+1):
                        binIndex = 0
                        binCenter = thisHist.GetBinCenter(iBin+1)
                        if binCenter < mjj_bins[0]:
                            continue
                        while binIndex < 3:
                            if binCenter >= mjj_bins[binIndex] and binCenter < mjj_bins[binIndex+1] :
                                break
                            binIndex = binIndex + 1
                        thisYield[binIndex] += thisHist.GetBinContent(iBin+1)
                        thisYieldIncl += thisHist.GetBinContent(iBin+1)
                        err_thisYield[binIndex] += thisHist.GetBinError(iBin+1)*thisHist.GetBinError(iBin+1)
                        err_thisYieldIncl += thisHist.GetBinError(iBin+1)*thisHist.GetBinError(iBin+1)
                    for j in range(nbins):
                        pdfYield[j]    += avgNormalization * thisYield[j]
                        pdfYieldSq[j]  += avgNormalization * thisYield[j] * thisYield[j]
                        err_pdfYield[j] = avgNormalization * math.sqrt(err_thisYield[binIndex])
                    pdfYieldIncl   += avgNormalization * thisYieldIncl
                    pdfYieldSqIncl += avgNormalization * thisYieldIncl * thisYieldIncl
                    err_pdfYieldIncl = avgNormalization * math.sqrt(err_thisYieldIncl)
                pdf_up   = TH1F(wVar+"_up",   wVar+" up reweight",   nbins, 800, 2500)
                pdf_down = TH1F(wVar+"_down", wVar+" down reweight", nbins, 800, 2500)
                pdfError = [0.,0.,0.,0.]
                tmp_pdfVar=[0.,0.,0.,0.]
                for i in range(nbins) :
                    if(pdfYield[i] == 0):
                        if(debug): print " yield is zero for bin %i"%i
                        continue
                    pdfError[i] = math.sqrt(pdfYieldSq[i] - (pdfYield[i] * pdfYield[i]))
                    tmp_pdfVar[i] = pdfError[i]/pdfYield[i]
                    if (debug):  print wVar+" variation in bin %i: %f %%" % (i, tmp_pdfVar[i]*100)
                    pdf_up.SetBinContent(  i+1, 1 + tmp_pdfVar[i])
                    pdf_down.SetBinContent(i+1, 1 - tmp_pdfVar[i])
                    pdf_up.SetBinError(  i+1, err_pdfYield[i])
                    pdf_down.SetBinError(i+1, err_pdfYield[i])
                    if binItr[wVar] < 8:
                        theoUncUp[wVar][binItr[wVar]]   = 1 + tmp_pdfVar[i]
                        theoUncDown[wVar][binItr[wVar]] = 1 - tmp_pdfVar[i]
                        binItr[wVar] = binItr[wVar]+1
                pdfErrorIncl = math.sqrt(pdfYieldSqIncl - (pdfYieldIncl * pdfYieldIncl))
                theoUncUp[wVar][binItr[wVar]]   = 1 + pdfErrorIncl/pdfYieldIncl
                theoUncDown[wVar][binItr[wVar]] = 1 - pdfErrorIncl/pdfYieldIncl
                pdf_up.Write()
                pdf_down.Write()
            inFile.Close()
            outFile.Close()

        f = open(outPath+"/listTheorySyst", "w")
        if (debug): print "\n=====================\n"
        for theo in theoUncUp:
            print region+"up="+theo+"_"+channel, ",".join([str('{0:.5g}'.format(x)) for x in theoUncUp[theo]])
        print ""
        for theo in theoUncDown:
            print region+"down="+theo+"_"+channel, ",".join([str('{0:.5g}'.format(x)) for x in theoUncDown[theo]])

