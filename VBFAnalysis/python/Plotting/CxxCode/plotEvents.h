//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 17 17:25:13 2018 by ROOT version 6.12/06
// from TTree Z_EWKNominal/Z_EWKNominal
// found on file: /nfs/dust/atlas/user/ahnenjan/postprocessing_CFW2/run/channelAdded/merged/Z_EWK.root
//////////////////////////////////////////////////////////

#ifndef plotEvents_h
#define plotEvents_h

#include <TROOT.h>
#include <TMath.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>


// Header file for the classes stored in the TTree if any.
#include <TLorentzVector.h>
#include <iostream>
#include "vector"


class plotEvents {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TFile* fout;
   TString process;
   TString sys;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         w;
   Int_t           runNumber;
   ULong64_t       eventNumber;
   Int_t           trigger_met;
   Int_t           trigger_lep;
   Int_t           passJetCleanTight;
   Int_t           n_jet;
   Int_t           n_el;
   Int_t           n_mu;
   Double_t        jj_mass;
   Double_t        jj_deta;
   Double_t        jj_dphi;
   Double_t        met_tst_j1_dphi;
   Double_t        met_tst_j2_dphi;
   Double_t        met_tst_nolep_j1_dphi;
   Double_t        met_tst_nolep_j2_dphi;
   Float_t         met_tst_et;
   Double_t        met_cst_jet;
   Float_t         met_tst_nolep_et;
   Float_t         met_tst_phi;
   Float_t         met_tst_nolep_phi;
   Float_t         j1_pt;
   Float_t         j2_pt;
   Float_t         j3_pt;
   Float_t         j1_eta;
   Float_t         j2_eta;
   Float_t         j3_eta;
   Float_t         j1_phi;
   Float_t         j2_phi;
   Float_t         j3_phi;
   Float_t         mu1_pt;
   Float_t         mu2_pt;
   Float_t         el1_pt;
   Float_t         el2_pt;
   Int_t           mu1_charge;
   Int_t           mu2_charge;
   Int_t           el1_charge;
   Int_t           el2_charge;
   Float_t         mll;
   Float_t         met_significance;
   Float_t         averageIntPerXing;
   Int_t           isSR;
   Int_t           isCRWep;
   Int_t           isCRWen;
   Int_t           isCRWepLowSig;
   Int_t           isCRWenLowSig;
   Int_t           isCRWmp;
   Int_t           isCRWmn;
   Int_t           isCRZee;
   Int_t           isCRZmm;

   // List of branches
   TBranch        *b_w;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_trigger_met;   //!
   TBranch        *b_trigger_lep;   //!
   TBranch        *b_passJetCleanTight;   //!
   TBranch        *b_n_jet;   //!
   TBranch        *b_n_el;   //!
   TBranch        *b_n_mu;   //!
   TBranch        *b_jj_mass;   //!
   TBranch        *b_jj_deta;   //!
   TBranch        *b_jj_dphi;   //!
   TBranch        *b_met_tst_j1_dphi;   //!
   TBranch        *b_met_tst_j2_dphi;   //!
   TBranch        *b_met_tst_nolep_j1_dphi;   //!
   TBranch        *b_met_tst_nolep_j2_dphi;   //!
   TBranch        *b_met_tst_et;   //!
   TBranch        *b_met_cst_jet;   //!
   TBranch        *b_met_tst_nolep_et;   //!
   TBranch        *b_met_tst_phi;   //!
   TBranch        *b_met_tst_nolep_phi;   //!
   TBranch        *b_j1_pt;   //!
   TBranch        *b_j2_pt;   //!
   TBranch        *b_j3_pt;   //!
   TBranch        *b_j1_eta;   //!
   TBranch        *b_j2_eta;   //!
   TBranch        *b_j3_eta;   //!
   TBranch        *b_j1_phi;   //!
   TBranch        *b_j2_phi;   //!
   TBranch        *b_j3_phi;   //!
   TBranch        *b_mu1_pt;   //!
   TBranch        *b_mu2_pt;   //!
   TBranch        *b_el1_pt;   //!
   TBranch        *b_el2_pt;   //!
   TBranch        *b_mu1_charge;   //!
   TBranch        *b_mu2_charge;   //!
   TBranch        *b_el1_charge;   //!
   TBranch        *b_el2_charge;   //!
   TBranch        *b_mll;   //!
   TBranch        *b_met_significance;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_isSR;   //!
   TBranch        *b_isCRWep;   //!
   TBranch        *b_isCRWen;   //!
   TBranch        *b_isCRWepLowSig;   //!
   TBranch        *b_isCRWenLowSig;   //!
   TBranch        *b_isCRWmp;   //!
   TBranch        *b_isCRWmn;   //!
   TBranch        *b_isCRZee;   //!
   TBranch        *b_isCRZmm;   //!

