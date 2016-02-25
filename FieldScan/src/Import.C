void ImportData(TString inpath,int RunNumber,vector<double> &B); 
void ImportData2(TString inpath,int Run,vector<double> &Ampl,vector<double> &Noise,vector<double> &ZC);
void ImportScanData(TString inpath,vector<double> &z,vector<double> &B,vector<double> &dB); 
void ImportRunParams2(TString inpath,vector<int> &Run,vector<int> &SlotA,vector<int> &SlotB,vector<int> &Azi); 
void ImportRunParams4(TString inpath,vector<int> &Run,
                      vector<int> &SlotA,vector<int> &SlotB,vector<int> &SlotC,vector<int> &SlotD,vector<int> &Azi); 
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
void ImportData2(TString inpath,int Run,vector<double> &Ampl,vector<double> &Noise,vector<double> &ZC){

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
            // cout << irun << "\t" << ipulse << "\t" << Form("%.5lf",ifc) << endl;
	    cntr++;
	    Ampl.push_back(iampl);
	    Noise.push_back(inoise); 
            ZC.push_back(izc); 
         } 
      }
      infile.close(); 
      // B.pop_back();
   }

}
//______________________________________________________________________________
void ImportScanData(TString inpath,vector<double> &z,vector<double> &B,vector<double> &dB){

   int cntr=0;
   double ix,iy,iz,ib,idb,ibr,idbr;

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      while( !infile.eof() ){
	 infile >> ix >> iy >> iz >> ib >> idb >> ibr >> idbr; 
	 z.push_back(iz);
         B.push_back(ib);
         dB.push_back(idb);
      }
      infile.close(); 
   }

}
//______________________________________________________________________________
void ImportRunParams2(TString inpath,vector<int> &Run,vector<int> &SlotA,vector<int> &SlotB,vector<int> &Azi){

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
void ImportRunParams4(TString inpath,vector<int> &Run,
                      vector<int> &SlotA,vector<int> &SlotB,vector<int> &SlotC,vector<int> &SlotD,vector<int> &Azi){

   int cntr=0;
   double irun,islota,islotb,islotc,islotd,iazi,iz;

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
	 infile >> irun >> islota >> islotb >> islotc >> islotd >> iazi >> iz; 
	 cntr++;
	 // cout << irun << "\t" << islota << "\t" << islotb << "\t" << iazi << endl;
	 Run.push_back(irun);
	 SlotA.push_back(islota);
	 SlotB.push_back(islotb);
	 SlotC.push_back(islotc);
	 SlotD.push_back(islotd);
	 Azi.push_back(iazi);
      }
      Run.pop_back(); 
      SlotA.pop_back();
      SlotB.pop_back();
      SlotC.pop_back();
      SlotD.pop_back();
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
	 if(irun==Run){
            MechSw.push_back(isw);
            // cout << irun << "\t" << ipulse << "\t" << isw << endl;
         }
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
