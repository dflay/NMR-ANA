#ifndef NMRPULSEANALYZED_H
#define NMRPULSEANALYZED_H 

// an analyzed NMR pulse; derives from NMRPulse  

#include <cstdlib>
#include <cstdio>  
#include <iostream> 
#include "NMRPulse.h"

class NMRPulseAnalyzed: public NMRPulse{

   private: 
      int fNumZeroCrossings;
      double *fFREQ_zc; 
      double fFREQ_fit,fFREQ_ph;
      double fNumCycles;

   public:
      // constructor and destructor 
      NMRPulseAnalyzed(int PulseNumber=0,int NPTS=1);
      ~NMRPulseAnalyzed();

      // copy constructors 
      NMRPulseAnalyzed(const NMRPulseAnalyzed &aPulse);         
      NMRPulseAnalyzed(const NMRPulseAnalyzed *aPulse);         

      // overload assignment operator  
      NMRPulseAnalyzed& operator=(const NMRPulseAnalyzed &aPulse);  
      NMRPulseAnalyzed* operator=(const NMRPulseAnalyzed *aPulse); 

      void Print(); 
      void ClearData(); 
      void SetNumZeroCrossings(int zc)                    {fNumZeroCrossings = zc;} 
      void SetFrequencyZeroCrossingMidpoint(double f)     {fFREQ_zc[0]       = f;} 
      void SetFrequencyZeroCrossingLinearInterp(double f) {fFREQ_zc[1]       = f;} 
      void SetFrequencyZeroCrossingLeastSquares(double f) {fFREQ_zc[2]       = f;} 
      void SetFrequencyFit(double f)                      {fFREQ_fit         = f;} 
      void SetFrequencyPhaseFit(double f)                 {fFREQ_ph          = f;} 
      void SetNumCycles(double nc)                        {fNumCycles        = nc;} 

      int GetNumZeroCrossings()                     const {return fNumZeroCrossings;} 

      double GetFrequencyZeroCrossingMidpoint()     const {return fFREQ_zc[0];}  
      double GetFrequencyZeroCrossingLinearInterp() const {return fFREQ_zc[1];}  
      double GetFrequencyZeroCrossingLeastSquares() const {return fFREQ_zc[2];}  
      double GetFrequencyFit()                      const {return fFREQ_fit;}  
      double GetFrequencyPhaseFit()                 const {return fFREQ_ph;}  
      double GetNumCycles()                         const {return fNumCycles;} 

}; 

#endif 
