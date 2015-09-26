#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TCanvas.h"


void Na04_BkgFit() {

   gStyle->SetOptStat(11);
   gStyle->SetStatY(0.5);
   gStyle->SetStatX(0.5);
   gStyle->SetStatW(0.4);
   gStyle->SetStatH(0.2);

   const int nBins = 37;

   Double_t data[nBins] = {   9,   0,  7,  0,  2,  0,  15,  0,  10,  0,  
			      6,   0,  9, 12, 16, 35,  41,  52, 42, 45,
			     43,  49, 40, 25, 16,  9,   8,  13,  8,  0,
                              4,   0,  0, 10,  0,  0,  11}; 


   TH1F *histo = new TH1F("histo", "Na_4cm gamma angular correlation",37,90.0,270.0);

   histo->SetMarkerStyle(21);
   histo->SetMarkerSize(0.8);
   histo->SetStats(0);

   for(int i=0; i < nBins;  i++) histo->SetBinContent(i+1,data[i]);

   //defined Function =  gauss + pol0                                                                            
   TF1 * f1 = new TF1("myfunc", "[0] / sqrt(2.0 * TMath::Pi()) / [2] * exp(-(x - [1]) * (x - [1])/2./[2]/[2]) + [3]", 0, 100);


   //set parameter start values (mandatory)                                                            
   f1->SetParNames("Constant", "Mean", "Sigma", "Flat");
   f1->SetParameters(180.,histo->GetMean(),histo->GetRMS(),2.);
   f1->SetParLimits(80, 90.0, 180.0);
   f1->SetParLimits(1,  100.0,  90.0);
   f1->SetParLimits(2,   0.1,  10.0);
   f1->SetParLimits(3,   0.0,  10.0);
   f1->SetLineWidth(4);
   f1->SetLineColor(kCyan);

   TCanvas * c1 = new TCanvas("c1", "myfit", 200,18,800,600);
   c1->SetGrid();
   histo->Fit("myfunc");
   histo->GetYaxis()->SetTitle("Coincidence Counts");
   histo->GetXaxis()->SetTitle("angle #theta (degrees)");

   //   gStyle->SetOptStat(1101);

   histo->Draw("elp");

   //   c1->Update();

   //retrieve stat box
   //TPaveStats *ps = (TPaveStats*)c1->GetPrimitive("stats");
   //ps->SetName("mystats");
   //TList *list = ps->GetListOfLines();
   //histo->SetStats(0);
   //c1->Modified();
   

}
# Na_gammaAnglCorr
