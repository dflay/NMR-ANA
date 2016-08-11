// plot probe data for a scan along z 

#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"

void yScan(){

   double sf = 1.; 
   double ppm = 1E-6; 
   double ppb = 1E-9; 

   int units = 0;    // 0 = ppm, 1 = ppb 
   TString Units = "ND"; 

   if(units==0){
      sf = ppm;
      Units = Form("ppm"); 
   }else if(units==1){
      sf = ppb;
      Units = Form("ppb"); 
   }

   TString prefix = Form("./probe/");
   TString inpath = prefix + Form("bnl-probe.dat");

   vector<double> y,F,dF,FR,dFR; 

   double F_LO = 61.723E+6; 
   ImportScanDataFreq(inpath,F_LO,y,F,dF); 

   double mean_b = GetMean(F); 
   double arg=0,err=0;

   cout << "F AVG = " << Form("%.15lf",mean_b) << endl;

   int TH=0; 

   const int N = y.size();
   for(int i=0;i<N;i++){
      // TH = (int)th[i]; 
      arg = (F[i]-mean_b)/mean_b/sf;
      err = dF[i]/mean_b/sf;
      cout << Form("%10.3f",y[i])  << "\t" 
           << Form("%10.3f",arg )  << "\t" 
           << Form("%10.3f",err )  << endl;
      FR.push_back(arg); 
      dFR.push_back(err); 
   } 

   TGraphErrors *g = GetTGraphErrors(y,FR,dFR);
   SetGraphParameters(g,20,kBlack);

   double MarkerSize = 1.5; 

   double xMin = y[0]   - 5; 
   double xMax = y[N-1] + 5; 

   TLine *xAxisLine  = new TLine(xMin,0,xMax,0); 
   TLine *xAxisLine2 = new TLine(-150,0, 150,0); 

   TString Title      = Form("Magnetic Field Map Along y Axis (x = 0, z = 0) ");
   TString xAxisTitle = Form("y (mm)");
   TString yAxisTitle = Form("B (%s)",Units.Data());

   TCanvas *c1 = new TCanvas("c1","y Scan",1200,800);
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
   g->Draw("ap");
   xAxisLine->Draw("same"); 
   c1->Update(); 

}
