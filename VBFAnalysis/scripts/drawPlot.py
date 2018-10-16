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
p.add_option('--logy', action='store_true', help='Sets log scale on y axis')
p.add_option('--syst', action='store_true', help='Draws all systematic errors and MC stat errors')
p.add_option('--data', action='store_true', help='Draw data')
p.add_option('--signal', action='store_true', help='Draw the signal')
p.add_option('--MC', action='store_true', help='Draws the full MC background')
p.add_option('--stack', action='store_true', help='Draws the MC with each contribution stacked.')
p.add_option('--saveAs', type='string', help='Saves the canvas in a given format. example argument: pdf')
p.add_option('--region', type='string', default="pass_sr_allmjj_nn", help='Defines the region that is plotted. You can give more than one region if you sperate them by , (e.g.: --region pass_sr_allmjj_nn,pass_zcr_allmjj_ll). If "all" is given all the regions are plotted')
p.add_option('--var', type='string', default="jj_mass", help='Variable that is plotted. can give multiple variables or even "all" as parameter (see --region)')
p.add_option('-i', '--input', type='string', default="out.root", help='input file. Created from plotEvent.py')
p.add_option('--ratio', action='store_true', help='produces Data/MC plot. Only works with option --draw-data')
p.add_option('-q', '--quite', action='store_true', help='activates Batch mode')
p.add_option('--Debug', action='store_true', help='Produces usefull information for debugging.')

for option in p.option_list:
    if option.default != ("NO", "DEFAULT"):
        option.help += (" " if option.help else "") + "[default: %default]"

(options, args) = p.parse_args()  



#TODO dont constantly reopen the input root file.


def make_pull_canvas():
    c=ROOT.TCanvas("pull_canvas","Canvas",600,720)
    c.Divide(1,2)
    c.cd(1)
    ROOT.gPad.SetBottomMargin(0)
    ROOT.gPad.SetRightMargin(0.1)
    ROOT.gPad.SetPad(0,0.3,1,1)
    c.cd(2)
    ROOT.gPad.SetTopMargin(0)
    ROOT.gPad.SetBottomMargin(0.25)
    ROOT.gPad.SetRightMargin(0.1)
    ROOT.gPad.SetPad(0,0,1,0.3)
    return c

def removeLabel(leg, name):
    LOP=leg.GetListOfPrimitives()
    nothingWasRemoved=True
    for prim in LOP:
        if prim.GetLabel()==name:
            LOP.Remove(prim) 
            nothingWasRemoved=False
    if nothingWasRemoved:
        print name, "was not found in labels and was not removed. List of labels:"
        for prim in LOP:
            print prim.GetLabel()

def make_legend(can):
    leg=can.BuildLegend(0.65,0.7,0.85,0.9)
    leg.SetBorderSize(0)
    leg.SetFillStyle (0)
    leg.SetTextFont(42)    
    leg.SetTextSize(0.04)         
    #leg.SetNColumns  (2)
    removeLabel(leg, 'dummy')
    if options.stack:
        removeLabel(leg, 'bkgs')
    nEntries=len(leg.GetListOfPrimitives())
    leg.SetY1(0.9-nEntries*0.04)
    return leg


def hist_from_file(rfileName, hname, newTitle):
    f=ROOT.TFile(rfileName)
    hist = f.Get(hname)
    if hist==None:
        if options.Debug: print "This hist was not found",hname
        return None
    if hist.Integral()==0:
        if options.Debug: print "This hist has no entries",hname
        return None
    hist.SetDirectory(0)
    f.Close()
    hist.SetNameTitle(newTitle, newTitle)
    if newTitle in Style.styleDict:
        Style.setStyles(hist, Style.styleDict[newTitle])
    if options.Debug: print hist.GetName(), hist.Integral(), "(",hist.GetEntries(),")"
    return hist

def get_HStack(region, var, rfileName):
    backgrounds=listSamples.MCbackgrounds
    hstack=ROOT.THStack("Bkgs","Bkgs")
    hlist=[]
    for p in backgrounds:
        htemp=(hist_from_file(rfileName, region+"_Nominal/plotEvent_"+p+"/"+var, p))
        if htemp!=None:
            hlist.append(htemp)
    hlist.sort(key=lambda x: x.Integral())
    for h in hlist:
        hstack.Add(h)
    return hstack


#TODO make AsymSysErrors with TGraphAsymmErrors
def getSymSysErrors(rfileName, centralHist, region, var):
    rfile=ROOT.TFile(rfileName)
    # This will put all the systematics hists in the list systList
    LOK=rfile.GetListOfKeys()
    systList=[]
    for i in LOK:
        if region in str(i):
            systList.append(str(i)[20:-16])
            if "Nominal" in  systList[-1]: #TODO make this better
                systList.pop(-1)
    rfile.Close()
    # Calculating the errors for each systematic and bin
    systBkgsHists=[]
    sysErrorDict={} # This dict holds the variation (i.e. withVariation-centralValue) for each systematic and bin
    for sys in systList:
        systBkgsHists.append(hist_from_file(rfileName, sys+"/plotEvent_bkgs/"+var, sys))
        sysErrorDict[sys.replace(region+"_","")]={}
    for bini in range(1,centralHist.GetNbinsX()+1): #TODO underflow/overflow bin are for now ignored
        centralValue=centralHist.GetBinContent(bini)
        upSquared=0
        downSquared=0
        for sysH in systBkgsHists:
            if sysH==None:
                continue # TODO this is not so nice
            diff=sysH.GetBinContent(bini)-centralValue
            sysErrorDict[sysH.GetName().replace(region+"_","")][bini]=diff
            if diff>=0:
                upSquared+=diff**2
            else:
                downSquared+=abs(diff)**2
        sysError=(math.sqrt(upSquared) + math.sqrt(downSquared)) / 2. 
        #centralHist.SetBinContent(bini, centralValue+(math.sqrt(upSquared) - math.sqrt(downSquared))/2) #TODO make this work together with draw_MC
        MCstatE=centralHist.GetBinError(bini) # TODO check that this is correct.
        centralHist.SetBinError(bini, math.sqrt(sysError**2+MCstatE**2))
        if options.Debug: print "bini, MCstat, sysError (up, down):",bini, MCstatE, sysError,"(",math.sqrt(upSquared),",",math.sqrt(downSquared),")"
    if options.Debug: print sysErrorDict


    
        
