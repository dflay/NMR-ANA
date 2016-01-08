## Table of Contents 

   1. Introduction 
   2. C++ Classes 
   3. Running an Analysis 
   4. Authors and Contact Information  

## 1. Introduction

   This code carries out the data (frequency) analysis for NMR signals via a C++ framework. 
   The analysis is realized by the use of a number of classes for specific tasks; the time 
   and voltage data of a given NMR pulse is organized into the NMRPulse (and derived) class(es), 
   while the multiple analysis options have their own specialized classes. 

## 2. C++ Classes and Namespaces 

   - NMRPulse:            A basic class containing pulse information: time and voltage data are stored 
                          in arrays; additionally, variables exist for the maximum amplitude, RMS noise and 
                          the timestamp associated with when the pulse was acquired.  

   - NMRPulseAnalyzed:    An analyzed pulse; the frequency from multiple analyses can be stored to this object; it 
                          derives from NMRPulse.  

   - NMRRun:              A class to store a collection of pulses, along with statistics about those pulses;
                          for instance, the mean and standard deviations of the various data like frequencies, 
                          amplitudes, noise, etc. 

   - NMRZeroCrossing:     A frequency analysis class: counts zero crossings of an input pulse and can return 
                          up to three different types of results: midpoint method, linear interpolation and least squares fitting.  

   - NMRAnalysis:         A generic analysis class which has objects of analysis classes (like NMRZeroCrossing) as data members.
                          Carries out the specified analyses on a given pulse.     

   - NMRFileManager:      This class handles the input and output of all files; it loads data into NMRPulse and also prints 
                          frequency results to output files.

   - NMRInputManager:     A public member of NMRFileManager; stores all input parameter information (from `./input/parameters.dat`) 
 
   - NMRFourierTransform: A Fourier transform class; given an array of voltage data, will output the corresponding frequency
                          spectrum; the output is normalized such that the power spectrum is in Volts.  

   - NMRMath:             A namespace that has basic mathematical functions like obtaining the mean or standard deviation 
                          of an array and other more complicated functions like least squares fitting algorithms. 

   - NMRUtility:          A namespace for miscellaneous functions. 

## 3. Running an Analysis  

### Compilation 

   To compile the code, in a terminal type: `make`.  To run the program, type `./nmr_ana`.

### Main Program and Command Line  

   See `./src/main.cpp` for an example of code utilizing the classes mentioned in chapter 2. The user needs to provide a 
   number of things to the classes, listed below:

   - The run number(s) 
   - The date  
   - Which analysis method to use, whether or not to use a time range, along with the desired start and end times of 
     said time range. 
   - The verbosity level, which controls how much information is printed to screen during an analysis. 
   - The offset order, which determines what offset correction to apply to the data upon loading from input files. 

   All of these parameters are listed in the parameter input file, located in `./input/parameters.dat`. 
   The user may also run an analysis using the graphical user interface (see next subsection).  

### Graphical User Interface

   A graphical user interface (GUI) has been developed.  To run the GUI, run `python gui.py`.  Fill in the input fields
   to the desired values.  

   The **Run Range** field is where the user sets the runs to analyze.  Enter the desired run numbers separated by 
   commas; if you want to do all runs between (and including) 20 and 30, for instance, write `20-30`.  The user can
   also do *combinations* of these delimitations, as follows: 

   > 1,4,5-10,17

   This will tell the C++ code to analyze runs 1, 4, 5, 6, 7, 8, 9, 10 and 17.    

   Under the **Analysis Options** section, there are check boxes for **Zero Crossing**, **Time Fit** and 
   **Phase Fit**, each of which corresponds to a different analysis method.  Check the analysis type you 
   would like the code to perform on the data.  The user may choose to use all options.  The options are
   described as follows:

   - Zero Crossing: Count zero crossings to determine the frequency
   - Time Fit: Fit the data as a function of time to determine the frequency
   - Phase Fit: Use a Hilbert Transform to determine the phase of the signal as a function of time 
     and fit the phase as a function of time to obtain the frequency.  

   --- 

   The **Offset Correction Order** field corresponds to the voltage offset correction to be applied to the 
   data.  The pull-down menu gives the options of 0--4.  The values are as follows:

   - 0: No correction
   - 1: Subtract an average noise level (found from the last millisecond of the data) 
   - 2: Recursive algorithm to find the proper constant voltage offset to subtract from the data based on the time range 
        indicated (**Start Time** and **End Time** fields)
   - 3: Similar to option 2, but determines the final offset by computing the voltage offset as a function of time
        and fits these offset points to a line 
   - 4: This option does options 2 and 3, and then does option 2 once more

   ---
 
   Option 2 is the proper setting to use for real data; option 3 and 4 are best suited for simulated data.  

   The **Verbosity** field is used to tell the program how much information should be printed to the screen
   when running; a higher value indicates more text will be printed to the terminal.  

## 4. Adding Analysis Classes 

   To add an analysis class to the code, the user should integrate their class into the NMRAnalysis class;
   see NMRZeroCrossing for an example.  Also, if there are specific inputs required for your analysis, 
   be sure to integrate them into the NMRFileManager and/or the NMRInputManager appropriately.   

## 5. Authors and Contact Information 

   Authors:     David Flay and Zac Meadows  
   Affiliation: UMass Amherst   
   Contact:     David (flay@umass.edu) 

