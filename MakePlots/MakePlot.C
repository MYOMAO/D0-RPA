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

	const int N = 3;

const int BINNUM = 20000;
const int NPlots = 1;

TFile *fin[N];

 gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
//TFile *fin = new TFile("/data/wangj/MC2015/Dntuple/pp/Official/ntD_EvtBase_20170427_DfinderMC_pp_20170427_D0_dPt0tkPt0p1_Pythia8_prompt_D0pt0p0_pp502_TuneCUETP8M1_pthatweight.root"); 
 fin[0] = new TFile("/data/wangj/MC2016/ntD_EvtBase_20170612_DfinderMC_20170503_pp_Pythia8_prompt_D0pt0p0_Pthat0-5-10_pp502_TuneCUETP8M1_AOD_dPt0tkPt0p2_D0_BDT_pp_0p0_0p5_trkpt0p2.root");
fin[1] = new TFile("/data/wangj/MC2016/ntD_EvtBase_20170612_DfinderMC_20170503_pp_Pythia8_prompt_D0pt0p0_Pthat0-5-10_pp502_TuneCUETP8M1_AOD_dPt0tkPt0p2_D0_BDT_pp_0p0_0p5_trkpt0p2.root");
fin[2] = new TFile("/data/zhaozhong/newMinBias/MergeBDT/MinBias1/PD1BDT.root");

//TFile *fin2 = new TFile("/data/zhaozhong/AllPD/PD3.root");

double MassAve = 1.86484;
double Width = 0.08;
double MassMin = MassAve - Width;
double MassMax = MassAve + Width;

cout << "MassMin = " << MassMin << endl;
cout << "MassMax = " << MassMax << endl;

TH1D *h1 = new TH1D("h1","Track1EtaS",200,-2,2);
TH1D *h2 = new TH1D("h2","Track1EtaB",200,-2,2);
TH1D *h3 = new TH1D("h3","Track2EtaS",200,-2,2);
TH1D *h4 = new TH1D("h4","Track2EtaB",200,-2,2);
TH1D *d1 = new TH1D("d1","Track1EtaD",200,-2,2);
TH1D *d2 = new TH1D("d2","Track1EtaD",200,-2,2);


TH1D *h5 = new TH1D("h5","Track1pTSignal",80,0,1.5);
TH1D *h6 = new TH1D("h6","Track2pTSignal",80,0,1.5);
TH1D *h7 = new TH1D("h7","Track1pTB",80,0,1.5);
TH1D *h8 = new TH1D("h8","Track2pTB",80,0,1.5);
TH1D *d3 = new TH1D("d3","Track1PtD",80,0,1.5);
TH1D *d4 = new TH1D("d4","Track2PtD",80,0,1.5);


TH1D *h9 = new TH1D("h9","Dchi2clS",80,0,1);
TH1D *h10 = new TH1D("h10","Dchi2clB",80,0,1);
TH1D *h11 = new TH1D("h11","DalphaS",100,0,5);
TH1D *h12 = new TH1D("h12","DalphaB",100,0,5);
TH1D *d5 = new TH1D("d5","Dchi2clD",80,0,1);
TH1D *d6 = new TH1D("d6","DalphaD",100,0,5);


TH1D *h13 = new TH1D("h13","DsvpvDistanceS",80,0,0.1);
TH1D *h14 = new TH1D("h14","DsvpvDistanceB",80,0,0.1);
TH1D *h15 = new TH1D("h15","DsvpvDisErrS",80,0,0.1);
TH1D *h16 = new TH1D("h16","DsvpvDisErrB",80,0,0.1);
TH1D *d7 = new TH1D("d7","DsvpvDistanceD",80,0,0.1);
TH1D *d8 = new TH1D("d8","DsvpvDisErrD",80,0,0.1);


TH1D *h17 = new TH1D("h17","Dtrk1PtErrS",80,0,0.1);
TH1D *h18 = new TH1D("h18","Dtrk1PtErrB",80,0,0.1);
TH1D *h19 = new TH1D("h19","Dtrk2PtErrS",80,0,0.1);
TH1D *h20 = new TH1D("h20","Dtrk2PtErrB",80,0,0.1);
TH1D *d9 = new TH1D("d9","Dtrk1PtErrD",80,0,0.1);
TH1D *d10 = new TH1D("d10","Dtrk2PtErrD",80,0,0.1);


