#ifndef NMRRUN_H
#define NMRRUN_H 

// a generic NMR run; consists of an arbitrary number of NMR pulses 

#include <iostream> 
#include <cstdlib>  
#include "NMRPulseAnalyzed.h"

class NMRRun{

   private:
      int fVerbosity; 
      int fPulseIndex; 
      int fNumPulses; 
      int fRunNumber;
      int fMeanNumZeroCrossings;  

      double fMeanNoiseRMS,fMeanAmpl ,fMeanSNR  ,fMeanNumCycles;   
      double fSigNoiseRMS ,fSigAmpl  ,fSigSNR   ,fSigNumCycles;   
      double *fFreqMeanZC,*fFreqSigZC;  
      double fFreqMeanFit,fFreqMeanPhaseFit;  
      double fFreqSigFit ,fFreqSigPhaseFit; 

      NMRPulseAnalyzed **fPulse;                                    // a double-pointer to NMR Pulses 

   public: 
      NMRRun(int NumPulses=1);
      ~NMRRun(); 

      void ClearData(); 
      void PrintStatistics() const; 
      void PrintPulseData(int index=-1) const; 
      void AddNMRPulse(NMRPulseAnalyzed *aPulse); 
      // void SetNumPulses(int NumPulses); 
      void SetVerbosity(int v)                                 {fVerbosity            = v;} 
      void SetRunNumber(int r)                                 {fRunNumber            = r;} 
      void SetMeanFrequencyZeroCrossingMidpoint(double x)      {fFreqMeanZC[0]        = x;}  
      void SetMeanFrequencyZeroCrossingLinearInterp(double x)  {fFreqMeanZC[1]        = x;}  
      void SetMeanFrequencyZeroCrossingLeastSquares(double x)  {fFreqMeanZC[2]        = x;}  
      void SetMeanFrequencyFit(double x)                       {fFreqMeanFit          = x;}  
      void SetMeanFrequencyPhaseFit(double x)                  {fFreqMeanPhaseFit     = x;}  
      void SetSigmaFrequencyZeroCrossingMidpoint(double x)     {fFreqSigZC[0]         = x;}  
      void SetSigmaFrequencyZeroCrossingLinearInterp(double x) {fFreqSigZC[1]         = x;}  
      void SetSigmaFrequencyZeroCrossingLeastSquares(double x) {fFreqSigZC[2]         = x;}  
      void SetSigmaFrequencyFit(double x)                      {fFreqSigFit           = x;}  
      void SetSigmaFrequencyPhaseFit(double x)                 {fFreqSigPhaseFit      = x;}  
      void SetMeanNumZeroCrossings(int x)                      {fMeanNumZeroCrossings = x;} 
      void SetMeanAmplitude(double x)                          {fMeanAmpl             = x;}  
      void SetMeanNoiseRMS(double x)                           {fMeanNoiseRMS         = x;}  
      void SetMeanNumCycles(double x)                          {fMeanNumCycles        = x;}  
      void SetMeanSignalToNoiseRatio(double x)                 {fMeanSNR              = x;}  
      void SetSigmaAmplitude(double x)                         {fSigAmpl              = x;}  
      void SetSigmaNoiseRMS(double x)                          {fSigNoiseRMS          = x;}  
      void SetSigmaNumCycles(double x)                         {fSigNumCycles         = x;}  
      void SetSigmaSignalToNoiseRatio(double x)                {fSigSNR               = x;}  
      
      // data from a specific pulse  
      int GetPulseNumZeroCrossings(int i)                     const {return fPulse[i]->GetNumZeroCrossings();}                     
      int GetPulseNumber(int i)                               const {return fPulse[i]->GetPulseNumber();     } 
 
      double GetPulseFrequencyZeroCrossingMidpoint(int i)     const {return fPulse[i]->GetFrequencyZeroCrossingMidpoint();     }   
      double GetPulseFrequencyZeroCrossingLinearInterp(int i) const {return fPulse[i]->GetFrequencyZeroCrossingLinearInterp(); }   
      double GetPulseFrequencyZeroCrossingLeastSquares(int i) const {return fPulse[i]->GetFrequencyZeroCrossingLeastSquares(); }   
      double GetPulseFrequencyFit(int i)                      const {return fPulse[i]->GetFrequencyFit();                      }   
      double GetPulseFrequencyPhaseFit(int i)                 const {return fPulse[i]->GetFrequencyPhaseFit();                 }   
      double GetPulseAmplitude(int i)                         const {return fPulse[i]->GetAmplitude();                         }   
      double GetPulseNoiseRMS(int i)                          const {return fPulse[i]->GetNoiseRMS();                          }   
      double GetPulseSignalToNoiseRatio(int i)                const {return fPulse[i]->GetSignalToNoiseRatio();                }   
      double GetPulseNumCycles(int i)                         const {return fPulse[i]->GetNumCycles();                         }   

      // data for a set of pulses (run) 
      int GetRunNumber()                                      const {return fRunNumber;} 
      int GetNumPulses()                                      const {return fNumPulses;}  
      int GetMeanNumZeroCrossings()                           const {return fMeanNumZeroCrossings;} 

      double GetFrequencyMeanZeroCrossingMidpoint()           const {return fFreqMeanZC[0];    }  
      double GetFrequencyMeanZeroCrossingLinearInterp()       const {return fFreqMeanZC[1];    }  
      double GetFrequencyMeanZeroCrossingLeastSquares()       const {return fFreqMeanZC[2];    }  
      double GetFrequencySigmaZeroCrossingMidpoint()          const {return fFreqSigZC[0];     }  
      double GetFrequencySigmaZeroCrossingLinearInterp()      const {return fFreqSigZC[1];     }  
      double GetFrequencySigmaZeroCrossingLeastSquares()      const {return fFreqSigZC[2];     }  
      double GetFrequencyMeanFit()                            const {return fFreqMeanFit;      } 
      double GetFrequencySigmaFit()                           const {return fFreqSigFit;       } 
      double GetFrequencyMeanPhaseFit()                       const {return fFreqMeanPhaseFit; } 
      double GetFrequencySigmaPhaseFit()                      const {return fFreqSigPhaseFit;  } 
      double GetMeanAmplitude()                               const {return fMeanAmpl;         }  
      double GetMeanNoiseRMS()                                const {return fMeanNoiseRMS;     }  
      double GetMeanNumCycles()                               const {return fMeanNumCycles;    }  
      double GetMeanSignalToNoiseRatio()                      const {return fMeanSNR;          }  
      double GetSigmaAmplitude()                              const {return fSigAmpl;          }  
      double GetSigmaNoiseRMS()                               const {return fSigNoiseRMS;      }  
      double GetSigmaNumCycles()                              const {return fSigNumCycles;     }  
      double GetSigmaSignalToNoiseRatio()                     const {return fSigSNR;           }  

};

#endif 
