#define truthAnalyzer_cxx


#include "truthAnalyzer.h"
#include <TH2.h>
#include <TStyle.h>



void truthAnalyzer::Begin(TTree * /*tree*/)
{

 TString option = GetOption();
}

void truthAnalyzer::SlaveBegin(TTree * /*tree*/)
{
 TString option = GetOption();
 std::vector<std::string> options = getTokens(option, ",");
 nentries = std::stoi(string(options.at(0)));
 TString outputDir = options.at(1);
 TString output = options.at(2);
 lumi = 36.1;

  // create file
 TString subdir(outputDir);
 std::cout<<"subdir "<<subdir<<std::endl;
 system ("mkdir -p "+subdir);
 TString filename =  output;
 m_prooffile = new TProofOutputFile(TString(subdir+"/"+filename+".root").Data(), "LOCAL");
 m_outfile = m_prooffile->OpenFile("RECREATE");

    //book minitree
 newtree = new TTree("nominal", "nominal");
 BookMinitree();
}

Bool_t truthAnalyzer::Process(Long64_t entry)
{

   fProcessed++; // processed events
   fReader.SetEntry(entry);
   fStatus++; // selected events

   if ((fProcessed - 1) == 0)
    Info("Process", "Started to process %d events...", nentries);
  else if ((fProcessed - 1) % 100000 == 0)
    Info("Process", "Processed %lld / %d events... ", fProcessed - 1, nentries);

  FillMinitree();
  newtree->Fill();

  return kTRUE;
}

void truthAnalyzer::SlaveTerminate()
{
   // save
 m_outfile->Write();
 m_outfile->Close();
 TDirectory *savedir = gDirectory;
 savedir->cd();
 m_prooffile->Print();
 fOutput->Add(m_prooffile);
}

void truthAnalyzer::Terminate()
{

 if (!fInput) Info("Terminate", "processed %lld events", fProcessed);

}

void truthAnalyzer::BookMinitree()
{
 newtree->Branch("jj_mass", &newtree_jj_mass);

 Info("SlaveBegin", "Booked minitree");
}

void truthAnalyzer::FillMinitree()
{

  newtree_jj_mass = *jj_mass;

}
