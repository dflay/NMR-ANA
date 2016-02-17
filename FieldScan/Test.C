// Test out field scan code
// - coordinates of probes
// - 3D plot  

#include "TString.h"
#include "./src/Coordinates.C"
#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"
#include "./src/Parse.C"
#include "./src/Generate.C"
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

void AddToMultiGraph(TGraph *g,int probe,int color,TMultiGraph *mg,TLegend *L); 
void PrintToFile(TString outpath,vector<double> x,vector<double> y,vector<double> z,
                 vector<double> B,vector<double> dB, 
                 vector<double> Br,vector<double> dBr); 

void Test(){

   int M=0,D=0,Yr=0; 

   cout << "Enter date (M D Y): ";
   cin  >> M >> D >> Yr; 

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
   TString data_path   = prefix + Form("results_pulse-stats-field_%s.dat",mdy.Data()); 
   TString data_path_2 = prefix + Form("results_pulse-stats_%s.dat",mdy.Data()); 

   vector<int> Run,SlotA,SlotB,Azi; 
   ImportRunParams(run_path,Run,SlotA,SlotB,Azi); 

   vector<double> ampl,noise;
   vector<double> b,BA,BB;
   vector<double> X1,Y1,Z1,P1;
   vector<double> X2,Y2,Z2,P2;
   vector<double> B1A,dB1A,B1R,dB1R;
   vector<double> B2A,dB2A,B2R,dB2R;
   vector<double> B,dB,BR,dBR; 

   vector<double> Ppa,Bpa; 
   vector<double> Ppb,Bpb; 

   vector<double> xa,ya,za,pa,ba,ba_err,bar,bar_err; 
   vector<double> xb,yb,zb,pb,bb,bb_err,bbr,bbr_err; 

   double th0=0,thr_a=0,thr_b=0,th_a=0,th_b=0; 
   double x_a=0,y_a=0,z_a=0; 
   double x_b=0,y_b=0,z_b=0; 

   // double B0 = 61.79E+6/GAMMA_p; 
   // double B0 = 1.4513; 
   double B0 = 62.316E+6/GAMMA_p; 
   double BA_avg=0,BA_avg_err=0;
   double BA_rel=0,BA_rel_err=0;  
   double BB_avg=0,BB_avg_err=0; 
   double BB_rel=0,BB_rel_err=0;  
 
   FieldData myData; 
   TTree *myTree = new TTree("T","Field Data"); 
   myTree->Branch("field",&myData.x,"x/D:y/D:z/D:phi/D:B/D:dB/D:B_rel/D:dB_rel/D");

   int sw_a = 3; 
   int sw_b = 4; 
   vector<int> MechSw; 
  
   TString mech_path;

   int dummy=0;
   int cntr=0,cntr2=2;  

   int color[28] = {kOrange  ,kRed   ,kBlue  ,kGreen,
                    kOrange+1,kRed+1 ,kBlue+1,kGreen+1,
                    kOrange+2,kRed+2 ,kBlue+2,kGreen+2,
                    kOrange+3,kRed+3 ,kBlue+3,kGreen+3,
                    kOrange+4,kRed+4 ,kBlue+4,kGreen+4,
                    kOrange+5,kMagenta,kAzure+5,kTeal+7,
                    kCyan    ,kCyan+1,kCyan+2,kViolet
                   }; 

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

   TString probe_a,probe_b; 

   const int N = Run.size();
   for(int i=0;i<N;i++){
      // mech_path = Form("./data/%s/mech-sw.dat",date.Data());
      mech_path = prefix + Form("mech-sw_%s.dat",mdy.Data());
      ImportData(data_path,Run[i],b);                              // read in data for a run (contains data for two probes) 
      ImportData2(data_path_2,Run[i],ampl,noise);                  // read in data for a run (contains data for two probes) 
      ImportMechSwParams(mech_path,Run[i],MechSw);
      ParseDataTwoProbes(sw_a,sw_b,MechSw,ampl,noise,b,BA,BB);     // parse data into two vectors: one for probe A, the other for probe B 
      // calculate coordinates 
      GetCoordinates(SlotA[i],Azi[i],th0,x_a,y_a,z_a,th_a); 
      GetCoordinates(SlotB[i],Azi[i],th0,x_b,y_b,z_b,th_b);
      // calculate statistics 
      BA_avg     = GetMean(BA);      
      BA_avg_err = GetStandardErrorOfTheMean(BA);      
      BB_avg     = GetMean(BB);      
      BB_avg_err = GetStandardErrorOfTheMean(BB);  
      CalculateB_rel(B0,BA_avg,BA_avg_err,BA_rel,BA_rel_err);  
      CalculateB_rel(B0,BB_avg,BB_avg_err,BB_rel,BB_rel_err); 
      if( cntr<16 ){
         xa.push_back(x_a); 
         ya.push_back(y_a); 
         za.push_back(z_a); 
	 pa.push_back(th_a); 
	 ba.push_back(BA_avg); 
	 ba_err.push_back(BA_avg_err); 
	 bar.push_back(BA_rel); 
	 bar_err.push_back(BB_rel_err); 
         xb.push_back(x_b); 
         yb.push_back(y_b); 
         zb.push_back(z_b); 
	 pb.push_back(th_b); 
	 bb.push_back(BB_avg); 
	 bb_err.push_back(BB_avg_err); 
	 bbr.push_back(BB_rel); 
	 bbr_err.push_back(BB_rel_err); 
	 cntr++;
      }else{
	 TGraph *ga = GetTGraph(pa,bar); 
         TGraph *gb = GetTGraph(pb,bbr); 
         SetGraphParameters(ga,20,kBlack); 
         SetGraphParameters(gb,20,kBlack); 
         probe_a = Form("probe-%d.dat",cntr2-1);
	 PrintToFile(probe_a,xa,ya,za,ba,ba_err,bar,bar_err); 
         probe_b = Form("probe-%d.dat",cntr2);
	 PrintToFile(probe_b,xb,yb,zb,bb,bb_err,bbr,bbr_err); 
	 if(cntr2>24) cntr2 = 2; 
         cout << cntr << "\t" << cntr2 << endl;
         if(cntr2<7){
	    AddToMultiGraph(ga,cntr2-1,color[cntr2-1],mg1,L1);
	    AddToMultiGraph(gb,cntr2  ,color[cntr2]  ,mg1,L1);
         }else if(cntr2<13){
	    AddToMultiGraph(ga,cntr2-1,color[cntr2-1],mg2,L2);
	    AddToMultiGraph(gb,cntr2  ,color[cntr2]  ,mg2,L2);
         }else if(cntr2<19){
	    AddToMultiGraph(ga,cntr2-1,color[cntr2-1],mg3,L3);
	    AddToMultiGraph(gb,cntr2  ,color[cntr2]  ,mg3,L3);
         }else if(cntr2<25){
	    AddToMultiGraph(ga,cntr2-1,color[cntr2-1],mg4,L4);
	    AddToMultiGraph(gb,cntr2  ,color[cntr2]  ,mg4,L4);
         } 
	 cntr2 += 2;
	 cntr   = 0;
         xa.clear(); 
         ya.clear(); 
         za.clear(); 
         pa.clear();    
         ba.clear();  
         ba_err.clear();  
         bar.clear();    
         bar_err.clear();    
         pb.clear();    
         bb.clear();  
         bb_err.clear();  
         bbr.clear();  
         bbr_err.clear();  
         xb.clear(); 
         yb.clear(); 
         zb.clear(); 
         // keep the current data point, it's apart of the next data set 
         cntr++;  
	 pa.push_back(th_a); 
	 ba.push_back(BA_avg);
	 ba_err.push_back(BA_avg_err);
	 bar.push_back(BA_rel);
	 bar_err.push_back(BA_rel_err);
         xa.push_back(x_a);  
         ya.push_back(y_a);  
         za.push_back(z_a);  
	 pb.push_back(th_b); 
	 bb.push_back(BB_avg);
	 bb_err.push_back(BB_avg_err);
	 bbr.push_back(BB_rel); 
	 bbr_err.push_back(BB_rel_err); 
         xb.push_back(x_b);  
         yb.push_back(y_b);  
         zb.push_back(z_b);  
      }
      if( TMath::Abs(BA_rel)<1000 && TMath::Abs(BB_rel)< 1000 ){  
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
	 cout << "RUN: " << Run[i] << endl;
	 cout << "B0 = " << Form("%.10lf",B0) << endl;  
	 cout << "probe A: " << SlotA[i] 
	    << " x = "     << Form("%.3lf" ,x_a) 
	    << " y = "     << Form("%.3lf" ,y_a) 
	    << " z = "     << Form("%.3lf" ,z_a) 
	    << " th = "    << Form("%.3lf" ,th_a) 
	    << " B = "     << Form("%.10lf",BA_avg) << " +/- " << Form("%.10lf",BA_avg_err) << " " 
	    << " ("        << Form("%.3lf" ,BA_rel) << " +/- " << Form("%.3lf" ,BA_rel_err)  << " ppm)" << endl; 
	 cout << "probe B: " << SlotB[i] 
	    << " x = "     << Form("%.3lf" ,x_b) 
	    << " y = "     << Form("%.3lf" ,y_b) 
	    << " z = "     << Form("%.3lf" ,z_b) 
	    << " th = "    << Form("%.3lf" ,th_b) 
	    << " B = "     << Form("%.10lf",BB_avg) << " +/- " << Form("%.10lf",BB_avg_err) << " " 
	    << " ("        << Form("%.3lf" ,BB_rel)  << " +/- " << Form("%.3lf" ,BB_rel_err) << " ppm)" << endl; 
	 cout << "=========================================================================================================================" << endl;
	 // if( TMath::Abs(BA_rel)>160 || TMath::Abs(BB_rel)>160){ 
	 //    cin >> dummy;
	 // }
      }
      // get ready for next run 
      b.clear(); 
      BA.clear();
      BB.clear();
      MechSw.clear();
      ampl.clear();
      noise.clear();
   } 

   TGraph *ga = GetTGraph(pa,bar); 
   TGraph *gb = GetTGraph(pb,bbr); 
   SetGraphParameters(ga,20,kBlack); 
   SetGraphParameters(gb,20,kBlack); 
   AddToMultiGraph(ga,1,color[cntr2-1],mg1,L1);
   AddToMultiGraph(gb,2,color[cntr2]  ,mg1,L1);

   TString outpath_a = Form("probe-1a.dat");
   TString outpath_b = Form("probe-2a.dat");

   PrintToFile(outpath_a,xa,ya,za,ba,ba_err,bar,bar_err); 
   PrintToFile(outpath_b,xb,yb,zb,bb,bb_err,bbr,bbr_err); 

   myTree->SetMarkerStyle(20); 
   myTree->SetMarkerSize(1.6);

   TCanvas *c1 = new TCanvas("c1");
   c1->SetFillColor(kWhite);
   c1->cd(); 

   myTree->Draw("x:y:z:B_rel","","colz");
   // for (int i=0; i<360; i+=5){
   //    gPad->SetPhi(i);gPad->SetTheta(15);
   //    gPad->Update();
   //    if (i==0){
   //       c1->Print("anim.gif+10(");
   //    }else{
   //       c1->Print("anim.gif+");
   //    }
   // }  
   //gPad->SetPhi(25);gPad->SetTheta(15);
   //gPad->Update();
   // c1->Print("anim.gif++)");

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
void AddToMultiGraph(TGraph *g,int probe,int color,TMultiGraph *mg,TLegend *L){
   g->SetMarkerColor(color); 
   g->SetLineColor(color); 
   mg->Add(g,"cp"); 
   L->AddEntry(g,Form("Probe %d",probe),"p");
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
