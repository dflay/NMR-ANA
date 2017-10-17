#ifndef NMRFILEMANAGER_H
#define NMRFILEMANAGER_H

// a class to manage the input and output of data files 

#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <vector>
#include <sys/stat.h> 
#include <dirent.h>
#include <boost/filesystem.hpp>  

#include "NMRDAQEvent.h"
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
      int fSIZE,fNPTS;                                                                  // fSIZE = 1E+6, fNPTS = total number of data points 
      int fNCycles;                                                                     // number of cycles (used in offset correction) 
      int *fSample;                                                                     // sample number 

      unsigned short *fADCCounts;                                                       // adc counts  
    
      double fTStart,fTEnd;                                                             // cuts to apply to data according to time (s) 
      double *fTime,*fVoltage;                                                          // time (s), voltage (V)
      double *fX,*fY,*fEY;                                                              // for offset corrections  

      // for zero crossing calcs 
      int *fNCrossing,*fCrossingIndex;
      double *fTcross,*fVcross;

      struct stat fSB;                                                                  // for checking on file states   

      void ClearDataArrays();                                                           // set arrays to zero  
      void ClearNZCArrays();                                                            // set arrays to zero  
      void DoOffsetCorrectionAndRMSNoiseVMax(int order,double t_thr,NMRPulse *aPulse,double &RMSNoise,double &VMax);  // apply voltage offset of arbitrary order to a pulse  
      void ApplyOffset(double offset);                                                  // apply voltage offset to data 
      void ApplyOffset(double offset,NMRPulse *aPulse);                                 // apply voltage offset to data 
      void ApplyOffsetLinear(double *offset,NMRPulse *aPulse);                          // apply voltage offset to data 
      void ImportDataRawADCBin(int run,int pulse);
      void Convert(int adcID,const char *Units); 
      void PrintRunToFile(NMRRun *aRun); 
      void PrintRunToFileField(NMRRun *aRun); 
      void PrintRunFreqStatsToFile(NMRRun *aRun); 
      void PrintRunFieldStatsToFile(NMRRun *aRun); 

      void PrintRunStatsToFile(NMRRun *aRun); 
      void PrintRunMetaStatsToFile(NMRRun *aRun); 
      void PrintRunFreqToFileZC(NMRRun *aRun); 
      void PrintRunFreqToFileTimeFit(NMRRun *aRun); 
      void PrintRunFreqToFileHilbert(NMRRun *aRun);
      void PrintRunFieldToFileZC(NMRRun *aRun); 
      void PrintRunFieldToFileTimeFit(NMRRun *aRun); 
      void PrintRunFieldToFileHilbert(NMRRun *aRun); 

      void CalculateRMSNoiseVMax(double t_min,double t_max,double t_thr,double &rms_noise,double &vmax); 
      void CalculateRMSNoiseVMax(double t_thr,NMRPulse *aPulse,double &rms_noise,double &vmax); 
      void GetOffsetLinear(double input_offset,NMRPulse *aPulse,double *offset); 

      int CheckOffset(double,double,double,double,double);

      double GetTMax();
      double GetTDiff(int nzc,double *tCross,double &delta_t_even_nc,double &delta_t_odd_nc);
      double GetTDiff(vector<double> tCross,double &delta_t_even_nc,double &delta_t_odd_nc);
      double GetPulseTimeStamp(int run,int pulse);  
      double GetOffset(double t_min,double t_max,double t_thr); 
      double GetOffset(double t_thr,NMRPulse *aPulse); 
      double GetOffsetZC(double input_offset,NMRPulse *aPulse);
      double GetRMSNoise(double t_thr,NMRPulse *aPulse);  
      double GetVMax(NMRPulse *aPulse);  

   public:
      // constructor and destructor  
      NMRFileManager(); 
      ~NMRFileManager();

      // copy constructors  
      NMRFileManager(const NMRFileManager &fm);
      NMRFileManager(const NMRFileManager *fm);

      // overload assignment operator  
      NMRFileManager& operator=(const NMRFileManager &fm);
      NMRFileManager* operator=(const NMRFileManager *fm);

      NMRInputManager *InputManager; 

      void Update(const NMRFileManager *fm); 
      void UpdateInputManager(const NMRInputManager *a); 

      void GetInputParameters(const char *); 

      void SetVerbosity(int v){fVerbosity = v;} 
      void InitInputDirectory();
      void InitOutputDirectory();
      void Load(int RunNum,int PulseNum,NMRPulse *aPulse);     // import data into NMRPulse 

      // functions to print data to files  
      void PrintResultsToFile(NMRRun *aRun); 
      void AppendToFile(const char *fn,const char *header,int i,double a,double b,double c,double d); 

      // directory and file management 
      int MakeDirectory(const char *path);            // make a directory based on a path   
      int DeleteRun(int runNumber);                   // delete a run  
      int DeleteFile(const char *fn);                 // delete a file  
      int DeleteDirectory(const char *path);          // delete a directory   
      int DeleteSymLink(const char *suffix);          // delete a symbolic link 
      
      bool CheckIfExists(const char *name);           // check if file exists
      bool CheckIfDirectoryExists(const char *path);  // check if directory exists 
      bool RunExists(int runNumber);                  // check if run exists 
 
      int ReadEventData(int,int,NMRDAQEvent &);  

      // misc
      char *GetDataDir()       const {return fDataDir;}  
      char *GetOutputBaseDir() const {return fOutputBaseDir;}  
      char *GetOutputDir()     const {return fOutputDir;}  

      bool GetOffsetStatus()   const {return fOffsetFail;} 
 
      int GetVerbosity()       const {return fVerbosity;}

};

#endif 
