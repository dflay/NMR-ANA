// plot probe data for a scan along z 

#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"

void zScan(){

   double sf = 1.; 
   double ppm = 1E-6; 
   double ppb = 1E-9; 

   int units = 1;    // 0 = ppm, 1 = ppb 
   TString Units = "ND"; 

   if(units==0){
      sf = ppm;
      Units = Form("ppm"); 
   }else if(units==1){
      sf = ppb;
      Units = Form("ppb"); 
   }

   TString prefix = Form("./probe/");
   TString inpath = prefix + Form("probe-1_z-scan_2_24_16.dat");

   vector<double> z,B,dB; 
   vector<double> BR,dBR; 

   ImportScanData(inpath,z,B,dB); 

   double mean_b = GetMean(B); 

   double arg=0,err=0;

   const int N = z.size();
   for(int i=0;i<N;i++){
      arg = (B[i]-mean_b)/mean_b/sf;
      err = dB[i]/mean_b/sf; 
      BR.push_back(arg); 
      dBR.push_back(err); 
   } 

   TGraphErrors *g = GetTGraphErrors(z,BR,dBR);
   SetGraphParameters(g,20,kBlack);

   double xMin = -350; 
   double xMax =  350; 
   // double yMin = -15;  
   // double yMax =  15;  

   TLine *xAxisLine = new TLine(xMin,0,xMax,0); 

   TString Title = Form("Magnetic Field Map Along z Axis (x = 0, y = 0) ");
   TString xAxisTitle = Form("z (mm)");
   TString yAxisTitle = Form("B (%s)",Units.Data());

   TCanvas *c1 = new TCanvas("c1","z Scan",1200,800);
   c1->SetFillColor(kWhite); 
   c1->cd();

   gStyle->SetOptFit(111); 
   g->Draw("ap");
   g->SetTitle(Title); 
   g->GetXaxis()->SetTitle(xAxisTitle);
   g->GetXaxis()->CenterTitle();
   g->GetYaxis()->SetTitle(yAxisTitle);
   g->GetYaxis()->CenterTitle(); 
   g->GetXaxis()->SetLimits(xMin,xMax);  
   // g->GetYaxis()->SetRangeUser(yMin,yMax);
   g->Draw("ap");
   xAxisLine->Draw("same"); 
   c1->Update(); 


}
