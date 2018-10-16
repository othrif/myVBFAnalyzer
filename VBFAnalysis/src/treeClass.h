//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 21 15:35:01 2018 by ROOT version 6.12/06
// from TTree Z_EWKNominal/Z_EWKNominal
// found on file: /nfs/dust/atlas/user/ahnenjan/STPProcessing/run/testmerged/Z_EWK.root
//////////////////////////////////////////////////////////

#ifndef treeClass_h
#define treeClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <fstream>
#include <string>

#include <TLorentzVector.h>
#include <TMath.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

class treeClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.


   vector<TH1D*> histVec;
	TFile* outFile;

	TString fname;
	TString ud;
	TString hl;
	TString syst;
    TString binFileName;

    int binLow;
    int binHigh;
    double lumi;

    map<TString, double> cutMap;

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

   treeClass(TTree *tree=0, TFile* outFile=0);
   virtual ~treeClass();
   virtual bool    Cut();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   virtual void init_CutMap(int);
   TString getMassRegion(double, double);
   vector<TString> getRegions();
   void fillHists(int);
};

#endif

#ifdef treeClass_cxx

TString treeClass::getMassRegion(double m1=1.5e6, double m2=2.e6)
{
		if(jj_mass<m1) return "1";
		else if(jj_mass<m2) return "2";
		else return "3";
}

vector<TString> treeClass::getRegions()
{
	vector<TString> regions;
	if (n_el==0 && n_mu==0 && trigger_met) regions.push_back("SR");
	if (n_el==1 && n_mu==0 && trigger_lep)
	{
		if(met_significance>4. && el_pt->at(0)>30.e3)
		{
			if(el_charge->at(0)==1) regions.push_back("oneElePosCR");
			if(el_charge->at(0)==-1) regions.push_back("oneEleNegCR");
		}
	        else if(el_pt->at(0)>30.e3)
		{
			if(el_charge->at(0)==1) regions.push_back("oneElePosLowSigCR");
			if(el_charge->at(0)==-1) regions.push_back("oneEleNegLowSigCR");
		}
	}
	if (n_el==0 && n_mu==1 && trigger_lep && mu_pt->at(0)>30.e3)
	{
		if(mu_charge->at(0)==1) regions.push_back("oneMuPosCR");
		if(mu_charge->at(0)==-1) regions.push_back("oneMuNegCR");
	}
	if (n_el==2 && n_mu==0 && trigger_lep && el_pt->at(0)>30.e3 && el_pt->at(1)>7.e3 && el_charge->at(0)!=el_charge->at(1))
       {
	   TLorentzVector e1,e2;
	   e1.SetPtEtaPhiM(el_pt->at(0), el_eta->at(0), el_phi->at(0), 0.511);
	   e2.SetPtEtaPhiM(el_pt->at(1), el_eta->at(1), el_phi->at(1), 0.511);
	   double mll=(e1+e2).M();
	   if(TMath::Abs(mll-91.2e3)<25.e3) regions.push_back("twoEleCR");
       }
	if (n_el==0 && n_mu==2 && trigger_lep && mu_pt->at(0)>30.e3 && mu_pt->at(1)>7.e3 && mu_charge->at(0)!=mu_charge->at(1)) {
	   TLorentzVector m1,m2;
	   m1.SetPtEtaPhiM(mu_pt->at(0), mu_eta->at(0), mu_phi->at(0), 105.6);
	   m2.SetPtEtaPhiM(mu_pt->at(1), mu_eta->at(1), mu_phi->at(1), 105.6);
	   double mll=(m1+m2).M();
	   if(TMath::Abs(mll-91.2e3)<25.e3) regions.push_back("twoMuCR");
	}
	return regions;
}

void treeClass::fillHists(int bini) 
{
	vector<TString> regions=this->getRegions(); //This vector should allways have length 1 (or 0) because of the orthogonality of the regions
	double finalWeight=1.;
	TString mRegion=this->getMassRegion();
	if (fname!="data") finalWeight=lumi*1000*w;
	for(auto reg:regions)
	{
		TString HISTNAME;
        if(fname=="data" && syst=="Nominal") HISTNAME="h"+fname+"_NONE_"+reg+mRegion+"_obs_cuts";
		else if(syst=="Nominal") HISTNAME="h"+fname+"_VBFjetSel_"+mRegion+"Nom"+"_"+reg+mRegion+"_obs_cuts";
		else if(syst==hl) ;//TODO fix this, this is for systematics without up/down variations
		else HISTNAME="h"+fname+"_VBFjetSel_"+mRegion+syst+hl+"_"+reg+mRegion+"_obs_cuts";
		TH1D* htemp=(TH1D*)outFile->Get(HISTNAME);
		if (htemp==NULL)
		{
			cout << "Hist not found!: " << HISTNAME << endl;
		}
		htemp->Fill(bini-0.5,finalWeight);
	}
}




treeClass::treeClass(TTree *tree, TFile* outF) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/nfs/dust/atlas/user/ahnenjan/STPProcessing/run/testmerged/Z_EWK.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/nfs/dust/atlas/user/ahnenjan/STPProcessing/run/testmerged/Z_EWK.root");
      }
      f->GetObject("Z_EWKNominal",tree);

   }
   Init(tree);
   outFile=outF;
}

treeClass::~treeClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t treeClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t treeClass::LoadTree(Long64_t entry)
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

void treeClass::Init(TTree *tree)
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
   Notify();
}

Bool_t treeClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void treeClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


void treeClass::init_CutMap(int bini){ 

    ifstream binFile(binFileName); 
    string frst, scnd, thrd, frth, ffth, sxth;
    while (binFile >> frst >> scnd >> thrd >> frth >> ffth >> sxth)
    {
        if ((frst)==to_string(bini))
        {
            cutMap["jj_mass"]=stod(scnd);
            cutMap["jj_dphi"]=stod(thrd);
            cutMap["jj_deta"]=stod(frth);
            cutMap["met_tst_et"]=stod(ffth);
            cutMap["n_jet"]=stod(sxth);
        }
    }

    //map<TString, double>::iterator it;
    //for(it=cutMap.begin(); it!=cutMap.end(); ++it)
    //{
    //    cout << it->first << " " << it->second << endl;
    //}
}

//TODO add missing cuts like MHT, met_sig after fix, dphi vars with correct met/met_nolep...
bool treeClass::Cut()
{
   double met;
   vector<TString> reg=getRegions();
   //if (reg.size()>1) std::cout << "What happend here?!" << std::endl;
   if (reg.size()>0 && reg.at(0)=="SR"){
      if(met_cst_jet<150e3 || met_tst_j1_dphi<1.0 || met_tst_j2_dphi<1.0) return 0;
      met=met_tst_et;
   }
   else if (reg.size()>0){
           if(met_cst_jet<150e3 || met_tst_nolep_j1_dphi<1.0 || met_tst_nolep_j2_dphi<1.0) return 0;
	   met=met_tst_nolep_et;
   }
   else{
      met=0;
      return 0;
   }
    if(
        jj_mass>cutMap["jj_mass"] 
     && met>cutMap["met_tst_et"] 
     && n_jet == cutMap["n_jet"] 
     && jj_dphi<cutMap["jj_dphi"] 
     && jj_deta>cutMap["jj_deta"]
        )return 1;
    return 0;
}
#endif // #ifdef treeClass_cxx
