//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 12 14:48:02 2018 by ROOT version 6.13/03
// from TTree VBFH125Nominal/VBFH125Nominal
// found on file: /Users/othmanerifki/vbf/plot/v11Rui/VBFH125.root
//////////////////////////////////////////////////////////

#ifndef analyze_h
#define analyze_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>
#include <map>

class TProofOutputFile;

class analyze : public TSelector {
   public :

   bool doDetail=true; //!

   std::map<TString, TH1F*> histo; //!
   TProofOutputFile *m_prooffile; //!
   TFile *m_outfile; //!

   Long64_t        fProcessed=0;//!
   Int_t nentries; //!
   Float_t lumi;//!

   std::map < TString, Bool_t> isRegion;//!


   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> w = {fReader, "w"};
   TTreeReaderValue<Int_t> runNumber = {fReader, "runNumber"};
   TTreeReaderValue<ULong64_t> eventNumber = {fReader, "eventNumber"};
   TTreeReaderValue<Int_t> trigger_met = {fReader, "trigger_met"};
   TTreeReaderValue<Int_t> trigger_lep = {fReader, "trigger_lep"};
   TTreeReaderValue<Int_t> passJetCleanTight = {fReader, "passJetCleanTight"};
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
   TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};
   TTreeReaderValue<Float_t> met_tst_nolep_et = {fReader, "met_tst_nolep_et"};
   TTreeReaderValue<Float_t> met_tst_phi = {fReader, "met_tst_phi"};
   TTreeReaderValue<Float_t> met_tst_nolep_phi = {fReader, "met_tst_nolep_phi"};
   TTreeReaderArray<float> mu_charge = {fReader, "mu_charge"};
   TTreeReaderArray<float> mu_pt = {fReader, "mu_pt"};
   TTreeReaderArray<float> el_charge = {fReader, "el_charge"};
   TTreeReaderArray<float> el_pt = {fReader, "el_pt"};
   TTreeReaderArray<float> jet_pt = {fReader, "jet_pt"};
   TTreeReaderArray<float> jet_timing = {fReader, "jet_timing"};
   TTreeReaderArray<float> mu_phi = {fReader, "mu_phi"};
   TTreeReaderArray<float> el_phi = {fReader, "el_phi"};
   TTreeReaderArray<float> mu_eta = {fReader, "mu_eta"};
   TTreeReaderArray<float> el_eta = {fReader, "el_eta"};
   TTreeReaderArray<float> jet_phi = {fReader, "jet_phi"};
   TTreeReaderArray<float> jet_eta = {fReader, "jet_eta"};
   TTreeReaderValue<Float_t> met_significance = {fReader, "met_significance"};
/*   TTreeReaderValue<Float_t> GenMET_pt = {fReader, "GenMET_pt"};
   TTreeReaderValue<Float_t> met_truth_et = {fReader, "met_truth_et"};
   TTreeReaderValue<Float_t> met_truth_sumet = {fReader, "met_truth_sumet"};
   TTreeReaderArray<float> truth_jet_pt = {fReader, "truth_jet_pt"};
   TTreeReaderArray<float> truth_jet_eta = {fReader, "truth_jet_eta"};
   TTreeReaderArray<float> truth_jet_phi = {fReader, "truth_jet_phi"};
   TTreeReaderArray<float> truth_jet_m = {fReader, "truth_jet_m"};
   TTreeReaderValue<Double_t> truth_jj_mass = {fReader, "truth_jj_mass"};*/


   analyze(TTree * /*tree*/ =0) { }
   virtual ~analyze() { }
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

   // Analysis methods
   virtual void    BookHistograms();
   virtual void    FillHistograms(Float_t weight = 1.0);
   virtual void    DefineRegions();


   ClassDef(analyze,0);

};

#endif

#ifdef analyze_cxx
void analyze::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t analyze::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef analyze_cxx
