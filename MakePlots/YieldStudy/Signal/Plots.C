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

void Plots(){

const int N = 2;

double lpt =0.5;
double hpt = 1.0;

TCanvas *c = new TCanvas("c", "c",0,0,600,600);
c->cd();

gPad->SetLeftMargin(0.14);
gPad->SetRightMargin(0.08);
gPad->SetBottomMargin(0.10);
gPad->SetTopMargin(0.08);
TFile *fin[N];
	TString label ="pp MC at 5TeV";
/*
TString label = Form(" %f GeV/c < p_{T} < %f GeV/c", lpt, hpt);
  high->GetXaxis()->SetTitle("D mass  (GeV)");
high->GetYaxis()->SetTitle("Counts");
high->SetTitle("D Meson Invariant Mass Distribution"); 
*/


TString pthigh[N] = {"0.5","1.0"};
TString ptlow[N] = {"0","0.5"};
double max[N]={70000,140000};
int j;

TString name[N];
TString outname[N];

for(int i = 0; i < N; i++)
{


j = i + 4;

name[i] = Form("outfile%d.root",j);
outname[i] = Form("outfile%d.png",j);


fin[i] = new TFile(name[i].Data());

	TLatex* tex;
	tex = new TLatex(0.20,0.88,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);


	TLatex* low;
	low = new TLatex(0.20,0.83,Form("%s < D^{0} p_{T} < %s GeV/c",ptlow[i].Data(),pthigh[i].Data()));
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);

TLegend *leg = new TLegend(0.18,0.60,0.42,0.82,NULL,"brNDC");//paper
	leg->SetBorderSize(0);
	//leg->SetTextSize(0.04);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	//leg->SetTextFont(62);
	leg->SetFillStyle(0);
leg->AddEntry(high,"D^{0} Signal");
leg->AddEntry(highbkgd,"Combinatorial");
leg->AddEntry(highswap,"K - #pi Swapped");


high->GetYaxis()->SetTitleOffset(1.5);
high->GetXaxis()->SetTitleOffset(1.0);
high->SetTitle("D^{0} Invariant Mass Distribution");
high->GetXaxis()->SetTitle("D^{0} Mass (GeV/c^{2})");
high->GetYaxis()->SetTitle("Counts");
high->SetTitleSize(0.045,"x");
high->SetTitleSize(0.045,"y");

high->SetMaximum(max[i]);

high->Draw();

highswap->Draw("SAME");
highbkgd->Draw("SAME");
leg->Draw("SAME");
low->Draw("SAME");
tex->Draw("SAME");

c->Update();
c->SaveAs(outname[i].Data());

}


}
