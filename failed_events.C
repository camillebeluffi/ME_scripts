#include <vector>
#include <sstream>
#include "TMath.h"
#include "TString.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "THStack.h"
#include "TF1.h"
#include "TTree.h"
#include <fstream>
#include "TROOT.h"
using namespace std;

void failed_events(TString hypothesis, TString sample)
{

   TString input="/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/"+hypothesis+"/Events/ReReco_llbb_"+sample+"/input.lhco";
   TString weights_out="/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/"+hypothesis+"/Events/ReReco_llbb_"+sample+"/weights.out";

 
 //__________________________________________________________________________________ 
 std::ifstream myfile("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/"+hypothesis+"/Events/ReReco_llbb_"+sample+"/input.lhco");
 myfile.unsetf(std::ios_base::skipws);

 unsigned line_count = std::count(
    std::istream_iterator<char>(myfile),
    std::istream_iterator<char>(),
    '\n');

 myfile.close();

 std::ifstream myfile2("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/"+hypothesis+"/Events/ReReco_llbb_"+sample+"/weights.out");
 myfile2.unsetf(std::ios_base::skipws);

 unsigned line_count2 = std::count(
    std::istream_iterator<char>(myfile2),
    std::istream_iterator<char>(),
    '\n');

  myfile2.close();
 //__________________________________________________________________________________ 
  
  int nevet= line_count/6;
 
   cout <<"nevet: " << nevet<< endl;
   cout <<"line_count2: " <<line_count2 << endl;
   
//----------------------- -------- --------------------------------------------------------------
   
   vector<TString> events;
   events.clear();
   ifstream infile_w(weights_out);
   TString evt;
   Double_t trigger;
   Double_t hypo;
   Double_t weight;
   Double_t error;

   Int_t i = 0;
   string line;
   while (i < 2){
        getline(infile_w,line);
        //cout << line << endl;
        i++;
        }
//cout << i << endl;

   while(infile_w >> evt >> trigger >> hypo >> weight >> error){
    events.push_back(evt);
    //cout << "evt: " << evt << endl;
    }
   infile_w.close();

   
   int n_weights= events.size();

  

   ifstream infile(input);
  
   ofstream myfile_final;


   //int i=0;
   myfile_final.open("Relaunch/relaunch_"+hypothesis+"_"+sample+".lhco"); 

 for(int k=0; k<nevet ; k++){
   string line1; 
   string line2;  
   string line3; 
   string line4;   
   string line5; 
   string line6;    
   getline(infile,line1); 
   getline(infile,line2); 
   getline(infile,line3); 
   getline(infile,line4); 
   getline(infile,line5); 
   getline(infile,line6); 

   for (int j=0; j< n_weights; j++){
     TString line11= line1;
//      cout << "k: " <<k << endl;
//      cout << "j: " << j<< endl;
//      cout << "n_weights: " << n_weights<< endl;
//      cout << "line11: " <<line11 << endl;
      if (line11.Contains(events[j])) {
        j=n_weights;
      }
      else{
        if(j==n_weights-1){
         myfile_final<< line1 << endl;
         myfile_final<< line2 << endl;
         myfile_final<< line3 << endl;
         myfile_final<< line4 << endl;
         myfile_final<< line5 << endl;
         myfile_final<< line6 << endl;
     
        }
      }
   }
   
  }    
  infile.close();
  myfile_final.close();
}

