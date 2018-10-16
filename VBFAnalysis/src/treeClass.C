#define treeClass_cxx
#include "treeClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void treeClass::Loop(int bini)
{
//   In a ROOT session, you can do:
//      root> .L treeClass.C
//      root> treeClass t
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
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

	  init_CutMap(bini);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

	  if(runNumber>=324320 && runNumber<=341649 ) continue; //FIXME data 17 is ignored for now
	  if(!passJetCleanTight) continue;
	  if (!Cut()) continue;
	  fillHists(bini);


   }
}

void runLoop(TFile* outF,TString inputFileName, TString fname, TString syst, TString ud, int binLow=1, int binHigh=1, TString binFileName="output_info.txt", double lumi=36.1)
{

	if(fname=="data" && syst!="Nominal") return; // NOTE this is redundant. See makeHFinput.py

	TFile* inputF=new TFile(inputFileName);
	TString treeName=fname+syst+ud;
	if (syst=="Nominal") treeName=fname+syst;
	TTree* currentTree=(TTree*)inputF->Get(treeName);
	if (currentTree==NULL) 
	{
		cout << "Tree not found!!: " << treeName << " , in file: "<<inputFileName<<endl;
		return;
	}
	treeClass obj(currentTree, outF);
	obj.syst=syst;
	obj.ud=ud;
	if (ud=="__1up") obj.hl="High";
	if (ud=="__1down") obj.hl="Low";
	obj.fname=fname;
    obj.binLow=binLow;
    obj.binHigh=binHigh;
    obj.binFileName=binFileName;
	obj.lumi=lumi;
    for(int i=obj.binLow; i<=obj.binHigh; i++) obj.Loop(i);
}
