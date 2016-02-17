// Test out field scan code
// - coordinates of probes
// - 3D plot  

#include "TString.h"
#include "./src/Coordinates.C"
#include "./src/Math.C"
// #include "./src/Graph.C"
#include "./src/Import.C"
#include "./src/Parse.C"
#include "./src/Generate.C"
#include "./src/Field.C"

struct FieldData{
   double x;
   double y;
   double z;
   double B;
   double dB;
   double B_rel;
   double dB_rel;
};

void PrintToFile(TString outpath,vector<double> x,vector<double> y,vector<double> z,
                 vector<double> B,vector<double> dB, 
                 vector<double> Br,vector<double> dBr); 

void Test(){

   int M=0,D=0,Yr=0; 

   cout << "Enter date (M D Y): ";
   cin  >> M >> D >> Yr; 

   TString date; 

   if(M<10  && D<10)  date = Form("20%d/0%d_%d/0%d_0%d_%d/",Yr,M,Yr,M,D,Yr); 
   if(M>=10 && D<10)  date = Form("20%d/%d_%d/%d_0%d_%d/"  ,Yr,M,Yr,M,D,Yr); 
   if(M<10  && D>=10) date = Form("20%d/0%d_%d/0%d_%d_%d/" ,Yr,M,Yr,M,D,Yr); 
   if(M>=10 && D>=10) date = Form("20%d/%d_%d/%d_%d_%d/"   ,Yr,M,Yr,M,D,Yr); 

   TString prefix      = Form("./input/test/");
   TString prefix_alt  = Form("./output/%s",date.Data());
   TString run_path    = prefix + Form("runlist_new.dat"); 
   TString data_path   = prefix_alt + Form("results_pulse-stats-field.dat"); 
   TString data_path_2 = prefix_alt + Form("results_pulse-stats.dat"); 

   vector<int> Run,SlotA,SlotB,Azi; 
   ImportRunParams(run_path,Run,SlotA,SlotB,Azi); 

   vector<double> ampl,noise;
   vector<double> b,BA,BB;
   vector<double> X1,Y1,Z1;
   vector<double> X2,Y2,Z2;
   vector<double> B1A,dB1A,B1R,dB1R;
   vector<double> B2A,dB2A,B2R,dB2R;
   vector<double> B,dB,BR,dBR; 

   double th0=0,th_a=0,th_b=0; 
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
   myTree->Branch("field",&myData.x,"x/D:y/D:z/D:B/D:dB/D:B_rel/D:dB_rel/D");

   int sw_a = 3; 
   int sw_b = 4; 
   vector<int> MechSw; 
  
   TString mech_path;

   int dummy=0; 
 
   const int N = Run.size();
   for(int i=0;i<N;i++){
      mech_path = Form("./data/%s/mech-sw.dat",date.Data(),Run[i]);
      ImportData(data_path,Run[i],b);  // read in data for a run (contains data for two probes) 
      ImportData2(data_path_2,Run[i],ampl,noise);  // read in data for a run (contains data for two probes) 
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

      if( TMath::Abs(BA_rel)<1000 && TMath::Abs(BB_rel)< 1000 ){  
      // probe A 
      myData.x      = x_a;        
      myData.y      = y_a;        
      myData.z      = z_a;        
      myData.B      = BA_avg;     
      myData.dB     = BA_avg_err; 
      myData.B_rel  = BA_rel;      
      myData.dB_rel = BA_rel_err; 
      X1.push_back(x_a);        
      Y1.push_back(y_a);        
      Z1.push_back(z_a);        
      B1A.push_back(BA_avg);     
      dB1A.push_back(BA_avg_err); 
      B1R.push_back(BA_rel);      
      dB1R.push_back(BA_rel_err); 
      myTree->Fill();  
      // probe B 
      myData.x      = x_b;        
      myData.y      = y_b;        
      myData.z      = z_b;        
      myData.B      = BB_avg;     
      myData.dB     = BB_avg_err; 
      myData.B_rel  = BB_rel;      
      myData.dB_rel = BB_rel_err;  
      X2.push_back(x_b);        
      Y2.push_back(y_b);        
      Z2.push_back(z_b);        
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
           << " B = "     << Form("%.10lf",BA_avg) << " +/- " << Form("%.10lf",BA_avg_err) << " " 
           << " ("        << Form("%.3lf" ,BA_rel) << " +/- " << Form("%.3lf" ,BA_rel_err)  << " ppm)" << endl; 
      cout << "probe B: " << SlotB[i] 
           << " x = "     << Form("%.3lf" ,x_b) 
           << " y = "     << Form("%.3lf" ,y_b) 
           << " z = "     << Form("%.3lf" ,z_b) 
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

   TString outpath_a = Form("probe-a.dat");
   TString outpath_b = Form("probe-b.dat");

   PrintToFile(outpath_a,X1,Y1,Z1,B1A,dB1A,B1R,dB1R); 
   PrintToFile(outpath_b,X2,Y2,Z2,B2A,dB2A,B2R,dB2R); 

   // double NBin = 100;
   // TH3F *h = new TH3F("h","h",NBin,0,0,NBin,0,0,NBin,0,0); 

   myTree->SetMarkerStyle(20); 
   myTree->SetMarkerSize(1.6);
   // myTree->Draw("x:y:z:B_rel>>h(100,-300,300,100,-300,300,100,-300,300,100,-1,1)","","colz");
   // myTree->Draw("x:y:z:B_rel","","colz");
   // myTree->Draw("y:x:z:B_rel","","colz");
   // myTree->Draw("x:y:z","B_rel","colz");

   // myTree->Draw("x:y:z:B_rel>>h(100,-300,300,100,-300,300,100,-300,300,100,-1,1)","","colz");
   TCanvas *c1 = new TCanvas();
   myTree->Draw("x:y:z:B_rel","","colz");
   for (int i=0; i<360; i+=5){
      gPad->SetPhi(i);gPad->SetTheta(15);
      gPad->Update();
      if (i==0) c1->Print("anim.gif+10(");
      else c1->Print("anim.gif+");
   }  
   //gPad->SetPhi(25);gPad->SetTheta(15);
   //gPad->Update();
   c1->Print("anim.gif++)");
   // myTree->Draw("x:y:z","B_rel","colz");

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
         outfile << Form("%5.3lf",x[i])     << "\t" 
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
