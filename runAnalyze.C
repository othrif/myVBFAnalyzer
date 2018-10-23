// TO DO: Run with PROOF

#include <TSystem.h>
#include <TProof.h>
#include <TProofLog.h>
#include <THashList.h>
#include "TStopwatch.h"

{

  TStopwatch p;
  p.Start();
  TChain * chain = new TChain("", "");
  //chain->Add("/Users/othmanerifki/vbf/samples/v11/131018/All/VBFH125Nominal308276.root/VBFH125Nominal");
  chain->Add("./input/processed_Z_strong_rel21.root/nominal");

   //Processing
  TString entries = TString::Format("%lld", chain->GetEntries());
  chain->Process("analyze.C",entries);

  p.Stop();
  p.Print();

}

