void plot_env_stat(TString folder= "theoVariation_300919"){

  //  SetAtlasStyle();
  gStyle->SetMarkerSize(0.9);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetTextSize(0.04);
  gROOT->ForceStyle();
  TH1::AddDirectory(kFALSE);


  gSystem->Exec("mkdir -p output/"+folder+"/plots/env/");

  double max_def = 2;
  double min_def = 0.6;

  TString version = "rel20";

  TString files[] = {"reweight_Z_strong_SR"+version,"reweight_Z_strong_CRZ"+version,"reweight_W_strong_SR"+version,"reweight_W_strong_CRW"+version};
  int numfiles = 4;

  TString var[] = {"envelope"};
  int numvars =1;

  double tf[3] = {0.1,0.2,0.15};

  for (int ifile =0; ifile< numfiles; ifile++)
    for (int jvar =0; jvar< numvars; jvar++){

      TString name_process = files[ifile];
      name_process.ReplaceAll("/","_");
      name_process.ReplaceAll("reweight_","");
      TString file_in = "output/"+folder+"/"+files[ifile]+".root";

      TFile *fIn = new TFile( file_in );

      TString namefile = files[ifile];
      namefile.ReplaceAll("reweight","variedYields");
      TString file_inError = "output/"+folder+"/"+namefile+".root";
      TFile *fInError = new TFile( file_inError );

/*      TH1F  *h_Error = (TH1F*)fInError->Get( "h_nominal" );
      TAxis *axis = h_Error->GetXaxis();
      double err[3],bin[3];
      bin[0] = h_Error->IntegralAndError(axis->FindBin(1),axis->FindBin(1.5),err[0]);
      bin[1] = h_Error->IntegralAndError(axis->FindBin(1.5),axis->FindBin(2),err[1]);
      bin[2] = h_Error->IntegralAndError(axis->FindBin(2),h_Error->GetNbinsX()+1,err[2]);*/
//   cout << name_process << " bin0 = " << bin[0] << " +/- " << err[0] << " >> " << err[0]/bin[0] << endl;
//    cout << name_process << " bin1 = " << bin[1] << " +/- " << err[1] << " >> " << err[1]/bin[1] << endl;
//    cout << name_process << " bin2 = " << bin[2] << " +/- " << err[2] << " >> " << err[2]/bin[2] << endl;

      TH1F  *h_Nom   = (TH1F*)fIn->Get( var[jvar]+"_up" );
      TH1F  *h_Up   = (TH1F*)fIn->Get( var[jvar]+"_up" );
      TH1F  *h_Down = (TH1F*)fIn->Get( var[jvar]+"_down" );

      h_Nom->SetLineColor(kBlue+1);
      h_Up->SetLineColor(kBlue+1);
      h_Up->SetMarkerColor(kBlue+1);
      h_Down->SetLineColor(kBlue+1);
      h_Down->SetMarkerColor(kBlue+1);
      h_Down->SetLineStyle(7);

      h_Nom->GetXaxis()->SetLabelOffset(0.01);
      h_Nom->SetTitle("");
      h_Nom->GetYaxis()->SetTitle("Ratio to Nominal");
      h_Nom->SetMinimum(min_def);
      h_Nom->SetMaximum(max_def);

      const int num = 3;
      TString Ax_SR[num] = {"1 TeV < m_{jj} < 1.5 TeV","1.5 TeV < m_{jj} < 2 TeV", "m_{jj} > 2 TeV"};
      for (int i=0; i<num; i++) {
        h_Nom->SetBinContent(i+1, 1);
        //h_Nom->SetBinError(i+1, err[i]/bin[i]);
        h_Nom->SetBinError(i+1, 0);
        h_Nom->GetXaxis()->SetBinLabel(i+1,Ax_SR[i]);
      }

      TCanvas *c = new TCanvas( Form("SystVar%d%d",ifile,jvar) , "SystVar" );
      TPad* p1 = new TPad("p1","p1",0.0,0.25,1.0,1.0,-22);
      p1->SetBottomMargin(0.02);
      p1->Draw();

      h_Nom->Draw("E");
      h_Down->Draw("HIST SAME E");
      h_Up->Draw("HIST SAME E");
      h_Nom->Draw("AXIS same");

      TString bkg = name_process;
      if (bkg.Contains("Z"))
        bkg = "Z";
      TLegend *legend=new TLegend(0.69,0.69,0.85,0.94);
      TString tmp_name = name_process;
      legend->SetHeader(tmp_name.ReplaceAll("_"," "));
      legend->SetTextFont(62);
      legend->SetTextSize(0.04);
      legend->AddEntry(h_Up, var[jvar]+" up","lp");
      legend->AddEntry(h_Down, var[jvar]+" down","lp");
      legend->Draw();

      TF1 *line = new TF1("line","1",-100000,100000);
      line->SetLineColor(kBlack);
      line->SetLineWidth(1);
      line->Draw("same");

    // Write
      c->Print( "output/"+folder+"/plots/env/"+name_process+".pdf" );

    }
  }
