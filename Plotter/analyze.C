#define analyze_cxx
// The class definition in analyze.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("analyze.C")
// root> T->Process("analyze.C","some options")
// root> T->Process("analyze.C+")
//


#include "analyze.h"
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>


//#include <TProofOutputFile.h>
//#include <TLorentzVector.h>
//#include <TParameter.h>
//#include <stdexcept>

void analyze::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   Info("Begin", "Starting VBF analysis with process option: %s", option.Data());
}

void analyze::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   nentries = std::stoi(string(option));
   lumi = 36.1;

  // create file
   TString filename =  "outFile.root";
   m_prooffile = new TProofOutputFile(filename, "LOCAL");
   m_outfile = m_prooffile->OpenFile("RECREATE");

   BookHistograms();

}

Bool_t analyze::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fProcessed++; // processed events
   fReader.SetEntry(entry);
   fStatus++; // selected events

   if ((fProcessed - 1) == 0)
      Info("Process", "Started to process %d events...", nentries);
   else if ((fProcessed - 1) % 100000 == 0)
      Info("Process", "Processed %lld / %d events... ", fProcessed - 1, nentries);

   DefineRegions();
   FillHistograms(*w);

   return kTRUE;
}

void analyze::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
if(doDetail){
   TString label_jetClass_hist[] = {"SR","j80j50eta48","j80j50eta4","j80j50eta3","j70j40eta48","j40j40eta48"};
   for (auto lab : label_jetClass_hist){
      TString jetClasstmp = "jetClass_"+lab;
      TString jetClassEfftmp = "jetClassEff_"+lab;
   for (int i=1; i<=4; i++)
      histo[jetClassEfftmp]->SetBinContent(i,histo[jetClasstmp]->GetBinContent(i+2)/histo[jetClasstmp]->GetBinContent(2));
}
}
   // save
   m_outfile->Write();
   m_outfile->Close();
   TDirectory *savedir = gDirectory;
   savedir->cd();
//   m_prooffile->Print();
   fOutput->Add(m_prooffile);
}

void analyze::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   if (!fInput) Info("Terminate", "processed %lld events", fProcessed);

}

void analyze::BookHistograms()
{

   histo.clear();
   histo["jj_mass"] = new TH1F("jj_mass", "jj_mass;m_{jj} [GeV];events", 100, 0, 5000);
   histo["met_tst_et"] = new TH1F("met_tst_et", "met_tst_et;MET [GeV];events", 100, 0, 1000);

// Jet class study
if(doDetail){
   TH1F* tmp = new TH1F("jetClass","jetClass",10,0,10);
   TString label_jetClass[] = {"All","SR","1Central1Fwd","1Fwd1Central","2Fwd", "2Central"};
   for (auto lab : label_jetClass)
      tmp->GetXaxis()->FindBin(lab);
   TString label_jetClass_hist[] = {"SR","j80j50eta48","j80j50eta4","j80j50eta3","j70j40eta48","j40j40eta48"};
   TH1F* tmpEff = new TH1F("jetClassEff","jetClassEff",4,0,4);
   for (int i=2; i<6; i++)
      tmpEff->GetXaxis()->FindBin(label_jetClass[i]);

   for (auto lab : label_jetClass_hist){
      histo["jetClass_"+lab] = (TH1F*)tmp->Clone("jetClass_"+lab);
      histo["jetClassEff_"+lab] = (TH1F*)tmpEff->Clone("jetClassEff_"+lab);
   }
   delete tmp;
   delete tmpEff;
}
}

void analyze::DefineRegions()
{
   // Regions definition
   bool metSel = (*met_tst_et > 180e3) && (*met_tst_j1_dphi>1.0) && (*met_tst_j2_dphi>1.0);
   bool jetSel = (*n_jet == 2) && (jet_pt[0] > 80e3) && (jet_pt[1] > 50e3);
   bool vbfSel = (*jj_deta > 4.8) && ((jet_eta[0] * jet_eta[1])<0) && (*jj_mass > 1e6) && (*jj_dphi < 1.8);
   bool commonSel = metSel && jetSel && vbfSel;

   isRegion["SR"]   = ( commonSel && *trigger_met && (*n_el == 0) && (*n_mu == 0) );

if(doDetail){
   isRegion["PRE"]  = commonSel;
   isRegion["CR1e"] = ( commonSel && *trigger_lep && (*n_el == 1) && (*n_mu == 0) && *met_significance > 4.0);
   isRegion["CR1m"] = ( commonSel && *trigger_lep && (*n_el == 0) && (*n_mu == 1) );
   isRegion["CR2e"] = ( commonSel && *trigger_lep && (*n_el == 2) && (*n_mu == 0) );
   isRegion["CR2m"] = ( commonSel && *trigger_lep && (*n_el == 0) && (*n_mu == 2) );

   // Study Central vs Forward jet
   isRegion["j80j50eta48"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 4.8) && (jet_pt[0] > 80e3) && (jet_pt[1] > 50e3) );
   isRegion["j80j50eta4"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 3) && (jet_pt[0] > 80e3) && (jet_pt[1] > 50e3) );
   isRegion["j80j50eta3"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 2) && (jet_pt[0] > 80e3) && (jet_pt[1] > 50e3) );
   isRegion["j70j40eta48"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 4.8) && (jet_pt[0] > 70e3) && (jet_pt[1] > 40e3) );
   isRegion["j40j40eta48"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 4.8) && (jet_pt[0] > 40e3) && (jet_pt[1] > 40e3) );
}
}

void analyze::FillHistograms(Float_t weight)
{

   histo["jj_mass"]->Fill(*jj_mass*1.e-3, weight);
   histo["met_tst_et"]->Fill(*met_tst_et*1.e-3, weight);

if(doDetail){
   // Classify jets in the event if Central or Forward
   TString label_jetClass_hist[] = {"j80j50eta48","j80j50eta4","j80j50eta3","j70j40eta48","j40j40eta48"};
   for (auto lab : label_jetClass_hist){
      TString jetClasstmp = "jetClass_"+lab;
      histo[jetClasstmp]->Fill(0.1);
      if(isRegion[lab]){
         histo[jetClasstmp]->Fill(1.1);
         if( abs(jet_eta[0]) < 2.4 &&  fabs(jet_eta[1]) > 2.4)
            histo[jetClasstmp]->Fill(2.1);
         else if( abs(jet_eta[0]) > 2.4 &&  fabs(jet_eta[1]) < 2.4)
            histo[jetClasstmp]->Fill(3.1);
         else if( abs(jet_eta[0]) > 2.4 &&  fabs(jet_eta[1]) > 2.4)
            histo[jetClasstmp]->Fill(4.1);
         else if( abs(jet_eta[0]) < 2.4 &&  fabs(jet_eta[1]) < 2.4)
            histo[jetClasstmp]->Fill(5.1);
         else
            histo[jetClasstmp]->Fill(6.1);
      }
   }
}

}