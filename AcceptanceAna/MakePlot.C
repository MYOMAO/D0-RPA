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


void MakePlot(){


const int BINNUM = 20000;
const int NPlots = 1;

 gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
//TFile *fin = new TFile("/data/wangj/MC2015/Dntuple/pp/Official/ntD_EvtBase_20170427_DfinderMC_pp_20170427_D0_dPt0tkPt0p1_Pythia8_prompt_D0pt0p0_pp502_TuneCUETP8M1_pthatweight.root"); 
TFile *fin = new TFile("/data/zhaozhong/MVAFiles/MC.root");
//TFile *fin = new TFile("/data/zhaozhong/MVAFiles/0GeV/MC.root");

//  TFile *fin2 = new TFile("/data/zhaozhong/AllPD/PD3.root");

  TTree *MC = (TTree*)fin->Get("ntDkpi");

  MC->AddFriend("ntHlt");
  MC->AddFriend("ntHi");
  MC->AddFriend("ntSkim");
  MC->AddFriend("mvaTree");

  
  float Dmass[BINNUM];
float Dpt[BINNUM];
float Dgen[BINNUM];
float PVz[BINNUM];
float Dy[BINNUM];
bool Dtrk1highPurity[BINNUM];
bool Dtrk2highPurity[BINNUM];
float Dtrk1PtErr[BINNUM];
float Dtrk1Pt[BINNUM];
float Dtrk2PtErr[BINNUM];
float Dtrk2Pt[BINNUM];
float Dtrk1Eta[BINNUM];
float Dtrk2Eta[BINNUM];
float DsvpvDistance[BINNUM];
float DsvpvDisErr[BINNUM];
float DlxyBS[BINNUM];
float DlxyBSErr[BINNUM];
float Dchi2cl[BINNUM];
float Dalpha[BINNUM];
 int Dsize;
  TString Name[NPlots];


MC->SetBranchAddress("Dmass",Dmass);
MC->SetBranchAddress("Dpt",Dpt);
MC->SetBranchAddress("Dgen",Dgen);
MC->SetBranchAddress("PVz",PVz);
MC->SetBranchAddress("Dy",Dy);
MC->SetBranchAddress("Dtrk1highPurity",Dtrk1highPurity);
MC->SetBranchAddress("Dtrk2highPurity",Dtrk2highPurity);
MC->SetBranchAddress("Dtrk1PtErr",Dtrk1PtErr);
MC->SetBranchAddress("Dtrk1Pt",Dtrk1Pt);
MC->SetBranchAddress("Dtrk2PtErr",Dtrk2PtErr);
MC->SetBranchAddress("Dtrk2Pt",Dtrk2Pt);
MC->SetBranchAddress("Dtrk1Eta",Dtrk1Eta);
MC->SetBranchAddress("Dtrk2Eta",Dtrk2Eta);
MC->SetBranchAddress("DsvpvDistance",DsvpvDistance);
MC->SetBranchAddress("DsvpvDisErr",DsvpvDisErr);
MC->SetBranchAddress("DlxyBS",DlxyBS);
MC->SetBranchAddress("DlxyBSErr",DlxyBSErr);
MC->SetBranchAddress("Dchi2cl",Dchi2cl);
MC->SetBranchAddress("Dalpha",Dalpha);
MC->SetBranchAddress("Dsize",&Dsize);

/*
TString Primarycut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>2.5";
 TString Ptcut1 = "Dpt > 0.5 && Dpt < 1.0"; 
 TString Ptcut2 = "Dpt > 0.0 && Dpt <  0.5"; 

  TString cuts = "Dgen == 23333"; 
    TString cutb = "Dgen != 23333"; 

 TString Cut[NPlots];
 
 Cut[0] = Form("%s && %s && %s",Primarycut.Data(),Ptcut1.Data(),cuts.Data());
cout << Cut[0].Data() << endl;c->Update();

*/


const int NBins = 10;

double lpt =0.0;
double hpt = 0.5;








double ptmax = 1;
double ptmin = 0;

double etamin = 1.2;
double etamax = 2.2;

double ptstep = (ptmax-ptmin)/NBins;
double etastep = (etamax-etamin)/NBins;

double Acceffpt;
double Acceffeta;


double track1pt[NBins];
double track2pt[NBins];
double track1eta[NBins];
double track2eta[NBins];



double Afterpt[NBins][NBins];
double Aftereta[NBins][NBins];
double Total = 0;

for(int p = 0; p < NBins; p++)
{
for(int q = 0; q < NBins; q++)
{

Afterpt[p][q]=0;
Aftereta[p][q]=0;

}

}
const int NBinD0pt = 10;



double TotalAcc[NBinD0pt];
double TotalPrefilter[NBinD0pt];


for(int i =0; i<NBinD0pt; i++)
{
	TotalAcc[i] = 0;
	TotalPrefilter[i] = 0;
}

double D0ptmin = 0;
double D0ptmax = 1;

double D0ptstep = (D0ptmax - D0ptmin)/NBinD0pt;




double D0ptL[NBinD0pt];
double D0ptU[NBinD0pt];
double D0ptmid[NBinD0pt];


double PrefilterEff;

int N = MC->GetEntries();


//TH1D* DmassTotal = new TH1D("DmassTotal","DmassTotal",200,1.5,2.2);
//TH1D* Dmassptcut[NBins][NBins];
//TH1D* Dmassetacut[NBins][NBins];
TH2D *AccPt = new TH2D("AccPt","AccPt",NBins,ptmin,ptmax,NBins,ptmin,ptmax);

TH2D *AccEta = new TH2D("AccEta","AccEta",NBins,etamin,etamax,NBins,etamin,etamax);


TH1D *PreEff = new TH1D("PreEff","PreEff",NBinD0pt,D0ptmin,D0ptmax);






for(int i =0; i < N; i++)
{

cout << "Now working on event " << i << "  out of total " << N << endl;


MC->GetEntry(i);





for(int j = 0; j < Dsize; j++)
{


if(Dy[j]< 1 && Dy[j] > -1 && Dpt[j] > lpt && Dpt[j] < hpt && Dgen[j] == 23333)
{


//DmassTotal->Fill(Dmass[j]);

Total = Total + 1;

}




for(int m = 0; m < NBinD0pt; m++)
{
D0ptL[m] = m * D0ptstep;
D0ptU[m] = (m+1) * D0ptstep;
D0ptmid[m] = (D0ptL[m]+D0ptU[m])/2;
if(Dy[j]< 1 && Dy[j] > -1 && Dpt[j] > D0ptL[m] && Dpt[j]< D0ptU[m] && Dgen[j] == 23333 && Dtrk1Pt[j] > 0.1 && Dtrk2Pt[j] > 0.1 && abs(Dtrk1Eta[j])< 1.5 && abs(Dtrk2Eta[j])< 1.5 )
{



//DmassTotal->Fill(Dmass[j]);

TotalAcc[m] = TotalAcc[m] + 1;

}



if(abs(PVz[j])<15&& Dy[j]>-1. && Dy[j]<1. && Dtrk1highPurity[j] && Dtrk2highPurity[j] && abs(Dtrk1Eta[j])<1.5 && abs(Dtrk2Eta[j])<1.5 && DlxyBS[j]/DlxyBSErr[j]>2.5 && Dpt[j] > D0ptL[m] && Dpt[j]< D0ptU[m] && Dgen[j] == 23333 && Dtrk1Pt[j] > 0.1 && Dtrk2Pt[j] > 0.1)
{ 

TotalPrefilter[m] = TotalPrefilter[m]+1;

}

}


for(int k = 0; k < NBins; k++)
{

//cout << "k = " << k << endl;
	
	track1pt[k] = ptmin + k*ptstep;

track1eta[k] = etamin + k*etastep;

	for(int l = 0; l < NBins; l++)
{


//Dmassptcut[i][j] = new TH1D("Dmassptcut","Dmassptcut",200,1.5,2.2);
//Dmassetacut[i][j] = new TH1D("Dmassetacut","Dmassetacut",200,1.5,2.2);

//	cout << "l = " << l << endl;
	track2pt[l] = ptmin + l*ptstep;

track2eta[l] = etamin + l*etastep;

//Acceptance Calculations//


if(Dy[j]< 1 && Dy[j] > -1 && Dpt[j] > lpt && Dpt[j] < hpt && Dgen[j] == 23333 && Dtrk1Pt[j] > track1pt[k] && Dtrk2Pt[j] > track2pt[l] && abs(Dtrk1Eta[j])< 1.5 && abs(Dtrk2Eta[j])< 1.5)
{


//Dmassptcut->Fill(Dmass[j]);

	Afterpt[k][l] = Afterpt[k][l]  + 1;


}


if(Dy[j]< 1 && Dy[j] > -1 && Dpt[j] > lpt && Dpt[j] < hpt && Dgen[j] == 23333 && Dtrk1Pt[j] > 0.1 && Dtrk2Pt[j] > 0.1 && abs(Dtrk1Eta[j])< track1eta[k] && abs(Dtrk2Eta[j])< track2eta[l])
{


//Dmassetacut->Fill(Dmass[j]);

	Aftereta[k][l] = Aftereta[k][l] + 1;



}



//Prefilter Calculations//

/*
if(Dy[j]< 1 && Dy[j] > -1 && Dpt[j] > lpt && Dpt[j] < hpt && Dgen[j] == 23333 && Dtrk1Pt[j] > 0.1 && Dtrk2Pt[j] > 0.1 && abs(Dtrk1Eta[j])< track1eta[k] && abs(Dtrk2Eta[j])< track2eta[l] )
{


//Dmassetacut->Fill(Dmass[j]);

	Aftereta[k][l] = Aftereta[k][l] + 1;


}


*/
}





}



}





}



double BinXpt;
double BinYpt;
double BinXeta;
double BinYeta;
double BinX;



AccPt->GetXaxis()->SetTitle("Track 1 p_{T} (GeV/c)");
AccPt->GetYaxis()->SetTitle("Track 2 p_{T} (GeV/c)");

AccPt->SetTitle("Acceptance vs Track 1 p_{T} and Track 2 p_{T}");


AccEta->GetXaxis()->SetTitle("Track 1 #eta");
AccEta->GetYaxis()->SetTitle("Track 2 #eta");
AccEta->SetTitle("Acceptance vs Track 1 #eta and Track 2 #eta");


PreEff->SetTitle("D^{0} p_{T} (GeV/c)");
PreEff->SetTitle("Prefilter Efficiency vs D^{0} p_{T} (GeV/c)");

for(int i = 0; i <NBins; i++)
{

//	track1pt[i] = ptmin + i*ptstep;

//track1eta[i] = etamin + i*etastep;


for(int j = 0; j< NBins; j++)
{


//	track1pt[j] = ptmin + j*ptstep;
//track1eta[j] = etamin + j*etastep;


BinXpt = AccPt->GetXaxis()->FindBin(track1pt[i]);
BinYpt = AccPt->GetYaxis()->FindBin(track2pt[j]);
BinXeta = AccEta->GetXaxis()->FindBin(track1eta[i]+0.000001);
BinYeta = AccEta->GetYaxis()->FindBin(track2eta[j]+0.000001);

Acceffpt = Afterpt[i][j]/Total;

Acceffeta = Aftereta[i][j]/Total;
 
cout << "BinXpt =  " << BinXpt << "  BinYpt =  " << BinYpt << "  PT Cut Efficiency = " << Acceffpt << endl; 



cout << "BinXeta =  " << BinXeta << "  BinYeta =  " << BinYeta <<  "  Eta Cut Efficiency = " << Acceffeta <<  endl; 


AccPt->SetBinContent(BinXpt,BinYpt,Acceffpt);
AccEta->SetBinContent(BinXeta,BinYeta,Acceffeta);


}



}


for(int k = 0; k < NBinD0pt;k++)
{


	BinX = PreEff->GetXaxis()->FindBin(D0ptmid[k]);

	PrefilterEff = TotalPrefilter[k]/TotalAcc[k];

cout << "BinX =  " << BinX << "  Prefilter  Efficiency = " << PrefilterEff << endl; 


PreEff->SetBinContent(BinX,PrefilterEff);

}



TFile *fout = new TFile("/afs/cern.ch/work/s/szhaozho/SignalAna/AllEff.root","RECREATE");
fout->cd();
AccPt->Write();
AccEta->Write();
PreEff->Write();

//Draw Plots//

TCanvas *c = new TCanvas("c", "c",0,0,600,600);

c->cd();
AccPt->Draw("colz");
c->Update();
c->SaveAs("PTAcceptance.png");

AccEta->Draw("colz");
c->Update();

c->SaveAs("EtaAccpetance.png");

PreEff->Draw();
c->Update();
c->SaveAs("PrefilterEfficiency.png");



}


