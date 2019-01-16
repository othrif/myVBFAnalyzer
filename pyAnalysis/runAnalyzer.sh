#!/bin/bash

outputDir=${1:-"/Users/othmanerifki/vbf/myVBFAnalyzer/processed"}
inputDir=${2:-"/Users/othmanerifki/vbf/input/truth_v18_090119/"}

echo "################################################################################"
echo "Input Directory:  ${inputDir}"
echo "Output Directory: ${outputDir}"
echo "################################################################################"

root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"VBFH125\"\);
root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"ggFH125\"\);
root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"VH125\"\);
root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"W_strong\"\);
root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"W_EWK\"\);
root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"Z_strong\"\);
root -l -q procAnalyzer.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"Z_EWK\"\);