TH1D *h21 = new TH1D("h21","RatioS",80,0,10);
TH1D *h22 = new TH1D("h22","RatioB",80,0,10);
TH1D *d11 = new TH1D("d11","RatioD",80,0,10);

TH1D *RawMid = new TH1D("RawMid","p_{T} < 1.0",200,1.7,2.0);
TH1D *RawLow = new TH1D("RawLow","p_{T} < 0.5",200,1.7,2.0);


TH1D *asyms = new TH1D("asyms","asymS",80,-0.1,0.7);
TH1D *asymb = new TH1D("asymb","asymB",80,-0.1,0.7);
TH1D *asymd = new TH1D("asymd","asymD",80,-0.1,0.7);

TH1D *h23 = new TH1D("h23","DsvpvDistanceCorrectedS",80,0,0.1);
TH1D *h24 = new TH1D("h24","DsvpvDistanceCorrectedB",80,0,0.1);
TH1D *h25 = new TH1D("h25","DsvpvDisErrCorrectedS",80,0,0.1);
TH1D *h26 = new TH1D("h26","DsvpvDisErrCorrectedB",80,0,0.1);
TH1D *d12 = new TH1D("d12","DsvpvDistanceCorrectedD",80,0,0.1);
TH1D *d13 = new TH1D("d13","DsvpvDisErrCorrectedD",80,0,0.1);

TH1D *h27 = new TH1D("h27","DCASig",100,0,0.1);
TH1D *h28 = new TH1D("h28","DCAb",100,0,0.1);
TH1D *d14 = new TH1D("d14","DCAD",100,0,0.1);

TH1D *h29 = new TH1D("h29","Costheta1S",100,-1.1,1.1);
TH1D *h30 = new TH1D("h30","Costheta1B",100,-1.1,1.1);
TH1D *d15 = new TH1D("d15","Costheta1D",100,-1.1,1.1);



TH1D *h31 = new TH1D("h31","Costheta2S",100,-1.1,1.1);
TH1D *h32 = new TH1D("h32","Costheta2B",100,-1.1,1.1);
TH1D *d16 = new TH1D("d16","Costheta2D",100,-1.1,1.1);


TH1D *h33 = new TH1D("h33","Dtrk1BDTS",100,-1.1,1.1);
TH1D *h34 = new TH1D("h34","Dtrk1BDTB",100,-1.1,1.1);
TH1D *d17 = new TH1D("d17","Dtrk1BDTD",100,-1.1,1.1);



TH1D *h35 = new TH1D("h35","Dtrk2BDTS",100,-1.1,1.1);
TH1D *h36 = new TH1D("h36","Dtrk2BDTB",100,-1.1,1.1);
TH1D *d18 = new TH1D("d18","Dtrk2BDTD",100,-1.1,1.1);


TH1D *h37 = new TH1D("h37","Dtrk1DxyS",100,-0.2,0.2);
TH1D *h38 = new TH1D("h38","Dtrk1DxyB",100,-0.2,0.2);
TH1D *d19 = new TH1D("d18","Dtrk1DxyD",100,-0.2,0.2);

TH1D *h39 = new TH1D("h39","Dtrk2DxyS",100,-0.2,0.2);
TH1D *h40 = new TH1D("h40","Dtrk2DxyB",100,-0.2,0.2);
TH1D *d20 = new TH1D("d20","Dtrk2DxyD",100,-0.2,0.2);


TH1D *h41 = new TH1D("h41","Dtrk1DzS",100,-0.2,0.2);
TH1D *h42 = new TH1D("h42","Dtrk1DzB",100,-0.2,0.2);
TH1D *d21 = new TH1D("d21","Dtrk1DzD",100,-0.2,0.2);

TH1D *h43 = new TH1D("h43","Dtrk2DzS",100,-0.2,0.2);
TH1D *h44 = new TH1D("h44","Dtrk2DzB",100,-0.2,0.2);
TH1D *d22 = new TH1D("d22","Dtrk2DzD",100,-0.2,0.2);


