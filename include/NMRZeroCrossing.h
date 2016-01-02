#ifndef NMRZEROCROSSING_H
#define NMRZEROCROSSING_H

// a class that does zero crossing analysis to extract the frequency of a signal 

#include <cstdlib> 
#include <iostream>
#include "NMRPulse.h"
#include "NMRMath.h"
#include "NMRFileManager.h"

#define MAX_SIZE 1E+6 

class NMRZeroCrossing{

   private:
      bool fUseTimeRange;                                     // do zero crossings over a specified range in time 
      bool fUseMidpoint,fUseLinearInterp,fUseLeastSq;         // booleans for each method  
      bool fUseIntegerCycles;                                 // use only integer number of cycles in calculation 

      int fVerbosity;         
      int fNPTS;                                              // number of points to use in least squares fitting 
      int fNPTSUseable;                                       // number of points to use in least squares fitting (useable; we may have less -- see StoreData method) 
      int fStep;                                              // number of points to skip in counting zero crossings
      int *fZC;                                               // number of zero crossings 
      int fNZC;                                               // number of zero crossings (single pulse) 
      
      double fTMin,fTMax;                                     // time range to consider when fUseTimeRange is true 
      double *fX,*fY,*fEY;                                    // "analysis arrays": store data for fitting here  
      double *fFREQ;                                          // final frequency results 
      double *fNC;                                            // number of cycles
      double fSampleFreq;                                     // sample frequency
      double fExpFreq;                                        // expected frequency  
      
      NMRFileManager *fFileManager;                           // a file manager used to print diagnostic data to files 

      int *fNCrossing,*fCrossingIndex;

      double *fTcross,*fVcross;
      double *fFreqAtCrossing,*fNumCycles;

      // vector<int> fNCrossing,fCrossingIndex;                  // crossing indices 

      // vector<double> fTcross,fVcross;                         // time and voltage of crossing 
      // vector<double> fFreqAtCrossing;                         // frequencies for each crossing  
      // vector<double> fNumCycles;                              // Number of cycles at each crossing   

      void Reset(); 
      void ClearAnaArrays(); 
      void ClearVectors(); 
      void InitAnaArrays();
      void PrintVectorData(int Type,int PulseNumber); 
      void CountZeroCrossings(int method,NMRPulse *aPulse);   // uses the NMRMath::CountZeroCrossings function 
      void SetNumPointsForFits(int n); 
      void SetStepSize(int i)                               {fStep = i;     } 

      int CalculateFrequencies(int &TrueNumCrossings,double &FreqFullRange);

   public:
      NMRZeroCrossing();
      ~NMRZeroCrossing();

      void UseAll(){
         UseMidpoint(); 
         UseLinearInterpolation();
         UseLeastSquares();
      }

      void UseTimeRange(bool val=true){
         if(val) std::cout << "[NMRZeroCrossing]: Will use time range in counting zero crossings." << std::endl;
         fUseTimeRange = val;
      }  
      void UseMidpoint(bool v=true){
         if(v) std::cout << "[NMRZeroCrossing]: Will use midpoint method." << std::endl;
         fUseMidpoint = v;
      }
      void UseLinearInterpolation(bool v=true){
         if(v) std::cout << "[NMRZeroCrossing]: Will use linear interpolation method." << std::endl;
         fUseLinearInterp = v;
      }
      void UseLeastSquares(bool v=true){
         if(v) std::cout << "[NMRZeroCrossing]: Will use least squares method." << std::endl;
         fUseLeastSq = v;
      }

      void UseIntegerCycles(bool v=true){
         if(v) std::cout << "[NMRZeroCrossing]: Will use integer number of cycles ONLY." << std::endl;
         fUseIntegerCycles = v;
      }

      void SetupForRun()                             { fFileManager->InitOutputDirectory(); }
      
      void UpdateFileManager(NMRFileManager *fm)     { fFileManager->Update(fm); }  

      void UpdateParameters();                                              // update fNPTS and fStep  
      void SetFileManager(NMRFileManager *fm)        {fFileManager = new NMRFileManager(fm);}  
      void SetVerbosity(int v)                       {fVerbosity   = v; } 
      void SetSampleFrequency(double f)              {fSampleFreq  = f; } 
      void SetExpectedFrequency(double f)            {fExpFreq     = f; } 
      void SetMinTime(double t)                      {fTMin        = t; } 
      void SetMaxTime(double t)                      {fTMax        = t; }
      void SetTimeRange(double tmin,double tmax){
         fTMin = tmin;
         fTMax = tmax;
      }     

      int Calculate(NMRPulse *aPulse);                                       // runs the calculation based on choices 
      // int GetNumAnaBins()                      const {return fNCrossing.size();}  
      int GetNumAnaBins()                      const {return fNZC;}  
      int GetCrossingNumber(int i)             const {return fNCrossing[i];}  
      int GetCrossingIndex(int i)              const {return fCrossingIndex[i];}  
      int GetNumZeroCrossingsMidpoint()        const {return fZC[0];} 
      int GetNumZeroCrossingsLinearInterp()    const {return fZC[1];} 
      int GetNumZeroCrossingsLeastSquares()    const {return fZC[2];} 

      double GetNumCyclesMidpoint()            const {return fNC[0];} 
      double GetNumCyclesLinearInterp()        const {return fNC[1];} 
      double GetNumCyclesLeastSquares()        const {return fNC[2];} 

      double GetFrequencyMidpoint()            const {return fFREQ[0];} 
      double GetFrequencyLinearInterp()        const {return fFREQ[1];} 
      double GetFrequencyLeastSquares()        const {return fFREQ[2];} 

      double GetTimeAtCrossing(int i)          const {return fTcross[i];} 
      double GetVoltageAtCrossing(int i)       const {return fVcross[i];} 
      double GetFrequencyAtCrossing(int i)     const {return fFreqAtCrossing[i];} 
      double GetNumberOfCylces(int i)          const {return fNumCycles[i];} 

};

#endif 
