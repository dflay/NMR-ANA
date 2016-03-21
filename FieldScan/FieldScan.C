// Test out field scan code
// - coordinates of probes
// - 3D plot  

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

#include <iostream> 
#include <fstream> 

#include "./src/Coordinates.C"
#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"
#include "./src/Parse.C"
#include "./src/Generate.C"
#include "./src/Field.C"

using namespace std; 

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

void FillVectors(double x,double y,double z,double th,double b,double b_err,double br,double br_err,
                 vector<double> &vx,vector<double> &vy,vector<double> &vz,vector<double> &vth,
                 vector<double> &vb,vector<double> &vb_err,vector<double> &vbr,vector<double> &vbr_err); 
void ClearVectors(vector<double> &vx,vector<double> &vy,vector<double> &vz,vector<double> &vth,
                  vector<double> &vb,vector<double> &vb_err,vector<double> &vbr,vector<double> &vbr_err); 
void AddToMultiGraph(TGraph *g,int probe,int color,TMultiGraph *mg,TLegend *L); 
void PrintToFile(TString outpath,vector<double> x,vector<double> y,vector<double> z,
                 vector<double> B,vector<double> dB, 
                 vector<double> Br,vector<double> dBr); 

int GetColorIndex(int index); 

void FieldScan(){

   int M=0,D=0,Yr=0;
   int r_dsv=0;  

   bool PlotGIF = false; 

   cout << "Enter date (M D Y): ";
   cin  >> M >> D >> Yr; 
   cout << "Enter dynamic radius (cm): ";
   cin  >> r_dsv; 

   TString date,mdy; 

   if(M<10  && D<10){
      date = Form("20%d/0%d_%d/0%d_0%d_%d/",Yr,M,Yr,M,D,Yr);
      mdy  = Form("0%d_0%d_%d",M,D,Yr);
   }else if(M>=10 && D<10){
      date = Form("20%d/%d_%d/%d_0%d_%d/"  ,Yr,M,Yr,M,D,Yr);
      mdy  = Form("%d_0%d_%d"  ,M,D,Yr);
   }else if(M<10  && D>=10){ 
      date = Form("20%d/0%d_%d/0%d_%d_%d/" ,Yr,M,Yr,M,D,Yr); 
      mdy  = Form("0%d_%d_%d" ,M,D,Yr); 
   }else if(M>=10 && D>=10){
      date = Form("20%d/%d_%d/%d_%d_%d/"   ,Yr,M,Yr,M,D,Yr); 
      mdy  = Form("%d_%d_%d"   ,M,D,Yr); 
   }

   TString prefix      = Form("./input/test/");
   TString prefix_alt  = Form("./output/%s",date.Data());
   TString run_path    = prefix + Form("runlist_%s.dat",mdy.Data()); 
   // TString data_path   = prefix + Form("results_pulse-stats-field_%s.dat",mdy.Data()); 
   // TString data_path_2 = prefix + Form("results_pulse-stats_%s.dat",mdy.Data()); 
   TString data_path   = prefix_alt + Form("results_pulse-stats-field.dat"); 
   TString data_path_2 = prefix_alt + Form("results_pulse-stats.dat"); 
   TString prefix_pr   = Form("./probe/");

   vector<int> Run,SlotA,SlotB,SlotC,SlotD,Azi; 
   // ImportRunParams2(run_path,Run,SlotA,SlotB,Azi); 
   ImportRunParams4(run_path,Run,SlotA,SlotB,SlotC,SlotD,Azi); 

   // int NRUNS = Run.size();
   // for(int i=0;i<NRUNS;i++){
   //    cout << Run[i] << endl;
   // }

   vector<double> ampl,noise,zeroc;
   vector<double> b,BA,BB,BC,BD;
   vector<double> X1,Y1,Z1,P1;
   vector<double> X2,Y2,Z2,P2;
   vector<double> X3,Y3,Z3,P3;
   vector<double> X4,Y4,Z4,P4;
   vector<double> B1A,dB1A,B1R,dB1R;
   vector<double> B2A,dB2A,B2R,dB2R;
   vector<double> B3A,dB3A,B3R,dB3R;
   vector<double> B4A,dB4A,B4R,dB4R;
   vector<double> B,dB,BR,dBR; 

   vector<double> Ppa,Bpa; 
   vector<double> Ppb,Bpb; 
   vector<double> Ppc,Bpc; 
   vector<double> Ppd,Bpd; 

   vector<double> xa,ya,za,tha,pa,ba,ba_err,bar,bar_err; 
   vector<double> xb,yb,zb,thb,pb,bb,bb_err,bbr,bbr_err; 
   vector<double> xc,yc,zc,thc,pc,bc,bc_err,bcr,bcr_err; 
   vector<double> xd,yd,zd,thd,pd,bd,bd_err,bdr,bdr_err; 

   double th0=0; 
   double thr_a=0,thr_b=0,thr_c=0,thr_d=0;
   double th_a=0,th_b=0,th_c=0,th_d=0; 
   double x_a=0,y_a=0,z_a=0; 
   double x_b=0,y_b=0,z_b=0; 
   double x_c=0,y_c=0,z_c=0; 
   double x_d=0,y_d=0,z_d=0; 

   // double B0 = 61.742E+6/GAMMA_p; 
   // double B0 = 61.743E+6/GAMMA_p;  // I = 157.60 A  
   // double B0 = 61.930E+6/GAMMA_p;  // I = 157.62 A 
   // double B0 = 62.080E+6/GAMMA_p;  // I = 157.64 A 
   // double B0 = 62.154E+6/GAMMA_p;     // I = 157.66 A 
   double B0 = 61.754E+6/GAMMA_p;  // I = 157.60 A  
   double BA_avg=0,BA_avg_err=0;
   double BA_rel=0,BA_rel_err=0;  
   double BB_avg=0,BB_avg_err=0; 
   double BB_rel=0,BB_rel_err=0;  
   double BC_avg=0,BC_avg_err=0;
   double BC_rel=0,BC_rel_err=0;  
   double BD_avg=0,BD_avg_err=0; 
   double BD_rel=0,BD_rel_err=0; 
 
   FieldData myData; 
   TTree *myTree = new TTree("T","Field Data"); 
   myTree->Branch("field",&myData.x,"x/D:y/D:z/D:phi/D:B/D:dB/D:B_rel/D:dB_rel/D");

   int sw_a = 1; 
   int sw_b = 2; 
   int sw_c = 3; 
   int sw_d = 4; 
   vector<int> MechSw; 
  
   TString mech_path = Form("./data/%s/mech-sw.dat",date.Data());

   int dummy=0;
   int cntr=0,cntr2=4;  

   int color[6] = {kBlack,kRed,kBlue,kGreen+2,kMagenta,kCyan+1}; 
   int iColor=0; 

   TMultiGraph *mg1 = new TMultiGraph(); 
   TMultiGraph *mg2 = new TMultiGraph(); 
   TMultiGraph *mg3 = new TMultiGraph(); 
   TMultiGraph *mg4 = new TMultiGraph(); 

   TLegend *L1 = new TLegend(0.6,0.6,0.8,0.8); 
   L1->SetFillStyle(0); 
   TLegend *L2 = new TLegend(0.6,0.6,0.8,0.8); 
   L2->SetFillStyle(0); 
   TLegend *L3 = new TLegend(0.6,0.6,0.8,0.8); 
   L3->SetFillStyle(0); 
   TLegend *L4 = new TLegend(0.6,0.6,0.8,0.8); 
   L4->SetFillStyle(0); 

   int ia=0,ib=0,ic=0,id=0; 

   TString probe_a,probe_b,probe_c,probe_d; 

   const int N = Run.size();
   for(int i=0;i<N;i++){
      ImportData(data_path,Run[i],b);                              // read in data for a run (contains data for two probes) 
      ImportData2(data_path_2,Run[i],ampl,noise,zeroc);            // read in data for a run (contains data for two probes) 
      ImportMechSwParams(mech_path,Run[i],MechSw);
      // ParseDataTwoProbes(sw_a,sw_b,MechSw,ampl,noise,zc,b,BA,BB);     // parse data into two vectors: one for probe A, the other for probe B 
      ParseDataFourProbes(sw_a,sw_b,sw_c,sw_d,MechSw,ampl,noise,zeroc,b,BA,BB,BC,BD);     // parse data into four vectors: one each for A, B, C and D  
      // calculate coordinates 
      GetCoordinates(r_dsv,SlotA[i],Azi[i],th0,x_a,y_a,z_a,th_a); 
      GetCoordinates(r_dsv,SlotB[i],Azi[i],th0,x_b,y_b,z_b,th_b);
      GetCoordinates(r_dsv,SlotC[i],Azi[i],th0,x_c,y_c,z_c,th_c);
      GetCoordinates(r_dsv,SlotD[i],Azi[i],th0,x_d,y_d,z_d,th_d);
      // calculate statistics 
      BA_avg     = GetMean(BA);      
      BA_avg_err = GetStandardErrorOfTheMean(BA);      
      CalculateB_rel(B0,BA_avg,BA_avg_err,BA_rel,BA_rel_err);  
      BB_avg     = GetMean(BB);      
      BB_avg_err = GetStandardErrorOfTheMean(BB);  
      CalculateB_rel(B0,BB_avg,BB_avg_err,BB_rel,BB_rel_err); 
      BC_avg     = GetMean(BC);      
      BC_avg_err = GetStandardErrorOfTheMean(BC);      
      CalculateB_rel(B0,BC_avg,BC_avg_err,BC_rel,BC_rel_err);  
      BD_avg     = GetMean(BD);      
      BD_avg_err = GetStandardErrorOfTheMean(BD);  
      CalculateB_rel(B0,BD_avg,BD_avg_err,BD_rel,BD_rel_err); 
      if( cntr<32 ){  // number of azimuthal positions 
         FillVectors(x_a,y_a,z_a,th_a,BA_avg,BA_avg_err,BA_rel,BA_rel_err,xa,ya,za,pa,ba,ba_err,bar,bar_err); 
         FillVectors(x_b,y_b,z_b,th_b,BB_avg,BB_avg_err,BB_rel,BB_rel_err,xb,yb,zb,pb,bb,bb_err,bbr,bbr_err); 
         FillVectors(x_c,y_c,z_c,th_c,BC_avg,BC_avg_err,BC_rel,BC_rel_err,xc,yc,zc,pc,bc,bc_err,bcr,bcr_err); 
         FillVectors(x_d,y_d,z_d,th_d,BD_avg,BD_avg_err,BD_rel,BD_rel_err,xd,yd,zd,pd,bd,bd_err,bdr,bdr_err);
	 cntr++;
      }else{
         ia = SlotA[i-1]; // cntr2 - 3;  
         ib = SlotB[i-1]; // cntr2 - 2;  
         ic = SlotC[i-1]; // cntr2 - 1;  
         id = SlotD[i-1]; // cntr2; 
	 TGraphErrors *ga = GetTGraphErrors(pa,bar,bar_err); 
         TGraphErrors *gb = GetTGraphErrors(pb,bbr,bbr_err); 
         TGraphErrors *gc = GetTGraphErrors(pc,bcr,bcr_err); 
         TGraphErrors *gd = GetTGraphErrors(pd,bdr,bdr_err); 
         SetGraphParameters(ga,20,kBlack); 
         SetGraphParameters(gb,20,kBlack); 
         SetGraphParameters(gc,20,kBlack); 
         SetGraphParameters(gd,20,kBlack); 
         probe_a = prefix_pr + Form("probe-%d.dat",ia);
	 PrintToFile(probe_a,xa,ya,za,ba,ba_err,bar,bar_err); 
         probe_b = prefix_pr + Form("probe-%d.dat",ib);
	 PrintToFile(probe_b,xb,yb,zb,bb,bb_err,bbr,bbr_err); 
         probe_c = prefix_pr + Form("probe-%d.dat",ic);
	 PrintToFile(probe_c,xc,yc,zc,bc,bc_err,bcr,bcr_err); 
         probe_d = prefix_pr + Form("probe-%d.dat",id);
	 PrintToFile(probe_d,xd,yd,zd,bd,bd_err,bdr,bdr_err); 

	 if(cntr2>24) cntr2 = 4;
         cout << "cntr = " << cntr << "\t" << "ia = " << ia << "\t" << "ib = " << ib << "\t" << "ic = " << ic << "\t" << "id = " << id << endl;

         if(ia<7){
            iColor = GetColorIndex(ia);  
	    AddToMultiGraph(ga,ia,color[iColor],mg1,L1);
         }else if(ia<13){
            iColor = GetColorIndex(ia);  
	    AddToMultiGraph(ga,ia,color[iColor],mg2,L2);
         }else if(ia<19){
            iColor = GetColorIndex(ia);  
	    AddToMultiGraph(ga,ia,color[iColor],mg3,L3);
         }else if(ia<25){
            iColor = GetColorIndex(ia);  
	    AddToMultiGraph(ga,ia,color[iColor],mg4,L4);
         } 

         if(ib<7){
            iColor = GetColorIndex(ib);  
	    AddToMultiGraph(gb,ib,color[iColor],mg1,L1);
         }else if(ib<13){
            iColor = GetColorIndex(ib);  
	    AddToMultiGraph(gb,ib,color[iColor],mg2,L2);
         }else if(ib<19){
            iColor = GetColorIndex(ib);  
	    AddToMultiGraph(gb,ib,color[iColor],mg3,L3);
         }else if(ib<25){
            iColor = GetColorIndex(ib);  
	    AddToMultiGraph(gb,ib,color[iColor],mg4,L4);
         } 

         if(ic<7){
            iColor = GetColorIndex(ic);  
	    AddToMultiGraph(gc,ic,color[iColor],mg1,L1);
         }else if(ic<13){       
            iColor = GetColorIndex(ic);  
	    AddToMultiGraph(gc,ic,color[iColor],mg2,L2);
         }else if(ic<19){       
            iColor = GetColorIndex(ic);  
	    AddToMultiGraph(gc,ic,color[iColor],mg3,L3);
         }else if(ic<25){       
            iColor = GetColorIndex(ic);  
	    AddToMultiGraph(gc,ic,color[iColor],mg4,L4);
         } 

         if(id<7){
            iColor = GetColorIndex(id);  
	    AddToMultiGraph(gd,id,color[iColor],mg1,L1);
         }else if(id<13){       
            iColor = GetColorIndex(id);  
	    AddToMultiGraph(gd,id,color[iColor],mg2,L2);
         }else if(id<19){       
            iColor = GetColorIndex(id);  
	    AddToMultiGraph(gd,id,color[iColor],mg3,L3);
         }else if(id<25){      
            iColor = GetColorIndex(id);  
	    AddToMultiGraph(gd,id,color[iColor],mg4,L4);
         } 

	 cntr2 += 4;
	 cntr   = 0;
         ia = SlotA[i-1] + 4; // cntr2 - 3;  
         ib = SlotB[i-1] + 4; // cntr2 - 2;  
         ic = SlotC[i-1] + 4; // cntr2 - 1;  
         id = SlotD[i-1] + 4; // cntr2; 
 
         ClearVectors(xa,ya,za,pa,ba,ba_err,bar,bar_err); 
         ClearVectors(xb,yb,zb,pb,bb,bb_err,bbr,bbr_err); 
         ClearVectors(xc,yc,zc,pc,bc,bc_err,bcr,bcr_err); 
         ClearVectors(xd,yd,zd,pd,bd,bd_err,bdr,bdr_err);
         // keep the current data point, it's apart of the next data set 
         cntr++;  
         FillVectors(x_a,y_a,z_a,th_a,BA_avg,BA_avg_err,BA_rel,BA_rel_err,xa,ya,za,pa,ba,ba_err,bar,bar_err); 
         FillVectors(x_b,y_b,z_b,th_b,BB_avg,BB_avg_err,BB_rel,BB_rel_err,xb,yb,zb,pb,bb,bb_err,bbr,bbr_err); 
         FillVectors(x_c,y_c,z_c,th_c,BC_avg,BC_avg_err,BC_rel,BC_rel_err,xc,yc,zc,pc,bc,bc_err,bcr,bcr_err); 
         FillVectors(x_d,y_d,z_d,th_d,BD_avg,BD_avg_err,BD_rel,BD_rel_err,xd,yd,zd,pd,bd,bd_err,bdr,bdr_err);
      }
      cout << "RUN: " << Run[i] << endl;
      cout << "B0 = " << Form("%.10lf",B0) << endl;  
      cout << x_a << "\t" << y_a << "\t" << z_a << endl;
      cout << x_b << "\t" << y_b << "\t" << z_b << endl;
      cout << x_c << "\t" << y_c << "\t" << z_c << endl;
      cout << x_d << "\t" << y_d << "\t" << z_d << endl;
      if( (TMath::Abs(x_a)<500)&&(TMath::Abs(y_a)<500) &&(TMath::Abs(z_a)<500) ){  
	 // probe A 
	 myData.x      = x_a;        
	 myData.y      = y_a;        
	 myData.z      = z_a;        
	 myData.phi    = th_a;        
	 myData.B      = BA_avg;     
	 myData.dB     = BA_avg_err; 
	 myData.B_rel  = BA_rel;      
	 myData.dB_rel = BA_rel_err; 
	 X1.push_back(x_a);        
	 Y1.push_back(y_a);        
	 Z1.push_back(z_a);        
	 P1.push_back(th_a);        
	 B1A.push_back(BA_avg);     
	 dB1A.push_back(BA_avg_err); 
	 B1R.push_back(BA_rel);      
	 dB1R.push_back(BA_rel_err); 
	 myTree->Fill(); 
	 cout << "probe A: " << SlotA[i] 
	    << " x = "     << Form("%.3lf" ,x_a) 
	    << " y = "     << Form("%.3lf" ,y_a) 
	    << " z = "     << Form("%.3lf" ,z_a) 
	    << " th = "    << Form("%.3lf" ,th_a) 
	    << " B = "     << Form("%.10lf",BA_avg) << " +/- " << Form("%.10lf",BA_avg_err) << " " 
	    << " ("        << Form("%.3lf" ,BA_rel) << " +/- " << Form("%.3lf" ,BA_rel_err)  << " ppm)" << endl; 
      } 
      if( (TMath::Abs(x_b)<500)&&(TMath::Abs(y_b)<500) &&(TMath::Abs(z_b)<500) ){  
	 // probe B 
	 myData.x      = x_b;        
	 myData.y      = y_b;        
	 myData.z      = z_b;        
	 myData.phi    = th_b;        
	 myData.B      = BB_avg;     
	 myData.dB     = BB_avg_err; 
	 myData.B_rel  = BB_rel;      
	 myData.dB_rel = BB_rel_err;  
	 X2.push_back(x_b);        
	 Y2.push_back(y_b);        
	 Z2.push_back(z_b);        
	 P2.push_back(th_b);        
	 B2A.push_back(BB_avg);     
	 dB2A.push_back(BB_avg_err); 
	 B2R.push_back(BB_rel);      
	 dB2R.push_back(BB_rel_err); 
	 myTree->Fill(); 
	 cout << "probe B: " << SlotB[i] 
	    << " x = "     << Form("%.3lf" ,x_b) 
	    << " y = "     << Form("%.3lf" ,y_b) 
	    << " z = "     << Form("%.3lf" ,z_b) 
	    << " th = "    << Form("%.3lf" ,th_b) 
	    << " B = "     << Form("%.10lf",BB_avg) << " +/- " << Form("%.10lf",BB_avg_err) << " " 
	    << " ("        << Form("%.3lf" ,BB_rel)  << " +/- " << Form("%.3lf" ,BB_rel_err) << " ppm)" << endl; 

       }  
      if( (TMath::Abs(x_c)<500)&&(TMath::Abs(y_c)<500) &&(TMath::Abs(z_c)<500) ){  
	 // probe C 
	 myData.x      = x_c;        
	 myData.y      = y_c;        
	 myData.z      = z_c;        
	 myData.phi    = th_c;        
	 myData.B      = BC_avg;     
	 myData.dB     = BC_avg_err; 
	 myData.B_rel  = BC_rel;      
	 myData.dB_rel = BC_rel_err; 
	 X3.push_back(x_c);        
	 Y3.push_back(y_c);        
	 Z3.push_back(z_c);        
	 P3.push_back(th_c);        
	 B3A.push_back(BC_avg);     
	 dB3A.push_back(BC_avg_err); 
	 B3R.push_back(BC_rel);      
	 dB3R.push_back(BC_rel_err); 
	 myTree->Fill(); 
	 cout << "probe C: " << SlotC[i] 
	    << " x = "     << Form("%.3lf" ,x_c) 
	    << " y = "     << Form("%.3lf" ,y_c) 
	    << " z = "     << Form("%.3lf" ,z_c) 
	    << " th = "    << Form("%.3lf" ,th_c) 
	    << " B = "     << Form("%.10lf",BC_avg) << " +/- " << Form("%.10lf",BC_avg_err) << " " 
	    << " ("        << Form("%.3lf" ,BC_rel) << " +/- " << Form("%.3lf" ,BC_rel_err)  << " ppm)" << endl; 

      } 
      if( (TMath::Abs(x_d)<500)&&(TMath::Abs(y_d)<500) &&(TMath::Abs(z_d)<500) ){  
	 // probe D 
	 myData.x      = x_d;        
	 myData.y      = y_d;        
	 myData.z      = z_d;        
	 myData.phi    = th_d;        
	 myData.B      = BD_avg;     
	 myData.dB     = BD_avg_err; 
	 myData.B_rel  = BD_rel;      
	 myData.dB_rel = BD_rel_err;  
	 X4.push_back(x_b);        
	 Y4.push_back(y_b);        
	 Z4.push_back(z_b);        
	 P4.push_back(th_b);        
	 B4A.push_back(BD_avg);     
	 dB4A.push_back(BD_avg_err); 
	 B4R.push_back(BD_rel);      
	 dB4R.push_back(BD_rel_err); 
	 myTree->Fill();  
         cout << "probe D: " << SlotD[i] 
            << " x = "     << Form("%.3lf" ,x_d) 
            << " y = "     << Form("%.3lf" ,y_d) 
            << " z = "     << Form("%.3lf" ,z_d) 
            << " th = "    << Form("%.3lf" ,th_d) 
            << " B = "     << Form("%.10lf",BD_avg) << " +/- " << Form("%.10lf",BD_avg_err) << " " 
            << " ("        << Form("%.3lf" ,BD_rel)  << " +/- " << Form("%.3lf" ,BD_rel_err) << " ppm)" << endl; 
      }
      cout << "=========================================================================================================================" << endl;
      // get ready for next run 
      b.clear(); 
      BA.clear();
      BB.clear();
      BC.clear();
      BD.clear();
      MechSw.clear();
      ampl.clear();
      noise.clear();
      zeroc.clear();
   } 

   TGraphErrors *ga = GetTGraphErrors(pa,bar,bar_err); 
   TGraphErrors *gb = GetTGraphErrors(pb,bbr,bbr_err); 
   TGraphErrors *gc = GetTGraphErrors(pc,bcr,bcr_err); 
   TGraphErrors *gd = GetTGraphErrors(pd,bdr,bdr_err); 
   SetGraphParameters(ga,20,kBlack); 
   SetGraphParameters(gb,20,kBlack); 
   SetGraphParameters(gc,20,kBlack); 
   SetGraphParameters(gd,20,kBlack);

   iColor = GetColorIndex(21); 
   AddToMultiGraph(ga,21,color[iColor],mg4,L4);
   iColor = GetColorIndex(22); 
   AddToMultiGraph(gb,22,color[iColor],mg4,L4);
   iColor = GetColorIndex(23); 
   AddToMultiGraph(gc,23,color[iColor],mg4,L4);
   iColor = GetColorIndex(24); 
   AddToMultiGraph(gd,24,color[iColor],mg4,L4);

   TString outpath_a = Form("./probe/probe-11.dat");
   TString outpath_b = Form("./probe/probe-12.dat");
   TString outpath_c = Form("./probe/probe-13.dat");
   TString outpath_d = Form("./probe/probe-14.dat");

   PrintToFile(outpath_a,xa,ya,za,ba,ba_err,bar,bar_err); 
   PrintToFile(outpath_b,xb,yb,zb,bb,bb_err,bbr,bbr_err); 
   PrintToFile(outpath_c,xc,yc,zc,bc,bc_err,bcr,bcr_err); 
   PrintToFile(outpath_d,xd,yd,zd,bd,bd_err,bdr,bdr_err); 

   myTree->SetMarkerStyle(20); 
   myTree->SetMarkerSize(1.6);

   TCanvas *c1 = new TCanvas("c1");
   c1->SetFillColor(kWhite);
   c1->cd(); 

   if(PlotGIF){
      for (int i=0; i<360; i+=5){
         gPad->SetPhi(i);gPad->SetTheta(15);
         gPad->Update();
         if (i==0){
            c1->Print("anim.gif+10(");
         }else{
            c1->Print("anim.gif+");
         }
      }  
      gPad->SetPhi(25);
      gPad->SetTheta(15);
      gPad->Update();
      c1->Print("anim.gif++)");
   }else{
      myTree->Draw("y:x:z:B_rel","","colz");
   }
  
   TCanvas *c2 = new TCanvas("c2","Probe vs Azimuth",1200,800);
   c2->SetFillColor(kWhite);
   c2->Divide(2,2);

   c2->cd(1); 
   mg1->Draw("a");
   mg1->SetTitle("Probes 1-6");
   mg1->GetXaxis()->SetTitle("Angular position (deg)");  
   mg1->GetXaxis()->CenterTitle(); 
   mg1->GetYaxis()->SetTitle("B (ppm)");  
   mg1->GetYaxis()->CenterTitle();   
   mg1->Draw("a");
   L1->Draw("same");
   c2->Update();

   c2->cd(2); 
   mg2->Draw("a");
   mg2->SetTitle("Probes 7-12");
   mg2->GetXaxis()->SetTitle("Angular position (deg)");  
   mg2->GetXaxis()->CenterTitle(); 
   mg2->GetYaxis()->SetTitle("B (ppm)");  
   mg2->GetYaxis()->CenterTitle();   
   mg2->Draw("a");
   L2->Draw("same");
   c2->Update();

   c2->cd(3); 
   mg3->Draw("a");
   mg3->SetTitle("Probes 13-18");
   mg3->GetXaxis()->SetTitle("Angular position (deg)");  
   mg3->GetXaxis()->CenterTitle(); 
   mg3->GetYaxis()->SetTitle("B (ppm)");  
   mg3->GetYaxis()->CenterTitle();   
   mg3->Draw("a");
   L3->Draw("same");
   c2->Update();

   c2->cd(4); 
   mg4->Draw("a");
   mg4->SetTitle("Probes 19-24");
   mg4->GetXaxis()->SetTitle("Angular position (deg)");  
   mg4->GetXaxis()->CenterTitle(); 
   mg4->GetYaxis()->SetTitle("B (ppm)");  
   mg4->GetYaxis()->CenterTitle();   
   mg4->Draw("a");
   L4->Draw("same");
   c2->Update();

}
//______________________________________________________________________________
void FillVectors(double x,double y,double z,double th,double b,double b_err,double br,double br_err,
                 vector<double> &vx,vector<double> &vy,vector<double> &vz,vector<double> &vth,
                 vector<double> &vb,vector<double> &vb_err,vector<double> &vbr,vector<double> &vbr_err){
   vx.push_back(x); 
   vy.push_back(y); 
   vz.push_back(z); 
   vth.push_back(th); 
   vb.push_back(b); 
   vb_err.push_back(b_err); 
   vbr.push_back(br); 
   vbr_err.push_back(br_err); 
}
//______________________________________________________________________________
void ClearVectors(vector<double> &vx,vector<double> &vy,vector<double> &vz,vector<double> &vth,
                  vector<double> &vb,vector<double> &vb_err,vector<double> &vbr,vector<double> &vbr_err){
   vx.clear(); 
   vy.clear(); 
   vz.clear(); 
   vth.clear(); 
   vb.clear(); 
   vb_err.clear(); 
   vbr.clear(); 
   vbr_err.clear(); 
}
//______________________________________________________________________________
void AddToMultiGraph(TGraph *g,int probe,int color,TMultiGraph *mg,TLegend *L){
   g->SetMarkerColor(color); 
   g->SetLineColor(color); 
   mg->Add(g,"cp"); 
   L->AddEntry(g,Form("Probe %d",probe),"p");
}
//______________________________________________________________________________
int GetColorIndex(int index){
   int color=0;
   if(index<7){
      color = index;
   }else if(index>=7 && index<13){
      color = index - 6; 
   }else if(index>=13 && index<19){
      color = index - 12;
   }else if(index>=19 && index<25){
      color = index - 18; 
   }
   return color-1; 
}
//______________________________________________________________________________
void PrintToFile(TString outpath,vector<double> x,vector<double> y,vector<double> z,
                 vector<double> B,vector<double> dB,
                 vector<double> Br,vector<double> dBr){
   const int N = x.size(); 
   ofstream outfile;
   outfile.open(outpath);
   if( outfile.fail() ){
      cout << "Cannot open the file: " << outpath << endl;
      exit(1);
   }else{
      for(int i=0;i<N;i++){
         outfile << Form("%15.3lf",x[i])     << "\t" 
                 << Form("%20.3lf",y[i]  )  << "\t" 
                 << Form("%20.3lf",z[i]  )  << "\t" 
                 << Form("%20.10lf",B[i] )  << "\t" 
                 << Form("%20.10lf",dB[i])  << "\t" 
                 << Form("%20.10lf",Br[i] ) << "\t" 
                 << Form("%20.10lf",dBr[i]) << endl;
      }
      outfile.close();
      cout << "The data has been written to the file: " << outpath << endl;
   }
}