   plotEvents(TTree *tree=0, Double_t lumii=36100., TString="out.root", TString sys="Nominal");
   virtual ~plotEvents();
   virtual bool    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString sys);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     fillHists(TString,TString);
   virtual void     cutflowHists();
   virtual void     fillCutflow(TString,TString, double nb);
   virtual bool     fillSR();
   virtual bool     fillWCR(TString);
   virtual bool     fillZCR(TString);
};

#endif

#ifdef plotEvents_cxx
plotEvents::plotEvents(TTree *tree, Double_t lumii, TString outFilei, TString sysi) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/dust/atlas/user/ahnenjan/postprocessing_CFW2/run/channelAdded/merged/Z_EWK.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/nfs/dust/atlas/user/ahnenjan/postprocessing_CFW2/run/channelAdded/merged/Z_EWK.root");
      }
      f->GetObject("Z_EWKNominal",tree);

   }
   lumi=lumii;
   outFile=outFilei;
   sys=sysi;
   Init(tree);
}

plotEvents::~plotEvents()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t plotEvents::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t plotEvents::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void plotEvents::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   mu_charge = 0;
   mu_pt = 0;
   el_charge = 0;
   el_pt = 0;
   jet_pt = 0;
   jet_timing = 0;
   mu_phi = 0;
   el_phi = 0;
   mu_eta = 0;
   el_eta = 0;
   jet_phi = 0;
   jet_eta = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

  fChain->SetBranchAddress("w", &w, &b_w);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("trigger_met", &trigger_met, &b_trigger_met);
   fChain->SetBranchAddress("trigger_lep", &trigger_lep, &b_trigger_lep);
   fChain->SetBranchAddress("passJetCleanTight", &passJetCleanTight, &b_passJetCleanTight);
   fChain->SetBranchAddress("n_jet", &n_jet, &b_n_jet);
   fChain->SetBranchAddress("n_el", &n_el, &b_n_el);
   fChain->SetBranchAddress("n_mu", &n_mu, &b_n_mu);
   fChain->SetBranchAddress("jj_mass", &jj_mass, &b_jj_mass);
   fChain->SetBranchAddress("jj_deta", &jj_deta, &b_jj_deta);
   fChain->SetBranchAddress("jj_dphi", &jj_dphi, &b_jj_dphi);
   fChain->SetBranchAddress("met_tst_j1_dphi", &met_tst_j1_dphi, &b_met_tst_j1_dphi);
   fChain->SetBranchAddress("met_tst_j2_dphi", &met_tst_j2_dphi, &b_met_tst_j2_dphi);
   fChain->SetBranchAddress("met_tst_nolep_j1_dphi", &met_tst_nolep_j1_dphi, &b_met_tst_nolep_j1_dphi);
   fChain->SetBranchAddress("met_tst_nolep_j2_dphi", &met_tst_nolep_j2_dphi, &b_met_tst_nolep_j2_dphi);
   fChain->SetBranchAddress("met_tst_et", &met_tst_et, &b_met_tst_et);
   fChain->SetBranchAddress("met_cst_jet", &met_cst_jet, &b_met_cst_jet);
   fChain->SetBranchAddress("met_tst_nolep_et", &met_tst_nolep_et, &b_met_tst_nolep_et);
   fChain->SetBranchAddress("met_tst_phi", &met_tst_phi, &b_met_tst_phi);
   fChain->SetBranchAddress("met_tst_nolep_phi", &met_tst_nolep_phi, &b_met_tst_nolep_phi);
   fChain->SetBranchAddress("j1_pt", &j1_pt, &b_j1_pt);
   fChain->SetBranchAddress("j2_pt", &j2_pt, &b_j2_pt);
   fChain->SetBranchAddress("j3_pt", &j3_pt, &b_j3_pt);
   fChain->SetBranchAddress("j1_eta", &j1_eta, &b_j1_eta);
   fChain->SetBranchAddress("j2_eta", &j2_eta, &b_j2_eta);
   fChain->SetBranchAddress("j3_eta", &j3_eta, &b_j3_eta);
   fChain->SetBranchAddress("j1_phi", &j1_phi, &b_j1_phi);
   fChain->SetBranchAddress("j2_phi", &j2_phi, &b_j2_phi);
   fChain->SetBranchAddress("j3_phi", &j3_phi, &b_j3_phi);
   fChain->SetBranchAddress("mu1_pt", &mu1_pt, &b_mu1_pt);
   fChain->SetBranchAddress("mu2_pt", &mu2_pt, &b_mu2_pt);
   fChain->SetBranchAddress("el1_pt", &el1_pt, &b_el1_pt);
   fChain->SetBranchAddress("el2_pt", &el2_pt, &b_el2_pt);
   fChain->SetBranchAddress("mu1_charge", &mu1_charge, &b_mu1_charge);
   fChain->SetBranchAddress("mu2_charge", &mu2_charge, &b_mu2_charge);
   fChain->SetBranchAddress("el1_charge", &el1_charge, &b_el1_charge);
   fChain->SetBranchAddress("el2_charge", &el2_charge, &b_el2_charge);
   fChain->SetBranchAddress("mll", &mll, &b_mll);
   fChain->SetBranchAddress("met_significance", &met_significance, &b_met_significance);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("isSR", &isSR, &b_isSR);
   fChain->SetBranchAddress("isCRWep", &isCRWep, &b_isCRWep);
   fChain->SetBranchAddress("isCRWen", &isCRWen, &b_isCRWen);
   fChain->SetBranchAddress("isCRWepLowSig", &isCRWepLowSig, &b_isCRWepLowSig);
   fChain->SetBranchAddress("isCRWenLowSig", &isCRWenLowSig, &b_isCRWenLowSig);
   fChain->SetBranchAddress("isCRWmp", &isCRWmp, &b_isCRWmp);
   fChain->SetBranchAddress("isCRWmn", &isCRWmn, &b_isCRWmn);
   fChain->SetBranchAddress("isCRZee", &isCRZee, &b_isCRZee);
   fChain->SetBranchAddress("isCRZmm", &isCRZmm, &b_isCRZmm);
   Notify();
}