/*
TString Primarycut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>2.5";
 TString Ptcut1 = "Dpt > 0.5 && Dpt < 1.0"; 
 TString Ptcut2 = "Dpt > 0.0 && Dpt <  0.5"; 

  TString cuts = "Dgen == 23333"; 
    TString cutb = "Dgen != 23333"; 

 TString Cut[NPlots];
 
 Cut[0] = Form("%s && %s && %s",Primarycut.Data(),Ptcut1.Data(),cuts.Data());
cout << Cut[0].Data() << endl;
*/
TCanvas *c = new TCanvas("c", "c",0,0,600,600);
c->cd();

for(int k = 0; k < N; k++)
{

  TTree *MC = (TTree*)fin[k]->Get("ntDkpi");

  MC->AddFriend("ntHlt");
  MC->AddFriend("ntHi");
  MC->AddFriend("ntSkim");
  MC->AddFriend("Dtrk1mvaTree");
  MC->AddFriend("Dtrk2mvaTree");

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
double Dtrk1BDT[BINNUM];
double Dtrk2BDT[BINNUM];
float Dtrk1thetastar[BINNUM];
float Dtrk2thetastar[BINNUM];
float Dtrk1Dxy[BINNUM];
float Dtrk2Dxy[BINNUM];
float Dtrk1Dz[BINNUM];
float Dtrk2Dz[BINNUM];


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
MC->SetBranchAddress("Dtrk1BDT",Dtrk1BDT);
MC->SetBranchAddress("Dtrk2BDT",Dtrk2BDT);
MC->SetBranchAddress("Dtrk1thetastar",Dtrk1thetastar);
MC->SetBranchAddress("Dtrk2thetastar",Dtrk2thetastar);

MC->SetBranchAddress("Dtrk1Dxy",Dtrk1Dxy);
MC->SetBranchAddress("Dtrk2Dxy",Dtrk2Dxy);
MC->SetBranchAddress("Dtrk1Dz",Dtrk1Dz);
MC->SetBranchAddress("Dtrk2Dz",Dtrk2Dz);

int Num = MC->GetEntries();

for(int i =0; i < Num; i++)
{

if(i%1000000==0)  cout << "Now working on event " << i << "  out of total " << Num << endl;


MC->GetEntry(i);





for(int j = 0; j < Dsize; j++)
{
/*
if(Dgen[j] == 23333 && Dpt[j] < 1)
{
RawMid->Fill(Dmass[j]);
}

if(Dgen[j] == 23333 && Dpt[j] < 0.5)
{
RawLow->Fill(Dmass[j]);
}


if(abs(PVz[j])<15&&Dy[j]>-1.&&Dy[j]<1.&&Dtrk1highPurity[j]&&Dtrk2highPurity[j]&&abs(Dtrk1Eta[j])<1.5&&abs(Dtrk2Eta[j])<1.5&&DlxyBS[j]/DlxyBSErr[j]>2.5 && Dpt[j] > 0.5 && Dpt[j]< 1.0 && Dgen[j]==23333){ 

	
	h1->Fill(Dmass[j]);
}


if(abs(PVz[j])<15&&Dy[j]>-1.&&Dy[j]<1.&&Dtrk1highPurity[j]&&Dtrk2highPurity[j]&&abs(Dtrk1Eta[j])<1.5&&abs(Dtrk2Eta[j])<1.5&&DlxyBS[j]/DlxyBSErr[j]>2.5 && Dpt[j] > 0.5 && Dpt[j]< 1.0 && Dgen[j] !=23333){ 

	
	h2->Fill(Dmass[j]);
}

if(abs(PVz[j])<15&&Dy[j]>-1.&&Dy[j]<1.&&Dtrk1highPurity[j]&&Dtrk2highPurity[j]&&abs(Dtrk1Eta[j])<1.5&&abs(Dtrk2Eta[j])<1.5&&DlxyBS[j]/DlxyBSErr[j]>2.5 && Dpt[j] > 0.0 && Dpt[j]< 0.5 && Dgen[j]==23333){ 

	
	h3->Fill(Dmass[j]);
}


if(abs(PVz[j])<15&&Dy[j]>-1.&&Dy[j]<1.&&Dtrk1highPurity[j]&&Dtrk2highPurity[j]&&abs(Dtrk1Eta[j])<1.5&&abs(Dtrk2Eta[j])<1.5&&DlxyBS[j]/DlxyBSErr[j]>2.5 && Dpt[j] > 0.0 && Dpt[j]< 0.5 && Dgen[j] !=23333){ 

	
	h4->Fill(Dmass[j]);
}

*/
//if(abs(PVz[j])<15&&Dy[j]>-1.&&Dy[j]<1.&&Dtrk1highPurity[j]&&Dtrk2highPurity[j]&&abs(Dtrk1Eta[j])<1.5&&abs(Dtrk2Eta[j])<1.5&&DlxyBS[j]/DlxyBSErr[j]>2.5 && Dpt[j] > 0.0 && Dpt[j]< 0.5){ }
if(Dpt[j] > 0.0 && Dpt[j]< 0.5 ){ 

if(k < 1)
{
	if(Dgen[j] ==23333) {
h1->Fill(Dtrk1Eta[j]);
h3->Fill(Dtrk2Eta[j]);

		h5->Fill(Dtrk1Pt[j]);
h6->Fill(Dtrk2Pt[j]);
h9->Fill(Dchi2cl[j]);
h11->Fill(Dalpha[j]);
h13->Fill(DsvpvDistance[j]);
h15->Fill(DsvpvDisErr[j]);
h17->Fill(Dtrk1PtErr[j]);
h19->Fill(Dtrk2PtErr[j]);
h21->Fill(DsvpvDistance[j]/DsvpvDisErr[j]);
asyms->Fill((Dtrk1Pt[j]-Dtrk2Pt[j])/(Dtrk1Pt[j]+Dtrk2Pt[j]));
h23->Fill(2*DsvpvDistance[j]/(TMath::Exp(Dy[j])+TMath::Exp(-Dy[j])));
h25->Fill(2*DsvpvDisErr[j]/(TMath::Exp(Dy[j])+TMath::Exp(-Dy[j])));
h27->Fill(DsvpvDistance[j]*TMath::Sin(Dalpha[j]));
h29->Fill(TMath::Cos(Dtrk1thetastar[j]));
h31->Fill(TMath::Cos(Dtrk2thetastar[j]));
h33->Fill(Dtrk1BDT[j]);
h35->Fill(Dtrk2BDT[j]);
h37->Fill(Dtrk1Dxy[j]);
h39->Fill(Dtrk2Dxy[j]);
h41->Fill(Dtrk1Dz[j]);
h43->Fill(Dtrk2Dz[j]);

}

}

if(k == 1){

if(Dgen[j] !=23333)	{
	h2->Fill(Dtrk1Eta[j]);
h4->Fill(Dtrk2Eta[j]);
		h7->Fill(Dtrk1Pt[j]);
h8->Fill(Dtrk2Pt[j]);
h10->Fill(Dchi2cl[j]);
h12->Fill(Dalpha[j]);
h14->Fill(DsvpvDistance[j]);
h16->Fill(DsvpvDisErr[j]);
h18->Fill(Dtrk1PtErr[j]);
h20->Fill(Dtrk2PtErr[j]);
h22->Fill(DsvpvDistance[j]/DsvpvDisErr[j]);
asymb->Fill((Dtrk1Pt[j]-Dtrk2Pt[j])/(Dtrk1Pt[j]+Dtrk2Pt[j]));
h24->Fill(2*DsvpvDistance[j]/(TMath::Exp(Dy[j])+TMath::Exp(-Dy[j])));
h26->Fill(2*DsvpvDisErr[j]/(TMath::Exp(Dy[j])+TMath::Exp(-Dy[j])));
h28->Fill(DsvpvDistance[j]*TMath::Sin(Dalpha[j]));
h30->Fill(TMath::Cos(Dtrk1thetastar[j]));
h32->Fill(TMath::Cos(Dtrk2thetastar[j]));
h34->Fill(Dtrk1BDT[j]);
h36->Fill(Dtrk2BDT[j]);
h38->Fill(Dtrk1Dxy[j]);
h40->Fill(Dtrk2Dxy[j]);
h42->Fill(Dtrk1Dz[j]);
h44->Fill(Dtrk2Dz[j]);

}

}






if(k >1)
{
//cout << "Dmass = " << Dmass[j] << endl;

if(Dmass[j] > MassMax || Dmass[j] < MassMin)
{
d1->Fill(Dtrk1Eta[j]);
d2->Fill(Dtrk2Eta[j]);
d3->Fill(Dtrk1Pt[j]);
d4->Fill(Dtrk2Pt[j]);
d5->Fill(Dchi2cl[j]);
d6->Fill(Dalpha[j]);
d7->Fill(DsvpvDistance[j]);
d8->Fill(DsvpvDisErr[j]);
d9->Fill(Dtrk1PtErr[j]);
d10->Fill(Dtrk2PtErr[j]);
d11->Fill(DsvpvDistance[j]/DsvpvDisErr[j]);
asymd->Fill((Dtrk1Pt[j]-Dtrk2Pt[j])/(Dtrk1Pt[j]+Dtrk2Pt[j]));
d12->Fill(2*DsvpvDistance[j]/(TMath::Exp(Dy[j])+TMath::Exp(-Dy[j])));
d13->Fill(2*DsvpvDisErr[j]/(TMath::Exp(Dy[j])+TMath::Exp(-Dy[j])));
d14->Fill(DsvpvDistance[j]*TMath::Sin(Dalpha[j]));
d15->Fill(TMath::Cos(Dtrk1thetastar[j]));
d16->Fill(TMath::Cos(Dtrk2thetastar[j]));
d17->Fill(Dtrk1BDT[j]);
d18->Fill(Dtrk2BDT[j]);
d19->Fill(Dtrk1Dxy[j]);
d20->Fill(Dtrk2Dxy[j]);
d21->Fill(Dtrk1Dz[j]);
d22->Fill(Dtrk2Dz[j]);

//cout << " j = " << j << endl;
}




}




}


}

}
}
TString outFileName = Form("YieldStudy/outputfile.root");

