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
using namespace std;



using std::cout;
using std::endl;
#endif


void Fit(){

double min = 0;
double max = 6700;

double xmin = 1.7;
double xmax = 2.05;

double min2 = 0;
double max2 = 3000;


	 gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);

TCanvas *c11 = new TCanvas("c11", "c11",0,0,600,600);
c11->cd();


TFile *fin = new TFile("output.root");


TF1 *f1 = new TF1("f1","[0] +[1]*x+[2]*x*x+[3]*TMath::Exp(-(x-[4])*(x-[4])/(2*[5]*[5]))",xmin,xmax);


f1->SetParameter(4,1.87);
f1->SetParameter(5,0.02);
/*
f1->SetParameter(0,-78240);
f1->SetParameter(1,66042);
f1->SetParameter(2,-36302);
*/



hInCone->Scale(4.0);
  hInCone->GetXaxis()->SetTitleSize(0.05);
  hInCone->GetYaxis()->SetTitleSize(0.05);
hInCone->GetXaxis()->SetTitle("m_{#Lambda_{c}}(GeV/c^{2})");
hInCone->GetXaxis()->CenterTitle();
hInCone->GetYaxis()->SetTitle("Counts/(7 MeV/c^{2})");
   hInCone->GetYaxis()->SetTitleOffset(1.4);
hInCone->GetYaxis()->CenterTitle();
hInCone->SetMaximum(max);
hInCone->SetMinimum(min);
hInCone->GetXaxis()->SetRangeUser(xmin,xmax);
gPad->SetLeftMargin(0.14);
gPad->SetRightMargin(0.05);
gPad->SetBottomMargin(0.13);
gPad->SetTopMargin(0.07);
hInCone->SetTitle("");
hInCone->Fit(f1,"R");



hInCone->Draw("ex0P");
hInCone->SetMarkerSize(1);
hInCone->SetMarkerStyle(10);
hInCone->SetMarkerColor(1);


//Latex - Collision Type Region and Centrality //

  TLatex* texlumiafter = new TLatex(0.28,0.936," 5.02 TeV PbPb Centrality 0 - 100%");
  texlumiafter->SetNDC();
  texlumiafter->SetTextFont(42);
  texlumiafter->SetTextSize(0.038);
  texlumiafter->SetLineWidth(2);
texlumiafter->Draw("same");



if(0){
//Latex - Collision Type Region //
TLatex* texCol;
texCol= new TLatex(0.22,0.81, "PbPb 5.02TeV");
texCol->SetNDC();
	texCol->SetTextAlign(13);
	//texCol->SetTextSize(0.04);
	texCol->SetTextSize(0.05);
	texCol->SetTextFont(42);
	texCol->SetLineWidth(2);
	texCol->Draw();
}
//Latex - CMS Label Region // 
	
	TLatex* texcms = new TLatex(0.22,0.87,"CMS");
	texcms->SetNDC();
	texcms->SetTextAlign(13);
	texcms->SetTextFont(62);//61
	texcms->SetTextSize(0.06);
	texcms->SetLineWidth(2);
	texcms->Draw();

// Projection Label //
  TLatex* texpreafter = new TLatex(0.22,0.81,"Projection");
  texpreafter->SetNDC();
  texpreafter->SetTextAlign(13);
  texpreafter->SetTextFont(52);
  texpreafter->SetTextSize(0.05);
  texpreafter->SetLineWidth(2);
texpreafter->Draw("same");
hInCone->SetMarkerSize(1);
hInCone->SetMarkerStyle(10);
hInCone->SetMarkerColor(1);
	if(0){

//Centrality Label//
TLatex* texCent;
texCent= new TLatex(0.22,0.74, "Centrality 0% - 100%");
texCent->SetNDC();
	texCent->SetTextAlign(13);
	//texCol->SetTextSize(0.04);
	texCent->SetTextSize(0.05);
	texCent->SetTextFont(42);
	texCent->SetLineWidth(2);
	texCent->Draw();
	}


// Latex - p_T Label//
	TLatex* tex;
	tex = new TLatex(0.65,0.85,"p_{T} > 20 GeV/c");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);
	tex->Draw();

	TLatex* jet;
	jet = new TLatex(0.65,0.79,"#DeltaR < 0.5");
	jet->SetNDC();
	jet->SetTextFont(42);
	jet->SetTextSize(0.04);
	jet->SetLineWidth(2);
	jet->Draw();



