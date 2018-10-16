#!/usr/bin/env python
import os
import sys
import VBFAnalysis.HTCsubmit
from optparse import OptionParser
import VBFAnalysis.systematics


p = OptionParser()

p.add_option('--lumi', type='float', default=36.1, help='Integrated luminosity [1/fb]')
p.add_option('-i', '--input', type='string', default="fullinput.txt", help='input file')
p.add_option('-o', '--output', type='string', default="output.root", help='output file')
p.add_option('-s', '--syst', type='string', default="Nominal", help='defines the list of systematics')
p.add_option('--cut-config', type='string', default=os.path.expandvars("${SourceArea}/VBFAnalysis/data/cutConfig.txt"), help='Defines all different cut variations')
p.add_option('--nLow', type='int', default=1, help='lowest bin which will be filled')
p.add_option('--nHigh', type='int', default=10, help='highest bin which will be filled')

p.add_option('--binsPerJob', type='int', default=5, help='Number of bins per job and systematic')

for option in p.option_list:
    if option.default != ("NO", "DEFAULT"):
        option.help += (" " if option.help else "") + "[default: %default]"

(options, args) = p.parse_args() 

def main():
    systObj=VBFAnalysis.systematics.systematics(options.syst)
    systList=systObj.systematicsList
    print "estimated time per job [hrs]",7*options.binsPerJob*len(systList)/3600.
    goOn=raw_input("Do you want to continue?[y/n]")
    if not (goOn in ["y","Y","yes","YES","Yes"]):
        sys.exit()
    workDir=os.getcwd()


    HTCjob=VBFAnalysis.HTCsubmit.HTCclass() 
    for i in range(0,(options.nHigh-options.nLow)/options.binsPerJob+1): #TODO check this
        HTCjob.writeInput(options.nLow+(options.binsPerJob*i), options.binsPerJob*(i+1), workDir+"/Condor_out_{num}.root".format(num=i))
    HTCjob.writeExec(commandList=["lsetup root",os.path.expandvars("export SourceArea=${SourceArea}"),os.path.expandvars("source ${SourceArea}/../build/x86_64-slc6-gcc62-opt/setup.sh"), "makeHFinput.py --nLow $1 --nHigh $2 --output $3 --input /nfs/dust/atlas/user/ahnenjan/STPProcessing/run/CondorTest/fullinput.txt"]) #TODO give it all options. Remove the export of SourceArea somehow.
    HTCjob.writeSubmit()
    HTCjob.submit()
    

if __name__=="__main__":
    main()
