def setLineAttr(self,color=1,style=1,width=1):
    self.SetLineColor(color)
    self.SetLineStyle(style)
    self.SetLineWidth(width)

def setFillAttr(self,color=1,style=3018):
    self.SetFillColor(color)
    self.SetFillStyle(style)

def setMarkerAttr(self,color=1,style=1,size=1):
    self.SetMarkerColor(color)
    self.SetMarkerStyle(style)
    self.SetMarkerSize(size)

def setStyles(self, styleList):
    setLineAttr(self,styleList[0],styleList[1],styleList[2])
    setFillAttr(self,styleList[3],styleList[4])
    setMarkerAttr(self,styleList[5],styleList[6],styleList[7])

# This dict defines the style for the histograms create by hist_from_file if the argument newTitle is a key
styleDict={}
    #processList=["hvh", "mqcd", "higgs", "vvv", "wewk", "hggf", "top2", 
    # "top1", "zewk", "data", "bkgs", "tall", "hvbf", "zldy", "dqcd", "zqcd", "wqcd"]

#0:LColor, 1:LStyle, 2:LWidth, 3:FColor, 4:FStyle, 5:MColor, 6:MStyle, 7:MSize
styleDict["bkgs"]=[1,1,2,0,0,0,0,0]
styleDict["data"]=[1,0,2,0,0,1,20,1.2]
styleDict["signal"]=[2,2,3,0,0,0,0,0]

styleDict["Znunu"]=[1,1,1,3,1001,0,0,0]
styleDict["Wtaunu"]=[1,1,1,4,1001,0,0,0]
styleDict["Wmunu"]=[1,1,1,5,1001,0,0,0]
styleDict["ZnunuEWK"]=[1,1,1,6,1001,0,0,0]
styleDict["WEWK"]=[1,1,1,7,1001,0,0,0]
styleDict["Wenu"]=[1,1,1,8,1001,0,0,0]
styleDict["top"]=[1,1,1,9,1001,0,0,0]
styleDict["Zmumu"]=[1,1,1,28,1001,0,0,0]
styleDict["Ztautau"]=[1,1,1,30,1001,0,0,0]
styleDict["VV"]=[1,1,1,34,1001,0,0,0]
styleDict["ZEWK"]=[1,1,1,42,1001,0,0,0]
styleDict["Zee"]=[1,1,1,46,1001,0,0,0]
styleDict["QCDw"]=[1,1,1,47,1001,0,0,0]
styleDict["Others"]=[1,1,1,49,1001,0,0,0]

# Define the binning for each variable
varBinning={}
# 0:Nbins, 1:Xmin, 2:Xmax
varBinning["jj_mass"]=[10,0,5e6]
varBinning["jj_deta"]=[50,2,10]
varBinning["jj_dphi"]=[50,0,3.3]
varBinning["jet1_pt"]=[50,3e4,5e5]
varBinning["jet2_pt"]=[50,3e4,3e5]
varBinning["met"]=[30,1e5,4e5]

variables=[v for v in varBinning]



cutflow={}
sameForAll=["passJetCleanTight","n_jet==2","j1_pt","j2_pt","jj_mass","jj_deta","jj_dphi","mht","met","n_el","n_mu","dphi(j1,met)","dphi(j2,met)","hemispheres"]
cutflow["sr"]=sameForAll+["trigger_met"]
cutflow["wcr"]=sameForAll+["trigger_lep","lep1","met_sig","charge"]
cutflow["zcr"]=sameForAll+["trigger_lep","lep1","lep2","mll","SFOS"]
