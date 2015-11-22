/// Test out the new analysis classes

#include <iostream> 
#include <cstdlib> 
#include <string>

#include "NMRPulse.h"
#include "NMRPulseAnalyzed.h"
#include "NMRRun.h"
// #include "NMRZeroCrossing.h"
#include "NMRFileManager.h"
#include "NMRAnalysis.h"
// #include "NMRFourierTransform.h"
// #include "NMRInputManager.h"

int main(){

   const char *inpath = "./input/parameters.dat"; 

   NMRFileManager *FM = new NMRFileManager(); 
   FM->GetInputParameters(inpath); 
   FM->InitInputDirectory();

   int NPulses        = FM->InputManager->GetNumPulses();
   int Verbosity      = FM->InputManager->GetVerbosity(); 
   int StartRunNumber = FM->InputManager->GetStartRunNumber(); 
   int EndRunNumber   = FM->InputManager->GetEndRunNumber(); 
 
   NMRPulse *aPulse            = new NMRPulse(1,1); 
   NMRPulseAnalyzed *aPulseAna = new NMRPulseAnalyzed(1,1); 

   aPulse->SetVerbosity(Verbosity); 
   aPulseAna->SetVerbosity(Verbosity); 

   NMRAnalysis *myAna = new NMRAnalysis();
   myAna->SetFileManager(FM);
   myAna->InitializeAnalysis();  

   NMRRun *aRun = new NMRRun(NPulses);
   aRun->SetVerbosity(Verbosity);  

   for(int i=StartRunNumber;i<=EndRunNumber;i++){
      FM->SetRunNumber(i);
      FM->InitOutputDirectory(); 
      myAna->SetupForRun(i); 
      aRun->SetRunNumber(i);
      // try a loop over pulses 
      for(int j=1;j<=NPulses;j++){
         // minimal initialization of the pulse 
         aPulse->SetPulseNumber(j); 
         // load data 
         FM->Load(i,j,aPulse);
         // compute frequencies, add to analyzed pulse   
         myAna->CalculateFrequency(aPulse,aPulseAna); 
         // print results to screen 
         // aPulseAna->Print(); 
         // set up for next pulse 
         aRun->AddNMRPulse(aPulseAna); 
         aPulse->ClearData();
         aPulseAna->ClearData();
      }
      myAna->CalculateStatistics(aRun); // calculate statistics on the run (mean, std dev, etc) 
      // aRun->PrintPulseData();        // print data for all pulses to the screen   
      aRun->PrintStatistics();          // print data for statistics of a run to the screen 
      FM->PrintResultsToFile(aRun);     // print analysis results for pulses of a run to file  
      aRun->ClearData();                // clear run data 
   }

   // delete objects (order shouldn't matter)  
   delete aPulse;
   delete aPulseAna;
   delete myAna;                          // FIXME: this causes a segfault (when everything is commented out in the loops above)  
   delete aRun;
   delete FM;  

   return 0;

}
