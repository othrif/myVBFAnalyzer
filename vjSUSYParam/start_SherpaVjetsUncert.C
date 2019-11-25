void start_SherpaVjetsUncert( TString suffix = "mc16d", int nentries = -1) {
 TChain * chain = new TChain("", "");

 TString directory = "/nfs/dust/atlas/user/othrif/scratch/myPP/latest/run_condor_211119/final_merged_v34";
 std::cout << "Start" << std::endl;
 chain->Add(directory + "_mc16a/Z_strong.root/Z_strongNominal");
 chain->Add(directory + "_mc16d/Z_strong.root/Z_strongNominal");
 chain->Add(directory + "_mc16e/Z_strong.root/Z_strongNominal");
 chain->Add(directory + "_mc16a/W_strong.root/W_strongNominal");
 chain->Add(directory + "_mc16d/W_strong.root/W_strongNominal");
 chain->Add(directory + "_mc16e/W_strong.root/W_strongNominal");
 if(nentries == -1)
    nentries = chain->GetEntries();
 chain->Process("MySelector.C",suffix,nentries);
 std::cout << "End" << std::endl;
}
