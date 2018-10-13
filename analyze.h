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

   TTreeReaderValue<Float_t> j1_pt = {fReader, "j1_pt"};
   TTreeReaderValue<Float_t> j2_pt = {fReader, "j2_pt"};
   TTreeReaderValue<Float_t> j3_pt = {fReader, "j3_pt"};
   TTreeReaderValue<Float_t> j1_eta = {fReader, "j1_eta"};
   TTreeReaderValue<Float_t> j2_eta = {fReader, "j2_eta"};
   TTreeReaderValue<Float_t> j3_eta = {fReader, "j3_eta"};
   TTreeReaderValue<Float_t> j1_phi = {fReader, "j1_phi"};
   TTreeReaderValue<Float_t> j2_phi = {fReader, "j2_phi"};
   TTreeReaderValue<Float_t> j3_phi = {fReader, "j3_phi"};
   TTreeReaderValue<Float_t> mu1_pt = {fReader, "mu1_pt"};
   TTreeReaderValue<Float_t> mu2_pt = {fReader, "mu2_pt"};
   TTreeReaderValue<Float_t> el1_pt = {fReader, "el1_pt"};
   TTreeReaderValue<Float_t> el2_pt = {fReader, "el2_pt"};
   TTreeReaderValue<Int_t> mu1_charge = {fReader, "mu1_charge"};
   TTreeReaderValue<Int_t> mu2_charge = {fReader, "mu2_charge"};
   TTreeReaderValue<Int_t> el1_charge = {fReader, "el1_charge"};
   TTreeReaderValue<Int_t> el2_charge = {fReader, "el2_charge"};
   TTreeReaderValue<Float_t> mll = {fReader, "mll"};
   TTreeReaderValue<Float_t> met_significance = {fReader, "met_significance"};
   TTreeReaderValue<Float_t> averageIntPerXing = {fReader, "averageIntPerXing"};
   TTreeReaderValue<Int_t> isSR = {fReader, "isSR"};
   TTreeReaderValue<Int_t> isCRWep = {fReader, "isCRWep"};
   TTreeReaderValue<Int_t> isCRWen = {fReader, "isCRWen"};
   TTreeReaderValue<Int_t> isCRWepLowSig = {fReader, "isCRWepLowSig"};
   TTreeReaderValue<Int_t> isCRWenLowSig = {fReader, "isCRWenLowSig"};
   TTreeReaderValue<Int_t> isCRWmp = {fReader, "isCRWmp"};
   TTreeReaderValue<Int_t> isCRWmn = {fReader, "isCRWmn"};
   TTreeReaderValue<Int_t> isCRZee = {fReader, "isCRZee"};
   TTreeReaderValue<Int_t> isCRZmm = {fReader, "isCRZmm"};
   TTreeReaderValue<Float_t> met_truth_et = {fReader, "met_truth_et"};
   TTreeReaderValue<Float_t> met_truth_sumet = {fReader, "met_truth_sumet"};
   TTreeReaderValue<Double_t> truth_jj_mass = {fReader, "truth_jj_mass"};


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
