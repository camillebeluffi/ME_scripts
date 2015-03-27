

TF_Check(){
  //TFile *TF_file = TFile::Open("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/TF_generator/Control_plots_JESMinus.root","READ");
  TFile *TF_file = TFile::Open("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/TF_generator/Control_plots_moreStat.root","READ");  
  TFile *TF_fileJM = TFile::Open("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/TF_generator/Control_plots_JESMinus.root","READ");
  TFile *TF_fileJP = TFile::Open("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/TF_generator/Control_plots_JESPlus.root","READ");  
  TFile *TF_fileJZ = TFile::Open("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/TF_generator/Control_plots_JERtwo.root","READ"); 
  TFile *TF_fileJT = TFile::Open("/home/fynu/cbeluffi/scratch/MW5_aug14/MG5_aMC_v2_1_2_beta2/TF_generator/Control_plots_JERzero.root","READ");   
   
//TH2D *h2D = (TH2D*) TF_file->Get("Binned_Egen_DeltaE_SmoothNorm_muon");
//TH2D *h2D = (TH2D*) TF_file->Get("Binned_Egen_DeltaE_SmoothNorm_ele_central");
//TH2D *h2DJM = (TH2D*) TF_fileJM->Get("Binned_Egen_DeltaE_SmoothNorm_jet")

TH2D *h2D = (TH2D*) TF_file->Get("Binned_Egen_DeltaE_SmoothNorm_jet");
TH2D *h2DJM = (TH2D*) TF_fileJM->Get("Binned_Egen_DeltaE_SmoothNorm_jet");
TH2D *h2DJP = (TH2D*) TF_fileJP->Get("Binned_Egen_DeltaE_SmoothNorm_jet");
TH2D *h2DJZ = (TH2D*) TF_fileJZ->Get("Binned_Egen_DeltaE_SmoothNorm_jet");
TH2D *h2DJT = (TH2D*) TF_fileJT->Get("Binned_Egen_DeltaE_SmoothNorm_jet");


//   TTree *t1 = (TTree*) TF_file->Get("Mu_energy");
//   Double_t egen_forward, erec_forward;
//   t1->SetBranchAddress("egen_mu",&egen_forward);
//   t1->SetBranchAddress("ereco_mu",&erec_forward);
//   TTree *t1 = (TTree*) TF_file->Get("Ele_energy_central");
//   Double_t egen_forward, erec_forward;
//   t1->SetBranchAddress("egen_ele_central",&egen_forward);
//   t1->SetBranchAddress("ereco_ele_central",&erec_forward); 
  TTree *t1 = (TTree*) TF_file->Get("Jet_energy");
  Double_t egen_forward, erec_forward;
  t1->SetBranchAddress("egen_jet",&egen_forward);
  t1->SetBranchAddress("ereco_jet",&erec_forward); 
 

  Int_t nentries = (Int_t) t1->GetEntries();

//   TH1D *DE_TF1 = new TH1D("DE_TF1","DE_TF1",75,-150,150);
//   TH1D *DE_TF2 = new TH1D("DE_TF2","DE_TF2",75,-150,150);
//   TH1D *DE_TF3 = new TH1D("DE_TF3","DE_TF3",75,-150,150);
//   TH1D *DE_TF4 = new TH1D("DE_TF4","DE_TF4",75,-150,150);
//   TH1D *h1 = new TH1D("DE_TF1"," 50 < E_{gen} < 100",75,-150,150);
//   TH1D *h2 = new TH1D("DE_TF2","100 < E_{gen} < 150",75,-150,150);
//   TH1D *h3 = new TH1D("DE_TF3","150 < E_{gen} < 200",75,-150,150);
//   TH1D *h4 = new TH1D("DE_TF4","200 < E_{gen} < 1500",75,-150,150);

     TH1D *h1 = new TH1D("h1"," 0 < E_{gen} < 1500",150,-150,150); 
     TH1D *h1JM = new TH1D("h1JM"," 0 < E_{gen} < 1500",150,-150,150); 
     TH1D *h1JP = new TH1D("h1JP"," 0 < E_{gen} < 1500",150,-150,150); 
     TH1D *h1JT = new TH1D("h1JT"," 0 < E_{gen} < 1500",150,-150,150); 
     TH1D *h1JZ = new TH1D("h1JZ"," 0 < E_{gen} < 1500",150,-150,150); 
     
     
      
  for (Int_t i = 0; i < nentries; i++) {

    t1->GetEntry(i);
   //if (TMath::Abs((Double_t) erec_forward-egen_forward ) < 20){ 
   
      TAxis *xaxis = h2DJM->GetXaxis();
      Int_t binx = xaxis->FindBin(egen_forward);
      
      h1->Add(h2D->ProjectionY( "prof_pfY",binx,binx)); 
      h1JM->Add(h2DJM->ProjectionY( "prof_pfY",binx,binx)); 
      h1JP->Add(h2DJP->ProjectionY( "prof_pfY",binx,binx)); 
      h1JT->Add(h2DJT->ProjectionY( "prof_pfY",binx,binx)); 
      h1JZ->Add(h2DJZ->ProjectionY( "prof_pfY",binx,binx)); 
      
      
        
//     if (egen_forward > 50 && egen_forward < 100){
//       DE_TF1->Fill(erec_forward-egen_forward);
// 
//       TAxis *xaxis = h2D->GetXaxis();
//       Int_t binx = xaxis->FindBin(egen_forward);
//       h1->Add(h2D->ProjectionY( "prof_pfY",binx,binx));
//       }
//     else if (egen_forward > 100 && egen_forward < 150){
//       DE_TF2->Fill(erec_forward-egen_forward);
// 
//       TAxis *xaxis = h2D->GetXaxis();
//       Int_t binx = xaxis->FindBin(egen_forward);
//       h2->Add(h2D->ProjectionY( "prof_pfY",binx,binx));
//       }
//     else if (egen_forward > 150 && egen_forward < 200){
//       DE_TF3->Fill(erec_forward-egen_forward);
// 
//       TAxis *xaxis = h2D->GetXaxis();
//       Int_t binx = xaxis->FindBin(egen_forward);
//       h3->Add(h2D->ProjectionY( "prof_pfY",binx,binx));
//       }
//     else if (egen_forward > 200 && egen_forward < 1500){
//       DE_TF4->Fill(erec_forward-egen_forward);
// 
//       TAxis *xaxis = h2D->GetXaxis();
//       Int_t binx = xaxis->FindBin(egen_forward);
//       h4->Add(h2D->ProjectionY( "prof_pfY",binx,binx));
//       }
    //}


    }

      h1->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
      h1JM->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
      h1JP->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
      h1JT->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
      h1JZ->GetXaxis()->SetTitle("E_{rec}-E_{gen}");

//   h1->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
//   h2->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
//   h3->GetXaxis()->SetTitle("E_{rec}-E_{gen}");
//   h4->GetXaxis()->SetTitle("E_{rec}-E_{gen}");

//   h1->GetXaxis()->SetTitleSize(0.07);
//   h2->GetXaxis()->SetTitleSize(0.07);
//   h3->GetXaxis()->SetTitleSize(0.07);
//   h4->GetXaxis()->SetTitleSize(0.07);

//   h1->SetLineColor(kRed);
//   h2->SetLineColor(kRed);
//   h3->SetLineColor(kRed);
//   h4->SetLineColor(kRed);
//   h1->SetLineWidth(2);
//   h2->SetLineWidth(2);
//   h3->SetLineWidth(2);
//   h4->SetLineWidth(2);

      h1JM->SetLineColor(kBlue);
      h1JP->SetLineColor(kRed);
      h1JT->SetLineColor(kPink);
      h1JZ->SetLineColor(kGreen);      


  TCanvas *c1 = new TCanvas("c1","multipads",900,700);
  gStyle->SetOptStat(0);
  //c1->Divide(2,2);
c1->Divide(2,1);
c1->cd(1);
h1->Draw();
h1JM->Draw("same");
h1JP->Draw("same");

c1->cd(2);
h1->Draw();
h1JZ->Draw("same");
h1JT->Draw("same");

//   c1->cd(1);
//   h1->Draw();
//   DE_TF1->Draw("same");
// 
// 
//   c1->cd(2);
//   h2->Draw();
//   DE_TF2->Draw("same");
// 
//   c1->cd(3);
//   h3->Draw();
//   DE_TF3->Draw("same");
// 
//   c1->cd(4);
//   h4->Draw();
//   DE_TF4->Draw("same");

}
