# CHANGELOG 

## 11/30/15, David Flay

   - Removed redundant index variable in NMRMath::CountZeroCrossings (use cntr only now). 

## 11/22/15, David Flay

   - Changed all remaining vectors in NMRMath, NMRFileManager and NMRZeroCrossing to arrays.   

## 10/29/15, David Flay

   - Changed the way the NMRInputManager is used in NMRFileManager; there are now no private
     data members for the date or ADC type in the NMRFileManager; these are only accessed via
     the NMRInputManager; this will keep things cleaner in the code. 

   - Started work on tracking down the memory leak -- see the TODO.  With respect to this,
     the Clone() method was added to NMRFileManager (and NMRInputManager) so that the NMRZeroCrossing 
     and NMRAnalysis classes can have their own copies not tied to the same memory address 
     as the original instance in main().  

## 10/27/15, David Flay

   - Added the class NMRInputManager, a public member of NMRFileManager; this allows for 
     clear organization of the input parameters and an easy way to access them. Thus, setting
     the FileManager in various classes allows for a clean way to propagate the input parameters
     around the code. 
     - Updated NMRAnalysis to have its own FileManager, and a new function to take advantage
       of NMRInputManager (called InitializeAnalysis)  

## 10/26/15, David Flay
 
   - Added the function GetInputParameters() to the FileManager class; we now read in 
     input parameters from files, not hard-coded in the main function.  This functionality 
     needs to be fully propagated across the code (mostly in main, but also in the ZeroCrossing
     class). 

## 10/22/15, David Flay

   - Changed the way the RMS noise is computed; it is now computed after the 1st order 
     offset correction; the maximum amplitude is computed after the offset corrections. 
     See Thoughts section of the TODO list about such calculations.  

## 10/21/15, David Flay 

   - Added error-handling for offset corrections.

## 10/19/15, David Flay

   - Added the Makefile. 

## 10/13/15, David Flay

   - Updated the NMRFileManager functions for offset corrections; these functions are now 
     consistent up through order 5; the problem was in the way we were cutting the data 
     upon first pass (see beginning of the Load method).  We were including the cutoff 
     bounds.  They should be excluded here. 

## 10/12/15, David Flay

   - Updated the NMRFileManager functions corresponding to offset corrections; the offset
     correction now works up to order 2; order 3 is consistent with the old code (~/NMR/ana/src/LoadFuncs.C), 
     up until the 7th decimal place for a test run (8/6/15, run 13, pulse 1).  The fix to 
     get order 2 working was that we were using the full pulse for the offset correction,
     not the amount of data desired in the zero crossing analysis.  Corrections are of course
     applied to the full data set as they are determined. WARNING: This will probably yield
     a funky looking signal, especially towards the end of the pulse when using offset corrections
     that are linear in time.  

## 10/2/15, David Flay

   - Added the NMRFourierTransform class.  This allows the user to compute the Fourier 
     transform of a function stored in an array.  

## 9/30/15, David Flay 

   - Moved the method CountZeroCrossings and associated methods to the NMRMath namespace. 
     This was done so that we can use these functions when computing the voltage offset 
     corrections on data in the FileManager. Using the CountZeroCrossings function in the
     NMRMath namespace works as expected. 

   - Implemented methods to compute higher-order voltage offset corrections; everything 
     compiles, but it does not work past first order.  This needs work. Can be sped up 
     by using arrays for zero crossing data as opposed to vectors.   

## 9/11/15, David Flay

   - Added verbosity settings to all current classes. 

## 9/10/15, David Flay

   - Added a method to NMRFileManager to retrieve the time stamp associated with each pulse; 
     this function is called when data is loaded into NMRPulse via the Load() function. 

   - Changed the way the step size and number of points used in a fit in the NMRZeroCrossing 
     class are set; the user now sets the sampling frequency and the expected frequency. 
     After this, the user has to call the method UpdateParameters() from the NMRZeroCrossing 
     class to update the step size and number of points.  This makes it easy to analyze 
     multiple runs with different expected frequencies.    

## 9/9/15, David Flay 

   - Added methods to NMRFileManager to print a number of output files, storing mean and 
     std. dev. values for amplitude, RMS noise, frequencies, etc.

   - Updated the README 

## 9/8/15, David Flay

   - Added a new method to NMRFileManager that prints all results of an analysis for a run 
     to a file; the file includes all frequency results, amplitude, RMS noise, etc. for each pulse.  

## 9/5/15, David Flay

   - Added methods to the NMRFileManager and NMRZeroCrossing to print diagnostic data to files.

   - Changed the way input and output directory paths are set in the NMRFileManager; the
     user now sets the date and run number, and the directories can be set using InitInputDirectory()
     or InitOutputDirectory(); this way, an analysis for multiple runs may be realized where
     the user can update the run number when looping over runs.  The user would need to call
     InitOutputDirectory() each time the run number is changed.     

## 9/4/15, David Flay 
 
   - Added a statistical analysis method to NMRAnalysis; the mean and standard deviation
     of most quantities is computed for a run (NMRRun).  Also added a print method to NMRRun
     to print such results to the screen.     

## 9/3/15, David Flay

   - Added better setter/getter methods to NMRPulse, NMRPulseAnalyzed and NMRRun

   - NMRAnalysis now transfers frequency analysis results and other metadata to 
     NMRPulseAnalyzed 

## 9/2/15, David Flay

   - Tested the code for looping over a number of pulses; everything works as expected

## 9/1/15, David Flay

   - Over the past week, the NMRZeroCrossing, NMRRun, NMRAnalysis classes have been 
     implemented.   

## 8/26/15, David Flay
 
   - Updates to NMRPulseAnalyzed and NMRRun corresponding to getter/setter methods; 
     NMRPulse, NMRPulseAnalyzed and NMRRun all function as expected. 

## 8/25/15, David Flay 

   - Added the NMRPulseAnalyzed class; derives from NMRPulse.  

   - CHANGELOG and TODO lists created
