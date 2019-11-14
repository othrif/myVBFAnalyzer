#ifndef VJETS_UNCERTAINTY_TOOL_H
#define VJETS_UNCERTAINTY_TOOL_H

#include <TString.h>
#include <map>
#include <vector>

class TH1;
class TF1;

class VJetsUncertaintyTool {

public:
  
  VJetsUncertaintyTool();
  ~VJetsUncertaintyTool();

  void setInputFileName(TString fname);
  void applyEWCorrection(bool doApply, TString processes = "eej,evj,vvj,aj");
  void applyQCDCorrection(bool doApply, TString processes = "eej,evj,vvj,aj");
  void smoothQCDCorrection(bool doSmooth);
  void mergePDF(bool do_merge_PDF);
  void applyDynamicIsolation(bool doPhotonDynamicIsolation);
  TF1 *getFitFunction(TString process) {return m_fit[process];} 
 
  int initialize();

  const std::vector<TString> &getAllVariationNames();

  double getCorrection(int mcChannelNumber, double pTV, TString variation="Nominal");

private:

  Int_t m_nPDF;
  bool m_initialized;
  TString m_inputName;
  std::map<TString, TH1*> m_histoMap;
  std::vector<TString> m_variations;
  std::map<TString, bool> m_applyEWCorrection;
  std::map<TString, bool> m_applyQCDCorrection;
  bool m_smoothQCDCorrection;
  bool m_mergePDF;
  bool m_applyDynamicIsolation;
  std::map<TString, TF1 *>m_fit;
};

#endif
