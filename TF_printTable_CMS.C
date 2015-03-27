// First attempt to create a data base with a tabulated TF. 
// This is the piece of code creating the tabulated TF.
// Version for Delphes use. 
//  *************************************************
//  *********** M.Vidal 12-06-2014 *******************
//  **************************************************

#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TString.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1.h"
#include "TStyle.h"
#include "TLorentzVector.h"
#include "TChain.h"
#include "rds_zbb.h"
#include "rds_zbb.C"
// #include "ExRootTreeReader.h"
// #include "ExRootTreeWriter.h"
// #include "ExRootTreeBranch.h"
// #include "ExRootResult.h"

#include "TClonesArray.h"
#include "TRandom.h"
#include "TF1.h"

const int NX = 149; // Bins in E_gen + 1 
const int NY = 161;//161; // Bins in Delta(E_reco - E_gen) + 1
const int NX_jets = 88; // Bins in E_gen + 1 JETS 
const int NY_jets = 151; // Bins in Delta(E_reco - E_gen) + 1  
const int NY_jets_forward = 76; // Bins in Delta(E_reco - E_gen) + 1  
//-------------------------- 
using namespace std;

//--------------------------
struct Plots
{
  //Electrons
  TH2D *Ereco_Egen_ele;
  TH2D *Egen_DeltaE_ele; 
  TH2D *Binned_Egen_DeltaE_ele;
  TH2D *Binned_Egen_DeltaE_Smooth_ele;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_ele;
  TH2D *Binned_Egen_DeltaE_Norm_ele; 
  
  //Electrons ETA bins
  TH2D *Ereco_Egen_ele_forward;
  TH2D *Egen_DeltaE_ele_forward; 
  TH2D *Binned_Egen_DeltaE_ele_forward;
  TH2D *Binned_Egen_DeltaE_Smooth_ele_forward;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_ele_forward;
  TH2D *Binned_Egen_DeltaE_Norm_ele_forward;  
  
  TH2D *Ereco_Egen_ele_central;
  TH2D *Egen_DeltaE_ele_central; 
  TH2D *Binned_Egen_DeltaE_ele_central;
  TH2D *Binned_Egen_DeltaE_Smooth_ele_central;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_ele_central;
  TH2D *Binned_Egen_DeltaE_Norm_ele_central;   

  
  TH2D *Ereco_Egen_muon;
  TH2D *Egen_DeltaE_muon; 
  TH2D *Binned_Egen_DeltaE_muon;
  TH2D *Binned_Egen_DeltaE_Smooth_muon;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_muon;
  TH2D *Binned_Egen_DeltaE_Norm_muon;  
   

  //Jets
  TH2D *Ereco_Egen_jet;
  TH2D *Egen_DeltaE_jet; 
  TH2D *Binned_Egen_DeltaE_jet;
  TH2D *Binned_Egen_DeltaE_Smooth_jet;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_jet;
  TH2D *Binned_Egen_DeltaE_Norm_jet; 
  
  TH2D *Ereco_Egen_jet_central;
  TH2D *Egen_DeltaE_jet_central; 
  TH2D *Binned_Egen_DeltaE_jet_central;
  TH2D *Binned_Egen_DeltaE_Smooth_jet_central;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_jet_central;
  TH2D *Binned_Egen_DeltaE_Norm_jet_central;  
  
  TH2D *Ereco_Egen_jet_forward;
  TH2D *Egen_DeltaE_jet_forward; 
  TH2D *Binned_Egen_DeltaE_jet_forward;
  TH2D *Binned_Egen_DeltaE_Smooth_jet_forward;
  TH2D *Binned_Egen_DeltaE_SmoothNorm_jet_forward;
  TH2D *Binned_Egen_DeltaE_Norm_jet_forward;   
  
};