Bool_t plotEvents::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void plotEvents::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


void plotEvents::fillCutflow(TString region, TString lep, double nb){
    double helplumi=lumi;
    if (process=="data15" || process=="data16" || process=="data17") helplumi=1.;
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/cutflow"))->Fill(nb-0.5,helplumi*w);
}


bool plotEvents::fillSR(){
   if(!passJetCleanTight) return 0;
   fillCutflow("sr", "nn", 1);
   if(n_jet!=2) return 0;
   fillCutflow("sr", "nn", 2);
   if(jet1_pt<80e3) return 0;
   fillCutflow("sr", "nn", 3);
   if(jet2_pt<50e3) return 0;
   fillCutflow("sr", "nn", 4);
   if(jj_mass<1e6) return 0;
   fillCutflow("sr", "nn", 5);
   if(jj_deta<4.8) return 0;
   fillCutflow("sr", "nn", 6);
   if(jj_dphi>1.8) return 0;
   fillCutflow("sr", "nn", 7);
   if(met_cst_jet<150e3) return 0;
   fillCutflow("sr", "nn", 8);
   if(met_tst_et<180e3) return 0;
   fillCutflow("sr", "nn", 9);
   if(n_el!=0) return 0;
   fillCutflow("sr", "nn", 10);
   if(n_mu!=0) return 0;
   fillCutflow("sr", "nn", 11);
   if(met_tst_j1_dphi<1) return 0;
   fillCutflow("sr", "nn", 12);
   if(met_tst_j2_dphi<1) return 0;
   fillCutflow("sr", "nn", 13);
   if(0) return 0; // hemisphere cut is done in STPP
   fillCutflow("sr", "nn", 14);
   if(!trigger_met) return 0;
   fillCutflow("sr", "nn", 15);
   return 1;
}

