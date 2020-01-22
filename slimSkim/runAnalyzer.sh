#!/bin/bash

outputDir=${1:-"/nfs/dust/atlas/user/othrif/scratch/myPP/latest/processed/161219"}
inputDir=${2:-"/nfs/dust/atlas/user/othrif/samples/MicroNtuples/v35Truth/"}

mkdir -p ${outputDir}

echo "################################################################################"
echo "Input Directory:  ${inputDir}"
echo "Output Directory: ${outputDir}"
echo "################################################################################"

root -l -q runSkim.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"W_strong\"\);
root -l -q runSkim.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"W_EWK\"\)
root -l -q runSkim.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"Z_strong\"\);
root -l -q runSkim.C\(\"${inputDir}\"\,\"${outputDir}\"\,\"Z_EWK\"\);
