//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  9 20:18:05 2019 by ROOT version 6.13/03
// from TTree VBFH125Nominal/VBFH125Nominal
// found on file: input/VBFH125.root
//////////////////////////////////////////////////////////

#ifndef truthAnalyzer_h
#define truthAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>

// Headers needed by this particular selector
#include <vector>

#define muon_mass             105.6583715   // in MeV
#define electron_mass         0.510998928   // in MeV

class truthAnalyzer : public TSelector {
private :
   TTree* newtree; //!
   TProofOutputFile *m_prooffile; //!
   TFile *m_outfile; //!

public :
   Long64_t        fProcessed=0;//!
   Int_t nentries; //!
   Float_t lumi;//!
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   //Analysis Methods
   void BookMinitree();
   void FillMinitree();

   Float_t         newtree_w;
   UInt_t          newtree_runNumber;
   ULong64_t       newtree_eventNumber;
   Int_t           newtree_n_jet;
   Int_t           newtree_n_el;
   Int_t           newtree_n_mu;
   Double_t        newtree_jj_mass;
   Double_t        newtree_jj_deta;
   Double_t        newtree_jj_dphi;
   Double_t        newtree_met_tst_j1_dphi;
   Double_t        newtree_met_tst_j2_dphi;
   Double_t        newtree_met_tst_nolep_j1_dphi;
   Double_t        newtree_met_tst_nolep_j2_dphi;
   Double_t        newtree_met_cst_jet;
   Float_t         newtree_met_tst_et;
   Float_t         newtree_met_tst_nolep_et;
   Float_t         newtree_met_tst_phi;
   Float_t         newtree_met_tst_nolep_phi;
   vector<float>   newtree_mu_charge;
   vector<float>   newtree_mu_pt;
   vector<float>   newtree_el_charge;
   vector<float>   newtree_el_pt;
   vector<float>   newtree_mu_phi;
   vector<float>   newtree_el_phi;
   vector<float>   newtree_mu_eta;
   vector<float>   newtree_el_eta;
   vector<Float_t> newtree_jet_pt;
   vector<float>   newtree_jet_eta;
   vector<float>   newtree_jet_phi;
   vector<float>   newtree_jet_m;
   vector<float>   newtree_jet_E;
   vector<int>     newtree_jet_label;
   Float_t         newtree_met_significance;
   vector<float>   newtree_j3_centrality;
   vector<float>   newtree_j3_dRj1;
   vector<float>   newtree_j3_dRj2;
   vector<float>   newtree_j3_minDR;
   vector<float>   newtree_j3_mjclosest;
   vector<float>   newtree_j3_min_mj;
   vector<float>   newtree_j3_min_mj_over_mjj;
   Float_t         newtree_mj34;
   Float_t         newtree_max_j_eta;
   Int_t           newtree_n_jet25;
   Int_t           newtree_n_jet30;
   Int_t           newtree_n_jet35;
   Int_t           newtree_n_jet40;
   Int_t           newtree_n_jet50;
   Double_t        newtree_mll;

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> w = {fReader, "w"};
   TTreeReaderValue<UInt_t> runNumber = {fReader, "runNumber"};
   TTreeReaderValue<ULong64_t> eventNumber = {fReader, "eventNumber"};
   TTreeReaderValue<Int_t> n_jet = {fReader, "n_jet"};
   TTreeReaderValue<Int_t> n_el = {fReader, "n_el"};
   TTreeReaderValue<Int_t> n_mu = {fReader, "n_mu"};
   TTreeReaderValue<Double_t> jj_mass = {fReader, "jj_mass"};
   TTreeReaderValue<Double_t> jj_deta = {fReader, "jj_deta"};
   TTreeReaderValue<Double_t> jj_dphi = {fReader, "jj_dphi"};
   TTreeReaderValue<Double_t> met_tst_j1_dphi = {fReader, "met_tst_j1_dphi"};
   TTreeReaderValue<Double_t> met_tst_j2_dphi = {fReader, "met_tst_j2_dphi"};
   TTreeReaderValue<Double_t> met_tst_nolep_j1_dphi = {fReader, "met_tst_nolep_j1_dphi"};
   TTreeReaderValue<Double_t> met_tst_nolep_j2_dphi = {fReader, "met_tst_nolep_j2_dphi"};
   TTreeReaderValue<Double_t> met_cst_jet = {fReader, "met_cst_jet"};
   TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};
   TTreeReaderValue<Float_t> met_tst_nolep_et = {fReader, "met_tst_nolep_et"};
   TTreeReaderValue<Float_t> met_tst_phi = {fReader, "met_tst_phi"};
   TTreeReaderValue<Float_t> met_tst_nolep_phi = {fReader, "met_tst_nolep_phi"};
   TTreeReaderArray<float> mu_charge = {fReader, "mu_charge"};
   TTreeReaderArray<float> mu_pt = {fReader, "mu_pt"};
   TTreeReaderArray<float> el_charge = {fReader, "el_charge"};
   TTreeReaderArray<float> el_pt = {fReader, "el_pt"};
   TTreeReaderArray<float> mu_phi = {fReader, "mu_phi"};
   TTreeReaderArray<float> el_phi = {fReader, "el_phi"};
   TTreeReaderArray<float> mu_eta = {fReader, "mu_eta"};
   TTreeReaderArray<float> el_eta = {fReader, "el_eta"};
   TTreeReaderArray<float> jet_pt = {fReader, "jet_pt"};
   TTreeReaderArray<float> jet_eta = {fReader, "jet_eta"};
   TTreeReaderArray<float> jet_phi = {fReader, "jet_phi"};
   TTreeReaderArray<float> jet_m = {fReader, "jet_m"};
   TTreeReaderArray<float> jet_E = {fReader, "jet_E"};
   TTreeReaderArray<int> jet_label = {fReader, "jet_label"};
   TTreeReaderValue<Float_t> met_significance = {fReader, "met_significance"};
   TTreeReaderArray<float> j3_centrality = {fReader, "j3_centrality"};
   TTreeReaderArray<float> j3_dRj1 = {fReader, "j3_dRj1"};
   TTreeReaderArray<float> j3_dRj2 = {fReader, "j3_dRj2"};
   TTreeReaderArray<float> j3_minDR = {fReader, "j3_minDR"};
   TTreeReaderArray<float> j3_mjclosest = {fReader, "j3_mjclosest"};
   TTreeReaderArray<float> j3_min_mj = {fReader, "j3_min_mj"};
   TTreeReaderArray<float> j3_min_mj_over_mjj = {fReader, "j3_min_mj_over_mjj"};
   TTreeReaderValue<Float_t> mj34 = {fReader, "mj34"};
   TTreeReaderValue<Float_t> max_j_eta = {fReader, "max_j_eta"};


   truthAnalyzer(TTree * /*tree*/ =0) { }
   virtual ~truthAnalyzer() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
   std::vector<std::string> getTokens(TString line, TString delim);

   ClassDef(truthAnalyzer,0);

};

#endif

#ifdef truthAnalyzer_cxx
void truthAnalyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t truthAnalyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

std::vector<std::string> truthAnalyzer::getTokens(TString line, TString delim)
{
   std::vector<std::string> vtokens;
   TObjArray *              tokens = TString(line).Tokenize(delim); // delimiters
   if (tokens->GetEntriesFast()) {
      TIter       iString(tokens);
      TObjString *os = 0;
      while ((os = (TObjString *)iString())) {
         vtokens.push_back(os->GetString().Data());
      }
   }
   delete tokens;

   return vtokens;
}




#endif // #ifdef truthAnalyzer_cxx