TFile *fout = new TFile(outFileName.Data(),"RECREATE");

fout->cd();

//cout << "Total" << d1->Integral() << endl;;

h1->SetTitle("Signal at 0.5GeV < P_{T} < 1 GeV");
h1->GetYaxis()->SetTitle("Probability");
h1->GetXaxis()->SetTitle("p_{T} (GeV)");
h1->Draw();
c->Update();

c->SaveAs("YieldStudy/MidPTSignal.png");


h2->SetTitle("Background at 0.5GeV < P_{T} < 1 GeV");
h2->GetYaxis()->SetTitle("Counts");
h2->GetXaxis()->SetTitle("p_{T} (GeV)");
h2->Draw();
c->Update();

c->SaveAs("YieldStudy/MidPb.png");


h3->SetTitle("Signal at 0.0GeV < P_{T} < 0.5 GeV");
h3->GetYaxis()->SetTitle("Counts");
h3->GetXaxis()->SetTitle("p_{T} (GeV)");
h3->Draw();
c->Update();

c->SaveAs("YieldStudy/LowPTsignal.png");

h4->SetTitle("Background at 0.0GeV < P_{T} < 0.5 GeV");
h4->GetYaxis()->SetTitle("Counts");
h4->GetXaxis()->SetTitle("p_{T} (GeV)");
h4->Draw();
c->Update();

