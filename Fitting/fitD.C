#include "uti.h"
#include "parameters.h"
#include "TF1.h"

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

TString weight;
TString weightgen;
TString seldata;
TString selmc;
TString selmceff;
TString selmcgen;
TString collisionsystem;
Float_t hiBinMin,hiBinMax,centMin,centMax;

void fitD(int usePbPb, TString inputdata, TString inputmc, TString trgselection,
          TString cut, TString cutmcgen,
          int isMC, Double_t luminosity, int doweight, TString collsyst,
          TString outputfile,
          Float_t centmin=0., Float_t centmax=0.)
{
  collisionsystem=collsyst;
  hiBinMin = centmin*2;
  hiBinMax = centmax*2;
  centMin = centmin;
  centMax = centmax;
  
  double ErrorOnSigma(double width, double errwidth, double smear, double errsmearing);
  
  if (!(usePbPb==1||usePbPb==0)) std::cout<<"ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, you are using a non valid isPbPb option"<<std::endl;
  bool isPbPb=(bool)(usePbPb);

  if(!isPbPb)
    {
      seldata = Form("%s&&%s",trgselection.Data(),cut.Data());
      selmceff = Form("%s",cut.Data());
      selmcgen = Form("%s",cutmcgen.Data());
    }
  else
    {
      seldata = Form("%s&&%s&&hiBin>=%f&&hiBin<=%f&&Dy>-0.535&&Dy<1.465",trgselection.Data(),cut.Data(),hiBinMin,hiBinMax);
      selmceff = Form("%s&&abs(Dy)<1.",cut.Data());
      selmcgen = Form("%s&&abs(Dy)<1.",cutmcgen.Data());
      //selmceff = Form("%s&&hiBin>=%f&&hiBin<=%f&&abs(Dy)<1.",cut.Data(),hiBinMin,hiBinMax);
      //selmcgen = Form("%s&&hiBin>=%f&&hiBin<=%f&&abs(Dy)<1.",cutmcgen.Data(),hiBinMin,hiBinMax);
    }

  selmc = Form("%s",cut.Data());

  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);

  void clean0 (TH1D* h);
  TF1* fit (TTree* nt, TTree* ntMC, double ptmin, double ptmax, int isMC,bool, TF1* &total,Float_t centmin, Float_t centmax);

  if(doweight==0) {
     weightgen="1";
     weight="1";
  }

  // pp weight
  if(doweight==1) {
     weightgen="(pthatweight)*(maxDgenpt<pthat/1.2)*(0.0116437+Gpt*(0.0602697)+Gpt*Gpt*(-0.00226879)+Gpt*Gpt*Gpt*(3.91035e-05)+Gpt*Gpt*Gpt*Gpt*(-3.0699e-07)+Gpt*Gpt*Gpt*Gpt*Gpt*(8.73234e-10))";
     weight="(pthatweight)*(maxDgenpt<pthat/1.2)*(0.0116437+Dgenpt*(0.0602697)+Dgenpt*Dgenpt*(-0.00226879)+Dgenpt*Dgenpt*Dgenpt*(3.91035e-05)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-3.0699e-07)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*Dgenpt*(8.73234e-10))";
  }
  //PbPb weight
  if(doweight==2) {
    weightgen="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))";
    weight="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))";
  }
  //PbPb low pt weight
  if(doweight==3) {
   weightgen="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Gpt*(0.0838585)+Gpt*Gpt*(-0.00991096)+Gpt*Gpt*Gpt*(0.000496019)+Gpt*Gpt*Gpt*Gpt*(-8.50065e-06))";
   weight="(pthatweight)*(maxDgenpt<pthat/1.2)*(6.14981+hiBin*(-0.156513)+hiBin*hiBin*(0.00149127)+hiBin*hiBin*hiBin*(-6.29087e-06)+hiBin*hiBin*hiBin*hiBin*(9.90029e-09))*(-0.00600791+Dgenpt*(0.0838585)+Dgenpt*Dgenpt*(-0.00991096)+Dgenpt*Dgenpt*Dgenpt*(0.000496019)+Dgenpt*Dgenpt*Dgenpt*Dgenpt*(-8.50065e-06))";
  }
  if(doweight<0 || doweight>4) std::cout<<"ERROR, this weighting option is not defined"<<std::endl;
  
  std::cout<<"we are using weight="<<weight<<std::endl;
  
  TFile* inf = new TFile(inputdata.Data());
  TFile* infMC = new TFile(inputmc.Data());

  TTree* nt = (TTree*)inf->Get("ntDkpi");
  nt->AddFriend("ntHlt");
  nt->AddFriend("ntHi");
  nt->AddFriend("ntSkim");

  TTree* ntGen = (TTree*)infMC->Get("ntGen");
  ntGen->AddFriend("ntHlt");
  ntGen->AddFriend("ntHi");

  TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
  ntMC->AddFriend("ntHlt");
  ntMC->AddFriend("ntHi");
  ntMC->AddFriend("ntSkim");
  ntMC->AddFriend(ntGen);
  
  TH1D* hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D* hPtRecoTruth = new TH1D("hPtRecoTruth","",nBins,ptBins);
  TH1D* hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D* hPtGen = new TH1D("hPtGen","",nBins,ptBins);

  TH1D* hMean = new TH1D("hMean","",nBins,ptBins);                       
  TH1D* hSigmaGaus1 = new TH1D("hSigmaGaus1","",nBins,ptBins); 
  TH1D* hSigmaGaus2 = new TH1D("hSigmaGaus2","",nBins,ptBins); 
  TH1D* hRelMagnGausOverGaus2 = new TH1D("hRelMagnGausOverGaus2","",nBins,ptBins); 
  TH1D* hSigmaGausRefl = new TH1D("hSigmaGausRefl","",nBins,ptBins); 
  TH1D* hRelMagnReflOverSignal = new TH1D("hRelMagnReflOverSignal","",nBins,ptBins); 
  TH1D* hDcandidates = new TH1D("hDcandidates","",nBins,ptBins);
  TF1 *totalmass;
  
  //mass [1]
  //yield total signal [7]
  //relative yield first gaussian [9]
  //sigma first gaussian signal [2]*(1+[11])
  //relative yield second gaussian 1-[9]
  //sigma second gaussian signal [10]*(1+[11])
  //yield reflection gaussian 1-[7]
  //sigma reflection gaussian [8]*(1+[11])
  
  //mi serve
  //mean [1]
  //sigma seconda gaussiana [10]*(1+[11])
  //sigma reflected gaussiana [8]*(1+[11])
  //relative signal/swapped

  for(int i=0;i<nBins;i++)
    {
      TF1* f = fit(nt,ntMC,ptBins[i],ptBins[i+1],isMC,isPbPb, totalmass,centmin, centmax);
      double yield = f->Integral(minhisto,maxhisto)/binwidthmass;
      double yieldErr = f->Integral(minhisto,maxhisto)/binwidthmass*f->GetParError(0)/f->GetParameter(0);
      hPt->SetBinContent(i+1,yield/(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,yieldErr/(ptBins[i+1]-ptBins[i]));
      hMean->SetBinContent(i+1,totalmass->GetParameter(1));
      hMean->SetBinError(i+1,totalmass->GetParError(1));
      
      double errorsigma1=ErrorOnSigma(totalmass->GetParameter(2),totalmass->GetParError(2),totalmass->GetParameter(11),totalmass->GetParError(11));
      double errorsigma2=ErrorOnSigma(totalmass->GetParameter(10),totalmass->GetParError(10),totalmass->GetParameter(11),totalmass->GetParError(11));
      double errorrefl=ErrorOnSigma(totalmass->GetParameter(8),totalmass->GetParError(8),totalmass->GetParameter(11),totalmass->GetParError(11));
      
      hSigmaGaus1->SetBinContent(i+1,totalmass->GetParameter(2)*(1+totalmass->GetParameter(11)));
      hSigmaGaus1->SetBinError(i+1,errorsigma1);
      hSigmaGaus2->SetBinContent(i+1,totalmass->GetParameter(10)*(1+totalmass->GetParameter(11)));
      hSigmaGaus2->SetBinError(i+1,errorsigma2);
      hRelMagnGausOverGaus2->SetBinContent(i+1,totalmass->GetParameter(9));
      hRelMagnGausOverGaus2->SetBinError(i+1,totalmass->GetParError(9));
      hSigmaGausRefl->SetBinContent(i+1,totalmass->GetParameter(8)*(1+totalmass->GetParameter(11)));
      hSigmaGausRefl->SetBinError(i+1,errorrefl);
      hRelMagnReflOverSignal->SetBinContent(i+1,totalmass->GetParameter(7));
      hRelMagnReflOverSignal->SetBinError(i+1,totalmass->GetParError(7));
    }  
    
  ntMC->Project("hPtMC","Dpt",TCut(weight)*(TCut(selmceff.Data())&&"(Dgen==23333)"));
  divideBinWidth(hPtMC);
  ntMC->Project("hPtRecoTruth","Dpt",TCut(selmceff.Data())&&"(Dgen==23333)");
  divideBinWidth(hPtRecoTruth);
  ntGen->Project("hPtGen","Gpt",TCut(weightgen)*(TCut(selmcgen.Data())));
  divideBinWidth(hPtGen);
  nt->Project("hDcandidates","Dpt",Form("%s&&Dmass>1.8&&Dmass<1.9",seldata.Data()));
  divideBinWidth(hDcandidates);

  TCanvas* cPt =  new TCanvas("cPt","",600,600);
  cPt->SetLogy();
  hPt->SetXTitle("D^{0} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected dN(D^{0})/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();
  if(isMC)
    {
      hPtMC->Draw("same hist");
      TLegend* legPt = myLegend(0.55,0.80,0.90,0.94);
      legPt->AddEntry(hPt,"Signal extraction","pl");
      legPt->AddEntry(hPtMC,"Matched reco","lf");
      legPt->Draw("same");  
    }
  hPtMC->Sumw2();
  TH1D* hEff = (TH1D*)hPtMC->Clone("hEff");
  hEff->SetTitle(";D^{0} p_{T} (GeV/c);Efficiency");
  hEff->Sumw2();
  hEff->Divide(hPtGen);
  TCanvas* cEff = new TCanvas("cEff","",600,600);
  hEff->Draw();
  
  TH1D* hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->SetTitle(";D^{0} p_{T} (GeV/c);Corrected dN(D^{0})/dp_{T}");
  hPtCor->Divide(hEff);
  TCanvas* cPtCor=  new TCanvas("cCorResult","",600,600);
  cPtCor->SetLogy();
  hPtCor->Draw();
  if(isMC)
    {
      hPtGen->Draw("same hist");
      TLegend* legPtCor = myLegend(0.55,0.80,0.90,0.94);
      legPtCor->AddEntry(hPtCor,"Corrected signal","pl");
      legPtCor->AddEntry(hPtGen,"Generated D^{0}","lf");
      legPtCor->Draw("same");  
    }

  TH1D* hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  hPtSigma->SetTitle(";D^{0} p_{T} (GeV/c);d#sigma(D^{0})/dp_{T} (pb/GeV)");
  hPtSigma->Scale(1./(2*luminosity*BRchain));
  TCanvas* cPtSigma=  new TCanvas("cPtSigma","",600,600);
  cPtSigma->SetLogy();
  hPtSigma->Draw();
  
  TFile* outf = new TFile(outputfile.Data(),"recreate");
  outf->cd();
  hPt->Write();
  hEff->Write();
  hPtGen->Write();
  hPtMC->Write();
  hPtCor->Write();
  hPtSigma->Write();
  hMean->Write();
  hSigmaGaus1->Write();
  hSigmaGaus2->Write();
  hRelMagnGausOverGaus2->Write();
  hSigmaGausRefl->Write();
  hRelMagnReflOverSignal->Write();
  hDcandidates->Write();
  outf->Close();
}

void clean0(TH1D* h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

TF1* fit(TTree* nt, TTree* ntMC, Double_t ptmin, Double_t ptmax, int isMC,bool isPbPb,TF1* &total,Float_t centmin, Float_t centmax)
{
  static int count=0;
  count++;

  TCanvas* c= new TCanvas(Form("c%d",count),"",600,600);
  TH1D* h = new TH1D(Form("h-%d",count),"",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hMCSignal = new TH1D(Form("hMCSignal-%d",count),"",nbinsmasshisto,minhisto,maxhisto);
  TH1D* hMCSwapped = new TH1D(Form("hMCSwapped-%d",count),"",nbinsmasshisto,minhisto,maxhisto);
  
  TF1* f = new TF1(Form("f%d",count),"[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);
  
  if(isMC==1) nt->Project(Form("h-%d",count),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f)","1",seldata.Data(),ptmin,ptmax));   
  else nt->Project(Form("h-%d",count),"Dmass",Form("(%s&&Dpt>%f&&Dpt<%f)",seldata.Data(),ptmin,ptmax));   
  
  ntMC->Project(Form("hMCSignal-%d",count),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23333))","1",selmc.Data(),ptmin,ptmax));   
  ntMC->Project(Form("hMCSwapped-%d",count),"Dmass",Form("%s*(%s&&Dpt>%f&&Dpt<%f&&(Dgen==23344))","1",selmc.Data(),ptmin,ptmax));   
  
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
  
  hMCSignal->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  hMCSignal->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSignal->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);
  
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);
  
  hMCSwapped->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  hMCSwapped->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);
  
  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);
  
  h->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.86,1.87);
  f->ReleaseParameter(11);
  f->SetParLimits(11,-1.,1.);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L q","",minhisto,maxhisto);
  h->Fit(Form("f%d",count),"L m","",minhisto,maxhisto);
  
  TF1* background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
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
  h->GetXaxis()->SetTitleOffset(1.3);
  h->GetYaxis()->SetTitleOffset(1.8);
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

  TLegend* leg = new TLegend(0.65,0.58,0.82,0.88,NULL,"brNDC");
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

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  texCms->Draw();

  TLatex* texCol;
  if(collisionsystem=="PP"||collisionsystem=="PPMB") texCol= new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","pp"));
  else texCol= new TLatex(0.96,0.93, Form("%s #sqrt{s_{NN}} = 5.02 TeV","pPb"));
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);
  texCol->Draw();

  TLatex* tex;

  tex = new TLatex(0.22,0.78,Form("%.1f < p_{T} < %.1f GeV/c",ptmin,ptmax));
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  
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

  tex = new TLatex(0.22,0.83,"|y| < 1.0");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  
  total=f;

  h->GetFunction(Form("f%d",count))->Delete();
  TH1F* histo_copy_nofitfun = ( TH1F * ) h->Clone("histo_copy_nofitfun");
  histo_copy_nofitfun->Draw("esame");

