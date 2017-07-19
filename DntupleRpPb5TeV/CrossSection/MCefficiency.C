using namespace std;
#include "uti.h"
#include "parameters.h"

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

TString weightfunctiongen = "1";
TString weightfunctionreco = "1";

Float_t hiBinMin,hiBinMax,centMin,centMax;

void MCefficiency(int isPbPb, TString inputmc,
                  TString selmcgen, TString selmcgenacceptance,
                  TString cut_recoonly, TString cut,
                  TString label="PP",TString outputfile="test", int useweight=1,Float_t centmin=0., Float_t centmax=100.)
{
  hiBinMin = centmin*2;
  hiBinMax = centmax*2;
  centMin = centmin;
  centMax = centmax;
  
  if(isPbPb==1)
    {
      selmcgen = selmcgen;
      selmcgenacceptance = selmcgenacceptance;
      cut_recoonly = cut_recoonly;
      cut = cut+"&&Dy>-1.&&Dy<1.&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5";
      /*
      selmcgen = selmcgen+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
      selmcgenacceptance = selmcgenacceptance+Form("&&hiBin>=%f&&hiBin<=%f",hiBinMin,hiBinMax);
      cut_recoonly = cut_recoonly+Form("&&hiBin>=%f&&hiBin<=%f&&Dy>-1.&&Dy<1.",hiBinMin,hiBinMax);
      cut = cut+Form("&&hiBin>=%f&&hiBin<=%f&&Dy>-1.&&Dy<1.",hiBinMin,hiBinMax);
      */
    }
  else
    {
      selmcgen = selmcgen;
      selmcgenacceptance = selmcgenacceptance;
      cut_recoonly = cut_recoonly;
      cut = cut;
    }

  std::cout<<"selmcgen="<<selmcgen<<std::endl;
  std::cout<<"selmcgenacceptance="<<selmcgenacceptance<<std::endl;
  std::cout<<"cut_recoonly"<<cut_recoonly<<std::endl;
  std::cout<<"AAAA cut="<<cut<<std::endl;
  
  std::cout<<"option="<<useweight<<std::endl;
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
 
  TFile* infMC = new TFile(inputmc.Data());
  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  TTree* ntSkim = (TTree*)infMC->Get("ntSkim");
  ntMC->AddFriend(ntGen);
  ntMC->AddFriend(ntSkim);
  

  TTree* nthi = (TTree*)infMC->Get("ntHi");
  ntGen->AddFriend(nthi);
  ntGen->AddFriend(ntSkim);
  nthi->AddFriend(ntMC);
  ntMC->AddFriend(nthi);

// optimal weigths
if(useweight==0) {
    weightfunctiongen="1";
    weightfunctionreco="1";
  }
  // pp weight
  if(useweight==1) {
     weightfunctiongen="(pthatweight)*(maxDgenpt<pthat/1.2)*(0.0116437+Gpt*(0.0602697)+Gpt*Gpt*(-0.00226879)+Gpt*Gpt*Gpt*(3.91035e-05)+Gpt*Gpt*Gpt*Gpt*(-3.0699e-07)+Gpt*Gpt*Gpt*Gpt*Gpt*(8.73234e-10))";
     weightfunctionreco="(pthatweight)*(maxDgenpt<pthat/1.2)*(0.0116437+Dgenpt*(0.0602697)+Dgenpt*Dgenpt*(-0.00226879)+Dgenpt*Dgenpt*Dgenpt*(3.91035e-05)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-3.0699e-07)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*(8.73234e-10))";
  }
  //PbPb weight
  if(useweight==2) {
    weightfunctiongen="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))";
    weightfunctionreco="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))";
  }
  //PbPb low pt weight
  if(useweight==3) {
    weightfunctiongen="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Gpt*(0.0838585)+Gpt*Gpt*(-0.00991096)+Gpt*Gpt*Gpt*(0.000496019)+Gpt*Gpt*Gpt*Gpt*(-8.50065e-06))";
    weightfunctionreco="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Dgenpt*(0.0838585)+Dgenpt*Dgenpt*(-0.00991096)+Dgenpt*Dgenpt*Dgenpt*(0.000496019)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-8.50065e-06))";
  }
  if(useweight==4) {
    weightfunctiongen="(pthatweight)*(maxDgenpt<pthat/1.2)";
    weightfunctionreco="(pthatweight)*(maxDgenpt<pthat/1.2)";
  }

  std::cout<<"fit function parameters="<<weightfunctiongen<<std::endl;

  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D* hPtMCrecoonly = new TH1D("hPtMCrecoonly","",nBins,ptBins);
  TH1D* hPtGen = new TH1D("hPtGen","",nBins,ptBins);
  TH1D* hPtGenAcc = new TH1D("hPtGenAcc","",nBins,ptBins);
  TH1D* hPthat = new TH1D("hPthat","",100,0,500);
  TH1D* hPthatweight = new TH1D("hPthatweight","",100,0,500);
  
  ntMC->Project("hPtMC","Dpt",TCut(weightfunctionreco)*(TCut(cut.Data())&&"(Dgen==23333)"));
  divideBinWidth(hPtMC);
  std::cout<<"step1"<<std::endl;
  ntMC->Project("hPtMCrecoonly","Dpt",TCut(weightfunctionreco)*(TCut(cut_recoonly.Data())&&"(Dgen==23333)"));
  divideBinWidth(hPtMCrecoonly);
  std::cout<<"step2"<<std::endl;
  ntGen->Project("hPtGen","Gpt",TCut(weightfunctiongen)*(TCut(selmcgen.Data())));
  divideBinWidth(hPtGen);
  std::cout<<"step3"<<std::endl;
  ntGen->Project("hPtGenAcc","Gpt",TCut(weightfunctiongen)*(TCut(selmcgenacceptance.Data())));
  divideBinWidth(hPtGenAcc);
  std::cout<<"step4"<<std::endl;


  ntMC->Project("hPthat","pthat","1");
  ntMC->Project("hPthatweight","pthat",TCut("1"));

  hPtMC->Sumw2();
  TH1D* hEff = (TH1D*)hPtMC->Clone("hEff");
  hEff->Divide(hPtGen);

  TH1D* hEffReco = (TH1D*)hPtMCrecoonly->Clone("hEffReco");
  hEffReco->Sumw2();
  hEffReco->Divide(hPtGen);

  TH1D* hEffAcc = (TH1D*)hPtGenAcc->Clone("hEffAcc");
  hEffAcc->Sumw2();
  hEffAcc->Divide(hEffAcc,hPtGen,1,1,"b");
  
  TH1D* hEffSelection = (TH1D*)hPtMC->Clone("hEffSelection");
  hEffSelection->Sumw2();
  hEffSelection->Divide(hEffSelection,hPtMCrecoonly,1,1,"b");
  
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,ptBins[0]-5.,ptBins[nBins]+5.,10.,0,1.5);  
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("acceptance x #epsilon_{reco} x #epsilon_{sel} ");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.9);
  hemptyEff->GetYaxis()->SetTitleOffset(0.95);
  hemptyEff->GetXaxis()->SetTitleSize(0.05);
  hemptyEff->GetYaxis()->SetTitleSize(0.05);
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.035);
  hemptyEff->GetYaxis()->SetLabelSize(0.035);  
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();

  TH2F* hemptyEffAcc=(TH2F*)hemptyEff->Clone("hemptyEffAcc");
  TH2F* hemptyEffReco=(TH2F*)hemptyEff->Clone("hemptyEffReco");
  TH2F* hemptyEffSelection=(TH2F*)hemptyEff->Clone("hemptyEffSelection");
  
  TCanvas*canvasEff=new TCanvas("canvasEff","canvasEff",1000.,500);
  canvasEff->Divide(2,1);
  canvasEff->cd(1);
  
  hemptyEffAcc->SetYTitle("#alpha");
  hemptyEffAcc->Draw();
  hEffAcc->Draw("same");
  canvasEff->cd(2);
  hemptyEff->Draw();
  hEff->Draw("same");
  canvasEff->SaveAs(Form("plotEff/canvasEff_study%s.pdf",Form(label.Data())));
  
  
  TH2F* hemptyPthat=new TH2F("hemptyPthat","",50,0.,500.,10,1e-5,1e9);  
  hemptyPthat->GetXaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->SetTitle("Entries");
  hemptyPthat->GetXaxis()->SetTitle("pthat");
  hemptyPthat->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthat->GetYaxis()->SetTitleOffset(0.95);
  hemptyPthat->GetXaxis()->SetTitleSize(0.05);
  hemptyPthat->GetYaxis()->SetTitleSize(0.05);
  hemptyPthat->GetXaxis()->SetTitleFont(42);
  hemptyPthat->GetYaxis()->SetTitleFont(42);
  hemptyPthat->GetXaxis()->SetLabelFont(42);
  hemptyPthat->GetYaxis()->SetLabelFont(42);
  hemptyPthat->GetXaxis()->SetLabelSize(0.035);
  hemptyPthat->GetYaxis()->SetLabelSize(0.035);  
  hemptyPthat->SetMaximum(2);
  hemptyPthat->SetMinimum(0.);


  TH2F* hemptySpectra=new TH2F("hemptySpectra","",50,0.,130.,10,1,1e5);  
  hemptySpectra->GetXaxis()->CenterTitle();
  hemptySpectra->GetYaxis()->CenterTitle();
  hemptySpectra->GetYaxis()->SetTitle("Entries");
  hemptySpectra->GetXaxis()->SetTitle("p_{T}");
  hemptySpectra->GetXaxis()->SetTitleOffset(0.9);
  hemptySpectra->GetYaxis()->SetTitleOffset(0.95);
  hemptySpectra->GetXaxis()->SetTitleSize(0.05);
  hemptySpectra->GetYaxis()->SetTitleSize(0.05);
  hemptySpectra->GetXaxis()->SetTitleFont(42);
  hemptySpectra->GetYaxis()->SetTitleFont(42);
  hemptySpectra->GetXaxis()->SetLabelFont(42);
  hemptySpectra->GetYaxis()->SetLabelFont(42);
  hemptySpectra->GetXaxis()->SetLabelSize(0.035);
  hemptySpectra->GetYaxis()->SetLabelSize(0.035);  

  TH2F* hemptyPthatWeighted=(TH2F*)hemptyPthat->Clone("hemptyPthatWeighted");
  hemptyPthatWeighted->GetXaxis()->SetTitle("pthat reweighted");
  
  TCanvas*canvasPthat=new TCanvas("canvasPthat","canvasPthat",1000.,500);
  canvasPthat->Divide(2,1);
  canvasPthat->cd(1);
  gPad->SetLogy();
  hemptyPthat->Draw("same");
  hPthat->Draw("same");
  canvasPthat->cd(2);
  gPad->SetLogy();
  hemptyPthatWeighted->Draw();
  hPthatweight->Draw("same");
 // canvasPthat->SaveAs(Form("plotEff/canvasPthat_%s.pdf",Form(label.Data())));
  
  TCanvas*canvasSpectra=new TCanvas("canvasSpectra","canvasSpectra",1000.,500);
  canvasSpectra->Divide(2,1);
  canvasSpectra->cd(1);
  gPad->SetLogy();
  hemptySpectra->Draw();
  hPtMC->Draw("same");
  canvasSpectra->cd(2);
  gPad->SetLogy();
  hemptySpectra->Draw();
  hPtGen->Draw("same");

  TFile *fout=new TFile(outputfile.Data(),"recreate");
  fout->cd();
  hPtGen->Write();
  hEffAcc->Write();
  hEffReco->Write();
  hEffSelection->Write();
  hEff->Write();
  hPtMC->Write();
  fout->Close();  

}

int main(int argc, char *argv[])
{
  if((argc !=12))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }
  
  if(argc == 12)
    MCefficiency(atoi(argv[1]),argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],atoi(argv[9]),atof(argv[10]),atof(argv[11]));
  return 0;
}




