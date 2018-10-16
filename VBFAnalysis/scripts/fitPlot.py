#!/usr/bin/env python

import os
import sys
import ROOT
import math
import VBFAnalysis.ATLAS as ATLAS
import VBFAnalysis.Style as Style
from optparse import OptionParser
import VBFAnalysis.listSamples as listSamples


p = OptionParser()

p.add_option('--lumi', type='float', default=36.1, help='Defines the integrated luminosity shown in the label')
p.add_option('--nBin', type='int', default=1, help='Defines which bin is plotted')
p.add_option('--syst', action='store_true', help='Draws all systematic errors and MC stat errors')
p.add_option('--data', action='store_true', help='Draw data')
p.add_option('--signal', action='store_true', help='Draw the signal')
p.add_option('--MC', action='store_true', help='Draws the full MC background')
p.add_option('--stack', action='store_true', help='Draws the MC with each contribution stacked.')
p.add_option('--saveAs', type='string', help='Saves the canvas in a given format. example argument: pdf')
p.add_option('-i', '--input', type='string', default="output.root", help='input file. Created from plotEvent.py')
p.add_option('--ratio', action='store_true', help='produces Data/MC plot. Only works with option --draw-data')
p.add_option('-q', '--quite', action='store_true', help='activates Batch mode')

for option in p.option_list:
    if option.default != ("NO", "DEFAULT"):
        option.help += (" " if option.help else "") + "[default: %default]"

(options, args) = p.parse_args()  


def get_THStack_sum(hstack):
	li = hstack.GetHists()
	tot_hist=None
	for i in li:
		if tot_hist==None:
			tot_hist=i.Clone("Total_MC")
		else:
			tot_hist.Add(i)
	return tot_hist


def main():

    can=ROOT.TCanvas("c","c",1000,600)
    can.SetLogy()

    dummyHist=ROOT.TH1F("dummy","",27,0,27)
    dummyHist.SetStats(0)


    hDict={}
    histNames=["signal", "W_strong", "Z_strong", "W_EWK", "Z_EWK", "ttbar"]



    regDict={}
    regDict["SR1"]=25
    regDict["SR2"]=26
    regDict["SR3"]=27
    regDict["oneMuNegCR1"]=13
    regDict["oneMuNegCR2"]=14
    regDict["oneMuNegCR3"]=15
    regDict["oneMuPosCR1"]=16
    regDict["oneMuPosCR2"]=17
    regDict["oneMuPosCR3"]=18
    regDict["oneEleNegCR1"]=7
    regDict["oneEleNegCR2"]=8
    regDict["oneEleNegCR3"]=9
    regDict["oneElePosCR1"]=10
    regDict["oneElePosCR2"]=11
    regDict["oneElePosCR3"]=12
    regDict["twoMuCR1"]=22
    regDict["twoEleCR1"]=19
    regDict["twoMuCR2"]=23
    regDict["twoEleCR2"]=20
    regDict["twoMuCR3"]=24
    regDict["twoEleCR3"]=21
    regDict["oneEleNegLowSigCR1"]=1
    regDict["oneEleNegLowSigCR2"]=2
    regDict["oneEleNegLowSigCR3"]=3
    regDict["oneElePosLowSigCR1"]=4
    regDict["oneElePosLowSigCR2"]=5
    regDict["oneElePosLowSigCR3"]=6

    #setting dummyHist
    for k in regDict:
        dummyHist.GetXaxis().SetBinLabel(regDict[k],k)
    dummyHist.SetMaximum(1500)
    dummyHist.SetMinimum(1)
    dummyHist.GetYaxis().SetTitle("Events")
    dummyHist.Draw()



    hists=[]
    for hname in histNames[::-1]:
        hists.append(ROOT.TH1F(hname,hname,27,0,27))
        hDict[hname]=hists[-1]
    data=ROOT.TH1F("data","data",27,0,27)


    #Styles
    Style.setStyles(data,[1,0,2,0,0,1,20,1.2])
    Style.setStyles(hDict["signal"],[2,2,3,0,0,0,0,0])
    Style.setStyles(hDict["Z_strong"],[1,1,1,46,1001,0,0,0])
    Style.setStyles(hDict["Z_EWK"],[1,1,1,8,1001,0,0,0])
    Style.setStyles(hDict["W_strong"],[1,1,1,9,1001,0,0,0])
    Style.setStyles(hDict["W_EWK"],[1,1,1,5,1001,0,0,0])
    Style.setStyles(hDict["ttbar"],[1,1,1,0,1001,0,0,0])

    # loop over all hists in input file and add their content to the right hist
    rfile=ROOT.TFile(options.input)
    LOK=rfile.GetListOfKeys()
    for key in LOK:
        htemp=rfile.Get(key.GetName())
        if htemp.InheritsFrom('TH1'):
            hname=htemp.GetName()
            if not(("Nom" in hname) or ("NONE" in hname)): continue
            binC=htemp.GetBinContent(options.nBin)
            proc=(hname.split("_")[0])[1:]
            subproc=(hname.split("_")[1])
            if proc in ["VBFH125","ggFH125","VH125"]:
                hDict["signal"].AddBinContent(regDict[hname.split("_")[-3]],binC)
            elif proc+"_"+subproc in ["W_strong"]:
                hDict["W_strong"].AddBinContent(regDict[hname.split("_")[-3]],binC)
            elif proc+"_"+subproc in ["W_EWK"]:
                hDict["W_EWK"].AddBinContent(regDict[hname.split("_")[-3]],binC)
            elif proc+"_"+subproc in ["Z_strong"]:
                hDict["Z_strong"].AddBinContent(regDict[hname.split("_")[-3]],binC)
            elif proc+"_"+subproc in ["Z_EWK"]:
                hDict["Z_EWK"].AddBinContent(regDict[hname.split("_")[-3]],binC)
            elif proc in ["ttbar"]:
                hDict["ttbar"].AddBinContent(regDict[hname.split("_")[-3]],binC)
            elif proc in ["data"]:
                data.AddBinContent(regDict[hname.split("_")[-3]],binC)
            else:
                print hname, "could not be identified correctly!"

    hStack=ROOT.THStack()
    for h in hists:
        hStack.Add(h)
    hStack.Draw("samehist")
    data.Draw("Esame")
    can.BuildLegend() #TODO make legend better

    print "region data bkg"
    for i in regDict:
        print i, data.GetBinContent(regDict[i]), get_THStack_sum(hStack).GetBinContent(regDict[i])

    


    can.Modified()
    can.Update()
    raw_input("Press Enter to continue")
            


if __name__=='__main__':
    main()
