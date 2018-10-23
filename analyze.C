#define analyze_cxx

//
// root> T->Process("analyze.C")
// root> T->Process("analyze.C","some options")
// root> T->Process("analyze.C+")
//

#include "analyze.h"
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>


void analyze::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.

   TString option = GetOption();
   Info("Begin", "Starting VBF analysis with process option: %s", option.Data());
}

void analyze::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.

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
   // The Process() function is called for each entry in the tree

   fProcessed++; // processed events
   fReader.SetEntry(entry);
   fStatus++; // selected events

   if ((fProcessed - 1) == 0)
      Info("Process", "Started to process %d events...", nentries);
   else if ((fProcessed - 1) % 100000 == 0)
      Info("Process", "Processed %lld / %d events... ", fProcessed - 1, nentries);

   DefineRegions();
   FillHistograms(*w);

   /*bool isMC = false;
   if (!isMC) {
      unique = (evtmap[*runNumber].insert(*eventNumber)).second;
      if (!unique) {
         Info("Process", "Warning: duplicate event in RunNb=%d", *runNumber);
         return kTRUE;
      }
   }*/


return kTRUE;
}

void analyze::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

   TString label_jetClass_hist[] = {"j80j50eta48","j80j50eta2","j40j40eta48","j40j40eta2"};
   for (auto lab : label_jetClass_hist){
      TString jetClasstmp = "jetClass_"+lab;
      TString jetClassEfftmp = "jetClassEff_"+lab;
      for (int i=1; i<=4; i++)
         histo[jetClassEfftmp]->SetBinContent(i,histo[jetClasstmp]->GetBinContent(i+2)/histo[jetClasstmp]->GetBinContent(2));
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
   TH1F* tmp = new TH1F("jetClass","jetClass",6,0,6);
   TString label_jetClass[] = {"All","SR","1Central1Fwd","1Fwd1Central","2Fwd", "2Central"};
   for (auto lab : label_jetClass)
      tmp->GetXaxis()->FindBin(lab);
   TString label_jetClass_hist[] = {"j80j50eta48","j80j50eta2","j40j40eta48","j40j40eta2"};
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

void analyze::DefineRegions()
{
   // Regions definition
   isRegion["SR"]   = *isSR;
   isRegion["CR1e"] = (*isCRWep || *isCRWen);
   isRegion["CR1m"] = (*isCRWmp || *isCRWmn);
   isRegion["CR2e"] = *isCRZee;
   isRegion["CR2m"] = *isCRZmm;

   // Study Central vs Forward jet
   isRegion["j80j50eta48"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 4.8) && (*j1_pt > 80e3) && (*j2_pt > 50e3) );
   isRegion["j80j50eta2"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 2) && (*j1_pt > 80e3) && (*j2_pt > 50e3) );
   isRegion["j40j40eta48"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 4.8) && (*j1_pt > 40e3) && (*j2_pt > 40e3) );
   isRegion["j40j40eta2"] = ( *trigger_met && (*n_el == 0) && (*n_mu == 0) && (*jj_deta > 2) && (*j1_pt > 40e3) && (*j2_pt > 40e3) );

}

void analyze::FillHistograms(Float_t weight)
{

   if(isRegion["SR"]){
      histo["jj_mass"]->Fill(*jj_mass*1.e-3, weight);
      histo["met_tst_et"]->Fill(*met_tst_et*1.e-3, weight);
   }

   // Classify jets in the event if Central or Forward
   TString label_jetClass_hist[] = {"j80j50eta48","j80j50eta2","j40j40eta48","j40j40eta2"};
   for (auto lab : label_jetClass_hist){
      TString jetClasstmp = "jetClass_"+lab;
      histo[jetClasstmp]->Fill(0.1);
      if(isRegion[lab] && *isSR){
         histo[jetClasstmp]->Fill(1.1);
         if( abs(*j1_eta) < 2.4 &&  fabs(*j2_eta) > 2.4)
            histo[jetClasstmp]->Fill(2.1);
         else if( abs(*j1_eta) > 2.4 &&  fabs(*j2_eta) < 2.4)
            histo[jetClasstmp]->Fill(3.1);
         else if( abs(*j1_eta) > 2.4 &&  fabs(*j2_eta) > 2.4)
            histo[jetClasstmp]->Fill(4.1);
         else if( abs(*j1_eta) < 2.4 &&  fabs(*j2_eta) < 2.4)
            histo[jetClasstmp]->Fill(5.1);
         else
            histo[jetClasstmp]->Fill(6.1);
      }
   }

}