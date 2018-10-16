#!/usr/bin/env python

# Allows to easily create several kinds of LaTeX tables from the out of makeInput.py.


import os
import sys
import ROOT
from optparse import OptionParser
import VBFAnalysis.listSamples as listSamples
import VBFAnalysis.Style as Style



p = OptionParser() #TODO parser is not working correctly while importing from drawPlot.py
p
p.add_option('-i', '--input', type='string', default="out.root", help='input file. Created from plotEvent.py')
p.add_option('-o', '--output', type='string', default="tables.txt", help='All the tables will be written to this file')
p.add_option('--yields', action='store_true', help='writes yield table')
p.add_option('--cutflow', action='store_true', help='writes cutflow table')
p.add_option('--Debug', action='store_true', help='Produces usefull information for debugging.') # Is needed because hist_from_file in drawPlot.py uses options.Debug

for option in p.option_list:
    if option.default != ("NO", "DEFAULT"):
        option.help += (" " if option.help else "") + "[default: %default]"

(options, args) = p.parse_args()  


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

def writeLines(lines, fname):
    fout=open(fname,"a")
    for l in lines:
        fout.write(l)
        fout.write("\n")
    fout.close()



def yieldTable(fname): #TODO add errors
    lines=[]
    var="jj_mass"
    lines.append("\\begin{tabular}{"+(1+len(listSamples.regions))*"c|"+"}")
    lines.append("Process & "+' & '.join([r.split("_")[1]+"-"+r.split("_")[3] for r in listSamples.regions]) + " \\\\")
    lines.append("\\hline")
    for p in listSamples.MCbackgrounds:
        lines.append(p)
    lines.append("\\hline")
    lines.append("signal") #TODO split signal, right now its VBFH and ggFH
    lines.append("bkg")
    lines.append("data")

    for region in listSamples.regions:
        print region
        bkgs=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"bkgs"+"/"+var, "bkgs")
        sig=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"signal"+"/"+var, "signal")
        data=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"data"+"/"+var, "data")
        fullStack=get_HStack(region, var, options.input) 
        for l in range(3,len(lines)-4): #TODO Unnessecary high amount of if statemants. Make this easier
            for h in fullStack:
                histWasFound=False
                if h.GetName() in lines[l]:
                    lines[l]+=" & "+str(int(h.Integral()))
                    histWasFound=True
                    break 
            if not histWasFound: lines[l]+=" & 0"
        try:
            lines[-3]+=" & "+str(int(sig.Integral()))
        except:
            lines[-3]+=" & 0"
        lines[-2]+=" & "+str(int(bkgs.Integral()))
        lines[-1]+=" & "+str(int(data.Integral()))
    for l in range(3,len(lines)):
        if "hline" in lines[l]:
            continue
        lines[l]+=" \\\\"
    lines.append("\\end{tabular}")

    print len(lines)
    writeLines(lines, fname)

def cutflowTable(fname, region):
    # Cuts data eff fulleff bkg eff fulleff data/bkg signal eff fulleff signal/bkg
    lines=[]
    lines.append(region)
    var="cutflow"
    dataCF=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"data"+"/"+var, "data")
    bkgCF=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"bkgs"+"/"+var, "bkgs")
    sigCF=hist_from_file(options.input, region+"_Nominal/"+"plotEvent_"+"signal"+"/"+var, "signal")

    lines.append("\\begin{tabular}{"+12*"c|"+"}")
    lines.append("Cuts &"+ " data &"+ " eff &"+ " fulleff &"+ " bkg &"+ " eff &"+ " fulleff &"+ " data/bkg &"+ " signal &"+ " eff &"+ " fulleff &"+ " S/B")
    lines.append("\\hline")
    fdataBC=dataCF.GetBinContent(1)
    fbkgBC=bkgCF.GetBinContent(1)
    fsigBC=sigCF.GetBinContent(1)
    for b in range(1,dataCF.GetNbinsX()+1):
        pdataBC=dataCF.GetBinContent(b-1)
        pbkgBC=bkgCF.GetBinContent(b-1)
        psigBC=sigCF.GetBinContent(b-1)
        if b==1:
            pdataBC=dataCF.GetBinContent(b)
            pbkgBC=bkgCF.GetBinContent(b)
            psigBC=sigCF.GetBinContent(b)

        dataBC=dataCF.GetBinContent(b)
        bkgBC=bkgCF.GetBinContent(b)
        sigBC=sigCF.GetBinContent(b)
        if region!="pass_sr_allmjj_nn": #TODO fix this
            sigBC=0.0001
            psigBC=0.0001
            fsigBC=0.0001
        lines.append((dataCF.GetXaxis().GetBinLabel(b)).replace("_","-")+" & "+str(int(dataBC))+" & "+str(round(dataBC/pdataBC,3))+" & "+str(round(dataBC/fdataBC,3))+" & "+str(int(bkgBC))+" & "+str(round(bkgBC/pbkgBC,3))+" & "+str(round(bkgBC/fbkgBC,3))+" & "+str(round(dataBC/bkgBC,3))+" & "+str(int(sigBC))+" & "+str(round(sigBC/psigBC,3))+" & "+str(round(sigBC/fsigBC,3))+" & "+str(round(sigBC/bkgBC,3)))
    lines.append("\\hline")
    for l in range(1,len(lines)):
        if "hline" in lines[l]:
            continue
        lines[l]+=" \\\\"
    lines.append("\\end{tabular}")

    writeLines(lines, fname)


def main():
    f=open(options.output,"w")
    f.close()
    if options.yields: yieldTable(options.output)
    if options.cutflow:
        reg=[l for l in listSamples.regions if (('e'==l[-2]) or ('u'==l[-2]) or ('nn' in l))]
        for r in reg:
            print r
            cutflowTable(options.output, r)


if __name__=='__main__':
    main()