###############################################
#################### main #####################
###############################################

def main():
    if options.quite:
        ROOT.gROOT.SetBatch(True)

    ATLAS.Style()
    ROOT.gStyle.SetMarkerSize(0)
    if options.ratio:
        can = make_pull_canvas()
        can.cd(1)
    else:
        can = ROOT.TCanvas("Stack", "Stack", 600, 600)
        ROOT.gPad.SetRightMargin(0.1)
    can.Draw()

    regions=[]
    variables=[]

    if options.region=="all":
        regions=listSamples.regions
    else:
        regions=[r for r in options.region.split(",")] 
    
    if options.var=="all":
        variables=Style.variables
    else:
        variables=[r for r in options.var.split(",")] 



    # starting the loop over all regions and variables
    for variable in variables:
        for region in regions:
            bkgs=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"bkgs"+"/"+variable, "bkgs")


            DummyHist=ROOT.TH1F("dummy","dummy",1,Style.varBinning[variable][1],Style.varBinning[variable][2])
            maxScale=1.4
            if options.logy:
                ROOT.gPad.SetLogy()
                maxScale=14
            DummyHist.SetMaximum(bkgs.GetMaximum()*maxScale)
            DummyHist.SetMinimum(0.1)
            DummyHist.GetXaxis().SetNdivisions(505,True)
            DummyHist.Draw("hist")
            DummyHist.GetYaxis().SetTitle("Entries")
            DummyHist.GetXaxis().SetTitle(variable)


            if options.MC:
                bkgs.Draw("histsame")
                systHist=bkgs.Clone()
                if options.syst:
                    getSymSysErrors(options.input, systHist, region, variable)
                systHist.SetFillColor(1)
                systHist.SetFillStyle(3018)
                ROOT.gStyle.SetErrorX(0.5)
                systHist.SetLineWidth(0)
                if options.syst:
                    systHist.SetNameTitle("Systematics","Systematics")
                else:
                    systHist.SetNameTitle("MCStatError","MCStatError")

                if options.stack:
                    fullStack=get_HStack(region, variable, options.input) 
                    fullStack.Draw("histsame") #TODO PFC not reliable. Give each process a style in Style.py
                systHist.Draw("same e2")

            if options.data: #TODO allow splitting of data into 15/16/17
                data=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"data"+"/"+variable, "data")
                data.SetMarkerStyle(20)
                if data.GetMaximum()>bkgs.GetMaximum()/maxScale:
                    DummyHist.SetMaximum(data.GetMaximum()*maxScale)
                data.Draw("PsameE1")

            if options.signal:
                sig=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"signal"+"/"+variable, "signal")
                try:
                    sig.Draw("samehist")
                except:
                    print "Warning: Signal hist is None"
            



            leg=make_legend(ROOT.gPad)
            leg.Draw()

            texts = ATLAS.getATLASLabels(can, 0.2, 0.88, options.lumi, selkey=region)
            for text in texts:
                text.Draw()

            if options.ratio and options.data: #TODO make this more compact.
                can.cd(2)
                dataClone=data.Clone()
                straightLine=data.Clone()

                Style.setStyles(dataClone,[1,0,2,2,3018,1,20,1.2])
                Style.setStyles(straightLine,[1,1,1,0,0,0,0,0])
                for b in range(straightLine.GetNbinsX()+2):
                    straightLine.SetBinContent(b,1)
                if options.syst:
                    dataClone.Divide(systHist)
                else:
                    dataClone.Divide(bkgs)
                dataClone.GetXaxis().SetTitle(variable)
                dataClone.GetXaxis().SetTitleOffset(0.8)
                dataClone.GetXaxis().SetTitleSize(0.05*500/220)
                dataClone.GetXaxis().SetLabelSize(0.05*500/220)
                dataClone.GetXaxis().SetNdivisions(505,True)
                dataClone.GetYaxis().SetRangeUser(0,2.1)
                dataClone.GetYaxis().SetTitle("Data/MC")
                dataClone.GetYaxis().SetTitleOffset(0.4)
                dataClone.GetYaxis().SetTitleSize(0.05*500/220)
                dataClone.GetYaxis().SetLabelSize(0.05*500/220)
                dataClone.GetYaxis().SetNdivisions(506,True)
                if options.syst:
                    dataClone.Draw("E")
                else:
                    dataClone.Draw("E2")
                straightLine.Draw("samehist")
                can.cd(1)
                ROOT.gPad.RedrawAxis()
                can.cd(2)
                ROOT.gPad.RedrawAxis()

            can.RedrawAxis() # Moves axis ticks agian in front of hists
            can.Modified()
            can.Update()

            if options.saveAs:
                can.SaveAs(region+"_"+variable+"."+options.saveAs)
            if not options.quite:
                raw_input("Press Enter to continue")
            del DummyHist




if __name__=='__main__':
    main()
