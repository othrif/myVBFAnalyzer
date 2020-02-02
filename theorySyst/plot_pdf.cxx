// Plot all the pdf variations
// root plot_pdf.cxx
// Change path
void plot_pdf(TString folder= "theoVariation_171019"){

  TString procV = "strong"; // strong, EWK
  TString region = "Njet"; // PhiHigh, PhiLow, Njet

  //  SetAtlasStyle();
  gStyle->SetMarkerSize(0.9);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetTextSize(0.04);
  gROOT->ForceStyle();
  TH1::AddDirectory(kFALSE);

  gSystem->Exec("mkdir -p output/"+folder+"/plots/env/");

  const int num = 5;
  TString Ax_SR[num] = {"0.8 TeV < m_{jj} < 1 TeV","1 TeV < m_{jj} < 1.5 TeV","1.5 TeV < m_{jj} < 2 TeV", "2 < m_{jj} < 3.5 TeV", "m_{jj} > 3.5 TeV"};
  int numfiles;

  double max_def = 2.5;
  double min_def = 0.5;

 TString files[] = {"Z_"+procV+"_SR"+region,"Z_"+procV+"_CRZ"+region,"W_"+procV+"_SR"+region,"W_"+procV+"_CRW"+region};
  numfiles = 4;

/*
region = "WCR";
  TString files[] = {"Wenu","Wenu2jets"};
  numfiles = 2;*/
/*
  region = "ZCR";
  TString files[] = {"Zee","Zee2jets"};
  numfiles = 2;*/


  for (int ifile =0; ifile< numfiles; ifile++){
    std::cout << files[ifile] << std::endl;

    TString file_in = "output/"+folder+"/reweight_"+files[ifile]+".root";
    TString file_out = "output/"+folder+"/plots/env/output.root";
    TString Legend = "Uncertainties";


    TFile *fIn = new TFile( file_in );
    TFile *fFinal = new TFile( file_out ,"recreate");

    TH1F  *h_Nom   = (TH1F*)fIn->Get( "pdf_up" );
    TH1F  *h_FUp   = (TH1F*)fIn->Get( "pdf_up" );
    TH1F  *h_FDown = (TH1F*)fIn->Get( "pdf_down" );
    TH1F  *h_RUp   = (TH1F*)fIn->Get( "renorm_up" );
    TH1F  *h_RDown = (TH1F*)fIn->Get( "renorm_down" );
    TH1F  *h_QUp   = (TH1F*)fIn->Get( "both_up" );
    TH1F  *h_QDown = (TH1F*)fIn->Get( "both_down" );
    TH1F  *h_EnvUp   = (TH1F*)fIn->Get( "envelope_up" );
    TH1F  *h_EnvDown = (TH1F*)fIn->Get( "envelope_down" );

    h_Nom->SetLineColor(kBlack);
    h_FUp->SetLineColor(kBlue+1);
    h_FUp->SetMarkerColor(kBlue+1);
    h_FDown->SetLineColor(kBlue+1);
    h_FDown->SetMarkerColor(kBlue+1);
    h_FDown->SetLineStyle(7);

    h_Nom->GetXaxis()->SetLabelOffset(0.01);
    h_Nom->SetTitle("");
    h_Nom->GetYaxis()->SetTitle("Ratio to Nominal");
  //  h_Nom->SetMaximum( std::max(h_QUp->GetMaximum(),
  //			      h_FUp->GetMaximum() )*1.2 );
    h_Nom->SetMinimum(min_def);
    h_Nom->SetMaximum(max_def);



  for (int i=1; i<=num; i++) {
    h_Nom->SetBinContent(i, 0);
    h_Nom->SetBinError(i, 0);
    h_Nom->GetXaxis()->SetBinLabel(i,Ax_SR[i-1]);
  }



  TCanvas *c = new TCanvas( Form("SystVar%d",ifile) , "SystVar" );
  TPad* p1 = new TPad("p1","p1",0.0,0.25,1.0,1.0,-22);
  p1->SetBottomMargin(0.02);
  p1->Draw();

  h_Nom->Draw();

  TH1F* envHi =  new TH1F("envhi", "envhi", num,1000 , 2500);
  TH1F* envLo =  new TH1F("envhi", "envhi", num,1000 , 2500);
  for (int j = 1; j <= num; ++j) {
    double yHi = h_EnvDown->GetBinContent(j); //cout << envHi->GetBinContent(j) << " -> " << yHi << endl;
    double yLow = h_EnvUp->GetBinContent(j); //cout << envLo->GetBinContent(j) << " -> " << yLow << endl;
    envHi->SetBinContent(j, yHi);
    envLo->SetBinContent(j, yLow);
  }

  TH1F* quadUp =  new TH1F("quadUp", "quadUp", num,1000 , 2500);
  TH1F* quadLo =  new TH1F("quadLo", "quadLo", num,1000 , 2500);
  for (int j = 1; j <= num; ++j) {
    double yU1 = h_RUp->GetBinContent(j)-1; //cout << "Up1 = " << yU1 << endl;
    double yU2 = h_FUp->GetBinContent(j)-1; //cout << "Up2 = " << yU2 << endl;
    double yL1 = h_RDown->GetBinContent(j)-1;
    double yL2 = h_FDown->GetBinContent(j)-1;
     quadUp->SetBinContent(j, 1-TMath::Sqrt(yU1*yU1+yU2*yU2)); //cout << "Up^2 = " << TMath::Sqrt(yU1*yU1+yU2*yU2) << endl;
     quadLo->SetBinContent(j, TMath::Sqrt(yL1*yL1+yL2*yL2)+1); //cout << "Dn = " << TMath::Sqrt(yL1*yL1+yL2*yL2) << endl;
   }
   quadUp->SetLineColor(kYellow+2);
   quadUp->SetMarkerColor(kYellow+2);
   quadLo->SetLineColor(kYellow+2);
   quadLo->SetMarkerColor(kYellow+2);
   quadLo->SetLineStyle(7);


   envHi->SetLineColor(kGray);
  //envHi->SetFillColor(kGray);
   //envHi->Draw("hist same");

   h_FDown->Draw("HIST  SAME");
   //h_RDown->Draw("HIST  SAME");
   //h_QDown->Draw("HIST  SAME");

   std::cout << "test1" << std::endl;
   TH1F* whitearea =  new TH1F("whitearea", "whitearea", num,1000 , 2500);;
   for (int j = 1; j <= num; ++j) {
     whitearea->SetBinContent(j, h_EnvUp->GetBinContent(j));
     cout << whitearea->GetBinContent(j)<< endl;
   }
   std::cout << "test2" << std::endl;
   whitearea->SetFillColorAlpha(kWhite, 0);
   whitearea->SetFillColor(kWhite);
   whitearea->SetLineColor(kGray);
//whitearea->Draw("hist same");
   //h_QUp->Draw("HIST  SAME");
   h_FUp->Draw("HIST  SAME");
   //h_RUp->Draw("HIST  SAME");
   //quadUp->Draw("HIST  SAME");
   //quadLo->Draw("HIST  SAME");

   h_Nom->Draw("AXIS same");
   std::cout << "test3" << std::endl;
  //  ATLASLabel(0.20,0.87,true);

   //  TLegend *legend=new TLegend(0.70,0.30,0.90,0.85);
   TLegend *legend=new TLegend(0.67,0.75,0.88,0.89);
   legend->SetTextFont(62);
   legend->SetTextSize(0.04);
    legend->SetHeader(files[ifile]);
  //  legend->AddEntry(h_Nom, "Nominal","lp");
   legend->AddEntry(h_FUp, "pdf up","lp");
   legend->AddEntry(h_FDown, "pdf dn","lp");
   legend->Draw();

   std::cout << "test4" << std::endl;
   TF1 *line = new TF1("line","1",-100000,100000);
   line->SetLineColor(kBlack);
   line->SetLineWidth(1);
   line->Draw("same");
   std::cout << "test5" << std::endl;
/*
 TLatex *xlabel = new TLatex();
 xlabel-> SetNDC();
 xlabel -> SetTextFont(1);
 xlabel -> SetTextColor(1);
 xlabel -> SetTextSize(0.03);
 xlabel -> SetTextAlign(22);
 xlabel -> SetTextAngle(0);
 xlabel -> DrawText(0.26, 0.88, files[ifile]+", "+region);
std::cout << "test6" << std::endl;
*/
  // Write
   c->Print( "/Users/othmanerifki/vbf/systematics/theoUnc_7bin/output/"+folder+"/plots/pdf/"+files[ifile]+"_"+region+".pdf");
  //c->Write();
  //fFinal->Close();

 }
}
