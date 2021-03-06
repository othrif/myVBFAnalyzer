#!/usr/bin/env python

import os
import sys
import math
import subprocess
from ROOT import *
from array import array

# usage: python calculateOTFYields.py Z_strong SR
# Valid channels:
# W_EWK, Z_EWK, W_strong, Z_strong
# Valid regions:
# Incl, SRPhiHigh, CRWPhiHigh, CRZPhiHigh, SRPhiLow, CRWPhiLow, CRZPhiLow, SRNjet, CRWNjet, CRZNjet

debug = True
basePath = "./input/theoVariation_171019"
outPath = "./output/theoVariation_171019"

if not os.path.exists(outPath):
    os.makedirs(outPath)

outAll = TFile(outPath+"/VJetsWeights_VBFparam.root", "recreate")
outAll.Close()

channels = ["Z_strong"] #, "W_EWK", "Z_EWK", "W_strong"]
regions  = ["SR"]#, "CRW", "CRZ"]

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

        # Labels
        if channel == "W_EWK":
            channel_label = "evj_EWK"
        if channel == "Z_EWK" and region == "SR":
            channel_label = "vvj_EWK"
        if channel == "Z_EWK" and region == "CRZ":
            channel_label = "eej_EWK"
        if channel == "W_strong":
            channel_label = "evj_QCD"
        if channel == "Z_strong" and region == "SR":
            channel_label = "vvj_QCD"
        if channel == "Z_strong" and region == "CRZ":
            channel_label = "eej_QCD"
        print "\nRunning systs for channel:", channel, region

        # bin1Low, bin2Low, bin3Low, bin1High, bin2High, bin3High, binNjet
        # up, down
        # renofact, pdf, resum, ckkw

        theoUncUp= {     "renofact"     : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "resum"        : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "ckkw"         : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "pdf"          : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]}
        theoUncDown= {   "renofact"     : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "resum"        : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "ckkw"         : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
                         "pdf"          : [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0]}


        mjj_bins_xaxis = [0.8,1.,1.5,2.,3.5,5]
        dphijj_bins_yaxis = [0,1,2]
        njet_bins_zaxis = [1.5,2.5,4]
        mjj_nbins_xaxis = 5
        dphijj_nbins_yaxis = 2
        njet_nbins_zaxis = 2
        var__up = {}
        var__down = {}
        for var3 in [ "fac", "renorm", "both", "pdf", "qsf", "ckkw"]:
            var__up[var3] = TH3F(channel_label + "_" +  region + "_" + var3 + "__1up", var3 + " up reweight",        mjj_nbins_xaxis, array('d',mjj_bins_xaxis), dphijj_nbins_yaxis, array('d',dphijj_bins_yaxis), njet_nbins_zaxis, array('d',njet_bins_zaxis))
            var__down[var3] = TH3F(channel_label + "_" +  region + "_"  + var3 + "__1down", var3 + " down reweight", mjj_nbins_xaxis, array('d',mjj_bins_xaxis), dphijj_nbins_yaxis, array('d',dphijj_bins_yaxis), njet_nbins_zaxis, array('d',njet_bins_zaxis))
            var__up[var3].SetDirectory(0)
            var__down[var3].SetDirectory(0)

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

            inFile = TFile.Open(basePath+"/theoVariation_"+channel+".root")
            outFile = TFile(outPath+"/variedYields_"+channel+"_"+reg+".root", "recreate")

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
                inFile = TFile.Open(basePath+"/theoVariation_"+channel+"_"+key+".root")
                outFile = TFile(outPath+"/variedYields_"+channel+"_"+reg+".root", "update")
                thisHist = inFile.Get("jj_mass_" + reg + "_nominal")
                if(len(thisHist.GetSumw2()) == 0):
                    thisHist.Sumw2()
                varDict[key] = thisHist.Clone("h_" + key)
                varDict[key].SetDirectory(0)
                varDict[key].Write()
                inFile.Close()
                outFile.Close()

            ########################
            # Nominal
            ########################
            nbins    = 5
            mjj_bins = [0.,1.,1.5,2.,3.5]
            mjj_incl = [0.8,1000]
            systs    = ["fac", "renorm", "both"]

            inFile   = TFile.Open(outPath+"/variedYields_"+channel+"_"+reg+".root")
            outAll = TFile(outPath+"/VJetsWeights_VBFparam.root", "update")

            yieldNom    = [0.,0.,0.,0.,0.]
            largestUp   = [1.,1.,1.,1.,1.]
            largestDown = [1.,1.,1.,1.,1.]
            err_yieldNom    = [0.,0.,0.,0.,0.]
            err_largestUp   = [0.,0.,0.,0.,0.]
            err_largestDown = [0.,0.,0.,0.,0.]
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
                while binIndex < 4:
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

            ########################
            # Scale variations
            ########################
            for syst in systs :
                yieldU = [0.,0.,0.,0.,0.]
                yieldD = [0.,0.,0.,0.,0.]
                yieldUIncl = 0.
                yieldDIncl = 0.
                err_yieldU = [0.,0.,0.,0.,0.]
                err_yieldD = [0.,0.,0.,0.,0.]
                err_yieldUIncl = 0.
                err_yieldDIncl = 0.
                upHist = inFile.Get("h_" + syst + "_up")
                downHist = inFile.Get("h_" + syst + "_down")
                for iBin in range(upHist.GetNbinsX()+1):
                    binIndex = 0
                    binCenter = upHist.GetBinCenter(iBin+1)
                    if binCenter < mjj_bins[0]:
                        continue
                    while binIndex < 4:
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
                reweight_up = TH1F(channel_label + "_" +  reg + "_" + syst + "__1up", syst + " up reweight", nbins, array('d',mjj_bins_xaxis))
                reweight_down = TH1F(channel_label + "_" +  reg + "_"  + syst + "__1down", syst + " down reweight", nbins, array('d',mjj_bins_xaxis))
                reweight_up.SetDirectory(0)
                reweight_down.SetDirectory(0)
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
                    reweight_up.SetBinContent(  i+1, variationUp)
                    reweight_up.SetBinError(  i+1, err_variationUp)
                    reweight_down.SetBinContent(i+1, variationDown)
                    reweight_down.SetBinError(i+1, err_variationDown)
                    # SetBinContent(Int_t binx, Int_t biny, Int_t binz, Double_t content)
                    if "PhiLow" in reg:
                        var__up[syst].SetBinContent(  i+1, 1, 1,  variationUp)
                        var__down[syst].SetBinContent(  i+1, 1, 1,  variationDown)
                    elif "PhiHigh" in reg:
                        var__up[syst].SetBinContent(  i+1, 2, 1,  variationUp)
                        var__down[syst].SetBinContent(  i+1, 2, 1,  variationDown)
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
                if "Njet" in reg:
                    for i in range(nbins) :
                        var__up[syst].SetBinContent(  i+1, 1, 2,  variationUpIncl)
                        var__down[syst].SetBinContent(  i+1, 1, 2,  variationDownIncl)

            envelope_up = TH1F(channel_label + "_" + reg + "_"  + "_" + "envelope__1up", "Envelope up reweight", nbins, array('d',mjj_bins_xaxis))
            envelope_down = TH1F(channel_label + "_" + reg + "_"  + "_" + "envelope__1down", "Envelope down reweight", nbins, array('d',mjj_bins_xaxis))
            for i in range(nbins):
                if (debug):  print "Largest DOWN variation in bin %i: %f %%" % (i, (largestDown[i]-1)*100)
                envelope_up.SetBinContent(i+1, largestUp[i])
                envelope_up.SetBinError(i+1, err_largestUp[i])
                if (debug):  print "Largest UP variation in bin %i: %f %%" % (i, (largestUp[i]-1)*100)
                envelope_down.SetBinContent(i+1, largestDown[i])
                envelope_down.SetBinError(i+1, err_largestDown[i])
                if binItrScale < 10:
                    theoUncUp["renofact"][binItrScale]=largestUp[i]
                    theoUncDown["renofact"][binItrScale]=largestDown[i]
                    binItrScale = binItrScale+1
            theoUncUp["renofact"][binItrScale]=largestUpIncl
            theoUncDown["renofact"][binItrScale]=largestDownIncl
            envelope_up.Write()
            envelope_down.Write()

            ########################
            # PDF variations
            ########################
            avgNormalization = 1./100
            pdfYield = [0.,0.,0.,0.,0.]
            pdfYieldSq = [0.,0.,0.,0.,0.]
            varSafeOld = 0.
            pdfYieldIncl = 0.
            pdfYieldSqIncl = 0.
            err_pdfYield = [0.,0.,0.,0.,0.]
            err_pdfYieldIncl = 0.
            for i in range(100):
                thisHist = inFile.Get("h_pdf%i"%i)
                varSafe = abs(thisHist.Integral()/nomHist.Integral()-1)*100
            #    print i, thisHist.Integral(), varSafe, abs(varSafe-varSafeOld)
                if abs(varSafe-varSafeOld) > 20:
                    thisHist = nomHist
                    varSafeOld = 0
                    if(debug): print "REPLACED bin ", i, "with nominal"
                else:
                    varSafeOld = varSafe
                thisYield = [0.,0.,0.,0.,0.]
                thisYieldIncl = 0.
                err_thisYield = [0.,0.,0.,0.,0.]
                err_thisYieldIncl = 0.
                for iBin in range(thisHist.GetNbinsX()+1):
                    binIndex = 0
                    binCenter = thisHist.GetBinCenter(iBin+1)
                    if binCenter < mjj_bins[0]:
                        continue
                    while binIndex < 4:
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
            pdf_up   = TH1F(channel_label + "_" + reg + "_" + "pdf__1up",   "PDF up reweight",   nbins, array('d',mjj_bins_xaxis))
            pdf_down = TH1F(channel_label + "_" + reg + "_" + "pdf__1down", "PDF down reweight", nbins, array('d',mjj_bins_xaxis))
            pdfError = [0.,0.,0.,0.,0.]
            tmp_pdfVar=[0.,0.,0.,0.,0.]
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
                if binItrPDF < 10:
                    theoUncUp["pdf"][binItrPDF]   = 1 + tmp_pdfVar[i]
                    theoUncDown["pdf"][binItrPDF] = 1 - tmp_pdfVar[i]
                    binItrPDF = binItrPDF+1
            pdfErrorIncl = math.sqrt(pdfYieldSqIncl - (pdfYieldIncl * pdfYieldIncl))
            theoUncUp["pdf"][binItrPDF]   = 1 + pdfErrorIncl/pdfYieldIncl
            theoUncDown["pdf"][binItrPDF] = 1 - pdfErrorIncl/pdfYieldIncl
            pdf_up.Write()
            pdf_down.Write()

            ########################
            # qsf/ckkw variations
            ########################
            for wVar in ["resum", "ckkw"]:
                avgNormalization = 1./2
                qsfckkwYield = [0.,0.,0.,0.,0.]
                qsfckkwYieldSq = [0.,0.,0.,0.,0.]
                qsfckkwYieldIncl = 0.
                qsfckkwYieldSqIncl = 0.
                err_qsfckkwYield = [0.,0.,0.,0.,0.]
                err_qsfckkwYieldIncl = 0.
                if wVar == "resum":
                    wList = ["qsf025", "qsf4"]
                elif wVar == "ckkw":
                    wList = ["ckkw15", "ckkw30"]
                for i in wList:
                    thisHist = inFile.Get("h_"+i)
                    thisYield = [0.,0.,0.,0.,0.]
                    err_thisYield = [0.,0.,0.,0.,0.]
                    thisYieldIncl = 0.
                    err_thisYieldIncl = 0.
                    for iBin in range(thisHist.GetNbinsX()+1):
                        binIndex = 0
                        binCenter = thisHist.GetBinCenter(iBin+1)
                        if binCenter < mjj_bins[0]:
                            continue
                        while binIndex < 4:
                            if binCenter >= mjj_bins[binIndex] and binCenter < mjj_bins[binIndex+1] :
                                break
                            binIndex = binIndex + 1
                        thisYield[binIndex] += thisHist.GetBinContent(iBin+1)
                        thisYieldIncl += thisHist.GetBinContent(iBin+1)
                        err_thisYield[binIndex] += thisHist.GetBinError(iBin+1)*thisHist.GetBinError(iBin+1)
                        err_thisYieldIncl += thisHist.GetBinError(iBin+1)*thisHist.GetBinError(iBin+1)
                    for j in range(nbins):
                        qsfckkwYield[j]    += avgNormalization * thisYield[j]
                        qsfckkwYieldSq[j]  += avgNormalization * thisYield[j] * thisYield[j]
                        err_qsfckkwYield[j] = avgNormalization * math.sqrt(err_thisYield[binIndex])
                    qsfckkwYieldIncl   += avgNormalization * thisYieldIncl
                    qsfckkwYieldSqIncl += avgNormalization * thisYieldIncl * thisYieldIncl
                    err_qsfckkwYieldIncl = avgNormalization * math.sqrt(err_thisYieldIncl)
                qsfckkw_up   = TH1F(channel_label + "_" + reg + "_" + wVar+"__1up",   wVar+" up reweight",   nbins, array('d',mjj_bins_xaxis))
                qsfckkw_down = TH1F(channel_label + "_" + reg + "_" + wVar+"__1down", wVar+" down reweight", nbins, array('d',mjj_bins_xaxis))
                qsfckkwError = [0.,0.,0.,0.,0.]
                tmp_qsfckkwVar=[0.,0.,0.,0.,0.]
                for i in range(nbins) :
                    if(qsfckkwYield[i] == 0):
                        if(debug): print " yield is zero for bin %i"%i
                        continue
                    qsfckkwError[i] = math.sqrt(qsfckkwYieldSq[i] - (qsfckkwYield[i] * qsfckkwYield[i]))
                    tmp_qsfckkwVar[i] = qsfckkwError[i]/qsfckkwYield[i]
                    if (debug):  print wVar+" variation in bin %i: %f %%" % (i, tmp_qsfckkwVar[i]*100)
                    qsfckkw_up.SetBinContent(  i+1, 1 + tmp_qsfckkwVar[i])
                    qsfckkw_down.SetBinContent(i+1, 1 - tmp_qsfckkwVar[i])
                    qsfckkw_up.SetBinError(  i+1, err_qsfckkwYield[i])
                    qsfckkw_down.SetBinError(i+1, err_qsfckkwYield[i])
                    if binItr[wVar] < 10:
                        theoUncUp[wVar][binItr[wVar]]   = 1 + tmp_qsfckkwVar[i]
                        theoUncDown[wVar][binItr[wVar]] = 1 - tmp_qsfckkwVar[i]
                        binItr[wVar] = binItr[wVar]+1
                qsfckkwErrorIncl = math.sqrt(qsfckkwYieldSqIncl - (qsfckkwYieldIncl * qsfckkwYieldIncl))
                theoUncUp[wVar][binItr[wVar]]   = 1 + qsfckkwErrorIncl/qsfckkwYieldIncl
                theoUncDown[wVar][binItr[wVar]] = 1 - qsfckkwErrorIncl/qsfckkwYieldIncl
                qsfckkw_up.Write()
                qsfckkw_down.Write()
            inFile.Close()
            for var3 in [ "fac", "renorm", "both", "pdf", "qsf", "ckkw"]:
                var__up[var3].Write()
                var__down[var3].Write()
            outAll.Close()



        f = open(outPath+"/listTheorySyst", "w")
        if (debug): print "\n=====================\n"
        for theo in theoUncUp:
            print region+"up="+theo+"_"+channel, ",".join([str('{0:.5g}'.format(x)) for x in theoUncUp[theo]])
        print ""
        for theo in theoUncDown:
            print region+"down="+theo+"_"+channel, ",".join([str('{0:.5g}'.format(x)) for x in theoUncDown[theo]])

