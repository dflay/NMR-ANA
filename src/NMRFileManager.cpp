#include "NMRFileManager.h"
//______________________________________________________________________________
NMRFileManager::NMRFileManager(){
   fOffsetFail    = false;
   fVerbosity     = 0; 
   fNPTS          = 0;
   fNCycles       = 10;  
   fSIZE          = 10E+6; 
   fTStart        = 0;    // 0 s 
   fTEnd          = 100;  // 100 s 
   fDataDir       = new char[200]();   // initializes to '0' 
   fOutputBaseDir = new char[200](); 
   fOutputDir     = new char[200](); 
   InputManager   = new NMRInputManager();  
   const int N    = fSIZE; 
   fSample        = new int[N]; 
   fADCCounts     = new unsigned short[N]; 
   fTime          = new double[N]; 
   fVoltage       = new double[N]; 
   fX             = new double[N]; 
   fY             = new double[N]; 
   fEY            = new double[N]; 
   fNCrossing     = new int[N];
   fCrossingIndex = new int[N];
   fTcross        = new double[N];
   fVcross        = new double[N];
   ClearDataArrays(); 
}
//______________________________________________________________________________
NMRFileManager::~NMRFileManager(){
   delete[] fSample; 
   delete[] fADCCounts;
   delete[] fTime;
   delete[] fVoltage;
   delete[] fX; 
   delete[] fY; 
   delete[] fEY;
   delete[] fNCrossing;
   delete[] fCrossingIndex;
   delete[] fTcross;
   delete[] fVcross; 
   delete[] fDataDir; 
   delete[] fOutputBaseDir; 
   delete[] fOutputDir;
   delete InputManager;  
}
//______________________________________________________________________________
NMRFileManager::NMRFileManager(const NMRFileManager &fm){
   // copy constructor 
   // shallow copy 
   fOffsetFail    = fm.GetOffsetStatus();  
   fTStart        = 0;    // 0 s 
   fTEnd          = 100;  // 100 s 
   fNPTS          = 0;  
   fNCycles       = 10;  
   fSIZE          = 1E+6; 
   // deep copy 
   InputManager   = new NMRInputManager(fm.InputManager);  
   fDataDir       = new char[200](); 
   fOutputBaseDir = new char[200](); 
   fOutputDir     = new char[200](); 
   strcpy(fDataDir      ,fm.GetDataDir()       ); 
   strcpy(fOutputBaseDir,fm.GetOutputBaseDir() ); 
   strcpy(fOutputDir    ,fm.GetOutputDir()     ); 

}
//______________________________________________________________________________
NMRFileManager::NMRFileManager(const NMRFileManager *fm){
   // copy constructor 
   // shallow copy 
   fOffsetFail    = fm->GetOffsetStatus();  
   fTStart        = 0;    // 0 s 
   fTEnd          = 100;  // 100 s 
   fNPTS          = 0;  
   fNCycles       = 10;  
   fSIZE          = 1E+6; 
   // deep copy 
   InputManager   = new NMRInputManager(fm->InputManager);  
   fDataDir       = new char[200](); 
   fOutputBaseDir = new char[200](); 
   fOutputDir     = new char[200](); 
   strcpy(fDataDir      ,fm->GetDataDir()       ); 
   strcpy(fOutputBaseDir,fm->GetOutputBaseDir() ); 
   strcpy(fOutputDir    ,fm->GetOutputDir()     ); 
}
//______________________________________________________________________________
void NMRFileManager::ClearDataArrays(){
   for(int i=0;i<fSIZE;i++){
      fSample[i]    = 0; 
      fADCCounts[i] = 0; 
      fTime[i]      = 0; 
      fVoltage[i]   = 0; 
      fX[i]         = 0; 
      fY[i]         = 0; 
      fEY[i]        = 0; 
   }
}
//______________________________________________________________________________
void NMRFileManager::ClearNZCArrays(){
   for(int i=0;i<fSIZE;i++){
      fNCrossing[i]     = 0; 
      fCrossingIndex[i] = 0;
      fTcross[i]        = 0; 
      fVcross[i]        = 0; 
   }
}
//______________________________________________________________________________
void NMRFileManager::GetInputParameters(const char *inpath){
   InputManager->GetInputParameters(inpath);
   // InputManager->Print(); 
   fVerbosity = InputManager->GetVerbosity(); 
}
//______________________________________________________________________________
void NMRFileManager::Update(const NMRFileManager *fm){
   UpdateInputManager(fm->InputManager);
}
//______________________________________________________________________________
void NMRFileManager::UpdateInputManager(const NMRInputManager *a){
   // update the input manager when we read in data from a run's summary file 
   InputManager->Update(a);    
}
//______________________________________________________________________________
int NMRFileManager::DeleteSymLink(const char *suffix){

   int rc = 0; 

   const int SIZE = 200;
   char *full_path = new char[SIZE];
   sprintf(full_path,"%s/%s",fOutputDir,suffix); 

   // check to see if the symbolic link exists
   if( (stat(full_path,&fSB)==0)&&(S_ISLNK(fSB.st_mode)) ){
      // the symbolic link exists!  Delete it  
      rc = remove(full_path); 
   }else{
      // symbolic link doesn't exist, do nothing 
   }

   if(rc!=0) std::cout << "[NMRFileManager]: Cannot delete the symbolic link: " << full_path << std::endl;

   delete[] full_path; 

   return rc;
}
//______________________________________________________________________________
bool NMRFileManager::CheckIfExists(const char *name){
   struct stat buffer;   
   return (stat (name, &buffer) == 0); 
}
//______________________________________________________________________________
bool NMRFileManager::RunExists(int runNumber){
   char path[200]; 
   sprintf(path,"./output/run-%05d/",runNumber); 
   bool state = CheckIfDirectoryExists(path);
   return state; 
}
//______________________________________________________________________________
int NMRFileManager::DeleteRun(int runNumber){
   char path[200]; 
   sprintf(path,"./output/run-%05d/",runNumber); 
   int rc = DeleteDirectory(path); 
   return rc; 
}
//______________________________________________________________________________
bool NMRFileManager::CheckIfDirectoryExists(const char *path){
   int rc = boost::filesystem::exists(path);
   return rc;
}
//______________________________________________________________________________
int NMRFileManager::DeleteFile(const char *file){

   int rc = 0; 

   const int SIZE = 200;
   char *full_path = new char[SIZE];
   sprintf(full_path,"%s/%s",fOutputDir,file); 

   // check to see if the file exists
   if( (stat(full_path,&fSB)==0)&&(S_ISREG(fSB.st_mode)) ){
      // the file exists!  Delete it  
      rc = remove(full_path); 
   }else{
      // file doesn't exist, do nothing 
   }

   if(rc!=0) std::cout << "[NMRFileManager]: Cannot delete the file: " << full_path << std::endl;

   delete[] full_path; 

   return rc;
}
//______________________________________________________________________________
int NMRFileManager::DeleteDirectory(const char *path){
   int rc=0;
   if( boost::filesystem::exists(path) ) rc = boost::filesystem::remove_all(path);
   return rc;
}
//______________________________________________________________________________
int NMRFileManager::MakeDirectory(const char *path){

   int rc=0; 

   const int SIZE = 200;
   char *dir_path = new char[SIZE]; 

   sprintf(dir_path,"%s",path);

   // check to see if the directory exists
   if( (stat(dir_path,&fSB)==0)&&(S_ISDIR(fSB.st_mode)) ){
      // the directory exists!  Do nothing.  
      // You can also check for other file types using other S_IS* macros:
      // S_ISDIR — directory
      // S_ISREG — regular file
      // S_ISCHR — character device
      // S_ISBLK — block device
      // S_ISFIFO — FIFO
      // S_ISLNK — symbolic link
      // S_ISSOCK — socket
   }else{
      rc = mkdir(dir_path,0700);
   }

   if(rc!=0) std::cout << "[NMRFileManager]: Cannot make the directory: " << path << std::endl;

   delete[] dir_path; 

   return rc;  

}
//______________________________________________________________________________
void NMRFileManager::InitInputDirectory(){
   const char *d1 = "./data/"; 
   strcpy(fDataDir,d1);
}
//______________________________________________________________________________
void NMRFileManager::InitOutputDirectory(){

   const int SIZE = 200; 
   const char *d1 = "./output"; 
   char *d2 = new char[SIZE]; 

   int RunNumber = InputManager->GetRunNumber(); 
   sprintf(d2,"%s/run-%05d",d1,RunNumber); 

   const char *D1 = d1; 
   const char *D2 = d2; 

   int rc=0;
   rc = MakeDirectory(D1); 
   if(rc!=0){
      std::cout << "[NMRFileManager]: Cannot make directory " << D1 << std::endl;
   }
   rc = MakeDirectory(D2); 
   if(rc!=0){
      std::cout << "[NMRFileManager]: Cannot make directory " << D2 << std::endl;
   }

   strcpy(fOutputBaseDir,D1); 
   strcpy(fOutputDir    ,D2);

   // delete the arrays
   delete[] d2; 

}
//______________________________________________________________________________
int NMRFileManager::PrintSignalToFile(int run,int pulseNumber,NMRPulse *aPulse){
  const int N = aPulse->GetNumPoints();
  char outpath[500],outStr[500];
  sprintf(outpath,"./csv/nmr-daq_run-%05d_trace-%02d.csv",run,pulseNumber);
  std::ofstream outfile(outpath);
  if( outfile.fail() ){
    std::cout << "[NMRFileManager::PrintSignalToFile]: Cannot open the file: " << outpath << std::endl;
    return 1;
  }else{
    for(int i=0;i<N;i++){
      sprintf(outStr,"%.3lf",aPulse->GetVoltage(i));
      outfile << outStr << std::endl;
    }
    outfile.close();
    std::cout << "[NMRFileManager::PrintSignalToFile]: The data has been written to the file: " << outpath << std::endl;
  }
  return 0;
}
//______________________________________________________________________________
void NMRFileManager::PrintResultsToFile(NMRRun *aRun){
   PrintRunToFile(aRun); 
   PrintRunToFileField(aRun); 
   PrintRunFreqStatsToFile(aRun); 
   PrintRunFieldStatsToFile(aRun); 
   PrintRunMetaStatsToFile(aRun); 
}

