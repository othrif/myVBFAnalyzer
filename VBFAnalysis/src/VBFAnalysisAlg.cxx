// VBFAnalysis includes
#include "VBFAnalysisAlg.h"
#include "SUSYTools/SUSYCrossSection.h"
#include "PathResolver/PathResolver.h"
//#include "xAODEventInfo/EventInfo.h"
#include <vector>
#include "TLorentzVector.h"

#define muon_mass             105.6583715   // in MeV
#define electron_mass         0.510998928   // in MeV


VBFAnalysisAlg::VBFAnalysisAlg( const std::string& name, ISvcLocator* pSvcLocator ) : AthAnalysisAlgorithm( name, pSvcLocator ){
  declareProperty( "currentSample", m_currentSample = "W_strong", "current sample");
  declareProperty( "runNumberInput", m_runNumberInput, "runNumber read from file name");
  declareProperty( "isMC", m_isMC = true, "true if sample is MC" );
  declareProperty( "currentVariation", m_currentVariation = "Nominal", "current sytematics of the tree" );
  declareProperty( "normFile", m_normFile = "current.root", "path to a file with the number of events processed" );
  declareProperty( "mcCampaign", m_mcCampaign = "mc16a", "mcCampaign of the mc sample. only read if isMC is true" );
}


VBFAnalysisAlg::~VBFAnalysisAlg() {}


