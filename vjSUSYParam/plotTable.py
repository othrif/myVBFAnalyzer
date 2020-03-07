# used for ckkw and qsf

#################### Global settings
import math
import sys
import ROOT
import imp
import array
from ROOT import *
import AtlasStyle
gStyle.SetPaintTextFormat('1.3f')
gStyle.SetLineStyleString(11,"27 15")

colors = [kBlack, kRed+2, kBlue]
styles = [20,21,22,23]

bins_mjj = ['800', '1000', '1500', '2000', '3500']
histobins = [800, 1000, 1500, 2000, 3500, 5000]


def makePlots(unc,suffix):
  # plot the uncertainty vs mjj bins for each sample in each region do this for a given NP

  name = suffix
  c = TCanvas(name, name, 600, 600)

  legend = TLegend(0.34866,0.810435,0.748328,0.895652,'')

  bins = array.array('d', histobins)
  bins_n = len(histobins)-1

  namehisto =  suffix
  histo = TH1F(namehisto, namehisto, bins_n, bins)

  for i in range(bins_n):
      histo.SetBinContent(i+1, unc[i]-1)
  #histo.Draw()
  #raw_input("Press Enter to continue...")
  j=0
  histo.SetLineWidth(2)
  histo.SetLineColor(colors[j])
  histo.SetMarkerColor(colors[j])
  histo.SetMarkerStyle(styles[j])
  histo.SetTitle(suffix)

  histo.GetXaxis().SetTitle('M_{jj} [GeV]')
  histo.GetXaxis().SetNdivisions(505, True)
  histo.GetYaxis().SetTitle('Relative uncertainty')
  histo.GetYaxis().SetRangeUser(0.0, 0.1)
  #histo.Draw('P')
  histo.Draw('PhistL')
  c.SetGridy()
  legend.AddEntry(histo.GetName(),histo.GetName(), 'LP')
  legend.Draw('same')
  #raw_input("Press Enter to continue...")
  c.SaveAs('systPlots/new/'+suffix+'.pdf')


if __name__ == "__main__":

    print "starting to process...."
    sr_qsf_Z_strong=[1.0623,1.0637,1.0586,1.0614,1.0662,1.0569,1.0577,1.0574,1.056,1.0516,1.0438]
    sr_qsf_W_strong=[1.0572,1.0599,1.0587,1.0537,1.0734,1.0588,1.0611,1.0647,1.0543,1.0499,1.0431]
    sr_ckkw_Z_strong =[1.0479,1.0506,1.046,1.0525,1.0396,1.0533,1.0553,1.057,1.0577,1.0602,1.04]
    sr_ckkw_W_strong =[1.0358,1.036,1.042,1.0367,1.0433,1.042,1.0457,1.0521,1.0477,1.0484,1.0301]

    cr_qsf_Z_strong =[1.0813,1.0743,1.0696,1.0759,1.09,1.0711,1.0659,1.0605,1.0646,1.0572,1.0499]
    cr_ckkw_Z_strong =[1.0544,1.055,1.053,1.0545,1.0423,1.0583,1.0623,1.0608,1.0635,1.0659,1.0464]

    cr_qsf_W_strong =[1.0694,1.065,1.0703,1.0736,1.0408,1.0627,1.0563,1.0516,1.0532,1.0589,1.0438]
    cr_ckkw_W_strong =[1.0386,1.0397,1.0387,1.0392,1.0145,1.0454,1.0463,1.048,1.0503,1.0473,1.0318]

    unc = cr_ckkw_W_strong[6:]
    print unc
    makePlots(unc,"ckkw_W_strong_CRW_mc16ade")



