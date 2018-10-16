from collections import OrderedDict

mainMC = OrderedDict([
    ('signal',    [308276,308567,308284]),
    ('signalAlt', [308275] + range(308277,308283 + 1)),
    ('VH',        [308071,308072]),
    ('VV',        range(363355, 363360+1) + [363489]),
    ('ZEWK',       range(308092, 308094+1)),
    ('ZnunuEWK',       range(308092, 308094+1)),
    ('WEWK',       range(308096, 308098+1)),
    ('Wenu',      range(364170,364183 + 1)),
    ('Wmunu',     range(364156,364169 + 1)),
    ('Wtaunu',    range(364184,364197 + 1)),
    ('Zee',       range(364114, 364127 + 1)),
    ('Zmumu',     range(364100, 364113 +1)),
    ('Ztautau',   range(364128,364141 + 1)),
    ('Znunu',     range(364142,364155 + 1)),
    ('QCDw',      range(361020,361032 + 1)),
    ('top',       [410470,410472,410011,410012,410013,410014,410025,410026])
    ])

altMC = OrderedDict([
    ('ZllVBF',    [345101,345102,345099,345100]),
    ('ZllDY',     range(364198, 364215+1)),
    ('topAlt',    [410471]),
    ('VVrare',    [363494,364250,364254,364255] ),
    ('VVV',       range(364242,364249 + 1)),
    ('QCDunw',    range(426001,426009 + 1))
    ])

truthMC = OrderedDict([
    ('signal',    [308276,308567,308284]),
    ('signalAlt', [308275] + range(308277,308283 + 1)),
    ('EWK',       range(308092, 308098+1)),
    ('Wenu',      range(364170,364183 + 1)),
    ('Wmunu',     range(364156,364169 + 1)),
    ('Wtaunu',    range(364184,364197 + 1)),
    ('Zee',       range(364114, 364127 + 1)),
    ('Zmumu',     range(364100, 364113 +1)),
    ('Ztautau',   range(364128,364141 + 1)),
    ('Znunu',     range(364142,364155 + 1)),
    ])

mcCampaign = {"mc16a":"r9364", "mc16c":"r9781", "mc16d":"r10201"}

# Modified by user:
#####################
pTagDict = { "data15_13TeV"                  : "p3576",
             "data16_13TeV"                  : "p3576",
             "mc16_13TeV"                    : "p3575"} # skimmed or unskimmed here

dataDict={
    "data15": range(266905,284484 + 1),
    "data16": range(296939,311481 + 1),
    "data17": range(324320,341649 + 1)
}

MCbackgrounds=['VV', 'ZEWK', 'ZnunuEWK', 'WEWK', 'Wenu',
 'Wmunu', 'Wtaunu', 'Zee', 'Zmumu', 'Ztautau', 'Znunu', 'QCDw', 'top']+["Others"]
MCprocesses=[k for k in mainMC]
dataSets=[k for k in dataDict]
allProcesses=dataSets+MCprocesses+["Others","bkgs","data"] # This list is used to create the histograms


# Defining all the regions
regions=[]
regions.append("pass_sr_allmjj_nn")
for k in ['ep','en','up','un','l','e','u']:
    regions.append("pass_"+"wcr"+"_allmjj_"+k)
for k in ['ee','uu','ll']:
    regions.append("pass_"+"zcr"+"_allmjj_"+k)



# Defining systematics
systDict={}
systDict["Nominal"] = ["Nominal"]
systDict["TEST"] = ["Nominal", "JET_JER_SINGLE_NP__1up", "JET_JER_SINGLE_NP__1down", "MET_SoftTrk_ResoPara", "JET_EtaIntercalibration_Modelling__1down", "JET_EtaIntercalibration_Modelling__1up",    "JET_EffectiveNP_Detector1__1up",    "JET_EffectiveNP_Detector1__1down"]
