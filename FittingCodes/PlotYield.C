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


void PlotYield(){

const int N = 13; 

TFile *fin = new TFile("/data/zhaozhong/prefiltered/All.root");


	gStyle->SetOptStat(0);
	TCanvas* c = new TCanvas("c","",600,600);
	c->cd();

TTree *t = (TTree*)fin->Get("ntDkpi");

 double ptL[N] = {0,0.5,1,0.8,2,3,4,5,6,7,8,10,15};

 double ptU[N] = {0.5,1,2,1.0,3,4,5,6,7,8,10,15,20};

  TString MVA[4] = {"MVA > 0.90","MVA>0.90","MVA > 0.965","MVA > 0.85"};
TFile *fout = new TFile("output.root","RECREATE");


	TLatex* mid;

for(int i = 0; i< N; i++)
{

TString HisName = Form("DmassBin%d.png",i);

TString cut;

if(i < 3)  cut = Form("Dpt > %f && Dpt < %f && %s ", ptL[i], ptU[i], MVA[i].Data());

if( i > 2)   cut = Form("Dpt > %f && Dpt < %f", ptL[i], ptU[i]);


	mid = new TLatex(0.20,0.75,Form("%f < p_{T} < %f", ptL[i], ptU[i]));
	mid->SetNDC();
	mid->SetTextFont(42);
	mid->SetTextSize(0.04);
	mid->SetLineWidth(2);


TH1F *DMass = new TH1F("DMass","",60,1.7,2.0);
DMass->GetXaxis()->SetTitle("Dmass (GeV/c^{2})");
DMass->GetYaxis()->SetTitle("Counts");
DMass->SetTitle("D^{0} Invriant Mass Distribution");
t->Project("DMass","Dmass",cut.Data());


DMass->Draw();
mid->Draw("SAME");


c->Update();

c->SaveAs( HisName.Data() );

DMass->Write();

}




}
