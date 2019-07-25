#include "NMRInputManager.h"
//______________________________________________________________________________
NMRInputManager::NMRInputManager(){
   fUseZeroCrossing  = false;
   fUseTimeFit       = false;
   fUsePhaseFit      = false;
   fUseIntegerCycles = false; 
   fADCID            = 0;
   fADCChannelNumber = 0;
   fMonth            = 0;
   fDay              = 0;
   fYear             = 0;
   fVerbosity        = 0;
   fOffsetOrder      = 0; 
   fRunNumber        = 0;
   fNumPulses        = 0;
   fStartTimeZC      = 0;
   fEndTimeZC        = 0;
   fT2Time           = 0; 
   fExpFreq          = 0;
   fSampleFreq       = 0;
   fLOFreq           = 0; 
   fPi2Freq          = 0;
   fADCNumSamples    = 0;
   fADCSignalLength  = 0;
   fBNCVoltage       = 0;
   fNTypeVoltage     = 0;
   fNumRuns          = 0;
   fPhaseFitFunc     = 0; 
   const int N       = 5E+3; 
   fRunList          = new int[N]; 
   for(int i=0;i<N;i++) fRunList[i] = 0; 
}
//______________________________________________________________________________
NMRInputManager::~NMRInputManager(){
   delete[] fRunList; 
}
//______________________________________________________________________________
NMRInputManager::NMRInputManager(const NMRInputManager &a){
   // copy constructor 
   // shallow copy (don't need deep copy, no pointers in class) 
   fPhaseFitFunc     = a.GetPhaseFitFunction(); 
   fUseZeroCrossing  = a.GetZeroCrossingStatus(); 
   fUseTimeFit       = a.GetTimeFitStatus(); 
   fUsePhaseFit      = a.GetPhaseFitStatus(); 
   fUseIntegerCycles = a.GetIntegerCycleStatus(); 
   fUseT2Time        = a.GetT2TimeStatus(); 
   fADCID            = a.GetADCID(); 
   fADCChannelNumber = a.GetADCChannelNumber(); 
   fMonth            = a.GetMonth(); 
   fDay              = a.GetDay(); 
   fYear             = a.GetYear(); 
   fVerbosity        = a.GetVerbosity(); 
   fOffsetOrder      = a.GetOffsetOrder(); 
   fRunNumber        = a.GetRunNumber(); 
   fNumPulses        = a.GetNumPulses(); 
   fStartTimeZC      = a.GetStartTimeZC(); 
   fEndTimeZC        = a.GetEndTimeZC(); 
   fT2Time           = a.GetT2Time(); 
   fExpFreq          = a.GetExpectedFrequency(); 
   fSampleFreq       = a.GetSampleFrequency(); 
   fLOFreq           = a.GetLOFrequency();
   fPi2Freq          = a.GetPi2Frequency();
   fADCNumSamples    = a.GetNumSamples(); 
   fADCSignalLength  = a.GetSignalLength();
   fBNCVoltage       = a.GetBNCVoltage();     
   fNTypeVoltage     = a.GetNTypeVoltage();     
}
//______________________________________________________________________________
NMRInputManager::NMRInputManager(const NMRInputManager *a){
   // copy constructor 
   // shallow copy (don't need deep copy, no pointers in class) 
   fPhaseFitFunc     = a->GetPhaseFitFunction(); 
   fUseZeroCrossing  = a->GetZeroCrossingStatus(); 
   fUseTimeFit       = a->GetTimeFitStatus(); 
   fUsePhaseFit      = a->GetPhaseFitStatus(); 
   fUseIntegerCycles = a->GetIntegerCycleStatus(); 
   fUseT2Time        = a->GetT2TimeStatus(); 
   fADCID            = a->GetADCID(); 
   fADCChannelNumber = a->GetADCChannelNumber(); 
   fMonth            = a->GetMonth(); 
   fDay              = a->GetDay(); 
   fYear             = a->GetYear(); 
   fVerbosity        = a->GetVerbosity(); 
   fOffsetOrder      = a->GetOffsetOrder(); 
   fRunNumber        = a->GetRunNumber(); 
   fNumPulses        = a->GetNumPulses(); 
   fStartTimeZC      = a->GetStartTimeZC(); 
   fEndTimeZC        = a->GetEndTimeZC(); 
   fT2Time           = a->GetT2Time(); 
   fExpFreq          = a->GetExpectedFrequency(); 
   fSampleFreq       = a->GetSampleFrequency(); 
   fLOFreq           = a->GetLOFrequency();
   fPi2Freq          = a->GetPi2Frequency();
   fADCNumSamples    = a->GetNumSamples(); 
   fADCSignalLength  = a->GetSignalLength();
   fBNCVoltage       = a->GetBNCVoltage();     
   fNTypeVoltage     = a->GetNTypeVoltage();     
}
//______________________________________________________________________________
void NMRInputManager::Update(const NMRInputManager &a){
   // shallow copy (don't need deep copy, no pointers in class), the "hard" way  
   fPhaseFitFunc     = a.GetPhaseFitFunction(); 
   fUseZeroCrossing  = a.GetZeroCrossingStatus(); 
   fUseTimeFit       = a.GetTimeFitStatus(); 
   fUsePhaseFit      = a.GetPhaseFitStatus(); 
   fUseIntegerCycles = a.GetIntegerCycleStatus(); 
   fUseT2Time        = a.GetT2TimeStatus(); 
   fADCID            = a.GetADCID(); 
   fADCChannelNumber = a.GetADCChannelNumber(); 
   fMonth            = a.GetMonth(); 
   fDay              = a.GetDay(); 
   fYear             = a.GetYear(); 
   fVerbosity        = a.GetVerbosity(); 
   fOffsetOrder      = a.GetOffsetOrder(); 
   fRunNumber        = a.GetRunNumber(); 
   fNumPulses        = a.GetNumPulses(); 
   fStartTimeZC      = a.GetStartTimeZC(); 
   fEndTimeZC        = a.GetEndTimeZC(); 
   fT2Time           = a.GetT2Time(); 
   fExpFreq          = a.GetExpectedFrequency(); 
   fSampleFreq       = a.GetSampleFrequency(); 
   fLOFreq           = a.GetLOFrequency();
   fPi2Freq          = a.GetPi2Frequency();
   fADCNumSamples    = a.GetNumSamples(); 
   fADCSignalLength  = a.GetSignalLength();
   fBNCVoltage       = a.GetBNCVoltage();     
   fNTypeVoltage     = a.GetNTypeVoltage();     
}
//______________________________________________________________________________
void NMRInputManager::Update(const NMRInputManager *a){
   // shallow copy (don't need deep copy, no pointers in class), the "hard" way  
   fPhaseFitFunc     = a->GetPhaseFitFunction(); 
   fUseZeroCrossing  = a->GetZeroCrossingStatus(); 
   fUseTimeFit       = a->GetTimeFitStatus(); 
   fUsePhaseFit      = a->GetPhaseFitStatus(); 
   fUseIntegerCycles = a->GetIntegerCycleStatus(); 
   fUseT2Time        = a->GetT2TimeStatus(); 
   fADCID            = a->GetADCID(); 
   fADCChannelNumber = a->GetADCChannelNumber(); 
   fMonth            = a->GetMonth(); 
   fDay              = a->GetDay(); 
   fYear             = a->GetYear(); 
   fVerbosity        = a->GetVerbosity(); 
   fOffsetOrder      = a->GetOffsetOrder(); 
   fRunNumber        = a->GetRunNumber(); 
   fNumPulses        = a->GetNumPulses(); 
   fStartTimeZC      = a->GetStartTimeZC(); 
   fEndTimeZC        = a->GetEndTimeZC(); 
   fT2Time           = a->GetT2Time(); 
   fExpFreq          = a->GetExpectedFrequency(); 
   fSampleFreq       = a->GetSampleFrequency(); 
   fLOFreq           = a->GetLOFrequency();
   fPi2Freq          = a->GetPi2Frequency();
   fADCNumSamples    = a->GetNumSamples(); 
   fADCSignalLength  = a->GetSignalLength();
   fBNCVoltage       = a->GetBNCVoltage();     
   fNTypeVoltage     = a->GetNTypeVoltage();     
}
//______________________________________________________________________________
void NMRInputManager::GetInputParameters(const char *inpath){

   const int MAX = 2000; 
   char itag[MAX],buf[MAX]; 
 
   int k=0,ival=0; 
   double ivalue=0; 

   const char *day                  = "day"; 
   const char *month                = "month"; 
   const char *year                 = "year"; 
   const char *tstart               = "t_start"; 
   const char *tend                 = "t_end"; 
   const char *verb                 = "verbosity"; 
   const char *offset               = "offset_correction_order";
   const char *zc_status            = "zero_crossing"; 
   const char *time_fit_status      = "time_fit"; 
   const char *phase_fit_status     = "phase_fit"; 
   const char *phase_fit_func       = "phase_fit_func"; 
   const char *integer_cycle_status = "integer_cycles"; 
   const char *t2_time_status       = "t2_time"; 
   const char *eof                  = "end_of_file";  
 
   std::ifstream infile;
   infile.open(inpath,std::ios::in);

   if( infile.fail() ){
      printf("[NMRFileManager::GetInputParameters]: Cannot open the file: %s.  Exiting... \n",inpath);
      exit(1);
   }else{
      while( !infile.eof() ){
         if(k==0){
            infile.getline(buf,MAX);
         }else{
            infile >> itag >> ivalue; 
            // printf("%s %15.2lf \n",itag,ivalue);
            if( !NMRUtility::AreEquivStrings(itag,eof) ){
               if( NMRUtility::AreEquivStrings(itag,month)       ) fMonth        = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,day)         ) fDay          = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,year)        ) fYear         = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,tstart)      ) fStartTimeZC  = ivalue;  
               if( NMRUtility::AreEquivStrings(itag,tend)        ) fEndTimeZC    = ivalue;  
               if( NMRUtility::AreEquivStrings(itag,verb)        ) fVerbosity    = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,offset)      ) fOffsetOrder  = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,zc_status)   ){
                  ival = (int)ivalue;
                  if(ival==1) fUseZeroCrossing = true;  
               } 
               if( NMRUtility::AreEquivStrings(itag,time_fit_status)   ){
                  ival = (int)ivalue;
                  if(ival==1) fUseTimeFit = true;  
               } 
               if( NMRUtility::AreEquivStrings(itag,phase_fit_status)   ){
                  ival = (int)ivalue;
                  if(ival==1) fUsePhaseFit = true;  
               } 
               if( NMRUtility::AreEquivStrings(itag,integer_cycle_status)   ){
                  ival = (int)ivalue;
                  if(ival==1) fUseIntegerCycles = true;  
               } 
               if( NMRUtility::AreEquivStrings(itag,t2_time_status)   ){
                  ival = (int)ivalue;
                  if(ival==1) fUseT2Time = true;  
               }
	       if( NMRUtility::AreEquivStrings(itag,phase_fit_func) ){
		 fPhaseFitFunc = (int)ivalue;
	       }
            }else{
               break;
            }
         }
         k++;
      }
      infile.close(); 
   }

   if(fPhaseFitFunc!=1 && fPhaseFitFunc!=3 && fPhaseFitFunc!=5 && fPhaseFitFunc!=7 && fPhaseFitFunc!= 9){
     std::cout << "[NMRInputManager::GetInputParameters]: Invalid fit function = " << fPhaseFitFunc << std::endl;
     exit(1); 
   }

}
//______________________________________________________________________________
void NMRInputManager::GetRunList(const char *inpath){
 
   int k=0,irun=0; 
 
   std::ifstream infile;
   infile.open(inpath,std::ios::in);

   if( infile.fail() ){
      printf("[NMRFileManager::GetRunList]: Cannot open the file: %s.  Exiting... \n",inpath);
      exit(1);
   }else{
      while( !infile.eof() ){
            infile >> irun; 
            fRunList[k] = irun;
            k++; 
      }
      infile.close(); 
   }

   k--; 
   fNumRuns = k; 
 
}
//______________________________________________________________________________
void NMRInputManager::ReadRunSummary(int RunNumber){

   // read the summary file for a run; simplifies what the user needs to input
   // because we can get: 
   // - the clock frequency, expected IF, LO frequency, RF frequency 
   // - the number of pulses 

   const int MAX = 2000; 
   char itag[MAX],ivalue[MAX]; 
   
   char *inpath = new char[MAX];
   sprintf(inpath,"./data/run-%05d/summary.dat",RunNumber); 

   const char *adc               = "adc_id"; 
   const char *adc_ch            = "adc_channel_number"; 
   const char *adc_num_samples   = "adc_number_of_samples"; 
   const char *adc_clock_freq    = "adc_clock_frequency"; 
   const char *adc_signal_length = "adc_signal_length"; 
   const char *exp_freq          = "expected_IF_frequency"; 
   const char *lo_freq           = "LO_frequency";            // local oscillator frequency
   const char *rf_freq           = "pi2_frequency_1";         // frequency of pulse sent to probe
   const char *bnc_voltage       = "bnc_voltage"; 
   const char *ntype_voltage     = "ntype_voltage";
   const char *num_pulses        = "num_pulses";  
   const char *run               = "run_number"; 
   const char *eof               = "end_of_file";  
 
   std::ifstream infile;
   infile.open(inpath,std::ios::in);

   if( infile.fail() ){
      printf("[NMRInputManager::ReadRunSummary]: Cannot open the file: %s.  Exiting... \n",inpath);
      exit(1);
   }else{
      while( !infile.eof() ){
         infile >> itag >> ivalue; 
         // printf("%s %15.2lf \n",itag,ivalue);
         if( !NMRUtility::AreEquivStrings(itag,eof) ){
            if( NMRUtility::AreEquivStrings(itag,run)               ) fRunNumber        = atoi(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,num_pulses)        ) fNumPulses        = atoi(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,adc)               ) fADCID            = atoi(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,adc_ch)            ) fADCChannelNumber = atoi(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,adc_num_samples)   ) fADCNumSamples    = atoi(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,adc_clock_freq)    ) fSampleFreq       = atof(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,adc_signal_length) ) fADCSignalLength  = atof(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,exp_freq)          ) fExpFreq          = atof(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,lo_freq)           ) fLOFreq           = atof(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,rf_freq)           ) fPi2Freq          = atof(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,bnc_voltage)       ) fBNCVoltage       = atof(ivalue);  
            if( NMRUtility::AreEquivStrings(itag,ntype_voltage)     ) fNTypeVoltage     = atof(ivalue);  
         }else{
            break;
         }
      }
      infile.close(); 
   }

   delete[] inpath;
   // delete prefix; 

   // check on the anticipated IF
   if(fExpFreq==0){
      std::cout << "[NMRInputManager::ReadRunSummary]: IF = 0? Assuming 10 kHz." << std::endl;
      fExpFreq = 10E+3; 
   }

}
//______________________________________________________________________________
void NMRInputManager::Print(){
   std::cout << "============= Input Parameters =============" << std::endl;
   // printf("Month                = %d     \n",fMonth                );  
   // printf("Day                  = %d     \n",fDay                  );  
   // printf("Year                 = %d     \n",fYear                 );  
   printf("Start Time (ZC)      = %.3E s \n",fStartTimeZC          );
   printf("End Time (ZC)        = %.3E s \n",fEndTimeZC            );      
   printf("Verbosity            = %d     \n",fVerbosity            );     
   printf("Offset Order         = %d     \n",fOffsetOrder          );
   printf("Zero Crossing Status = %d     \n",(int)fUseZeroCrossing );
   printf("Time Fit Status      = %d     \n",(int)fUseTimeFit      );
   printf("T2 Time Status       = %d     \n",(int)fUseT2Time       );
   printf("Phase Fit Status     = %d     \n",(int)fUsePhaseFit     );
   printf("Integer Cycle Status = %d     \n",(int)fUseIntegerCycles);
   printf("Phase Fit Function   = pol-%d \n",fPhaseFitFunc         ); 
}
//______________________________________________________________________________
void NMRInputManager::PrintRunSummary(){
   std::cout << "============= Input Parameters: Run Summary =============" << std::endl;
   printf("Run Number           = %d      \n",fRunNumber            );  
   printf("Number of Pulses     = %d      \n",fNumPulses            );  
   printf("Expected Frequency   = %.3E Hz \n",fExpFreq              );        
   printf("Sample Frequency     = %.3E Hz \n",fSampleFreq           );        
   printf("LO Frequency         = %.3E Hz \n",fLOFreq               ); 
   printf("pi/2 Frequency       = %.3E Hz \n",fPi2Freq              ); 
   printf("LO BNC Voltage       = %.3E V  \n",fBNCVoltage           );
   printf("LO NType Voltage     = %.3E V  \n",fNTypeVoltage         );
   printf("ADC ID               = %d      \n",fADCID                );       
   printf("ADC Channel Number   = %d      \n",fADCChannelNumber     );       
   // printf("Number of Samples    = %d      \n",fADCNumSamples        );
   // printf("Signal Length        = %.3E s  \n",fADCSignalLength      );
}
//______________________________________________________________________________
void NMRInputManager::PrintRunList(){
   std::cout << "============= Input Parameters: Run List =============" << std::endl;
   for(int i=0;i<fNumRuns;i++) std::cout << fRunList[i] << std::endl;
}
