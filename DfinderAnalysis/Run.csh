source /cvmfs/cms.cern.ch/crab3/crab.sh
cmsenv
scram b

echo $0
which grid-proxy-info
echo $SCRAM_ARCH
voms-proxy-init --voms cms --valid 168:00
voms-proxy-info --all
