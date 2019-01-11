class systematics(object):
    systDict={}


    systDict["Nominal"] = ["Nominal"]


    systDict["v13Systematics"]=["EG_RESOLUTION_ALL__1down", "EG_RESOLUTION_ALL__1up", "EG_SCALE_AF2__1down", "EG_SCALE_AF2__1up", "EG_SCALE_ALL__1down", "EG_SCALE_ALL__1up", "EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1up", "FT_EFF_B_systematics__1down", "FT_EFF_B_systematics__1up", "FT_EFF_C_systematics__1down", "FT_EFF_C_systematics__1up", "FT_EFF_extrapolation__1down", "FT_EFF_extrapolation__1up", "FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation_from_charm__1up", "FT_EFF_Light_systematics__1down", "FT_EFF_Light_systematics__1up", "JET_Comb_Baseline_Kin__1down", "JET_Comb_Baseline_Kin__1up", "JET_Comb_Modelling_Kin__1down", "JET_Comb_Modelling_Kin__1up", "JET_Comb_TotalStat_Kin__1down", "JET_Comb_TotalStat_Kin__1up", "JET_Comb_Tracking_Kin__1down", "JET_Comb_Tracking_Kin__1up", "JET_EtaIntercalibration_NonClosure__1down", "JET_EtaIntercalibration_NonClosure__1up", "JET_fJvtEfficiency__1down", "JET_fJvtEfficiency__1up", "JET_GroupedNP_1__1down", "JET_GroupedNP_1__1up", "JET_GroupedNP_2__1down", "JET_GroupedNP_2__1up", "JET_GroupedNP_3__1down", "JET_GroupedNP_3__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_MassRes_Hbb__1down", "JET_MassRes_Hbb__1up", "JET_MassRes_Top__1down", "JET_MassRes_Top__1up", "JET_MassRes_WZ__1down", "JET_MassRes_WZ__1up", "JET_Rtrk_Baseline_Sub__1down", "JET_Rtrk_Baseline_Sub__1up", "JET_Rtrk_Modelling_Sub__1down", "JET_Rtrk_Modelling_Sub__1up", "JET_Rtrk_TotalStat_Sub__1down", "JET_Rtrk_TotalStat_Sub__1up", "JET_Rtrk_Tracking_Sub__1down", "JET_Rtrk_Tracking_Sub__1up", "MET_SoftTrk_ResoPara", "MET_SoftTrk_ResoPerp", "MET_SoftTrk_ScaleDown", "MET_SoftTrk_ScaleUp", "MUON_EFF_BADMUON_STAT__1down", "MUON_EFF_BADMUON_STAT__1up", "MUON_EFF_BADMUON_SYS__1down", "MUON_EFF_BADMUON_SYS__1up", "MUON_EFF_ISO_STAT__1down", "MUON_EFF_ISO_STAT__1up", "MUON_EFF_ISO_SYS__1down", "MUON_EFF_ISO_SYS__1up", "MUON_EFF_RECO_STAT__1down", "MUON_EFF_RECO_STAT__1up", "MUON_EFF_RECO_STAT_LOWPT__1down", "MUON_EFF_RECO_STAT_LOWPT__1up", "MUON_EFF_RECO_SYS__1down", "MUON_EFF_RECO_SYS__1up", "MUON_EFF_RECO_SYS_LOWPT__1down", "MUON_EFF_RECO_SYS_LOWPT__1up", "MUON_EFF_TrigStatUncertainty__1down", "MUON_EFF_TrigStatUncertainty__1up", "MUON_EFF_TrigSystUncertainty__1down", "MUON_EFF_TrigSystUncertainty__1up", "MUON_EFF_TTVA_STAT__1down", "MUON_EFF_TTVA_STAT__1up", "MUON_EFF_TTVA_SYS__1down", "MUON_EFF_TTVA_SYS__1up", "MUON_ID__1down", "MUON_ID__1up", "MUON_MS__1down", "MUON_MS__1up", "MUON_SAGITTA_RESBIAS__1down", "MUON_SAGITTA_RESBIAS__1up", "MUON_SAGITTA_RHO__1down", "MUON_SAGITTA_RHO__1up", "MUON_SCALE__1down", "MUON_SCALE__1up", "PH_EFF_ID_Uncertainty__1down", "PH_EFF_ID_Uncertainty__1up", "PH_EFF_ISO_Uncertainty__1down", "PH_EFF_ISO_Uncertainty__1up", "PH_EFF_TRIGGER_Uncertainty__1down", "PH_EFF_TRIGGER_Uncertainty__1up", "PRW_DATASF__1down", "PRW_DATASF__1up", "TAUS_TRUEELECTRON_EFF_ELEOLR_TOTAL__1down", "TAUS_TRUEELECTRON_EFF_ELEOLR_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL__1down", "TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORR2025__1down", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORR2025__1up", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORR2530__1down", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORR2530__1up", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORR3040__1down", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORR3040__1up", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORRGE40__1down", "TAUS_TRUEHADTAU_EFF_JETID_1PRONGSTATSYSTUNCORRGE40__1up", "TAUS_TRUEHADTAU_EFF_JETID_3PRONGSTATSYSTUNCORR2030__1down", "TAUS_TRUEHADTAU_EFF_JETID_3PRONGSTATSYSTUNCORR2030__1up", "TAUS_TRUEHADTAU_EFF_JETID_3PRONGSTATSYSTUNCORRGE30__1down", "TAUS_TRUEHADTAU_EFF_JETID_3PRONGSTATSYSTUNCORRGE30__1up", "TAUS_TRUEHADTAU_EFF_JETID_HIGHPT__1down", "TAUS_TRUEHADTAU_EFF_JETID_HIGHPT__1up", "TAUS_TRUEHADTAU_EFF_JETID_SYST__1down", "TAUS_TRUEHADTAU_EFF_JETID_SYST__1up", "TAUS_TRUEHADTAU_EFF_RECO_HIGHPT__1down", "TAUS_TRUEHADTAU_EFF_RECO_HIGHPT__1up", "TAUS_TRUEHADTAU_EFF_RECO_TOTAL__1down", "TAUS_TRUEHADTAU_EFF_RECO_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2015__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2015__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2016__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2016__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2017__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2017__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2015__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2015__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2016__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2016__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2017__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2017__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2015__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2015__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2016__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2016__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2017__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2017__1up", "TAUS_TRUEHADTAU_SME_TES_DETECTOR__1down", "TAUS_TRUEHADTAU_SME_TES_DETECTOR__1up", "TAUS_TRUEHADTAU_SME_TES_INSITU__1down", "TAUS_TRUEHADTAU_SME_TES_INSITU__1up", "TAUS_TRUEHADTAU_SME_TES_MODEL__1down", "TAUS_TRUEHADTAU_SME_TES_MODEL__1up"]



























    systDict["fullSyst"] = ["Nominal", "EG_RESOLUTION_ALL__1down", "EG_RESOLUTION_ALL__1up", "EG_SCALE_AF2__1down", "EG_SCALE_AF2__1up", "EG_SCALE_ALL__1down", "EG_SCALE_ALL__1up", "EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_ChargeIDSel_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_Trigger_TOTAL_1NPCOR_PLUS_UNCOR__1up", "EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1down", "EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1up", "FT_EFF_B_systematics__1down", "FT_EFF_B_systematics__1up", "FT_EFF_C_systematics__1down", "FT_EFF_C_systematics__1up", "FT_EFF_extrapolation__1down", "FT_EFF_extrapolation__1up", "FT_EFF_extrapolation_from_charm__1down", "FT_EFF_extrapolation_from_charm__1up", "FT_EFF_Light_systematics__1down", "FT_EFF_Light_systematics__1up", "JET_Comb_Baseline_Kin__1down", "JET_Comb_Baseline_Kin__1up", "JET_Comb_Modelling_Kin__1down", "JET_Comb_Modelling_Kin__1up", "JET_Comb_TotalStat_Kin__1down", "JET_Comb_TotalStat_Kin__1up", "JET_Comb_Tracking_Kin__1down", "JET_Comb_Tracking_Kin__1up", "JET_EtaIntercalibration_NonClosure__1down", "JET_EtaIntercalibration_NonClosure__1up", "JET_fJvtEfficiency__1down", "JET_fJvtEfficiency__1up", "JET_GroupedNP_1__1down", "JET_GroupedNP_1__1up", "JET_GroupedNP_2__1down", "JET_GroupedNP_2__1up", "JET_GroupedNP_3__1down", "JET_GroupedNP_3__1up", "JET_JER_SINGLE_NP__1up", "JET_JvtEfficiency__1down", "JET_JvtEfficiency__1up", "JET_MassRes_Hbb__1down", "JET_MassRes_Hbb__1up", "JET_MassRes_Top__1down", "JET_MassRes_Top__1up", "JET_MassRes_WZ__1down", "JET_MassRes_WZ__1up", "JET_Rtrk_Baseline_Sub__1down", "JET_Rtrk_Baseline_Sub__1up", "JET_Rtrk_Modelling_Sub__1down", "JET_Rtrk_Modelling_Sub__1up", "JET_Rtrk_TotalStat_Sub__1down", "JET_Rtrk_TotalStat_Sub__1up", "JET_Rtrk_Tracking_Sub__1down", "JET_Rtrk_Tracking_Sub__1up", "MET_SoftTrk_ResoPara", "MET_SoftTrk_ResoPerp", "MET_SoftTrk_ScaleDown", "MET_SoftTrk_ScaleUp", "MUON_EFF_BADMUON_STAT__1down", "MUON_EFF_BADMUON_STAT__1up", "MUON_EFF_BADMUON_SYS__1down", "MUON_EFF_BADMUON_SYS__1up", "MUON_EFF_ISO_STAT__1down", "MUON_EFF_ISO_STAT__1up", "MUON_EFF_ISO_SYS__1down", "MUON_EFF_ISO_SYS__1up", "MUON_EFF_RECO_STAT__1down", "MUON_EFF_RECO_STAT__1up", "MUON_EFF_RECO_STAT_LOWPT__1down", "MUON_EFF_RECO_STAT_LOWPT__1up", "MUON_EFF_RECO_SYS__1down", "MUON_EFF_RECO_SYS__1up", "MUON_EFF_RECO_SYS_LOWPT__1down", "MUON_EFF_RECO_SYS_LOWPT__1up", "MUON_EFF_TrigStatUncertainty__1down", "MUON_EFF_TrigStatUncertainty__1up", "MUON_EFF_TrigSystUncertainty__1down", "MUON_EFF_TrigSystUncertainty__1up", "MUON_EFF_TTVA_STAT__1down", "MUON_EFF_TTVA_STAT__1up", "MUON_EFF_TTVA_SYS__1down", "MUON_EFF_TTVA_SYS__1up", "MUON_ID__1down", "MUON_ID__1up", "MUON_MS__1down", "MUON_MS__1up", "MUON_SAGITTA_RESBIAS__1down", "MUON_SAGITTA_RESBIAS__1up", "MUON_SAGITTA_RHO__1down", "MUON_SAGITTA_RHO__1up", "MUON_SCALE__1down", "MUON_SCALE__1up", "PH_EFF_ID_Uncertainty__1down", "PH_EFF_ID_Uncertainty__1up", "PH_EFF_ISO_Uncertainty__1down", "PH_EFF_ISO_Uncertainty__1up", "PH_EFF_TRIGGER_Uncertainty__1down", "PH_EFF_TRIGGER_Uncertainty__1up", "PRW_DATASF__1down", "PRW_DATASF__1up", "TAUS_TRUEELECTRON_EFF_ELEOLR_TOTAL__1down", "TAUS_TRUEELECTRON_EFF_ELEOLR_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL__1down", "TAUS_TRUEHADTAU_EFF_ELEOLR_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_JETID_HIGHPT__1down", "TAUS_TRUEHADTAU_EFF_JETID_HIGHPT__1up", "TAUS_TRUEHADTAU_EFF_JETID_TOTAL__1down", "TAUS_TRUEHADTAU_EFF_JETID_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_RECO_HIGHPT__1down", "TAUS_TRUEHADTAU_EFF_RECO_HIGHPT__1up", "TAUS_TRUEHADTAU_EFF_RECO_TOTAL__1down", "TAUS_TRUEHADTAU_EFF_RECO_TOTAL__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2015__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2015__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2016__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2016__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2017__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATDATA2017__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2015__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2015__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2016__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2016__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2017__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_STATMC2017__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2015__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2015__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2016__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2016__1up", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2017__1down", "TAUS_TRUEHADTAU_EFF_TRIGGER_SYST2017__1up", "TAUS_TRUEHADTAU_SME_TES_DETECTOR__1down", "TAUS_TRUEHADTAU_SME_TES_DETECTOR__1up", "TAUS_TRUEHADTAU_SME_TES_INSITU__1down", "TAUS_TRUEHADTAU_SME_TES_INSITU__1up", "TAUS_TRUEHADTAU_SME_TES_MODEL__1down", "TAUS_TRUEHADTAU_SME_TES_MODEL__1up"]
    systDict["JET"] = ["Nominal"] + [s for s in systDict["fullSyst"] if "JET_" in s]
    systDict["problem"] = ["JET_Comb_Baseline_Kin__1up"]
    systDict["TEST"] = ["JET_GroupedNP_1__1down", "JET_GroupedNP_1__1up"] 

    def __init__(self,mode):
        self.systematicsList=systematics.systDict[mode]


    def getsystematicsList(self):
        return self.systematicsList