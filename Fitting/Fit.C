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
#include <TAttMarker>
using namespace std;





using std::cout;
using std::endl;
#endif


//void Fit(const int N, TString P[0], TString P[1], TString P[2], TString P[3],TString P[4],TString P[5],TString P[6],TString P[7],TString P[8]  ){
//void Fit(const int N, TString P0, TString P1,TString P2,TString P3, TString P4, TString P5){
void Fit(const int N, TString P0, TString P1, TString P2, TString P3, TString P4, TString P5){

double min[N] = {0,0,0,0,0,0};
double max[N] = {100,100,350,300,3000,1000};

double xmin = 1.7;
double xmax = 2.05;

double min2 = 0;
double max2 = 3000;

TString Plot[N] = {P0,P1,P2,P3,P4,P5};

TH1F * His[N];
char Name[512];

	 gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);



TFile *fin = new TFile("output.root");
TCanvas *c11 = new TCanvas("c11", "c11",0,0,600,600);


for(int i = 0; i < N; i++){

TF1* f = new TF1("f","[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);
c11->cd();

//sprintf(Name,"P%d.Data()",i);

	cout << "Name = " << Plot[i].Data() << endl;

His[i] = (TH1F*)fin->Get(Plot[i].Data());

TF1 *f1 = new TF1("f1","[0] +[1]*x+[2]*x*x+[3]*TMath::Exp(-(x-[4])*(x-[4])/(2*[5]*[5]))",xmin,xmax);


f1->SetParameter(4,1.87);
f1->SetParameter(5,0.02);
/*
f1->SetParameter(0,-78240);
f1->SetParameter(1,66042);
f1->SetParameter(2,-36302);
*/

if( i == 0 || i == 4) f1->SetParameter(5,0.03);
if(i == 2){

f1->SetParameter(3,280);	
	f1->SetParameter(4,1.867);
		f1->SetParameter(5,0.035);

}

//His[i]->Scale(4.0);
  His[i]->GetXaxis()->SetTitleSize(0.05);
  His[i]->GetYaxis()->SetTitleSize(0.05);
His[i]->GetXaxis()->SetTitle("m_{#Lambda_{c}}(GeV/c^{2})");
His[i]->GetXaxis()->CenterTitle();
His[i]->GetYaxis()->SetTitle("Counts/(7 MeV/c^{2})");
   His[i]->GetYaxis()->SetTitleOffset(1.4);
His[i]->GetYaxis()->CenterTitle();
His[i]->SetMaximum(max[i]);
His[i]->SetMinimum(min[i]);
His[i]->GetXaxis()->SetRangeUser(xmin,xmax);
gPad->SetLeftMargin(0.14);
gPad->SetRightMargin(0.05);
gPad->SetBottomMargin(0.13);
gPad->SetTopMargin(0.07);
His[i]->Draw("ex0P");
His[i]->SetTitle("");
His[i]->Fit(f1,"R");


His[i]->SetMarkerSize(1);
His[i]->SetMarkerStyle(8);
His[i]->SetMarkerColor(1);



His[i]->SetMarkerStyle(8);
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
	
	if(i == 2 || i ==3 || i ==4) jet = new TLatex(0.65,0.79,"#DeltaR < 0.5");
		if(i == 0 || i ==1 || i ==5) jet = new TLatex(0.65,0.79,"#DeltaR > 0.5");

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
	leg->AddEntry(His[i],"Data","pl");
	leg->AddEntry(f1,"Fit","l");
	//leg->AddEntry(mass,"B^{+} signal","f");
leg->AddEntry(mass,"D^{0}","f");

	leg->AddEntry(background,"Combinatorial","l");
//	leg->AddEntry(Bkpi,"B #rightarrow J/#psi X","f");
	leg->Draw("same");



c11->Update();





sprintf(Name,"%s.png",Plot[i].Data());


c11->SaveAs(Name);



}
}




int main(const int N, TString P[]) {

	Fit(N,P);
return 0;

}