//______________________________________________________________________________
void NMRFileManager::PrintRunFreqStatsToFile(NMRRun *aRun){

   int run               = aRun->GetRunNumber();
   double mean_zc_mid    = aRun->GetFrequencyMeanZeroCrossingMidpoint();  
   double mean_zc_lin    = aRun->GetFrequencyMeanZeroCrossingLinearInterp();  
   double mean_zc_lsq    = aRun->GetFrequencyMeanZeroCrossingLeastSquares();  
   double sig_zc_mid     = aRun->GetFrequencySigmaZeroCrossingMidpoint();  
   double sig_zc_lin     = aRun->GetFrequencySigmaZeroCrossingLinearInterp();  
   double sig_zc_lsq     = aRun->GetFrequencySigmaZeroCrossingLeastSquares();  
   double mean_zc_mid_ph = aRun->GetFrequencyMeanZeroCrossingMidpointPhaseFit();  
   double mean_zc_lin_ph = aRun->GetFrequencyMeanZeroCrossingLinearInterpPhaseFit();  
   double mean_zc_lsq_ph = aRun->GetFrequencyMeanZeroCrossingLeastSquaresPhaseFit();  
   double sig_zc_mid_ph  = aRun->GetFrequencySigmaZeroCrossingMidpointPhaseFit();  
   double sig_zc_lin_ph  = aRun->GetFrequencySigmaZeroCrossingLinearInterpPhaseFit();  
   double sig_zc_lsq_ph  = aRun->GetFrequencySigmaZeroCrossingLeastSquaresPhaseFit();  
   // double mean_fit       = aRun->GetFrequencyMeanFit();  
   // double sig_fit        = aRun->GetFrequencySigmaFit();  
   // double mean_ph        = aRun->GetFrequencyMeanPhaseFit();  
   // double sig_ph         = aRun->GetFrequencySigmaPhaseFit();  

   const int SIZE = 200;
   char *outpath = new char[SIZE]; 
   sprintf(outpath,"%s/results_run-freq-stats.dat",fOutputDir);
   const char *header  = 
   "# Run \t Mean [Mid] (Hz) \t Sig [Mid] \t Mean [Lin] (Hz) \t Sig [Lin] (Hz) \t Mean [Lsq] (Hz) \t Sig [Lsq] (Hz) \t Mean [mid ph] \t Sig [mid ph] \t Mean [lin ph] \t Sig [lin ph] \t Mean [lsq ph] \t Sig [lsq ph]"; 

   const char *mode = "a";  // append data; create if it doesn't exist  

   FILE *outfile;
   outfile = fopen(outpath,mode); 

   if( outfile==NULL ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << outpath << std::endl;
      std::cout << "                  No data will be printed to file." << std::endl;
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Printing data to the file: " << outpath << std::endl;
      if(run==1) fprintf(outfile,"%s \n",header);
      fprintf(outfile,"%d \t %5.7lf \t %5.7lf \t %10.7lf \t %5.7lf \t %10.7lf \t %5.7lf \t %10.7lf \t %5.7lf \t %10.7lf \t %5.7lf \t %10.7lf \t %5.7lf \n",
              run,mean_zc_mid,sig_zc_mid,mean_zc_lin,sig_zc_lin,mean_zc_lsq,sig_zc_lsq,mean_zc_mid_ph,sig_zc_mid_ph,mean_zc_lin_ph,sig_zc_lin_ph,mean_zc_lsq_ph,sig_zc_lsq_ph);
      fclose(outfile);
   }

   delete[] outpath;

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFieldStatsToFile(NMRRun *aRun){

   int run               = aRun->GetRunNumber();
   double mean_zc_mid    = aRun->GetFieldMeanZeroCrossingMidpoint();  
   double mean_zc_lin    = aRun->GetFieldMeanZeroCrossingLinearInterp();  
   double mean_zc_lsq    = aRun->GetFieldMeanZeroCrossingLeastSquares();  
   double sig_zc_mid     = aRun->GetFieldSigmaZeroCrossingMidpoint();  
   double sig_zc_lin     = aRun->GetFieldSigmaZeroCrossingLinearInterp();  
   double sig_zc_lsq     = aRun->GetFieldSigmaZeroCrossingLeastSquares();  
   double mean_zc_mid_ph = aRun->GetFieldMeanZeroCrossingMidpointPhaseFit();  
   double mean_zc_lin_ph = aRun->GetFieldMeanZeroCrossingLinearInterpPhaseFit();  
   double mean_zc_lsq_ph = aRun->GetFieldMeanZeroCrossingLeastSquaresPhaseFit();  
   double sig_zc_mid_ph  = aRun->GetFieldSigmaZeroCrossingMidpointPhaseFit();  
   double sig_zc_lin_ph  = aRun->GetFieldSigmaZeroCrossingLinearInterpPhaseFit();  
   double sig_zc_lsq_ph  = aRun->GetFieldSigmaZeroCrossingLeastSquaresPhaseFit();  
   // double mean_fit       = aRun->GetFieldMeanFit();  
   // double sig_fit        = aRun->GetFieldSigmaFit();  
   // double mean_ph        = aRun->GetFieldMeanPhaseFit();  
   // double sig_ph         = aRun->GetFieldSigmaPhaseFit();  

   const int SIZE = 200;
   char *outpath = new char[SIZE]; 
   sprintf(outpath,"%s/results_run-field-stats.dat",fOutputDir);
   const char *header  = 
   "# Run \t Mean [Mid] (T) \t Sig [Mid] \t Mean [Lin] (T) \t Sig [Lin] (T) \t Mean [Lsq] (T) \t Sig [Lsq] (T) \t Mean [mid ph] \t Sig [mid ph] \t Mean [lin ph] \t Sig [lin ph] \t Mean [lsq ph] \t Sig [lsq ph]"; 

   const char *mode = "a";  // append data; create if it doesn't exist  

   FILE *outfile;
   outfile = fopen(outpath,mode); 

   if( outfile==NULL ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << outpath << std::endl;
      std::cout << "                  No data will be printed to file." << std::endl;
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Printing data to the file: " << outpath << std::endl;
      if(run==1) fprintf(outfile,"%s \n",header);
      fprintf(outfile,"%d \t %5.15lf \t %5.15lf \t %10.15lf \t %5.15lf \t %10.15lf \t %5.15lf \t %10.15lf \t %5.15lf \t %10.15lf \t %5.15lf \t %10.15lf \t %5.15lf  \n",
              run,mean_zc_mid,sig_zc_mid,mean_zc_lin,sig_zc_lin,mean_zc_lsq,sig_zc_lsq,mean_zc_mid_ph,sig_zc_mid_ph,mean_zc_lin_ph,sig_zc_lin_ph,mean_zc_lsq_ph,sig_zc_lsq_ph);
      fclose(outfile);
   }

   delete[] outpath;

}
//______________________________________________________________________________
void NMRFileManager::PrintRunMetaStatsToFile(NMRRun *aRun){

   int run           = aRun->GetRunNumber();
   double mean_ampl  = aRun->GetMeanAmplitude();
   double sig_ampl   = aRun->GetSigmaAmplitude();
   double mean_noise = aRun->GetMeanNoiseRMS();
   double sig_noise  = aRun->GetSigmaNoiseRMS();

   const int SIZE = 200;
   char *outpath = new char[SIZE]; 
   sprintf(outpath,"%s/results_run-meta-stats.dat",fOutputDir);
   const char *header  = "# Run \t Mean Ampl (V) \t Sig Ampl (V) \t Mean Noise RMS (V) \t Sig Noise RMS (V)"; 

   const char *mode = "a";  // append data; create if it doesn't exist  

   FILE *outfile;
   outfile = fopen(outpath,mode); 

   if( outfile==NULL ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << outpath << std::endl;
      std::cout << "                  No data will be printed to file." << std::endl;
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Printing data to the file: " << outpath << std::endl;
      if(run==1) fprintf(outfile,"%s \n",header);
      fprintf(outfile,"%d \t %5.7lf \t %5.7lf \t %5.7lf \t %5.7lf \n",run,mean_ampl,sig_ampl,mean_noise,sig_noise);
      fclose(outfile);
   }

   delete[] outpath;

}
//______________________________________________________________________________
void NMRFileManager::PrintRunToFile(NMRRun *aRun){
 
   int N   = aRun->GetNumPulses(); 
   int run = aRun->GetRunNumber();

   int pulse=0,zc=0;
   double ampl=0,rms_noise=0,nc=0,snr=0;
   double freq_mid=0,freq_lin=0,freq_lsq=0,freq_fit=0,freq_ph=0;
   double freq_mid_ph=0,freq_lin_ph=0,freq_lsq_ph=0; 

   // kill warnings
   snr+=0; 
   freq_fit+=0; 
   freq_ph+=0; 

   const int SIZE = 200;
   char *outpath = new char[SIZE]; 
   sprintf(outpath,"%s/results_pulse-stats.dat",fOutputDir);
     
   const char *header  = "# Run \t Pulse \t Max Ampl (V) \t RMS Noise (V) \t Zc \t Nc \t Freq [Mid] (Hz) \t Freq [Lin] (Hz) \t Freq [Lsq] (Hz) \t Freq [mid ph] (Hz) \t Freq [lin ph] (Hz) \t Freq [lsq ph] (Hz)"; 

   const char *mode = "a";  // append data; create if it doesn't exist  

   FILE *outfile;
   outfile = fopen(outpath,mode); 

   if( outfile==NULL ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << outpath << std::endl;
      std::cout << "                  No data will be printed to file." << std::endl;
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Printing data to the file: " << outpath << std::endl;
      if(run==1) fprintf(outfile,"%s \n",header); 
      for(int i=0;i<N;i++){
         pulse     = aRun->GetPulseNumber(i); 
         ampl      = aRun->GetPulseAmplitude(i); 
         rms_noise = aRun->GetPulseNoiseRMS(i); 
         snr       = aRun->GetPulseSignalToNoiseRatio(i);      // we won't print this because it makes the file difficult to read (and can calculate yourself anyway) 
         zc        = aRun->GetPulseNumZeroCrossings(i); 
         nc        = aRun->GetPulseNumCycles(i); 
         freq_mid  = aRun->GetPulseFrequencyZeroCrossingMidpoint(i); 
         freq_lin  = aRun->GetPulseFrequencyZeroCrossingLinearInterp(i); 
         freq_lsq  = aRun->GetPulseFrequencyZeroCrossingLeastSquares(i); 
         freq_mid_ph = aRun->GetPulseFrequencyZeroCrossingMidpointPhaseFit(i); 
         freq_lin_ph = aRun->GetPulseFrequencyZeroCrossingLinearInterpPhaseFit(i); 
         freq_lsq_ph = aRun->GetPulseFrequencyZeroCrossingLeastSquaresPhaseFit(i); 
         freq_fit  = aRun->GetPulseFrequencyFit(i); 
         freq_ph   = aRun->GetPulseFrequencyPhaseFit(i); 
         fprintf(outfile,"%d %5d %5.7lf %20.7lf %5d %5.3lf %20.7lf %20.7lf %20.7lf %20.7lf %20.7lf %20.7lf \n",
                 run,pulse,ampl,rms_noise,zc,nc,freq_mid,freq_lin,freq_lsq,freq_mid_ph,freq_lin_ph,freq_lsq_ph);
      }
      fclose(outfile);
   }

   delete[] outpath;

}
//______________________________________________________________________________
void NMRFileManager::PrintRunToFileField(NMRRun *aRun){
 
   int N   = aRun->GetNumPulses(); 
   int run = aRun->GetRunNumber();

   int pulse=0;
   double b_mid=0,b_lin=0,b_lsq=0,b_fit=0,b_ph=0; 
   double b_mid_ph=0,b_lin_ph=0,b_lsq_ph=0; 

   b_fit+=0;
   b_ph+=0; 

   const int SIZE = 200;
   char *outpath = new char[SIZE]; 
   sprintf(outpath,"%s/results_pulse-stats-field.dat",fOutputDir);
     
   const char *header  = "# Run \t Pulse \t B [Mid] (T) \t B [Lin] (T) \t B [Lsq] (T) \t B [fit] (T) \t B [ph] (T)"; 

   const char *mode = "a";  // append data; create if it doesn't exist  

   FILE *outfile;
   outfile = fopen(outpath,mode); 

   if( outfile==NULL ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << outpath << std::endl;
      std::cout << "                  No data will be printed to file." << std::endl;
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Printing data to the file: " << outpath << std::endl;
      if(run==1) fprintf(outfile,"%s \n",header); 
      for(int i=0;i<N;i++){
         pulse    = aRun->GetPulseNumber(i); 
         b_mid    = aRun->GetPulseFieldZeroCrossingMidpoint(i); 
         b_lin    = aRun->GetPulseFieldZeroCrossingLinearInterp(i); 
         b_lsq    = aRun->GetPulseFieldZeroCrossingLeastSquares(i); 
         b_mid_ph = aRun->GetPulseFieldZeroCrossingMidpointPhaseFit(i); 
         b_lin_ph = aRun->GetPulseFieldZeroCrossingLinearInterpPhaseFit(i); 
         b_lsq_ph = aRun->GetPulseFieldZeroCrossingLeastSquaresPhaseFit(i); 
         b_fit    = aRun->GetPulseFieldFit(i); 
         b_ph     = aRun->GetPulseFieldPhaseFit(i); 
         fprintf(outfile,"%d %5d %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf \n",
                 run,pulse,b_mid,b_lin,b_lsq,b_mid_ph,b_lin_ph,b_lsq_ph);
      }
      fclose(outfile);
   }

   delete[] outpath;

}
//______________________________________________________________________________
void NMRFileManager::PrintRunStatsToFile(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFreqToFileZC(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFreqToFileTimeFit(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFreqToFileHilbert(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFieldToFileZC(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFieldToFileTimeFit(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::PrintRunFieldToFileHilbert(NMRRun *aRun){

}
//______________________________________________________________________________
void NMRFileManager::AppendToFile(const char *path,const char *header,int i,double a,double b,double c,double d){

   const int SIZE = 200;
   char *outpath = new char[SIZE]; 
   sprintf(outpath,"%s/%s",fOutputDir,path);

   const char *mode = "a";  // append data; create if it doesn't exist  

   FILE *outfile;
   outfile = fopen(outpath,mode); 

   if( outfile==NULL ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << outpath << std::endl;
      std::cout << "                  No data will be printed to file." << std::endl;
   }else{
      if(i==1){
         if(fVerbosity>=1) std::cout << "[NMRFileManager]: Printing data to the file: " << outpath << std::endl;
         fprintf(outfile,"%s \n",header); 
      }
      fprintf(outfile,"%d \t %10.3lf \t %20.15E \t %20.15E \t %20.15lf \n",i,a,b,c,d);
      fclose(outfile);
   }

   delete[] outpath; 

}
//______________________________________________________________________________
void NMRFileManager::Load(int RunNumber,int PulseNumber,NMRPulse *aPulse){

   ImportDataRawADCBin(RunNumber,PulseNumber); 

   NMRDAQEvent_t myEvent; 
   int rc = ReadEventData(RunNumber,PulseNumber,myEvent); 
   std::string timeStamp = NMRUtility::GetStringTimeStampFromUTC( myEvent.timestamp/1E+9 ); 

   if(rc!=0){
     std::cout << "[NMRFileManager::Load]: Cannot read the DAQ event!" << std::endl;
     exit(1); 
   }else{
     std::cout << "[NMRFileManager::Load]: Processing event " << PulseNumber << " at " << timeStamp << std::endl; 
   }
 
   aPulse->SetTimeStamp(myEvent.timestamp);
   aPulse->SetTemperature(myEvent.temperature); 
   aPulse->SetXCoordinate(myEvent.x);   
   aPulse->SetYCoordinate(myEvent.y);   
   aPulse->SetZCoordinate(myEvent.z);   

   // convert to time (seconds) and voltage (V)
   int ADCID = InputManager->GetADCID();  
   const char *units = "s"; 
   Convert(ADCID,units);  

   double tmin=0; 
   double tmax = GetTMax(); 

   // set the start time: if we're using a start time that's non-zero, set tmin accordingly 
   if(fTStart!=0){
      if(fTStart>0){
         tmin = fTStart; 
      }else if(fTStart<0){
         if(fVerbosity>=2) std::cout << "Cannot have start time < 0!  Exiting..." << std::endl;
         exit(1);
      }
   }else{
      if(ADCID==3302) tmin  = 30E-6;  // trim off first 30 us of data (weird step function at the beginning); for the SIS3302 
      if(ADCID==3316) tmin  = 1E-6;   // trim off first 1 us of data (weird step function at the beginning) for the SIS3316 
   }
   tmax -= 0.5E-3; // trim off last 0.5 ms of data to avoid step from Radant Mems switch 
   // tmax -= 10E-3; // trim off last 10 ms of data to avoid step from Radant Mems switch 

   // set the data in aPulse 
   // find the total number of data points (to resize aPulse's arrays if necessary) 
   int j=0; 
   for(int i=0;i<fSIZE;i++){
      if( fTime[i]>tmin && fTime[i]<tmax){
         j++; 
      }
   }

   fNPTS = j; 

   int NN = aPulse->GetNumPoints(); 

   if(fVerbosity>=4) std::cout << "[NMRFileManager]: Setting " << fNPTS << " data points..." << std::endl;
   if(fNPTS!=NN) aPulse->SetNumPoints(fNPTS);    

   j = 0; 
   for(int i=0;i<fSIZE;i++){
      if( fTime[i]>tmin && fTime[i]<tmax){
         aPulse->SetDataPoint(j,fTime[i],fVoltage[i],0); 
         j++; 
      }
   }

   // apply the voltage offset correction 

   double tnoise = 1E-3; 
   double RMSNoise=0,VMax=-300; 

   // PrintSignalToFile(InputManager->GetRunNumber(),aPulse->GetPulseNumber(),aPulse);

   int OffsetOrder = InputManager->GetOffsetOrder(); 
   DoOffsetCorrectionAndRMSNoiseVMax(OffsetOrder,tnoise,aPulse,RMSNoise,VMax); 
   
   // PrintSignalToFile(InputManager->GetRunNumber(),aPulse->GetPulseNumber(),aPulse);

   // set RMSNoise as the error bar on the data 
   NN = aPulse->GetNumPoints();
   double t=0,v=0;
   for(int i=0;i<NN;i++){
      t = aPulse->GetTime(i);
      v = aPulse->GetVoltage(i); 
      aPulse->SetDataPoint(i,t,v,RMSNoise); 
   }

   aPulse->SetAmplitude(VMax); 
   aPulse->SetNoiseRMS(RMSNoise);  

   if(fVerbosity>=2){
      printf("--------------------------------------------- \n"    ); 
      printf("[NMRFileManager]: Data Summary                \n"    );  
      // printf("offset                            = %.7f \n",offset  );
      printf("max voltage                       = %.7f \n",VMax    ); 
      printf("RMS noise:                        = %.7f \n",RMSNoise);
      printf("--------------------------------------------- \n"    );
   }

   // set up for next pulse
   ClearDataArrays(); 

   if(fVerbosity>=2) std::cout << "[NMRFileManager]: Load complete. " << std::endl;

}
//______________________________________________________________________________
void NMRFileManager::Convert(int adcID,const char *Units){
   double SampleFreq = InputManager->GetSampleFrequency(); 
   for(int i=0;i<fSIZE;i++){
      fTime[i] = NMRMath::GetTimeInUnits(fSample[i],SampleFreq,Units);
      if(adcID==3302) fVoltage[i] = NMRMath::ConvertToVoltage3302(fADCCounts[i]);
      if(adcID==3316) fVoltage[i] = NMRMath::ConvertToVoltage3316(fADCCounts[i]);
   } 
}
//______________________________________________________________________________
int NMRFileManager::ReadEventData(int run,int pulse,NMRDAQEvent_t &myEvent){
   std::string sPulseNum,sChNum,sTime,sTemp,sx,sy,sz;
   int aPulse=0; 
   char inpath[30]; 
   sprintf(inpath,"./data/run-%05d/event-data.csv",run);

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      std::cout << "Cannot open the file: " << inpath << std::endl;
      return 1;
   }else{
      while( !infile.eof() ){
         std::getline(infile,sPulseNum,',');
         std::getline(infile,sChNum   ,',');
         std::getline(infile,sTime    ,',');
         std::getline(infile,sTemp    ,',');
         std::getline(infile,sx       ,',');
         std::getline(infile,sy       ,',');
         std::getline(infile,sz);
         aPulse = std::atoi( sPulseNum.c_str() ); 
         if(pulse==aPulse){ 
            myEvent.pulseNum    = aPulse;
            myEvent.chNum       = std::atoi( sChNum.c_str() );
            myEvent.timestamp   = std::stoull(sTime.c_str());
            myEvent.temperature = std::atof( sTemp.c_str() );
            myEvent.x           = std::atof( sx.c_str() );
            myEvent.y           = std::atof( sy.c_str() );
            myEvent.z           = std::atof( sz.c_str() );
         }
      }
   }
   return 0;
}
//______________________________________________________________________________
double NMRFileManager::GetPulseTimeStamp(int run,int pulse){

   // import the timestamp for the pulse 
   int ipulse=0;  
   double isec=0,ims=0,ius=0;
   double ts_us=0,ts=0; 
  
   const int SIZE = 200; 
   char *run_dir  = new char[SIZE];
   char *inpath   = new char[SIZE]; 

   sprintf(run_dir,"run-%05d"  ,run); 
   sprintf(inpath ,"%s/%s/timestamps.dat",fDataDir,run_dir);

   ifstream infile;
   infile.open(inpath,ios::in);

   if( infile.fail() ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << inpath << std::endl;
      exit(1);
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Opening the file: " << inpath << std::endl;
      while( !infile.eof() ){
         infile >> ipulse >> isec >> ims >> ius;
         if(pulse==ipulse) ts_us = ius;
      }
   }

   ts = ts_us*1E-6; // convert timestamp from us to s 

   delete[] run_dir; 
   delete[] inpath; 

   return ts; 

}
//______________________________________________________________________________
void NMRFileManager::ImportDataRawADCBin(int run,int pulse){

   // import the raw data, no conversions to seconds and volts 
   // file is in binary format
   // int it=0;  
   // unsigned short iv=0;

   streampos size; 
  
   // to remove warnings during compilation, we initialize memblock to some size  
   const int SIZE = 200; 
   char *memblock = new char[SIZE];
   char *run_dir  = new char[SIZE];
   char *pulse_fn = new char[SIZE];
   char *inpath   = new char[SIZE]; 

   sprintf(run_dir  ,"run-%05d"  ,run); 
   sprintf(pulse_fn ,"%d.bin"  ,pulse); 
   sprintf(inpath   ,"%s/%s/%s",fDataDir,run_dir,pulse_fn);

   ifstream infile;
   infile.open(inpath,ios::in | ios::binary | ios::ate);

   if( infile.fail() ){
      std::cout << "[NMRFileManager]: Cannot open the file: " << inpath << std::endl;
      exit(1);
   }else{
      if(fVerbosity>=1) std::cout << "[NMRFileManager]: Opening the file: " << inpath << std::endl;
   }

   if( infile.is_open() ){
      delete[] memblock;
      size = infile.tellg();
      memblock = new char[size]; 
      infile.seekg(0,ios::beg);
      infile.read(memblock,size);
      infile.close();
   }

   unsigned short *arr = new unsigned short[size];
   memcpy(arr,(unsigned short *)memblock,size); 

   double MB = 1.0E+6; 

   const int NPTS = (int)size/2; 
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: File size:          " << size/MB << " MB" << std::endl;
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Number of samples:  " << NPTS    << std::endl;
   for(int i=0;i<NPTS;i++){
      fSample[i]    = i; 
      fADCCounts[i] = arr[i]; 
   }
   
   delete[] memblock; 
   delete[] arr;            
   delete[] run_dir; 
   delete[] inpath; 
   delete[] pulse_fn;

}
//______________________________________________________________________________
void NMRFileManager::CalculateRMSNoiseVMax(double t_min,double t_max,double t_thr,double &rms_noise,double &vmax){

   // get starting time for noise.  Offset is determined from mean of noise.
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Computing max amplitude and RMS noise..." << std::endl;

   vector<double> Noise; 
 
   double tstart = t_max - t_thr; 
   double tend   = t_max; 

   for(int i=0;i<fSIZE;i++){
      // find vmax
      if( fTime[i]>t_min && fTime[i]<t_max){
         if( fVoltage[i] > vmax) vmax = fVoltage[i];  
      }
      // find RMS noise: look at very end of data set, defined by t_thr 
      if( (fTime[i] > tstart) && (fTime[i] < tend) ){
         Noise.push_back(fVoltage[i]); 
      } 
   }

   rms_noise = NMRMath::GetRMS(Noise);  

   Noise.clear(); 

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;
 
}
//______________________________________________________________________________
void NMRFileManager::CalculateRMSNoiseVMax(double t_thr,NMRPulse *aPulse,double &rms_noise,double &vmax){

   // get starting time for noise.  Offset is determined from mean of noise.
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Computing max amplitude and RMS noise..." << std::endl;

   vector<double> Noise; 

   const int N   = aPulse->GetNumPoints(); 
   double t_max  = aPulse->GetTime(N-1); 
   double tstart = t_max - t_thr; 
   // double tend   = t_max; 

   std::cout << "Noise start time: " << tstart << std::endl;

   double t=0,v=0;
   for(int i=0;i<N;i++){
      t = aPulse->GetTime(i);
      v = aPulse->GetVoltage(i);  
      if(t>tstart){
         Noise.push_back(v); 
      } 
      if(v>vmax) vmax = v;  
   }

   rms_noise = NMRMath::GetRMS(Noise); 
   Noise.clear();

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;
 
}
//______________________________________________________________________________
double NMRFileManager::GetRMSNoise(double t_thr,NMRPulse *aPulse){

   // get starting time for noise.  Offset is determined from mean of noise.
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Computing RMS noise..." << std::endl;

   vector<double> Noise; 

   const int N   = aPulse->GetNumPoints(); 
   double t_max  = aPulse->GetTime(N-1); 
   double tstart = t_max - t_thr; 
   // double tend   = t_max; 

   // std::cout << "Noise start time: " << tstart << std::endl;

   double t=0,v=0;
   for(int i=0;i<N;i++){
      t = aPulse->GetTime(i);
      v = aPulse->GetVoltage(i);  
      if(t>tstart){
         Noise.push_back(v); 
      } 
   }

   double rms_noise = NMRMath::GetRMS(Noise); 
   Noise.clear();

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;

   return rms_noise; 
 
}
//______________________________________________________________________________
double NMRFileManager::GetVMax(NMRPulse *aPulse){

   // get starting time for noise.  Offset is determined from mean of noise.
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Computing max amplitude..." << std::endl;

   const int N   = aPulse->GetNumPoints(); 
   double vmax   = -300; 

   double t=0,v=0;
   t+=0;
   v+=0;
   for(int i=0;i<N;i++){
      t = aPulse->GetTime(i);
      v = aPulse->GetVoltage(i);  
      if(v>vmax) vmax = v;  
   }

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;

   return vmax; 
}
//______________________________________________________________________________
void NMRFileManager::DoOffsetCorrectionAndRMSNoiseVMax(int order,double t_thr,NMRPulse *aPulse,double &RMSNoise,double &VMax){

   // test NMRPulse object 
   NMRPulse *myPulse  = new NMRPulse(); 

   if(fVerbosity>=2) std::cout << "[NMRFileManager]: Doing offset correction..." << std::endl;

   int N          = aPulse->GetNumPoints(); 
   // double t_start = aPulse->GetTime(0); 
   // double t_end   = aPulse->GetTime(N-1);

   double offset1=0;
   double offset2=0;
   double offset4=0;
    
   const int SIZE = 2;
   double *offset3 = new double[SIZE]; 
   double *offset5 = new double[SIZE]; 

   for(int i=0;i<SIZE;i++){
      offset3[i] = 0; 
      offset5[i] = 0; 
   }

   if(order<1) std::cout << "[NMRFileManager]: No offset correction applied." << std::endl;

   // order 1 is ALWAYS applied to "raw" data (aPulse) 
   if(order>=1){
      offset1 = GetOffset(t_thr,aPulse); 
      ApplyOffset(offset1,aPulse); 
      if(fVerbosity>=2) std::cout << "[NMRFileManager]: Offset1 = " << offset1 << std::endl;
   }

   // get RMS noise here. 
   RMSNoise = GetRMSNoise(t_thr,aPulse);  

   // set data in test pulse object: use chunk of data desired in ZC analysis 
   double TStartZC = InputManager->GetStartTimeZC(); 
   double TEndZC   = InputManager->GetEndTimeZC(); 
 
   int j=0;
   double time=0,voltage=0,vErr=0;
   for(int i=0;i<N;i++){
      time = aPulse->GetTime(i); 
      if( time>=TStartZC && time<=TEndZC){
         j++;
      }
   }

   int NN = j; 

   j = 0; 
   myPulse->SetNumPoints(NN); 
   for(int i=0;i<N;i++){
      time    = aPulse->GetTime(i); 
      voltage = aPulse->GetVoltage(i); 
      vErr    = aPulse->GetVoltageErr(i); 
      if( time>=TStartZC && time<=TEndZC){
         myPulse->SetDataPoint(j,time,voltage,vErr); 
         j++; 
      }
   }

   double ExpFreq = InputManager->GetExpectedFrequency(); 
   fNCycles = (int)( ExpFreq*(TEndZC - TStartZC)/10 ) ;

   if(order>=2){
      fOffsetFail = false;
      offset2 = GetOffsetZC(offset1,myPulse); 
      ApplyOffset(offset2,myPulse); 
      ApplyOffset(offset2,aPulse); 
      if(fVerbosity>=2) std::cout << "[NMRFileManager]: Offset2 = " << offset2 << std::endl;
   }

   if(order>=3){
      fOffsetFail = false;
      GetOffsetLinear(offset2,myPulse,offset3); 
      ApplyOffsetLinear(offset3,myPulse); 
      ApplyOffsetLinear(offset3,aPulse); 
      if(fVerbosity>=2) std::cout << "[NMRFileManager]: Offset3: constant = " << offset3[0] << " slope = " << offset3[1] << std::endl;
   }

   if(order>=4){
      fOffsetFail = false;
      offset4 = GetOffsetZC(offset3[0],myPulse); 
      ApplyOffset(offset4,myPulse); 
      ApplyOffset(offset4,aPulse); 
      if(fVerbosity>=2) std::cout << "[NMRFileManager]: Offset4 = " << offset4 << std::endl;
   }

   if(order>=5){
      fOffsetFail = false;
      GetOffsetLinear(offset4,myPulse,offset5); 
      ApplyOffsetLinear(offset5,myPulse); 
      ApplyOffsetLinear(offset5,aPulse); 
      if(fVerbosity>=2) std::cout << "[NMRFileManager]: Offset5: constant = " << offset5[0] << " slope = " << offset5[1] << std::endl;
   }

   VMax = GetVMax(aPulse); 
 
   if(fVerbosity>=2) std::cout << "[NMRFileManager]: Done." << std::endl;

   delete[] offset3; 
   delete[] offset5; 
   delete myPulse; 

}
//______________________________________________________________________________
void NMRFileManager::GetOffsetLinear(double input_offset,NMRPulse *aPulse,double *offset){

   // for each complete N cycles, compute the offset of the data by considering 
   // zero crossings  

   int counter=0;

   double t=0,v=0,ev=0;
   double v_mean=0,t_mean=0;

   vector<double> x,tOff,vOff;

   double ExpFreq    = InputManager->GetExpectedFrequency(); 
   double SampleFreq = InputManager->GetSampleFrequency(); 

   if(fVerbosity>=4){ 
      printf("Expected frequency: %.7f \n",ExpFreq   );
      printf("Sampling frequency: %.7f \n",SampleFreq);
   }

   double NumCycles = (double)fNCycles; 
   int NSamples      = (int)( (NumCycles/ExpFreq)*SampleFreq );  // length of time to average over 

   NMRPulse *myPulse = new NMRPulse(0,NSamples); 

   if(fVerbosity>=4) std::cout << "Averaging over " << NSamples << " samples..." << std::endl;

   // int dummy=0;
   // cin >> dummy;  

   const int N = aPulse->GetNumPoints();
   for(int i=0;i<N;i++){
      counter++;
      if(counter<=NSamples){
         t  = aPulse->GetTime(i); 
         v  = aPulse->GetVoltage(i);
         ev = aPulse->GetVoltageErr(i);  
         myPulse->SetDataPoint(counter-1,t,v,ev); 
      }else{
         // std::cout << "counter = " << counter << "\t" << "NSamples = " << NSamples << std::endl;
         // achieved the desired number of samples 
         for(int j=0;j<NSamples;j++) x.push_back( myPulse->GetTime(j) ); 
         t_mean = NMRMath::GetMean(x);
         v_mean = GetOffsetZC(input_offset,myPulse); 
         // std::cout << "t_mean = " << t_mean << "\t" << "v_mean = " << v_mean << std::endl;
         // cin >> dummy;
         tOff.push_back(t_mean);
         vOff.push_back(v_mean);
         // clean up 
         counter = 0;
         myPulse->ClearVectorData();
         x.clear();  
      }
   }

   delete myPulse; 

   // Do least squares fit to f(t) = a + bt  
   double a=0,b=0,r=0,rc=0;

   if(fOffsetFail){
      offset[0] = 0; 
      offset[1] = 0; 
   }else{
      rc = NMRMath::LeastSquaresFitting(tOff,vOff,a,b,r);
      if(rc!=0){
         std::cout << "[NMRFileManager::GetOffsetLinear]: Linear fit failed! Setting fit coefficients to zero..." << std::endl;
         offset[0] = 0; 
         offset[1] = 0; 
      }else{
         offset[0] = a; 
         offset[1] = b;
      }
   }

}
//______________________________________________________________________________
double NMRFileManager::GetOffsetZC(double input_offset,NMRPulse *aPulse){

   // find the offset using zero crossings to determine if time between crossings is constant,
   // as is expected for pure sine waves

   // NMRPulse *myPulse = aPulse->Clone();          // FIXME: this is where the memory leak is occuring! 
   NMRPulse *myPulse = new NMRPulse(aPulse);        // FIXME: this is where the memory leak is occuring! 
   // NMRPulse *myPulse = aPulse;                // object initialization; copy constructor called; doesn't really work...

   double ExpFreq    = InputManager->GetExpectedFrequency(); 
   double SampleFreq = InputManager->GetSampleFrequency(); 

   double T_exp  = 1./ExpFreq;
   double N_exp  = T_exp*SampleFreq;       // number of points for one period 
   int step      = (int)( (1./8.)*N_exp );  // skip 1/8 of a period 
   int NPTS      = step/2;                  // use step/2 

   if(fVerbosity>=3) std::cout << "[NMRFileManager::GetOffsetZC]: Finding additional offset..." << std::endl;

   if(fVerbosity>=3){
      std::cout << "[NMRFileManager::GetOffsetZC]: Parameters: " << std::endl;
      std::cout << "                               Points in fit: " << NPTS << std::endl;
      std::cout << "                               step size:     " << step << std::endl;
   }
 
   // settings for counting zero crossings
   bool UseT2Time = false;
   bool UseRange  = false; 
   double tMin    = 0;    // in seconds 
   double tMax    = 1;    // in seconds                         
   int type       = NMRMath::kLeastSquares; 

   vector<int> NCrossing,CrossingIndex;
   vector<double> tCross,vCross;
   vector<double> T,V,Slope;

   // int NN=0;
   // int is_nan=0; 
   int rc=0,counter=0; 

   int NNa = aPulse->GetNumPoints();
   int NNb = myPulse->GetNumPoints();
   if(NNb!=NNa){
      std::cout << "[NMRFileManager::GetOffsetZC]: NMRPulse objects don't match! " << std::endl;
      std::cout << "                               input pulse size: " << NNa << std::endl;
      std::cout << "                               test pulse size:  " << NNb << std::endl;
      exit(1); 
   } 

   double t_even=0,t_odd=0; 
   double err   = 1E-16; 

   double t_diff_abs=0,t_diff_abs_2=0;  
   t_diff_abs_2+=0; 

   // first calculation 
   int nzc = NMRMath::CountZeroCrossings(fVerbosity,type,NPTS,step,UseT2Time,UseRange,tMin,tMax,
                                         myPulse,fX,fY,fEY,fNCrossing,fCrossingIndex,fTcross,fVcross);
   double t_diff_old = GetTDiff(nzc,fTcross,t_even,t_odd); 
   ClearNZCArrays(); 
   // NCrossing.clear(); 
   // CrossingIndex.clear(); 
   // tCross.clear();
   // vCross.clear();

   if(fOffsetFail){
      delete myPulse;
      return 0; 
   }

   double offset_old  = input_offset; 
   double offset_new  = offset_old*(1. + 0.01);  // add 1%  

   if(offset_old==0) offset_new = 1E-6; 

   if(fVerbosity>=4){
      std::cout << "----------------------------------------------------------------" << std::endl;
      std::cout << "First calculation: " << std::endl;
      printf("offset_old = %.7E \n",offset_old);
      printf("t_diff_old = %.7E \n",t_diff_old);
      printf("offset_new = %.7E \n",offset_new);
      std::cout << "----------------------------------------------------------------" << std::endl;
   }

   ApplyOffset(offset_new,myPulse);
 
   nzc = NMRMath::CountZeroCrossings(fVerbosity,type,NPTS,step,UseT2Time,UseRange,tMin,tMax,
                                     myPulse,fX,fY,fEY,fNCrossing,fCrossingIndex,fTcross,fVcross);
   double t_diff_new = GetTDiff(nzc,fTcross,t_even,t_odd); 
   ClearNZCArrays();
   // NCrossing.clear(); 
   // CrossingIndex.clear(); 
   // tCross.clear();
   // vCross.clear();
  
   if(fOffsetFail){
      delete myPulse;
      return 0; 
   }

   // reset the pulse 
   // myPulse = aPulse->Clone();
   delete myPulse; 
   myPulse = new NMRPulse(aPulse);
 
   double slope = (t_diff_new - t_diff_old)/(offset_new - offset_old);

   rc = CheckOffset(offset_old,offset_new,t_diff_old,t_diff_new,slope); 
   if(rc>0){
      delete myPulse;
      return 0;
   }

   if(fVerbosity>=4){
      std::cout << "----------------------------------------------------------------" << std::endl;
      std::cout << "Second calculation: " << std::endl;
      printf("offset_old = %.7E \n",offset_old);
      printf("t_diff_old = %.7E \n",t_diff_old);
      printf("offset_new = %.7E \n",offset_new);
      printf("t_diff_new = %.7E \n",t_diff_new);
      printf("slope      = %.7E \n",slope)     ; 
      std::cout << "----------------------------------------------------------------" << std::endl;
   }

   offset_new = offset_old - t_diff_old/slope;
   double root_diff  = fabs(offset_new-offset_old);

   rc = CheckOffset(offset_old,offset_new,t_diff_old,t_diff_new,slope); 
   if(rc>0){
      delete myPulse;
      return 0;
   }
   
   if(t_diff_new==0) offset_new = offset_old;          // if new time difference is identically zero, we use old offset. 

   if(fVerbosity>4){
      std::cout << "trial     = 0"                   << std::endl; 
      printf("slope      = %.7E \n",slope); 
      printf("offset_old = %.7E   ",offset_old);
      printf("t_diff_old = %.7E \n",t_diff_old);
      printf("offset_new = %.7E \n",offset_new);
      printf("diff(offset-offset_prev) = %.7E \n",root_diff);
      std::cout << "----------------------------------------------------------------" << std::endl;
   }

   // we can't have a massive offset -- that's just not true. 
   if( fabs(offset_new)>0.005 ) offset_new = offset_old; 

   // update values 
   offset_old = offset_new; 
   t_diff_old = t_diff_new; 

   // clear arrays before starting
   ClearNZCArrays();

   do{ 
      offset_new = offset_old - t_diff_old/slope;
      // check the new offset  
      rc = CheckOffset(offset_old,offset_new,t_diff_old,t_diff_new,slope); 
      if(rc>0) break; 
      ApplyOffset(offset_new,myPulse); 
      nzc = NMRMath::CountZeroCrossings(fVerbosity,type,NPTS,step,UseT2Time,UseRange,tMin,tMax,
                                        myPulse,fX,fY,fEY,fNCrossing,fCrossingIndex,fTcross,fVcross);
      t_diff_new = GetTDiff(nzc,fTcross,t_even,t_odd); 
      slope      = (t_diff_new - t_diff_old)/(offset_new - offset_old);
      root_diff  = fabs(offset_new - offset_old); 
      if(fVerbosity>4){ 
         std::cout << "trial     = " << counter+1 << std::endl; 
         printf("slope      = %.7E \n",slope); 
         printf("offset_old = %.7E   ",offset_old); 
         printf("t_diff_old = %.7E \n",t_diff_old);
         printf("offset_new = %.7E   ",offset_new); 
         printf("t_diff_new = %.7E \n",t_diff_new); 
         printf("diff(offset-offset_prev) = %.7E \n",root_diff);
         std::cout << "----------------------------------------------------------------" << std::endl;
      }
      if(fOffsetFail) break;
      // set up for next calc 
      // myPulse = aPulse->Clone();       // reset the pulse   
      delete myPulse; 
      myPulse = new NMRPulse(aPulse);
      t_diff_abs   = fabs(t_diff_new); 
      t_diff_abs_2 = fabs(t_diff_new-t_diff_old); 
      t_diff_old   = t_diff_new;
      offset_old   = offset_new;
      ClearNZCArrays();
      counter++; 
      // fill vectors 
      // V.push_back(offset_new); 
      // T.push_back(t_diff_new);
      // Slope.push_back(slope);   
      // clear vectors  
      // NCrossing.clear(); 
      // CrossingIndex.clear(); 
      // tCross.clear();
      // vCross.clear();
   }while( (t_diff_abs>err)&&(counter<20) ); 

   if(counter==20){
      if(fVerbosity>=3){
         std::cout << "Reached max counter (20).  Giving up." << std::endl;
         printf("offset_old: %.7E \n",offset_old);
         printf("offset_new: %.7E \n",offset_new);
         printf("t_diff_old: %.7E \n",t_diff_old);
         printf("t_diff_new: %.7E \n",t_diff_new);
         printf("slope:      %.7E \n",slope     );
      }
   }

   if(fVerbosity>=3) std::cout << "[NMRFileManager::GetOffsetZC]: Done." << std::endl;

   delete myPulse; 
   ClearNZCArrays();

   if(rc>0 || fOffsetFail==true){
      return 0;
   }else{
      return offset_new;
   } 

}
//______________________________________________________________________________
double NMRFileManager::GetOffset(double t_min,double t_max,double t_thr){

   // get starting time for noise.  Offset is determined from mean of noise.

   vector<double> Noise; 
 
   double tstart = t_max - t_thr; 
   double tend   = t_max; 

   // std::cout << "tmax   = " << t_max  << std::endl; 
   // std::cout << "tstart = " << tstart << std::endl;
   // std::cout << "tend   = " << tend   << std::endl;

   for(int i=0;i<fSIZE;i++){
      if( (fTime[i] > tstart) && (fTime[i] < tend) ){
         Noise.push_back(fVoltage[i]); 
      } 
   }

   // double rms    = NMRMath::GetRMS(Noise); 
   double mean   = NMRMath::GetMean(Noise); 
   double offset = mean; 
   Noise.clear();

   return offset;  
 
}
//______________________________________________________________________________
double NMRFileManager::GetOffset(double t_thr,NMRPulse *aPulse){

   vector<double> Noise; 

   const int N   = aPulse->GetNumPoints(); 
   double t_max  = aPulse->GetTime(N-1); 
   double tstart = t_max - t_thr; 
   double tend   = t_max; 

   // std::cout << "tmax   = " << t_max  << std::endl; 
   // std::cout << "tstart = " << tstart << std::endl;
   // std::cout << "tend   = " << tend   << std::endl;

   double t=0,v=0;
   for(int i=0;i<N;i++){
      t = aPulse->GetTime(i);
      v = aPulse->GetVoltage(i);  
      if( (t>tstart)&&(t<tend) ){
         Noise.push_back(v); 
      } 
   }

   // double rms    = NMRMath::GetRMS(Noise); 
   double mean   = NMRMath::GetMean(Noise); 
   double offset = mean; 
   Noise.clear();

   return offset;  

}
//______________________________________________________________________________
void NMRFileManager::ApplyOffset(double offset){
   // apply an offset to the data based on the mean voltage
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Applying offset of " << offset << " V to raw data..." << std::endl;

   double arg=0; 

   for(int i=0;i<fSIZE;i++){
      arg = fVoltage[i] - offset; 
      fVoltage[i] = arg; 
   }

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;

}
//______________________________________________________________________________
void NMRFileManager::ApplyOffset(double offset,NMRPulse *aPulse){
   // apply an offset to the data based on the mean voltage
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Applying offset of " << offset << " V to data..." << std::endl;

   double t=0,v=0,ev=0; 

   int N = aPulse->GetNumPoints(); 
   for(int i=0;i<N;i++){
      t  = aPulse->GetTime(i);  
      v  = aPulse->GetVoltage(i) - offset;
      ev = aPulse->GetVoltageErr(i);  
      aPulse->SetDataPoint(i,t,v,ev); 
   }

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;

}
//______________________________________________________________________________
void NMRFileManager::ApplyOffsetLinear(double *par,NMRPulse *aPulse){
   // apply an offset to the data based on the mean voltage
   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Applying offset to data..." << std::endl;

   double offset=0,t=0,v=0,ev=0; 

   int N = aPulse->GetNumPoints(); 
   for(int i=0;i<N;i++){
      t      = aPulse->GetTime(i);  
      offset = par[0] + par[1]*t; 
      v      = aPulse->GetVoltage(i) - offset;
      ev     = aPulse->GetVoltageErr(i);  
      aPulse->SetDataPoint(i,t,v,ev); 
   }

   if(fVerbosity>=3) std::cout << "[NMRFileManager]: Done." << std::endl;

}
//______________________________________________________________________________
int NMRFileManager::CheckOffset(double offset_old,double offset_new,double t_diff_old,double t_diff_new,double slope){

   int is_nan_t_diff_old = std::isnan(t_diff_old);
   int is_nan_t_diff_new = std::isnan(t_diff_new);
   int is_nan_offset_old = std::isnan(offset_old);
   int is_nan_offset_new = std::isnan(offset_new);
   int is_nan_slope      = std::isnan(slope); 

   int rc = 0,rc_tot=0;
   rc+=0;
 
   if(is_nan_t_diff_old){
      rc = 1; 
      rc_tot++;
   }
   if(is_nan_t_diff_new){
      rc = 2; 
      rc_tot++;
   }
   if(is_nan_offset_old){ 
      rc = 3;
      rc_tot++; 
   } 
   if(is_nan_offset_new){
      rc = 4; 
      rc_tot++;
   } 
   if(is_nan_slope){
      rc = 5; 
      rc_tot++;
   }

   // int dummy=0; 
   if(rc_tot>0){
      printf("[NMRFileManager]: WARNING: One of the offset values below is NAN! \n");
      printf("                  offset_old: %.7E \n",offset_old);
      printf("                  offset_new: %.7E \n",offset_new);
      printf("                  t_diff_old: %.7E \n",t_diff_old);
      printf("                  t_diff_new: %.7E \n",t_diff_new);
      printf("                  slope:      %.7E \n",slope     );
      // printf("Enter any number to continue: ");
      // cin  >> dummy; 
   }

   return rc_tot;  

}
//______________________________________________________________________________
double NMRFileManager::GetTDiff(vector<double> tCross,double &delta_t_even_nc,double &delta_t_odd_nc){
   delta_t_odd_nc=0;
   delta_t_even_nc=0;
   int counter_odd=0,counter_even=0;
   int NN = tCross.size();
   // int dummy=0;
   if(NN<2){
      if(fVerbosity>=4) std::cout << "[NMRFileManager::GetTDiff]: NOT ENOUGH DATA POINTS!" << std::endl;
      if(fVerbosity>=4) std::cout << "[NMRFileManager::GetTDiff]: Number of data points: " << NN << std::endl;
      // cin >> dummy;
      // delta_t_odd_nc = 1E-17; // arbitrary value... 
      fOffsetFail = true;  
      return -1; 
   }else{
      for(int i=1;i<NN;i++){
         if(i%2==0){
            delta_t_odd_nc  += (tCross[i]-tCross[i-1]);   // we're going by even/odd Zc -- not Nc, so we interchange odd/even wrt Nc. 
            counter_odd++;
         }else if(i%2!=0){
            delta_t_even_nc += (tCross[i]-tCross[i-1]);
            counter_even++;
         }
         // std::cout << delta_t_odd_nc << "\t" << delta_t_even_nc << std::endl;
      }
      delta_t_odd_nc  /= ( (double)counter_odd );
      delta_t_even_nc /= ( (double)counter_even);
   }
   // std::cout << "dt_odd  = " << delta_t_odd_nc  << std::endl;
   // std::cout << "dt_even = " << delta_t_even_nc << std::endl;
   double t_diff = delta_t_odd_nc-delta_t_even_nc;
   return t_diff;
}
//______________________________________________________________________________
double NMRFileManager::GetTDiff(int nzc,double *tCross,double &delta_t_even_nc,double &delta_t_odd_nc){
   delta_t_odd_nc=0;
   delta_t_even_nc=0;
   int counter_odd=0,counter_even=0;
   if(nzc<2){
      if(fVerbosity>=4) std::cout << "[NMRFileManager::GetTDiff]: NOT ENOUGH DATA POINTS!" << std::endl;
      if(fVerbosity>=4) std::cout << "[NMRFileManager::GetTDiff]: Number of data points: " << nzc << std::endl;
      fOffsetFail = true;  
      return -1; 
   }else{
      for(int i=1;i<nzc;i++){
         if(i%2==0){
            delta_t_odd_nc  += (tCross[i]-tCross[i-1]);   // we're going by even/odd Zc -- not Nc, so we interchange odd/even wrt Nc. 
            counter_odd++;
         }else if(i%2!=0){
            delta_t_even_nc += (tCross[i]-tCross[i-1]);
            counter_even++;
         }
      }
      delta_t_odd_nc  /= ( (double)counter_odd );
      delta_t_even_nc /= ( (double)counter_even);
   }
   double t_diff = delta_t_odd_nc-delta_t_even_nc;
   return t_diff;
}
//______________________________________________________________________________
double NMRFileManager::GetTMax(){
   double TMax = -300;
   for(int i=0;i<fSIZE;i++){
      if(fTime[i]>TMax) TMax = fTime[i];
   }
   return TMax; 
}
