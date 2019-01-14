
#include <TSystem.h>
#include <TProof.h>
#include <TProofLog.h>
#include <THashList.h>
#include "TStopwatch.h"

void runAnalyzer(TString inputDir="/Users/othmanerifki/vbf/input/truth_v18_090119/", TString outputDir="/Users/othmanerifki/vbf/myVBFAnalyzer/processed") {

  TStopwatch p;
  p.Start();

  TChain * chain;
  TString process,options;

  // VBF
  process="VBFH125";
  std::cout << "\nProcessing " << process << "..." << std::endl;
  chain = new TChain("", "");
  chain->Add(inputDir+"/"+process+".root/"+process+"Nominal");
  options = TString::Format("%lld", chain->GetEntries())+","+outputDir+","+process;
  chain->Process("truthAnalyzer.C+",options);
  delete chain;
  std::cout << "Done processing " << process << ".\n" << std::endl;

  // ggF
  process="ggFH125";
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
