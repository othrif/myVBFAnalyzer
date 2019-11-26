
#include <TSystem.h>
#include <TProof.h>
#include <TProofLog.h>
#include <THashList.h>
#include "TStopwatch.h"

void procAnalyzer(TString inputDir="/nfs/dust/atlas/user/othrif/samples/MicroNtuples/v35Truth/", TString outputDir="/nfs/dust/atlas/user/othrif/scratch/myPP/latest/processed", TString process="W_EWK") {

  TStopwatch p;
  p.Start();

  TChain * chain;
  TString options;

  std::cout << "\nProcessing " << process << "..." << std::endl;
  chain = new TChain("", "");
  chain->Add(inputDir+"/"+process+".root/"+process+"Nominal");
  options = TString::Format("%lld", chain->GetEntries())+","+outputDir+","+process;
  chain->Process("truthAnalyzer.C+",options);
  delete chain;
  std::cout << "Done processing " << process << ".\n" << std::endl;

  p.Stop();
  p.Print();

}
