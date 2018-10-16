#############################################
# VBF Higgs to Invisible Full Run 2 Analysis
# My private post-processing framework
#############################################

[![pipeline status](https://gitlab.cern.ch/othrif/myVBFAnalyzer/badges/master/pipeline.svg)](https://gitlab.cern.ch/othrif/myVBFAnalyzer/commits/master)

## Developer ##
Othmane Rifki (othmane.rifki@cern.ch) - DESY


## First time setup ##

```bash
git clone ssh://git@gitlab.cern.ch:7999/VBFInv/STPostProcessing.git source/
mkdir build;cd build
acmSetup AthAnalysis,21.2.35
acm compile
```

## Future setup ##

```bash
cd build
acmSetup
```

## Run VBFAnalysisAlg ##

- Create the normalization file:
```bash
ls -d ParentDir/vXX/* > samples
getN.py -l samples
```
If you want to examine sum of weights of a dsid in the file `h_total->GetBinContent(h_total->GetXaxis()->FindBin("308276"))`

- Run test local:
```bash
athena VBFAnalysis/VBFAnalysisAlgJobOptions.py --evtMax 10 --filesInput <file.root>  - --currentVariation Nominal
```

- Run on condor:
```bash
compactVBFAnalysisCondor.py -l samples -s Nominal -d dir
```
Root files stored in `dir/rootFiles`

- Merge output:
``` bash
mergeVBFAnalysisAlg.sh dir/rootFiles
```

- Create input for plotting
``` bash
mkdir Plots
cd ../Plots
ls FullPath/dir/rootFiles/merged/* > input.txt
makeInput.py --syst Nominal
```
To add variables you would have to change `plotEvents::fillHists` in `plotEvents.h` and `varBinning` dict in `Style.py`. The different lists of systematics are defined in `listSamples.py`

- Plot
``` bash
drawPlot.py --MC --stack --data --signal --ratio
```
Adding "--saveAs pdf" would save the plot as a pdf file

- Create yield table for all regions
``` bash
tables.py
```
