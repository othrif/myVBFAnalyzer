#!/usr/bin/env python
import os
import sys
import ROOT
import VBFAnalysis.Style
import VBFAnalysis.listSamples 
from optparse import OptionParser
import math
import time


p = OptionParser()

p.add_option('--lumi', type='float', default=36.1, help='Defines the integrated luminosity [fb^-1]. The histograms are scaled acordingly.')
p.add_option('-i', '--input', type='string', default="input.txt", help='input file. A textfile containing all absolute paths to the sample files')
p.add_option('-o', '--output', type='string', default="out.root", help='output root file.')
p.add_option('--syst', type='string', default="Nominal", help='Key to the systematic dictonarie in listSamples.py that defines the systematics to run on.')

for option in p.option_list:
    if option.default != ("NO", "DEFAULT"):
        option.help += (" " if option.help else "") + "[default: %default]"

(options, args) = p.parse_args()  


def cutflowHists(iDir):
    cfDic=VBFAnalysis.Style.cutflow
    for k in cfDic:
        if k in iDir.GetPath():
            htemp=ROOT.TH1D("cutflow","cutflow",len(cfDic[k]),0,len(cfDic[k]))
            htemp.Sumw2()
            for b in range(1,len(cfDic[k])+1):
                htemp.GetXaxis().SetBinLabel(b,cfDic[k][b-1])
            htemp.Write()





def makeOutFile(sysList):
    processList=VBFAnalysis.listSamples.allProcesses 
    outF=ROOT.TFile(options.output,"recreate")
    lvlOne=[]
    lvlTwo=[]
    for syst in sysList:
        lvlOne.append(outF.mkdir("pass_sr_allmjj_nn_"+syst))
        for k in ['ep','en','up','un','l','e','u']:
            lvlOne.append(outF.mkdir("pass_"+"wcr"+"_allmjj_"+k+"_"+syst))
        for k in ['ee','uu','ll']:
            lvlOne.append(outF.mkdir("pass_"+"zcr"+"_allmjj_"+k+"_"+syst))
    for k in lvlOne:
        for p in processList:
            lvlTwo.append(k.mkdir("plotEvent_"+p))
    for j in lvlTwo:
        j.cd()
        for v in VBFAnalysis.Style.variables:
            htemp=ROOT.TH1D(v,v,VBFAnalysis.Style.varBinning[v][0],VBFAnalysis.Style.varBinning[v][1],VBFAnalysis.Style.varBinning[v][2])
            htemp.Sumw2()
            htemp.Write()
        cutflowHists(j)
    outF.Write()
    outF.Close()


def AddOverflow(hist):
    lb=hist.GetNbinsX()
    ob=hist.GetNbinsX()+1
    lbc=hist.GetBinContent(lb)
    obc=hist.GetBinContent(ob)
    lbe=hist.GetBinError(lb)
    obe=hist.GetBinError(ob)
    hist.SetBinContent(lb,lbc+obc)
    hist.SetBinError(lb,math.sqrt(lbe**2+obe**2))


def hist_from_file(rfileName, hname, newTitle):
    f=ROOT.TFile(rfileName)
    hist = f.Get(hname)
    if hist==None:
        return None
    hist.SetDirectory(0)
    f.Close()
    hist.SetNameTitle(newTitle, newTitle)
    if newTitle in VBFAnalysis.Style.styleDict:
        VBFAnalysis.Style.setStyles(hist, VBFAnalysis.Style.styleDict[newTitle])
    AddOverflow(hist)
    return hist

# TODO make this in a different way
def make_bkgs_hist(rfileName,syst):
    for r in VBFAnalysis.listSamples.regions:
        for v in (VBFAnalysis.Style.variables+["cutflow"]):
            totalHist=None
            for p in VBFAnalysis.listSamples.MCbackgrounds:
                if totalHist==None:
                    totalHist=hist_from_file(rfileName, r+"_"+syst+"/plotEvent_"+p+"/"+v, p)
                else:
                    totalHist.Add(hist_from_file(rfileName, r+"_"+syst+"/plotEvent_"+p+"/"+v, p))
            if totalHist!=None:
                trfile=ROOT.TFile(rfileName,"UPDATE")
                bkgHist=trfile.Get(r+"_"+syst+"/plotEvent_"+"bkgs"+"/"+v)
                for i in range(1,totalHist.GetNbinsX()+1):
                    bkgHist.SetBinContent(i,totalHist.GetBinContent(i))
                    bkgHist.SetBinError(i,totalHist.GetBinError(i))
                trfile.Write()
                trfile.Close()
            

# TODO make this in a different way
def make_data_hist(rfileName):
    for r in VBFAnalysis.listSamples.regions:
        for v in (VBFAnalysis.Style.variables+["cutflow"]):
            totalHist=None
            for p in VBFAnalysis.listSamples.dataSets:
                if totalHist==None:
                    totalHist=hist_from_file(rfileName, r+"_Nominal/plotEvent_"+p+"/"+v, p)
                else:
                    totalHist.Add(hist_from_file(rfileName, r+"_Nominal/plotEvent_"+p+"/"+v, p))
            if totalHist!=None:
                trfile=ROOT.TFile(rfileName,"UPDATE")
                dataHist=trfile.Get(r+"_Nominal/plotEvent_"+"data"+"/"+v)
                for i in range(1,totalHist.GetNbinsX()+1):
                    dataHist.SetBinContent(i,totalHist.GetBinContent(i))
                    dataHist.SetBinError(i,totalHist.GetBinError(i))
                trfile.Write()
                trfile.Close()
            



def main():
    systList=VBFAnalysis.listSamples.systDict[options.syst]
    print "Running with the following systematics:",systList
    makeOutFile(systList)


    sampsToRun=open(options.input)
    # Run loop
    pathToScript=os.path.realpath(__file__).strip(__file__.split("/")[-1])
    ROOT.gROOT.LoadMacro(pathToScript+"../python/Plotting/CxxCode/plotEvents.C+") 
    for path in sampsToRun.readlines():
        inputFileName=path.strip("\n")

        for syst in systList:
            rfile=ROOT.TFile(inputFileName,"READ")
            sToRemove=((rfile.GetName().split("/"))[-1]).replace(".root","")
            LOKrfile=rfile.GetListOfKeys()
            if sToRemove+syst in LOKrfile:
                iTree=rfile.Get(sToRemove+syst)
                print sToRemove+syst
                if iTree.GetEntriesFast()==0:
                    print "!!!Warning!!!: Tree is empty",sToRemove+syst, path
                ROOT.runLoop(iTree, syst, options.lumi*1000, options.output)
            else:
                print "!!!WARNING!!!: Systematic Tree not found!", sToRemove+syst, path


    for syst in systList:
        make_bkgs_hist(options.output,syst)
    make_data_hist(options.output)


if __name__=="__main__":
    start=time.time()
    main()
    end=time.time()
    print "Time elapsed",end-start
