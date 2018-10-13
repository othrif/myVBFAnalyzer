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
  TString directory = "/Users/othmanerifki/vbf/plot/v11Rui/";
  chain->Add("/Users/othmanerifki/vbf/relComp/input/raw_vbf_rel21.root/VBFH125Nominal");
//  chain->Add(directory + "data.root/dataNominal");

   //Processing
  TString entries = TString::Format("%lld", chain->GetEntries());
  chain->Process("analyze.C",entries);

  p.Stop();
  p.Print();

}

