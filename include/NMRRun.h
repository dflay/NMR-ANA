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

      double fMeanT2,fSigT2;
      double fMeanNoiseRMS,fMeanAmpl ,fMeanSNR  ,fMeanNumCycles;   
      double fSigNoiseRMS ,fSigAmpl  ,fSigSNR   ,fSigNumCycles;   
      double *fFreqMeanZC,*fFreqSigZC;  
      double *fFreqMeanZC_ph,*fFreqSigZC_ph;  
      double fFreqMeanFit,fFreqMeanPhaseFit;  
      double fFreqSigFit ,fFreqSigPhaseFit;
      double *fBMeanZC,*fBSigZC;  
      double *fBMeanZC_ph,*fBSigZC_ph;  
      double fBMeanFit,fBMeanPhaseFit;  
      double fBSigFit ,fBSigPhaseFit; 

      NMRPulseAnalyzed **fPulse;                                    // a double-pointer to NMR Pulses 

   public: 
      NMRRun(int NumPulses=1);
      ~NMRRun(); 

      void ClearData(); 
      void PrintStatistics() const; 
      void PrintPulseData(int index=-1) const; 
      void AddNMRPulse(NMRPulseAnalyzed *aPulse); 
      void SetNumPulses(int NumPulses); 
      void SetVerbosity(int v)                                         {fVerbosity            = v;} 
      void SetRunNumber(int r)                                         {fRunNumber            = r;} 
      void SetMeanFrequencyZeroCrossingMidpoint(double x)              {fFreqMeanZC[0]        = x;}  
      void SetMeanFrequencyZeroCrossingLinearInterp(double x)          {fFreqMeanZC[1]        = x;}  
      void SetMeanFrequencyZeroCrossingLeastSquares(double x)          {fFreqMeanZC[2]        = x;}  
      void SetMeanFrequencyZeroCrossingMidpointPhaseFit(double x)      {fFreqMeanZC_ph[0]     = x;}  
      void SetMeanFrequencyZeroCrossingLinearInterpPhaseFit(double x)  {fFreqMeanZC_ph[1]     = x;}  
      void SetMeanFrequencyZeroCrossingLeastSquaresPhaseFit(double x)  {fFreqMeanZC_ph[2]     = x;}  
      void SetMeanFrequencyFit(double x)                               {fFreqMeanFit          = x;}  
      void SetMeanFrequencyPhaseFit(double x)                          {fFreqMeanPhaseFit     = x;}  
      void SetSigmaFrequencyZeroCrossingMidpoint(double x)             {fFreqSigZC[0]         = x;}  
      void SetSigmaFrequencyZeroCrossingLinearInterp(double x)         {fFreqSigZC[1]         = x;}  
      void SetSigmaFrequencyZeroCrossingLeastSquares(double x)         {fFreqSigZC[2]         = x;}  
      void SetSigmaFrequencyZeroCrossingMidpointPhaseFit(double x)     {fFreqSigZC_ph[0]      = x;}  
      void SetSigmaFrequencyZeroCrossingLinearInterpPhaseFit(double x) {fFreqSigZC_ph[1]      = x;}  
      void SetSigmaFrequencyZeroCrossingLeastSquaresPhaseFit(double x) {fFreqSigZC_ph[2]      = x;}  
      void SetSigmaFrequencyFit(double x)                              {fFreqSigFit           = x;}  
      void SetSigmaFrequencyPhaseFit(double x)                         {fFreqSigPhaseFit      = x;}  
      void SetMeanFieldZeroCrossingMidpoint(double x)                  {fBMeanZC[0]           = x;}  
      void SetMeanFieldZeroCrossingLinearInterp(double x)              {fBMeanZC[1]           = x;}  
      void SetMeanFieldZeroCrossingLeastSquares(double x)              {fBMeanZC[2]           = x;}  
      void SetMeanFieldZeroCrossingMidpointPhaseFit(double x)          {fBMeanZC_ph[0]        = x;}  
      void SetMeanFieldZeroCrossingLinearInterpPhaseFit(double x)      {fBMeanZC_ph[1]        = x;}  
      void SetMeanFieldZeroCrossingLeastSquaresPhaseFit(double x)      {fBMeanZC_ph[2]        = x;}  
      void SetMeanFieldFit(double x)                                   {fBMeanFit             = x;}  
      void SetMeanFieldPhaseFit(double x)                              {fBMeanPhaseFit        = x;}  
      void SetSigmaFieldZeroCrossingMidpoint(double x)                 {fBSigZC[0]            = x;}  
      void SetSigmaFieldZeroCrossingLinearInterp(double x)             {fBSigZC[1]            = x;}  
      void SetSigmaFieldZeroCrossingLeastSquares(double x)             {fBSigZC[2]            = x;}  
      void SetSigmaFieldZeroCrossingMidpointPhaseFit(double x)         {fBSigZC_ph[0]         = x;}  
      void SetSigmaFieldZeroCrossingLinearInterpPhaseFit(double x)     {fBSigZC_ph[1]         = x;}  
      void SetSigmaFieldZeroCrossingLeastSquaresPhaseFit(double x)     {fBSigZC_ph[2]         = x;}  
      void SetSigmaFieldFit(double x)                                  {fBSigFit              = x;}  
      void SetSigmaFieldPhaseFit(double x)                             {fBSigPhaseFit         = x;}  
      void SetMeanNumZeroCrossings(int x)                              {fMeanNumZeroCrossings = x;} 
      void SetMeanAmplitude(double x)                                  {fMeanAmpl             = x;}  
      void SetMeanNoiseRMS(double x)                                   {fMeanNoiseRMS         = x;}  
      void SetMeanNumCycles(double x)                                  {fMeanNumCycles        = x;}  
      void SetMeanSignalToNoiseRatio(double x)                         {fMeanSNR              = x;}  
      void SetSigmaAmplitude(double x)                                 {fSigAmpl              = x;}  
      void SetSigmaNoiseRMS(double x)                                  {fSigNoiseRMS          = x;}  
      void SetSigmaNumCycles(double x)                                 {fSigNumCycles         = x;}  
      void SetSigmaSignalToNoiseRatio(double x)                        {fSigSNR               = x;} 
      void SetMeanT2Time(double x)                                     {fMeanT2               = x;} 
      void SetSigmaT2Time(double x)                                    {fSigT2                = x;} 
      
      // data from a specific pulse  
      int GetPulseNumZeroCrossings(int i)                             const {return fPulse[i]->GetNumZeroCrossings();                          }                     
      int GetPulseNumber(int i)                                       const {return fPulse[i]->GetPulseNumber();                               }
      int GetPulseChannelNumber(int i)                                const {return fPulse[i]->GetChannelNumber();                             } 
 
      double GetPulseFrequencyZeroCrossingMidpoint(int i)             const {return fPulse[i]->GetFrequencyZeroCrossingMidpoint();             }   
      double GetPulseFrequencyZeroCrossingLinearInterp(int i)         const {return fPulse[i]->GetFrequencyZeroCrossingLinearInterp();         }   
      double GetPulseFrequencyZeroCrossingLeastSquares(int i)         const {return fPulse[i]->GetFrequencyZeroCrossingLeastSquares();         }   
      double GetPulseFrequencyZeroCrossingMidpointPhaseFit(int i)     const {return fPulse[i]->GetFrequencyZeroCrossingMidpointPhaseFit();     }   
      double GetPulseFrequencyZeroCrossingLinearInterpPhaseFit(int i) const {return fPulse[i]->GetFrequencyZeroCrossingLinearInterpPhaseFit(); }   
      double GetPulseFrequencyZeroCrossingLeastSquaresPhaseFit(int i) const {return fPulse[i]->GetFrequencyZeroCrossingLeastSquaresPhaseFit(); }   
      double GetPulseFrequencyFit(int i)                              const {return fPulse[i]->GetFrequencyFit();                              }   
      double GetPulseFrequencyPhaseFit(int i)                         const {return fPulse[i]->GetFrequencyPhaseFit();                         }   
      double GetPulseFieldZeroCrossingMidpoint(int i)                 const {return fPulse[i]->GetFieldZeroCrossingMidpoint();                 }   
      double GetPulseFieldZeroCrossingLinearInterp(int i)             const {return fPulse[i]->GetFieldZeroCrossingLinearInterp();             }   
      double GetPulseFieldZeroCrossingLeastSquares(int i)             const {return fPulse[i]->GetFieldZeroCrossingLeastSquares();             }   
      double GetPulseFieldZeroCrossingMidpointPhaseFit(int i)         const {return fPulse[i]->GetFieldZeroCrossingMidpointPhaseFit();         }   
      double GetPulseFieldZeroCrossingLinearInterpPhaseFit(int i)     const {return fPulse[i]->GetFieldZeroCrossingLinearInterpPhaseFit();     }   
      double GetPulseFieldZeroCrossingLeastSquaresPhaseFit(int i)     const {return fPulse[i]->GetFieldZeroCrossingLeastSquaresPhaseFit();     }   
      double GetPulseFieldFit(int i)                                  const {return fPulse[i]->GetFieldFit();                                  }   
      double GetPulseFieldPhaseFit(int i)                             const {return fPulse[i]->GetFieldPhaseFit();                             }   
      double GetPulseAmplitude(int i)                                 const {return fPulse[i]->GetAmplitude();                                 }   
      double GetPulseNoiseRMS(int i)                                  const {return fPulse[i]->GetNoiseRMS();                                  }   
      double GetPulseSignalToNoiseRatio(int i)                        const {return fPulse[i]->GetSignalToNoiseRatio();                        }   
      double GetPulseNumCycles(int i)                                 const {return fPulse[i]->GetNumCycles();                                 }  
      double GetPulseT2Time(int i)                                    const {return fPulse[i]->GetT2Time();                                    }
      double GetPulseTemperature(int i)                               const {return fPulse[i]->GetTemperature();                               } 
      double GetPulseLOFrequency(int i)                               const {return fPulse[i]->GetLOFrequency();                               } 
      double GetPulsePi2Frequency(int i)                              const {return fPulse[i]->GetPi2Frequency();                              }

      unsigned long long GetPulseTimeStamp(int i)                     const {return fPulse[i]->GetTimeStamp();                                 }

      // data for a set of pulses (run) 
      int GetRunNumber()                                              const {return fRunNumber;} 
      int GetNumPulses()                                              const {return fNumPulses;}  
      int GetMeanNumZeroCrossings()                                   const {return fMeanNumZeroCrossings;} 

      double GetFrequencyMeanZeroCrossingMidpoint()                   const {return fFreqMeanZC[0];    }  
      double GetFrequencyMeanZeroCrossingLinearInterp()               const {return fFreqMeanZC[1];    }  
      double GetFrequencyMeanZeroCrossingLeastSquares()               const {return fFreqMeanZC[2];    }  
      double GetFrequencySigmaZeroCrossingMidpoint()                  const {return fFreqSigZC[0];     }  
      double GetFrequencySigmaZeroCrossingLinearInterp()              const {return fFreqSigZC[1];     }  
      double GetFrequencySigmaZeroCrossingLeastSquares()              const {return fFreqSigZC[2];     } 
 
      double GetFrequencyMeanZeroCrossingMidpointPhaseFit()           const {return fFreqMeanZC_ph[0]; }    
      double GetFrequencyMeanZeroCrossingLinearInterpPhaseFit()       const {return fFreqMeanZC_ph[1]; }  
      double GetFrequencyMeanZeroCrossingLeastSquaresPhaseFit()       const {return fFreqMeanZC_ph[2]; }  
      double GetFrequencySigmaZeroCrossingMidpointPhaseFit()          const {return fFreqSigZC_ph[0];  }  
      double GetFrequencySigmaZeroCrossingLinearInterpPhaseFit()      const {return fFreqSigZC_ph[1];  }  
      double GetFrequencySigmaZeroCrossingLeastSquaresPhaseFit()      const {return fFreqSigZC_ph[2];  }  

      double GetFrequencyMeanFit()                                    const {return fFreqMeanFit;      } 
      double GetFrequencySigmaFit()                                   const {return fFreqSigFit;       } 
      double GetFrequencyMeanPhaseFit()                               const {return fFreqMeanPhaseFit; } 
      double GetFrequencySigmaPhaseFit()                              const {return fFreqSigPhaseFit;  } 

      double GetFieldMeanZeroCrossingMidpoint()                       const {return fBMeanZC[0];       }  
      double GetFieldMeanZeroCrossingLinearInterp()                   const {return fBMeanZC[1];       }  
      double GetFieldMeanZeroCrossingLeastSquares()                   const {return fBMeanZC[2];       }  
      double GetFieldSigmaZeroCrossingMidpoint()                      const {return fBSigZC[0];        }  
      double GetFieldSigmaZeroCrossingLinearInterp()                  const {return fBSigZC[1];        }  
      double GetFieldSigmaZeroCrossingLeastSquares()                  const {return fBSigZC[2];        } 

      double GetFieldMeanZeroCrossingMidpointPhaseFit()               const {return fBMeanZC_ph[0];    }  
      double GetFieldMeanZeroCrossingLinearInterpPhaseFit()           const {return fBMeanZC_ph[1];    }  
      double GetFieldMeanZeroCrossingLeastSquaresPhaseFit()           const {return fBMeanZC_ph[2];    }  
      double GetFieldSigmaZeroCrossingMidpointPhaseFit()              const {return fBSigZC_ph[0];     }  
      double GetFieldSigmaZeroCrossingLinearInterpPhaseFit()          const {return fBSigZC_ph[1];     }  
      double GetFieldSigmaZeroCrossingLeastSquaresPhaseFit()          const {return fBSigZC_ph[2];     }  
 
      double GetFieldMeanFit()                                        const {return fBMeanFit;         } 
      double GetFieldSigmaFit()                                       const {return fBSigFit;          } 
      double GetFieldMeanPhaseFit()                                   const {return fBMeanPhaseFit;    } 
      double GetFieldSigmaPhaseFit()                                  const {return fBSigPhaseFit;     }
 
      double GetMeanAmplitude()                                       const {return fMeanAmpl;         }  
      double GetMeanNoiseRMS()                                        const {return fMeanNoiseRMS;     }  
      double GetMeanNumCycles()                                       const {return fMeanNumCycles;    }  
      double GetMeanSignalToNoiseRatio()                              const {return fMeanSNR;          }  
      double GetSigmaAmplitude()                                      const {return fSigAmpl;          }  
      double GetSigmaNoiseRMS()                                       const {return fSigNoiseRMS;      }  
      double GetSigmaNumCycles()                                      const {return fSigNumCycles;     }  
      double GetSigmaSignalToNoiseRatio()                             const {return fSigSNR;           } 

      double GetMeanT2Time()                                          const {return fMeanT2;           } 
      double GetSigmaT2Time()                                         const {return fSigT2;            } 

};

#endif 
