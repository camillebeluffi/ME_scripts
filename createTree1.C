#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TLorentzVector.h"
//#include "RooDataSet.h"
#include "rds_zbb.C"


#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void CreateTree(TString InputFile, TString tagger){  


  long int runNumber;
  long int eventNumber;

  double E_j1;
  double E_j2;
  double Eta_j1;
  double Eta_j2;
  double phi_j1;
  double phi_j2;
  double Pt_j1;
  double Pt_j2;
  double btag_j1;
  double btag_j2;
  double Mass_j1;
  double Mass_j2;
  int Flavor_j1;
  int Flavor_j2;
  

  double E_l1;
  double E_l2;
  double Eta_l1;
  double Eta_l2;
  double phi_l1;
  double phi_l2;
  double Pt_l1;
  double Pt_l2;
  double Mass_l1;
  double Mass_l2; 
  int charge_l1;
  int charge_l2; 
    

  double Met;
  double Met_phi;
  double Met_sig;





   std::cout << "Running over sample: " << InputFile << std::endl;
   //bool isMuChannel = false;

   
   bool IsMuDATA = InputFile.Contains("DoubleMu");
   bool IsElDATA = InputFile.Contains("DoubleEl");
   bool IsEMuDATA = InputFile.Contains("MuEG");

      
   //TFile* f_RDS  = new TFile("/nfs/user/cbeluffi/ControlPlots/RDS_"+tagger+"_V4/RDS_"+InputFile+"/"+InputFile+"_Summer12_final.root");
   TFile* f_RDS  = new TFile("/nfs/user/cbeluffi/ControlPlots/RDS_JP_JESMinus/RDS_ZZ/ZZ_Summer12_final.root");
   TTree* t_RDS    = (TTree*)f_RDS->Get("rds_zbb");  
   
   
   ofstream myfile2; 
   ofstream myfile3;
   ofstream myfile4;
   //if( IsMuDATA==false && IsEMuDATA==false) myfile2.open ("LHCO_ReReco_newProd_"+tagger+"_MET/outRDStoLHCO_"+InputFile+"_El.lhco",ios::app); 
   //if( IsElDATA==false && IsEMuDATA==false) myfile3.open ("LHCO_ReReco_newProd_"+tagger+"_MET/outRDStoLHCO_"+InputFile+"_Mu.lhco",ios::app);
   //if( IsMuDATA==false && IsElDATA==false) myfile4.open ("LHCO_ReReco_newProd_"+tagger+"_MET/outRDStoLHCO_"+InputFile+"_EMu.lhco",ios::app); 
   if( IsMuDATA==false && IsEMuDATA==false) myfile2.open ("outRDStoLHCO_JESMinus"+InputFile+"_El.lhco",ios::app); 
   if( IsElDATA==false && IsEMuDATA==false) myfile3.open ("outRDStoLHCO_JESMinus"+InputFile+"_Mu.lhco",ios::app);
   if( IsMuDATA==false && IsElDATA==false) myfile4.open ("outRDStoLHCO_JESMinus"+InputFile+"_EMu.lhco",ios::app); 
   rds_zbb* mc_RDS = new rds_zbb(t_RDS);
   
   //TFile *f_RDSME_El = new TFile("outRDStoLHCO_"+InputFile+"_El.root", "RECREATE");
  // TFile *f_RDSME_Mu = new TFile("outRDStoLHCO_"+InputFile+"_Mu.root", "RECREATE");
   
   TTree *t_RDSME = new TTree("tree1", "tree 1");   
   
   t_RDSME->Branch("runNumber", &runNumber, "runNumber/l");
   t_RDSME->Branch("eventNumber", &eventNumber, "eventNumber/l");

   t_RDSME->Branch("E_j1",&E_j1,"E_j1/D");
   t_RDSME->Branch("E_j2",&E_j2,"E_j2/D");
   t_RDSME->Branch("Eta_j1",&Eta_j1,"Eta_j1/D");
   t_RDSME->Branch("Eta_j2",&Eta_j2,"Eta_j2/D");
   t_RDSME->Branch("phi_j1",&phi_j1,"phi_j1/D");
   t_RDSME->Branch("phi_j2",&phi_j2,"phi_j2/D");
   t_RDSME->Branch("Pt_j1",&Pt_j1,"Pt_j1/D");
   t_RDSME->Branch("Pt_j2",&Pt_j2,"Pt_j2/D");
   t_RDSME->Branch("btag_j1",&btag_j1,"btag_j1/D");
   t_RDSME->Branch("btag_j2",&btag_j2,"btag_j2/D");
   t_RDSME->Branch("Mass_j1",&Mass_j1,"Mass_j1/D");
   t_RDSME->Branch("Mass_j2",&Mass_j2,"Mass_j2/D");   
   t_RDSME->Branch("Flavor_j1",&Flavor_j1,"Flavor_j1/I");
   t_RDSME->Branch("Flavor_j2",&Flavor_j2,"Flavor_j2/I");   

   t_RDSME->Branch("E_l1",&E_l1,"E_l1/D");
   t_RDSME->Branch("E_l2",&E_l2,"E_l2/D");
   t_RDSME->Branch("Eta_l1",&Eta_l1,"Eta_l1/D");
   t_RDSME->Branch("Eta_l2",&Eta_l2,"Eta_l2/D");
   t_RDSME->Branch("phi_l1",&phi_l1,"phi_l1/D");
   t_RDSME->Branch("phi_l2",&phi_l2,"phi_l2/D");
   t_RDSME->Branch("Pt_l1",&Pt_l1,"Pt_l1/D");
   t_RDSME->Branch("Pt_l2",&Pt_l2,"Pt_l2/D");
   t_RDSME->Branch("Mass_l1",&Mass_l1,"Mass_l1/D");
   t_RDSME->Branch("Mass_l2",&Mass_l2,"Mass_l2/D");  
   t_RDSME->Branch("charge_l1",&charge_l1,"charge_l1/I");
   t_RDSME->Branch("charge_l2",&charge_l2,"charge_l2/I");
        

   

   	  
   Long64_t nbytesRDS = 0, nbRDS = 0;
   for (Int_t iRDS=0;iRDS<t_RDS->GetEntries();iRDS++) {

      Long64_t ientry = mc_RDS->LoadTree(iRDS);
      if (ientry < 0  ) break;
      nbRDS = mc_RDS->GetEntry(iRDS);   nbytesRDS += nbRDS;
        // electron channel is 1, muon channel is 2
        int isMuChannel=0;
	int isElChannel=0;
	int isEMuChannel=0;
	bool passMucut=false;
	bool passElcut=false;
	bool passElMucut=false;
	
	if (mc_RDS->rc_stage_6_idx == 1 && IsElDATA==false && IsEMuDATA==false) isMuChannel = 1;
	if (mc_RDS->rc_stage_16_idx == 1 && IsMuDATA==false && IsEMuDATA==false) isElChannel = 1;
	if (mc_RDS->rc_stage_26_idx == 1 && IsMuDATA==false && IsElDATA==false) isEMuChannel = 1;
	
	if (mc_RDS->memu1pt > 8 && fabs(mc_RDS->memu1etapm) < 2.4 && mc_RDS->memu2pt > 8 && fabs(mc_RDS->memu2etapm) < 2.4 && mc_RDS->mebjet1pt > 20 && fabs(mc_RDS-> mebjet2etapm)
	< 2.4&& mc_RDS->mebjet2pt > 20 && fabs(mc_RDS-> mebjet1etapm) < 2.4 &&((mc_RDS->memu1charge ==1 && mc_RDS->memu2charge ==-1)||(mc_RDS->memu1charge ==-1 && mc_RDS->memu2charge ==1))) passMucut = true;
	if (mc_RDS->meel1pt > 8 && fabs(mc_RDS->meel1etapm) < 2.5 && mc_RDS->meel2pt > 8 && fabs(mc_RDS->meel2etapm) < 2.5 && mc_RDS->mebjet1pt > 20 && fabs(mc_RDS-> mebjet2etapm)
	< 2.4&& mc_RDS->mebjet2pt > 20 && fabs(mc_RDS-> mebjet1etapm) < 2.4 && ((mc_RDS->meel1charge ==1 && mc_RDS->meel2charge ==-1)||(mc_RDS->meel1charge ==-1 && mc_RDS->meel2charge ==1))) passElcut = true;	
	if ((mc_RDS->meel1pt > 8 || mc_RDS->memu1pt > 8)&& (fabs(mc_RDS->meel1etapm) < 2.5 || fabs(mc_RDS->memu1etapm) < 2.4)&& (mc_RDS->meel2pt > 8 || mc_RDS->memu2pt >
	8)&& (fabs(mc_RDS->meel2etapm) < 2.5 ||fabs(mc_RDS->memu2etapm) )&& mc_RDS->mebjet1pt > 20 && fabs(mc_RDS-> mebjet2etapm)
	< 2.4&& mc_RDS->mebjet2pt > 20 && fabs(mc_RDS-> mebjet1etapm) < 2.4 && ((mc_RDS->meel1charge ==1 && mc_RDS->memu2charge ==-1)||(mc_RDS->meel1charge ==-1 &&
 	mc_RDS->memu2charge ==1)||(mc_RDS->memu1charge ==-1 && mc_RDS->meel2charge ==1)||(mc_RDS->memu1charge ==1 && mc_RDS->meel2charge ==-1))) passElMucut = true;
	
	
      
        runNumber   = mc_RDS->eventSelectionrun;
        eventNumber = mc_RDS->eventSelectionevent;
	TLorentzVector tlj1(0,0,0,0);
	TLorentzVector tlj2(0,0,0,0);
	tlj1.SetPtEtaPhiM(mc_RDS->mebjet1pt, mc_RDS->mebjet1etapm, mc_RDS->mebjet1phi, mc_RDS->mebjet1mass);
	tlj2.SetPtEtaPhiM(mc_RDS->mebjet2pt, mc_RDS->mebjet2etapm, mc_RDS->mebjet2phi, mc_RDS->mebjet2mass);

        E_j1          = tlj1.E();
        E_j2          = tlj2.E();
        Eta_j1        = mc_RDS->mebjet1etapm;
        Eta_j2        = mc_RDS->mebjet2etapm;
        phi_j1        = mc_RDS->mebjet1phi;
        phi_j2        = mc_RDS->mebjet2phi;
        Pt_j1         = mc_RDS->mebjet1pt;
	Pt_j2         = mc_RDS->mebjet2pt;
        Mass_j1       = mc_RDS->mebjet1mass;
	Mass_j2       = mc_RDS->mebjet2mass;	
        Flavor_j1       = mc_RDS->jetmetbjet1Flavor;
	Flavor_j2       = mc_RDS->jetmetbjet2Flavor;	
        Met= mc_RDS->jetmetMET;
        Met_phi= mc_RDS->jetmetMETphi;
	
	int type_lep1=0;
	int type_lep2=0;

	  
	  
	if (isMuChannel==1 ){
	  TLorentzVector tlm1(0,0,0,0);
	  TLorentzVector tlm2(0,0,0,0);
	  tlm1.SetPtEtaPhiM(mc_RDS->memu1pt, mc_RDS->memu1etapm, mc_RDS->memu1phi, mc_RDS->memu1mass);
	  tlm2.SetPtEtaPhiM(mc_RDS->memu2pt, mc_RDS->memu2etapm, mc_RDS->memu2phi, mc_RDS->memu2mass);
          E_l1         = tlm1.E();
          E_l2         = tlm2.E();
          Eta_l1       = mc_RDS->memu1etapm;
          Eta_l2       = mc_RDS->memu2etapm;
          phi_l1       = mc_RDS->memu1phi;
          phi_l2       = mc_RDS->memu2phi;
          Pt_l1        = mc_RDS->memu1pt;
          Pt_l2        = mc_RDS->memu2pt;
          Mass_l1      = mc_RDS->memu1mass;
          Mass_l2      = mc_RDS->memu2mass;
          charge_l1    = mc_RDS->memu1charge;
          charge_l2    = mc_RDS->memu2charge;	
	}
	else if (isElChannel ==1 ){
	  TLorentzVector tle1(0,0,0,0);
	  TLorentzVector tle2(0,0,0,0);
	  tle1.SetPtEtaPhiM(mc_RDS->meel1pt, mc_RDS->meel1etapm, mc_RDS->meel1phi, mc_RDS->meel1mass);
	  tle2.SetPtEtaPhiM(mc_RDS->meel2pt, mc_RDS->meel2etapm, mc_RDS->meel2phi, mc_RDS->meel2mass);

          E_l1         = tle1.E();
          E_l2         = tle2.E();
          Eta_l1       = mc_RDS->meel1etapm;
          Eta_l2       = mc_RDS->meel2etapm;
          phi_l1       = mc_RDS->meel1phi;
          phi_l2       = mc_RDS->meel2phi;
          Pt_l1        = mc_RDS->meel1pt;
          Pt_l2        = mc_RDS->meel2pt;
          Mass_l1      = mc_RDS->meel1mass;
          Mass_l2      = mc_RDS->meel2mass;
          charge_l1    = mc_RDS->meel1charge;
          charge_l2    = mc_RDS->meel2charge;		
	}
			
	else if (isEMuChannel==1 ){          
	  E_l1         = 0;
          E_l2         = 0;
	  if (mc_RDS->memu1pt > mc_RDS->meel1pt) {
	    Pt_l1= mc_RDS->memu1pt;
	    Eta_l1= mc_RDS->memu1etapm;
	    phi_l1= mc_RDS->memu1phi;
	    Mass_l1= mc_RDS->memu1mass;
	    charge_l1= mc_RDS->memu1charge;
	    type_lep1=2; 
	  }
	  else {
	    Pt_l1= mc_RDS->meel1pt;
	    Eta_l1= mc_RDS->meel1etapm;
	    phi_l1= mc_RDS->meel1phi;	    
	    Mass_l1= mc_RDS->meel1mass;
	    charge_l1= mc_RDS->meel1charge;
	    type_lep1=1;
	  }
	  if (mc_RDS->memu2pt > mc_RDS->meel2pt) {
	    Pt_l2= mc_RDS->memu2pt;
	    Eta_l2= mc_RDS->memu2etapm;
	    phi_l2= mc_RDS->memu2phi;	    
	    Mass_l2= mc_RDS->memu2mass;
	    charge_l2= mc_RDS->memu2charge;
	    type_lep2=2;	    
	  }
	  else {
	    Pt_l2= mc_RDS->meel2pt;
	    Eta_l2= mc_RDS->meel2etapm;
	    phi_l2= mc_RDS->meel2phi;	    
	    Mass_l2= mc_RDS->meel2mass;
	    charge_l2= mc_RDS->meel2charge;
	    type_lep2=1;
	  }	  
	
	}
                      
	if (isMuChannel == 1 && passMucut){
	

	  myfile3 <<"0 "<<eventNumber << "@" << runNumber<< " 1" << endl;
	  myfile3 <<"1  2 " <<setprecision(9) <<Eta_l1<<" " <<phi_l1<<" " <<Pt_l1<< " " <<Mass_l1<< " " <<charge_l1<<" 0 0 0 0" <<endl;
	  myfile3 <<"2  2 " <<setprecision(9) <<Eta_l2<<" " <<phi_l2<<" " <<Pt_l2<< " " <<Mass_l2<< " " <<charge_l2<<" 0 0 0 0" <<endl;	 
	  myfile3 <<"3  4 " <<setprecision(9) <<Eta_j1<<" " <<phi_j1 <<" " <<Pt_j1<< " " <<Mass_j1<< " " <<"0"<<" 2 0 0 0" <<endl;
	  myfile3 <<"4  4 " <<setprecision(9) <<Eta_j2<<" " <<phi_j2 <<" " <<Pt_j2<< " " <<Mass_j2<< " " <<"0"<<" 2 0 0 0" <<endl;
	  myfile3 <<"5  6 " <<"0"   <<" " <<Met_phi<<" " <<Met  << " " <<"0 0 0 0 0 0" <<endl;

          //t_RDSME->Fill();
	}
	
        else if (isElChannel == 1 && passElcut){
	

	  myfile2 <<"0 "<<eventNumber << "@" << runNumber << " 1" << endl;
	  myfile2 <<"1  1 " <<setprecision(9) <<Eta_l1<<" " <<phi_l1<<" " <<Pt_l1<< " " <<Mass_l1<< " " <<charge_l1<<" 0 0 0 0" <<endl;
	  myfile2 <<"2  1 " <<setprecision(9) <<Eta_l2<<" " <<phi_l2<<" " <<Pt_l2<< " " <<Mass_l2<< " " <<charge_l2<<" 0 0 0 0" <<endl;	
	  myfile2 <<"3  4 " <<setprecision(9) <<Eta_j1<<" " <<phi_j1 <<" " <<Pt_j1<< " " <<Mass_j1<< " " <<"0"<<" 2 0 0 0" <<endl;
	  myfile2 <<"4  4 " <<setprecision(9) <<Eta_j2<<" " <<phi_j2 <<" " <<Pt_j2<< " " <<Mass_j2<< " " <<"0"<<" 2 0 0 0" <<endl;
	  myfile2 <<"5  6 " <<"0"   <<" " <<Met_phi<<" " <<Met  << " " <<"0 0 0 0 0 0" <<endl;

	} 
	     
	else if (isEMuChannel == 1 && passElMucut){
	

	  myfile4 <<"0 "<<eventNumber << "@" << runNumber << " 1" << endl;
	  myfile4 <<"1  " << type_lep1 << " " <<setprecision(9) <<Eta_l1<<" " <<phi_l1<<" " <<Pt_l1<< " " <<Mass_l1<< " " <<charge_l1<<" 0 0 0 0" <<endl;
	  myfile4 <<"2  " << type_lep2 << " " <<setprecision(9) <<Eta_l2<<" " <<phi_l2<<" " <<Pt_l2<< " " <<Mass_l2<< " " <<charge_l2<<" 0 0 0 0" <<endl;	
	  myfile4 <<"3  4 " <<setprecision(9) <<Eta_j1<<" " <<phi_j1 <<" " <<Pt_j1<< " " <<Mass_j1<< " " <<"0"<<" 2 0 0 0" <<endl;
	  myfile4 <<"4  4 " <<setprecision(9) <<Eta_j2<<" " <<phi_j2 <<" " <<Pt_j2<< " " <<Mass_j2<< " " <<"0"<<" 2 0 0 0" <<endl;
	  myfile4 <<"5  6 " <<"0"   <<" " <<Met_phi<<" " <<Met  << " " <<"0 0 0 0 0 0" <<endl;

	} 	
      }  
      myfile2.close();
      myfile3.close();
      myfile4.close();
   
      delete mc_RDS;
      std::cout << "Processed sample " << InputFile << std::endl;
      
}
void createTree1(){

   CreateTree("ZZ","CSV"); 
   CreateTree("ZZ","JP"); 
   CreateTree("DYjets","CSV");
   CreateTree("DYjets","JP");
   CreateTree("DoubleEle2012A","CSV");
   CreateTree("DoubleEle2012A","JP");
  CreateTree("DoubleEle2012B","CSV");
  CreateTree("DoubleEle2012B","JP");
  CreateTree("DoubleEle2012C","CSV");
  CreateTree("DoubleEle2012C","JP");
  CreateTree("DoubleEle2012D","CSV");
  CreateTree("DoubleEle2012D","JP");   
   CreateTree("DoubleMu2012A","CSV");
   CreateTree("DoubleMu2012A","JP");
  CreateTree("DoubleMu2012B","CSV");
  CreateTree("DoubleMu2012B","JP");
 CreateTree("DoubleMu2012C","CSV");
 CreateTree("DoubleMu2012C","JP");
 CreateTree("DoubleMu2012D","CSV");  
 CreateTree("DoubleMu2012D","JP");   
   CreateTree("ZH125","CSV");
   CreateTree("ZH125","JP");
  CreateTree("Wtbar","CSV");
  CreateTree("Wtbar","JP");
  CreateTree("Wt","CSV");
CreateTree("Wt","JP");
  CreateTree("WW","CSV");
  CreateTree("WW","JP");
  CreateTree("WZ","CSV");
  CreateTree("WZ","JP");
  CreateTree("DYjets_M10to50","CSV");
  CreateTree("DYjets_M10to50","JP");
  CreateTree("DYjets_Pt50to70","CSV");
  CreateTree("DYjets_Pt50to70","JP");
  CreateTree("DYjets_Pt70to100","CSV");
  CreateTree("DYjets_Pt70to100","JP");
  CreateTree("DYjets_Pt180","CSV");
  CreateTree("DYjets_Pt180","JP");
  CreateTree("DYjets_Pt100","CSV");
  CreateTree("DYjets_Pt100","JP");
 CreateTree("DYjets_HT400","CSV");
 CreateTree("DYjets_HT400","JP");
 CreateTree("DYjets_HT200to400","CSV");
 CreateTree("DYjets_HT200to400","JP");
   CreateTree("TTFullLept","CSV");
   CreateTree("TTFullLept","JP");
 CreateTree("TTSemiLept","CSV");
 CreateTree("TTSemiLept","JP");
CreateTree("MuEG2012D","CSV");
CreateTree("MuEG2012D","JP");
CreateTree("MuEG2012B","CSV");
CreateTree("MuEG2012B","JP");
CreateTree("MuEG2012C","CSV");
CreateTree("MuEG2012C","JP");
   CreateTree("MuEG2012A","CSV");
   CreateTree("MuEG2012A","JP");
}
