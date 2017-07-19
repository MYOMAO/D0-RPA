#!/bin/bash

CENTpPbMIN=0
CENTpPbMAX=100

#
DOSAVEHISTPP=0
DOSAVEHISTpPb=0
DOSAVEHISTPPMB=1
DOSAVEHISTpPbMB=1

#
DOFITDEFAULTNEWPP=0
DOFITDEFAULTNEWpPb=0
DOFITDEFAULTNEWPPMB=1
DOFITDEFAULTNEWpPbMB=1

DOFITINCREASEWIDPP=0
DOFITINCREASEWIDpPb=0
DOFITINCREASEWIDPPMB=1
DOFITINCREASEWIDpPbMB=1

DOFITDECREASEWIDPP=0
DOFITDECREASEWIDpPb=0
DOFITDECREASEWIDPPMB=1
DOFITDECREASEWIDpPbMB=1

DOFITPOLY2PP=0
DOFITPOLY2pPb=0
DOFITPOLY2PPMB=1
DOFITPOLY2pPbMB=1

DOFITEXPO2PP=0
DOFITEXPO2pPb=0
DOFITEXPO2PPMB=1
DOFITEXPO2pPbMB=1


#rm -rf outYield
#rm -rf outfMasshisto
#mkdir outfMasshisto
#mkdir outYield


echo $CENTpPbMAX

INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTDATAPP="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
INPUTMCpPb="/data/wangj/MC2015/Dntuple/pPb/revised/ntD_pPb_Dzero_kpi_prompt/ntD_EvtBase_20160330_Dfinder_20160329_pPb_Pythia8_prompt_D0_dPt1tkPt0p5_pthatweight.root"
INPUTDATApPb="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160331_DfinderData_pPb_20160126_dPt0tkPt2p5_D0_FINALJSON_v6_skimmed.root"
INPUTDATAPPMB="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmedPt1.root"
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTDATApPbMB="/data/wangj/Data2016/5TeV/MinimumBias/ntD_EvtBase_20170328_DfinderData_PAMinimumBias1-8_pPb_20170328_PARun2016B_PromptReco_v1_D0_dPt0tkPt0p2_Dalpha0p14Dchi20p05_LowDsvpv6Dchi20p15_HightkPt0p5.root"
INPUTMCpPbMB="/data/wangj/MC2015/Dntuple/pp/Official/ntD_EvtBase_20161206_DfinderMC_pp_20160502_dPt0tkPt0p5_D0_prompt_Dpt1Dy1p5tkPt0p5Decay2p9Dalpha0p14Skim_pthatweight.root"

##

ISMCPP=0
ISDOWEIGHTPP=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<=8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<=8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"

ISMCpPb=0
ISDOWEIGHTpPb=0
SELGENpPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTpPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGpPb="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
LABELpPb="pPb"


cp config/parametersHighpt.h parameters.h

