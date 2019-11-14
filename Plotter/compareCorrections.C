void compareCorrections (TString correction = "pTV_K_NNLO") {
  // pTV_LO, pTV_kappa_EW, pTV_K_NNLO

  TString path = "./theoretical_corrections.root";

  auto file = new TFile(path);
  std::map <TString, TH1F*> hist;

  std::vector <TString> processes = {"eej", "evj", "vvj"};

  Int_t color = 1;

  TCanvas* c = new TCanvas();
  for (auto process: processes) {

    hist[process] = (TH1F*)file->Get(process + "_" + correction);
    hist[process]->GetYaxis()->SetTitle(correction);
    hist[process]->GetXaxis()->SetTitle("p_{T}^{V} [GeV]");
    hist[process]->GetXaxis()->SetRangeUser(30, 2000);
    hist[process]->SetLineColor(color);
    hist[process]->Draw("histsame");

    color++;

  }

  //c->SetLogx();
  //c->SetLogy();
  c->BuildLegend();
  c->SaveAs("img/comparison_" + correction + ".pdf");
}



