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

   See `./src/main.cpp` for an example of code utilizing the classes mentioned in chapter 2. The user needs to provide a 
   number of things to the classes, listed below:

   - The run number and the number of pulses associated with the run. 
   - The Struck SIS ADC ID number (for converting ADC counts to voltage), the date and sampling frequency
   - Which analysis method to use, whether or not to use a time range, along with the desired start and end times of 
     said time range. 
   - The verbosity level, which controls how much information is printed to screen during an analysis.
   - The offset order, which determines what offset correction to apply to the data upon loading from input files.  

   All of these parameters are listed in the parameter input file, located in `./input/parameters.dat`.  

   To compile the code, in a terminal type: `make`.  To run the program, type `./nmr_ana`.

## 4. Adding Analysis Classes 

   To add an analysis class to the code, the user should integrate their class into the NMRAnalysis class;
   see NMRZeroCrossing for an example.  

## 5. Authors and Contact Information 

   Authors:     David Flay and Zac Meadows  
   Affiliation: UMass Amherst   
   Contact:     David, flay@umass.edu 