c->SaveAs("YieldStudy/LowPtb.png");


h1->Scale(1./h1->Integral()); 
h2->Scale(1./h2->Integral()); 
   h1->SetLineColor(kRed);
	  h1->SetLineWidth(3);
    h2->SetLineColor(kBlue+1);
	  h2->SetLineWidth(3);
h1->Draw();
h2->Draw("SAME");
	  d1->Scale(1./d1->Integral()); 
d1->SetLineColor(kGreen);
	  d1->SetLineWidth(3);
	  d1->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/Track1Eta.png");


h3->Scale(1./h3->Integral()); 
h4->Scale(1./h4->Integral()); 
   h3->SetLineColor(kRed);
	  h3->SetLineWidth(3);
    h4->SetLineColor(kBlue+1);
	  h4->SetLineWidth(3);
h3->Draw();
h4->Draw("SAME");
	  d2->Scale(1./d2->Integral()); 
d2->SetLineColor(kGreen);
	  d2->SetLineWidth(3);
	  d2->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/Track1Eta.png");



h5->Scale(1./h5->Integral()); 
h7->Scale(1./h7->Integral()); 
   h5->SetLineColor(kRed);
	  h5->SetLineWidth(3);
    h7->SetLineColor(kBlue+1);
	  h7->SetLineWidth(3);