void runAll(){


// failed_events("ZZ_cor3_mm", "ZZ_2");
failed_events("ZZ_cor3_mm", "ZZ_2");
failed_events("ZZ_cor3_mm", "DYinc_2");
 failed_events("ZZ_cor3_mm", "DoubleA_2");
failed_events("ZZ_cor3_mm", "DoubleD_2");
failed_events("ZZ_cor3_mm", "DoubleC_2");
failed_events("ZZ_cor3_mm", "DoubleB_2");
failed_events("ZZ_cor3_mm", "ZH125_2");
failed_events("ZZ_cor3_mm", "TTFull_2");
failed_events("ZZ_cor3_mm", "DYPt50_70_2");
failed_events("ZZ_cor3_mm", "DYPt70_100_2");
failed_events("ZZ_cor3_mm", "DYPt100_2");
failed_events("ZZ_cor3_mm", "DYPt100_2_2");
failed_events("ZZ_cor3_mm", "DYPt180_2");
failed_events("ZZ_cor3_mm", "DYHT200_2");
failed_events("ZZ_cor3_mm", "DYHT400_2");



failed_events("tt_mm", "ZZ_2");
failed_events("tt_mm", "DYinc_2");
failed_events("tt_mm", "DoubleA_2");
failed_events("tt_mm", "DoubleD_2");
failed_events("tt_mm", "DoubleC_2");
failed_events("tt_mm", "DoubleB_2");
failed_events("tt_mm", "ZH125_2");
failed_events("tt_mm", "TTFull_2");
failed_events("tt_mm", "DYPt50_70_2");
failed_events("tt_mm", "DYPt70_100_2");
failed_events("tt_mm", "DYPt100_2");
failed_events("tt_mm", "DYPt180_2");
failed_events("tt_mm", "DYHT200_2");
failed_events("tt_mm", "DYHT400_2");


failed_events("qq_Zbb_mm", "ZZ_2");
failed_events("qq_Zbb_mm", "DYinc_2");
 failed_events("qq_Zbb_mm", "DoubleA_2");
failed_events("qq_Zbb_mm", "DoubleD_2");
failed_events("qq_Zbb_mm", "DoubleC_2");
failed_events("qq_Zbb_mm", "DoubleB_2");
failed_events("qq_Zbb_mm", "ZH125_2");
failed_events("qq_Zbb_mm", "TTFull_2");
failed_events("qq_Zbb_mm", "DYPt50_70_2");
failed_events("qq_Zbb_mm", "DYPt100_2");
failed_events("qq_Zbb_mm", "DYPt180_2");
failed_events("qq_Zbb_mm", "DYHT200_2");
failed_events("qq_Zbb_mm", "DYHT400_2");
failed_events("qq_Zbb_mm", "DYPt70_100_2");


failed_events("gg_Zbb_mm", "ZZ_2");
failed_events("gg_Zbb_mm", "DYinc_2");
 failed_events("gg_Zbb_mm", "DoubleA_2");
failed_events("gg_Zbb_mm", "DoubleD_2");
failed_events("gg_Zbb_mm", "DoubleC_2");
failed_events("gg_Zbb_mm", "DoubleB_2");
failed_events("gg_Zbb_mm", "ZH125_2");
failed_events("gg_Zbb_mm", "TTFull_2");
failed_events("gg_Zbb_mm", "DYPt50_70_2");
failed_events("gg_Zbb_mm", "DYPt100_2");
failed_events("gg_Zbb_mm", "DYPt180_2");
failed_events("gg_Zbb_mm", "DYHT200_2");
failed_events("gg_Zbb_mm", "DYHT400_2");
failed_events("gg_Zbb_mm", "DYPt70_100_2");

failed_events("ZH_cor3_mm", "ZZ_2");
failed_events("ZH_cor3_mm", "DYinc_2");
 failed_events("ZH_cor3_mm", "DoubleA_2");
failed_events("ZH_cor3_mm", "DoubleD_2");
failed_events("ZH_cor3_mm", "DoubleC_2");
failed_events("ZH_cor3_mm", "DoubleB_2");
failed_events("ZH_cor3_mm", "ZH125_2");
failed_events("ZH_cor3_mm", "TTFull_2");
failed_events("ZH_cor3_mm", "DYPt50_70_2");
failed_events("ZH_cor3_mm", "DYPt100_2");
failed_events("ZH_cor3_mm", "DYPt180_2");
failed_events("ZH_cor3_mm", "DYHT200_2");
failed_events("ZH_cor3_mm", "DYHT400_2");
failed_events("ZH_cor3_mm", "DYPt70_100_2");


failed_events("ZZ_cor0_mm", "ZZ_2");
failed_events("ZZ_cor0_mm", "DYinc_2");
 failed_events("ZZ_cor0_mm", "DoubleA_2");
failed_events("ZZ_cor0_mm", "DoubleD_2");
failed_events("ZZ_cor0_mm", "DoubleC_2");
failed_events("ZZ_cor0_mm", "DoubleB_2");
failed_events("ZZ_cor0_mm", "ZH125_2");
failed_events("ZZ_cor0_mm", "TTFull_2");
failed_events("ZZ_cor0_mm", "DYPt50_70_2");
failed_events("ZZ_cor0_mm", "DYPt100_2");
failed_events("ZZ_cor0_mm", "DYPt180_2");
failed_events("ZZ_cor0_mm", "DYHT200_2");
failed_events("ZZ_cor0_mm", "DYHT400_2");
failed_events("ZZ_cor0_mm", "DYPt70_100_2");


failed_events("ZH_cor0_mm", "ZZ_2");
failed_events("ZH_cor0_mm", "DYinc_2");
 failed_events("ZH_cor0_mm", "DoubleA_2");
failed_events("ZH_cor0_mm", "DoubleD_2");
failed_events("ZH_cor0_mm", "DoubleC_2");
failed_events("ZH_cor0_mm", "DoubleB_2");
failed_events("ZH_cor0_mm", "ZH125_2");
failed_events("ZH_cor0_mm", "TTFull_2");
failed_events("ZH_cor0_mm", "DYPt50_70_2");
failed_events("ZH_cor0_mm", "DYPt100_2");
failed_events("ZH_cor0_mm", "DYPt180_2");
failed_events("ZH_cor0_mm", "DYHT200_2");
failed_events("ZH_cor0_mm", "DYHT400_2");
failed_events("ZH_cor0_mm", "DYPt70_100_2");


failed_events("ZZ_cor3_ee", "ZZ_2");
failed_events("ZZ_cor3_ee", "DYinc_2");
failed_events("ZZ_cor3_ee", "DoubleA_2");
failed_events("ZZ_cor3_ee", "DoubleD_2");
failed_events("ZZ_cor3_ee", "DoubleC_2");
failed_events("ZZ_cor3_ee", "DoubleB_2");
failed_events("ZZ_cor3_ee", "ZH125_2");
failed_events("ZZ_cor3_ee", "TTFull_2");
failed_events("ZZ_cor3_ee", "DYPt50_70_2");
failed_events("ZZ_cor3_ee", "DYPt70_100_2");
failed_events("ZZ_cor3_ee", "DYPt100_2");
failed_events("ZZ_cor3_ee", "DYPt180_2");
failed_events("ZZ_cor3_ee", "DYHT200_2");
failed_events("ZZ_cor3_ee", "DYHT400_2");


failed_events("tt_ee", "ZZ_2");
failed_events("tt_ee", "DYinc_2");
failed_events("tt_ee", "DoubleA_2");
failed_events("tt_ee", "DoubleD_2");
failed_events("tt_ee", "DoubleC_2");
failed_events("tt_ee", "DoubleB_2");
failed_events("tt_ee", "ZH125_2");
failed_events("tt_ee", "TTFull_2");
failed_events("tt_ee", "DYPt50_70_2");
failed_events("tt_ee", "DYPt70_100_2");
failed_events("tt_ee", "DYPt100_2");
failed_events("tt_ee", "DYPt180_2");
failed_events("tt_ee", "DYHT200_2");
failed_events("tt_ee", "DYHT400_2");


failed_events("qq_Zbb_ee", "ZZ_2");
failed_events("qq_Zbb_ee", "DYinc_2");
failed_events("qq_Zbb_ee", "DoubleA_2");
failed_events("qq_Zbb_ee", "DoubleD_2");
failed_events("qq_Zbb_ee", "DoubleC_2");
failed_events("qq_Zbb_ee", "DoubleB_2");
failed_events("qq_Zbb_ee", "ZH125_2");
failed_events("qq_Zbb_ee", "TTFull_2");
failed_events("qq_Zbb_ee", "DYPt50_70_2");
failed_events("qq_Zbb_ee", "DYPt70_100_2");
failed_events("qq_Zbb_ee", "DYPt100_2");
failed_events("qq_Zbb_ee", "DYPt180_2");
failed_events("qq_Zbb_ee", "DYHT200_2");
failed_events("qq_Zbb_ee", "DYHT400_2");


failed_events("gg_Zbb_ee", "ZZ_2");
failed_events("gg_Zbb_ee", "DYinc_2");
failed_events("gg_Zbb_ee", "DoubleA_2");
failed_events("gg_Zbb_ee", "DoubleD_2");
failed_events("gg_Zbb_ee", "DoubleC_2");
failed_events("gg_Zbb_ee", "DoubleB_2");
failed_events("gg_Zbb_ee", "ZH125_2");
failed_events("gg_Zbb_ee", "TTFull_2");
failed_events("gg_Zbb_ee", "DYPt50_70_2");
failed_events("gg_Zbb_ee", "DYPt70_100_2");
failed_events("gg_Zbb_ee", "DYPt100_2");
failed_events("gg_Zbb_ee", "DYPt180_2");
failed_events("gg_Zbb_ee", "DYHT200_2");
failed_events("gg_Zbb_ee", "DYHT400_2");


failed_events("ZH_cor3_ee", "ZZ_2");
failed_events("ZH_cor3_ee", "DYinc_2");
failed_events("ZH_cor3_ee", "DoubleA_2");
failed_events("ZH_cor3_ee", "DoubleD_2");
failed_events("ZH_cor3_ee", "DoubleC_2");
failed_events("ZH_cor3_ee", "DoubleB_2");
failed_events("ZH_cor3_ee", "ZH125_2");
failed_events("ZH_cor3_ee", "TTFull_2");
failed_events("ZH_cor3_ee", "DYPt50_70_2");
failed_events("ZH_cor3_ee", "DYPt70_100_2");
failed_events("ZH_cor3_ee", "DYPt100_2");
failed_events("ZH_cor3_ee", "DYPt180_2");
failed_events("ZH_cor3_ee", "DYHT200_2");
failed_events("ZH_cor3_ee", "DYHT400_2");


failed_events("ZZ_cor0_ee", "ZZ_2");
failed_events("ZZ_cor0_ee", "DYinc_2");
failed_events("ZZ_cor0_ee", "DoubleA_2");
failed_events("ZZ_cor0_ee", "DoubleD_2");
failed_events("ZZ_cor0_ee", "DoubleC_2");
failed_events("ZZ_cor0_ee", "DoubleB_2");
failed_events("ZZ_cor0_ee", "ZH125_2");
failed_events("ZZ_cor0_ee", "TTFull_2");
failed_events("ZZ_cor0_ee", "DYPt50_70_2");
failed_events("ZZ_cor0_ee", "DYPt70_100_2");
failed_events("ZZ_cor0_ee", "DYPt100_2");
failed_events("ZZ_cor0_ee", "DYPt180_2");
failed_events("ZZ_cor0_ee", "DYHT200_2");
failed_events("ZZ_cor0_ee", "DYHT400_2");



failed_events("ZH_cor0_ee", "ZZ_2");
failed_events("ZH_cor0_ee", "DYinc_2");
failed_events("ZH_cor0_ee", "DoubleA_2");
failed_events("ZH_cor0_ee", "DoubleD_2");
failed_events("ZH_cor0_ee", "DoubleC_2");
failed_events("ZH_cor0_ee", "DoubleB_2");
failed_events("ZH_cor0_ee", "ZH125_2");
failed_events("ZH_cor0_ee", "TTFull_2");
failed_events("ZH_cor0_ee", "DYPt50_70_2");
failed_events("ZH_cor0_ee", "DYPt70_100_2");
failed_events("ZH_cor0_ee", "DYPt100_2");
failed_events("ZH_cor0_ee", "DYPt180_2");
failed_events("ZH_cor0_ee", "DYHT200_2");
failed_events("ZH_cor0_ee", "DYHT400_2");



}
