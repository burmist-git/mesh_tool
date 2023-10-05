//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

#include <time.h>

using namespace std;

void load_data( TString fileName, TGraph2D *gr, TH1D *h1_x, TH1D *h1_y, TH1D *h1_z, TH2D *h2_y_vs_x, TH2D *h2_z_vs_x, TGraph *gr_z_vs_r);

Int_t plots(){
  //
  TString fileN01;
  fileN01 = "./Primary_Mirror_high.stl";
  //
  TH1D *h1_x = new TH1D("h1_x","h1_x",1000, -4000, 4000);
  TH1D *h1_y = new TH1D("h1_y","h1_y",1000, -4000, 4000);
  TH1D *h1_z = new TH1D("h1_z","h1_z",1000, -4000, 4000);
  TH2D *h2_y_vs_x = new TH2D("h2_y_vs_x","h2_y_vs_x", 400, -1000, 1000, 400, -1000, 1000);
  TH2D *h2_z_vs_x = new TH2D("h2_z_vs_x","h2_z_vs_x", 400, -1000, 1000, 400, 1000, 1000);
  TGraph *gr_z_vs_r = new TGraph();
  gr_z_vs_r->SetNameTitle("","");
  TGraph2D *gr01 = new TGraph2D();
  gr01->SetNameTitle("","");
  load_data(fileN01, gr01, h1_x, h1_y, h1_z, h2_y_vs_x, h2_z_vs_x, gr_z_vs_r);
  TCanvas *c1 = new TCanvas("c1","c1",10,10,800,800);
  gr01->Draw();
  TCanvas *c2 = new TCanvas("c2","c2",10,10,800,800);
  h1_x->Draw();
  TCanvas *c3 = new TCanvas("c3","c3",10,10,800,800);
  h1_y->Draw();
  TCanvas *c4 = new TCanvas("c4","c4",10,10,800,800);
  h1_z->Draw();
  TCanvas *c5 = new TCanvas("c5","c5",10,10,800,800);
  h2_y_vs_x->Draw("ZCOLOR");
  TCanvas *c6 = new TCanvas("c6","c6",10,10,800,800);
  h2_z_vs_x->Draw("ZCOLOR");
  TCanvas *c7 = new TCanvas("c7","c7",10,10,800,800);
  gr_z_vs_r->Draw("AP");  
  return 0;
}

void load_data( TString fileName, TGraph2D *gr, TH1D *h1_x, TH1D *h1_y, TH1D *h1_z, TH2D *h2_y_vs_x, TH2D *h2_z_vs_x, TGraph *gr_z_vs_r){
  ifstream fileIn(fileName.Data());
  Double_t x;
  Double_t y;
  Double_t z;
  Double_t xnew;
  Double_t ynew;
  Double_t znew;
  Double_t r;
  Int_t i = 0;
  TString mot;
  Double_t angleX = 0.0/180.0*TMath::Pi();
  Double_t angleY = 22.5/180.0*TMath::Pi();
  Double_t angleZ = 0.0/180.0*TMath::Pi();
  if(fileIn.is_open()){
    while(fileIn>>mot){
      if(mot == "vertex"){
	fileIn>>x>>y>>z;
	TVector3 *v = new TVector3(x,y,z);
	v->RotateY(angleY);
	//
	xnew = v->X() + 354.8 - 11.03;
	ynew = v->Y() - 636.9 + 3.455;
	znew = v->Z() + 2396;
	//znew = -znew;
	r=TMath::Sqrt(xnew*xnew+ynew*ynew);
	//	
	if(znew<-10 && r<200 && r>110){
	  i=gr->GetN();
	  gr->SetPoint(i,xnew,ynew,znew);
	  h1_x->Fill(xnew);
	  h1_y->Fill(ynew);
	  h1_z->Fill(znew);
	  h2_y_vs_x->Fill(xnew,ynew);
	  h2_z_vs_x->Fill(xnew,znew);
	  gr_z_vs_r->SetPoint(gr_z_vs_r->GetN(),r,znew);
	  gr_z_vs_r->SetPoint(gr_z_vs_r->GetN(),-r,znew);
	  //
	}
	delete v;
      }
    }
    fileIn.close();
  }
  else
    cout<<"Unable to open file"<<endl;
}
  
