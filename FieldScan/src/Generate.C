void GenerateData(TString prefix,int Run,int NPTS,double B,double dB); 
void GenerateRunList(TString prefix,int Run,int slot_a,int slot_b,int azi); 

//______________________________________________________________________________
void GenerateData(TString prefix,int Run,int NPTS,double B,double dB){

   double b_val=0,zero=0;  

   TString outpath = prefix + Form("results_pulse-stats-field.dat");

   ofstream outfile; 
   outfile.open(outpath,ios::app);
   if( outfile.fail() ){
      cout << "Cannot open the file: " << outpath << endl;
      exit(1);
   }else{
      for(int i=0;i<NPTS;i++){
         b_val = gRandom->Gaus(B,dB); 
	 outfile << Form("%d",Run        ) << "\t" 
                 << Form("%5d",i+1       ) << "\t" 
                 << Form("%20.15lf",b_val) << "\t" 
                 << Form("%20.15lf",b_val) << "\t" 
                 << Form("%20.15lf",b_val) << "\t" 
                 << Form("%20.15lf",zero ) << "\t"
                 << Form("%20.15lf",zero ) << endl; 
      }
      outfile.close();
      cout << "Data printed to file: " << outpath << endl; 
   }

}
//______________________________________________________________________________
void GenerateRunList(TString prefix,int Run,int slot_a,int slot_b,int azi){

   double b_val=0,zero=0;  

   TString outpath = prefix + Form("runlist.dat");

   ofstream outfile; 
   outfile.open(outpath,ios::app);
   if( outfile.fail() ){
      cout << "Cannot open the file: " << outpath << endl;
      exit(1);
   }else{
      outfile << Form("%d" ,Run   ) << "\t" 
	      << Form("%5d",slot_a) << "\t" 
	      << Form("%5d",slot_b) << "\t"
	      << Form("%5d",azi   ) << endl; 
      outfile.close();
      cout << "Data printed to file: " << outpath << endl; 
   }

}
