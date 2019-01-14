import itertools
def grouper(n, iterable):
    it = iter(iterable)
    while True:
       chunk = tuple(itertools.islice(it, n))
       if not chunk:
           return
       yield chunk

import os
import ROOT
import numpy as np
import root_numpy as rnp

common = "jet_pt[0]>80e3 && jet_pt[1]>50e3 && n_jet>=2 && jet_eta[0]*jet_eta[1]<0 && jj_deta>2.5 && jj_dphi<2.4  && jj_mass>500e3 && "
selection = {"Zvv_QCD_SR"  :"364142 <=runNumber && runNumber <= 364155 "
             #"Zvv_QCD_SR"  :common + "364142 <=runNumber && runNumber <= 364155 && (trigger_met==1) && met>50e3       && met_j1_dphi>1       && met_j2_dphi>1       && (n_el+n_mu==0)",
             #"Wlv_QCD_SR"  :common + "364156 <=runNumber && runNumber <= 364197  && (trigger_met==1) && met>50e3       && met_j1_dphi>1       && met_j2_dphi>1       && (n_el+n_mu==0)",
             #"Wlvp_QCD_CR" :common + "364156 <=runNumber && runNumber <= 364197 && (trigger_lep==1) && met_nolep>50e3 && met_nolep_j1_dphi>1 && met_nolep_j2_dphi>1 && ( (n_el==1 && n_mu==0 && el1_charge>0 && el1_pt>30e3) || (n_el==0 && n_mu==1 && mu1_charge>0 && mu1_pt>30e3) )",
             #"Wlvn_QCD_CR" :common + "364156 <=runNumber && runNumber <= 364197 && (trigger_lep==1) && met_nolep>50e3 && met_nolep_j1_dphi>1 && met_nolep_j2_dphi>1 && ( (n_el==1 && n_mu==0 && el1_charge>0 && el1_pt>30e3) || (n_el==0 && n_mu==1 && mu1_charge>0 && mu1_pt>30e3) )",
             #"Zll_QCD_CR"  :common + "364100 <=runNumber && runNumber <= 364141 && (trigger_lep==1) && met_nolep>50e3 && met_nolep_j1_dphi>1 && met_nolep_j2_dphi>1 && ( (n_el==2 && n_mu==0 && el1_charge*el2_charge<0 && el1_pt>30e3 && el2_pt>7e3 && abs(mll-91.2e3)<25e3) || (n_el==0 && n_mu==2 && mu1_charge*mu2_charge<0 && mu1_pt>30e3 && mu2_pt>7e3 && abs(mll-91.2e3)<25e3) )",
             #"Zvv_EWK_SR"  :common + "308095 <=runNumber && runNumber <= 308095 && (trigger_met==1) && met>50e3       && met_j1_dphi>1       && met_j2_dphi>1       && (n_el+n_mu==0)",
             #"Wlv_EWK_SR"  :common + "308096 <=runNumber && runNumber <= 308098  && (trigger_met==1) && met>50e3       && met_j1_dphi>1       && met_j2_dphi>1       && (n_el+n_mu==0)",
             #"Wlvp_EWK_CR" :common + "308096 <=runNumber && runNumber <= 308098 && (trigger_lep==1) && met_nolep>50e3 && met_nolep_j1_dphi>1 && met_nolep_j2_dphi>1 && ( (n_el==1 && n_mu==0 && el1_charge>0 && el1_pt>30e3) || (n_el==0 && n_mu==1 && mu1_charge>0 && mu1_pt>30e3) )",
             #"Wlvn_EWK_CR" :common + "308096 <=runNumber && runNumber <= 308098 && (trigger_lep==1) && met_nolep>50e3 && met_nolep_j1_dphi>1 && met_nolep_j2_dphi>1 && ( (n_el==1 && n_mu==0 && el1_charge>0 && el1_pt>30e3) || (n_el==0 && n_mu==1 && mu1_charge>0 && mu1_pt>30e3) )",
             #"Zll_EWK_CR"  :common + "308092 <=runNumber && runNumber <= 308094 && (trigger_lep==1) && met_nolep>50e3 && met_nolep_j1_dphi>1 && met_nolep_j2_dphi>1 && ( (n_el==2 && n_mu==0 && el1_charge*el2_charge<0 && el1_pt>30e3 && el2_pt>7e3 && abs(mll-91.2e3)<25e3) || (n_el==0 && n_mu==2 && mu1_charge*mu2_charge<0 && mu1_pt>30e3 && mu2_pt>7e3 && abs(mll-91.2e3)<25e3) )"
             }

for key, sel in selection.iteritems():
  print "Processing ", key, "..."
  treelist_r21 = ROOT.TList()
  in_f_r21 = ROOT.TFile.Open("/Users/othmanerifki/vbf/myVBFAnalyzer/processed/VBFH125.root", "READ")
  in_t_r21 = in_f_r21.Get("nominal")
  f="./"
  outfilename = os.path.join(os.path.dirname(f), "{0:s}_rel21.root".format(key))
  out_f_r21 = ROOT.TFile.Open("tmp.root", "RECREATE")
  new_t_r21 = in_t_r21.CopyTree(sel)
  new_t_r21.SetName("nominal")
  new_t_r21.SetTitle("nominal")
  if new_t_r21.GetEntries()==0:
    print "   > Skipping {0:s}... ".format(key)
    os.remove("tmp.root")
    continue
  else:
    os.rename("tmp.root",outfilename)
  treelist_r21.Add(new_t_r21)
  out_f_r21.cd()
  out_t_r21 = ROOT.TTree.MergeTrees(treelist_r21)
  out_t_r21.SetName("nominal")
  out_t_r21.SetTitle("nominal")
  out_f_r21.Write("",ROOT.TObject.kOverwrite)
  out_f_r21.Close()
  in_f_r21.Close()