if [ $DOSAVEHISTPP -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPP" "$INPUTMCPP" "$TRGPP" "$CUTPP" "$ISMCPP" "$ISDOWEIGHTPP" "$LABELPP"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTpPb -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATApPb" "$INPUTMCpPb" "$TRGpPb" "$CUTpPb" "$ISMCpPb" "$ISDOWEIGHTpPb" "$LABELpPb" "$CENTpPbMIN" "$CENTpPbMAX"
rm saveMasshisto.exe
fi

if [ $DOFITDEFAULTNEWPP -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELPP" 
rm fitDdefaultnew.exe
fi

if [ $DOFITDEFAULTNEWpPb -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELpPb" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDdefaultnew.exe
fi

if [ $DOFITINCREASEWIDPP -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELPP"
rm fitDincreasewid.exe
fi

if [ $DOFITINCREASEWIDpPb -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELpPb" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDincreasewid.exe
fi

if [ $DOFITDECREASEWIDPP -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELPP"
rm fitDdecreasewid.exe
fi

if [ $DOFITDECREASEWIDpPb -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELpPb" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDdecreasewid.exe
fi

if [ $DOFITPOLY2PP -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELPP"
rm fitDpoly2.exe
fi

if [ $DOFITPOLY2pPb -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELpPb" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDpoly2.exe
fi

if [ $DOFITEXPO2PP -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELPP"
rm fitDexpo2.exe
fi

if [ $DOFITEXPO2pPb -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELpPb" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDexpo2.exe
fi

#
rm parameters.h

##
ISMCPPMB=0
ISDOWEIGHTPPMB=0
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
CUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"

ISMCpPbMB=0
ISDOWEIGHTpPbMB=0
SELGENpPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"

CUTpPbMB="abs(PVz)<15&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&(Dpt>1.&&Dpt<2.&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.5&&Dalpha<0.12))||(Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&((Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050))))"
#CUTpPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
#TRGpPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
TRGpPbMB="(HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part1_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part2_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part3_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part4_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part5_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part6_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part7_v1||HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_part8_v1)"
LABELpPbMB="pPbMB"

cp config/parametersLowpt.h parameters.h

if [ $DOSAVEHISTPPMB -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATAPPMB" "$INPUTMCPPMB" "$TRGPPMB" "$CUTPPMB" "$ISMCPPMB" "$ISDOWEIGHTPPMB" "$LABELPPMB"
rm saveMasshisto.exe
fi

if [ $DOSAVEHISTpPbMB -eq 1 ]; then
g++ saveMasshisto.C $(root-config --cflags --libs) -g -o saveMasshisto.exe 
./saveMasshisto.exe "$INPUTDATApPbMB" "$INPUTMCpPbMB" "$TRGpPbMB" "$CUTpPbMB" "$ISMCpPbMB" "$ISDOWEIGHTpPbMB" "$LABELpPbMB" "$CENTpPbMIN" "$CENTpPbMAX"
rm saveMasshisto.exe
fi

if [ $DOFITDEFAULTNEWPPMB -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELPPMB"
rm fitDdefaultnew.exe
fi

if [ $DOFITDEFAULTNEWpPbMB -eq 1 ]; then
g++ fitDdefaultnew.C $(root-config --cflags --libs) -g -o fitDdefaultnew.exe 
./fitDdefaultnew.exe "$LABELpPbMB" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDdefaultnew.exe
fi

if [ $DOFITINCREASEWIDPPMB -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELPPMB"
rm fitDincreasewid.exe
fi

if [ $DOFITINCREASEWIDpPbMB -eq 1 ]; then
g++ fitDincreasewid.C $(root-config --cflags --libs) -g -o fitDincreasewid.exe 
./fitDincreasewid.exe "$LABELpPbMB" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDincreasewid.exe
fi

if [ $DOFITDECREASEWIDPPMB -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELPPMB"
rm fitDdecreasewid.exe
fi

if [ $DOFITDECREASEWIDpPbMB -eq 1 ]; then
g++ fitDdecreasewid.C $(root-config --cflags --libs) -g -o fitDdecreasewid.exe 
./fitDdecreasewid.exe "$LABELpPbMB" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDdecreasewid.exe
fi

if [ $DOFITPOLY2PPMB -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELPPMB"
rm fitDpoly2.exe
fi

if [ $DOFITPOLY2pPbMB -eq 1 ]; then
g++ fitDpoly2.C $(root-config --cflags --libs) -g -o fitDpoly2.exe 
./fitDpoly2.exe "$LABELpPbMB" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDpoly2.exe
fi

if [ $DOFITEXPO2PPMB -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELPPMB"
rm fitDexpo2.exe
fi

if [ $DOFITEXPO2pPbMB -eq 1 ]; then
g++ fitDexpo2.C $(root-config --cflags --libs) -g -o fitDexpo2.exe 
./fitDexpo2.exe "$LABELpPbMB" "$CENTpPbMIN" "$CENTpPbMAX"
rm fitDexpo2.exe
fi

#
rm parameters.h

##