StatusCode VBFAnalysisAlg::initialize() {
  ATH_MSG_INFO ("Initializing " << name() << "...");
  //
  //This is called once, before the start of the event loop
  //Retrieves of tools you have configured in the joboptions go here
  //

  cout<<"NAME of input tree in intialize ======="<<m_currentVariation<<endl;
  cout << "isMC: " << m_isMC << endl;
  //  cout<<"NAME of output before ======="<<newtree->GetName()<<endl;
  cout<< "CURRENT  sample === "<< m_currentSample<<endl;

  //double crossSection;
  if(m_isMC){
    //SUSY::CrossSectionDB *my_XsecDB;
    std::string xSecFilePath = "dev/PMGTools/PMGxsecDB_mc15.txt";
    xSecFilePath = PathResolverFindCalibFile(xSecFilePath);
    my_XsecDB = new SUSY::CrossSectionDB(xSecFilePath);
    // if( (runNumber == 308567 || runNumber == 308276 ) ){
    //   if(truthHiggs_pt->size() > 0) w_VBFhiggs =  -0.000342 * truthHiggs_pt->at(0)/GeV - 0.0708;
    // }else {
    //   w_VBFhiggs =1.;
    // }
  }
  //    if(runNumber >= 276262 && runNumber <= 284484) is2015 =true;
  //    else if(runNumber >= 296939 && runNumber <= 311481) is2016 =true;
  //    else throw std::invalid_argument("runNumber could not be identified with a dataset :o");

  //Create new output TTree
  treeTitleOut = m_currentSample+m_currentVariation;
  treeNameOut = m_currentSample+m_currentVariation;
  m_tree_out = new TTree(treeNameOut.c_str(), treeTitleOut.c_str());
  m_tree_out->Branch("w",&w);
  m_tree_out->Branch("runNumber",&runNumber);
  m_tree_out->Branch("eventNumber",&eventNumber);
  m_tree_out->Branch("trigger_met", &trigger_met);
  m_tree_out->Branch("trigger_lep", &trigger_lep);
  m_tree_out->Branch("passJetCleanTight", &passJetCleanTight);
  m_tree_out->Branch("n_jet",&n_jet);
  m_tree_out->Branch("n_el",&n_el);
  m_tree_out->Branch("n_mu",&n_mu);
  m_tree_out->Branch("jj_mass",&jj_mass);
  m_tree_out->Branch("jj_deta",&jj_deta);
  m_tree_out->Branch("jj_dphi",&jj_dphi);
  m_tree_out->Branch("met_tst_j1_dphi",&met_tst_j1_dphi);
  m_tree_out->Branch("met_tst_j2_dphi",&met_tst_j2_dphi);
  m_tree_out->Branch("met_tst_nolep_j1_dphi",&met_tst_nolep_j1_dphi);
  m_tree_out->Branch("met_tst_nolep_j2_dphi",&met_tst_nolep_j2_dphi);
  m_tree_out->Branch("met_tst_et",&met_tst_et);
  m_tree_out->Branch("met_cst_jet",&met_cst_jet);
  m_tree_out->Branch("met_tst_nolep_et",&met_tst_nolep_et);
  m_tree_out->Branch("met_tst_phi",&met_tst_phi);
  m_tree_out->Branch("met_tst_nolep_phi",&met_tst_nolep_phi);
  m_tree_out->Branch("j1_pt",&j1_pt);
  m_tree_out->Branch("j2_pt",&j2_pt);
  m_tree_out->Branch("j3_pt",&j3_pt);
  m_tree_out->Branch("j1_eta",&j1_eta);
  m_tree_out->Branch("j2_eta",&j2_eta);
  m_tree_out->Branch("j3_eta",&j3_eta);
  m_tree_out->Branch("j1_phi",&j1_phi);
  m_tree_out->Branch("j2_phi",&j2_phi);
  m_tree_out->Branch("j3_phi",&j3_phi);
  m_tree_out->Branch("mu1_pt",&mu1_pt);
  m_tree_out->Branch("mu2_pt",&mu2_pt);
  m_tree_out->Branch("el1_pt",&el1_pt);
  m_tree_out->Branch("el2_pt",&el2_pt);
    m_tree_out->Branch("mu1_eta",&mu1_eta);
  m_tree_out->Branch("mu2_eta",&mu2_eta);
  m_tree_out->Branch("el1_eta",&el1_eta);
  m_tree_out->Branch("el2_eta",&el2_eta);
    m_tree_out->Branch("mu1_phi",&mu1_phi);
  m_tree_out->Branch("mu2_phi",&mu2_phi);
  m_tree_out->Branch("el1_phi",&el1_phi);
  m_tree_out->Branch("el2_phi",&el2_phi);
  m_tree_out->Branch("mu1_charge",&mu1_charge);
  m_tree_out->Branch("mu2_charge",&mu2_charge);
  m_tree_out->Branch("el1_charge",&el1_charge);
  m_tree_out->Branch("el2_charge",&el2_charge);
  m_tree_out->Branch("mll",&mll);
  m_tree_out->Branch("met_significance",&met_significance);
  m_tree_out->Branch("averageIntPerXing",&averageIntPerXing);
  m_tree_out->Branch("isSR",&isSR);
  m_tree_out->Branch("isCRWep",&isCRWep);
  m_tree_out->Branch("isCRWen",&isCRWen);
  m_tree_out->Branch("isCRWepLowSig",&isCRWepLowSig);
  m_tree_out->Branch("isCRWenLowSig",&isCRWenLowSig);
  m_tree_out->Branch("isCRWmp",&isCRWmp);
  m_tree_out->Branch("isCRWmn",&isCRWmn);
  m_tree_out->Branch("isCRZee",&isCRZee);
  m_tree_out->Branch("isCRZmm",&isCRZmm);

  //Register the output TTree
  CHECK(histSvc()->regTree("/MYSTREAM/"+treeTitleOut,m_tree_out));
  MapNgen(); //fill std::map with dsid->Ngen
  ATH_MSG_DEBUG ("Done Initializing");

  std::ostringstream runNumberss;
  runNumberss << runNumber;
  outputName = m_currentSample+m_currentVariation+runNumberss.str();
  return StatusCode::SUCCESS;
}

StatusCode VBFAnalysisAlg::finalize() {
  ATH_MSG_INFO ("Finalizing " << name() << "...");
  //
  //Things that happen once at the end of the event loop go here
  //


  return StatusCode::SUCCESS;
}

