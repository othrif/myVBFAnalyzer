#include "./VJetsUncertaintyTool.cxx"

#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH2.h>
#include <TLegend.h>

void testVJetsUncertaintyTool()
{

   std::cout << "Hello!" << std::endl;

   const Bool_t ph_dyn_iso = true;
   bool smooth = false;
   TString suffix = "_smooth_mc16a_mergePDF";
   if(!smooth)
      suffix = "_nosmooth_mc16a_mergePDF";
   VJetsUncertaintyTool *vjTool = new VJetsUncertaintyTool();

   vjTool->setInputFileName("./theoretical_corrections.root");
   vjTool->applyEWCorrection(true);
   vjTool->applyQCDCorrection(true);
   vjTool->smoothQCDCorrection(smooth);
   vjTool->mergePDF(true);
   vjTool->applyDynamicIsolation(ph_dyn_iso);
   vjTool->initialize();

   Bool_t drawPDFsys = false;
   if (drawPDFsys)
     suffix += "_PDFsys";

   //const std::vector<TString> variations = vjTool->getAllVariationNames();
   const std::vector<TString> variations = {"Nominal",
"vjets_d1kappa_EW_High",
"vjets_d1kappa_EW_Low",
"vjets_d2kappa_EW_High",
"vjets_d2kappa_EW_Low",
"vjets_d3kappa_EW_High",
"vjets_d3kappa_EW_Low",
"vjets_d1K_NNLO_High",
"vjets_d1K_NNLO_Low",
"vjets_d2K_NNLO_High",
"vjets_d2K_NNLO_Low",
"vjets_d3K_NNLO_High",
"vjets_d3K_NNLO_Low",
"vjets_dK_NNLO_mix_High",
"vjets_dK_NNLO_mix_Low",
"vjets_dK_PDF_High",
"vjets_dK_PDF_Low"};

   for(auto var:variations)
      std::cout << var << std::endl;
   std::vector<TString> processes = {
     //     "mmj",
     //     "mvj",
     "eej",
     "evj",
    "vvj",
     //     "aj"
   };
   std::vector<int> channels = {
     364100, // Zee
     364156, // Wenu
     364142, // Znunu
     //     364543  // photon
   };

      std::vector<int> colors = {1, 6, 6, 9, 9, 14, 14, 2, 2, 3, 3, 4, 4, 28, 28, 46, 46};
      std::vector<int> styles = {1, 1, 7, 1, 7,  1,  7, 1, 7, 1, 7, 1, 7,  1,  7,  1,  7};

   TH2 *hDummy = new TH2F("hDummy", "", 200, 0, 2000, 2000, 0., 2.);
   hDummy->SetStats(false);

   for (unsigned int iP = 0; iP < processes.size(); iP++) {
      TString process = processes[iP];
      int channel = channels[iP];

      double ymin = 0.7;
      double ymax = 1.2;
      //      if (process == "aj") {
      //	ymin = 0.5;
      //	ymax = 1.2;
      //      }

      TString cname = "C_" + process;
      TCanvas *C = new TCanvas(cname, cname, 700, 600);
      C->Range(0, 0, 1, 1);

      TPad *pad_up = new TPad(cname + "_up", cname + "_up", 0, 0.3, 1, 1);
      TPad *pad_down = new TPad(cname + "_down", cname + "_down", 0, 0, 1, 0.3);

      pad_up->SetBottomMargin(0.01);
      pad_up->Draw();
      C->cd();
      //      pad_down->Range(0, 0, 1, 1);
      pad_down->SetTopMargin(0);
      pad_down->SetBottomMargin(0.4);
      pad_down->Draw();

      TGraph *gNom;

      TLegend *L = new TLegend(0.5, 0.5, 0.85, 0.9);
      L->SetFillColor(kWhite);
      L->SetBorderSize(0);

      Bool_t addPDFLeg = false;

      Int_t color = 1;

      for (unsigned int iV = 0; iV < variations.size(); iV++) {

         TString variation = variations[iV];

	 if ((!drawPDFsys && variation.Contains("PDF")) ||
	     (drawPDFsys && !variation.Contains("PDF") && !variation.Contains("Nominal"))) continue;
         //      if (variation.Contains("QCDSmoothing")) continue;

         TGraph *g = new TGraph();
         if (iV == 0) gNom = g;
         TGraph *ratio = new TGraph();

         for (double pTV = 30; pTV <= 2000; pTV += 10) {

            double corr = vjTool->getCorrection(channel, pTV, variation);

            int p = g->GetN();
            g->SetPoint(p, pTV, corr);
            ratio->SetPoint(p, pTV, corr / gNom->GetY()[p]);

//            std::cout << channel << " - " << pTV << " GeV - " << variation << " - " << corr << std::endl;
         }

         pad_up->cd();

         TH2 *h;
         if (iV == 0) {
            h = (TH2*)hDummy->DrawClone();
	         h->GetYaxis()->SetRangeUser(ymin, ymax);
            h->GetXaxis()->SetTitle("pT(V) [GeV]");
            h->GetYaxis()->SetTitle("Correction factor");
         }


	   if (variation.Contains("PDF") && addPDFLeg) {
	     addPDFLeg = true;
	   }

         g->SetLineWidth(2);
         g->SetLineColor(color);
	 //	 if (variation.Contains("PDF"))
	 //	   g->SetLineColor(kGray);
         g->SetLineStyle(1);
	          g->SetLineColor(colors[iV]);
	          g->SetLineStyle(styles[iV]);

         g->Draw("L");

	 C->cd();

         pad_down->cd();
	 //         pad_down->SetGrid();

         if (iV == 0) {
            h = (TH2*)hDummy->DrawClone();
	    h->GetYaxis()->SetTitleSize(0.12);
	    h->GetYaxis()->SetTitleOffset(0.55);
	    h->GetYaxis()->SetNdivisions(505);
	    h->GetYaxis()->SetLabelOffset(0.01);
	    h->GetYaxis()->SetLabelSize(0.12);
	    h->GetXaxis()->SetTitleSize(0.12);
	    h->GetXaxis()->SetLabelOffset(0.015);
	    h->GetXaxis()->SetLabelSize(0.12);
	    h->GetYaxis()->SetRangeUser(0.91, 1.09);
            h->GetYaxis()->SetTitle("Uncertainty");
            h->GetXaxis()->SetTitle("pT(V) [GeV]");
         }

         ratio->SetLineWidth(2);
         ratio->SetLineColor(color);
         ratio->SetLineColor(colors[iV]);
	 if (variation.Contains("PDF"))
	   ratio->SetLineColor(kGray);
         ratio->SetLineStyle(1);
	 //         g->SetLineColor(colors[iV]);
	 //         g->SetLineStyle(styles[iV]);

         ratio->Draw("L");

	 pad_up->cd();
	 if (iV % 2 == 0) {
	   color++;
	   if(color == 10) color++;
	   if (!variation.Contains("PDF"))// ||  !addPDFLeg)
	     L->AddEntry(g, variation.ReplaceAll("_Low", ""), "l");
	 }

      }

      pad_up->cd();
      gNom->Draw("Lsame");
      /*
      TF1 *fit = vjTool->getFitFunction(process);
      fit->SetLineColor(2);
      fit->SetLineStyle(7);
      fit->Draw("sames");
      L->AddEntry(fit, "Linear fit in [250, 1200]", "l");

      TF1 *fit0up = (TF1*)fit->Clone(fit->GetName()+TString("0up"));
      fit0up->SetParameter(0, fit->GetParameter(0) + fit->GetParError(0));
      fit0up->SetLineColor(2);
      //fit0up->Draw("sames");
      TF1 *fit0dn = (TF1*)fit->Clone(fit->GetName()+TString("0dn"));
      fit0dn->SetParameter(0, fit->GetParameter(0) - fit->GetParError(0));
      fit0dn->SetLineColor(2);
      //fit0dn->Draw("sames");

      TF1 *fit1up = (TF1*)fit->Clone(fit->GetName()+TString("1up"));
      fit1up->SetParameter(1, fit->GetParameter(1) + fit->GetParError(1));
      fit1up->SetLineColor(4);
      //fit1up->Draw("sames");
      TF1 *fit1dn = (TF1*)fit->Clone(fit->GetName()+TString("1dn"));
      fit1dn->SetParameter(1, fit->GetParameter(1) - fit->GetParError(1));
      fit1dn->SetLineColor(4);
      //    fit1dn->Draw("sames");

      TF1 *fitup = new TF1(fit->GetName()+TString("up"), "(x<1000?[0]+[1]*x:[2]) + TMath::Sqrt( [3]*[3] + [4]*[4]*x*x )",
         0, 2000);
      fitup->SetParameter(0, fit->GetParameter(0));
      fitup->SetParameter(1, fit->GetParameter(1));
      fitup->SetParameter(2, fit->GetParameter(2));
      fitup->SetParameter(3, fit->GetParError(0));
      fitup->SetParameter(4, fit->GetParError(1));
      fitup->SetLineColor(6);
      fitup->Draw("sames");

      TF1 *fitdn = new TF1(fit->GetName()+TString("dn"), "(x<1000?[0]+[1]*x:[2]) - TMath::Sqrt( [3]*[3] + [4]*[4]*x*x )",
         0, 2000);
      fitdn->SetParameter(0, fit->GetParameter(0));
      fitdn->SetParameter(1, fit->GetParameter(1));
      fitdn->SetParameter(2, fit->GetParameter(2));
      fitdn->SetParameter(3, fit->GetParError(0));
      fitdn->SetParameter(4, fit->GetParError(1));
      fitdn->SetLineColor(6);
      fitdn->Draw("sames");
      */

      L->DrawClone();
      TString suffix_to_use = suffix;
      if (ph_dyn_iso && process == "aj") suffix_to_use += "_dyn_iso";
      C->SaveAs("img/" + cname + suffix_to_use + ".pdf");
//      C->SaveAs("img/" + cname + suffix_to_use + ".C");
   }

   //  delete vjTool;
}
