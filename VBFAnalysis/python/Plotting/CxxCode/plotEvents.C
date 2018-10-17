#define plotEvents_cxx
#include "plotEvents.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <iostream>


#include <TLorentzVector.h>
#include <TMath.h>

TString getProcess(Int_t rNumber){


//TODO still some events in Others. identify them.
//mainMC = OrderedDict([
//    ('signalAlt', [308275] + range(308277,308283 + 1)),
    if(rNumber==308071 || rNumber==308072) return "VH";
    if((rNumber>=363355 && rNumber<=363360) || rNumber==363489) return "VV";
    if(rNumber==308276 || rNumber==308567 || rNumber==308284) return "signal"; // VBFH125_ZZ4nu_MET125, VBFH125_ZZ4nu_125MET, gH125_ZZ4nu_MET75
    if(rNumber>=308092 && rNumber<=308094 ) return "ZEWK";
    if(rNumber==308095) return "ZnunuEWK";
    if(rNumber>=308096 && rNumber<=308098 ) return "WEWK";
    if(rNumber>=364170 && rNumber<=364183 ) return "Wenu";
    if(rNumber>=364156 && rNumber<=364169 ) return "Wmunu";
    if(rNumber>=364184 && rNumber<=364197 ) return "Wtaunu";
    if(rNumber>=364114 && rNumber<=364127 ) return "Zee";
    if(rNumber>=364100 && rNumber<=364113 ) return "Zmumu";
    if(rNumber>=364128 && rNumber<=364141 ) return "Ztautau";
    if(rNumber>=364142 && rNumber<=364155 ) return "Znunu";
    if(rNumber>=361020 && rNumber<=361032 ) return "QCDw";
    if(rNumber==410470 || rNumber==410472 || rNumber==410011 || rNumber==410012 || rNumber==410013 || rNumber==410014 || rNumber==410025 || rNumber==410026) return "top";
    if(rNumber>=266905 && rNumber<=284484 ) return "data15";
    if(rNumber>=296939 && rNumber<=311481 ) return "data16";
    if(rNumber>=324320 && rNumber<=341649 ) return "data17";
    //cout << "runNumber could not be identified!  " << rNumber << endl;
    return "Others";

//altMC = OrderedDict([
//    ('ZllVBF',    [345101,345102,345099,345100]),
//    ('ZllDY',     range(364198, 364215+1)),
//    ('topAlt',    [410471]),
//    ('VVrare',    [363494,364250,364254,364255] ),
//    ('VVV',       range(364242,364249 + 1)),
//    ('QCDunw',    range(426001,426009 + 1))
//    ])
}



void plotEvents::Loop(TString sys)
{
//   In a ROOT session, you can do:
//      root> .L plotEvents.C
//      root> plotEvents t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch


    //Defining output file
    fout=new TFile(outFile, "UPDATE");
    TString systematic;


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

       if (jentry==1) cout << "Identified process for the first event (of "<<nentries<<"): " << runNumber << ", " << getProcess(runNumber) << endl;


       process=getProcess(runNumber);
       if (process=="data17") continue; //FIXME REMOVE THIS. Right now hack for blinding data17
       plotEvents::cutflowHists(); //Fills the cutflow hists. quite time intesive.


       if(!passJetCleanTight) continue;
	   if(!Cut(jentry)) continue;


           //TODO make the lines below reduandent with cutflowHists()

        // Save event in the right histograms. Region, Systematic, Process
        if(n_el==0 && n_mu==0 && trigger_met) plotEvents::fillHists("sr", "nn");
        if(n_el==1 && n_mu==0 && trigger_lep && el1_pt>30.e3 && met_significance>4.){
            plotEvents::fillHists("wcr", "e");
            plotEvents::fillHists("wcr", "l");
            if(el1_charge==-1) plotEvents::fillHists("wcr", "en");
            if(el1_charge==1) plotEvents::fillHists("wcr", "ep");
        }
        if(n_el==0 && n_mu==1 && trigger_lep && mu1_pt>30.e3){
            plotEvents::fillHists("wcr", "u");
            plotEvents::fillHists("wcr", "l");
            if(mu1_charge==-1) plotEvents::fillHists("wcr", "un");
            if(mu1_charge==1) plotEvents::fillHists("wcr", "up");
        }
        if(n_el==2 && n_mu==0 && trigger_lep && el1_pt>30.e3 && el2_pt>7.e3){
	   TLorentzVector e1,e2;
	   e1.SetPtEtaPhiM(el1_pt, el1_eta, el1_phi, 0.511);
	   e2.SetPtEtaPhiM(el2_pt, el2_eta, el2_phi, 0.511);
	   double mll=(e1+e2).M();
	   if(TMath::Abs(mll-91.2e3)<25.e3){
            plotEvents::fillHists("zcr", "ll");
            plotEvents::fillHists("zcr", "ee");
           }
        }
        if(n_el==0 && n_mu==2 && trigger_lep && mu1_pt>30.e3 && mu2_pt>7.e3){
	   TLorentzVector m1,m2;
	   m1.SetPtEtaPhiM(mu1_pt, mu1_eta, mu1_phi, 105.6);
	   m2.SetPtEtaPhiM(mu2_pt, mu2_eta, mu2_phi, 105.6);
	   double mll=(m1+m2).M();
	   if(TMath::Abs(mll-91.2e3)<25.e3) {
            plotEvents::fillHists("zcr", "ll");
            plotEvents::fillHists("zcr", "uu");
           }
        }
        // TODO what about the lowSig wcr?
   }

   fout->Write();
   fout->Close();
}

void runLoop(TTree* t, TString sys, double lumi, TString outFile){
    plotEvents obj(t, lumi, outFile, sys);
    obj.Loop(sys);
}
