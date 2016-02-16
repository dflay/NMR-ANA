// Test out field scan code
// - coordinates of probes
// - 3D plot  

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
   double B;
   double dB;
   double B_rel;
   double dB_rel;
};

void Test(){

   TString prefix    = Form("./input/test/");
   TString run_path  = prefix + Form("runlist.dat"); 
   TString data_path = prefix + Form("results_pulse-stats-field.dat"); 

   vector<int> Run,SlotA,SlotB,Azi; 
   ImportRunParams(run_path,Run,SlotA,SlotB,Azi); 

   vector<double> b,BA,BB;
   vector<double> X,Y,Z;
   vector<double> B,dB,BR,dBR; 

   double th0=0,th_a=0,th_b=0; 
   double x_a=0,y_a=0,z_a=0; 
   double x_b=0,y_b=0,z_b=0; 

   // double B0 = 61.79E+6/GAMMA_p; 
   double B0 = 1.4513; 
   double BA_avg=0,BA_avg_err=0;
   double BA_rel=0,BA_rel_err=0;  
   double BB_avg=0,BB_avg_err=0; 
   double BB_rel=0,BB_rel_err=0;  
 
   FieldData myData; 
   TTree *myTree = new TTree("T","Field Data"); 
   myTree->Branch("field",&myData.x,"x/D:y/D:z/D:B/D:dB/D:B_rel/D:dB_rel/D");
 
   const int N = Run.size();
   for(int i=0;i<N;i++){
      ImportData(data_path,Run[i],b);  // read in data for a run (contains data for two probes) 
      ParseDataTwoProbes(b,BA,BB);     // parse data into two vectors: one for probe A, the other for probe B 
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
      cout << "RUN: " << Run[i] << endl;
      cout << "B0 = " << Form("%.10lf",B0) << endl;  
      cout << "probe A: " << SlotA[i] 
           << " x = "     << Form("%.3lf" ,x_a) 
           << " y = "     << Form("%.3lf" ,y_a) 
           << " z = "     << Form("%.3lf" ,z_a) 
           << " B = "     << Form("%.10lf",BB_avg) << " +/- " << Form("%.10lf",BB_avg_err) << " " 
           << " ("        << Form("%.3lf",BB_rel)  << " +/- " << Form("%.3lf",BB_rel_err)  << " ppm)" << endl; 
      cout << "probe B: " << SlotB[i] 
           << " x = "     << Form("%.3lf" ,x_b) 
           << " y = "     << Form("%.3lf" ,y_b) 
           << " z = "     << Form("%.3lf" ,z_b) 
           << " B = "     << Form("%.10lf",BA_avg) << " +/- " << Form("%.10lf",BA_avg_err) << " " 
           << " ("        << Form("%.3lf",BA_rel)  << " +/- " << Form("%.3lf",BA_rel_err) << " ppm)" << endl; 
      cout << "=========================================================================================================================" << endl;
      // fill vectors: we switch B and A when filling the field vectors
      // because we skip the first entry when parsing; this reverses the order 
      // probe A 
      X.push_back(x_a);  
      Y.push_back(y_a);  
      Z.push_back(z_a);  
      B.push_back(BB_avg);  
      dB.push_back(BB_avg_err);  
      BR.push_back(BB_rel);  
      dBR.push_back(BB_rel_err);  
      myData.x      = x_a;        // X[i];  
      myData.y      = y_a;        // Y[i];  
      myData.z      = z_a;        // Z[i];  
      myData.B      = BB_avg;     // B[i];  
      myData.dB     = BB_avg_err; // dB[i]; 
      myData.B_rel  = BB_rel;     // BR[i];  
      myData.dB_rel = BB_rel_err; // dBR[i]; 
      // probe B 
      X.push_back(x_b);  
      Y.push_back(y_b);  
      Z.push_back(z_b);  
      B.push_back(BA_avg);  
      dB.push_back(BA_avg_err); 
      BR.push_back(BA_rel);  
      dBR.push_back(BA_rel_err);  
      myData.x      = x_b;        // X[i];  
      myData.y      = y_b;        // Y[i];  
      myData.z      = z_b;        // Z[i];  
      myData.B      = BA_avg;     // B[i];  
      myData.dB     = BA_avg_err; // dB[i]; 
      myData.B_rel  = BA_rel;     // BR[i];  
      myData.dB_rel = BA_rel_err; // dBR[i]; 
      // fill tree 
      myTree->Fill();  
      // get ready for next run 
      b.clear(); 
      BA.clear();
      BB.clear();
   } 

   // double NBin = 100;
   // TH3F *h = new TH3F("h","h",NBin,0,0,NBin,0,0,NBin,0,0); 

   myTree->SetMarkerStyle(20); 
   myTree->SetMarkerSize(1.6);
   // myTree->Draw("x:y:z:B_rel>>h(100,-300,300,100,-300,300,100,-300,300,100,-1,1)","","colz");
   myTree->Draw("x:y:z:B_rel","","colz");
   // myTree->Draw("x:y:z","B_rel","colz");

}
