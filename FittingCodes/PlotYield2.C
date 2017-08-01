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


void PlotYield2(){

	const int init = 1; 
const int N = 18;

int TotalEvent=0;
int Event;

	gStyle->SetOptStat(0);
	TCanvas* c = new TCanvas("c","",600,600);
	c->cd();


/*
 double ptL[N] = {0,0.5,1,0.8,2,3,4,5,6,7,8,10,15};

 double ptU[N] = {0.5,1,2,1.0,3,4,5,6,7,8,10,15,20};

  TString MVA[4] = {"MVA > 0.90","MVA>0.90","MVA > 0.965","MVA > 0.85"};

*/

 double ptL = 0.5;

 double ptU = 1.0;
  TString MVA = "MVA > 4.4528113748207632e-01  && DsvpvDistance*TMath::Sin(Dalpha) < 2.5267702390470536e+01 && DsvpvDistance < 1.0499742786038405e+02 && Dtrk1PtErr < 1.6878326778437197e-01 && Dtrk2PtErr < 1.3779453051968235e-01 && (Dtrk1Pt*TMath::Cos(Dtrk1Phi)*Dtrk2Pt*TMath::Cos(Dtrk2Phi)+Dtrk1Pt*TMath::Sin(Dtrk1Phi)*Dtrk2Pt*TMath::Sin(Dtrk2Phi)+TMath::Sqrt(Dtrk1P*Dtrk1P-Dtrk1Pt*Dtrk1Pt)*TMath::Sqrt(Dtrk2P*Dtrk2P-Dtrk2Pt*Dtrk2Pt))/(Dtrk1P*Dtrk2P) < 9.0593440079741361e-01 && (Dtrk1Pt*TMath::Cos(Dtrk1Phi)*Dtrk2Pt*TMath::Cos(Dtrk2Phi)+Dtrk1Pt*TMath::Sin(Dtrk1Phi)*Dtrk2Pt*TMath::Sin(Dtrk2Phi)+TMath::Sqrt(Dtrk1P*Dtrk1P-Dtrk1Pt*Dtrk1Pt)*TMath::Sqrt(Dtrk2P*Dtrk2P-Dtrk2Pt*Dtrk2Pt))/(Dtrk1P*Dtrk2P) > -9.7388209097470269e-01";
//TString MVA = "MVA > 0.994";
	TLatex* mid;

for(int i = init; i< N; i++)
{
if(i != 2 && i !=15) 
{
	cout << "RUNNING FILE  " << i <<  endl;

TString infname = Form("/data/zhaozhong/prefiltered/PD%d.root",i); 

TFile *fin = new TFile(infname.Data());
TTree *t = (TTree*)fin->Get("ntDkpi");
TString HisName = "Dmass";

TString cut = Form("Dpt > %f && Dpt < %f && %s ", ptL, ptU, MVA.Data());

	mid = new TLatex(0.20,0.75,Form("%f < p_{T} < %f", ptL, ptU));
	mid->SetNDC();
	mid->SetTextFont(42);
	mid->SetTextSize(0.04);
	mid->SetLineWidth(2);



TH1F *DMass = new TH1F(HisName.Data(),"",60,1.7,2.0);
DMass->GetXaxis()->SetTitle("Dmass (GeV/c^{2})");
DMass->GetYaxis()->SetTitle("Counts");
DMass->SetTitle("D^{0} Invriant Mass Distribution");
t->Project(HisName.Data(),"Dmass",cut.Data());

	  TFile *fout = new TFile(Form("outfile%d.root",i),"RECREATE");
fout->cd();

DMass->Draw();
mid->Draw("SAME");


Event = t->GetEntries();

DMass->Write();

TotalEvent = TotalEvent + Event;

}

}


cout << "TotalEvent = " << TotalEvent << endl;

}
