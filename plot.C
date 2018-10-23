void plot(){

    //TFile f("outFile.root");
    TString result = "../results/131018/";
    TFile f(result+"jetClass.root");
    TH1F* h1 = (TH1F*) f.Get("jetClass_j80j50eta48"); h1->SetDirectory(0);
    TH1F* h2 = (TH1F*) f.Get("jetClass_j80j50eta2"); h2->SetDirectory(0);
    TH1F* h3 = (TH1F*) f.Get("jetClass_j40j40eta48"); h3->SetDirectory(0);
    TH1F* h4 = (TH1F*) f.Get("jetClass_j40j40eta2"); h4->SetDirectory(0);
    TH1F* hEff1 = (TH1F*) f.Get("jetClassEff_j80j50eta48"); hEff1->SetDirectory(0);
    TH1F* hEff2 = (TH1F*) f.Get("jetClassEff_j80j50eta2"); hEff2->SetDirectory(0);
    TH1F* hEff3 = (TH1F*) f.Get("jetClassEff_j40j40eta48"); hEff3->SetDirectory(0);
    TH1F* hEff4 = (TH1F*) f.Get("jetClassEff_j40j40eta2"); hEff4->SetDirectory(0);

    TCanvas *c = new TCanvas("c","c");
    c->SetLogy();
    h1->SetLineColor(kRed); h1->SetLineWidth(2);
    h2->SetLineColor(kBlue); h2->SetLineWidth(2);
    h3->SetLineColor(kViolet); h3->SetLineWidth(2);
    h4->SetLineColor(kOrange); h4->SetLineWidth(2);
    h1->SetMaximum(h1->GetMaximum()*1.2);
    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");
    h4->Draw("same");
    TLegend *l = new TLegend(0.63,0.75,0.9,0.93);
    l->SetHeader("Total yield","C");
    l->AddEntry(h1,"|#eta_{jj}|>4.8, j1>80, j2>50","l");
    l->AddEntry(h2,"|#eta_{jj}|>2, j1>80, j2>50","l");
    l->AddEntry(h3,"|#eta_{jj}|>4.8, j1>40, j2>40","l");
    l->AddEntry(h4,"|#eta_{jj}|>2, j1>40, j2>40","l");
    l->Draw("same");
    c->SaveAs(result+"jetClass.pdf");

    TCanvas *cEff = new TCanvas("cEff","cEff");
    hEff1->SetLineColor(kRed); hEff1->SetLineWidth(2);
    hEff2->SetLineColor(kBlue); hEff2->SetLineWidth(2);
    hEff3->SetLineColor(kViolet); hEff3->SetLineWidth(2);
    hEff4->SetLineColor(kOrange); hEff4->SetLineWidth(2);
    hEff1->SetMaximum(hEff1->GetMaximum()*1.5);
    hEff1->Draw();
    hEff2->Draw("same");
    hEff3->Draw("same");
    hEff4->Draw("same");
    TLegend *lEff = new TLegend(0.63,0.75,0.9,0.93);
    lEff->SetHeader("Efficiency","C");
    lEff->AddEntry(hEff1,"|#eta_{jj}|>4.8, j1>80, j2>50","l");
    lEff->AddEntry(hEff2,"|#eta_{jj}|>2, j1>80, j2>50","l");
    lEff->AddEntry(hEff3,"|#eta_{jj}|>4.8, j1>40, j2>40","l");
    lEff->AddEntry(hEff4,"|#eta_{jj}|>2, j1>40, j2>40","l");
    lEff->Draw("same");
    cEff->SaveAs(result+"jetClassEff.pdf");


}