//--------------------------
//-----------------------------------------------
void BookHistograms(Plots *plots)
{
  //Binning  Egen  LEPTONS----
  Double_t bins_Egen[NX];
  int k=100;
  for(int j=0; j<NX ; ++j){
    if(j <=100){ 
      bins_Egen[j]=j;
    }else if(j>100 && j <= 125){ 
      k=k+2;
      bins_Egen[j]=k;
    } else if(j>125 && j <= 135){ 
      k=k+4;
      bins_Egen[j]=k;
    } else if(j>135 && j <= 147){ 
      k=k+10;
      bins_Egen[j]=k;
    }else if(j==148 )bins_Egen[j]=1500;
  }
 
  Int_t  binnum_Egen = sizeof(bins_Egen)/sizeof(Double_t) - 1;
  cout<<"Number of E_gen bins in Binned test: "<<binnum_Egen<<endl; 
 
//Binning  DELTA-E  LEPTONS----
  Double_t bins_DeltaE[NY];
  //float r=-20;
  float r=-40;
  for(int i=0; i<NY ; ++i){
    bins_DeltaE[i]=r;
    r=r+0.5;
  }
 
  
  Int_t  binnum_DeltaE = sizeof(bins_DeltaE)/sizeof(Double_t) - 1;
  cout<<"Number of Delta-E bins in Binned test: "<<binnum_DeltaE<<endl;
 
//Binning  Egen  JETS----
  Double_t bins_Egen_jets[NX_jets];
  int b=0;
  for(int j=0; j<NX_jets ; ++j){
    if(j == 0){ bins_Egen_jets[j]=j;
    }else if(j>0 && j <= 60){ 
      b=b+5;
      bins_Egen_jets[j]=b;
    }else if(j>60 && j <= 80){ 
      b=b+10;
      bins_Egen_jets[j]=b;
    }else if(j>80 && j <= 84){ 
      b=b+50;
      bins_Egen_jets[j]=b;
    }else if(j>84 && j <= 85){ 
      b=b+100;
      bins_Egen_jets[j]=b;
    }else if(j>85 && j <= 86){ 
      b=b+200;
      bins_Egen_jets[j]=b;
    }else if(j==87 )bins_Egen_jets[j]=1500;
  }
  Int_t  binnum_Egen_jets = sizeof(bins_Egen_jets)/sizeof(Double_t) - 1;
  cout<<"Number of E_gen (JETS) bins in Binned test: "<<binnum_Egen_jets<<endl;

//Binning  DELTA-E  JETS----
  Double_t bins_DeltaE_jets[NY_jets];
  float t=-150;
  for(int i=0; i<NY_jets ; ++i){
    bins_DeltaE_jets[i]=t;
    t=t+2;
  }
//Binning  DELTA-E  JETS FORWARD----
  Double_t bins_DeltaE_jets_forward[NY_jets_forward];
  float t2=-150;
  for(int i=0; i<NY_jets_forward ; ++i){
    bins_DeltaE_jets_forward[i]=t2;
    t2=t2+4;
  }  
  
  Int_t  binnum_DeltaE_jets = sizeof(bins_DeltaE_jets)/sizeof(Double_t) - 1;
  Int_t  binnum_DeltaE_jets_forward = sizeof(bins_DeltaE_jets_forward)/sizeof(Double_t) - 1;  
  cout<<"Number of Delta-E (JETS) bins in Binned test: "<<binnum_DeltaE_jets<<endl;
  cout<<"--------------------------------------------------"<<endl;
  cout<<"Number of Delta-E (JETS) bins in Binned test forward: "<<binnum_DeltaE_jets_forward<<endl;
  cout<<"--------------------------------------------------"<<endl;  

  //Screen printing binning
  if(false){
    cout<<"================================================"<<endl;
    cout<<"Binning E gen:"<<endl;
    for(int i=0; i<NX ; ++i){
      cout<<bins_Egen[i]<<" ";
    }cout<<endl;
    cout<<"================================================"<<endl;
    cout<<"Binning Delta-E:"<<endl;
    for(int i=0; i<NY ; ++i){
      cout<<bins_DeltaE[i]<<" ";
    }cout<<endl;
    cout<<"================================================"<<endl;
    cout<<"Binning E gen (JETS):"<<endl;
    for(int i=0; i<NX_jets ; ++i){
      cout<<bins_Egen_jets[i]<<" ";
    }cout<<endl;
    cout<<"================================================"<<endl;
    cout<<"Binning Delta-E (JETS):"<<endl;
    for(int i=0; i<NY_jets ; ++i){
      cout<<bins_DeltaE_jets[i]<<" ";
    }cout<<endl;
    
    cout<<"Binning Delta-E (JETS FORWARD):"<<endl;
    for(int i=0; i<NY_jets_forward ; ++i){
      cout<<bins_DeltaE_jets_forward[i]<<" ";
    }cout<<endl;    
    
    cout<<"================================================"<<endl;
  }

  //Printing to file Binning
  ofstream f;
  f.open ("Binning_test_extended.txt");
  f<<"================================================"<<endl;
  f<<"Binning E gen:"<<endl;
  for(int i=0; i<NX ; ++i){
    f<<bins_Egen[i]<<" ";
  }f<<endl;
  f<<"================================================"<<endl;
  f<<"Binning Delta-E:"<<endl;
  for(int i=0; i<NY ; ++i){
    f<<bins_DeltaE[i]<<" ";
  }f<<endl;
  f<<"================================================"<<endl;  
  f<<"Binning E gen (JETS):"<<endl;
  for(int i=0; i<NX_jets ; ++i){
    f<<bins_Egen_jets[i]<<" ";
  }f<<endl;
  f<<"================================================"<<endl;
  f<<"Binning Delta-E (JETS):"<<endl;
  for(int i=0; i<NY_jets ; ++i){
    f<<bins_DeltaE_jets[i]<<" ";
  }f<<endl;
  f<<"================================================"<<endl;
  f<<"Binning Delta-E (JETS FORWARD):"<<endl;
  for(int i=0; i<NY_jets_forward ; ++i){
    f<<bins_DeltaE_jets_forward[i]<<" ";
  }f<<endl;  
  f<<"================================================"<<endl;
  f.close();
  //end printing file

  //Electrons
  
  plots->Ereco_Egen_ele = new TH2D("Ereco_Egen_ele","E(reco,gen) Electrons; E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_ele = new TH2D("Egen_DeltaE_ele","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", 1500,0,1500,160,-20,20);
  plots->Binned_Egen_DeltaE_ele = new TH2D("Binned_Egen_DeltaE_ele","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Norm_ele = new TH2D("Binned_Egen_DeltaE_Norm_ele","#DeltaE(Norm) vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_SmoothNorm_ele = new TH2D("Binned_Egen_DeltaE_SmoothNorm_ele","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Smooth_ele = new TH2D("Binned_Egen_DeltaE_Smooth_ele","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  
  plots->Ereco_Egen_ele_forward = new TH2D("Ereco_Egen_ele_forward","E(reco,gen) Electrons; E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_ele_forward = new TH2D("Egen_DeltaE_ele_forward","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", 1500,0,1500,160,-20,20);
  plots->Binned_Egen_DeltaE_ele_forward = new TH2D("Binned_Egen_DeltaE_ele_forward","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Norm_ele_forward = new TH2D("Binned_Egen_DeltaE_Norm_ele_forward","#DeltaE(Norm) vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_SmoothNorm_ele_forward = new TH2D("Binned_Egen_DeltaE_SmoothNorm_ele_forward","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Smooth_ele_forward = new TH2D("Binned_Egen_DeltaE_Smooth_ele_forward","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  
  plots->Ereco_Egen_ele_central = new TH2D("Ereco_Egen_ele_central","E(reco,gen) Electrons; E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_ele_central = new TH2D("Egen_DeltaE_ele_central","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", 1500,0,1500,160,-20,20);
  plots->Binned_Egen_DeltaE_ele_central = new TH2D("Binned_Egen_DeltaE_ele_central","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Norm_ele_central = new TH2D("Binned_Egen_DeltaE_Norm_ele_central","#DeltaE(Norm) vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_SmoothNorm_ele_central = new TH2D("Binned_Egen_DeltaE_SmoothNorm_ele_central","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Smooth_ele_central = new TH2D("Binned_Egen_DeltaE_Smooth_ele_central","#DeltaE vs E_{gen} - Electrons; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);

  plots->Ereco_Egen_muon = new TH2D("Ereco_Egen_muon","E(reco,gen) Muons;E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_muon = new TH2D("Egen_DeltaE_muon","#DeltaE vs E_{gen} - Muons;E_{gen};E_{reco} - E_{gen}", 1500,0,1500,400,-50,50);
  plots->Binned_Egen_DeltaE_muon = new TH2D("Binned_Egen_DeltaE_muon","#DeltaE vs E_{gen} - Muons;E_{gen};E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Norm_muon = new TH2D("Binned_Egen_DeltaE_Norm_muon","#DeltaE(Norm) vs E_{gen} - Muon; E_{gen}; E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_SmoothNorm_muon = new TH2D("Binned_Egen_DeltaE_SmoothNorm_muon","#DeltaE vs E_{gen} - Muons;E_{gen};E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);
  plots->Binned_Egen_DeltaE_Smooth_muon = new TH2D("Binned_Egen_DeltaE_Smooth_muon","#DeltaE vs E_{gen} - Muons;E_{gen};E_{reco} - E_{gen}", binnum_Egen, bins_Egen, binnum_DeltaE, bins_DeltaE);

  //Jets
  plots->Ereco_Egen_jet = new TH2D("Ereco_Egen_jet","E(reco,gen) Jets;E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_jet = new TH2D("Egen_DeltaE_jet","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", 1500,0,1500,400,-150,150);
  plots->Binned_Egen_DeltaE_jet = new TH2D("Binned_Egen_DeltaE_jet","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);
  plots->Binned_Egen_DeltaE_Norm_jet = new TH2D("Binned_Egen_DeltaE_Norm_jet","#DeltaE(Norm) vs E_{gen} - Jet; E_{gen}; E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);
  plots->Binned_Egen_DeltaE_SmoothNorm_jet = new TH2D("Binned_Egen_DeltaE_SmoothNorm_jet","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);
  plots->Binned_Egen_DeltaE_Smooth_jet = new TH2D("Binned_Egen_DeltaE_Smooth_jet","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);

  plots->Ereco_Egen_jet_central = new TH2D("Ereco_Egen_jet_central","E(reco,gen) Jets;E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_jet_central = new TH2D("Egen_DeltaE_jet_central","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", 1500,0,1500,400,-150,150);
  plots->Binned_Egen_DeltaE_jet_central = new TH2D("Binned_Egen_DeltaE_jet_central","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}",binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);
  plots->Binned_Egen_DeltaE_Norm_jet_central = new TH2D("Binned_Egen_DeltaE_Norm_jet_central","#DeltaE(Norm) vs E_{gen} - Jet; E_{gen}; E_{reco} - E_{gen}",binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);
  plots->Binned_Egen_DeltaE_SmoothNorm_jet_central = new TH2D("Binned_Egen_DeltaE_SmoothNorm_jet_central","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}",binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);
  plots->Binned_Egen_DeltaE_Smooth_jet_central = new TH2D("Binned_Egen_DeltaE_Smooth_jet_central","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}",binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets, bins_DeltaE_jets);

  plots->Ereco_Egen_jet_forward = new TH2D("Ereco_Egen_jet_forward","E(reco,gen) Jets;E_{reco}; E_{gen}", 1500,0,1500,1500,0,1500);
  plots->Egen_DeltaE_jet_forward = new TH2D("Egen_DeltaE_jet_forward","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", 1500,0,1500,400,-150,150);
  plots->Binned_Egen_DeltaE_jet_forward = new TH2D("Binned_Egen_DeltaE_jet_forward","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets,  binnum_DeltaE_jets_forward, bins_DeltaE_jets_forward);
  plots->Binned_Egen_DeltaE_Norm_jet_forward = new TH2D("Binned_Egen_DeltaE_Norm_jet_forward","#DeltaE(Norm) vs E_{gen} - Jet; E_{gen}; E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets_forward, bins_DeltaE_jets_forward);
  plots->Binned_Egen_DeltaE_SmoothNorm_jet_forward = new TH2D("Binned_Egen_DeltaE_SmoothNorm_jet_forward","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets_forward, bins_DeltaE_jets_forward);
  plots->Binned_Egen_DeltaE_Smooth_jet_forward = new TH2D("Binned_Egen_DeltaE_Smooth_jet_forward","#DeltaE vs E_{gen} - Jets;E_{gen};E_{reco} - E_{gen}", binnum_Egen_jets, bins_Egen_jets, binnum_DeltaE_jets_forward, bins_DeltaE_jets_forward);

 
}
//-----------------------------------------------
//-----------------------------------------------
void WriteHistograms(Plots *plots)
{


  //Electrons 
  plots->Ereco_Egen_ele->Write();
  plots->Egen_DeltaE_ele->Write();
  plots->Binned_Egen_DeltaE_ele->Write();
  plots->Binned_Egen_DeltaE_Norm_ele->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_ele->Write();
  plots->Binned_Egen_DeltaE_Smooth_ele->Write();
  
  plots->Ereco_Egen_ele_forward->Write();
  plots->Egen_DeltaE_ele_forward->Write();
  plots->Binned_Egen_DeltaE_ele_forward->Write();
  plots->Binned_Egen_DeltaE_Norm_ele_forward->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_ele_forward->Write();
  plots->Binned_Egen_DeltaE_Smooth_ele_forward->Write();  
  
  plots->Ereco_Egen_ele_central->Write();
  plots->Egen_DeltaE_ele_central->Write();
  plots->Binned_Egen_DeltaE_ele_central->Write();
  plots->Binned_Egen_DeltaE_Norm_ele_central->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_ele_central->Write();
  plots->Binned_Egen_DeltaE_Smooth_ele_central->Write();   
  //Muons 
  plots->Ereco_Egen_muon->Write();
  plots->Egen_DeltaE_muon->Write();
  plots->Binned_Egen_DeltaE_muon->Write();
  plots->Binned_Egen_DeltaE_Norm_muon->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_muon->Write();
  plots->Binned_Egen_DeltaE_Smooth_muon->Write();  
  
  //Jets 
  plots->Ereco_Egen_jet->Write();
  plots->Egen_DeltaE_jet->Write();
  plots->Binned_Egen_DeltaE_jet->Write();
  plots->Binned_Egen_DeltaE_Norm_jet->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_jet->Write();
  plots->Binned_Egen_DeltaE_Smooth_jet->Write();
  
  plots->Ereco_Egen_jet_central->Write();
  plots->Egen_DeltaE_jet_central->Write();
  plots->Binned_Egen_DeltaE_jet_central->Write();
  plots->Binned_Egen_DeltaE_Norm_jet_central->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_jet_central->Write();
  plots->Binned_Egen_DeltaE_Smooth_jet_central->Write();  
  
  plots->Ereco_Egen_jet_forward->Write();
  plots->Egen_DeltaE_jet_forward->Write();
  plots->Binned_Egen_DeltaE_jet_forward->Write();
  plots->Binned_Egen_DeltaE_Norm_jet_forward->Write();
  plots->Binned_Egen_DeltaE_SmoothNorm_jet_forward->Write();
  plots->Binned_Egen_DeltaE_Smooth_jet_forward->Write(); 
}
//-----------------------------------------------
//-----------------------------------------------

//-----------------------------------------------
//-----------------------------------------------
void PrintFileElectron(double data[NX][NY],double data_central[NX][NY], double data_forward[NX][NY])
{
  ofstream file;
  file.open ("Electron_matrix_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX-1; i++){
    for(int j=0; j < NY-1; j++){
      file << data[i][j] << " ";
    }
    file << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file.close();
  
  ofstream file_forward;
  file_forward.open ("Electron_matrix_forward_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX-1; i++){
    for(int j=0; j < NY-1; j++){
      file_forward << data_forward[i][j] << " ";
    }
    file_forward << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file_forward.close();  
  
  ofstream file_central;
  file_central.open ("Electron_matrix_central_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX-1; i++){
    for(int j=0; j < NY-1; j++){
      file_central << data_central[i][j] << " ";
    }
    file_central << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file_central.close();   //return 0;

}
//-----------------------------------------------
//-----------------------------------------------
void PrintFileMuon(double data[NX][NY])
{
  ofstream file;
  file.open ("Muon_matrix_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX-1; i++){
    for(int j=0; j < NY-1; j++){
      file << data[i][j] << " ";
    }
    file << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file.close();
  //return 0;
}
//-----------------------------------------------
//-----------------------------------------------
void PrintFileJet(double data[NX_jets][NY_jets],double data_central[NX_jets][NY_jets], double data_forward[NX_jets][NY_jets_forward])
{
  ofstream file;
  file.open ("Jet_matrix_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX_jets-1; i++){
    for(int j=0; j < NY_jets-1; j++){
      file << data[i][j] << " ";
    }
    file << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file.close();
  //return 0;
  
  
  ofstream file_forward;
  file_forward.open ("Jet_matrix_forward_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX_jets-1; i++){
    for(int j=0; j < NY_jets_forward-1; j++){
      file_forward << data_forward[i][j] << " ";
    }
    file_forward << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file_forward.close();  
  
  ofstream file_central;
  file_central.open ("Jet_matrix_central_extended_JERzero.txt");

  //file <<"====================================================================="<< endl;
  //Print the matrix in a file
  for (int i=0; i < NX_jets-1; i++){
    for(int j=0; j < NY_jets-1; j++){
      file_central << data_central[i][j] << " ";
    }
    file_central << endl;
  }
  //file <<"====================================================================="<< endl;
  //file << endl;

  file_central.close();  

}
//-----------------------------------------------
//-----------------------------------------------
//int main(int argc, char *argv[])
int TF_printTable_CMS()
{ 
  //Not needed in the version to be compiled
  //Delphes library
  //gSystem->Load("libDelphes.so");

  // Imput file to get Ereco and Egen for different eta regions. 
  // (Maybe storing different objects, i.e e, mu, jet, bjet...)  
  
  TFile outputfile("Control_plots_JERzero.root","recreate");  

  //Tree Variables                                                                                  
  Double_t egen_jet, ereco_jet, egen_jet_central, ereco_jet_central, egen_jet_forward, ereco_jet_forward;	

  TTree *tree_jets= new TTree("Jet_energy","Tree_j_energy");					  
  tree_jets->Branch("egen_jet",&egen_jet);							  
  tree_jets->Branch("ereco_jet",&ereco_jet);
  
  TTree *tree_jets_forward= new TTree("Jet_energy_forward","Tree_j_energy_forward");					  
  tree_jets_forward->Branch("egen_jet_forward",&egen_jet_forward);							  
  tree_jets_forward->Branch("ereco_jet_forward",&ereco_jet_forward); 
  
  TTree *tree_jets_central= new TTree("Jet_energy_central","Tree_j_energy_central");					  
  tree_jets_central->Branch("egen_jet_central",&egen_jet_central);							  
  tree_jets_central->Branch("ereco_jet_central",&ereco_jet_central); 
  							  
												  
  Double_t egen_ele, ereco_ele, egen_ele_forward, ereco_ele_forward, egen_ele_central, ereco_ele_central;
  									  
  TTree *tree_ele= new TTree("Ele_energy","Tree_el_energy");					  
  tree_ele->Branch("egen_ele",&egen_ele); 							  
  tree_ele->Branch("ereco_ele",&ereco_ele);
  
  TTree *tree_ele_forward= new TTree("Ele_energy_forward","Tree_el_energy_forward");
  tree_ele_forward->Branch("egen_ele_forward",&egen_ele_forward); 							  
  tree_ele_forward->Branch("ereco_ele_forward",&ereco_ele_forward); 
  
  TTree *tree_ele_central= new TTree("Ele_energy_central","Tree_el_energy_central"); 							  
  tree_ele_central->Branch("egen_ele_central",&egen_ele_central); 							  
  tree_ele_central->Branch("ereco_ele_central",&ereco_ele_central);
  												  
  Double_t egen_mu, ereco_mu, ptgen_mu, ptreco_mu;
  									  
  TTree *tree_mu= new TTree("Mu_energy","Tree_mu_energy");					  
  tree_mu->Branch("egen_mu",&egen_mu);								  
  tree_mu->Branch("ereco_mu",&ereco_mu);  

  //Plots 
  Plots *plots = new Plots;
  BookHistograms(plots);  
   
   TString folderRDS = "/nfs/user/cbeluffi/ControlPlots/RDS_CSV_JERzero/RDS_TTFullLept/";
   TFile* f_RDS = new TFile(folderRDS+"TTFullLept_Summer12_final.root");
   TTree* t_RDS = (TTree*) f_RDS->Get("rds_zbb");

   
   
   rds_zbb* mc_RDS = new rds_zbb(t_RDS);
   
    Long64_t nbytesRDS = 0, nbRDS = 0;
   
//     TChain c("rds_zbb");
// 
// 
//     cout << "add root files to the ttree" << endl;
//     c.Add("/nfs/user/cbeluffi/ControlPlots/RDS_CSV_JERzero/RDS_TTFullLept/TTFullLept_Summer12_*.root");
//     TTree* t_RDS = c.GetTree();
//     rds_zbb* mc_RDS = new rds_zbb(t_RDS);
    
   for (Int_t iRDS=0;iRDS<t_RDS->GetEntries();iRDS++) {

      Long64_t ientry = mc_RDS->LoadTree(iRDS);
      if (ientry < 0 ) break;
      nbRDS = mc_RDS->GetEntry(iRDS); nbytesRDS += nbRDS;

      if (mc_RDS->eventSelectionmu1pt > 8 && mc_RDS->eventSelectionmu2pt > 17 && fabs(mc_RDS->eventSelectionmu1eta)<2.4 && fabs(mc_RDS->eventSelectionmu2eta)<2.4){
        if(mc_RDS->meE_lrp != -1000 && mc_RDS->meE_lgp != -1000) plots->Ereco_Egen_muon->Fill(mc_RDS->meE_lrp,mc_RDS->meE_lgp);
        if(mc_RDS->meE_lrm != -1000 && mc_RDS->meE_lgm != -1000) plots->Ereco_Egen_muon->Fill(mc_RDS->meE_lrm,mc_RDS->meE_lgm);
	
	
        if(mc_RDS->meE_lgp != -1000 && mc_RDS->meDeltaE_lp != -1000){
	  plots->Egen_DeltaE_muon->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);
          plots->Binned_Egen_DeltaE_muon->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);	 
          plots->Binned_Egen_DeltaE_Smooth_muon->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);
	}	
	
        if(mc_RDS->meE_lgm != -1000 && mc_RDS->meDeltaE_lm != -1000){
	  plots->Egen_DeltaE_muon->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
          plots->Binned_Egen_DeltaE_muon->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm); 
          plots->Binned_Egen_DeltaE_Smooth_muon->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
	}
	
	
			
	//Tree mu 
        if(mc_RDS->meE_lrp != -1000 && mc_RDS->meE_lgp != -1000) {                                                                                 
          egen_mu = mc_RDS->meE_lgp; 								      
          ereco_mu= mc_RDS->meE_lrp;
	  								      
          tree_mu->Fill();
	}
	if(mc_RDS->meE_lrm != -1000 && mc_RDS->meE_lgm != -1000) {	     
          egen_mu = mc_RDS->meE_lgm; 								      
          ereco_mu= mc_RDS->meE_lrm;
	  								      
          tree_mu->Fill();
	}

	
	
      }    
      
      if (mc_RDS->eventSelectionel1pt > 8 && mc_RDS->eventSelectionel2pt > 17 && fabs(mc_RDS->eventSelectionel1eta)<2.5 && fabs(mc_RDS->eventSelectionel2eta)<2.5){
      
        bool is_lrp_central = fabs(mc_RDS->meEta_lrp) < 1.5;
	bool is_lrm_central = fabs(mc_RDS->meEta_lrm) < 1.5;
	
	
	if(mc_RDS->meE_lrp != -1000 && mc_RDS->meE_lgp != -1000) {
	  //if (fabs(mc_RDS->meEta_lgp) > 2.4) cout <<"crazy + value of eta spotted: "  << mc_RDS->meEta_lgp <<  endl;
	  plots->Ereco_Egen_ele->Fill(mc_RDS->meE_lrp,mc_RDS->meE_lgp);
	  if (is_lrp_central) plots->Ereco_Egen_ele_central->Fill(mc_RDS->meE_lrp,mc_RDS->meE_lgp);
	  else  plots->Ereco_Egen_ele_forward->Fill(mc_RDS->meE_lrp,mc_RDS->meE_lgp);
	}
        if(mc_RDS->meE_lrm != -1000 && mc_RDS->meE_lgm != -1000) {
	  //if (fabs(mc_RDS->meEta_lgm) > 2.4) cout <<"crazy - value of eta spotted: "  << mc_RDS->meEta_lgm <<  endl;
	  plots->Ereco_Egen_ele->Fill(mc_RDS->meE_lrm,mc_RDS->meE_lgm);
	  if (is_lrm_central) plots->Ereco_Egen_ele_central->Fill(mc_RDS->meE_lrm,mc_RDS->meE_lgm);
	  else  plots->Ereco_Egen_ele_forward->Fill(mc_RDS->meE_lrm,mc_RDS->meE_lgm);	  
	}
        if(mc_RDS->meE_lgp != -1000 && mc_RDS->meDeltaE_lp != -1000){
	  plots->Egen_DeltaE_ele->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);
          plots->Binned_Egen_DeltaE_ele->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);	
          plots->Binned_Egen_DeltaE_Smooth_ele->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp); 
	  if (is_lrp_central)  {
	    plots->Egen_DeltaE_ele_central->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);
            plots->Binned_Egen_DeltaE_ele_central->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);	
            plots->Binned_Egen_DeltaE_Smooth_ele_central->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);	  
	  }   
	  else  {
	    plots->Egen_DeltaE_ele_forward->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);
            plots->Binned_Egen_DeltaE_ele_forward->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);	
            plots->Binned_Egen_DeltaE_Smooth_ele_forward->Fill(mc_RDS->meE_lgp,-mc_RDS->meDeltaE_lp);	  
	  }	
	}
        if(mc_RDS->meE_lgm != -1000 && mc_RDS->meDeltaE_lm != -1000){
	  plots->Egen_DeltaE_ele->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
          plots->Binned_Egen_DeltaE_ele->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
          plots->Binned_Egen_DeltaE_Smooth_ele->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
	  if (is_lrm_central){
	    plots->Egen_DeltaE_ele_central->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
            plots->Binned_Egen_DeltaE_ele_central->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
            plots->Binned_Egen_DeltaE_Smooth_ele_central->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
	  }
	  else{
	    plots->Egen_DeltaE_ele_forward->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
            plots->Binned_Egen_DeltaE_ele_forward->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);
            plots->Binned_Egen_DeltaE_Smooth_ele_forward->Fill(mc_RDS->meE_lgm,-mc_RDS->meDeltaE_lm);	    
	  }
	}
	
	//Tree ele 
	if(mc_RDS->meE_lrp != -1000 && mc_RDS->meE_lgp != -1000){                                                                                 
          egen_ele = mc_RDS->meE_lgp; 								      
          ereco_ele= mc_RDS->meE_lrp;
	  tree_ele->Fill();
	  if (is_lrp_central){
            egen_ele_central = mc_RDS->meE_lgp; 								      
            ereco_ele_central= mc_RDS->meE_lrp;
	    tree_ele_central->Fill();	  
	  }
	  else{
            egen_ele_forward = mc_RDS->meE_lgp; 								      
            ereco_ele_forward= mc_RDS->meE_lrp;
	    tree_ele_forward->Fill();	  
	  }								      
          
	}
         if(mc_RDS->meE_lrm != -1000 && mc_RDS->meE_lgm != -1000){
	  egen_ele = mc_RDS->meE_lgm; 								      
          ereco_ele= mc_RDS->meE_lrm;
	  tree_ele->Fill();
	  if (is_lrm_central){
	    egen_ele_central = mc_RDS->meE_lgm; 								      
            ereco_ele_central= mc_RDS->meE_lrm;
	    tree_ele_central->Fill();	  
	  }
	  else{
	    egen_ele_forward = mc_RDS->meE_lgm; 								      
            ereco_ele_forward= mc_RDS->meE_lrm;	
	    tree_ele_forward->Fill();  
	  }
          	  
	 } 									      
        }                                                                                             
      
      if(mc_RDS->jetmetbjet1pt> 20 &&mc_RDS->jetmetbjet2pt> 20 && fabs(mc_RDS->jetmetbjet1eta)< 2.4 && fabs(mc_RDS->jetmetbjet2eta)< 2.4){
      
        bool is_b_central = fabs(mc_RDS->meEta_b) < 1.6;
	bool is_ab_central = fabs(mc_RDS->meEta_ab) < 1.6;
      
        if (mc_RDS->meE_jb != -1000 && mc_RDS->meE_b != -1000){
          plots->Ereco_Egen_jet->Fill(mc_RDS->meE_jb,mc_RDS->meE_b);
	  if (is_b_central) plots->Ereco_Egen_jet_central->Fill(mc_RDS->meE_jb,mc_RDS->meE_b);
	  else plots->Ereco_Egen_jet_forward->Fill(mc_RDS->meE_jb,mc_RDS->meE_b);
	}
        if (mc_RDS->meE_jab != -1000&& mc_RDS->meE_ab != -1000 ){
	  plots->Ereco_Egen_jet->Fill(mc_RDS->meE_jab,mc_RDS->meE_ab);
	  if (is_ab_central) plots->Ereco_Egen_jet_central->Fill(mc_RDS->meE_jab,mc_RDS->meE_ab);
	  else plots->Ereco_Egen_jet_forward->Fill(mc_RDS->meE_jab,mc_RDS->meE_ab);
	}
	
	
        if (mc_RDS->meDeltaE_jet != -1000 && mc_RDS->meE_b != -1000) {
	  plots->Egen_DeltaE_jet->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
          plots->Binned_Egen_DeltaE_jet->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
	  plots->Binned_Egen_DeltaE_Smooth_jet->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
	  if (is_b_central) {
	    plots->Egen_DeltaE_jet_central->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
            plots->Binned_Egen_DeltaE_jet_central->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
	    plots->Binned_Egen_DeltaE_Smooth_jet_central->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);	  
	  }  
	  else{
	    plots->Egen_DeltaE_jet_forward->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
            plots->Binned_Egen_DeltaE_jet_forward->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);
	    plots->Binned_Egen_DeltaE_Smooth_jet_forward->Fill(mc_RDS->meE_b,-mc_RDS->meDeltaE_jet);	  
	  
	  }   
	}
        if (mc_RDS->meDeltaE_ajet != -1000 && mc_RDS->meE_ab != -1000) {
	  plots->Egen_DeltaE_jet->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);
	  plots->Binned_Egen_DeltaE_jet->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);		 
          plots->Binned_Egen_DeltaE_Smooth_jet->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);
	  if(is_ab_central){
	    plots->Egen_DeltaE_jet_central->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);
	    plots->Binned_Egen_DeltaE_jet_central->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);		 
            plots->Binned_Egen_DeltaE_Smooth_jet_central->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);
	  
	  }
	  else{
	    plots->Egen_DeltaE_jet_forward->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);
	    plots->Binned_Egen_DeltaE_jet_forward->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);		 
            plots->Binned_Egen_DeltaE_Smooth_jet_forward->Fill(mc_RDS->meE_ab,-mc_RDS->meDeltaE_ajet);
	  
	  }
	}	
	
	if (mc_RDS->meE_jb != -1000 && mc_RDS->meE_b != -1000){
          egen_jet = mc_RDS->meE_b; 								      
          ereco_jet= mc_RDS->meE_jb;								      
          tree_jets->Fill();
	  if(is_b_central){
            egen_jet_central = mc_RDS->meE_b; 								      
            ereco_jet_central= mc_RDS->meE_jb;								      
            tree_jets_central->Fill();	  
	  }
	  else{
            egen_jet_forward = mc_RDS->meE_b; 								      
            ereco_jet_forward= mc_RDS->meE_jb;								      
            tree_jets_forward->Fill();	  
	  }
	}
	if (mc_RDS->meE_jab != -1000&& mc_RDS->meE_ab != -1000){
          egen_jet = mc_RDS->meE_ab; 								      
          ereco_jet= mc_RDS->meE_jab;								      
          tree_jets->Fill();	
	  if(is_ab_central){
            egen_jet_central = mc_RDS->meE_ab; 								      
            ereco_jet_central= mc_RDS->meE_jab;								      
            tree_jets_central->Fill();	  
	  }
	  else{
            egen_jet_forward = mc_RDS->meE_ab; 								      
            ereco_jet_forward= mc_RDS->meE_jab;								      
            tree_jets_forward->Fill();	  
	  }  	
        }
	
	
	
           
      }

  }


 //}//End Loop entries
  //Smoothing-------------
  
  plots->Binned_Egen_DeltaE_Smooth_ele->Smooth(1);
  plots->Binned_Egen_DeltaE_Smooth_ele_central->Smooth(1);  
  plots->Binned_Egen_DeltaE_Smooth_ele_forward->Smooth(1);  
  
  plots->Binned_Egen_DeltaE_Smooth_muon->Smooth(1);
  
  plots->Binned_Egen_DeltaE_Smooth_jet->Smooth(1);
  plots->Binned_Egen_DeltaE_Smooth_jet_central->Smooth(1);  
  plots->Binned_Egen_DeltaE_Smooth_jet_forward->Smooth(1);    
    //End Smoothing-------------
      
  
  //Normalized SMOOTHED DeltaE to area per E_reco bin ELECTRONS----------------
  
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_ele_smooth = plots->Binned_Egen_DeltaE_Smooth_ele->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_ele_smooth = plots->Binned_Egen_DeltaE_Smooth_ele->GetBinContent(x,y);
      if(integral_x_binned_ele_smooth > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_ele->SetBinContent(x,y, binContent_binned_ele_smooth/integral_x_binned_ele_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_ele->SetBinContent(x,y,0);
    }
  }
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_ele_smooth = plots->Binned_Egen_DeltaE_Smooth_ele_forward->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_ele_smooth = plots->Binned_Egen_DeltaE_Smooth_ele_forward->GetBinContent(x,y);
      if(integral_x_binned_ele_smooth > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_ele_forward->SetBinContent(x,y, binContent_binned_ele_smooth/integral_x_binned_ele_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_ele_forward->SetBinContent(x,y,0);
    }
  }  
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_ele_smooth = plots->Binned_Egen_DeltaE_Smooth_ele_central->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_ele_smooth = plots->Binned_Egen_DeltaE_Smooth_ele_central->GetBinContent(x,y);
      if(integral_x_binned_ele_smooth > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_ele_central->SetBinContent(x,y, binContent_binned_ele_smooth/integral_x_binned_ele_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_ele_central->SetBinContent(x,y,0);
    }
  }  
  
  //Normalized DeltaE to area per E_reco bin MUONS ----------------

  
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_muon_smooth = plots->Binned_Egen_DeltaE_Smooth_muon->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_muon_smooth = plots->Binned_Egen_DeltaE_Smooth_muon->GetBinContent(x,y);
      if(integral_x_binned_muon_smooth > 20){  //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_muon->SetBinContent(x,y, binContent_binned_muon_smooth/integral_x_binned_muon_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_muon->SetBinContent(x,y,0);
    }
  }
  
  //Normalized DeltaE to area per E_reco bin JETS ----------------

  
  for(Int_t x=1; x<NX_jets ; x++){
    Double_t integral_x_binned_jet_smooth = plots->Binned_Egen_DeltaE_Smooth_jet->Integral(x,x,1,NY_jets-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY_jets ;y++){
      Double_t binContent_binned_jet_smooth = plots->Binned_Egen_DeltaE_Smooth_jet->GetBinContent(x,y);
      if(integral_x_binned_jet_smooth > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_jet->SetBinContent(x,y, binContent_binned_jet_smooth/integral_x_binned_jet_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_jet->SetBinContent(x,y,0);
    }
  }
  
  for(Int_t x=1; x<NX_jets ; x++){
    Double_t integral_x_binned_jet_smooth = plots->Binned_Egen_DeltaE_Smooth_jet_central->Integral(x,x,1,NY_jets-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY_jets ;y++){
      Double_t binContent_binned_jet_smooth = plots->Binned_Egen_DeltaE_Smooth_jet_central->GetBinContent(x,y);
      if(integral_x_binned_jet_smooth > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_jet_central->SetBinContent(x,y, binContent_binned_jet_smooth/integral_x_binned_jet_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_jet_central->SetBinContent(x,y,0);
    }
  } 
   
  for(Int_t x=1; x<NX_jets ; x++){
    Double_t integral_x_binned_jet_smooth = plots->Binned_Egen_DeltaE_Smooth_jet_forward->Integral(x,x,1,NY_jets_forward-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY_jets_forward ;y++){
      Double_t binContent_binned_jet_smooth = plots->Binned_Egen_DeltaE_Smooth_jet_forward->GetBinContent(x,y);
      if(integral_x_binned_jet_smooth > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_SmoothNorm_jet_forward->SetBinContent(x,y, binContent_binned_jet_smooth/integral_x_binned_jet_smooth);
      }else plots->Binned_Egen_DeltaE_SmoothNorm_jet_forward->SetBinContent(x,y,0);
    }
  }  
  
  //Normalized DeltaE to area per E_reco bin ELECTRONS----------------

  
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_ele = plots->Binned_Egen_DeltaE_ele->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_ele = plots->Binned_Egen_DeltaE_ele->GetBinContent(x,y);
      if(integral_x_binned_ele > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_ele->SetBinContent(x,y, binContent_binned_ele/integral_x_binned_ele);
      }else plots->Binned_Egen_DeltaE_Norm_ele->SetBinContent(x,y,0);
    }
  }
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_ele = plots->Binned_Egen_DeltaE_ele_forward->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_ele = plots->Binned_Egen_DeltaE_ele_forward->GetBinContent(x,y);
      if(integral_x_binned_ele > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_ele_forward->SetBinContent(x,y, binContent_binned_ele/integral_x_binned_ele);
      }else plots->Binned_Egen_DeltaE_Norm_ele_forward->SetBinContent(x,y,0);
    }
  }  
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_ele = plots->Binned_Egen_DeltaE_ele_central->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_ele = plots->Binned_Egen_DeltaE_ele_central->GetBinContent(x,y);
      if(integral_x_binned_ele > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_ele_central->SetBinContent(x,y, binContent_binned_ele/integral_x_binned_ele);
      }else plots->Binned_Egen_DeltaE_Norm_ele_central->SetBinContent(x,y,0);
    }
  }  
  
  //Normalized DeltaE to area per E_reco bin MUONS ----------------

  
  for(Int_t x=1; x<NX ; x++){
    Double_t integral_x_binned_muon = plots->Binned_Egen_DeltaE_muon->Integral(x,x,1,NY-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY ;y++){
      Double_t binContent_binned_muon = plots->Binned_Egen_DeltaE_muon->GetBinContent(x,y);
      if(integral_x_binned_muon > 20){  //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_muon->SetBinContent(x,y, binContent_binned_muon/integral_x_binned_muon);
      }else plots->Binned_Egen_DeltaE_Norm_muon->SetBinContent(x,y,0);
    }
  }
  
  //Normalized DeltaE to area per E_reco bin JETS ----------------

  
  for(Int_t x=1; x<NX_jets ; x++){
    Double_t integral_x_binned_jet = plots->Binned_Egen_DeltaE_jet->Integral(x,x,1,NY_jets-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY_jets ;y++){
      Double_t binContent_binned_jet = plots->Binned_Egen_DeltaE_jet->GetBinContent(x,y);
      if(integral_x_binned_jet > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_jet->SetBinContent(x,y, binContent_binned_jet/integral_x_binned_jet);
      }else plots->Binned_Egen_DeltaE_Norm_jet->SetBinContent(x,y,0);
      
    }
  }
  
  for(Int_t x=1; x<NX_jets ; x++){
    Double_t integral_x_binned_jet = plots->Binned_Egen_DeltaE_jet_central->Integral(x,x,1,NY_jets-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY_jets ;y++){
      Double_t binContent_binned_jet = plots->Binned_Egen_DeltaE_jet_central->GetBinContent(x,y);
      if(integral_x_binned_jet > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_jet_central->SetBinContent(x,y, binContent_binned_jet/integral_x_binned_jet);
      }else plots->Binned_Egen_DeltaE_Norm_jet_central->SetBinContent(x,y,0);
      
    }
  }  
  
  for(Int_t x=1; x<NX_jets ; x++){
    Double_t integral_x_binned_jet = plots->Binned_Egen_DeltaE_jet_forward->Integral(x,x,1,NY_jets-1);
    //if (integral_x_binned ==0)  cout<<"Integral = 0. Please rebin properly"<<endl;
    
    for(Int_t y=1; y<NY_jets ;y++){
      Double_t binContent_binned_jet = plots->Binned_Egen_DeltaE_jet_forward->GetBinContent(x,y);
      if(integral_x_binned_jet > 20){ //To remove spikes BE CAREFUL !!
	plots->Binned_Egen_DeltaE_Norm_jet_forward->SetBinContent(x,y, binContent_binned_jet/integral_x_binned_jet);
      }else plots->Binned_Egen_DeltaE_Norm_jet_forward->SetBinContent(x,y,0);
      
    }
  } 
  //-------------------------------------------------------------------
  
  //Writting histograms in the ROOT file
  outputfile.cd();
  WriteHistograms(plots);
  tree_jets->Write();  
  tree_jets_central->Write();  
  tree_jets_forward->Write();                                                                              
  tree_ele->Write();
  tree_ele_central->Write();
  tree_ele_forward->Write();										    
  tree_mu->Write(); 
    
  //The matrix
  double data_ele[NX][NY]; // buffer for data to write
  double data_ele_central[NX][NY]; // buffer for data to write
  double data_ele_forward[NX][NY]; // buffer for data to write
  double data_muon[NX][NY]; // buffer for data to write
  double data_jet[NX_jets][NY_jets]; // buffer for data to write
  double data_jet_central[NX_jets][NY_jets]; // buffer for data to write  
  double data_jet_forward[NX_jets][NY_jets_forward]; // buffer for data to write  
  
  for (int x = 1; x < NX; x++){
    for (int y = 1; y < NY; y++){
      data_ele[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_ele->GetBinContent(x,y);
      data_ele_central[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_ele_central->GetBinContent(x,y);
      data_ele_forward[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_ele_forward->GetBinContent(x,y);
      data_muon[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_muon->GetBinContent(x,y);
    }
    
  } 
  for (int x = 1; x < NX_jets; x++){
    for (int y = 1; y < NY_jets; y++){
      data_jet[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_jet->GetBinContent(x,y);
      data_jet_central[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_jet_central->GetBinContent(x,y);
      
    }
    for (int y = 1; y < NY_jets_forward; y++){
      data_jet_forward[x-1][y-1] = plots->Binned_Egen_DeltaE_SmoothNorm_jet_forward->GetBinContent(x,y);
      
    }
  } 
  
  //Print the matrix in a file
  
  PrintFileElectron(data_ele,data_ele_central,data_ele_forward);
  PrintFileMuon(data_muon);
  PrintFileJet(data_jet,data_jet_central,data_jet_forward );
  
  //Delete stuff
   cout << "** Exiting..." << endl;
  
  delete plots;
  //delete treeReader;
  //delete input_chain;
  
  return 0;

} 
//End of File
