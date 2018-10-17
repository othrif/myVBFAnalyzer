#!/bin/bash       
                                                                                         
export inputDir=$1                                                                                         
export here=$PWD
cd ${inputDir}              
mkdir merged

#hadd merged/data.root data*root
if [ $(ls | grep data.*root | wc -l) == 0 ] ;then echo "WARNING: (data*root) No Files found" ;else hadd merged/data.root data*root; fi
#hadd merged/VV.root VV*root
if [ $(ls | grep VV.*root | wc -l) == 0 ] ;then echo "WARNING: (VV*root) No Files found" ;else hadd merged/VV.root VV*root; fi
#hadd merged/VVV.root VVV*root
if [ $(ls | grep VVV.*root | wc -l) == 0 ] ;then echo "WARNING: (VVV*root) No Files found" ;else hadd merged/VVV.root VVV*root; fi
#hadd merged/W_strong.root W_strong*root
if [ $(ls | grep W_strong.*root | wc -l) == 0 ] ;then echo "WARNING: (W_strong*root) No Files found" ;else hadd merged/W_strong.root W_strong*root; fi
#hadd merged/Z_strong.root Z_strong*root
if [ $(ls | grep Z_strong.*root | wc -l) == 0 ] ;then echo "WARNING: (Z_strong*root) No Files found" ;else hadd merged/Z_strong.root Z_strong*root; fi
#hadd merged/Z_strong_VBFFilt.root Z_strong_VBFFilt*root
if [ $(ls | grep Z_strong_VBFFilt.*root | wc -l) == 0 ] ;then echo "WARNING: (Z_strong_VBFFilt*root) No Files found" ;else hadd merged/Z_strong_VBFFilt.root Z_strong_VBFFilt*root; fi
#hadd merged/Z_strong_LowMass.root Z_strong_LowMass*root
if [ $(ls | grep Z_strong_LowMass.*root | wc -l) == 0 ] ;then echo "WARNING: (Z_strong_LowMass*root) No Files found" ;else hadd merged/Z_strong_LowMass.root Z_strong_LowMass*root; fi
#hadd merged/W_EWK.root W_EWK.root
if [ $(ls | grep W_EWK.*.root | wc -l) == 0 ] ;then echo "WARNING: (W_EWK*.root) No Files found" ;else hadd merged/W_EWK.root W_EWK*.root; fi
#hadd merged/Z_EWK.root Z_EWK*root
if [ $(ls | grep Z_EWK.*root | wc -l) == 0 ] ;then echo "WARNING: (Z_EWK*root) No Files found" ;else hadd merged/Z_EWK.root Z_EWK*root; fi
#hadd merged/ttbar.root ttbar*root
if [ $(ls | grep ttbar.*root | wc -l) == 0 ] ;then echo "WARNING: (ttbar*root) No Files found" ;else hadd merged/ttbar.root ttbar*root; fi
#hadd merged/QCDw.root QCDw*root
if [ $(ls | grep QCDw.*root | wc -l) == 0 ] ;then echo "WARNING: (QCDw*root) No Files found" ;else hadd merged/QCDw.root QCDw*root; fi
#hadd merged/QCDunw.root QCDunw*root
if [ $(ls | grep QCDunw.*root | wc -l) == 0 ] ;then echo "WARNING: (QCDunw*root) No Files found" ;else hadd merged/QCDunw.root QCDunw*root; fi
#hadd merged/VBFH125.root VBFH125*.root
if [ $(ls | grep VBFH125.*.root | wc -l) == 0 ] ;then echo "WARNING: (VBFH125*.root) No Files found" ;else hadd merged/VBFH125.root VBFH125*.root; fi
#hadd merged/ggFH125.root ggFH125*.root
if [ $(ls | grep ggFH125.*.root | wc -l) == 0 ] ;then echo "WARNING: (ggFH125*.root) No Files found" ;else hadd merged/ggFH125.root ggFH125*.root; fi
#hadd merged/VH125.root VH125*.root
if [ $(ls | grep VH125.*.root | wc -l) == 0 ] ;then echo "WARNING: (VH125*.root) No Files found" ;else hadd merged/VH125.root VH125*.root; fi

#haddmerged/ signal.root *H125*root
#haddmerged/ VV_VVV.root VV*root

cd $here