using namespace std;
#include "uti.h"

void CombineplotPnNP(TString collision="PbPb", TString outputfilePMB="test.root", TString outputfileP="test.root", TString outputfileNPMB="test.root", TString outputfileNP="test.root", Float_t centMin=0.,Float_t centMax=100.)
{
  gStyle->SetOptStat(0);
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.8);
  gStyle->SetTitleOffset(1.3,"X");
  gStyle->SetTitleOffset(1.8,"Y");

  Bool_t isPbPb = true;
  if(collision!="PbPb") isPbPb = false;

  TFile* infPMB = new TFile(Form("%s",outputfilePMB.Data()));
  TFile* infP = new TFile(Form("%s",outputfileP.Data()));
  TFile* infNPMB = new TFile(Form("%s",outputfileNPMB.Data()));
  TFile* infNP = new TFile(Form("%s",outputfileNP.Data()));

  TH1D* hEffAccPMB = (TH1D*)infPMB->Get("hEffAcc");    hEffAccPMB->SetName("hEffAccPMB");
  TH1D* hEffPMB = (TH1D*)infPMB->Get("hEff");          hEffPMB->SetName("hEffPMB");
  TH1D* hEffAccNPMB = (TH1D*)infNPMB->Get("hEffAcc");  hEffAccNPMB->SetName("hEffAccNPMB");
  TH1D* hEffNPMB = (TH1D*)infNPMB->Get("hEff");        hEffNPMB->SetName("hEffNPMB");

  TH1D* hEffAccP = (TH1D*)infP->Get("hEffAcc");    hEffAccP->SetName("hEffAccP");
  TH1D* hEffP = (TH1D*)infP->Get("hEff");          hEffP->SetName("hEffP");
  TH1D* hEffAccNP = (TH1D*)infNP->Get("hEffAcc");  hEffAccNP->SetName("hEffAccNP");
  TH1D* hEffNP = (TH1D*)infNP->Get("hEff");        hEffNP->SetName("hEffNP");

  /*
  hEffAccP->SetTitle(";p_{T} (GeV/c);#alpha");
  hEffAccNP->SetTitle(";p_{T} (GeV/c);#alpha");
  hEffP->SetTitle(";p_{T} (GeV/c);#alpha x #epsilon_{reco} x #epsilon_{sel}");
  hEffNP->SetTitle(";p_{T} (GeV/c);#alpha x #epsilon_{reco} x #epsilon_{sel}");
  */

  hEffAccPMB->SetLineColor(2);
  hEffAccPMB->SetMarkerColor(2);
  hEffPMB->SetLineColor(2);
  hEffPMB->SetMarkerColor(2);
  hEffAccNPMB->SetLineColor(4);
  hEffAccNPMB->SetMarkerColor(4);
  hEffNPMB->SetLineColor(4);
  hEffNPMB->SetMarkerColor(4);

  hEffAccP->SetLineColor(2);
  hEffAccP->SetMarkerColor(2);
  hEffP->SetLineColor(2);
  hEffP->SetMarkerColor(2);
  hEffAccNP->SetLineColor(4);
  hEffAccNP->SetMarkerColor(4);
  hEffNP->SetLineColor(4);
  hEffNP->SetMarkerColor(4);

  TH2F* hemptyEff = new TH2F("hemptyEff","",50,0.,102.,10.,0,1.0);  
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("#alpha x #epsilon_{reco} x #epsilon_{sel}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);
  hemptyEff->GetXaxis()->SetTitleSize(0.055);
  hemptyEff->GetYaxis()->SetTitleSize(0.055);
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);

  TH2F* hemptyEffAcc = new TH2F("hemptyEffAcc","",50,0.,102.,10.,0,1.0);  
  hemptyEffAcc->GetXaxis()->CenterTitle();
  hemptyEffAcc->GetYaxis()->CenterTitle();
  hemptyEffAcc->GetYaxis()->SetTitle("#alpha");
  hemptyEffAcc->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEffAcc->GetXaxis()->SetTitleOffset(0.95);
  hemptyEffAcc->GetYaxis()->SetTitleOffset(1.15);
  hemptyEffAcc->GetXaxis()->SetTitleSize(0.055);
  hemptyEffAcc->GetYaxis()->SetTitleSize(0.055);
  hemptyEffAcc->GetXaxis()->SetTitleFont(42);
  hemptyEffAcc->GetYaxis()->SetTitleFont(42);

  /*
  hEffAccP->SetMinimum(0.);
  hEffAccP->SetMaximum(1.5);
  hEffP->SetMinimum(0.);
  hEffP->SetMaximum(1.5);
  hEffAccP->GetXaxis()->SetTitleOffset(0.95);//0.9
  hEffAccP->GetYaxis()->SetTitleOffset(1.15);//1.
  hEffAccP->GetXaxis()->SetTitleSize(0.055);//0.045
  hEffAccP->GetYaxis()->SetTitleSize(0.055);//0.045
  hEffAccP->GetXaxis()->SetTitleFont(42);
  hEffAccP->GetYaxis()->SetTitleFont(42);
  hEffP->GetXaxis()->SetTitleOffset(0.95);//0.9
  hEffP->GetYaxis()->SetTitleOffset(1.15);//1.
  hEffP->GetXaxis()->SetTitleSize(0.055);//0.045
  hEffP->GetYaxis()->SetTitleSize(0.055);//0.045
  hEffP->GetXaxis()->SetTitleFont(42);
  hEffP->GetYaxis()->SetTitleFont(42);
  */

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  TLatex* texCol = new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV",collision.Data()));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);

  TString texper = "%";
  TLatex* texCent = new TLatex(0.57,0.84, Form("Centrality %.0f - %.0f%s",centMin,centMax,texper.Data()));
  texCent->SetNDC();
  texCent->SetTextAlign(12);
  texCent->SetTextSize(0.045);
  texCent->SetTextFont(42);

  TCanvas* cEffAcc = new TCanvas("cEffAcc","",600,600);
  TLegend* legEffAcc = new TLegend(0.55,0.70,0.90,0.81);
  legEffAcc->SetBorderSize(0);
  legEffAcc->SetFillStyle(0);
  legEffAcc->AddEntry(hEffAccP,"Prompt","pl");
  legEffAcc->AddEntry(hEffAccNP,"Non-prompt","pl");
  hemptyEffAcc->Draw();
  hEffAccPMB->Draw("same");
  hEffAccP->Draw("same");
  hEffAccNPMB->Draw("same");
  hEffAccNP->Draw("same");
  /*
  hEffAccP->Draw();
  hEffAccNP->Draw("same");
  */
  texCms->Draw();
  texCol->Draw();
  if(isPbPb) texCent->Draw();
  legEffAcc->Draw("same");
  if(!isPbPb) cEffAcc->SaveAs(Form("plotEff/canvasEffAcc_PnNPCombine_%s.pdf",collision.Data()));
  else cEffAcc->SaveAs(Form("plotEff/canvasEffAcc_PnNPCombine_%s_%.0f_%.0f.pdf",collision.Data(),centMin,centMax));

  TCanvas* cEff = new TCanvas("cEff","",600,600);
  TLegend* legEff = new TLegend(0.55,0.70,0.90,0.81);
  legEff->SetBorderSize(0);
  legEff->SetFillStyle(0);
  legEff->AddEntry(hEffP,"Prompt","pl");
  legEff->AddEntry(hEffNP,"Non-prompt","pl");
  hemptyEff->Draw();
  hEffPMB->Draw("same");
  hEffP->Draw("same");
  hEffNPMB->Draw("same");
  hEffNP->Draw("same");
  /*
  hEffP->Draw();
  hEffNP->Draw("same");
  */
  texCms->Draw();
  texCol->Draw();
  if(isPbPb) texCent->Draw();
  legEff->Draw("same");
  if(!isPbPb) cEff->SaveAs(Form("plotEff/canvasEff_PnNPCombine_%s.pdf",collision.Data()));
  else cEff->SaveAs(Form("plotEff/canvasEff_PnNPCombine_%s_%.0f_%.0f.pdf",collision.Data(),centMin,centMax));
}

int main(int argc, char* argv[])
{
  if(argc==8)
    {
      CombineplotPnNP(argv[1],argv[2],argv[3],argv[4],argv[5],atof(argv[6]),atof(argv[7]));
      return 1;
    }
  else if(argc==6)
    {
      CombineplotPnNP(argv[1],argv[2],argv[3],argv[4],argv[5]);
      return 1;
    }
  else
    {
      std::cout<<"Invalid parameter number"<<std::endl;
      return 0;
    }
}
