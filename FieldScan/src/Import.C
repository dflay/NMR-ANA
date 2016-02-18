void ImportData(TString inpath,int RunNumber,vector<double> &B); 
void ImportData2(TString inpath,int Run,vector<double> &Ampl,vector<double> &Noise);
void ImportRunParams(TString inpath,vector<int> &Run,vector<int> &SlotA,vector<int> &SlotB,vector<int> &Azi); 
void ImportMechSwParams(TString inpath,int Run,vector<int> &MechSw); 

//______________________________________________________________________________
void ImportData(TString inpath,int Run,vector<double> &B){

   int cntr=0;
   double irun,ipulse,iB_mid,iB_lin,iB_lsq,iB_fit,iB_ph;

   const int NLines = 1; 
   const int SIZE = 2048; 
   char buf[SIZE]; 

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      for(int i=0;i<NLines;i++) infile.getline(buf,SIZE);
      while( !infile.eof() ){
	 infile >> irun >> ipulse >> iB_mid >> iB_lin >> iB_lsq >> iB_fit >> iB_ph; 
         if(irun==Run){
	    cntr++;
	    // cout << cntr << "\t" << irun << "\t" << Form("%.15lf",iB_lsq) << endl;
	    B.push_back(iB_lsq);
         } 
      }
      infile.close(); 
   }

}
//______________________________________________________________________________
void ImportData2(TString inpath,int Run,vector<double> &Ampl,vector<double> &Noise){

   int irun=0,ipulse=0;
   int cntr=0;
   double iampl,inoise,izc,inc,ifa,ifb,ifc,ifd,ife;

   const int NLines = 1; 
   const int SIZE = 2048; 
   char buf[SIZE]; 

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      for(int i=0;i<NLines;i++) infile.getline(buf,SIZE);
      while( !infile.eof() ){
	 infile >> irun >> ipulse >> iampl >> inoise >> izc >> inc >> ifa >> ifb >> ifc >> ifd >> ife; 
         if(irun==Run){
            // cout << irun << "\t" << Form("%.5lf",iampl) << endl;
	    cntr++;
	    Ampl.push_back(iampl);
	    Noise.push_back(inoise); 
         } 
      }
      infile.close(); 
      // B.pop_back();
   }

}
//______________________________________________________________________________
void ImportRunParams(TString inpath,vector<int> &Run,vector<int> &SlotA,vector<int> &SlotB,vector<int> &Azi){

   int cntr=0;
   double irun,islota,islotb,iazi,iz;

   const int NLines = 1; 
   const int SIZE = 2048; 
   char buf[SIZE]; 

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      for(int i=0;i<NLines;i++) infile.getline(buf,SIZE);
      while( !infile.eof() ){
	 infile >> irun >> islota >> islotb >> iazi >> iz; 
	 cntr++;
	 // cout << irun << "\t" << islota << "\t" << islotb << "\t" << iazi << endl;
	 Run.push_back(irun);
	 SlotA.push_back(islota);
	 SlotB.push_back(islotb);
	 Azi.push_back(iazi);
      }
      Run.pop_back(); 
      SlotA.pop_back();
      SlotB.pop_back();
      Azi.pop_back();
      infile.close(); 
   }

}
//______________________________________________________________________________
void ImportMechSwParams(TString inpath,int Run,vector<int> &MechSw){

   int cntr=0,irun=0,ipulse=0,isw=0;

   const int NLines = 1; 
   const int SIZE = 2048; 
   char buf[SIZE]; 

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      while( !infile.eof() ){
	 infile >> irun >> ipulse >> isw; 
	 cntr++;
	 // cout << irun << "\t" << islota << "\t" << islotb << "\t" << iazi << endl;
	 if(irun==Run) MechSw.push_back(isw);
      }
      // MechSw.pop_back(); 
      infile.close(); 
   }

   int N = MechSw.size();
   if(N==0){
      cout << "No mechanical switch data!  Exiting..." << endl;
      exit(1);
   }

}
