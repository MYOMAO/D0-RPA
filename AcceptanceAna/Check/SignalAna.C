#ifndef __CINT__
#include "TROOT.h"
#include "TH1.h"
#include "TTree.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRandom.h"
#include <iostream>
#include <fstream>
#include "uti.h"

using namespace std;

using std::cout;
using std::endl;
#endif

void SignalAna(){

const int N = 10;

double lpt =0.0;
double hpt = 0.5;


double track1pt[N];
double track2pt[N];
double ptmax = 2.2;
double ptmin = 1.2;
double ptstep = (ptmax-ptmin)/N;
double Acc;

double BeforeD;
double AfterD;

TFile *fin = new TFile("/data/zhaozhong/MVAFiles/MC.root");
TFile *fin2 = new TFile("/data/zhaozhong/MVAFiles/Data.root");
TTree *MC = (TTree*)fin->Get("ntDkpi");
TTree *data = (TTree*)fin2->Get("ntDkpi");

TH2D * AccHis = new TH2D("AccHis","AccHis",N+1,ptmin,ptmax,N+1,ptmin,ptmax);

//AccHis->GetXaxis()->SetTitle("Track 1 p_{T} (GeV/c)");
//AccHis->GetYaxis()->SetTitle("Track 2 p_{T} (GeV/c)");
//AccHis->SetTitle("Acceptance vs Track and Track 2 p_{T}");


AccHis->GetXaxis()->SetTitle("Track 1 #eta");
AccHis->GetYaxis()->SetTitle("Track 2 #eta");
AccHis->SetTitle("Acceptance vs Track 1 and Track 2 #eta");


TH1D * BeforeCut = new TH1D("BeforeCut","BeforeCut",200,1.5,2.2);
TH1D * AfterCut = new TH1D("AfterCut","AfterCut",200,1.5,2.2);

int BinX;
int BinY;
for(int i = 0; i < N; i++)
{

cout << "i = " << i << endl;
	track1pt[i] = ptmin + i*ptstep;

 for(int j = 0; j< N; j++)
 {
cout << "j = " << j << endl;

	  track2pt[j] = ptmin + j*ptstep;

TString GenCut = Form(" Dy < 1 && Dy > -1 && Dpt >  %f && Dpt < %f && Dgen == 23333",lpt,hpt);

//TString AccCut = Form(" Dy < 1 && Dy > -1 && Dpt >  %f && Dpt < %f && Dgen == 23333 && Dtrk1Pt > %f && Dtrk2Pt > %f && abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5",lpt,hpt,track1pt[i],track2pt[j]);
TString AccCut = Form(" Dy < 1 && Dy > -1 && Dpt >  %f && Dpt < %f && Dgen == 23333 && Dtrk1Pt > 0.1 && Dtrk2Pt > 0.1 && abs(Dtrk1Eta)< %f &&  abs(Dtrk2Eta)< %f",lpt,hpt,track1pt[i],track2pt[j]);


  MC->Project("BeforeCut","Dmass",GenCut.Data());
  MC->Project("AfterCut","Dmass",AccCut.Data());

BeforeD = BeforeCut->Integral();
AfterD = AfterCut->Integral();

cout << "BeforeD = " << BeforeD << " AfterD = " << AfterD << endl; 

Acc = AfterD/BeforeD;

BinX = AccHis->GetXaxis()->FindBin(track1pt[i]-0.0000001);
BinY = AccHis->GetYaxis()->FindBin(track2pt[j]-0.0000001);

cout << "BinX =  " << BinX << " BinY =  " << BinY << endl; 

AccHis->SetBinContent(BinX,BinY,Acc);

 }


}



TFile *fout = new TFile("/afs/cern.ch/work/s/szhaozho/SignalAna/Acceptance.root","RECREATE");
fout->cd();
AccHis->Write();



}
