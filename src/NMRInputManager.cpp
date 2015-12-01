#include "NMRInputManager.h"
//______________________________________________________________________________
NMRInputManager::NMRInputManager(){
   fUseZeroCrossing  = false;
   fUseTimeFit       = false;
   fUsePhaseFit      = false;
   fUseIntegerCycles = false; 
   fADCID            = 0;
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
   const char *run                  = "run_number"; 
   const char *start_run            = "start_run"; 
   const char *end_run              = "end_run"; 
   const char *npulses              = "number_of_pulses"; 
   const char *tstart               = "t_start"; 
   const char *tend                 = "t_end"; 
   const char *adc                  = "adc_id"; 
   const char *verb                 = "verbosity"; 
   const char *offset               = "offset_correction_order";
   const char *exp_freq             = "expected_frequency"; 
   const char *sample_freq          = "sampling_frequency"; 
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
               if( NMRUtility::AreEquivStrings(itag,run)         ) fRunNumber    = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,start_run)   ) fStartRun     = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,end_run)     ) fEndRun       = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,npulses)     ) fNumPulses    = (int)ivalue;  
               if( NMRUtility::AreEquivStrings(itag,tstart)      ) fStartTimeZC  = ivalue;  
               if( NMRUtility::AreEquivStrings(itag,tend)        ) fEndTimeZC    = ivalue;  
               if( NMRUtility::AreEquivStrings(itag,exp_freq)    ) fExpFreq      = ivalue;  
               if( NMRUtility::AreEquivStrings(itag,sample_freq) ) fSampleFreq   = ivalue;  
               if( NMRUtility::AreEquivStrings(itag,adc)         ) fADCID        = (int)ivalue;  
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
void NMRInputManager::Print(){
   std::cout << "============= Input Parameters =============" << std::endl;
   printf("Month                = %d \n"  ,fMonth                );  
   printf("Day                  = %d \n"  ,fDay                  );  
   printf("Year                 = %d \n"  ,fYear                 );  
   printf("Run Number           = %d \n"  ,fRunNumber            );  
   printf("Start Run            = %d \n"  ,fStartRun             );  
   printf("End Run              = %d \n"  ,fEndRun               );     
   printf("Number of Pulses     = %d \n"  ,fNumPulses            );  
   printf("Start Time (ZC)      = %.3E \n",fStartTimeZC          );
   printf("End Time (ZC)        = %.3E \n",fEndTimeZC            );      
   printf("Expected Frequency   = %.3E \n",fExpFreq              );        
   printf("Sample Frequency     = %.3E \n",fSampleFreq           );        
   printf("ADC ID               = %d \n"  ,fADCID                );       
   printf("Verbosity            = %d \n"  ,fVerbosity            );     
   printf("Offset Order         = %d \n"  ,fOffsetOrder          );
   printf("Zero Crossing Status = %d \n"  ,(int)fUseZeroCrossing );
   printf("Time Fit Status      = %d \n"  ,(int)fUseTimeFit      );
   printf("Phase Fit Status     = %d \n"  ,(int)fUsePhaseFit     );
   printf("Integer Cycle Status = %d \n"  ,(int)fUseIntegerCycles);
}
