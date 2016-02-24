void ParseDataFourProbes(int sw_a,int sw_b,int sw_c,int sw_d,
                         vector<int> MechSw,vector<double> ampl,vector<double> noise,vector<double> zc,
                         vector<double> B,vector<double> &B1,vector<double> &B2,vector<double> &B3,vector<double> &B4); 
void ParseDataTwoProbes(vector<int> MechSw,vector<double> ampl,vector<double> noise,vector<double> zc,vector<double> B,vector<double> &B1,vector<double> &B2); 
void ParseDataTwoProbes(vector<double> B,vector<double> &B1,vector<double> &B2); 
void ParseData(int run,vector<double> Ampl,vector<double> B,vector<double> &B1,vector<double> &B2); 
void ParseData(int run,vector<double> Ampl,vector<double> Noise,vector<double> B,vector<double> &B1,vector<double> &B2); 
void DeleteZeroes(vector<double> &v); 

//______________________________________________________________________________
void ParseDataFourProbes(int sw_a,int sw_b,int sw_c,int sw_d,
                         vector<int> MechSw,vector<double> ampl,vector<double> noise,vector<double> zc,
                         vector<double> B,vector<double> &B1,vector<double> &B2,vector<double> &B3,vector<double> &B4){

   const int N = B.size();

   int start = 2;  // leave off the first pulse (sometimes is garbage)  
   int end   = N; 
   int dummy = 0;  

   // cout << "LAST PULSE: " << N << endl;

   for(int i=start;i<end;i++){
      if( (ampl[i]>0.050 && ampl[i]<2.00)&&(ampl[i] > noise[i])&&(zc[i]>5) ){
         if(MechSw[i]==sw_a) B1.push_back(B[i]); 
         if(MechSw[i]==sw_b) B2.push_back(B[i]);
         if(MechSw[i]==sw_c) B3.push_back(B[i]);
         if(MechSw[i]==sw_d) B4.push_back(B[i]);
      }else{
         cout << "REJECTED: pulse "        << i+1 << "\t" 
              << "ampl = "    << ampl[i]   << "\t" 
              << "noise = "   << noise[i]  << "\t" 
              << "zc = "      << zc[i]     << "\t" 
              << "mech-sw = " << MechSw[i] << "\t" 
              << "B = "       << B[i]      << endl;
         // cin  >> dummy; 
      } 
   }

}
//______________________________________________________________________________
void ParseDataTwoProbes(vector<double> B,vector<double> &B1,vector<double> &B2){

   const int N = B.size();

   int start = 1;  // leave off the first pulse (sometimes is garbage)   

   // probe 1
   for(int i=start;i<N;i+=2){
      B1.push_back(B[i]); 
   }
   // probe 2 
   for(int i=start+1;i<N;i+=2){
      B2.push_back(B[i]); 
   }

}
//______________________________________________________________________________
void ParseData(int run,vector<double> Ampl,vector<double> B,vector<double> &B1,vector<double> &B2){

   const int N = B.size();

   vector<double> a,b; 

   int cntr=0;
   double arg=0;

   // probe 1
   for(int i=0;i<N;i+=2){
      B1.push_back(B[i]); 
   }
   // probe 2 
   for(int i=1;i<N;i+=2){
      B2.push_back(B[i]); 
   }

}
//______________________________________________________________________________
void ParseDataAlt(int run,vector<double> Ampl,vector<double> Noise,vector<double> B,vector<double> &B1,vector<double> &B2){

   const int N = B.size();

   vector<double> a,b;
   vector<double> A1,A2;  

   int cntr=0;
   double arg=0;

   // choose all entries with a reasonable voltage
 
   cout << "SORTING" << endl;

   for(int i=0;i<N;i++){
      if( (Ampl[i]>0.1) && (Ampl[i]<2) && (B[i]!=0) && (Ampl[i]>Noise[i])  ){
	 b.push_back(B[i]);
	 a.push_back(Ampl[i]); 
	 // cout << i << "\t" << Form("%.5lf",Ampl[i]) << "\t" << Form("%.15lf",B[i]) << "\t" << cntr << "\t" << Form("%.15lf",b[cntr]) << endl;
	 cntr++;
      } 
   }

   cout << cntr << endl;

   // special sorting: if the amplitude for entry i is less than that of entry i-1, it's 
   // entry i is for probe 2, and vice-versa. 

   int M = b.size(); 
   for(int i=1;i<M-2;i+=2){
      if(a[i]<a[i-1]){
	 B2.push_back(b[i]); 
	 B1.push_back(b[i-1]); 
	 A2.push_back(a[i]); 
	 A1.push_back(a[i-1]); 
      }else{
	 B2.push_back(b[i-1]); 
	 B1.push_back(b[i]); 
	 A2.push_back(a[i-1]); 
	 A1.push_back(a[i]); 
      } 
   }

   // now delete all zeroes 
   DeleteZeroes(B1);
   DeleteZeroes(B2);

   int M1 = B1.size();
   int M2 = B2.size();

   if(M1==M2){
	 for(int i=0;i<M1;i++){
	    cout << Form("%.15lf",A1[i]) << "\t" << Form("%.15lf",B1[i]) << "\t" 
	         << Form("%.15lf",A2[i]) << "\t" << Form("%.15lf",B2[i]) << endl; 
	 }
   }else{
      do{
	 if(M1>M2) B1.pop_back();
	 if(M2>M1) B2.pop_back();
	 M1 = B1.size();
	 M2 = B2.size();
	 cout << "M1 = " << M1 << "\t" << "M2 = " << M2 << endl;
      }while(M1!=M2); 
   }
    

}
//______________________________________________________________________________
void DeleteZeroes(vector<double> &v){
   int N = v.size();
   vector<double> w; 
   for(int i=0;i<N;i++){
      if(v[i]!=0) w.push_back(v[i]); 
   }
   v.clear(); 
   int M = w.size();
   for(int i=0;i<M;i++) v.push_back(w[i]); 
}

