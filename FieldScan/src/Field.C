void CalculateB_rel(double B0,double B,double dB,double &Brel,double &dBrel); 
void CalculateB_rel_Vec(double B0,vector<double> B,vector<double> dB,vector<double> &Brel,vector<double> &dBrel); 

//______________________________________________________________________________
void CalculateB_rel(double B0,double B,double dB,double &Brel,double &dBrel){
   double ppm = 1E-6;
   double ppb = 1E-9;
   Brel       = (B - B0)/B0/ppm;
   dBrel      = dB/B0/ppm;
   
   int is_nan_1 = TMath::IsNaN(Brel); 
   int is_nan_2 = TMath::IsNaN(dBrel);

   if(is_nan_1)  Brel = -70000;  
   if(is_nan_2) dBrel = -70000;  

   // cout << B << " +/- " << dB << "\t" << "(" << Brel << " +/- " << dBrel << ")" << endl;

}
//______________________________________________________________________________
void CalculateB_rel_Vec(double B0,vector<double> B,vector<double> dB,vector<double> &Brel,vector<double> &dBrel){
 
   const int N = B.size(); 

   double ppm = 1E-6;
   double ppb = 1E-9;
   int is_nan_1 = 0; 
   int is_nan_2 = 0;
 
   double arg=0.,err=0; 
 
   for(int i=0;i<N;i++){
      arg        = (B[i] - B0)/B0/ppm;
      err        = dB[i]/B0/ppm;
      is_nan_1   = TMath::IsNaN(arg); 
      is_nan_2   = TMath::IsNaN(err);
      if(is_nan_1) arg = -70000;  
      if(is_nan_2) err = -70000; 
      Brel.push_back(arg);  
      dBrel.push_back(err); 
   }

   // cout << B << " +/- " << dB << "\t" << "(" << Brel << " +/- " << dBrel << ")" << endl;

}