h5->Draw();
h7->Draw("SAME");
	  d3->Scale(1./d3->Integral()); 

d3->SetLineColor(kGreen);
	  d3->SetLineWidth(3);
	  d3->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/Track1Pt.png");

h6->Scale(1./h6->Integral()); 
h8->Scale(1./h8->Integral());
h6->SetLineColor(kRed);
h6->SetLineWidth(3);
h8->SetLineColor(kBlue+1);
h8->SetLineWidth(3);

h6->Draw();
h8->Draw("SAME");
	  d4->Scale(1./d4->Integral()); 
d4->SetLineColor(kGreen);
	  d4->SetLineWidth(3);
	  d4->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/Track2Pt.png");

h9->Scale(1./h9->Integral()); 
h10->Scale(1./h10->Integral());
h9->SetLineColor(kRed);
h9->SetLineWidth(3);
h10->SetLineColor(kBlue+1);
h10->SetLineWidth(3);

h9->Draw();
h10->Draw("SAME");
	  d5->Scale(1./d5->Integral()); 
d5->SetLineColor(kGreen);
	  d5->SetLineWidth(3);
	  d5->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/Dchi2cl.png");

h11->Scale(1./h11->Integral()); 
h12->Scale(1./h12->Integral()); 
h11->SetLineColor(kRed);
h11->SetLineWidth(3);
h12->SetLineColor(kBlue+1);
h12->SetLineWidth(3);

h11->Draw();
h12->Draw("SAME");
	  d6->Scale(1./d6->Integral()); 
d6->SetLineColor(kGreen);
	  d6->SetLineWidth(3);
	  d6->Draw("SAME");


c->Update();

c->SaveAs("YieldStudy/Alpha.png");


h13->Scale(1./h13->Integral()); 
h14->Scale(1./h14->Integral()); 
h13->SetLineColor(kRed);
h13->SetLineWidth(3);
h14->SetLineColor(kBlue+1);
h14->SetLineWidth(3);

h13->Draw();
h14->Draw("SAME");

	  d7->Scale(1./d7->Integral()); 
d7->SetLineColor(kGreen);
	  d7->SetLineWidth(3);
	  d7->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/DsvpvDistance.png");


h15->Scale(1./h15->Integral()); 
h16->Scale(1./h16->Integral()); 
h15->SetLineColor(kRed);
h15->SetLineWidth(3);
h16->SetLineColor(kBlue+1);
h16->SetLineWidth(3);

h15->Draw();
h16->Draw("SAME");
	  d8->Scale(1./d8->Integral()); 
d8->SetLineColor(kGreen);
	  d8->SetLineWidth(3);
	  d8->Draw("SAME");


c->Update();

c->SaveAs("YieldStudy/DsvpvDistanceErr.png");


h21->Scale(1./h21->Integral()); 
h22->Scale(1./h22->Integral()); 
h21->SetLineColor(kRed);
h21->SetLineWidth(3);
h22->SetLineColor(kBlue+1);
h22->SetLineWidth(3);
h21->Draw();
h22->Draw("SAME");
	  d11->Scale(1./d11->Integral()); 
d11->SetLineColor(kGreen);
	  d11->SetLineWidth(3);
	  d11->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/DistanceRatio.png");

h17->Scale(1./h17->Integral()); 
h18->Scale(1./h18->Integral()); 
h17->SetLineColor(kRed);
h17->SetLineWidth(3);
h18->SetLineColor(kBlue+1);
h18->SetLineWidth(3);

h17->Draw();
h18->Draw("SAME");
	  d9->Scale(1./d9->Integral()); 
d9->SetLineColor(kGreen);
	  d9->SetLineWidth(3);
	  d9->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/Track1Error.png");

