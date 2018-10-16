#!/usr/bin/env python

import os
import sys
import subprocess
import argparse
import VBFAnalysis.sample
import VBFAnalysis.systematics
import pickle
from VBFAnalysis.compactCondorScript import *

parser = argparse.ArgumentParser( description = "Looping over sys and samples for HF Input Alg", add_help=True , fromfile_prefix_chars='@')

parser.add_argument( "-s", "--syst", dest = "syst", type=str, default = "Nominal", help = "Define the list of systematics ot run on" )
parser.add_argument( "-d", "--submitDir",  type = str, dest = "submitDir", default = "submitDir", help = "dir in run where all the output goes to")
parser.add_argument( "-l", "--listSample", type = str, dest = "listSample", default = "/eos/user/r/rzou/v04/list", help = "list of ntuples to run over" )
#parser.add_argument( "-f", "--normFile", type = str, dest = "normFile", default = "/home/rzou/STPostProcessing/run/f_out_total_v05.root", help = "file with the total number of event processed" )
parser.add_argument( "-f", "--normFile", type = str, dest = "normFile", default = os.path.expandvars("${SourceArea}/VBFAnalysis/data/f_norm.root"), help = "file with the total number of event processed" )
parser.add_argument( "-p", "--proxyName", type = str, dest = "proxyName", default = "/home/schae/testarea/HInv/run/x509up_u20186", help = "proxy file for grid")
parser.add_argument( "--noSubmit", dest = "noSubmit", action="store_true", default = False, help = "Dont submit jobs" )
args, unknown = parser.parse_known_args()

### Load systematics list from VBFAnalysis/python/systematics.py ###
syst = VBFAnalysis.systematics.systematics(args.syst)
systlist = syst.getsystematicsList()
print systlist
list_file=None
isFileMap=False
if args.listSample.count('.p'):
    list_file = pickle.load( open( args.listSample, "rb" ) ) #open(args.listSample, "r")
    isFileMap=True
else:
    list_file = open(args.listSample, "r")

### Remake submitDir ###
workDir = os.getcwd()+"/"+args.submitDir
CMTCONFIG = os.getenv('CMTCONFIG')
buildPaths = os.getenv('CMAKE_PREFIX_PATH')
buildPathsVec = buildPaths.split(':')
buildDir =  buildPathsVec[0][:buildPathsVec[0].find(CMTCONFIG)].rstrip('/')
os.system("rm -rf "+workDir)
os.system("mkdir "+workDir)                
os.system("mkdir "+workDir+"/rootFiles")                

listofrunN = workDir+"/filelist"
listofrunNMC = workDir+"/filelistMC"
f = open(listofrunN, 'w')
fMC = open(listofrunNMC, 'w')
samplePatternGlobal = ""
if isFileMap:
    nb=0
    for container,contFileList in list_file.iteritems():
        #if not container.count('276181'):#'364184'):
        #    continue
        s=VBFAnalysis.sample.sample(container)
        isMC = s.getisMC()
        runNumberS = s.getrunNumberS()
        comma_sep_files=''
        for filepath in contFileList:
            comma_sep_files+=filepath+','
            nb+=1
        f.write(comma_sep_files.rstrip(',')+' '+container+"\n")
        if isMC:
            fMC.write(comma_sep_files.rstrip(',')+' '+container+"\n")
        #if nb>10:
        #    break;
        samplePatternGlobal=''
else:
    for sampledir in list_file:
        s=VBFAnalysis.sample.sample(sampledir)
        isMC = s.getisMC()
        runNumberS = s.getrunNumberS()
        p = subprocess.Popen("ls "+sampledir.strip()+"/*root*", shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        for line in p.stdout.readlines():
            filepath = line.strip()
            if "physics_Main" in filepath[filepath.find(runNumberS):]:
                #f.write(filepath[filepath.find(runNumberS):]+"\n")
                f.write(filepath[filepath.find("user."):]+"\n")
            if isMC:
                fMC.write(filepath[filepath.find("user."):]+"\n")
        samplePattern = sampledir[:sampledir.find("user.")]
        foundV = False
        for p,s in enumerate(sampledir.split(".")):
            if s[0]=="v":
                #samplePattern+="."+s
                foundV = True
        if not(foundV):
            print "ERROR: samples have different names than assumed!"
            break
        if (samplePatternGlobal != samplePattern) and (samplePatternGlobal != ""):
            print "ERROR: samples have different patterns!"
            break
        samplePatternGlobal = samplePattern
f.close()
fMC.close()


runCommand=[]
dataCommand=[]
for syst in systlist:
    runCommand.append('''athena VBFAnalysis/VBFAnalysisAlgJobOptions.py --filesInput "'''+samplePatternGlobal+'''$1" - --currentVariation '''+syst+''' --normFile '''+args.normFile)
scriptName='AllSyst'
writeCondorShell(workDir, buildDir, runCommand, scriptName, "VBFAnalysisCondorSub", proxyName=args.proxyName)

dataCommand.append('''athena VBFAnalysis/VBFAnalysisAlgJobOptions.py --filesInput "'''+samplePatternGlobal+'''$1" - --currentVariation Nominal --normFile '''+args.normFile)
writeCondorShell(workDir, buildDir, dataCommand, "DATA", "VBFAnalysisCondorSub", proxyName=args.proxyName)


writeCondorSub(workDir, scriptName, "VBFAnalysisCondorSub", listofrunN, listofrunNMC)
writeCondorSub(workDir, "DATA", "VBFAnalysisCondorSub", listofrunN)




#for syst in systlist:
#    print listofrunN
#    if args.noSubmit:
#        break
#    runCommand = '''athena VBFAnalysis/VBFAnalysisAlgJobOptions.py --filesInput "'''+samplePatternGlobal+'''$1" - --currentVariation '''+syst+''' --normFile '''+args.normFile
#    if isFileMap:
#        runCommand+=''' --containerName $2'''
#    writeCondorShell(workDir, buildDir, runCommand, syst, "VBFAnalysisCondorSub", proxyName=args.proxyName) #writeCondorShell(subDir, buildDir, syst, runCommand, scriptName="VBFAnalysisCondorSub")
#    print listofrunN
#    writeCondorSub(workDir, syst, "VBFAnalysisCondorSub", listofrunN, listofrunNMC)
