// Plot the transfer factor theory uncertainty and compare two sets of uncertainties:
// 1 > Rel21
// 2 > Rel20

void plot_TF_unc_test(TString folder= "theoVariation_171019",TString procV = "EWK", TString region = "PhiLow"){

  using namespace TMath;

  //  SetAtlasStyle();
  gStyle->SetMarkerSize(0.9);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetTextSize(0.04);
  gROOT->ForceStyle();
  TH1::AddDirectory(kFALSE);

  gSystem->Exec("mkdir -p output/"+folder+"/plots/unc/");

  const int numbins = 5;
  const int numfiles = 4;
  TString Ax_SR[numbins] = {"0.8 TeV < m_{jj} < 1 TeV","1 TeV < m_{jj} < 1.5 TeV","1.5 TeV < m_{jj} < 2 TeV", "2 < m_{jj} < 3.5 TeV", "m_{jj} > 3.5 TeV"};

  double max_def = 10;
  double min_def = -10;

  TString files[] = {"Z_"+procV+"_SR"+region,"Z_"+procV+"_CRZ"+region,"W_"+procV+"_SR"+region,"W_"+procV+"_CRW"+region};
  TString legend_files[] = {"Z "+procV+" SR","Z "+procV+" CRZ","W "+procV+" SR","W "+procV+" CRW"};

  TFile *f1 = TFile::Open("output/"+folder+"/reweight_"+files[0]+".root");
  TH1F *h1; f1->GetObject("envelope_up", h1);
  //h1->Sumw2(1); //h1->SetDirectory(0);
  h1->SetMarkerColor(kBlue); h1->SetLineColor(kBlue);
  TFile *f2 = TFile::Open("output/"+folder+"/reweight_"+files[1]+".root");
  TH1F *h2; f2->GetObject("envelope_up", h2);
 // h2->Sumw2(1); //h2->SetDirectory(0);
  h2->SetMarkerColor(kGreen); h2->SetLineColor(kGreen);
  TH1F *h3 = ((TH1F*)(h1->Clone("h3")));
  h3->SetMarkerColor(kRed); h3->SetLineColor(kRed);
  h3->Divide(h2);
  TCanvas *c = new TCanvas("c", "c");
  auto rp = new TRatioPlot(h1, h2);
  rp->Draw();
  //rp->GetUpperPad()->cd();
  //h1->Draw("SAME");
  //rp->GetLowerPad()->cd();
  //h3->Draw("SAME");
  //h3->Print("all");
  c->cd(0);

}