bool plotEvents::fillZCR(TString leptons){
   double lep1, lep2, mll;
   bool SFOS;
   if(leptons=="ee" && n_el==2){
      lep1=el1_pt;
      lep2=el2_pt;
      SFOS=el1_charge!=el2_charge;
	   TLorentzVector e1,e2;
	   e1.SetPtEtaPhiM(el1_pt, el1_eta, el1_phi, 0.511);
	   e2.SetPtEtaPhiM(el2_pt, el2_eta, el2_phi, 0.511);
	   mll=(e1+e2).M();
   }
   else if(leptons=="uu" && n_mu==2){
      lep1=mu1_pt;
      lep2=mu2_pt;
      SFOS=mu1_charge!=mu2_charge;
	   TLorentzVector m1,m2;
	   m1.SetPtEtaPhiM(mu1_pt, mu1_eta, mu1_phi, 105.6);
	   m2.SetPtEtaPhiM(mu2_pt, mu2_eta, mu2_phi, 105.6);
	   mll=(m1+m2).M();
   }
   else{
      lep1=0;
      lep2=0;
      SFOS=false;
      mll=0;
   }

   if(!passJetCleanTight) return 0;
   fillCutflow("zcr", leptons, 1);
   if(n_jet!=2) return 0;
   fillCutflow("zcr", leptons, 2);
   if(jet1_pt<80e3) return 0;
   fillCutflow("zcr", leptons, 3);
   if(jet2_pt<50e3) return 0;
   fillCutflow("zcr", leptons, 4);
   if(jj_mass<1e6) return 0;
   fillCutflow("zcr", leptons, 5);
   if(jj_deta<4.8) return 0;
   fillCutflow("zcr", leptons, 6);
   if(jj_dphi>1.8) return 0;
   fillCutflow("zcr", leptons, 7);
   if(met_cst_jet<150e3) return 0;
   fillCutflow("zcr", leptons, 8);
   if(met_tst_nolep_et<180e3) return 0;
   fillCutflow("zcr", leptons, 9);
   if((n_el!=2 && leptons=="ee") || (n_el!=0 && leptons=="uu") ) return 0;
   fillCutflow("zcr", leptons, 10);
   if((n_mu!=0 && leptons=="ee") || (n_mu!=2 && leptons=="uu") ) return 0;
   fillCutflow("zcr", leptons, 11);
   if(met_tst_nolep_j1_dphi<1) return 0;
   fillCutflow("zcr", leptons, 12);
   if(met_tst_nolep_j2_dphi<1) return 0;
   fillCutflow("zcr", leptons, 13);
   if(0) return 0; // hemisphere cut is done in STPP
   fillCutflow("zcr", leptons, 14);
   if(!trigger_lep) return 0;
   fillCutflow("zcr", leptons, 15);
   if(lep1<30e3) return 0;
   fillCutflow("zcr", leptons, 16);
   if(lep1<7e3) return 0;
   fillCutflow("zcr", leptons, 17);
   if(TMath::Abs(mll-91.2e3)>25e3) return 0;
   fillCutflow("zcr", leptons, 18);
   if(!SFOS) return 0;
   fillCutflow("zcr", leptons, 19);
   return 1;
}


