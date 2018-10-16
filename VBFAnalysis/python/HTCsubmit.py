#Class for handling HTCondor job submission
#usage example:

#obj=HTCclass()
#obj.writeExec('subthis.sh',['echo "hello HTC!"', 'echo "finished"'])
#obj.writeSubmit()
#obj.submit()


import os
import sys
import subprocess


#TODO allow job monitoring. This also means adding a class for jobs (ProcId, ClusterId, status, resubmit()...)


class HTCclass():
    def __init__(self, submitDir='submitDir', inputFile=''):
        self.submitDir=os.getcwd()+'/'+submitDir
        # (re)make submit directory
        if os.path.isdir(self.submitDir):
            mkNew=raw_input('{submitDir} already exists! Do you want to remake it?[y/n]'.format(submitDir=self.submitDir))
            if mkNew=='y' or mkNew=='yes':
                os.system("rm -rf "+self.submitDir)
                os.mkdir(self.submitDir)
        else:
            os.mkdir(self.submitDir)

        self.executable=''
        self.transfer_files='Yes'
        self.RequestRuntime=10800 #3 hrs is standard
        self.max_retries=2
        self.inputFile=inputFile

    def writeInput(self, *args):
        fullPath=self.submitDir+'/'+"CondorInput.txt"
        self.inputFile=fullPath
        inputF=open(self.inputFile,'a')
        for v in args:
            inputF.write(str(v)+" ")
        inputF.write("\n")
        inputF.close()



    def writeExec(self, name='exec.sh', commandList=[]):
        fullPath=self.submitDir+'/'+name
        execFile=open(fullPath,'w')
        execFile.write('''
#!/bin/bash
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh --quiet
'''
        )
        for command in commandList: execFile.write(command + '\n')
        execFile.close()
        self.executable=fullPath


    def writeSubmit(self):
        if self.executable=='':
            print 'self.executable is None! Run self.writeExec()'
            return

        if self.inputFile=='':
            self.queue='queue'
        else:
            self.queue='queue arguments from '+self.inputFile

        sFile=open(self.submitDir+'/job.submit','w')
        sFile.write( ''' 
executable          = {self.executable}
transfer_executable = True
universe            = vanilla
output              = {self.submitDir}/job.out$(ClusterId).$(ProcId)
error               = {self.submitDir}/job.error$(ClusterId).$(ProcId)
log                 = {self.submitDir}/job.log$(ClusterId)
environment         = "ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase"
should_transfer_files   = {self.transfer_files} 
when_to_transfer_output = ON_EXIT

requirements            = (OpSysAndVer == "SL6" || OpSysAndVer == "CentOS7")
#RequestMemory = 1024

# max run time in seconds for a job, after it gets killed by the system
# if not set, default is 3 hours
# longer requested job run times get more hit in the fairshare calculation
+RequestRuntime     = {self.RequestRuntime}
max_retries={self.max_retries}
#
#
##########################
#queue arguments from input
{self.queue}
'''.format(self=self)
        )
        sFile.close()

    def submit(self):
        if os.path.isfile(self.submitDir+'/job.submit'):
            subprocess.call(['condor_submit',self.submitDir+'/job.submit'])
        else:
            print self.submitDir+'/job.submit','<- Does not exist! Maybe you want to run writeSubmit().'


# If you just want to submit a executable you can do: python HTCclass.py --exe yourExecutable.sh 
if __name__=='__main__':

    from optparse import OptionParser

    p = OptionParser()
    p.add_option("-i", "--input", default='', help="input file with arguments for the executable")
    p.add_option("-o", "--outDir", default="submitDir", help="Submit directory. This will hold all the output files")
    p.add_option("-e", "--exe", default='', help="executable to submit")
    (options, args) = p.parse_args()

    if options.exe=='':
        print 'no executable set!'
        sys.exit()

    obj=HTCclass(options.outDir, options.input)
    obj.executable=options.exe
    obj.writeSubmit()
    obj.submit()
