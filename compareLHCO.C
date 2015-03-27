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

//void compareLHCO(TString inlhco, TString inlhco2, int nevet, int nevet2)
void compareLHCO(TString sample, TString channel)
{
   TString inlhco="LHCO_ReReco_newProd_JP_MET/outRDStoLHCO_"+sample+"_"+channel+".lhco";
   TString inlhco2="LHCO_ReReco_newProd_CSV_MET/outRDStoLHCO_"+sample+"_"+channel+".lhco";
//   TString inlhco="test1.lhco";
//   TString inlhco2="test21.lhco";  
 
 cout << "Sample: " <<sample <<channel <<endl;
  
 std::ifstream myfile("LHCO_ReReco_newProd_JP_MET/outRDStoLHCO_"+sample+"_"+channel+".lhco");
 myfile.unsetf(std::ios_base::skipws);

 unsigned line_count = std::count(
    std::istream_iterator<char>(myfile),
    std::istream_iterator<char>(), 
    '\n');

 std::cout << "Lines file JP: " << line_count << "\n";
 myfile.close();
 
 std::ifstream myfile2("LHCO_ReReco_newProd_CSV_MET/outRDStoLHCO_"+sample+"_"+channel+".lhco");
 myfile2.unsetf(std::ios_base::skipws);

 unsigned line_count2 = std::count(
    std::istream_iterator<char>(myfile2),
    std::istream_iterator<char>(), 
    '\n');

 std::cout << "Lines file CSV: " << line_count2 << "\n";
 myfile2.close(); 
 
  ifstream infile(inlhco);
  
  ofstream myfile_final;
  
  Double_t evt;
  Double_t run_num;
  Double_t num;

 //int i=0;
 myfile_final.open("combinedLHCO_MET/common_events_"+sample+"_"+channel+".lhco"); 

 int nevet= line_count/6;
 int nevet2= line_count2/6;
 
 for(int i=0; i< nevet; i++){
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
   //infile >> run_num >> num >> evt;
   //cout <<"run: " << run_num <<"and num: " << num <<"and event: " << evt << endl;
//    cout << "line1: " << line1 << endl;
//    cout << "line2: " << line2 << endl;   
//    cout << "line3: " << line3 << endl;
//    cout << "line4: " << line4 << endl;   
//    cout << "line5: " << line5 << endl;  
//    cout << "line6: " << line6 << endl;  
      
   //int j=0;
   
   ifstream infile2(inlhco2);
   for (int j=0; j < nevet2; j++){
     
     string line7;
     string line8;    
     string line9;    
     string line10;
     string line11;    
     string line12;     
     getline(infile2,line7);
     getline(infile2,line8);     
     getline(infile2,line9);      
     getline(infile2,line10);
     getline(infile2,line11);     
     getline(infile2,line12);     
     //cout<< "line2: "  << line2 << endl;
     
     //if event both in CSV and JP
     if(line1 == line7) {
       //if they have the same jets
         TString line44= line4;
         TString line55= line5;
         TString line111= line11;
         TString line100= line10;	 
	 line44.Replace(0,1,"0");
	 line55.Replace(0,1,"0");
	 line111.Replace(0,1,"0");
	 line100.Replace(0,1,"0");

	        
       if((line44 == line100 && line55 == line111) || (line44 == line111 && line55 == line100) ){
         TString line11= line1;
         //line11.Replace(9,6,"1"); 
	 line11.ReplaceAll("@","@_CSVandJP");
         myfile_final<< line11 << endl;
         myfile_final<< line2 << endl;
         myfile_final<< line3 << endl;
         myfile_final<< line4 << endl;
         myfile_final<< line5 << endl;
         myfile_final<< line6 << endl;
         }
       else{
         TString line_11= line1;
         line_11.ReplaceAll("@","@_bothJPjets"); 
         myfile_final<< line_11 << endl;
         myfile_final<< line2 << endl;
         myfile_final<< line3 << endl;
         myfile_final<< line4 << endl;
         myfile_final<< line5 << endl;
         myfile_final<< line6 << endl;
	  
         TString line_21= line7;
         line_21.ReplaceAll("@","@_bothCSVjets"); 
         myfile_final<< line_21 << endl;
         myfile_final<< line8 << endl;
         myfile_final<< line9 << endl;
         myfile_final<< line10 << endl;
         myfile_final<< line11 << endl;
         myfile_final<< line12 << endl; 	 
	      
       }    
      j=nevet2-1;
     }
     else {
       if (j==nevet2-1){
         TString line11= line1;
         line11.ReplaceAll("@","@_JP"); 
         myfile_final<< line11 << endl;
         myfile_final<< line2 << endl;
         myfile_final<< line3 << endl;
         myfile_final<< line4 << endl;
         myfile_final<< line5 << endl;
         myfile_final<< line6 << endl;      
       }
       //else j++;
   
   }
     
   }
       
 
    
   infile2.close();
   //i++;
 }
  infile.close();
  
  ifstream infile3(inlhco2);
   for (int i=0; i < nevet2; i++){
     
     string line1;
     string line2;    
     string line3;    
     string line4;
     string line5;    
     string line6;     
     getline(infile3,line1);
     getline(infile3,line2);     
     getline(infile3,line3);      
     getline(infile3,line4);
     getline(infile3,line5);     
     getline(infile3,line6);     
     
     ifstream infile4(inlhco);
     for (int j=0; j < nevet; j++){
     
       string line7;
       string line8;    
       string line9;    
       string line10;
       string line11;    
       string line12;     
       getline(infile4,line7);
       getline(infile4,line8);     
       getline(infile4,line9);      
       getline(infile4,line10);
       getline(infile4,line11);     
       getline(infile4,line12);     
       if(line1 == line7) j=nevet-1;
       else{
         if (j==nevet-1){
           TString line11= line1;
           line11.ReplaceAll("@","@_CSV"); 
           myfile_final<< line11 << endl;
           myfile_final<< line2 << endl;
           myfile_final<< line3 << endl;
           myfile_final<< line4 << endl;
           myfile_final<< line5 << endl;
           myfile_final<< line6 << endl; 
	 }     
       
       }
        
     } 
    infile4.close();
   }   
  
  
  infile3.close();	
  myfile_final.close();
  
  

}
void runAll(){
compareLHCO("ZZ","EMu");
compareLHCO("ZH125","EMu");
compareLHCO("DYjets","EMu");
compareLHCO("WZ","EMu");
compareLHCO("WW","EMu");
compareLHCO("Wt","EMu");
compareLHCO("Wtbar","EMu");
compareLHCO("TTSemiLept","EMu");

compareLHCO("DYjets_M10to50","EMu");
compareLHCO("DYjets_Pt50to70","EMu");
compareLHCO("DYjets_Pt70to100","EMu");
compareLHCO("DYjets_Pt180","EMu");
compareLHCO("DYjets_Pt100","EMu");
compareLHCO("DYjets_HT400","EMu");
compareLHCO("DYjets_HT200to400","EMu");
compareLHCO("TTFullLept","EMu");

compareLHCO("MuEG2012A", "EMu");
compareLHCO("MuEG2012B", "EMu");
compareLHCO("MuEG2012C", "EMu");
compareLHCO("MuEG2012D", "EMu");

// // compareLHCO("DoubleMu2012A", "Mu");
// // compareLHCO("DoubleMu2012B", "Mu");
// compareLHCO("DoubleMu2012C", "Mu");
// compareLHCO("DoubleMu2012D", "Mu"); 
// // compareLHCO("DoubleEle2012C", "El");
// // compareLHCO("DoubleEle2012D", "El");
//  compareLHCO("ZZ","El");
//  compareLHCO("ZZ","Mu");
//  compareLHCO("ZH125","El");
//  compareLHCO("ZH125","Mu");
// //compareLHCO("DYjets","Mu");
// //compareLHCO("DYjets","El");
// compareLHCO("WZ","Mu");
// compareLHCO("WZ","El");
// compareLHCO("WW","Mu");
// compareLHCO("WW","El");
// compareLHCO("Wt","Mu");
// compareLHCO("Wt","El");
// compareLHCO("Wtbar","Mu");
// compareLHCO("Wtbar","El");
// 
// compareLHCO("TTSemiLept","Mu");
// compareLHCO("TTSemiLept","El");
// 
// compareLHCO("DYjets_M10to50","Mu");
// compareLHCO("DYjets_Pt50to70","Mu");
// compareLHCO("DYjets_Pt70to100","Mu");
// compareLHCO("DYjets_Pt180","Mu");
// compareLHCO("DYjets_Pt100","Mu");
// compareLHCO("DYjets_HT400","Mu");
// compareLHCO("DYjets_HT200to400","Mu");
// compareLHCO("DYjets_M10to50","El");
// compareLHCO("DYjets_Pt50to70","El");
// compareLHCO("DYjets_Pt70to100","El");
// compareLHCO("DYjets_Pt180","El");
// compareLHCO("DYjets_Pt100","El");
// compareLHCO("DYjets_HT400","El");
// compareLHCO("DYjets_HT200to400","El");
//  compareLHCO("TTFullLept","El");
//  compareLHCO("TTFullLept","Mu");
// compareLHCO("TTSemiLept","Mu");
// compareLHCO("TTSemiLept","El"); 
//  
// //compareLHCO("DoubleEle2012A", "El");
// //compareLHCO("DoubleEle2012B", "El");
// 
// // compareLHCO("MuEG2012A", "Mu");
// // compareLHCO("MuEG2012B", "Mu");
// // compareLHCO("MuEG2012C", "Mu");
// // compareLHCO("MuEG2012D", "Mu");


}

