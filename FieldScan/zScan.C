// plot probe data for a scan along z 

#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"

struct FieldData{
   double x;
   double y;
   double z;
   double phi;
   double B;
   double dB;
   double B_rel;
   double dB_rel;
};

void zScan(){

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
   TString inpath = prefix + Form("probe-1.dat");

   // double r = 5; 
   // TString inpath = Form("./probe/probe-1_r-%.0f-cm.dat",r);

   vector<double> x,y,z,th,B,dB;
   vector<double> z1,z2,z3,z4; 
   vector<double> b1,b2,b3,b4; 
   vector<double> db1,db2,db3,db4; 
   vector<double> BR,dBR; 

   ImportScanData(inpath,z,B,dB); 
   // ImportScanDataAlt(inpath,x,y,z,th,B,dB); 

   double mean_b = GetMean(B); 
   double arg=0,err=0;

   cout << "B AVG = " << Form("%.15lf",mean_b) << endl;

   int TH=0; 

   FieldData myData; 
   TTree *myTree = new TTree("T","Field Data");
   myTree->Branch("field",&myData.x,"x/D:y/D:z/D:phi/D:B/D:dB/D:B_rel/D:dB_rel/D");

   const int N = z.size();
   for(int i=0;i<N;i++){
      // TH = (int)th[i]; 
      arg = (B[i]-mean_b)/mean_b/sf;
      err = dB[i]/mean_b/sf;
      // if(TH==0){
      //    z1.push_back(z[i]); 
      //    b1.push_back(arg);
      //    db1.push_back(err);
      // }else if(TH==90){
      //    z2.push_back(z[i]); 
      //    b2.push_back(arg);
      //    db2.push_back(err);
      // }else if(TH==180){ 
      //    z3.push_back(z[i]); 
      //    b3.push_back(arg);
      //    db3.push_back(err);
      // }else if(TH==270){
      //    z4.push_back(z[i]); 
      //    b4.push_back(arg);
      //    db4.push_back(err);
      // } 
      cout // << Form("%10.3f",x[i])  << "\t" 
           // << Form("%10.3f",y[i])  << "\t" 
           << Form("%10.3f",z[i])  << "\t" 
           // << Form("%10.3f",th[i]) << "\t" 
           << Form("%10.3f",arg )  << "\t" 
           << Form("%10.3f",err )  << endl;
      // myData.x      = x[i];  
      // myData.y      = y[i];  
      // myData.z      = z[i];  
      // myData.B_rel  = arg;  
      // myData.dB_rel = err; 
      // myTree->Fill();  
      BR.push_back(arg); 
      dBR.push_back(err); 
   } 

   TGraphErrors *g = GetTGraphErrors(z,BR,dBR);
   SetGraphParameters(g,20,kBlack);

   double MarkerSize = 1.5; 

   // TGraphErrors *g1 = GetTGraphErrors(z1,b1,db1);
   // SetGraphParameters(g1,20,kBlack);
   // g1->SetMarkerSize(MarkerSize); 

   // TGraphErrors *g2 = GetTGraphErrors(z2,b2,db2);
   // SetGraphParameters(g2,21,kBlue);
   // g2->SetMarkerSize(MarkerSize); 

   // TGraphErrors *g3 = GetTGraphErrors(z3,b3,db3);
   // SetGraphParameters(g3,22,kRed);
   // g3->SetMarkerSize(MarkerSize); 

   // TGraphErrors *g4 = GetTGraphErrors(z4,b4,db4);
   // SetGraphParameters(g4,23,kMagenta);
   // g4->SetMarkerSize(MarkerSize); 

   // TLegend *L = new TLegend(0.6,0.6,0.8,0.8); 
   // L->SetFillStyle(0); 
   // L->AddEntry(g1,"#theta = 0#circ"  ,"p"); 
   // L->AddEntry(g2,"#theta = 90#circ" ,"p"); 
   // L->AddEntry(g3,"#theta = 180#circ","p"); 
   // L->AddEntry(g4,"#theta = 270#circ","p"); 

   // TMultiGraph *mg = new TMultiGraph(); 
   // mg->Add(g1,"p"); 
   // mg->Add(g2,"p"); 
   // mg->Add(g3,"p"); 
   // mg->Add(g4,"p"); 

   double xMin = -350; 
   double xMax =  350; 
   // double yMin = -2;  
   // double yMax =  2;  

   TLine *xAxisLine  = new TLine(xMin,0,xMax,0); 
   TLine *xAxisLine2 = new TLine(-150,0, 150,0); 

   TString Title      = Form("Magnetic Field Map Along z Axis (x = 0, y = 0) ");
   // TString Title2     = Form("Magnetic Field Map (r = %.0f cm)",r);
   TString xAxisTitle = Form("z (mm)");
   TString yAxisTitle = Form("B (%s)",Units.Data());

   TCanvas *c1 = new TCanvas("c1","z Scan (1)",1200,800);
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

   // TCanvas *c2 = new TCanvas("c2","z Scan (2)",1200,800);
   // c2->SetFillColor(kWhite); 
   // c2->cd();

   // gStyle->SetOptFit(111); 
   // mg->Draw("a");
   // mg->SetTitle(Title2); 
   // mg->GetXaxis()->SetTitle("z (mm)");
   // mg->GetXaxis()->CenterTitle();
   // mg->GetYaxis()->SetTitle(yAxisTitle);
   // mg->GetYaxis()->CenterTitle(); 
   // mg->GetXaxis()->SetLimits(-150,150);  
   // mg->GetYaxis()->SetRangeUser(yMin,yMax);
   // mg->Draw("a");
   // xAxisLine2->Draw("same");
   // L->Draw("same");  
   // c2->Update(); 

   // myTree->SetMarkerStyle(20);
   // myTree->SetMarkerSize(1.6);

   // TCanvas *c3 = new TCanvas("c3","3D Field Map",1200,800);
   // c3->SetFillColor(kWhite);

   // c3->cd();
   // myTree->Draw("y:x:z:B_rel","","colz");
   // c3->Update();

}