h19->Scale(1./h19->Integral()); 
h20->Scale(1./h20->Integral()); 
h19->SetLineColor(kRed);
h19->SetLineWidth(3);
h20->SetLineColor(kBlue+1);
h20->SetLineWidth(3);
h19->Draw();
h20->Draw("SAME");
	  d10->Scale(1./d10->Integral()); 
d10->SetLineColor(kGreen);
	  d10->SetLineWidth(3);
	  d10->Draw("SAME");

c->Update();


c->SaveAs("YieldStudy/Track2Error.png");


asyms->Scale(1./asyms->Integral()); 
asymb->Scale(1./asymb->Integral()); 
asyms->SetLineColor(kRed);
asyms->SetLineWidth(3);
asymb->SetLineColor(kBlue+1);
asymb->SetLineWidth(3);
asyms->Draw();
asymb->Draw("SAME");
	  asymd->Scale(1./d10->Integral()); 
asymd->SetLineColor(kGreen);
	  asymd->SetLineWidth(3);
	  asymd->Draw("SAME");

c->Update();


c->SaveAs("YieldStudy/TrackAsymetry.png");


RawMid->SetTitle("MC Signal p_{T} < 1 GeV");

RawMid->GetXaxis()->SetTitle("Mass (GeV)");
RawMid->GetYaxis()->SetTitle("Counts (GeV)");

RawMid->Draw();



c->SaveAs("YieldStudy/RawMid.png");





RawLow->SetTitle("MC Signal p_{T} < 0.5 GeV");

RawLow->GetXaxis()->SetTitle("Mass (GeV)");
RawLow->GetYaxis()->SetTitle("Counts (GeV)");

RawLow->Draw();



c->SaveAs("YieldStudy/RawLow.png");


h23->Scale(1./h23->Integral()); 
h24->Scale(1./h24->Integral()); 
h23->SetLineColor(kRed);
h23->SetLineWidth(3);
h24->SetLineColor(kBlue+1);
h24->SetLineWidth(3);

h23->Draw();
h24->Draw("SAME");
	  d12->Scale(1./d12->Integral()); 
d12->SetLineColor(kGreen);
	  d12->SetLineWidth(3);
	  d12->Draw("SAME");

c->Update();

c->SaveAs("YieldStudy/DsvpvDistanceCorrected.png");


h25->Scale(1./h25->Integral()); 
h26->Scale(1./h26->Integral()); 
h25->SetLineColor(kRed);
h25->SetLineWidth(3);
h26->SetLineColor(kBlue+1);
h26->SetLineWidth(3);

h25->Draw();
h26->Draw("SAME");

	  d13->Scale(1./d13->Integral()); 
d13->SetLineColor(kGreen);
	  d13->SetLineWidth(3);
	  d13->Draw("SAME");

c->Update();


c->SaveAs("YieldStudy/DsvpvDistanceErrCorrected.png");


h27->Scale(1./h27->Integral()); 
h28->Scale(1./h28->Integral()); 
h27->SetLineColor(kRed);
h27->SetLineWidth(3);
h28->SetLineColor(kBlue+1);
h28->SetLineWidth(3);

h27->Draw();
h28->Draw("SAME");
	  d14->Scale(1./d14->Integral()); 
d14->SetLineColor(kGreen);
	  d14->SetLineWidth(3);
	  d14->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/DCA.png");


h29->Scale(1./h29->Integral()); 
h30->Scale(1./h30->Integral()); 
h29->SetLineColor(kRed);
h30->SetLineWidth(3);
h29->SetLineColor(kBlue+1);
h30->SetLineWidth(3);

h29->Draw();
h30->Draw("SAME");
	  d15->Scale(1./d15->Integral()); 
d15->SetLineColor(kGreen);
	  d15->SetLineWidth(3);
	  d15->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/CosTheta1.png");




h31->Scale(1./h31->Integral()); 
h32->Scale(1./h32->Integral()); 
h31->SetLineColor(kRed);
h32->SetLineWidth(3);
h31->SetLineColor(kBlue+1);
h32->SetLineWidth(3);

h31->Draw();
h32->Draw("SAME");
	  d16->Scale(1./d16->Integral()); 
d16->SetLineColor(kGreen);
	  d16->SetLineWidth(3);
	  d16->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/CosTheta2.png");


