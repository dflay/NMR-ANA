// main program 

#include <iostream> 
#include <cstdlib> 
#include <string>

#include "NMRPulse.h"
#include "NMRPulseAnalyzed.h"
#include "NMRRun.h"
#include "NMRFileManager.h"
#include "NMRAnalysis.h"

int main(){

   const char *inpath   = "./input/parameters.dat"; 
   const char *run_list = "./input/runlist.dat";  

   NMRFileManager *FM = new NMRFileManager(); 
   FM->GetInputParameters(inpath);
   FM->InputManager->GetRunList(run_list);  
   FM->InputManager->Print();             
   FM->InputManager->PrintRunList();  
   FM->InitInputDirectory();

   int NPulses     = FM->InputManager->GetNumPulses();       // will be zero upon starting
   int Verbosity   = FM->InputManager->GetVerbosity(); 
   const int NRUNS = FM->InputManager->GetNumberOfRuns();  
   
   int RunList[NRUNS]; 
   for(int i=0;i<NRUNS;i++) RunList[i] = FM->InputManager->GetRun(i);  
 
   NMRPulse *aPulse            = new NMRPulse(1,1); 
   NMRPulseAnalyzed *aPulseAna = new NMRPulseAnalyzed(1,1); 

   aPulse->SetVerbosity(Verbosity); 
   aPulseAna->SetVerbosity(Verbosity); 

   NMRAnalysis *myAna = new NMRAnalysis();
   myAna->SetFileManager(FM);

   NMRRun *aRun = new NMRRun(1);                      // initialize to 1 pulse 
   aRun->SetVerbosity(Verbosity);  
 
   int run_num=0; 
   for(int i=0;i<NRUNS;i++){
      run_num = RunList[i]; 
      if( FM->RunExists(run_num) ) FM->DeleteRun(run_num);  // delete old data if necessary 
      FM->InputManager->ReadRunSummary(run_num);      // get details of the run
      FM->InputManager->PrintRunSummary();            // show new run information  
      FM->InitOutputDirectory();                      // initiaize output directories  
      myAna->UpdateFileManager(FM);                   // update the FileManager
      myAna->UpdateAnalysis();                        // initialize the analysis based on the run 
      NPulses = FM->InputManager->GetNumPulses();     // update the number of pulses  
      aRun->SetRunNumber(run_num);                    // set the run number  
      aRun->SetNumPulses(NPulses);                    // set the number of pulses 
      // loop over pulses 
      for(int j=1;j<=NPulses;j++){
         aPulse->SetPulseNumber(j);                   // minimal initialization of the pulse 
         FM->Load(run_num,j,aPulse);                  // load data 
	 // FM->PrintSignalToFile(run_num,j,aPulse);     // diagnostic testing  
         myAna->CalculateFrequency(aPulse,aPulseAna); // compute frequencies, add to analyzed pulse   
         myAna->CalculateMagneticField(aPulseAna);    // compute magnetic field values    
         if(Verbosity>4) aPulseAna->Print(); 
         aRun->AddNMRPulse(aPulseAna);                // add analyzed pulse to the run  
         aPulse->ClearData();                         // set up for next pulse  
         aPulseAna->ClearData();                      // set up for next pulse 
      }
      myAna->CalculateStatistics(aRun);               // calculate statistics on the run (mean, std dev, etc) 
      if(Verbosity>4) aRun->PrintPulseData();         // print data for all pulses to the screen   
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
