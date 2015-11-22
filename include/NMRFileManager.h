#ifndef NMRFILEMANAGER_H
#define NMRFILEMANAGER_H

// a class to manage the input and output of data files 

/// TODO                                                                        
/// 1. Change zero crossing vectors into arrays to speed up the offset stuff (not imperative)  

#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <vector>
#include <sys/stat.h> 

#include "NMRPulse.h"
#include "NMRMath.h" 
#include "NMRRun.h"
#include "NMRInputManager.h"

using namespace std; 

class NMRFileManager{

   private: 
      char *fDataDir;                                                                   // data directory path  
      char *fOutputBaseDir,*fOutputDir;                                                 // output dir path; OutputBaseDir has the path up through the date; 
                                                                                        // OutputDir has all the way through the run number. 

      bool fOffsetFail;                                                                 // offset flag; if offset corrections fail, return zero on all offset corrections 
      bool fUseZeroCrossing;                                                            // turn on zero crossing calculations (for frequency extraction)   
      bool fUseTimeRangeZC;                                                             // use time range (for zero crossing) 

      int fVerbosity;                                                                   // verbosity level 
      // int fOffsetOrder;                                                                 // offset correction order (1--5); default is 4.  
      int fStartRun,fEndRun;                                                            // start and end run numbers 
      int fRunNumber;                                                                   // run number
      // int fMonth,fDay,fYear;                                                            // month, day and year 
      // int fADCID;                                                                       // SIS ADC ID number  
      int fSIZE,fNPTS;                                                                  // fSIZE = 1E+6, fNPTS = total number of data points 
      int fNCycles;                                                                     // number of cycles (used in offset correction) 
      // int fNumPulses; 
      int *fSample;                                                                     // sample number 

      unsigned short *fADCCounts;                                                       // adc counts  
    
      // double fSampleFreq;                                                               // sample frequency (Hz) 
      // double fExpFreq;                                                                  // expected frequency (Hz) 
      double fTStart,fTEnd;                                                             // cuts to apply to data according to time (s) 
      // double fTStartZC,fTEndZC;                                                         // start and end time of data for ZC analysis (use in offset corrections)  
      double *fTime,*fVoltage;                                                          // time (s), voltage (V)
      double *fX,*fY,*fEY;                                                              // for offset corrections  

      struct stat fSB;                                                                  // for checking on file states   

      void ClearDataArrays();                                                           // set arrays to zero  
      void DoOffsetCorrectionAndRMSNoiseVMax(int order,double t_thr,NMRPulse *aPulse,double &RMSNoise,double &VMax);  // apply voltage offset of arbitrary order to a pulse  
      void ApplyOffset(double offset);                                                  // apply voltage offset to data 
      void ApplyOffset(double offset,NMRPulse *aPulse);                                 // apply voltage offset to data 
      void ApplyOffsetLinear(double *offset,NMRPulse *aPulse);                          // apply voltage offset to data 
      void ImportDataRawADCBin(int run,int pulse);
      void Convert(int adcID,const char *Units); 
      // void SetDataDirectory(char *path){fDataDir = path;} 
      void PrintRunToFile(NMRRun *aRun); 
      void PrintRunFreqStatsToFile(NMRRun *aRun); 
      void PrintRunMetaStatsToFile(NMRRun *aRun); 
      void CalculateRMSNoiseVMax(double t_min,double t_max,double t_thr,double &rms_noise,double &vmax); 
      void CalculateRMSNoiseVMax(double t_thr,NMRPulse *aPulse,double &rms_noise,double &vmax); 
      void GetOffsetLinear(double input_offset,NMRPulse *aPulse,double *offset); 

      int CheckOffset(double,double,double,double,double); 

      double GetTMax();
      double GetTDiff(vector<double> tCross,double &delta_t_even_nc,double &delta_t_odd_nc);
      double GetPulseTimeStamp(int run,int pulse);  
      double GetOffset(double t_min,double t_max,double t_thr); 
      double GetOffset(double t_thr,NMRPulse *aPulse); 
      double GetOffsetZC(double input_offset,NMRPulse *aPulse);
      double GetRMSNoise(double t_thr,NMRPulse *aPulse);  
      double GetVMax(NMRPulse *aPulse);  

   public: 
      NMRFileManager(); 
      NMRFileManager(const NMRFileManager &fm);
      NMRFileManager(const NMRFileManager *fm);
      ~NMRFileManager(); 

      // copy constructors 
      NMRFileManager& operator=(const NMRFileManager &fm);
      NMRFileManager* operator=(const NMRFileManager *fm);
      NMRFileManager* Clone() const{return new NMRFileManager(this); }    // Make a copy of this class 

      NMRInputManager *InputManager; 

      void GetInputParameters(const char *); 

      // void SetDate(int M,int D,int Y){
      //    fMonth = M;
      //    fDay   = D;
      //    fYear  = Y;
      // }
      // void SetTimeRange(double min,double max)             {fTStartZC = min; fTEndZC = max;} 
      // void SetMonth(int x)                                 {fMonth       = x;} 
      // void SetDay(int x)                                   {fDay         = x;} 
      // void SetYear(int x)                                  {fYear        = x;} 
      // void SetADCID(int a)                                 {fADCID       = a;} 
      void SetRunNumber(int r)                             {fRunNumber   = r;} 
      // void SetSampleFrequency(double f)                    {fSampleFreq  = f;} 
      // void SetExpectedFrequency(double f)                  {fExpFreq     = f;} 
      void SetVerbosity(int v)                             {fVerbosity   = v;} 
      // void SetOffsetOrder(int o)                           {fOffsetOrder = o;}
      void InitInputDirectory();
      void InitOutputDirectory();
      void Load(int RunNum,int PulseNum,NMRPulse *aPulse);     // import data into NMRPulse 

      // functions to print data to files  
      void PrintResultsToFile(NMRRun *aRun); 
      void AppendToFile(const char *fn,const char *header,int i,double a,double b,double c,double d); 

      // directory and file management 
      int MakeDirectory(const char *path);          // make a directory based on a path   
      int DeleteFile(const char *fn);               // delete a file  
      int DeleteSymLink(const char *suffix);        // delete a symbolic link 

      // misc

      char *GetDataDir()            const {return fDataDir;}  
      char *GetOutputBaseDir()      const {return fOutputBaseDir;}  
      char *GetOutputDir()          const {return fOutputDir;}  

      bool GetOffsetStatus()        const {return fOffsetFail;} 
 
      // int GetOffsetOrder()          const {return fOffsetOrder;} 
      // int GetNumPulses()            const {return fNumPulses;} 
      int GetVerbosity()            const {return fVerbosity;}

      // double GetStartTimeZC()       const {return fTStartZC;}    
      // double GetEndTimeZC()         const {return fTEndZC;}    
      // double GetExpectedFrequency() const {return fExpFreq;} 
      // double GetSampleFrequency()   const {return fSampleFreq;} 

};

#endif 
