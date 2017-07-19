using namespace std;
#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "TNtuple.h"
#include "TH1F.h"
#include "../TriggerStudies/triggerEfficiency.C"

double TAA=392.4/(70.*1e9);

void triggercombination(int usePbPb=0,
                        TString inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root",
                        int threshold=0, TString output="outputtestpp.root",
                        int useGJ=0)
{
  TFile* inf = new TFile(inputdata.Data());
  TTree* nt = (TTree*) inf->Get("ntDkpi");
  TTree* HltTree= (TTree*) inf->Get("ntHlt");
  HltTree->AddFriend(nt);
  nt->AddFriend(HltTree);
  
  TString cut = Form("Max$(Dpt)>%d",threshold);
  cout<<cut.Data()<<endl;

  TH1D* hPrescalesPtBins = new TH1D("hPrescalesPtBins","",nBins,ptBins);
  TH1D* hTriggerEfficiencyPtBins = new TH1D("hTriggerEfficiencyPtBins","",nBins,ptBins);
  
  TString triggerHLT[ntriggers];
  int triggerassignment[nBins];
  int triggerHLTthresholds[nBins];
  
  if (!(usePbPb==1||usePbPb==0))
    {
      std::cout<<"ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, you are using a non valid isPbPb option"<<std::endl;
      return;
    }
  bool isPbPb=(bool)(usePbPb);
  if (!(useGJ==1||useGJ==0))
    {
      std::cout<<"ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, you are using a non valid isGJ option"<<std::endl;
      return;
    }
  bool isGJ=(bool)(useGJ);

  
  if(!isPbPb)
    {
      for(int index=0; index<ntriggers;index++)
        {
          triggerHLT[index]=triggerHLTPP[index];
          triggerHLTthresholds[index]=triggerHLTPPthresholds[index];
        }
      for(int index=0; index<nBins;index++) triggerassignment[index]=triggerassignmentPP[index];
  }
  if(isPbPb)
    {
      for(int index=0; index<ntriggers;index++)
        {
          if(isGJ) triggerHLT[index]=triggerHLTPbPbGJ[index];
          else triggerHLT[index]=triggerHLTPbPbTO[index];
          triggerHLTthresholds[index]=triggerHLTPbPbthresholds[index];
        }
      for(int index=0; index<nBins;index++) triggerassignment[index]=triggerassignmentPbPb[index];
    }
  
  double ntriggerscounters[ntriggers];
  double prescale[ntriggers];
  double errorprescale[ntriggers];
  double nflag[ntriggers];               
  double ncounters[ntriggers];
  double ncountersANDunprescaled[ntriggers];
  
  for(int index=0;index<ntriggers;index++)
    {  
      ntriggerscounters[index]=0.;
      prescale[index]=0.;
      nflag[index]=0.;
      ncounters[index]=0.;
      ncountersANDunprescaled[index]=0.;
    }
  
  TH1D*hCountsPrescANDUnpresc[nBins];
  TH1D*hCountsUnpresc[nBins];
  
  for(int m=0;m<ntriggers;m++)
    {
      TString hnamePrescANDUnpresc=Form("hCountsPrescANDUnpresc_%d",m);
      TString hnameUnpresc=Form("hCountsUnpresc_%d",m);
      
      TString fillhistoPrescANDUnpresc=Form("%s>>%s",triggerHLT[m].Data(),hnamePrescANDUnpresc.Data());
      TString fillhistoUnpresc=Form("%s>>%s",triggerHLT[ntriggers-1].Data(),hnameUnpresc.Data());
      
      TString selPrescANDUnpresc=Form("%s&&%s&&%s",triggerHLT[m].Data(),triggerHLT[ntriggers-1].Data(),cut.Data());
      TString selUnpresc=Form("%s&&%s",triggerHLT[ntriggers-1].Data(),cut.Data());
      
      hCountsPrescANDUnpresc[m]=new TH1D(hnamePrescANDUnpresc.Data(),"histo",100,-0.5,2);
      hCountsUnpresc[m]=new TH1D(hnameUnpresc.Data(),"histo",100,-0.5,2);
      
      nt->Draw(fillhistoPrescANDUnpresc.Data(),selPrescANDUnpresc.Data());
      nt->Draw(fillhistoUnpresc.Data(),selUnpresc.Data());
      
      ncountersANDunprescaled[m]=hCountsPrescANDUnpresc[m]->GetEntries();
      ncounters[m]=hCountsUnpresc[m]->GetEntries();
    }
  
  for(int index=0;index<ntriggers;index++)
    {
      prescale[index]=ncountersANDunprescaled[index]/ncounters[ntriggers-1];
      errorprescale[index]=1/ncounters[ntriggers-1]*TMath::Sqrt(ncountersANDunprescaled[index]*(1-(ncountersANDunprescaled[index]/ncounters[ntriggers-1])));
      cout<<"------index------"<<endl;
      cout<<"triggerHLT="<<triggerHLT[index]<<endl;
      cout<<"nuprescaled="<<ncounters[ntriggers-1]<<endl; 
      cout<<"ncountersANDunprescaled="<<ncountersANDunprescaled[index]<<endl; 
      cout<<"prescale="<<prescale[index]<<endl; 
      cout<<"error on prescale binomial="<<errorprescale[index]<<endl; 
      cout<<"relative error on prescale binomial="<<errorprescale[index]/prescale[index]<<endl;    
    }
  
  for(int index=0;index<nBins;index++)
    {
      hPrescalesPtBins->SetBinContent(index+1,prescale[triggerassignment[index]]);
      hPrescalesPtBins->SetBinError(index+1,errorprescale[triggerassignment[index]]);
      double triggerefficiency = triggerEfficiency(hPrescalesPtBins->GetBinCenter(index+1),triggerHLTthresholds[triggerassignment[index]],isPbPb);
      std::cout<<"bin center="<<hPrescalesPtBins->GetBinCenter(index+1)<<", thresholds="<<triggerHLTthresholds[triggerassignment[index]]<<",isPbPb="<<isPbPb<<", efficiency="<<triggerefficiency<<std::endl;
      hTriggerEfficiencyPtBins->SetBinContent(index+1,triggerefficiency);
    }
    
    hTriggerEfficiencyPtBins->Draw();
    TFile* foutput=new TFile(output.Data(),"recreate");
    foutput->cd();
    hPrescalesPtBins->Write();
    hTriggerEfficiencyPtBins->Write();
    
}


int main(int argc, char *argv[])
{
  if(argc==6)
    {
      triggercombination(atoi(argv[1]),argv[2],atoi(argv[3]),argv[4],atoi(argv[5]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs: triggercombination.cc" << std::endl;
      return 1;
    }

}
