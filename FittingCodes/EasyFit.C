#include <cmath>
#include <TFile.h>
#include <TString.h>
#include <TLine.h>
#include <TTree.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include "uti.h"
#include "parameters.h"
#include "TF1.h"
using namespace std;





using std::cout;
using std::endl;


void EasyFit()
{

double ptmin = 0.5;
double ptmax = 1.0;
Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

double ymax;
double ymin;

TString cuts=  "MVA > 4.4528113748207632e-01  && DsvpvDistance*TMath::Sin(Dalpha) < 2.5267702390470536e+01 && DsvpvDistance < 1.0499742786038405e+02 && Dtrk1PtErr < 1.6878326778437197e-01 && Dtrk2PtErr < 1.3779453051968235e-01 && (Dtrk1Pt*TMath::Cos(Dtrk1Phi)*Dtrk2Pt*TMath::Cos(Dtrk2Phi)+Dtrk1Pt*TMath::Sin(Dtrk1Phi)*Dtrk2Pt*TMath::Sin(Dtrk2Phi)+TMath::Sqrt(Dtrk1P*Dtrk1P-Dtrk1Pt*Dtrk1Pt)*TMath::Sqrt(Dtrk2P*Dtrk2P-Dtrk2Pt*Dtrk2Pt))/(Dtrk1P*Dtrk2P) < 9.0593440079741361e-01 && (Dtrk1Pt*TMath::Cos(Dtrk1Phi)*Dtrk2Pt*TMath::Cos(Dtrk2Phi)+Dtrk1Pt*TMath::Sin(Dtrk1Phi)*Dtrk2Pt*TMath::Sin(Dtrk2Phi)+TMath::Sqrt(Dtrk1P*Dtrk1P-Dtrk1Pt*Dtrk1Pt)*TMath::Sqrt(Dtrk2P*Dtrk2P-Dtrk2Pt*Dtrk2Pt))/(Dtrk1P*Dtrk2P) > -9.7388209097470269e-01";

	TFile *fin = new TFile("AllMass.root");
	TFile *finMC = new TFile("/data/zhaozhong/prefiltered/MC.root");
 TCanvas* c= new TCanvas("c","c",0,0,600,600);

 gPad->SetBottomMargin(0.10);
 gPad->SetRightMargin(0.05);
  gPad->SetLeftMargin(0.15);

  
  TH1F* hMCSwapped = new TH1F("hMCSwapped","",60,1.7,2.0);  
  TH1F* hMCSignal = new TH1F("hMCSignal","",60,1.7,2.0);  
 
  hMCSwapped->GetXaxis()->SetRangeUser(1.7,2.0);
hMCSignal->GetXaxis()->SetRangeUser(1.7,2.0);

TTree *t = (TTree*)finMC->Get("ntDkpi");

t->AddFriend("ntHlt");
t->AddFriend("ntHi");
t->AddFriend("ntGen");
t->AddFriend("ntSkim");
t->AddFriend("mvaTree");
t->Project("hMCSwapped","Dmass",Form("Dpt > %f && Dpt < %f && Dgen == 23344 && %s",ptmin,ptmax,cuts.Data()));
t->Project("hMCSignal","Dmass",Form("Dpt > %f && Dpt < %f && Dgen == 23333 && %s",ptmin,ptmax,cuts.Data()));

    TH1D* h =  (TH1D*)fin->Get("Dmass");

//Scaling//



h->GetXaxis()->SetRangeUser(1.7,2.0);
hMCSwapped->SetTitle("");
hMCSignal->SetTitle("");
h->SetTitle("");

  TF1* f = new TF1("f","[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);

  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.001,0.05);
  f->SetParLimits(2,0.01,0.5);
  f->SetParLimits(8,0.02,0.2);
  f->SetParLimits(7,0,1);
  f->SetParLimits(9,0,1);
  
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(10,setparam10);
  f->SetParameter(9,setparam9);

  f->FixParameter(8,setparam8);
  f->FixParameter(7,1);
  f->FixParameter(1,fixparam1);
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,0);
  f->FixParameter(6,0);
  f->FixParameter(11,0);
  h->GetEntries();
  
  hMCSignal->Fit(f,"q","",minhisto,maxhisto);
  hMCSignal->Fit(f,"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  hMCSignal->Fit(f,"L q","",minhisto,maxhisto);
  hMCSignal->Fit(f,"L q","",minhisto,maxhisto);
  hMCSignal->Fit(f,"L m","",minhisto,maxhisto);
  
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit(f,"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(f,"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(f,"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(f,"L m","",minhisto,maxhisto);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);
  
  h->Fit(f,"q","",minhisto,maxhisto);
  h->Fit(f,"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.86,1.87);
  f->ReleaseParameter(11);
  f->SetParLimits(11,-1.,1.);
  h->Fit(f,"L q","",minhisto,maxhisto);
  h->Fit(f,"L q","",minhisto,maxhisto);
  h->Fit(f,"L q","",minhisto,maxhisto);
  h->Fit(f,"L m","",minhisto,maxhisto);
  
  TF1* background = new TF1("f1","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(minhisto,maxhisto);
  background->SetLineStyle(2);
  
  TF1* mass = new TF1(Form("fmass_%.0f_%.0f",ptmin,ptmax),"[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(11));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);
  
  TF1* massSwap = new TF1(Form("fmassSwap_%.0f_%.0f",ptmin,ptmax),"[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8),f->GetParameter(11));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);
  h->SetXTitle("m_{#piK} (GeV/c^{2})");
  h->SetYTitle("Entries / (5 MeV/c^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
  h->GetXaxis()->SetTitleOffset(0.94);
  h->GetYaxis()->SetTitleOffset(1.6);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.045);
  h->GetYaxis()->SetTitleSize(0.045);
  h->GetXaxis()->SetTitleFont(42);
  h->GetYaxis()->SetTitleFont(42);
  h->GetXaxis()->SetLabelFont(42);
  h->GetYaxis()->SetLabelFont(42);
  h->GetXaxis()->SetLabelSize(0.04);
  h->GetYaxis()->SetLabelSize(0.04);


  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  h->SetStats(0);
  h->Draw("e");

  background->Draw("same");   
  mass->SetRange(minhisto,maxhisto);	
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  f->Draw("same");
  
  Double_t yield = mass->Integral(minhisto,maxhisto)/binwidthmass;
  Double_t yieldErr = mass->Integral(minhisto,maxhisto)/binwidthmass*mass->GetParError(0)/mass->GetParameter(0);
 
  std::cout<<"YIELD="<<yield<<std::endl;
  std::cout<<"YIELDErr="<<yieldErr<<std::endl;


  TLegend* leg = new TLegend(0.64,0.58,0.87,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  TLatex* texCms;


// cout <<" i = "<< i  << endl;
texCms = new TLatex(0.20,0.93, "#scale[1.25]{CMS} Preliminary");


  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();

 TLatex* texCol;
//  if(collisionsystem=="PP"||collisionsystem=="PPMB") texCol= new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","pp"));
   texCol= new TLatex(0.92,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","pp"));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  TLatex* tex;

  tex = new TLatex(0.21,0.78,Form("%.1f GeV/c < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
 /*
  if(centMax>0){
  TString texper="%";
  tex = new TLatex(0.22,0.71,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tex->SetNDC();
  tex->SetTextColor(1);
  tex->SetTextFont(42);
  tex->SetTextSize(0.045);
  tex->SetLineWidth(2);
  tex->Draw();
  }
*/
  tex = new TLatex(0.21,0.83,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  
// total=f;

/*
	TLatex* Leading;
	  Leading = new TLatex(0.21,0.72,"Leading Jet p_{T} > 80GeV/c");
  Leading->SetNDC();
  Leading->SetTextFont(42);
  Leading->SetTextSize(0.04);
  Leading->SetLineWidth(2);
  Leading->Draw();

	TLatex* jet;

	if(i == 0 || i == 2) jet = new TLatex(0.21,0.66,"0 < #DeltaR < 0.05");
		if(i == 1 || i == 3) jet = new TLatex(0.21,0.66,"0.1 < #DeltaR < 0.2");
	jet->SetNDC();
	jet->SetTextFont(42);
	jet->SetTextSize(0.04);
	jet->SetLineWidth(2);
	jet->Draw();

*/

//  h->GetFunction(Form("f%d",count))->Delete();
  TH1F* histo_copy_nofitfun = ( TH1F * ) h->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->Draw("esame");
//
//c->SaveAs(Form("plotFits/DMass%s_%d.pdf",collisionsystem.Data(),count));
	 c->SaveAs(Form("Dmass_%.1f_%.1f.png",ptmin,ptmax));

 
  //reurn mass;
}



