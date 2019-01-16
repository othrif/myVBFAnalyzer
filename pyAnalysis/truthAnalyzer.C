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

   // speed up
  Bool_t saveMe = (*n_jet > 1 && jet_pt[0] >= 60e3 && jet_pt[1] >= 40e3);
  saveMe &= (*jj_mass > 200e3 && *jj_deta>2.5 && *jj_dphi<2.4);
  saveMe &= (*met_tst_et > 100e3 || *met_tst_nolep_et > 100e3);

  if (saveMe){
    FillMinitree();
    newtree->Fill();
  }

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
  newtree->Branch("w", &newtree_w);
  newtree->Branch("runNumber", &newtree_runNumber);
  newtree->Branch("eventNumber", &newtree_eventNumber);
  newtree->Branch("jj_deta", &newtree_jj_deta);
  newtree->Branch("jj_dphi", &newtree_jj_dphi);
  newtree->Branch("jj_mass", &newtree_jj_mass);
  newtree->Branch("n_jet", &newtree_n_jet);
  newtree->Branch("n_jet25", &newtree_n_jet25);
  newtree->Branch("n_jet30", &newtree_n_jet30);
  newtree->Branch("n_jet35", &newtree_n_jet35);
  newtree->Branch("n_jet40", &newtree_n_jet40);
  newtree->Branch("n_jet50", &newtree_n_jet50);
  newtree->Branch("jet_pt", &newtree_jet_pt);
  newtree->Branch("jet_eta", &newtree_jet_eta);
  newtree->Branch("met_tst_et", &newtree_met_tst_et);
  newtree->Branch("met_tst_j1_dphi", &newtree_met_tst_j1_dphi);
  newtree->Branch("met_tst_j2_dphi", &newtree_met_tst_j2_dphi);
  newtree->Branch("met_tst_nolep_et", &newtree_met_tst_nolep_et);
  newtree->Branch("met_tst_nolep_j1_dphi", &newtree_met_tst_nolep_j1_dphi);
  newtree->Branch("met_tst_nolep_j2_dphi", &newtree_met_tst_nolep_j2_dphi);
  newtree->Branch("n_el", &newtree_n_el);
  newtree->Branch("el_pt", &newtree_el_pt);
  newtree->Branch("el_charge", &newtree_el_charge);
  newtree->Branch("n_mu", &newtree_n_mu);
  newtree->Branch("mu_pt", &newtree_mu_pt);
  newtree->Branch("mu_charge", &newtree_mu_charge);
  newtree->Branch("mll", &newtree_mll);
  newtree->Branch("met_significance", &newtree_met_significance);

  Info("SlaveBegin", "Booked minitree");
}

void truthAnalyzer::FillMinitree()
{


  // Processing
  // Njets
  int njet25=0, njet30=0, njet35=0, njet40=0, njet50=0;
  for(auto j : jet_pt){
    if(j > 25e3) njet25++;
    if(j > 30e3) njet30++;
    if(j > 35e3) njet35++;
    if(j > 40e3) njet40++;
    if(j > 50e3) njet50++;
  }
  // Mll
  double mll_tmp=-1;
  TLorentzVector el_tlv[2];
  if (el_pt.GetSize() > 1){
    for(int i=0; i<2; i++)
      el_tlv[i].SetPtEtaPhiM(el_pt[i], el_eta[i], el_phi[i], electron_mass);
    TLorentzVector lep_sum = el_tlv[0] + el_tlv[1];
    mll_tmp = (lep_sum).M();
  }
  //std::cout << "\nrunNumber/eventNumber: " <<  *runNumber << "/" << *eventNumber << std::endl;
  //std::cout << "Mll in ee: " << mll_tmp << ", num e pt's:" << el_pt.GetSize() << ", Nel:" << *n_el << std::endl;
  TLorentzVector mu_tlv[2];
  if (mu_pt.GetSize() > 1){
    for(int i=0; i<2; i++)
      mu_tlv[i].SetPtEtaPhiM(mu_pt[i], mu_eta[i], mu_phi[i], muon_mass);
    TLorentzVector lep_sum = mu_tlv[0] + mu_tlv[1];
    mll_tmp = (lep_sum).M();
  }
  //std::cout << "Mll in mm: " << mll_tmp << ", num mu pt's:" << mu_pt.GetSize() << ", Nmu:" << *n_mu << std::endl;
  // Filling
  newtree_w = *w;
  newtree_runNumber = *runNumber;
  newtree_eventNumber = *eventNumber;
  newtree_jj_deta = *jj_deta;
  newtree_jj_dphi = *jj_dphi;
  newtree_jj_mass = *jj_mass;
  newtree_n_jet = *n_jet;
  newtree_n_jet25 = njet25;
  newtree_n_jet30 = njet30;
  newtree_n_jet35 = njet35;
  newtree_n_jet40 = njet40;
  newtree_n_jet50 = njet50;
  newtree_jet_pt = {jet_pt.begin(), jet_pt.end()};
  newtree_jet_eta = {jet_eta.begin(), jet_eta.end()};
  newtree_met_tst_et = *met_tst_et;
  newtree_met_tst_j1_dphi = *met_tst_j1_dphi;
  newtree_met_tst_j2_dphi = *met_tst_j2_dphi;
  newtree_met_tst_nolep_et = *met_tst_nolep_et;
  newtree_met_tst_nolep_j1_dphi = *met_tst_nolep_j1_dphi;
  newtree_met_tst_nolep_j2_dphi = *met_tst_nolep_j2_dphi;
  newtree_n_el = *n_el;
  newtree_el_pt = {el_pt.begin(), el_pt.end()};
  newtree_el_charge = {el_charge.begin(), el_charge.end()};
  if(*n_el==0){
    newtree_el_charge = {0.,0.};
    newtree_el_pt = {0.,0.};
  }
  newtree_n_mu = *n_mu;
  newtree_mu_pt = {mu_pt.begin(), mu_pt.end()};
  newtree_mu_charge = {mu_charge.begin(), mu_charge.end()};
  if(*n_mu==0){
    newtree_mu_charge = {0.,0.};
    newtree_mu_pt = {0.,0.};
  }
  newtree_mll = mll_tmp;
  newtree_met_significance = *met_significance;

}
