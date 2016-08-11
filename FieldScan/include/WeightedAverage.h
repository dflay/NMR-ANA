#ifndef WEIGHTEDAVERAGE_H
#define WEIGHTEDAVERAGE_H 

#include <cstdlib> 
#include <iostream> 
#include <vector> 

using namespace std; 

class WeightedAverage{

   private: 
      vector<double> fX,fXErr;
      double fWAvg,fWAvgErr;

   public: 
      WeightedAverage();
      ~WeightedAverage(); 

      void Init(); 
      void Calculate();
      void ClearVectors();
      void SetVectors(vector<double>,vector<double>); 

      double GetResult(){return fWAvg;} 
      double GetResultErr(){return fWAvgErr;} 

}; 

#endif 