// Latex Transverse Momentum Range//

double p_0 = f1->GetParameter(0);
double p_1 = f1->GetParameter(1);
double p_2 = f1->GetParameter(2);
double p_3 = f1->GetParameter(3);
double p_4 = f1->GetParameter(4);
double p_5 = f1->GetParameter(5);

//Signal Curve//
TF1 *mass =new TF1("mass",Form("%f*TMath::Exp(-(x-%f)*(x-%f)/(2*%f*%f)) + %f",p_3,p_4,p_4,p_5,p_5,min),xmin,xmax);

cout << Form("%f*TMath::Exp(-(x-%f)*(x-%f)/(2*%f*%f))",p_3,p_4,p_4,p_5,p_5) << endl;

mass->SetFillColor(kOrange-3);
	mass->SetLineColor(kOrange-3);
		mass->SetFillStyle(3002);
	mass->SetLineWidth(3);
	mass->SetLineStyle(7);
mass->Draw("same");



//Background Curve//
TF1 *background = new TF1("background",Form("%f + %f * x + %f *x *x",p_0,p_1,p_2),xmin,xmax);
background->SetLineColor(4);
background->SetLineStyle(3);
background->SetLineWidth(3);
background->Draw("same");





//Plot Legend//




  TLegend *leg = new TLegend(0.625,0.57,0.95,0.77,NULL,"brNDC");//paper
	leg->SetBorderSize(0);
	//leg->SetTextSize(0.04);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	//leg->SetTextFont(62);
	leg->SetFillStyle(0);
	leg->AddEntry(hInCone,"Data","pl");
	leg->AddEntry(f1,"Fit","l");
	//leg->AddEntry(mass,"B^{+} signal","f");
	leg->AddEntry(mass,"D^{0}","f");
	leg->AddEntry(background,"Combinatorial","l");
//	leg->AddEntry(Bkpi,"B #rightarrow J/#psi X","f");
	leg->Draw("same");



c11->Update();








c11->SaveAs("hInCone.png");

c11->cd();
//TFile *fin1 = new TFile("Ds.root");



TF1 *f2 = new TF1("f2","[0] +[1]*x+[2]*x*x+[3]*TMath::Exp(-(x-[4])*(x-[4])/(2*[5]*[5]))",xmin,xmax);
/*
f2->SetParameter(0,410000);
f2->SetParameter(1,-342000);
f2->SetParameter(2,71800);
f2->SetParameter(3,3260);
*/

f2->SetParameter(4,1.870);
f2->SetParameter(5,0.03);


//f2->SetParameter(7,1.865);
//f2->SetParameter(8,0.001);

hOutCone->Scale(4.0);

gPad->SetLeftMargin(0.14);
hOutCone->SetMaximum(max2);
hOutCone->SetMinimum(min2);
  hOutCone->GetXaxis()->SetTitleSize(0.05);
  hOutCone->GetYaxis()->SetTitleSize(0.05);
hOutCone->GetXaxis()->SetRangeUser(xmin,xmax);
hOutCone->GetXaxis()->SetTitle("m_{D_{s}}(GeV/c^{2})");
hOutCone->GetXaxis()->CenterTitle();
   hOutCone->GetYaxis()->SetTitleOffset(1.4);
hOutCone->GetYaxis()->SetTitle("Counts/(8.57 MeV/c^{2})");
hOutCone->GetYaxis()->CenterTitle();


hOutCone->SetTitle("");



hOutCone->Fit(f2,"R");

hOutCone->Draw("ex0p");

hOutCone->SetMarkerSize(1);
hOutCone->SetMarkerStyle(10);
hOutCone->SetMarkerColor(1);




if(0){
//Latex - Collision Type Region //
texCol= new TLatex(0.22,0.81, "pPb 5.02TeV");
texCol->SetNDC();
	texCol->SetTextAlign(13);
	//texCol->SetTextSize(0.04);
	texCol->SetTextSize(0.05);
	texCol->SetTextFont(42);
	texCol->SetLineWidth(2);
	texCol->Draw();
}
//Latex - CMS Label Region // 

