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
   TString         outFile;
   Float_t         w;
   Int_t           runNumber;
   ULong64_t       eventNumber;
   Int_t           trigger_met;
   Int_t           trigger_lep;
   Int_t           passJetCleanTight;
   Int_t           n_jet;
   Int_t           n_el;
   Int_t           n_mu;
   Double_t        lumi;
   Double_t        jj_mass;
   Double_t        jj_deta;
   Double_t        jj_dphi;
   Double_t        met_tst_j1_dphi;
   Double_t        met_tst_j2_dphi;
   Double_t        met_tst_nolep_j1_dphi;
   Double_t        met_tst_nolep_j2_dphi;
   Float_t         met_tst_et;
   Double_t         met_cst_jet;
   Float_t         met_tst_nolep_et;
   Float_t         met_tst_phi;
   Float_t         met_tst_nolep_phi;
   vector<float>   *mu_charge;
   vector<float>   *mu_pt;
   vector<float>   *el_charge;
   vector<float>   *el_pt;
   vector<float>   *jet_pt;
   vector<float>   *jet_timing;
   vector<float>   *mu_phi;
   vector<float>   *el_phi;
   vector<float>   *mu_eta;
   vector<float>   *el_eta;
   vector<float>   *jet_phi;
   vector<float>   *jet_eta;
   Float_t         met_significance;
   Bool_t          SR;
   Bool_t          CRWep;
   Bool_t          CRWen;
   Bool_t          CRWepLowSig;
   Bool_t          CRWenLowSig;
   Bool_t          CRWmp;
   Bool_t          CRWmn;
   Bool_t          CRZee;
   Bool_t          CRZmm;

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
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_timing;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_met_significance;   //!
   TBranch        *b_SR;   //!
   TBranch        *b_CRWep;   //!
   TBranch        *b_CRWen;   //!
   TBranch        *b_CRWepLowSig;   //!
   TBranch        *b_CRWenLowSig;   //!
   TBranch        *b_CRWmp;   //!
   TBranch        *b_CRWmn;   //!
   TBranch        *b_CRZee;   //!
   TBranch        *b_CRZmm;   //!

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
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_timing", &jet_timing, &b_jet_timing);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("met_significance", &met_significance, &b_met_significance);
   //fChain->SetBranchAddress("SR", &SR, &b_SR);
   //fChain->SetBranchAddress("CRWep", &CRWep, &b_CRWep);
   //fChain->SetBranchAddress("CRWen", &CRWen, &b_CRWen);
   //fChain->SetBranchAddress("CRWepLowSig", &CRWepLowSig, &b_CRWepLowSig);
   //fChain->SetBranchAddress("CRWenLowSig", &CRWenLowSig, &b_CRWenLowSig);
   //fChain->SetBranchAddress("CRWmp", &CRWmp, &b_CRWmp);
   //fChain->SetBranchAddress("CRWmn", &CRWmn, &b_CRWmn);
   //fChain->SetBranchAddress("CRZee", &CRZee, &b_CRZee);
   //fChain->SetBranchAddress("CRZmm", &CRZmm, &b_CRZmm);
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
   if(jet_pt->at(0)<80e3) return 0;
   fillCutflow("sr", "nn", 3);
   if(jet_pt->at(1)<50e3) return 0;
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
      lep1=el_pt->at(0);
      lep2=el_pt->at(1);
      SFOS=el_charge->at(0)!=el_charge->at(1);
	   TLorentzVector e1,e2;
	   e1.SetPtEtaPhiM(el_pt->at(0), el_eta->at(0), el_phi->at(0), 0.511);
	   e2.SetPtEtaPhiM(el_pt->at(1), el_eta->at(1), el_phi->at(1), 0.511);
	   mll=(e1+e2).M();
   }
   else if(leptons=="uu" && n_mu==2){
      lep1=mu_pt->at(0);
      lep2=mu_pt->at(1);
      SFOS=mu_charge->at(0)!=mu_charge->at(1);
	   TLorentzVector m1,m2;
	   m1.SetPtEtaPhiM(mu_pt->at(0), mu_eta->at(0), mu_phi->at(0), 105.6);
	   m2.SetPtEtaPhiM(mu_pt->at(1), mu_eta->at(1), mu_phi->at(1), 105.6);
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
   if(jet_pt->at(0)<80e3) return 0;
   fillCutflow("zcr", leptons, 3);
   if(jet_pt->at(1)<50e3) return 0;
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
      lep1=el_pt->at(0);
      met_sig=met_significance;
      charge=el_charge->at(0);
   }
   else if(leptons=="u" && n_mu==1){
      lep1=mu_pt->at(0);
      met_sig=999;
      charge=mu_charge->at(0);
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
   if(jet_pt->at(0)<80e3) return 0;
   fillCutflow("wcr", leptons+"p", 3);
   fillCutflow("wcr", leptons+"n", 3);
   if(jet_pt->at(1)<50e3) return 0;
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
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jet1_pt"))->Fill(jet_pt->at(0),helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/jet2_pt"))->Fill(jet_pt->at(1),helplumi*w);
    ((TH1D*)fout->Get("pass_"+region+"_allmjj_"+lep+"_"+sys+"/plotEvent_"+process+"/met"))->Fill(met_tst_et,helplumi*w);
}


#endif // #ifdef plotEvents_cxx
