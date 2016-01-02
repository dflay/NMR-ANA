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
   fStartRun         = 0;
   fEndRun           = 0;
   fNumPulses        = 0;
   fStartTimeZC      = 0;
   fEndTimeZC        = 0;
   fExpFreq          = 0;
   fSampleFreq       = 0;
   fLOFreq           = 0; 
   fRFFreq           = 0; 
   fADCNumSamples    = 0;
   fADCSignalLength  = 0;
   fBNCVoltage       = 0;
   fNTypeVoltage     = 0;
}
//______________________________________________________________________________
NMRInputManager::~NMRInputManager(){

}
//______________________________________________________________________________
NMRInputManager::NMRInputManager(const NMRInputManager &a){
   // copy constructor 
   // shallow copy (don't need deep copy, no pointers in class) 
   fUseZeroCrossing  = a.GetZeroCrossingStatus(); 
   fUseTimeFit       = a.GetTimeFitStatus(); 
   fUsePhaseFit      = a.GetPhaseFitStatus(); 
   fUseIntegerCycles = a.GetIntegerCycleStatus(); 
   fADCID            = a.GetADCID(); 
   fADCChannelNumber = a.GetADCChannelNumber(); 
   fMonth            = a.GetMonth(); 
   fDay              = a.GetDay(); 
   fYear             = a.GetYear(); 
   fVerbosity        = a.GetVerbosity(); 
   fOffsetOrder      = a.GetOffsetOrder(); 
   fRunNumber        = a.GetRunNumber(); 
   fStartRun         = a.GetStartRunNumber(); 
   fEndRun           = a.GetEndRunNumber(); 
   fNumPulses        = a.GetNumPulses(); 
   fStartTimeZC      = a.GetStartTimeZC(); 
   fEndTimeZC        = a.GetEndTimeZC(); 
   fExpFreq          = a.GetExpectedFrequency(); 
   fSampleFreq       = a.GetSampleFrequency(); 
   fLOFreq           = a.GetLOFrequency();
   fRFFreq           = a.GetRFFrequency();
   fADCNumSamples    = a.GetNumSamples(); 
   fADCSignalLength  = a.GetSignalLength();
   fBNCVoltage       = a.GetBNCVoltage();     
   fNTypeVoltage     = a.GetNTypeVoltage();     
}
//______________________________________________________________________________
NMRInputManager::NMRInputManager(const NMRInputManager *a){
   // copy constructor 
   // shallow copy (don't need deep copy, no pointers in class) 
   fUseZeroCrossing  = a->GetZeroCrossingStatus(); 
   fUseTimeFit       = a->GetTimeFitStatus(); 
   fUsePhaseFit      = a->GetPhaseFitStatus(); 
   fUseIntegerCycles = a->GetIntegerCycleStatus(); 
   fADCID            = a->GetADCID(); 
   fADCChannelNumber = a->GetADCChannelNumber(); 
   fMonth            = a->GetMonth(); 
   fDay              = a->GetDay(); 
   fYear             = a->GetYear(); 
   fVerbosity        = a->GetVerbosity(); 
   fOffsetOrder      = a->GetOffsetOrder(); 
   fRunNumber        = a->GetRunNumber(); 
   fStartRun         = a->GetStartRunNumber(); 
   fEndRun           = a->GetEndRunNumber(); 
   fNumPulses        = a->GetNumPulses(); 
   fStartTimeZC      = a->GetStartTimeZC(); 
   fEndTimeZC        = a->GetEndTimeZC(); 
   fExpFreq          = a->GetExpectedFrequency(); 
   fSampleFreq       = a->GetSampleFrequency(); 
   fLOFreq           = a->GetLOFrequency();
   fRFFreq           = a->GetRFFrequency();
   fADCNumSamples    = a->GetNumSamples(); 
   fADCSignalLength  = a->GetSignalLength();
   fBNCVoltage       = a->GetBNCVoltage();     
   fNTypeVoltage     = a->GetNTypeVoltage();     
}
//______________________________________________________________________________
void NMRInputManager::Update(const NMRInputManager &a){
   // shallow copy (don't need deep copy, no pointers in class), the "hard" way  
   fUseZeroCrossing  = a.GetZeroCrossingStatus(); 
   fUseTimeFit       = a.GetTimeFitStatus(); 
   fUsePhaseFit      = a.GetPhaseFitStatus(); 
   fUseIntegerCycles = a.GetIntegerCycleStatus(); 
   fADCID            = a.GetADCID(); 
   fADCChannelNumber = a.GetADCChannelNumber(); 
   fMonth            = a.GetMonth(); 
   fDay              = a.GetDay(); 
   fYear             = a.GetYear(); 
   fVerbosity        = a.GetVerbosity(); 
   fOffsetOrder      = a.GetOffsetOrder(); 
   fRunNumber        = a.GetRunNumber(); 
   fStartRun         = a.GetStartRunNumber(); 
   fEndRun           = a.GetEndRunNumber(); 
   fNumPulses        = a.GetNumPulses(); 
   fStartTimeZC      = a.GetStartTimeZC(); 
   fEndTimeZC        = a.GetEndTimeZC(); 
   fExpFreq          = a.GetExpectedFrequency(); 
   fSampleFreq       = a.GetSampleFrequency(); 
   fLOFreq           = a.GetLOFrequency();
   fRFFreq           = a.GetRFFrequency();
   fADCNumSamples    = a.GetNumSamples(); 
   fADCSignalLength  = a.GetSignalLength();
   fBNCVoltage       = a.GetBNCVoltage();     
   fNTypeVoltage     = a.GetNTypeVoltage();     
}
//______________________________________________________________________________
void NMRInputManager::Update(const NMRInputManager *a){
   // shallow copy (don't need deep copy, no pointers in class), the "hard" way  
   fUseZeroCrossing  = a->GetZeroCrossingStatus(); 
   fUseTimeFit       = a->GetTimeFitStatus(); 
   fUsePhaseFit      = a->GetPhaseFitStatus(); 
   fUseIntegerCycles = a->GetIntegerCycleStatus(); 
   fADCID            = a->GetADCID(); 
   fADCChannelNumber = a->GetADCChannelNumber(); 
   fMonth            = a->GetMonth(); 
   fDay              = a->GetDay(); 
   fYear             = a->GetYear(); 
   fVerbosity        = a->GetVerbosity(); 
   fOffsetOrder      = a->GetOffsetOrder(); 
   fRunNumber        = a->GetRunNumber(); 
   fStartRun         = a->GetStartRunNumber(); 
   fEndRun           = a->GetEndRunNumber(); 
   fNumPulses        = a->GetNumPulses(); 
   fStartTimeZC      = a->GetStartTimeZC(); 
   fEndTimeZC        = a->GetEndTimeZC(); 
   fExpFreq          = a->GetExpectedFrequency(); 
   fSampleFreq       = a->GetSampleFrequency(); 
   fLOFreq           = a->GetLOFrequency();
   fRFFreq           = a->GetRFFrequency();
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
   const char *start_run            = "start_run"; 
   const char *end_run              = "end_run"; 
   const char *tstart               = "t_start"; 
   const char *tend                 = "t_end"; 
   const char *verb                 = "verbosity"; 
   const char *offset               = "offset_correction_order";
   const char *zc_status            = "zero_crossing"; 
   const char *time_fit_status      = "time_fit"; 
   const char *phase_fit_status     = "phase_fit"; 
   const char *integer_cycle_status = "integer_cycles"; 
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
               if( NMRUtility::AreEquivStrings(itag,start_run)   ) fStartRun     = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,end_run)     ) fEndRun       = (int)ivalue;  
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

            }else{
               break;
            }
         }
         k++;
      }
      infile.close(); 
   }

}
//______________________________________________________________________________
void NMRInputManager::ReadRunSummary(int RunNumber){

   // read the summary file for a run; simplifies what the user needs to input
   // because we can get: 
   // - the clock frequency, expected IF, LO frequency, RF frequency 
   // - the number of pulses 

   const int MAX = 2000; 
   char itag[MAX]; 
   
   char *inpath = new char[MAX];
   char *prefix = new char[MAX]; 
   sprintf(prefix,"./data/%d/%d_%d/%d_%d_%d",fYear,fMonth,fYear-2000,fMonth,fDay,fYear-2000);  
   sprintf(inpath,"%s/run-%d/summary.dat",prefix,RunNumber); 

   double ivalue=0; 

   const char *adc               = "adc_id"; 
   const char *adc_ch            = "adc_channel_number"; 
   const char *adc_num_samples   = "adc_number_of_samples"; 
   const char *adc_clock_freq    = "adc_clock_frequency"; 
   const char *adc_signal_length = "adc_signal_length"; 
   const char *exp_freq          = "expected_IF_frequency"; 
   const char *lo_freq           = "LO_frequency";            // local oscillator frequency
   const char *rf_freq           = "RF_frequency";            // frequency of pulse sent to probe
   const char *bnc_voltage       = "bnc_voltage"; 
   const char *ntype_voltage     = "ntype_voltage";
   const char *num_pulses        = "number_of_pulses";  
   const char *run               = "run_number"; 
   const char *eof               = "end_of_file";  
 
   std::ifstream infile;
   infile.open(inpath,std::ios::in);

   if( infile.fail() ){
      printf("[NMRFileManager::ReadRunSummary]: Cannot open the file: %s.  Exiting... \n",inpath);
      exit(1);
   }else{
      while( !infile.eof() ){
         infile >> itag >> ivalue; 
         // printf("%s %15.2lf \n",itag,ivalue);
         if( !NMRUtility::AreEquivStrings(itag,eof) ){
            if( NMRUtility::AreEquivStrings(itag,run)               ) fRunNumber        = (int)ivalue;  
            if( NMRUtility::AreEquivStrings(itag,num_pulses)        ) fNumPulses        = (int)ivalue;  
            if( NMRUtility::AreEquivStrings(itag,adc)               ) fADCID            = (int)ivalue;  
            if( NMRUtility::AreEquivStrings(itag,adc_ch)            ) fADCChannelNumber = (int)ivalue;  
            if( NMRUtility::AreEquivStrings(itag,adc_num_samples)   ) fADCNumSamples    = (int)ivalue;  
            if( NMRUtility::AreEquivStrings(itag,adc_clock_freq)    ) fSampleFreq       = ivalue;  
            if( NMRUtility::AreEquivStrings(itag,adc_signal_length) ) fADCSignalLength  = ivalue;  
            if( NMRUtility::AreEquivStrings(itag,exp_freq)          ) fExpFreq          = ivalue;  
            if( NMRUtility::AreEquivStrings(itag,lo_freq)           ) fLOFreq           = ivalue;  
            if( NMRUtility::AreEquivStrings(itag,rf_freq)           ) fRFFreq           = ivalue;  
            if( NMRUtility::AreEquivStrings(itag,bnc_voltage)       ) fBNCVoltage       = ivalue;  
            if( NMRUtility::AreEquivStrings(itag,ntype_voltage)     ) fNTypeVoltage     = ivalue;  
         }else{
            break;
         }
      }
      infile.close(); 
   }

   delete inpath;
   delete prefix; 

}
//______________________________________________________________________________
void NMRInputManager::Print(){
   std::cout << "============= Input Parameters =============" << std::endl;
   printf("Month                = %d   \n",fMonth                );  
   printf("Day                  = %d   \n",fDay                  );  
   printf("Year                 = %d   \n",fYear                 );  
   printf("Start Run            = %d   \n",fStartRun             );  
   printf("End Run              = %d   \n",fEndRun               );     
   printf("Number of Pulses     = %d   \n",fNumPulses            );  
   printf("Start Time (ZC)      = %.3E \n",fStartTimeZC          );
   printf("End Time (ZC)        = %.3E \n",fEndTimeZC            );      
   printf("Verbosity            = %d   \n",fVerbosity            );     
   printf("Offset Order         = %d   \n",fOffsetOrder          );
   printf("Zero Crossing Status = %d   \n",(int)fUseZeroCrossing );
   printf("Time Fit Status      = %d   \n",(int)fUseTimeFit      );
   printf("Phase Fit Status     = %d   \n",(int)fUsePhaseFit     );
   printf("Integer Cycle Status = %d   \n",(int)fUseIntegerCycles);
}
//______________________________________________________________________________
void NMRInputManager::PrintRunSummary(){
   std::cout << "============= Input Parameters: Run Summary =============" << std::endl;
   printf("Run Number           = %d   \n",fRunNumber            );  
   printf("Number of Pulses     = %d   \n",fNumPulses            );  
   printf("Expected Frequency   = %.3E \n",fExpFreq              );        
   printf("Sample Frequency     = %.3E \n",fSampleFreq           );        
   printf("LO Frequency         = %.3E \n",fLOFreq               ); 
   printf("RF Frequency         = %.3E \n",fRFFreq               ); 
   printf("LO BNC Voltage       = %.3E \n",fBNCVoltage           );
   printf("LO NType Voltage     = %.3E \n",fNTypeVoltage         );
   printf("ADC ID               = %d   \n",fADCID                );       
   printf("ADC Channel Number   = %d   \n",fADCChannelNumber     );       
   printf("Number of Samples    = %d   \n",fADCNumSamples        );
   printf("Signal Length        = %.3E \n",fADCSignalLength      );
}