StatusCode VBFAnalysisAlg::MapNgen(){
  TFile *f = TFile::Open(m_normFile.c_str(),"READ");
  if(!f or f->IsZombie()) std::cout << "ERROR normFile. Could not open " << m_normFile << std::endl;
  h_Gen = (TH1F*) f->Get("h_total");
  if(!h_Gen)ATH_MSG_WARNING("Number of events not found");

  for(int i=1; i<=h_Gen->GetNbinsX();i++){
    TString tmp = h_Gen->GetXaxis()->GetBinLabel(i);
    int dsid = tmp.Atoi();
    float N = h_Gen->GetBinContent(i);
    Ngen[dsid]=N;
    //std::cout << "input: " << dsid << " " << N << std::endl;
  }

  return StatusCode::SUCCESS;

}

StatusCode VBFAnalysisAlg::execute() {
  ATH_MSG_DEBUG ("Executing " << name() << "...");
  //setFilterPassed(false); //optional: start with algorithm not passed
  //m_tree->GetEntry(m_tree->GetReadEntry());
  m_tree->GetEntry(nFileEvt);

  // check that we don't have too many events
  if(nFileEvt>=nFileEvtTot){
    ATH_MSG_ERROR("VBFAnaysisAlg::execute: Too  many events:  " << nFileEvt << " total evts: " << nFileEvtTot);
    return StatusCode::SUCCESS;
  }

  // iterate event count
  ++nFileEvt;
  if (runNumber != m_runNumberInput){ //HACK to hard set the run number
    ATH_MSG_ERROR("VBFAnaysisAlg::execute: runNumber " << runNumber << " != m_runNumberInput " << m_runNumberInput << " " << jj_dphi << " avg: " << averageIntPerXing);
    runNumber=m_runNumberInput;
  }

  npevents++;
  if( (npevents%10000) ==0) std::cout <<" Processed "<< npevents << " Events"<<std::endl;

  isSR = 0;
  isCRWep = 0;
  isCRWen = 0;
  isCRWepLowSig = 0;
  isCRWenLowSig = 0;
  isCRWmp = 0;
  isCRWmn = 0;
  isCRZee = 0;
  isCRZmm = 0;

  if (m_isMC){
    crossSection = my_XsecDB->xsectTimesEff(runNumber);//xs in pb
    if(Ngen[runNumber]>0)  weight = crossSection/Ngen[runNumber];
    else ATH_MSG_WARNING("Ngen " << Ngen[runNumber] << " dsid " << runNumber );
    ATH_MSG_DEBUG("VBFAnalysisAlg: xs: "<< crossSection << " nevent: " << Ngen[runNumber] );
  } else {
    weight = 1;
  }

  if (!((passGRL == 1) & (passPV == 1) & (passDetErr == 1) & (passJetCleanLoose == 1))) return StatusCode::SUCCESS;
  ATH_MSG_DEBUG ("Pass GRL, PV, DetErr, JetCleanLoose");
  //if (!(n_jet >= 2)) return StatusCode::SUCCESS;
  ATH_MSG_DEBUG ("n_jet >= 2!");
  if (!((jet_pt->at(0) > 70e3) & (jet_pt->at(1) > 40e3) & (jj_dphi < 2.0) & (jj_deta > 4.0) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 2e5) & (met_cst_jet > 100e3))) return StatusCode::SUCCESS;
  ATH_MSG_DEBUG ("Pass VBF cuts!");
  if(n_el== 1) {
    met_significance = met_tst_et/1e3/sqrt(jet_pt->at(0)/1e3+jet_pt->at(1)/1e3+el_pt->at(0)/1e3);
  } else {
    met_significance = 0;
  }
  ATH_MSG_DEBUG ("met_significance calculated");

  // Jets
  j1_pt = jet_pt->at(0);
  j2_pt = jet_pt->at(1);
  j1_eta = jet_eta->at(0);
  j2_eta = jet_eta->at(1);
  j1_phi = jet_phi->at(0);
  j2_phi = jet_phi->at(1);
  if(jet_pt->size() > 2){
    j3_pt = jet_pt->at(2);
    j3_eta = jet_eta->at(2);
    j3_phi = jet_phi->at(2);
  }
  else {
    j3_pt = -999.e3;
    j3_eta = -999.;
    j3_phi = -999.;
  }
  ATH_MSG_DEBUG ("done with jets");
  // Leptons
  mll = -999.;
  mu1_pt = -999.e3;
  mu1_charge = -999.;
  mu1_eta = -999.;
  mu1_phi = -999.;
  mu2_pt = -999.e3;
  mu2_charge = -999.;
  mu2_eta = -999.;
  mu2_phi = -999.;
  el1_pt = -999.e3;
  el1_charge = -999.;
  el1_eta = -999.;
  el1_phi = -999.;
  el2_pt = -999.e3;
  el2_charge = -999.;
  el2_eta = -999.;
  el2_phi = -999.;
  TLorentzVector el_tlv[2];
  TLorentzVector mu_tlv[2];
  if(el_pt->size() > 0){
    el1_pt = el_pt->at(0);
    el1_charge = el_charge->at(0);
    el1_eta = el_eta->at(0);
    el1_phi = el_phi->at(0);
    if (el_pt->size() > 1){
      el2_pt = el_pt->at(1);
      el2_charge = el_charge->at(1);
      el2_eta = el_eta->at(1);
      el2_phi = el_phi->at(1);
      for(int i=0; i<2; i++)
        el_tlv[i].SetPtEtaPhiM(el_pt->at(i), el_eta->at(i), el_phi->at(i), electron_mass);
      TLorentzVector lep_sum = el_tlv[0] + el_tlv[1];
      mll = (lep_sum).M();
    }
  }
  ATH_MSG_DEBUG ("done with electrons");
  if(mu_pt->size() > 0){
    mu1_pt = mu_pt->at(0);
    mu1_charge = mu_charge->at(0);
    mu1_eta = mu_eta->at(0);
    mu1_phi = mu_phi->at(0);
    if (mu_pt->size() > 1){
      mu2_pt = mu_pt->at(1);
      mu2_charge = mu_charge->at(1);
      mu2_eta = mu_eta->at(1);
      mu2_phi = mu_phi->at(1);
      for(int i=0; i<2; i++)
        mu_tlv[i].SetPtEtaPhiM(mu_pt->at(i), mu_eta->at(i), mu_phi->at(i), muon_mass);
      TLorentzVector lep_sum = mu_tlv[0] + mu_tlv[1];
      mll = (lep_sum).M();
    }
  }
    ATH_MSG_DEBUG ("done with muons");

  // All selection:
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_met == 1) & (met_tst_et       > 180e3) & (met_tst_j1_dphi      >1.0) & (met_tst_j2_dphi      >1.0) & (n_el == 0) & (n_mu == 0)) isSR = 1;
  if (isSR) ATH_MSG_DEBUG ("It's SR!"); else ATH_MSG_DEBUG ("It's NOT SR");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 1) & (n_mu == 0) ){ if ((el_charge->at(0) > 0) & (met_significance > 4.0) & (el_pt->at(0) > 30e3)) isCRWep = 1;}
  if (isCRWep) ATH_MSG_DEBUG ("It's CRWep!"); else ATH_MSG_DEBUG ("It's NOT CRWep");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 1) & (n_mu == 0) ){ if ((el_charge->at(0) < 0) & (met_significance > 4.0) & (el_pt->at(0) > 30e3)) isCRWen = 1;}
  if (isCRWen) ATH_MSG_DEBUG ("It's CRWen!"); else ATH_MSG_DEBUG ("It's NOT CRWen");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 1) & (n_mu == 0) ){ if ((el_charge->at(0) > 0) & (met_significance <= 4.0) & (el_pt->at(0) > 30e3)) isCRWepLowSig = 1;}
  if (isCRWepLowSig) ATH_MSG_DEBUG ("It's CRWepLowSig!"); else ATH_MSG_DEBUG ("It's NOT CRWepLowSig");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 1) & (n_mu == 0) ){ if ((el_charge->at(0) < 0) & (met_significance <= 4.0) & (el_pt->at(0) > 30e3)) isCRWenLowSig = 1;}
  if (isCRWenLowSig) ATH_MSG_DEBUG ("It's CRWenLowSig!"); else ATH_MSG_DEBUG ("It's NOT CRWenLowSig");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 0) & (n_mu == 1) ){ if ((mu_charge->at(0) > 0) & (mu_pt->at(0) > 30e3)) isCRWmp = 1;}
  if (isCRWmp) ATH_MSG_DEBUG ("It's CRWmp!"); else ATH_MSG_DEBUG ("It's NOT CRWmp");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 0) & (n_mu == 1) ){ if ((mu_charge->at(0) < 0) & (mu_pt->at(0) > 30e3)) isCRWmn = 1;}
  if (isCRWmn) ATH_MSG_DEBUG ("It's CRWmn!"); else ATH_MSG_DEBUG ("It's NOT CRWmn");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 2) & (n_mu == 0) ) { if ((el_charge->at(0)*el_charge->at(1) < 0) & (el_pt->at(0) > 30e3) & (el_pt->at(1) > 7e3) & (TMath::Abs(mll-91.2e3)<25e3)) isCRZee = 1;}
  if (isCRZee) ATH_MSG_DEBUG ("It's CRZee!"); else ATH_MSG_DEBUG ("It's NOT CRZee");
  if ((passJetCleanTight == 1) & (n_jet == 2) & (jet_pt->at(0) > 80e3) & (jet_pt->at(1) > 50e3) & (jj_dphi < 1.8) & (jj_deta > 4.8) & ((jet_eta->at(0) * jet_eta->at(1))<0) & (jj_mass > 1e6) & (met_cst_jet > 150e3) & (trigger_lep == 1) & (met_tst_nolep_et > 180e3) & (met_tst_nolep_j1_dphi>1.0) & (met_tst_nolep_j2_dphi>1.0) & (n_el == 0) & (n_mu == 2) ) { if ((mu_charge->at(0)*mu_charge->at(1) < 0) & (mu_pt->at(0) > 30e3) & (mu_pt->at(1) > 7e3) & (TMath::Abs(mll-91.2e3)<25e3)) isCRZmm = 1;}
  if (isCRZmm) ATH_MSG_DEBUG ("It's CRZmm!"); else ATH_MSG_DEBUG ("It's NOT CRZmm");

  w = weight*mcEventWeight*puWeight*jvtSFWeight*elSFWeight*muSFWeight*elSFTrigWeight*muSFTrigWeight;
  ATH_MSG_DEBUG("VBFAnalysisAlg: weight: " << weight << " mcEventWeight: " << mcEventWeight << " puWeight: " << puWeight << " jvtSFWeight: " << jvtSFWeight << " elSFWeight: " << elSFWeight << " muSFWeight: " << muSFWeight << " elSFTrigWeight: " << elSFTrigWeight << " muSFTrigWeight: " << muSFTrigWeight);
  // only save events that pass any of the regions
  if (!(isSR || isCRWep || isCRWen || isCRWepLowSig || isCRWenLowSig || isCRWmp || isCRWmn || isCRZee || isCRZmm)) return StatusCode::SUCCESS;


  m_tree_out->Fill();

  //setFilterPassed(true); //if got here, assume that means algorithm passed
  return StatusCode::SUCCESS;
}