//
  if(!isPbPb) c->SaveAs(Form("plotFits/DMass%s_%d.pdf",collisionsystem.Data(),count));
  else c->SaveAs(Form("plotFits/DMass%s_%.0f_%.0f_%d.pdf",collisionsystem.Data(),centMin,centMax,count));
  
  return mass;
}


int main(int argc, char *argv[])
{
  if(argc==14)
    {
      fitD(atoi(argv[1]),argv[2], argv[3], argv[4], argv[5], argv[6], atoi(argv[7]), atof(argv[8]), atoi(argv[9]),argv[10],argv[11],atof(argv[12]),atof(argv[13]));
      return 0;
    }
  else if(argc==12)
    {
      fitD(atoi(argv[1]), argv[2], argv[3], argv[4], argv[5], argv[6], atoi(argv[7]), atof(argv[8]), atoi(argv[9]),argv[10],argv[11]);
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs: fitD.C" << std::endl;
      return 1;
    }
}



double ErrorOnSigma(double width, double errwidth, double smear, double errsmearing)
{
  double squarederroronsigma=(1+smear)*(1+smear)*errwidth*errwidth+width*width*errsmearing*errsmearing;
  double erroronsigma=TMath::Sqrt(squarederroronsigma);
  return erroronsigma; 
}

