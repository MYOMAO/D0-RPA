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

void General(){

const int N = 6;
char name[512];

 gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
TCanvas *c = new TCanvas("c", "c",0,0,600,600);
c->cd();

//TFile *fin = new TFile("/data/wangj/MC2015/Dntuple/pp/Official/ntD_EvtBase_20170416_DfinderMC_pp_20170415_D0_dPt0tkPt0p1_Pythia8_prompt_D0pt0p0_pp502_TuneCUETP8M1_pthatweight.root");
//TFile *fin = new TFile("/data/wangj/MC2015/Dntuple/pp/Official/ntD_EvtBase_20170427_DfinderMC_pp_20170427_D0_dPt0tkPt0p1_Pythia8_prompt_D0pt0p0_pp502_TuneCUETP8M1_pthatweight.root"); 
TFile *fin = new TFile("/data/wangj/MC2015/Dntuple/pp/Official/ntD_EvtBase_20170427_DfinderMC_pp_20170427_D0_dPt0tkPt0p1_Pythia8_prompt_D0pt0p0_Pthat0-5-10_pp502_TuneCUETP8M1.root");
  
TTree *MC = (TTree*)fin->Get("ntDkpi");

  MC->AddFriend("ntHlt");
  MC->AddFriend("ntHi");
  MC->AddFriend("ntSkim");

TH2F *his = new TH2F("his","his",200,-1,1,200,0,10);

//TString Primarycut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05 &&Dtrk1Pt>0.9&&Dtrk2Pt>0.6";
//TString Primarycut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05";
TString Primarycut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>2.5 && Dalpha < 1.2 && Dchi2cl > 0.4 && DsvpvDistance < 0.04 && DsvpvDisErr < 0.04 && Dtrk1Pt > 0.85 && Dtrk2Pt> 0.63";


cout << "The cut is " << Primarycut.Data() << endl;

MC->Project("his","Dpt:Dy",Primarycut.Data());
his->Draw("colz");

his->GetXaxis()->SetTitle("Dy");
his->GetYaxis()->SetTitle("Dp_{T}");
his->SetTitle("Gen Match Plot");


c->Update();

c->SaveAs("GenMatch.png");



//TString cut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>0.85&&Dtrk2Pt>0.77&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.4&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.2 && (DsvpvDistance/DsvpvDisErr)<5.2&&Dchi2cl>0.161";
TString cut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>2.5 && Dalpha < 2.94  && Dalpha > 0.109 && Dchi2cl > 0.0447 && Dtrk1Pt > 0.835 && Dtrk2Pt> 0.535 && ((Dtrk1Pt - Dtrk2Pt)/(Dtrk1Pt + Dtrk2Pt)) < 0.536";

//TString cut = "abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DlxyBS/DlxyBSErr)>2.5 && Dalpha < 1.2 && Dchi2cl > 0.4 && DsvpvDistance < 0.04 && DsvpvDisErr < 0.04 && Dtrk1Pt > 0.85 && Dtrk2Pt> 0.63";
TString Backcut = "Dgen != 23333 && Dgen != 23344";
TString Swacut = "Dgen != 23333";
TString ptrange;
TString Signal = "Dgen == 23333";

/*
double ptlow[N]={0,0.1,0.2,0.3,0.4,0.5};
double pthigh[N]={0.5,0.5,0.5,0.5,0.5,1.0};
*/

double ptlow[N]={0,0,0,0,0,0.5};
double pthigh[N]={0.1,0.2,0.3,0.4,0.5,1.0};


TFile *fout[N];

TString outfilename[N];

for(int i =4; i < N; i++){

outfilename[i] = Form("outfile%d.root",i);
fout[i] = new TFile(outfilename[i].Data(),"RECREATE");
fout[i]->cd();
sprintf(name,"Plot%d.png",i);

//pt = i * 0.1;

ptrange =Form("Dpt > %f && Dpt < %f", ptlow[i],pthigh[i]);

TString label = Form(" %f GeV/c < p_{T} < %f GeV/c", ptlow[i],pthigh[i]);


TString cutall = Form("%s && %s",cut.Data(),ptrange.Data());
TString cutb = Form("%s && %s && %s",cut.Data(),ptrange.Data(),Backcut.Data());
TString cutsw = Form("%s && %s && %s",cut.Data(),ptrange.Data(),Swacut.Data());
TString cuts = Form("%s && %s && %s",cut.Data(),ptrange.Data(),Signal.Data());


TH1F *highs = new TH1F("highs","highs",60,1.7,2.0);
TH1F *high = new TH1F("high","high",60,1.7,2.0);
TH1F *highbkgd = new TH1F("highbkgd","highbkgd",60,1.7,2.0);
TH1F *highswap = new TH1F("highswap","highswap",60,1.7,2.0);

MC->Project("high","Dmass",cutall.Data());
MC->Project("highbkgd","Dmass",cutb.Data());
MC->Project("highswap","Dmass",cutsw.Data());
MC->Project("highs","Dmass",cuts.Data());

	TLatex* tex;
	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);



high->GetXaxis()->SetTitle("D mass  (GeV)");
high->GetYaxis()->SetTitle("Counts");
high->SetTitle("D Meson Invariant Mass Distribution");


high->SetFillStyle(3001);
highswap->SetFillStyle(3001);
highbkgd->SetFillStyle(3001);

high->SetFillColor(kOrange);
highswap->SetFillColor(kGreen);
highbkgd->SetFillColor(kBlue);


high->Draw();
highswap->Draw("SAME");
highbkgd->Draw("SAME");

tex->Draw("SAME");


TLegend *leg = new TLegend(0.625,0.65,0.95,0.85,NULL,"brNDC");//paper
	leg->SetBorderSize(0);
	//leg->SetTextSize(0.04);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	//leg->SetTextFont(62);
	leg->SetFillStyle(0);
leg->AddEntry(high,"Signal");
leg->AddEntry(highbkgd,"Combinatorial");
leg->AddEntry(highswap,"Swapped");

leg->Draw("SAME");



c->Update();
c->SaveAs(name);


highs->Write();
high->Write();
highswap->Write();
highbkgd->Write();



}


}
