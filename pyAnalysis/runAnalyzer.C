
#include <TSystem.h>
#include <TProof.h>
#include <TProofLog.h>
#include <THashList.h>
#include "TStopwatch.h"

{

  TStopwatch p;
  p.Start();
  TChain * chain = new TChain("", "");
  chain->Add("./input/VBFH125.root/VBFH125Nominal");

   //Processing
  TString entries = TString::Format("%lld", chain->GetEntries());
  chain->Process("truthAnalyzer.C",entries);

  p.Stop();
  p.Print();

}
