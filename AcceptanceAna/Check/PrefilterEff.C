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

void PrefilterEff(){
 gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);

TFile *fin = new TFile("/data/zhaozhong/MVAFiles/MC.root");
   TFile *fin2 = new TFile("/data/zhaozhong/dedxPD/MinBias1/PD1dedx.root");

  TTree *MC = (TTree*)fin->Get("ntDkpi");
  TTree *Data = (TTree*)fin2->Get("ntDkpi");

int TotalData = Data->GetEntries();
int TotalMC = MC->GetEntries();

double pt;
double ptL;
double ptU;
const int N = 10;

double ptmax = 1;
double ptmin = 0;

double step = (ptmax - ptmin)/N;

TH1D *his = new TH1D("his","Efficiency vs p_{T}",N,ptmin,ptmax);
TH1D *his2 = new TH1D("his2","SBRatio vs p_{T}",N,ptmin,ptmax);

for(int i = 0; i < N; i++)
{

cout << " i =  " << i << endl;

	ptL = i * step;
ptU = (i+1)*step;
	pt = (ptL + ptU)/2;
TString AccCut = Form(" Dy < 1 && Dy > -1 && Dpt > %f && Dpt < %f && Dgen == 23333 && Dtrk1Pt > 0.1 && Dtrk2Pt > 0.1 && abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5",ptL,ptU);
TString bkgdCut = Form(" Dy < 1 && Dy > -1 && Dpt > %f && Dpt < %f && Dtrk1Pt > 0.1 && Dtrk2Pt > 0.1 && abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5",ptL,ptU);

TString Prefilter = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>2.5 && (DsvpvDistance/DsvpvDisErr) > 2.5";

TString TotalSignalCut = Form("%s && %s ", Prefilter.Data(),AccCut.Data()); 

TString TotalCut = Form("%s && %s ", Prefilter.Data(),bkgdCut.Data()); 




double BeforePre;
double AfterPre;
double bkgd;
double efficiency;
double SBRatio;
double Signal;
double DmassAve = 1.865;
double Dwidth = 0.05;
double NSig = 4;
double Dis = 0.10;

TH1D * h1 = new TH1D("h1","h1",200,1.7,2.0);
TH1D * h2 = new TH1D("h2","h2",200,1.7,2.0);
TH1D * h3 = new TH1D("h3","h3",200,1.7,2.0);

double DMassMin = 1.8;

double DMassMax = 1.95;

double signalgap =DMassMax - DMassMin;

double DmassLeftMin = DmassAve - Dis - Dwidth;
double DmassLeftMax = DmassAve - Dis;


double DmassRightMin = DmassAve +  Dis;
double DmassRightMax = DmassAve + Dis + Dwidth;
cout << "Pass 1" << endl;
MC->Project("h1","Dmass", AccCut.Data());
cout << "Pass 2" << endl;
BeforePre = h1->Integral();

MC->Project("h2", "Dmass", TotalSignalCut.Data());



AfterPre = h2->Integral();


cout << "Before Pre = " << BeforePre << endl;
cout << "After Pre = " << AfterPre << endl;



efficiency = AfterPre/BeforePre;

int DMin = h2->FindBin(DMassMin+0.000001);
int DMax = h2->FindBin(DMassMax-0.000001);

Signal = h2->Integral(DMin,DMax);

Data->Project("h3","Dmass",TotalCut.Data());

int DLMin = h3->FindBin(DmassLeftMin+0.000001); 
int DLMax = h3->FindBin(DmassLeftMax-0.000001); 

int DRMin = h3->FindBin(DmassRightMin+0.000001); 
int DRMax = h3->FindBin(DmassRightMax-0.000001); 

cout << "Total bkgd = " << h3->Integral() << endl;


bkgd = h3->Integral(DLMin,DLMax) + h3->Integral(DRMin,DRMax);

cout << "DLMin = " <<  DLMin << endl;
cout << "DLMax = " <<  DLMax << endl;
cout << "DRMin = " <<  DRMin << endl;
cout << "DRMax = " <<  DRMax << endl;


cout << "bkgd = " << bkgd << endl;

SBRatio =(Signal/signalgap/TotalMC)/(bkgd/Dwidth*2/TotalData);

cout << "SBRatio = " << SBRatio << endl;

cout << "Prefilter Efficiency = " << efficiency << endl;
cout << "Pass 3" << endl;


his->SetBinContent(i,efficiency);
his2->SetBinContent(i,SBRatio);


}

TFile *fout = new TFile("/afs/cern.ch/work/s/szhaozho/SignalAna/Prefilter.root","RECREATE");
fout->cd();

his->Write();
his2->Write();



TCanvas *c = new TCanvas("c", "c",0,0,600,600);
c->cd();
gPad->SetLeftMargin(0.14);
gPad->SetRightMargin(0.08);
gPad->SetBottomMargin(0.10);
gPad->SetTopMargin(0.08);

his->GetXaxis()->SetTitle("p_{T} (GeV/c)");
his2->GetXaxis()->SetTitle("p_{T} (GeV/c)");


his->GetYaxis()->SetTitle("PreFilter Efficiency");
his2->GetYaxis()->SetTitle("Signal to Background Ratio");

his->SetTitle("PreFilter Efficiency");
his2->SetTitle("Signal to Background Ratio");

his->Draw("ex0p");
c->Update();
c->SaveAs("Efficiency.png");

his2->Draw("ex0p");
c->Update();
c->SaveAs("SBRatio.png");



}
