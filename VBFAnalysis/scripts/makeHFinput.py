#!/usr/bin/env python
import os, sys, time
from optparse import OptionParser
import ROOT
import VBFAnalysis.systematics
import csv



p = OptionParser()

p.add_option('--lumi', type='float', default=36.1, help='Integrated luminosity [1/fb]')
p.add_option('-i', '--input', type='string', default="input.txt", help='input file')
p.add_option('-o', '--output', type='string', default="output.root", help='output file')
p.add_option('-s', '--syst', type='string', default="Nominal", help='defines the list of systematics')
p.add_option('--cut-config', type='string', default=os.path.expandvars("${SourceArea}/VBFAnalysis/data/cutConfig.txt"), help='Defines all different cut variations')

p.add_option('--nLow', type='int', default=1, help='lowest bin which will be filled')
p.add_option('--nHigh', type='int', default=1, help='highest bin which will be filled')

p.add_option('--Debug', action='store_true', help='Produces usefull information for debugging.')

for option in p.option_list:
    if option.default != ("NO", "DEFAULT"):
        option.help += (" " if option.help else "") + "[default: %default]"

(options, args) = p.parse_args() 




class cutClass(object):
    def __init__(self, name, start, step, nLow, nHigh):
        self.name=name
        self.start=float(start)
        self.step=float(step)
        self.nLow=int(nLow)
        self.nHigh=int(nHigh)



def makeBinInfo():
    infoFile=open(options.output[:-5]+"_info.txt","w")
    infoFile.write("nBin jj_mass jj_dphi jj_deta met_tst_et n_jet")
    infoFile.write("\n")

    cuts={}
    with open(options.cut_config) as csvfile:
        reader=csv.DictReader(csvfile)
        for row in reader:
            cuts[row['Cut']]=cutClass(row['Cut'],row['start'],row['step'],row['nLow'],row['nHigh'])
    Nbin=0
    for i in range(cuts["jj_mass"].nLow,cuts["jj_mass"].nHigh+1):
        for j in range(cuts["jj_dphi"].nLow,cuts["jj_dphi"].nHigh+1):
            for k in range(cuts["jj_deta"].nLow,cuts["jj_deta"].nHigh+1):
                for l in range(cuts["met_tst_et"].nLow,cuts["met_tst_et"].nHigh+1):
                    for a in range(cuts["n_jet"].nLow,cuts["n_jet"].nHigh+1):
                        Nbin+=1
                        infoFile.write(str(Nbin)+" "+str(cuts["jj_mass"].start+cuts["jj_mass"].step*i) + " " + str(cuts["jj_dphi"].start+cuts["jj_dphi"].step*j) + " " + str(cuts["jj_deta"].start+cuts["jj_deta"].step*k) + " " + str(cuts["met_tst_et"].start+cuts["met_tst_et"].step*l) + " " + str(cuts["n_jet"].start+cuts["n_jet"].step*a) + "\n")  
    infoFile.close()
    return Nbin

    



def makeHistStructure(outFile, inputFnames, systList):
    regions=["SR","oneElePosCR","oneEleNegCR","oneElePosLowSigCR","oneEleNegLowSigCR","oneMuPosCR","oneMuNegCR", "twoEleCR", "twoMuCR"]
    mRegion=["1","2","3"]
    HL=["High","Low"]

    Nbin=makeBinInfo() 

    outFile.cd()
    for inputF in inputFnames:
        procName=(inputF.split("/")[-1])[:-5]
        for mR in mRegion:
            for reg in regions:
                if procName=="data":
                    hname="h"+procName+"_NONE_"+reg+mR+"_obs_cuts"
                    (ROOT.TH1D(hname,hname,Nbin,0,Nbin)).Write()
                    continue
                for syst in systList:
                    if syst=="Nominal":
                        hname="h"+procName+"_VBFjetSel_"+mR+"Nom"+"_"+reg+mR+"_obs_cuts"
                        (ROOT.TH1D(hname,hname,Nbin,0,Nbin)).Write()
                        continue
                    for hl in HL:
                        hname="h"+procName+"_VBFjetSel_"+mR+(syst.replace("__1up","")).replace("__1down","")+hl+"_"+reg+mR+"_obs_cuts"
                        if not(hname in [h.GetName() for h in outFile.GetListOfKeys()]): # This just prevents the creation of a new cycle. i could also use TObject.kOverwrite as option in .Write()
                            (ROOT.TH1D(hname,hname,Nbin,0,Nbin)).Write()



def main():
    start=time.time()
    inputTXTFile=open(options.input)
    inputFileNames=[n.strip("\n") for n in inputTXTFile.readlines()]
    systObj=VBFAnalysis.systematics.systematics(options.syst)
    systList=systObj.systematicsList

    ROOT.gROOT.LoadMacro(os.path.expandvars("${SourceArea}/VBFAnalysis/src/treeClass.C"))
    outF=ROOT.TFile(options.output,"RECREATE")
    makeHistStructure(outF, inputFileNames, systList) 
    for f in inputFileNames:
        print "Running on: ",f
        if f.split("/")[-1]=="data.root":
            syst="Nominal"
            ROOT.runLoop(outF, f, (f.split('/')[-1])[0:-5],syst.split("__")[0],"__"+syst.split("__")[-1], options.nLow,options.nHigh,options.output[:-5]+"_info.txt", options.lumi)
            continue

        for syst in systList:
            ROOT.runLoop(outF, f, (f.split('/')[-1])[0:-5],syst.split("__")[0],"__"+syst.split("__")[-1], options.nLow,options.nHigh,options.output[:-5]+"_info.txt", options.lumi)
    outF.Write("",ROOT.TObject.kOverwrite) # The kOverwrite prevents the creation of a new cycle.
    outF.Close()
    print "time elapsed:",time.time()-start

if __name__=="__main__":
    main()
