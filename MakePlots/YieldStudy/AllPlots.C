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

void AllPlots(){

double lpt =0.5;
double hpt = 1.0;

TCanvas *c = new TCanvas("c", "c",0,0,600,600);
gPad->SetLeftMargin(0.14);
gPad->SetRightMargin(0.08);
gPad->SetBottomMargin(0.10);
gPad->SetTopMargin(0.08);
TFile *fin = new TFile("output.root");
TString label ="pp MC at 5TeV";
/*
TString label = Form(" %f GeV/c < p_{T} < %f GeV/c", lpt, hpt);
  high->GetXaxis()->SetTitle("D mass  (GeV)");
high->GetYaxis()->SetTitle("Counts");
high->SetTitle("D Meson Invariant Mass Distribution"); 
*/
	TLatex* tex;
	tex = new TLatex(0.20,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	TLatex* mid;
	mid = new TLatex(0.20,0.75,"0.5 < p_{T} < 1");
	mid->SetNDC();
	mid->SetTextFont(42);
	mid->SetTextSize(0.04);
	mid->SetLineWidth(2);

	TLatex* low;
	low = new TLatex(0.20,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);

TLegend *leg = new TLegend(0.20,0.65,0.45,0.75,NULL,"brNDC");//paper
	leg->SetBorderSize(0);
	//leg->SetTextSize(0.04);
	leg->SetTextSize(0.04);
	leg->SetTextFont(42);
	//leg->SetTextFont(62);
	leg->SetFillStyle(0);
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

//h5->SetFillStyle(3001);
//h7->SetFillStyle(3001);

d3->SetLineWidth(3);
d3->SetLineColor(kGreen);
d3->Draw("SAME");
h5->SetLineWidth(3);
h7->SetLineWidth(3);

h5->SetLineColor(kRed);
h7->SetLineColor(kBlue);

h5->SetTitle("Track 1 p_{T} Distribution");
   h5->GetYaxis()->SetTitleOffset(1.5);
      h5->GetXaxis()->SetTitleOffset(1.0);

h5->GetXaxis()->SetTitle("Leading Track p_{T} (GeV/c)");
h5->GetYaxis()->SetTitle("Probability");
h5->SetTitleSize(0.045,"x");
h5->SetTitleSize(0.045,"y");

h5->Draw();
h7->Draw("SAME");
d3->SetLineWidth(3);
d3->SetLineColor(kGreen);
d3->Draw("SAME");


tex->Draw("SAME");
low->Draw("SAME");
leg->Draw("SAME");

c->Update();
c->SaveAs("lowptplots/Track1PT.png");


//leg->AddEntry(highswap,"Swapped");

//Plot2 //
h6->SetLineWidth(3);
h8->SetLineWidth(3);

h6->SetLineColor(kRed);
h8->SetLineColor(kBlue);

h6->SetTitle("Track 2 p_{T} Distribution");
h6->GetYaxis()->SetTitleOffset(1.5);
h6->GetXaxis()->SetTitleOffset(1.0);

h6->GetXaxis()->SetTitle("Low p_{T} Track p_{T} (GeV/c)");
h6->GetYaxis()->SetTitle("Probability");
h6->SetTitleSize(0.045,"x");
h6->SetTitleSize(0.045,"y");

h6->Draw();
h8->Draw("SAME");
d4->SetLineWidth(3);
d4->SetLineColor(kGreen);
d4->Draw("SAME");

tex->Draw("SAME");
low->Draw("SAME");
leg->Clear();

leg = new TLegend(0.18,0.65,0.43,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");



c->Update();
c->SaveAs("lowptplots/Track2PT.png");

//End//

//Plot3 //
h9->SetLineWidth(3);
h10->SetLineWidth(3);

h9->SetLineColor(kRed);
h10->SetLineColor(kBlue);

h9->SetTitle("Confident Level Distribution");
h9->GetYaxis()->SetTitleOffset(1.5);
h9->GetXaxis()->SetTitleOffset(1.0);

h9->GetXaxis()->SetTitle("Confident Level");
h9->GetYaxis()->SetTitle("Probability");
h9->SetTitleSize(0.045,"x");
h9->SetTitleSize(0.045,"y");

h9->Draw();
h10->Draw("SAME");
d5->SetLineWidth(3);
d5->SetLineColor(kGreen);
d5->Draw("SAME");

tex->Draw("SAME");
low->Draw("SAME");
leg->Clear();

leg = new TLegend(0.20,0.45,0.45,0.55,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");



c->Update();
c->SaveAs("lowptplots/Confident.png");

//End//



//Plot4 //
h11->SetLineWidth(3);

h11->SetLineColor(kRed);

h11->SetTitle("Angle #alpha Distribution");
h11->GetYaxis()->SetTitleOffset(1.5);
h11->GetXaxis()->SetTitleOffset(1.0);

h11->GetXaxis()->SetTitle("#alpha");
h11->GetYaxis()->SetTitle("Probability");
h11->SetTitleSize(0.045,"x");
h11->SetTitleSize(0.045,"y");

h11->Draw();

h12->SetLineWidth(3);

h12->SetLineColor(kBlue);
d5->SetLineWidth(3);
d5->SetLineColor(kGreen);
d5->Draw("SAME");

/*
d6->SetLineWidth(3);
d6->SetLineColor(kGreen);
d6->Draw("SAME");
*/
h12->Draw("SAME");
	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");
leg->Clear();

leg = new TLegend(0.62,0.65,0.87,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");



c->Update();
c->SaveAs("lowptplots/Alpha.png");

//End//

//Plot5 //
//

h13->SetLineWidth(3);
h13->SetLineColor(kRed);


h13->SetTitle("Decay Length Distribution");
h13->GetYaxis()->SetTitleOffset(1.5);
h13->GetXaxis()->SetTitleOffset(1.0);

h13->GetXaxis()->SetTitle("Decay Length (#mum)");
h13->GetYaxis()->SetTitle("Probability");
h13->SetTitleSize(0.045,"x");
h13->SetTitleSize(0.045,"y");

h13->Draw();
h14->SetLineWidth(3);
h14->SetLineColor(kBlue);
d7->SetLineWidth(3);
d7->SetLineColor(kGreen);
d7->Draw("SAME");

h14->Draw("SAME");

leg->Clear();

leg = new TLegend(0.50,0.65,0.75,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/DecayLength.png");

//End//


//Plot6 //

h15->SetLineWidth(3);
h15->SetLineColor(kRed);


h15->SetTitle("Decay Length Error Distribution");
h15->GetYaxis()->SetTitleOffset(1.5);
h15->GetXaxis()->SetTitleOffset(1.0);

h15->GetXaxis()->SetTitle("Decay Length Error(#mum)");
h15->GetYaxis()->SetTitle("Probability");
h15->SetTitleSize(0.045,"x");
h15->SetTitleSize(0.045,"y");

h15->Draw();
h16->SetLineWidth(3);
h16->SetLineColor(kBlue);

h16->Draw("SAME");
d8->SetLineWidth(3);
d8->SetLineColor(kGreen);
d8->Draw("SAME");

leg->Clear();

leg = new TLegend(0.50,0.65,0.75,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/DecayLengthError.png");

//End//



//Plot7 //

h21->SetLineWidth(3);
h21->SetLineColor(kRed);


h21->SetTitle("Decay Length Ratio Distribution");
h21->GetYaxis()->SetTitleOffset(1.5);
h21->GetXaxis()->SetTitleOffset(1.0);

h21->GetXaxis()->SetTitle("Decay Length Ratio");
h21->GetYaxis()->SetTitle("Probability");
h21->SetTitleSize(0.045,"x");
h21->SetTitleSize(0.045,"y");

h21->Draw();
h22->SetLineWidth(3);
h22->SetLineColor(kBlue);
d11->SetLineWidth(3);
d11->SetLineColor(kGreen);
d11->Draw("SAME");

h22->Draw("SAME");

leg->Clear();

leg = new TLegend(0.50,0.65,0.75,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/DecayLengthRatio.png");

//End//


//Plot8 //

h17->SetLineWidth(3);
h17->SetLineColor(kRed);


h17->SetTitle("Leading Track p_{T} Error Distribution");
h17->GetYaxis()->SetTitleOffset(1.5);
h17->GetXaxis()->SetTitleOffset(1.0);

h17->GetXaxis()->SetTitle("Leading Track p_{T} Error (p_{T})");
h17->GetYaxis()->SetTitle("Probability");
h17->SetTitleSize(0.045,"x");
h17->SetTitleSize(0.045,"y");

h17->Draw();
h18->SetLineWidth(3);
h18->SetLineColor(kBlue);
d9->SetLineWidth(3);
d9->SetLineColor(kGreen);
d9->Draw("SAME");

h18->Draw("SAME");

leg->Clear();

leg = new TLegend(0.50,0.65,0.75,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/Track1Err.png");

//End//


//Plo08 //

h19->SetLineWidth(3);
h19->SetLineColor(kRed);
h1->SetLineWidth(3);
h1->SetLineColor(kRed);

h1->SetTitle("Track 1 #eta Distribution");
h1->GetYaxis()->SetTitleOffset(1.5);
h1->GetXaxis()->SetTitleOffset(1.0);

h1->GetXaxis()->SetTitle("Track 1 #eta");
h1->GetYaxis()->SetTitle("Probability");
h1->SetTitleSize(0.045,"x");
h1->SetTitleSize(0.045,"y");

h1->Draw();
h1->SetLineWidth(3);
h2->SetLineColor(kBlue);
d1->SetLineWidth(3);
d1->SetLineColor(kGreen);
d1->Draw("SAME");

h2->Draw("SAME");

leg->Clear();

leg = new TLegend(0.55,0.65,0.80,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.55,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.55,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/Track1Eta.png");

//End//


h19->SetTitle("Lower p_{T} Track p_{T} Error Distribution");
h19->GetYaxis()->SetTitleOffset(1.5);
h19->GetXaxis()->SetTitleOffset(1.0);

h19->GetXaxis()->SetTitle("Lower p_{T} Track p_{T} Error (p_{T})");
h19->GetYaxis()->SetTitle("Probability");
h19->SetTitleSize(0.045,"x");
h19->SetTitleSize(0.045,"y");



h19->Draw();
h20->SetLineWidth(3);
h20->SetLineColor(kBlue);
d10->SetLineWidth(3);
d10->SetLineColor(kGreen);
d10->Draw("SAME");

h20->Draw("SAME");

leg->Clear();

leg = new TLegend(0.50,0.65,0.75,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/Track2Err.png");

//End//

//Plot10//

asyms->SetLineWidth(3);
asyms->SetLineColor(kRed);


asyms->SetTitle("p_{T} Asymmetry Distribution");
asyms->GetYaxis()->SetTitleOffset(1.5);
asyms->GetXaxis()->SetTitleOffset(1.0);

asyms->GetXaxis()->SetTitle("(p_{T}^{1} - p_{T}^{2})/(p_{T}^{1} + p_{T}^{2})");
asyms->GetYaxis()->SetTitle("Probability");
asyms->SetTitleSize(0.045,"x");
asyms->SetTitleSize(0.045,"y");

asyms->Draw();
asymb->SetLineWidth(3);
asymb->SetLineColor(kBlue);

asymb->Draw("SAME");
asymd->Scale(1.0/asymd->Integral());
asymd->SetLineWidth(3);
asymd->SetLineColor(kGreen);
asymd->Draw("SAME");

leg->Clear();

leg = new TLegend(0.50,0.65,0.75,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.50,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.50,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/TrackAsymetry.png");

//End//


//End//


h29->SetLineWidth(3);
h29->SetLineColor(kRed);


h29->SetTitle("Track 1 CosTheta Distribution");
h29->GetYaxis()->SetTitleOffset(1.5);
h29->GetXaxis()->SetTitleOffset(1.0);

h29->GetXaxis()->SetTitle("Track 1 Cos(thetastar)");
h29->GetYaxis()->SetTitle("Probability");
h29->SetTitleSize(0.045,"x");
h29->SetTitleSize(0.045,"y");

h29->Draw();
h29->SetLineWidth(3);
h30->SetLineColor(kBlue);

h30->Draw("SAME");
d15->SetLineWidth(3);
d15->SetLineColor(kGreen);
d15->Draw("SAME");

leg->Clear();

leg = new TLegend(0.25,0.65,0.50,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.25,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.25,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/CosTheta1.png");

//End//


h31->SetLineWidth(3);
h31->SetLineColor(kRed);

h31->SetTitle("Track 2 CosThetaStar Distribution");
h31->GetYaxis()->SetTitleOffset(1.5);
h31->GetXaxis()->SetTitleOffset(1.0);

h31->GetXaxis()->SetTitle("Track 2 Cos(thetastar)");
h31->GetYaxis()->SetTitle("Probability");
h31->SetTitleSize(0.045,"x");
h31->SetTitleSize(0.045,"y");

h31->Draw();
h31->SetLineWidth(3);
h32->SetLineColor(kBlue);
d16->SetLineWidth(3);
d16->SetLineColor(kGreen);
d16->Draw("SAME");

h32->Draw("SAME");

leg->Clear();

leg = new TLegend(0.55,0.65,0.80,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.55,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.55,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/CosTheta2.png");

//End//







h33->SetLineWidth(3);
h33->SetLineColor(kRed);

h33->SetTitle("Track 1 BDT (dE/dx) Distribution");
h33->GetYaxis()->SetTitleOffset(1.5);
h33->GetXaxis()->SetTitleOffset(1.0);

h33->GetXaxis()->SetTitle("Track 1 BDT");
h33->GetYaxis()->SetTitle("Probability");
h33->SetTitleSize(0.045,"x");
h33->SetTitleSize(0.045,"y");

h33->Draw();
h33->SetLineWidth(3);
h34->SetLineColor(kBlue);
d17->SetLineWidth(3);
d17->SetLineColor(kGreen);
d17->Draw("SAME");

h34->Draw("SAME");

leg->Clear();

leg = new TLegend(0.55,0.65,0.80,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");
leg->Draw("SAME");

	tex = new TLatex(0.55,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.55,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/BDT1.png");

//End//



h35->SetLineWidth(3);
h35->SetLineColor(kRed);

h35->SetTitle("Track 2 BDT (dE/dx) Distribution");
h35->GetYaxis()->SetTitleOffset(1.5);
h35->GetXaxis()->SetTitleOffset(1.0);

h35->GetXaxis()->SetTitle("Track 2 BDT");
h35->GetYaxis()->SetTitle("Probability");
h35->SetTitleSize(0.045,"x");
h35->SetTitleSize(0.045,"y");

h35->Draw();
h35->SetLineWidth(3);
h36->SetLineColor(kBlue);
d18->SetLineWidth(3);
d18->SetLineColor(kGreen);
d18->Draw("SAME");

h36->Draw("SAME");

leg->Clear();

leg = new TLegend(0.55,0.65,0.80,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.55,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.55,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/BDT2.png");

//End//


h1->SetLineWidth(3);
h1->SetLineColor(kRed);

h1->SetTitle("Track 1 #eta Distribution");
h1->GetYaxis()->SetTitleOffset(1.5);
h1->GetXaxis()->SetTitleOffset(1.0);

h1->GetXaxis()->SetTitle("Track 1 #eta");
h1->GetYaxis()->SetTitle("Probability");
h1->SetTitleSize(0.045,"x");
h1->SetTitleSize(0.045,"y");

h1->Draw();
h1->SetLineWidth(3);
h2->SetLineColor(kBlue);
d1->SetLineWidth(3);
d1->SetLineColor(kGreen);
d1->Draw("SAME");

h2->Draw("SAME");

leg->Clear();

leg = new TLegend(0.55,0.65,0.80,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.55,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.55,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/Track1Eta.png");

//End//

h3->SetLineWidth(3);
h3->SetLineColor(kRed);

h3->SetTitle("Track 2 #eta Distribution");
h3->GetYaxis()->SetTitleOffset(1.5);
h3->GetXaxis()->SetTitleOffset(1.0);

h3->GetXaxis()->SetTitle("Track 2 #eta");
h3->GetYaxis()->SetTitle("Probability");
h3->SetTitleSize(0.045,"x");
h3->SetTitleSize(0.045,"y");

h3->Draw();
h3->SetLineWidth(3);
h4->SetLineColor(kBlue);
d2->SetLineWidth(3);
d2->SetLineColor(kGreen);
d2->Draw("SAME");

h4->Draw("SAME");

leg->Clear();

leg = new TLegend(0.55,0.65,0.80,0.75,NULL,"brNDC");
leg->AddEntry(h5,"MC Signal");
leg->AddEntry(h7,"MC Background");
leg->AddEntry(d3,"Data SideBand");

leg->Draw("SAME");

	tex = new TLatex(0.55,0.85,label.Data());
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.04);
	tex->SetLineWidth(2);

	low = new TLatex(0.55,0.80,"D^{0} p_{T} < 0.5 GeV/c");
	low->SetNDC();
	low->SetTextFont(42);
	low->SetTextSize(0.04);
	low->SetLineWidth(2);
tex->Draw("SAME");
low->Draw("SAME");


c->Update();
c->SaveAs("lowptplots/Track2Eta.png");

//End//

}

