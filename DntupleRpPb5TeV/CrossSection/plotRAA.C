using namespace std;
#include "uti.h"
#include "TLegendEntry.h"
#include "TGraphErrors.h"
#include "../Systematics/systematics.C"
#include <fstream>

void plotRAA(TString fileMB="CrossSectionFullstatsTMVAfprompt/ROOTfiles/outputRAAMB.root", TString file="CrossSectionFullstatsTMVAfprompt/ROOTfiles/outputRAA.root", Float_t centMin=0., Float_t centMax=100)
{
  gStyle->SetOptTitle(0);   
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  const int nPtBins=10;
  Double_t ptbins[nPtBins+1]={1,2,3,4,5,6,7,8,12,16,24};
  ifstream ALICEdata[5];
  TString datafiles[5] = {"center","statlow","stathigh","systlow","systhigh"};
  Double_t ALICEraa[5][nPtBins];
  for(int i=0;i<5;i++)
    {
      Double_t tmp;
      ALICEdata[i].open(Form("ALICEdata/ALICE%s.dat",datafiles[i].Data()));
      for(int j=0;j<nPtBins;j++)
        {
          ALICEdata[i]>>tmp;
          ALICEdata[i]>>ALICEraa[i][j];
        }
    }
  Double_t ptcenter[nPtBins];
  Double_t pt0p4[nPtBins];
  Double_t pt0[nPtBins];
  Double_t ALICEcenter[nPtBins];
  Double_t ALICEstat[nPtBins];
  Double_t ALICEsystlow[nPtBins];
  Double_t ALICEsysthigh[nPtBins];
  for(int i=0;i<nPtBins;i++)
    {
      ptcenter[i]=(ptbins[i+1]+ptbins[i])/2.;
      pt0[i]=0;
      pt0p4[i]=0.4;
      ALICEcenter[i]=ALICEraa[0][i];
      ALICEstat[i]=(ALICEraa[2][i]-ALICEraa[1][i])/2.;
      ALICEsystlow[i]=ALICEraa[0][i]-ALICEraa[3][i];
      ALICEsysthigh[i]=ALICEraa[4][i]-ALICEraa[0][i];
    }

  TGraphErrors* gALICEstat = new TGraphErrors(nPtBins,ptcenter,ALICEcenter,pt0,ALICEstat);
  gALICEstat->SetLineWidth(2);//3
  gALICEstat->SetMarkerSize(1);
  gALICEstat->SetMarkerStyle(20);
  gALICEstat->SetLineColor(kRed);//kGreen+4
  gALICEstat->SetMarkerColor(kRed);//kGreen+4
  TGraphAsymmErrors* gALICEsyst = new TGraphAsymmErrors(nPtBins,ptcenter,ALICEcenter,pt0p4,pt0p4,ALICEsystlow,ALICEsysthigh);
  gALICEsyst->SetFillColor(0);//1
  gALICEsyst->SetFillStyle(0);//0 
  gALICEsyst->SetLineWidth(2);//3
  gALICEsyst->SetMarkerSize(1);
  gALICEsyst->SetMarkerStyle(20);
  gALICEsyst->SetLineColor(kRed);//kGreen+4
  gALICEsyst->SetMarkerColor(kRed);//kGreen+4
  

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");

  /*
  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  */
  
  TCanvas*canvasRAA = new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);//0.200
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);
  //canvasRAA->SetLogx();

  TH2F* hemptyRAA = new TH2F("hemptyRAA","",50,0.,25.,10.,0,2.5);//50,-2,120.,10.,0,1.5
  hemptyRAA->GetXaxis()->CenterTitle();
  hemptyRAA->GetYaxis()->CenterTitle();
  hemptyRAA->GetYaxis()->SetTitle("D^{0} R_{pPb}");
  hemptyRAA->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyRAA->GetXaxis()->SetTitleOffset(1.15);//0.9
  hemptyRAA->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyRAA->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyRAA->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyRAA->GetXaxis()->SetTitleFont(42);
  hemptyRAA->GetYaxis()->SetTitleFont(42);
  hemptyRAA->GetXaxis()->SetLabelFont(42);
  hemptyRAA->GetYaxis()->SetLabelFont(42);
  hemptyRAA->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyRAA->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyRAA->GetXaxis()->SetLabelOffset(0.01);
  hemptyRAA->SetMaximum(2);
  hemptyRAA->SetMinimum(0.);
  hemptyRAA->Draw();

  TLine *line = new TLine(1.0,1,150,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  /*
  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(3001);//0 
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);//kGreen+4
  gNuclearModification->SetMarkerColor(1);//kGreen+4
  gNuclearModification->Draw("5same");
  */
  gNuclearModificationMB->SetFillColor(5);//1
  gNuclearModificationMB->SetFillStyle(3001);//0 
  gNuclearModificationMB->SetLineWidth(1);//3
  gNuclearModificationMB->SetMarkerSize(1);
  gNuclearModificationMB->SetMarkerStyle(21);
  gNuclearModificationMB->SetLineColor(1);//kGreen+4
  gNuclearModificationMB->SetMarkerColor(1);//kGreen+4

  gNuclearModificationMB->Draw("5same");
  
  /*
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->SetLineColor(1);//kGreen+4
  hNuclearModification->SetMarkerColor(1);//kGreen+4
  hNuclearModification->Draw("psame");//same
  */

  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerSize(1);
  hNuclearModificationMB->SetMarkerStyle(21);
  hNuclearModificationMB->SetLineColor(1);//kGreen+4
  hNuclearModificationMB->SetMarkerColor(1);//kGreen+4
  hNuclearModificationMB->Draw("psame");//same

  TLatex* texlumi = new TLatex(0.19,0.936,"27.4 pb^{-1} (5.02 TeV pp) + (5.02 TeV pPb)");
  texlumi->SetNDC();
  //texlumi->SetTextAlign(31);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TString texper="%";
  TLatex * tlatexeff2 = new TLatex(0.49,0.71,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.045);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();

  TLegend *legendSigma = new TLegend(0.47,0.76,0.942953,0.89,"");//0.5100806,0.6268644,0.8084677,0.7805932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(0);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.031);//0.05

  TLegendEntry *ent_Dhighpt = legendSigma->AddEntry(gNuclearModificationMB,"CMS -1<y_{CM}<1","pf");
   ent_Dhighpt->SetTextFont(42);
   ent_Dhighpt->SetTextSize(0.038);//0.03
  TLegendEntry *ent_ALICE = legendSigma->AddEntry(gALICEsyst,"ALICE -0.96<y_{CM}<0.04","pf");
   ent_ALICE->SetTextFont(42);
   ent_ALICE->SetTextSize(0.038);//0.03

   legendSigma->Draw();

   canvasRAA->SaveAs("plotRAA/RpPb.pdf");
   canvasRAA->SaveAs("plotRAA/RpPb.png");

   gALICEsyst->Draw("5same");
   gALICEstat->Draw("pesame");

   canvasRAA->SaveAs("plotRAA/RpPbcompALICE.pdf");
   canvasRAA->SaveAs("plotRAA/RpPbcompALICE.png");
   
}

int main(int argc, char *argv[])
{

  if(argc==5)
    {
      plotRAA(argv[1], argv[2], atof(argv[3]), atof(argv[4]));
      return 0;
    }
  else
    {
      cout<<"  ERROR: Wrong number of inputs: plotRAA.C"<<endl;
      return 1;
    }
}