StatusCode VBFAnalysisAlg::beginInputFile() {
  //
  //This method is called at the start of each input file, even if
  //the input file contains no events. Accumulate metadata information here
  //

  //example of retrieval of CutBookkeepers: (remember you will need to include the necessary header files and use statements in requirements file)
  // const xAOD::CutBookkeeperContainer* bks = 0;
  // CHECK( inputMetaStore()->retrieve(bks, "CutBookkeepers") );

  //example of IOVMetaData retrieval (see https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/AthAnalysisBase#How_to_access_file_metadata_in_C)
  //float beamEnergy(0); CHECK( retrieveMetadata("/TagInfo","beam_energy",beamEnergy) );
  //std::vector<float> bunchPattern; CHECK( retrieveMetadata("/Digitiation/Parameters","BeamIntensityPattern",bunchPattern) );
  ATH_MSG_INFO("VBFAnalysisAlg::beginInputFile()");
  nFileEvt=0;
  m_treeName = "MiniNtuple";
  if(m_currentVariation!="Nominal")
    m_treeName = "MiniNtuple_"+m_currentVariation;
  std::cout << "Tree: " << m_treeName << std::endl;
  m_tree = static_cast<TTree*>(currentFile()->Get(m_treeName));
  nFileEvtTot=m_tree->GetEntries();
  m_tree->SetBranchStatus("*",0);
  m_tree->SetBranchStatus("runNumber", 1);
  m_tree->SetBranchStatus("eventNumber", 1);
  m_tree->SetBranchStatus("averageIntPerXing", 1);
  m_tree->SetBranchStatus("mcEventWeight", 1);
  m_tree->SetBranchStatus("puWeight", 1);
  m_tree->SetBranchStatus("jvtSFWeight", 1);
  m_tree->SetBranchStatus("elSFWeight", 1);
  m_tree->SetBranchStatus("muSFWeight", 1);
  m_tree->SetBranchStatus("elSFTrigWeight", 1);
  m_tree->SetBranchStatus("muSFTrigWeight", 1);
  m_tree->SetBranchStatus("trigger_met", 1);
  m_tree->SetBranchStatus("trigger_lep", 1);
  m_tree->SetBranchStatus("passGRL", 1);
  m_tree->SetBranchStatus("passPV", 1);
  m_tree->SetBranchStatus("passDetErr", 1);
  m_tree->SetBranchStatus("passJetCleanLoose", 1);
  m_tree->SetBranchStatus("passJetCleanTight", 1);
  m_tree->SetBranchStatus("n_jet",1);
  m_tree->SetBranchStatus("n_el",1);
  m_tree->SetBranchStatus("n_mu",1);
  m_tree->SetBranchStatus("jj_mass",1);
  m_tree->SetBranchStatus("jj_deta",1);
  m_tree->SetBranchStatus("jj_dphi",1);
  m_tree->SetBranchStatus("met_tst_j1_dphi",1);
  m_tree->SetBranchStatus("met_tst_j2_dphi",1);
  m_tree->SetBranchStatus("met_tst_nolep_j1_dphi",1);
  m_tree->SetBranchStatus("met_tst_nolep_j2_dphi",1);
  m_tree->SetBranchStatus("met_tst_et",1);
  m_tree->SetBranchStatus("met_cst_jet",1);
  m_tree->SetBranchStatus("met_tst_nolep_et",1);
  m_tree->SetBranchStatus("met_tst_phi",1);
  m_tree->SetBranchStatus("met_tst_nolep_phi",1);
  m_tree->SetBranchStatus("mu_charge",1);
  m_tree->SetBranchStatus("mu_pt",1);
  m_tree->SetBranchStatus("mu_phi",1);
  m_tree->SetBranchStatus("mu_eta",1);
  m_tree->SetBranchStatus("el_charge",1);
  m_tree->SetBranchStatus("el_pt",1);
  m_tree->SetBranchStatus("el_phi",1);
  m_tree->SetBranchStatus("el_eta",1);
  m_tree->SetBranchStatus("jet_pt",1);
  m_tree->SetBranchStatus("jet_phi",1);
  m_tree->SetBranchStatus("jet_eta",1);
  m_tree->SetBranchStatus("jet_jvt",1);
  m_tree->SetBranchStatus("jet_timing",1);

  m_tree->SetBranchAddress("runNumber", &runNumber);
  m_tree->SetBranchAddress("eventNumber", &eventNumber);
  m_tree->SetBranchAddress("averageIntPerXing", &averageIntPerXing);
  m_tree->SetBranchAddress("mcEventWeight", &mcEventWeight);
  m_tree->SetBranchAddress("puWeight", &puWeight);
  m_tree->SetBranchAddress("jvtSFWeight", &jvtSFWeight);
  m_tree->SetBranchAddress("elSFWeight", &elSFWeight);
  m_tree->SetBranchAddress("muSFWeight", &muSFWeight);
  m_tree->SetBranchAddress("elSFTrigWeight", &elSFTrigWeight);
  m_tree->SetBranchAddress("muSFTrigWeight", &muSFTrigWeight);
  m_tree->SetBranchAddress("trigger_lep", &trigger_lep);
  m_tree->SetBranchAddress("trigger_met", &trigger_met);
  m_tree->SetBranchAddress("passGRL", &passGRL);
  m_tree->SetBranchAddress("passPV", &passPV);
  m_tree->SetBranchAddress("passDetErr", &passDetErr);
  m_tree->SetBranchAddress("passJetCleanLoose", &passJetCleanLoose);
  m_tree->SetBranchAddress("passJetCleanTight", &passJetCleanTight);
  m_tree->SetBranchAddress("n_jet",&n_jet);
  m_tree->SetBranchAddress("n_el",&n_el);
  m_tree->SetBranchAddress("n_mu",&n_mu);
  m_tree->SetBranchAddress("jj_mass",&jj_mass);
  m_tree->SetBranchAddress("jj_deta",&jj_deta);
  m_tree->SetBranchAddress("jj_dphi",&jj_dphi);
  m_tree->SetBranchAddress("met_tst_j1_dphi",&met_tst_j1_dphi);
  m_tree->SetBranchAddress("met_tst_j2_dphi",&met_tst_j2_dphi);
  m_tree->SetBranchAddress("met_tst_nolep_j1_dphi",&met_tst_nolep_j1_dphi);
  m_tree->SetBranchAddress("met_tst_nolep_j2_dphi",&met_tst_nolep_j2_dphi);
  m_tree->SetBranchAddress("met_tst_et",&met_tst_et);
  m_tree->SetBranchAddress("met_cst_jet",&met_cst_jet);
  m_tree->SetBranchAddress("met_tst_nolep_et",&met_tst_nolep_et);
  m_tree->SetBranchAddress("met_tst_phi",&met_tst_phi);
  m_tree->SetBranchAddress("met_tst_nolep_phi",&met_tst_nolep_phi);
  m_tree->SetBranchAddress("mu_charge",&mu_charge);//, &b_mu_charge);
  m_tree->SetBranchAddress("mu_pt",&mu_pt);//, &b_mu_pt);
  m_tree->SetBranchAddress("mu_phi",&mu_phi);//, &b_mu_phi);
  m_tree->SetBranchAddress("el_charge",&el_charge);
  m_tree->SetBranchAddress("el_pt",&el_pt);
  m_tree->SetBranchAddress("el_phi",&el_phi);
  m_tree->SetBranchAddress("mu_eta",&mu_eta);
  m_tree->SetBranchAddress("el_eta",&el_eta);
  m_tree->SetBranchAddress("jet_pt",&jet_pt);
  m_tree->SetBranchAddress("jet_phi",&jet_phi);
  m_tree->SetBranchAddress("jet_eta",&jet_eta);
  m_tree->SetBranchAddress("jet_jvt",&jet_jvt);
  m_tree->SetBranchAddress("jet_timing",&jet_timing);

  return StatusCode::SUCCESS;
}

