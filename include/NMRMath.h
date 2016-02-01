#ifndef NMRMATHFUNC_H
#define NMRMATHFUNC_H

#include <cstdlib> 
#include <cmath> 
#include <iostream>
#include <vector> 

#include "NMRUtility.h"
#include "NMRPulse.h" 

namespace NMRMath{
   double GetScale(const char *units);
   double GetTimeInSeconds(const int counts,const double ClockFreq);
   double ConvertTimeFromSecondsToUnits(const double time_seconds,const char *units);
   double ConvertTimeFromUnitsToSeconds(const double time_in_units,const char *units);
   double GetTimeInUnits(const int counts,const double ClockFreq,const char *units);
   int GetClockCounts(const double time,const double ClockFreq,const char *units);
   double ConvertToVoltage3302(unsigned short int adc_reading);
   double ConvertToVoltage3316(unsigned short int adc_reading);
   int GetNextPowerOfTwo(int N);
   double GetMean(int N,double v[]);
   double GetMean(std::vector<unsigned short> v);
   double GetMean(std::vector<double> v);
   double GetStandardDeviation(std::vector<double> v);
   double GetStandardDeviation(int N,double v[]);
   double GetVariance(int N,double v[]);
   double GetVariance(std::vector<double> v);
   double GetCovariance(int N,double x[],double y[]);
   double GetCovariance(std::vector<double> x,std::vector<double> y);
   double GetStandardDeviationOfTheMean(int N,double v[]);
   double GetStandardDeviationOfTheMean(std::vector<double> v);
   double GetRMS(int N,double v[]);
   double GetRMS(std::vector<double> v);
   double LinearInterpolationForY(double x,double x0,double y0,double x1,double y1);
   double LinearInterpolationForX(double y,double x0,double y0,double x1,double y1);
   int LeastSquaresFitting(int N,double x[],double y[],double &a,double &b,double &r);
   int LeastSquaresFitting(std::vector<double> x,std::vector<double> y,double &a,double &b,double &r);
   int StoreData(int verbosity,int i,int NPTS,NMRPulse *aPulse,double *X,double *Y,double *EY);
   void ClearAnaArrays(int N,double *X,double *Y,double *EY);
   double GetTimeOfCrossing(int verbosity,int method,int NPTSUseable,double X[],double Y[],double EY[], 
                            double t_current,double v_current,double v_current_err,
                            double t_next   ,double v_next   ,double v_next_err);
   int CountZeroCrossings(int verbosity,int method,int NPTS,int step,
                           bool UseTimeRange,double tMin,double tMax,
                           NMRPulse *aPulse,
                           double *X,double *Y,double *EY,
                           int *NCrossing,int *CrossingIndex,double *tCross,double *vCross); 
   
}

#endif 
