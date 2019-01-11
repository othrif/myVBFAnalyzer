from AthenaCommon.AppMgr import ServiceMgr
ServiceMgr.MessageSvc.defaultLimit = 9999999  # all messages
ServiceMgr.MessageSvc.OutputLevel = INFO #DEBUG

#---- Import job config for customized command line inputs ----
from VBFAnalysis.job_configuration import JobConfigurationBase
import VBFAnalysis.sample
from glob import glob

#---- Options you could specify on command line -----
jps.AthenaCommonFlags.FilesInput = glob(vars().get("input", "/eos/user/r/rzou/v04/user.othrif.v04.364106.Sherpa_221_NNPDF30NNLO_Zmumu_MAXHTPTV140_280_CVetoBVeto.e5271_s3126_r9364_r9315_p3575_MiniNtuple.root/*"))
jps.AthenaCommonFlags.TreeName = "MiniNtuple"
jps.AthenaCommonFlags.EvtMax =vars().get("nEvents", -1)                          #set on command-line with: --evtMax=-1
#jps.AthenaCommonFlags.SkipEvents=0                       #set on command-line with: --skipEvents=0

config = JobConfigurationBase("JobOptions")
arg_group = config.parser.add_argument_group("JobOptions", "Extra arguments specific to VBFAnalysisAlgJobOptions")
arg_group.add_argument("--currentVariation", dest='currentVariation', default="Nominal", help="current systematics, default: Nominal")
arg_group.add_argument("--normFile", dest='normFile', default=os.path.expandvars("${SourceArea}/VBFAnalysis/data/f_out_total_v05.root"), help="file with the total number of event processed")
arg_group.add_argument("--containerName", dest='containerName', default="", help="container name used to look up the sample ID if not in the file path")

# parse the commandline options
args = config.parse_args()

### Build sample from FilesInput and read its properties ###
inputDir = str(jps.AthenaCommonFlags.FilesInput)
print 'inputDir: ',inputDir
s=VBFAnalysis.sample.sample(inputDir)
currentSample = s.getsampleType()
isMC = s.getisMC()
runNumber = s.getrunNumber()
subfileN = s.getsubfileN()
containerName = args.containerName
if containerName!="":
    s=VBFAnalysis.sample.sample(containerName)
    currentSample = s.getsampleType()
    isMC = s.getisMC()
    runNumber = s.getrunNumber()
    subfileN = s.getsubfileN()

print inputDir, " ", currentSample, " ", str(runNumber)
jps.AthenaCommonFlags.HistOutputs = ["MYSTREAM:"+currentSample+args.currentVariation+str(runNumber)+subfileN+".root"]  #optional, register output files like this. MYSTREAM is used in the code

athAlgSeq += CfgMgr.VBFAnalysisAlg("VBFAnalysisAlg",
                                   currentVariation = args.currentVariation,
                                   normFile = args.normFile,
                                   currentSample = currentSample,
                                   isMC = isMC,
                                   runNumberInput = runNumber);

include("AthAnalysisBaseComps/SuppressLogging.py") #optional line