h33->Scale(1./h33->Integral()); 
h34->Scale(1./h34->Integral()); 
h33->SetLineColor(kRed);
h34->SetLineWidth(3);
h33->SetLineColor(kBlue+1);
h34->SetLineWidth(3);

h33->Draw();
h34->Draw("SAME");
	  d17->Scale(1./d17->Integral()); 
d17->SetLineColor(kGreen);
	  d17->SetLineWidth(3);
	  d17->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/BDTTrack1.png");





h35->Scale(1./h35->Integral()); 
h36->Scale(1./h36->Integral()); 
h35->SetLineColor(kRed);
h36->SetLineWidth(3);
h35->SetLineColor(kBlue+1);
h36->SetLineWidth(3);

h35->Draw();
h36->Draw("SAME");
	  d18->Scale(1./d18->Integral()); 
d18->SetLineColor(kGreen);
	  d18->SetLineWidth(3);
	  d18->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/BDTTrack2.png");

h37->Scale(1./h37->Integral()); 
h38->Scale(1./h38->Integral()); 
h37->SetLineColor(kRed);
h38->SetLineWidth(3);
h37->SetLineColor(kBlue+1);
h38->SetLineWidth(3);


h37->Draw();
h38->Draw("SAME");
d19->Scale(1./d19->Integral()); 
d19->SetLineColor(kGreen);
d19->SetLineWidth(3);
d19->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/Track1Dxy.png");


h39->Scale(1./h39->Integral()); 
h40->Scale(1./h40->Integral()); 
h39->SetLineColor(kRed);
h40->SetLineWidth(3);
h39->SetLineColor(kBlue+1);
h40->SetLineWidth(3);


h39->Draw();
h40->Draw("SAME");
d20->Scale(1./d20->Integral()); 
d20->SetLineColor(kGreen);
d20->SetLineWidth(3);
d20->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/Track2Dxy.png");

h41->Scale(1./h41->Integral()); 
h42->Scale(1./h42->Integral()); 
h41->SetLineColor(kRed);
h42->SetLineWidth(3);
h41->SetLineColor(kBlue+1);
h42->SetLineWidth(3);


h41->Draw();
h42->Draw("SAME");
d21->Scale(1./d21->Integral()); 
d21->SetLineColor(kGreen);
d21->SetLineWidth(3);
d21->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/Track1Dz.png");

h43->Scale(1./h43->Integral()); 
h44->Scale(1./h44->Integral()); 
h43->SetLineColor(kRed);
h44->SetLineWidth(3);
h43->SetLineColor(kBlue+1);
h44->SetLineWidth(3);

h43->Draw();
h44->Draw("SAME");
d22->Scale(1./d22->Integral()); 
d22->SetLineColor(kGreen);
d22->SetLineWidth(3);
d22->Draw("SAME");
c->Update();

c->SaveAs("YieldStudy/Track2Dz.png");




h1->Write();
h2->Write();
h3->Write();
h4->Write();
h5->Write();
h6->Write();
h7->Write();
h8->Write();
h9->Write();
h10->Write();
h11->Write();
h12->Write();
h13->Write();
h14->Write();
h15->Write();
h16->Write();
h17->Write();
h18->Write();
h19->Write();
h20->Write();
RawMid->Write();
RawLow->Write();

h21->Write();
h22->Write();
asyms->Write();
asymb->Write();
asymd->Write();
h23->Write();
h24->Write();
h25->Write();
h26->Write();

h27->Write();
h28->Write();
h29->Write();
h30->Write();

h31->Write();
h32->Write();
h33->Write();
h34->Write();
h35->Write();
h36->Write();

h37->Write();
h38->Write();
h39->Write();
h40->Write();
h41->Write();
h42->Write();

h43->Write();
h44->Write();

d1->Write();
d2->Write();
d3->Write();
d4->Write();
d5->Write();
d6->Write();
d7->Write();
d8->Write();
d9->Write();
d10->Write();
d11->Write();
d12->Write();
d13->Write();
d14->Write();
d15->Write();
d16->Write();
d17->Write();
d18->Write();
d19->Write();
d20->Write();
d21->Write();
d22->Write();
}

