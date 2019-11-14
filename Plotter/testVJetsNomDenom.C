TH1 *getHisto(TDirectory *fIn, TString hname)
{

   TH1 *h = 0;

   if (!fIn || fIn->IsZombie()) {
      return h;
   }

   TObject *obj = fIn->Get(hname);
   if (!obj) {
      std::cout << "Error: object of name " << hname << " was not found in file " << fIn->GetName() << std::endl;
      return h;
   }

   h = (TH1*)obj->Clone();

   return h;
}

void testVJetsNomDenom (TString correction = "pTV_LO") {

  TString path = "./theoretical_corrections.root";

  auto fIn = new TFile(path);
  std::map <TString, TH1*> hist;

  std::vector <TString> processes = {"eej", "evj", "vvj"};

  Int_t color = 1;

  TCanvas* c = new TCanvas();
  for (auto process: processes) {

//   TH1 *hSLO = getHisto(fIn, process + "_pTV_LO");
//   TH1 *hKNNLO = getHisto(fIn, process + "_pTV_K_NNLO");
   std::cout << process + "_" + correction << std::endl;
    hist[process] = getHisto(fIn, process + "_" + correction);
    //hist[process]->GetYaxis()->SetTitle(correction);
    hist[process]->GetYaxis()->SetTitle("Events (A.U.)");
    hist[process]->GetXaxis()->SetTitle("p_{T}^{V} [GeV]");
    hist[process]->GetXaxis()->SetRangeUser(30, 2000);
    hist[process]->SetLineColor(color);
    hist[process]->Draw("histsame");
    color++;

  }

  c->SetLogy();
  c->BuildLegend();
  c->SaveAs("img/comparison_" + correction + ".pdf");
}



