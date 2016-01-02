/// Test out the new analysis classes

#include <iostream> 
#include <cstdlib> 
#include <string>

#include "NMRPulse.h"
#include "NMRPulseAnalyzed.h"
#include "NMRRun.h"
#include "NMRFileManager.h"
#include "NMRAnalysis.h"

int main(){

   const char *inpath = "./input/parameters.dat"; 

   NMRFileManager *FM = new NMRFileManager(); 
   FM->GetInputParameters(inpath); 
   FM->InputManager->Print();              
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
      FM->InputManager->ReadRunSummary(i);            // get details of the run
      FM->InputManager->PrintRunSummary();            // show new run information  
      FM->InitOutputDirectory();                      // initiaize output directories  
      myAna->UpdateFileManager(FM);                   // update the FileManager
      myAna->InitializeAnalysis();                    // initialize the analysis based on the run 
      NPulses = FM->InputManager->GetNumPulses();     // update the number of pulses  
      aRun->SetRunNumber(i);                          // set the run number  
      aRun->SetNumPulses(NPulses);                    // set the number of pulses 
      // try a loop over pulses 
      for(int j=1;j<=NPulses;j++){
         aPulse->SetPulseNumber(j);                   // minimal initialization of the pulse 
         FM->Load(i,j,aPulse);                        // load data 
         myAna->CalculateFrequency(aPulse,aPulseAna); // compute frequencies, add to analyzed pulse   
         // aPulseAna->Print(); 
         aRun->AddNMRPulse(aPulseAna);                // add analyzed pulse to the run  
         aPulse->ClearData();                         // set up for next pulse  
         aPulseAna->ClearData();                      // set up for next pulse 
      }
      myAna->CalculateStatistics(aRun);               // calculate statistics on the run (mean, std dev, etc) 
      // aRun->PrintPulseData();                      // print data for all pulses to the screen   
      aRun->PrintStatistics();                        // print data for statistics of a run to the screen 
      FM->PrintResultsToFile(aRun);                   // print analysis results for pulses of a run to file  
      aRun->ClearData();                              // clear run data 
   }

   // end of runs 
   printf("=================================================================== \n");

   // delete objects (order shouldn't matter)  
   delete aPulse;
   delete aPulseAna;
   delete myAna;                          // FIXME: this causes a segfault (when everything is commented out in the loops above)  
   delete aRun;
   delete FM;  

   return 0;

}
