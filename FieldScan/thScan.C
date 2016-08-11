// plot probe data for a scan along z 

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TString.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TLine.h"
#include "TStyle.h"

#include <iostream>
#include <fstream>

#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"
#include "./src/Field.C"

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

void CalculateDiff(vector<double> a,vector<double> da,
                   vector<double> b,vector<double> db,
                   vector<double> &c,vector<double> &dc); 

void thScan(){

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

   vector<double> x1,y1,z1,th1,B1,dB1,B1R,dB1R;
   vector<double> x2,y2,z2,th2,B2,dB2,B2R,dB2R;
   vector<double> x3,y3,z3,th3,B3,dB3,B3R,dB3R;
   vector<double> x4,y4,z4,th4,B4,dB4,B4R,dB4R;
   vector<double> x5,y5,z5,th5,B5,dB5,B5R,dB5R;
   vector<double> x6,y6,z6,th6,B6,dB6,B6R,dB6R;
   vector<double> x7,y7,z7,th7,B7,dB7,B7R,dB7R;
   vector<double> x8,y8,z8,th8,B8,dB8,B8R,dB8R;

   vector<double> D15,D26,D37,D48; 
   vector<double> dD15,dD26,dD37,dD48; 

   TString prefix = Form("./probe/");

   // TString inpath_1 = prefix + Form("probe-1_z-plus-95-mm.dat");
   // TString inpath_2 = prefix + Form("probe-1_z-minus-95-mm.dat");
   // TString inpath_1 = prefix + Form("probe-9_trial-2.dat");
   // TString inpath_2 = prefix + Form("probe-1_trial-2.dat");
   // TString inpath_3 = prefix + Form("probe-1_z-0-mm.dat");
   // TString inpath_4 = prefix + Form("probe-1_z-0-mm_no-plastic.dat");
   // TString inpath_5 = prefix + Form("probe-1_z-minus-95-mm_no-plastic.dat");

   const int N4 = 4; 
   const int N8 = 8; 

   int index = 2; 

   TString prefix_2[3] = {"no-al/","no-al-2/","al/"};
   TString fn[N4]   = {"probe-11.dat","probe-12.dat","probe-13.dat","probe-14.dat"}; 

   TString path[N8];
   path[0] = prefix + prefix_2[0]     + fn[0]; 
   path[1] = prefix + prefix_2[0]     + fn[1]; 
   path[2] = prefix + prefix_2[0]     + fn[2]; 
   path[3] = prefix + prefix_2[0]     + fn[3]; 
   path[4] = prefix + prefix_2[index] + fn[0]; 
   path[5] = prefix + prefix_2[index] + fn[1]; 
   path[6] = prefix + prefix_2[index] + fn[2]; 
   path[7] = prefix + prefix_2[index] + fn[3]; 

   ImportScanDataAlt(path[0],x1,y1,z1,th1,B1,dB1); 
   ImportScanDataAlt(path[1],x2,y2,z2,th2,B2,dB2); 
   ImportScanDataAlt(path[2],x3,y3,z3,th3,B3,dB3); 
   ImportScanDataAlt(path[3],x4,y4,z4,th4,B4,dB4); 
   ImportScanDataAlt(path[4],x5,y5,z5,th5,B5,dB5); 
   ImportScanDataAlt(path[5],x6,y6,z6,th6,B6,dB6); 
   ImportScanDataAlt(path[6],x7,y7,z7,th7,B7,dB7); 
   ImportScanDataAlt(path[7],x8,y8,z8,th8,B8,dB8); 

   double mean_b1 = GetMean(B1); 
   double mean_b2 = GetMean(B2);
   double mean_b3 = GetMean(B3);
   double mean_b4 = GetMean(B4);
   double mean_b5 = GetMean(B5);
   double mean_b6 = GetMean(B6);
   double mean_b7 = GetMean(B7);
   double mean_b8 = GetMean(B8);

   double mean_b  = (1./8.)*(mean_b1 + mean_b2 + mean_b3 + mean_b4 + mean_b5 + mean_b6 + mean_b7 + mean_b8); 
 
   double arg=0,err=0;
   cout << "B AVG = " << Form("%.15lf",mean_b) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b1) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b2) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b3) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b4) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b5) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b6) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b7) << endl;
   cout << "B AVG = " << Form("%.15lf",mean_b8) << endl;

   int TH=0; 

   FieldData myData; 
   TTree *myTree = new TTree("T","Field Data");
   myTree->Branch("field",&myData.x,"x/D:y/D:z/D:phi/D:B/D:dB/D:B_rel/D:dB_rel/D");

   CalculateB_rel_Vec(mean_b,B1,dB1,B1R,dB1R); 
   CalculateB_rel_Vec(mean_b,B2,dB2,B2R,dB2R); 
   CalculateB_rel_Vec(mean_b,B3,dB3,B3R,dB3R); 
   CalculateB_rel_Vec(mean_b,B4,dB4,B4R,dB4R); 
   CalculateB_rel_Vec(mean_b,B5,dB5,B5R,dB5R); 
   CalculateB_rel_Vec(mean_b,B6,dB6,B6R,dB6R); 
   CalculateB_rel_Vec(mean_b,B7,dB7,B7R,dB7R); 
   CalculateB_rel_Vec(mean_b,B8,dB8,B8R,dB8R); 

   CalculateDiff(B5R,dB5R,B1R,dB1R,D15,dD15); 
   CalculateDiff(B6R,dB6R,B2R,dB2R,D26,dD26); 
   CalculateDiff(B7R,dB7R,B3R,dB3R,D37,dD37); 
   CalculateDiff(B8R,dB8R,B4R,dB4R,D48,dD48); 

   TGraphErrors *g1 = GetTGraphErrors(th1,B1R,dB1R);
   SetGraphParameters(g1,kFullCircle,kBlack);

   TGraphErrors *g2 = GetTGraphErrors(th2,B2R,dB2R);
   SetGraphParameters(g2,kFullSquare,kRed);

   TGraphErrors *g3 = GetTGraphErrors(th3,B3R,dB3R);
   SetGraphParameters(g3,kFullTriangleUp,kBlue);

   TGraphErrors *g4 = GetTGraphErrors(th4,B4R,dB4R);
   SetGraphParameters(g4,kFullTriangleDown,kGreen+2);

   TGraphErrors *g5 = GetTGraphErrors(th5,B5R,dB5R);
   SetGraphParameters(g5,kOpenCircle,kBlack);

   TGraphErrors *g6 = GetTGraphErrors(th6,B6R,dB6R);
   SetGraphParameters(g6,kOpenSquare,kRed);

   TGraphErrors *g7 = GetTGraphErrors(th7,B7R,dB7R);
   SetGraphParameters(g7,kOpenTriangleUp,kBlue);

   TGraphErrors *g8 = GetTGraphErrors(th8,B8R,dB8R);
   SetGraphParameters(g8,kOpenTriangleDown,kGreen+2);

   TGraphErrors *g15 = GetTGraphErrors(th1,D15,dD15);
   SetGraphParameters(g15,kFullCircle,kBlack);

   TGraphErrors *g26 = GetTGraphErrors(th2,D26,dD26);
   SetGraphParameters(g26,kFullSquare,kRed);

   TGraphErrors *g37 = GetTGraphErrors(th3,D37,dD37);
   SetGraphParameters(g37,kFullTriangleUp,kBlue);

   TGraphErrors *g48 = GetTGraphErrors(th4,D48,dD48);
   SetGraphParameters(g48,kFullTriangleDown,kGreen+2);

   double MarkerSize = 1.6;
   g1->SetMarkerSize(MarkerSize);  
   g2->SetMarkerSize(MarkerSize);  
   g3->SetMarkerSize(MarkerSize);  
   g4->SetMarkerSize(MarkerSize);  
   g5->SetMarkerSize(MarkerSize);  
   g6->SetMarkerSize(MarkerSize);  
   g7->SetMarkerSize(MarkerSize);  
   g8->SetMarkerSize(MarkerSize);  
   g15->SetMarkerSize(MarkerSize);  
   g26->SetMarkerSize(MarkerSize);  
   g37->SetMarkerSize(MarkerSize);  
   g48->SetMarkerSize(MarkerSize);  

   TLegend *L = new TLegend(0.6,0.6,0.8,0.8); 
   L->SetFillStyle(0); 
   L->AddEntry(g1,Form("probe 11")                   ,"p"); 
   L->AddEntry(g2,Form("probe 12")                   ,"p"); 
   L->AddEntry(g3,Form("probe 13")                   ,"p"); 
   L->AddEntry(g4,Form("probe 14")                   ,"p"); 
   L->AddEntry(g5,Form("probe 11 (%s)",prefix_2[index].Data())  ,"p"); 
   L->AddEntry(g6,Form("probe 12 (%s)",prefix_2[index].Data())  ,"p"); 
   L->AddEntry(g7,Form("probe 13 (%s)",prefix_2[index].Data())  ,"p"); 
   L->AddEntry(g8,Form("probe 14 (%s)",prefix_2[index].Data())  ,"p"); 

   TMultiGraph *mg = new TMultiGraph(); 
   mg->Add(g1,"p"); 
   mg->Add(g2,"p"); 
   mg->Add(g3,"p"); 
   mg->Add(g4,"p"); 
   mg->Add(g5,"p"); 
   mg->Add(g6,"p"); 
   mg->Add(g7,"p"); 
   mg->Add(g8,"p"); 

   TMultiGraph *mgd = new TMultiGraph(); 
   mgd->Add(g15,"p"); 
   mgd->Add(g26,"p"); 
   mgd->Add(g37,"p"); 
   mgd->Add(g48,"p"); 

   double xMin = 0; 
   double xMax = 360; 

   TLine *xAxisLine  = new TLine(xMin,0,xMax,0); 
   TLine *xAxisLine2 = new TLine(-150,0, 150,0); 

   TString Title      = Form("Magnetic Field Map");
   TString xAxisTitle = Form("Azimuthal Position (deg)");
   TString yAxisTitle = Form("B (%s)",Units.Data());
   // TString yAxisTitle = Form("B (T)");

   TCanvas *c1 = new TCanvas("c1","z Scan (1)",1200,800);
   c1->SetFillColor(kWhite); 
   c1->cd();

   gStyle->SetOptFit(111); 
   mg->Draw("a");
   mg->SetTitle(Title); 
   mg->GetXaxis()->SetTitle(xAxisTitle);
   mg->GetXaxis()->CenterTitle();
   mg->GetYaxis()->SetTitle(yAxisTitle);
   mg->GetYaxis()->CenterTitle(); 
   mg->GetXaxis()->SetLimits(xMin,xMax);  
   mg->Draw("a");
   xAxisLine->Draw("same");
   L->Draw("same");  
   c1->Update(); 

   TCanvas *c2 = new TCanvas("c2","z Scan (2)",1200,800);
   c2->SetFillColor(kWhite); 
   c2->cd();

   gStyle->SetOptFit(111); 
   mgd->Draw("a");
   mgd->SetTitle("Difference"); 
   mgd->GetXaxis()->SetTitle(xAxisTitle);
   mgd->GetXaxis()->CenterTitle();
   mgd->GetYaxis()->SetTitle(yAxisTitle);
   mgd->GetYaxis()->CenterTitle(); 
   mgd->GetXaxis()->SetLimits(xMin,xMax);  
   mgd->Draw("a");
   xAxisLine->Draw("same");
   c2->Update(); 

   // myTree->SetMarkerStyle(20);
   // myTree->SetMarkerSize(1.6);

   // TCanvas *c3 = new TCanvas("c3","3D Field Map",1200,800);
   // c3->SetFillColor(kWhite);

   // c3->cd();
   // myTree->Draw("y:x:z:B_rel","","colz");
   // c3->Update();

}
//______________________________________________________________________________
void CalculateDiff(vector<double> a,vector<double> da,
                   vector<double> b,vector<double> db,
                   vector<double> &c,vector<double> &dc){

   double arg=0,err=0;
   const int N = a.size();
   for(int i=0;i<N;i++){
      arg = a[i] - b[i];
      err = TMath::Sqrt(da[i]*da[i] + db[i]*db[i]);  
      c.push_back(arg);
      dc.push_back(err);
   }

} 

