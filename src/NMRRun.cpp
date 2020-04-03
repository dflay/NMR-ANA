#include "NMRRun.h"
//______________________________________________________________________________
NMRRun::NMRRun(int NumPulses){
   fPulseIndex           = 0;           // which pulse are we looking at?   
   fNumPulses            = NumPulses;   // initialize a run for an arbitrary number of pulses 
   fFreqMeanFit          = 0;  
   fFreqMeanPhaseFit     = 0;  
   fFreqSigFit           = 0;  
   fFreqSigPhaseFit      = 0;  
   fBMeanFit             = 0;  
   fBMeanPhaseFit        = 0;  
   fBSigFit              = 0;  
   fBSigPhaseFit         = 0;  
   fRunNumber            = 0;     
   fMeanNumZeroCrossings = 0;                       
   fMeanNoiseRMS         = 0;              
   fMeanAmpl             = 0;               
   fMeanSNR              = 0;            
   fMeanNumCycles        = 0;       
   fSigNoiseRMS          = 0;              
   fSigAmpl              = 0;               
   fSigSNR               = 0;            
   fSigNumCycles         = 0;     
   fMeanT2               = 0; 
   fSigT2                = 0; 
   fVerbosity            = 0; 
   const int N           = fNumPulses; 
   fPulse                = new NMRPulseAnalyzed*[N];
   // for(int i=0;i<N;i++){
   //    fPulse[i] = new NMRPulseAnalyzed(i+1,1); 
   // }
   const int N3   = 3;
   fFreqMeanZC    = new double[N3];  
   fFreqSigZC     = new double[N3]; 
   fFreqMeanZC_ph = new double[N3];  
   fFreqSigZC_ph  = new double[N3]; 
   fBMeanZC       = new double[N3];  
   fBSigZC        = new double[N3]; 
   fBMeanZC_ph    = new double[N3];  
   fBSigZC_ph     = new double[N3]; 
   for(int i=0;i<N3;i++){
      fFreqMeanZC[i]    = 0;
      fFreqSigZC[i]     = 0;
      fBMeanZC[i]       = 0;
      fBSigZC[i]        = 0;
      fFreqMeanZC_ph[i] = 0;
      fFreqSigZC_ph[i]  = 0;
      fBMeanZC_ph[i]    = 0;
      fBSigZC_ph[i]     = 0;
   } 
}
//______________________________________________________________________________
NMRRun::~NMRRun(){
   // for(int i=0;i<fNumPulses;i++){
   //    delete fPulse[i];
   // } 
   delete[] fPulse;
   delete[] fFreqMeanZC;  
   delete[] fFreqSigZC;  
   delete[] fBMeanZC;  
   delete[] fBSigZC; 
   delete[] fFreqMeanZC_ph;  
   delete[] fFreqSigZC_ph;  
   delete[] fBMeanZC_ph;  
   delete[] fBSigZC_ph;   
}
//______________________________________________________________________________
void NMRRun::AddNMRPulse(NMRPulseAnalyzed *aPulse){
   // get the updated index (for checks) 
   int next_index = fPulseIndex + 1; 
   // check how many pulses we have
   if(next_index<=fNumPulses){
      fPulse[fPulseIndex] = new NMRPulseAnalyzed(aPulse);     
      fPulseIndex++; 
      if(fVerbosity>=3){
         std::cout << "[NMRRun::AddPulse]: Added a pulse to the run." << std::endl;
         std::cout << "[NMRRun::AddPulse]: Pulse count: " << fPulseIndex << std::endl; 
      }
   }else{
      std::cout << "[NMRRun::AddNMRPulse]: Cannot add the pulse!  Is the number of pulses set properly?" << std::endl;
      std::cout << "                       NumPulses = " << fNumPulses << std::endl; 
      std::cout << "                       new index = " << next_index << std::endl; 
   }
}
//______________________________________________________________________________
void NMRRun::SetNumPulses(int NumPulses){
   // set a new number of pulses
   // first delete the old array
   if(fVerbosity>=4) std::cout << "[NMRRun::SetNumPulses]: Deleting " << fNumPulses << " pulses." << std::endl; 
   for(int i=0;i<fNumPulses;i++){
      if(fPulse[i]!=NULL) delete fPulse[i];
   } 
   delete[] fPulse; 
   // now create a new array of pulses
   fNumPulses = NumPulses; 
   if(fVerbosity>=4) std::cout << "[NMRRun::SetNumPulses]: Creating " << fNumPulses << " pulses." << std::endl; 
   const int N = fNumPulses; 
   fPulse = new NMRPulseAnalyzed*[N];
   // for(int i=0;i<N;i++){
   //    fPulse[i] = new NMRPulseAnalyzed(); 
   // } 
}
//______________________________________________________________________________
void NMRRun::PrintPulseData(int index) const{
   // print all pulses (index<0) or a single pulse
   if(index<0){
      for(int i=0;i<fNumPulses;i++) fPulse[i]->Print();
   }else{
      fPulse[index]->Print();
   }
}
//______________________________________________________________________________
void NMRRun::PrintStatistics() const{
   printf("========================= Run Statistics ========================== \n");
   printf("Run number:          %d    \n",fRunNumber);
   printf("Number of pulses:    %d    \n",fNumPulses); 
   printf("Peak Ampl [mV]:                 mean = %9.3lf std. dev. = %.3lf \n",fMeanAmpl/1E-3,fSigAmpl/1E-3);
   printf("Noise RMS [mV]:                 mean = %9.3lf std. dev. = %.3lf \n",fMeanNoiseRMS/1E-3,fSigNoiseRMS/1E-3);
   printf("SNR:                            mean = %9.3lf std. dev. = %.3lf \n",fMeanSNR,fSigSNR);
   printf("T2 [ms]:                        mean = %9.3lf std. dev. = %.3lf \n",fMeanT2/1E-3,fSigT2/1E-3);
   printf("Freq [Hz] (ZC, midpoint):       mean = %9.3lf std. dev. = %.3lf \n",fFreqMeanZC[0],fFreqSigZC[0]);
   printf("Freq [Hz] (ZC, linear):         mean = %9.3lf std. dev. = %.3lf \n",fFreqMeanZC[1],fFreqSigZC[1]);
   printf("Freq [Hz] (ZC, least sq):       mean = %9.3lf std. dev. = %.3lf \n",fFreqMeanZC[2],fFreqSigZC[2]);
   printf("Freq [Hz] (ZC, midpoint phase): mean = %9.3lf std. dev. = %.3lf \n",fFreqMeanZC_ph[0],fFreqSigZC_ph[0]);
   printf("Freq [Hz] (ZC, linear phase):   mean = %9.3lf std. dev. = %.3lf \n",fFreqMeanZC_ph[1],fFreqSigZC_ph[1]);
   printf("Freq [Hz] (ZC, least sq phase): mean = %9.3lf std. dev. = %.3lf \n",fFreqMeanZC_ph[2],fFreqSigZC_ph[2]);
}
//______________________________________________________________________________
void NMRRun::ClearData(){
   fPulseIndex           = 0;           // which pulse are we looking at?   
   fFreqMeanFit          = 0;  
   fFreqMeanPhaseFit     = 0;  
   fFreqSigFit           = 0;  
   fFreqSigPhaseFit      = 0;  
   fBMeanFit             = 0;  
   fBMeanPhaseFit        = 0;  
   fBSigFit              = 0;  
   fBSigPhaseFit         = 0;  
   fRunNumber            = 0;     
   fMeanNumZeroCrossings = 0;                       
   fMeanNoiseRMS         = 0;              
   fMeanAmpl             = 0;               
   fMeanSNR              = 0;            
   fMeanNumCycles        = 0;      
   fMeanT2               = 0;
   fSigT2                = 0;
   fSigNoiseRMS          = 0;              
   fSigAmpl              = 0;               
   fSigSNR               = 0;            
   fSigNumCycles         = 0;      
   for(int i=0;i<fNumPulses;i++){
      delete fPulse[i];
      fPulse[i] = NULL;   // this might help.
   } 
   for(int i=0;i<3;i++){
      fFreqMeanZC[i]    = 0;
      fFreqSigZC[i]     = 0;
      fBMeanZC[i]       = 0;
      fBSigZC[i]        = 0;
      fFreqMeanZC_ph[i] = 0;
      fFreqSigZC_ph[i]  = 0;
      fBMeanZC_ph[i]    = 0;
      fBSigZC_ph[i]     = 0;
   } 
}