texlumiafter = new TLatex(0.28,0.936,"5.02 TeV PbPb Centrality 0 - 100%");
  texlumiafter->SetNDC();
  texlumiafter->SetTextFont(42);
  texlumiafter->SetTextSize(0.038);
  texlumiafter->SetLineWidth(2);
texlumiafter->Draw("same");



texcms = new TLatex(0.22,0.87,"CMS");
	texcms->SetNDC();
	texcms->SetTextAlign(13);
	texcms->SetTextFont(62);//61
	texcms->SetTextSize(0.06);
	texcms->SetLineWidth(2);
	texcms->Draw();


texpreafter = new TLatex(0.22,0.81,"Projection");
  texpreafter->SetNDC();
  texpreafter->SetTextAlign(13);
  texpreafter->SetTextFont(52);
  texpreafter->SetTextSize(0.05);
  texpreafter->SetLineWidth(2);
texpreafter->Draw("same");



if(0){
//Centrality Label//
texCent= new TLatex(0.22,0.74, "Centrality 30% - 100%");
texCent->SetNDC();
	texCent->SetTextAlign(13);
	//texCol->SetTextSize(0.04);
	texCent->SetTextSize(0.05);
	texCent->SetTextFont(42);
	texCent->SetLineWidth(2);
	texCent->Draw();
}

// Latex - p_T Label//
	tex = new TLatex(0.65,0.85,"p_{T} > 20 GeV/c");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);
	tex->Draw();


	jet = new TLatex(0.65,0.79,"#DeltaR > 0.5");
	jet->SetNDC();
	jet->SetTextFont(42);
	jet->SetTextSize(0.04);
	jet->SetLineWidth(2);
	jet->Draw();
// Latex Transverse Momentum Range//

 p_0 = f2->GetParameter(0);
 p_1 = f2->GetParameter(1);
 p_2 = f2->GetParameter(2);
 p_3 = f2->GetParameter(3);
 p_4 = f2->GetParameter(4);
 p_5 = f2->GetParameter(5);
double p_6 = f2->GetParameter(6);
double p_7 = f2->GetParameter(7);
double p_8 = f2->GetParameter(8);

//Signal Curve//
TF1 *mass1 =new TF1("mass1",Form("%f*TMath::Exp(-(x-%f)*(x-%f)/(2*%f*%f)) + %f",p_3,p_4,p_4,p_5,p_5,min2),xmin,xmax);
//TF1 *mass2 =new TF1("mass2",Form("%f*TMath::Exp(-(x-%f)*(x-%f)/(2*%f*%f)) + %f",p_6,p_7,p_7,p_8,p_8,min2),1.8,2.2);

//cout << Form("%f*TMath::Exp(-(x-%f)*(x-%f)/(2*%f*%f))",p_3,p_4,p_4,p_5,p_5) << endl;

mass1->SetFillColor(kOrange-3);
	mass1->SetLineColor(kOrange-3);
		mass1->SetFillStyle(3002);
	mass1->SetLineWidth(3);
	mass1->SetLineStyle(7);
mass1->Draw("same");

/*

mass2->SetFillColor(kGreen-3);
	mass2->SetLineColor(kGreen-3);
		mass2->SetFillStyle(3002);
	mass2->SetLineWidth(3);jet
	mass2->SetLineStyle(7);
mass2->Draw("same");

*/

//Background Curve//
TF1 *background2 = new TF1("background2",Form("%f + %f * x + %f *x *x",p_0,p_1,p_2),xmin,xmax);
background2->SetLineColor(4);
background2->SetLineStyle(3);
background2->SetLineWidth(3);
background2->Draw("same");





//Plot Legend//




  TLegend *leg = new TLegend(0.625,0.57,0.95,0.77,NULL,"brNDC");//paper
	leg->SetBorderSize(0);
	//leg->SetTextSize(0.04);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	//leg->SetTextFont(62);
	leg->SetFillStyle(0);
	leg->AddEntry(hOutCone,"Data","pl");
	leg->AddEntry(f2,"Fit","l");
	//leg->AddEntry(mass,"B^{+} signal","f");
	leg->AddEntry(mass1,"D^{0}","f");
//		leg->AddEntry(mass2,"D^{+}","f");
leg->AddEntry(background2,"Combinatorial","l");
//	leg->AddEntry(Bkpi,"B #rightarrow J/#psi X","f");
	leg->Draw("same");





c11->Update();

c11->SaveAs("hOutCone.png");



}



