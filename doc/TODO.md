# To Do

## General 

   - The change to arrays did not change the time for processing all that much; additionally, 
     we are in disagreement with the original code (see ~/NMR/new_ana/ files) by ~ 20 mHz or so.  

   - Segmentation fault problems
     - Upon testing, we have a segfault if we turn off all function calls, and just loop 
       over nothing, and delete the objects at the end; in particular, the NMRAnalysis 
       class is causing the problem.   
   
   - When using input parameter info, we should only access it through the NMRInputManager; 
     this should simplify a lot of the code, or at least cut down on making private data members
     for the date, for instance.  

   - Add capability to do different number of pulses for a given run (?)   

   - Improve error handling (?) 

## Classes to Complete or Add: 

   - NMRMath (namespace)  
     - Add corrected standard deviation, variance, etc. (N -> N-1) 

   - NMRAnalysis 
     - NMRPhase
     - NMRFit

   - NMRPlotter (namespace) 
     - Maybe?  It would include time-domain and frequency-domain plotting capabilities... 
     - Would be useful for once we integrate everything into the GUI 

## Ideas and Thoughts 

   - [Important]: RMS noise calculation was not consistent with old code (fixed as of 10/22/15).  
     - Found the source of the problem: applying the offset corrections (higher orders)
       shifts the baseline signal to be much larger than expected.  This is probably
       because offset corrections are determined by looking at the data to be used during
       zero crossing analysis (that is, 0 < t < 5 ms typically).  Perhaps it is best 
       to get the RMS noise level after either the first or second order correction;
       that is, BEFORE the linear offset correction (3rd order)?  It seems like it is fairer 
       to obtain the RMS noise after the 1st order correction.  Maybe we need to think about 
       this some more?   

   - Should we make all classes derive from an ABC that has members like verbosity, debugging, etc.? 

   - Perhaps make NMRFourierTransform a private data member of NMRPulse?  That way, one can
     easily obtain the FFT of a pulse... 

   - GUI functionality 
     - If we do this, we would want the classes to work in ROOT: do not need to compile,
       can build in compatability for TH1F, TGraph, etc.  
