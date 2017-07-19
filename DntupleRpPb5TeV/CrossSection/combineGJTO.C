#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "bFeedDown/bFeedDownCorrection.C"
#include "../Systematics/systematics.C"

void combineGJTO(TString inputGJ, TString inputTO, TString outputplot, double lumiGJ, double lumiTO)
{
  TFile* fGJ = new TFile(inputGJ.Data());
  TFile* fTO = new TFile(inputTO.Data());
  TH1F* hPtSigmaGJ = (TH1F*)fGJ->Get("hPtSigma");
  hPtSigmaGJ->SetName("hPtSigmaGJ");
  hPtSigmaGJ->Scale(lumiGJ);
  TH1F* hPtSigmaTO = (TH1F*)fTO->Get("hPtSigma");
  hPtSigmaTO->SetName("hPtSigmaTO");
  hPtSigmaTO->Scale(lumiTO);
  TH1F* hPtSigma = (TH1F*)hPtSigmaGJ->Clone("hPtSigma");
  hPtSigma->Add(hPtSigmaTO);
  hPtSigma->Scale(1./(lumiGJ+lumiTO));

  TFile* outputfile = new TFile(outputplot.Data(),"recreate");
  outputfile->cd();
  hPtSigma->Write();
}


int main(int argc, char *argv[])
{
  if(argc==6)
    {
      combineGJTO(argv[1], argv[2], argv[3], atof(argv[4]), atof(argv[5]));
      return 0;
    }
  else
    {
      std::cout << "Wrong number of inputs" << std::endl;
      return 1;
    }
  
}