bool plotEvents::fillWCR(TString leptons){
   double lep1, met_sig, charge;
   if(leptons=="e" && n_el==1){
      lep1=el1_pt;
      met_sig=met_significance;
      charge=el1_charge;
   }
   else if(leptons=="u" && n_mu==1){
      lep1=mu1_pt;
      met_sig=999;
      charge=mu1_charge;
   }
   else{
      lep1=0;
      met_sig=0;
      charge=0;
   }

   if(!passJetCleanTight) return 0;
   fillCutflow("wcr", leptons+"p", 1);
   fillCutflow("wcr", leptons+"n", 1);
   if(n_jet!=2) return 0;
   fillCutflow("wcr", leptons+"p", 2);
   fillCutflow("wcr", leptons+"n", 2);
   if(jet1_pt<80e3) return 0;
   fillCutflow("wcr", leptons+"p", 3);
   fillCutflow("wcr", leptons+"n", 3);
   if(jet2_pt<50e3) return 0;
   fillCutflow("wcr", leptons+"p", 4);
   fillCutflow("wcr", leptons+"n", 4);
   if(jj_mass<1e6) return 0;
   fillCutflow("wcr", leptons+"p", 5);
   fillCutflow("wcr", leptons+"n", 5);
   if(jj_deta<4.8) return 0;
   fillCutflow("wcr", leptons+"p", 6);
   fillCutflow("wcr", leptons+"n", 6);
   if(jj_dphi>1.8) return 0;
   fillCutflow("wcr", leptons+"p", 7);
   fillCutflow("wcr", leptons+"n", 7);
   if(met_cst_jet<150e3) return 0;
   fillCutflow("wcr", leptons+"p", 8);
   fillCutflow("wcr", leptons+"n", 8);
   if(met_tst_nolep_et<180e3) return 0;
   fillCutflow("wcr", leptons+"p", 9);
   fillCutflow("wcr", leptons+"n", 9);
   if((n_el!=1 && leptons=="e") || (n_el!=0 && leptons=="u")) return 0;
   fillCutflow("wcr", leptons+"p", 10);
   fillCutflow("wcr", leptons+"n", 10);
   if((n_mu!=1 && leptons=="u") || (n_mu!=0 && leptons=="e")) return 0;
   fillCutflow("wcr", leptons+"p", 11);
   fillCutflow("wcr", leptons+"n", 11);
   if(met_tst_nolep_j1_dphi<1) return 0;
   fillCutflow("wcr", leptons+"p", 12);
   fillCutflow("wcr", leptons+"n", 12);
   if(met_tst_nolep_j2_dphi<1) return 0;
   fillCutflow("wcr", leptons+"p", 13);
   fillCutflow("wcr", leptons+"n", 13);
   if(0) return 0; // hemisphere cut is done in STPP
   fillCutflow("wcr", leptons+"p", 14);
   fillCutflow("wcr", leptons+"n", 14);
   if(!trigger_lep) return 0;
   fillCutflow("wcr", leptons+"p", 15);
   fillCutflow("wcr", leptons+"n", 15);
   if(lep1<30e3) return 0;
   fillCutflow("wcr", leptons+"p", 16);
   fillCutflow("wcr", leptons+"n", 16);
   if(met_sig<4) return 0;
   fillCutflow("wcr", leptons+"p", 17);
   fillCutflow("wcr", leptons+"n", 17);
   if(charge==1){
      fillCutflow("wcr", leptons+"p", 18);
      //plotEvents::fillHists("wcr",leptons+"p");
   }
   else {
      fillCutflow("wcr", leptons+"n", 18);
      //plotEvents::fillHists("wcr",leptons+"n");
   }
   return 1;
}


void plotEvents::cutflowHists(){
   //if(fillSR()) plotEvents::fillHists("sr", "nn");
   //if(fillWCR("e")) plotEvents::fillHists("wcr", "e");
   //if(fillWCR("u")) plotEvents::fillHists("wcr", "u");
   //if(fillZCR("ee")) plotEvents::fillHists("zcr", "ee");
   //if(fillZCR("uu")) plotEvents::fillHists("zcr", "uu");

   fillSR();
   fillWCR("e");
   fillWCR("u");
   fillZCR("ee");
   fillZCR("uu");
}



bool plotEvents::Cut(Long64_t entry)
{
   //SR
        if(n_el==0 && n_mu==0 && trigger_met){
           if(jj_mass>1e6 && met_tst_et>180e3 && met_cst_jet>150e3 && n_jet==2 && jj_dphi<1.8 && jj_deta>4.8 && met_tst_j1_dphi>1.0 && met_tst_j2_dphi>1.0 ) return 1;
        }
   //CR
        else if((n_el>0 || n_mu>0) && trigger_lep){//TODO make plotting of low/high met_sig regions possible
           if(n_mu==0 && n_el==1 && met_significance<4) return 0;
           if(jj_mass>1e6 && met_tst_nolep_et>180e3 && met_cst_jet>150e3 && met_tst_nolep_j1_dphi>1.0 && met_tst_nolep_j2_dphi>1.0 && n_jet == 2 && jj_dphi<1.8 && jj_deta>4.8) return 1;
        }



   return 0;
}

void plotEvents::fillHists(TString region, TString lep){
    double helplumi=lumi; // TODO import list of variables from Style.py
    if (process=="data15" || process=="data16" || process=="data17") helplumi=1.;
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jj_mass"))->Fill(jj_mass,helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jj_dphi"))->Fill(jj_dphi,helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jj_deta"))->Fill(jj_deta,helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jet1_pt"))->Fill(jet1_pt,helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jet2_pt"))->Fill(jet2_pt,helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/met"))->Fill(met_tst_et,helplumi*w);
}


#endif // #ifdef plotEvents_cxx
