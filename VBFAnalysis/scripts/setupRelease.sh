#!/bin/bash

# Analysis base release
RELEASE_21="21.2.35"

echo 'Setting up VBF Analyzer code in Release 21 ...'
mkdir -p build run && cd build
acmSetup AthAnalysis,${RELEASE_21}
cd $TestArea/..

echo 'Generating setup script...'
# Clean up if it exists..
if [ -e 'setup.sh' ]; then
  rm -rf setup.sh
fi

echo "#!/bin/bash" >> "setup.sh"
echo "" >> "setup.sh"
echo "cd build" >> "setup.sh"
echo "acmSetup AthAnalysis,${RELEASE_21} " >> "setup.sh"
echo "acm compile" >> "setup.sh"
echo "cd ../" >> "setup.sh"
#echo "alias cbuild=\"cd \$TestArea/ && acm compile && cd ../\"" >> "setup.sh"
echo "alias build=\"cd \$TestArea/ && acm compile && cd ../\"" >> "setup.sh"
echo "alias clean=\"rm -rf  \$TestArea/ setup.sh\"" >> "setup.sh"
echo "echo \"Compile: cbuild, Recompile: build, Clean: clean\"" >> "setup.sh"
echo "echo \"Test with: athena VBFAnalysis/VBFAnalysisAlgJobOptions.py --evtMax 10 --filesInput <path/file.root>  - --currentVariation Nominal\"" >> "setup.sh"
echo "cd \$TestArea/.." >> "setup.sh"
echo "" >> "setup.sh"

echo "Running setup script..."
chmod +x setup.sh
source "setup.sh"
build

echo ''
echo 'Finished VBF R21 Analyzer setup..'
echo 'Next time you login: "source setup.sh"'
echo 'Recompile: build, Clean: clean'
echo 'Now run a quick test with ": athena VBFAnalysis/VBFAnalysisAlgJobOptions.py --evtMax 10 --filesInput <path/file.root>  - --currentVariation Nominal"'

