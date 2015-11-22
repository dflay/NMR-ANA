#ifndef NMRANALYSIS_H
#define NMRANALYSIS_H 

// generic NMR analysis class

#include <cstdlib> 
#include <iostream> 
#include "NMRMath.h"
#include "NMRRun.h"
#include "NMRPulse.h"
#include "NMRPulseAnalyzed.h"
#include "NMRZeroCrossing.h"
#include "NMRFileManager.h"

/// To do
/// 1. Add analysis objects for fitting and phase fitting 

class NMRAnalysis{

   private:
      bool fUseZeroCrossing; 
      bool fUseFit;  
      bool fUsePhaseFit; 

      int fVerbosity; 
   
      NMRFileManager *fFileManager; 

      void PrintZeroCrossingDataToFile(int Type); 

   public: 
      NMRAnalysis();
      ~NMRAnalysis(); 

      // analysis objects 
      NMRZeroCrossing *ZeroCrossing; 

      void SetFileManager(NMRFileManager *fm){ 
         fFileManager = new NMRFileManager(fm); 
         ZeroCrossing->SetFileManager(fm); 
      } 

      void SetVerbosity(int v){
         fVerbosity = v;
         ZeroCrossing->SetVerbosity(v); 
      } 

      void InitializeAnalysis(); 

      void SetupForRun(int run){
         ZeroCrossing->SetupForRun(run); 
      }
 
      void UseFit(bool v=true){ 
         std::cout << "[NMRAnalysis]: Will use fitting method." << std::endl;
         fUseFit = v;
      } 
      void UsePhaseFit(bool v=true){ 
         std::cout << "[NMRAnalysis]: Will use phase fitting method." << std::endl;
         fUsePhaseFit = v;
      } 
      void UseZeroCrossing(bool v=true){ 
         std::cout << "[NMRAnalysis]: Will use zero crossing method." << std::endl;
         fUseZeroCrossing = v;
      } 

      void CalculateFrequency(NMRPulse *aPulse,NMRPulseAnalyzed *aPulseAnalyzed); 
      void CalculateStatistics(NMRRun *aRun);   


}; 

#endif 
