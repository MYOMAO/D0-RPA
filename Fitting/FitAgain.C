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


void FitAgain(){

TFile *fin = new TFile("/Users/zhaozhongshi/Desktop/MIT/Research/CMS/Fitting/Djetanalysis/resultsPbPb_jet80_D10.root");
const int N = 5;
double xbin[6] = {0,0.05,0.1,0.2,0.3,0.5};

double x[N] = {0.025,0.075,0.15,0.25,0.4};
double y[N];
double x_err[N] = {0.025,0.025,0.05,0.05,0.1};
double y_err[N];
int Bin;
int Bin2;
for(int i =0; i < 2; i++)
{



 TCanvas* c= new TCanvas("c","c",0,0,600,600);
 gPad->SetBottomMargin(0.10);
 gPad->SetRightMargin(0.05);
  gPad->SetLeftMargin(0.13);
  TH1F* h =  (TH1F*)fin->Get("hSignalData");

  if(i==0){



  h->SetXTitle("#Delta R");
  h->SetYTitle("Uncorrected D Meson Yield (A. U.)");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetAxisRange(0,1.2);
  h->GetXaxis()->SetTitleOffset(0.9);
  h->GetYaxis()->SetTitleOffset(1.3);
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
  h->SetTitle("");
  h->SetMarkerSize(0.8);
  h->GetXaxis()->SetRangeUser(0,0.5);
  h->SetMarkerStyle(20);
h->SetStats(0);
h->Draw("e");
  }

if(i == 1)
{


  TH1F* h2 = new TH1F("h2","",5,xbin);

  h2->SetXTitle("#Delta R");
  h2->SetYTitle("Uncorrected D Meson Yield (A. U.)");

  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->CenterTitle();
h2->SetAxisRange(0,1.2);

for (int j = 0; j<N; j++)
{

Bin = h->FindBin(x[j]);
cout << "x = " << Bin << endl;
cout << "Bin = " << Bin << endl;

y[j] = h->GetBinContent(Bin);
y_err[j] = h->GetBinError(j);
cout << "y_err = " << y_err[j] << endl;
y_err[j] = y_err[j]/6**0.5;
cout << "y_err = " << y_err[j] << endl;

Bin2 = h2->FindBin(x[j]);

h2->SetBinContent(Bin2,y[j]);
if(j == 3) h2->SetBinContent(Bin2,y[j]+y_err[j]);


h2->SetBinError(Bin2,y_err[j]);
}
 

h2->GetXaxis()->SetTitleOffset(0.9);
  h2->GetYaxis()->SetTitleOffset(1.3);
  h2->GetXaxis()->SetLabelOffset(0.007);
  h2->GetYaxis()->SetLabelOffset(0.007);
  h2->GetXaxis()->SetTitleSize(0.045);
  h2->GetYaxis()->SetTitleSize(0.045);
  h2->GetXaxis()->SetTitleFont(42);
  h2->GetYaxis()->SetTitleFont(42);
  h2->GetXaxis()->SetLabelFont(42);
  h2->GetYaxis()->SetLabelFont(42);
  h2->GetXaxis()->SetLabelSize(0.04);
  h2->GetYaxis()->SetLabelSize(0.04);
  h2->SetTitle("");
  h2->SetMarkerSize(0.8);
  h2->SetMarkerStyle(20);
 h2->SetStats(0);
  h2->GetXaxis()->SetRangeUser(0,0.5);
 h2->SetMarkerColor(2);
   h2->SetLineColor(2);
// h->Sumw2();
h2->Draw("e");


}



 TLatex*  texCol= new TLatex(0.92,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","PbPb"));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

    TLatex* texCms;

if( i == 0 )   texCms = new TLatex(0.20,0.93, "#scale[1.25]{CMS} Preliminary");
if( i == 1 )   texCms = new TLatex(0.20,0.93, "#scale[1.25]{CMS} Projection");

  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();


  tex = new TLatex(0.51,0.83,"Leading Jet |#eta| < 1.6");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw("same");
  TLatex* tex;

  tex = new TLatex(0.51,0.78,"Dmeson |y| < 2.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw("same");
  TLatex* tex;

  tex = new TLatex(0.51,0.73,"D meson p_{T} > 10GeV/c");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();

	TLatex* Leading;
	  Leading = new TLatex(0.51,0.68,"Leading Jet p_{T} > 80GeV/c");
  Leading->SetNDC();
  Leading->SetTextFont(42);
  Leading->SetTextSize(0.04);
 Leading->SetLineWidth(2);
  Leading->Draw("same");
gPad->SetLogy();
 if(i == 0)  c->SaveAs("Plots/PrelimYield.png");
 if(i == 1)  c->SaveAs("Plots/ProjectionYield.png");
 if(i == 0)  c->SaveAs("Plots/PrelimYield.pdf");
 if(i == 1)  c->SaveAs("Plots/ProjectionYield.pdf");

 }


}



