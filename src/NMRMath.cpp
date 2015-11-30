#include "NMRMath.h"
//______________________________________________________________________________
namespace NMRMath{
   //______________________________________________________________________________
   double GetScale(const char *units){
      double scale=0;
      const char *second      = "s";
      const char *millisecond = "ms";
      const char *microsecond = "us";
      const char *nanosecond  = "ns";
      const char *picosecond  = "ps";
      const char *notdef      = "ND";
      if( NMRUtility::AreEquivStrings(units,second) ){
         scale = 1.0;
      }else if( NMRUtility::AreEquivStrings(units,millisecond) ){
         scale = 1E-3;
      }else if( NMRUtility::AreEquivStrings(units,microsecond) ){
         scale = 1E-6;
      }else if( NMRUtility::AreEquivStrings(units,nanosecond) ){
         scale = 1E-9;
      }else if( NMRUtility::AreEquivStrings(units,picosecond) ){
         scale = 1E-12;
      }else if( NMRUtility::AreEquivStrings(units,notdef) ){
         scale = -1;
      }else{
         std::cout << "[NMRDAQ::GetScale]: Invalid units!  Exiting..." << std::endl;
         exit(1);
      }
      return scale;
   }
   //______________________________________________________________________________
   double GetTimeInSeconds(const int counts,const double ClockFreq){
      // ClockFreq in Hz 
      // time in seconds 
      double counts_f = (double)counts;
      double time     = counts_f/ClockFreq;
      return time;
   }
   //______________________________________________________________________________
   double ConvertTimeFromSecondsToUnits(const double time_seconds,const char *units){
      // time is in seconds
      // output time is in units (e.g., ms, us, ns) 
      double scale         = GetScale(units);
      double time_in_units = time_seconds/scale;
      return time_in_units;
   }
   //______________________________________________________________________________
   double ConvertTimeFromUnitsToSeconds(const double time_in_units,const char *units){
      // time_in_units is in units (e.g., ms, us, ns)
      // output time is in seconds  
      double scale = GetScale(units);
      double time  = time_in_units*scale;
      return time;
   }
   //______________________________________________________________________________
   double GetTimeInUnits(const int counts,const double ClockFreq,const char *units){
      // ClockFreq in Hz 
      // time in units 
      double time_seconds = GetTimeInSeconds(counts,ClockFreq);
      double time_units   = ConvertTimeFromSecondsToUnits(time_seconds,units);
      return time_units;
   }
   //______________________________________________________________________________
   int GetClockCounts(const double time,const double ClockFreq,const char *units){
      double time_seconds = ConvertTimeFromUnitsToSeconds(time,units);
      int counts          = (int)( ClockFreq*time_seconds );
      return counts;
   }
   //______________________________________________________________________________
   double ConvertToVoltage3302(unsigned short int adc_reading){
      // unsigned short int = 16-bit-wide unsigned integer 
      // convert the 16-bit integer to a voltage
      // ADC details 
      // Manufacturer: Struck 
      // Model:        SIS3302 100 MHz 16-bit ADC
      // Input Span:   2 V (-1,..,1 V)  
      // Impedance:    100 Ohms 
      // Input Type:   Differential
      // use a linear fit to ADC counts vs voltage 
      double adc       = (double)adc_reading;
      double p0        = 32599.9;
      double p1        = 30465.9;
      double v         = (adc - p0)/p1;
      return v;
   }
   //______________________________________________________________________________
   double ConvertToVoltage3316(unsigned short int adc_reading){
      // unsigned short int = 16-bit-wide unsigned integer 
      // convert the 16-bit integer to a voltage
      // ADC details 
      // Manufacturer: Struck 
      // Model:        SIS3316 125 MHz 16-bit (or 250 MHz 14-bit) ADC
      // Input Span:   5 V (-2.5,..,2.5 V)  
      // Impedance:    50 Ohms 
      // Input Type:   ?? 
      // use a linear fit to ADC counts vs voltage 
      double adc       = (double)adc_reading;
      double p0        = 32558.5;
      double p1        = 12629.5;
      double v         = (adc - p0)/p1;
      return v;
   }
   //______________________________________________________________________________
   int GetNextPowerOfTwo(int N){
      double arg1 = log( (double)N )/log(2.);
      double arg2 = ceil(arg1);
      double NFT  = pow(2.,arg2);
      int NFFT    = (int)NFT;
      return NFFT;
   }
   //______________________________________________________________________________
   double GetMean(int N,double v[]){
      double sum = 0;
      for(int i=0;i<N;i++){
         sum += v[i];
      }
      double arg  = sum/( (double)N );
      double mean = arg;
      return mean;
   }
   //______________________________________________________________________________
   double GetMean(std::vector<unsigned short> v){
      double sum = 0;
      const int N = v.size();
      for(int i=0;i<N;i++){
         sum += (double)v[i];
      }
      double arg  = sum/( (double)N );
      double mean = arg;
      return mean;
   }
   //______________________________________________________________________________
   double GetMean(std::vector<double> v){
      double sum = 0;
      const int N = v.size();
      for(int i=0;i<N;i++){
         sum += v[i];
      }
      double arg  = sum/( (double)N );
      double mean = arg;
      return mean;
   }
   //______________________________________________________________________________
   double GetStandardDeviation(std::vector<double> v){

      double sum  = 0;
      double mean = GetMean(v);
      const int N = v.size();
      for(int i=0;i<N;i++){
         sum += pow(v[i]-mean,2.);
      }

      double var = sum/( (double)N );
      double sd  = sqrt(var);
      return sd;
   }
   //______________________________________________________________________________
   double GetStandardDeviation(int N,double v[]){

      double sum  = 0;
      double mean = GetMean(N,v);
      for(int i=0;i<N;i++){
         sum += pow(v[i]-mean,2.);
      }

      double var = sum/( (double)N );
      double sd  = sqrt(var);
      return sd;
   }
   //______________________________________________________________________________
   double GetVariance(int N,double v[]){
      double sum  = 0;
      double mean = GetMean(N,v);
      for(int i=0;i<N;i++){
         sum += pow(v[i]-mean,2.);
      }
      double var = sum/( (double) N);
      return var;
   }
   //______________________________________________________________________________
   double GetVariance(std::vector<double> v){
      double sum  = 0;
      double mean = GetMean(v);
      const int N = v.size();
      for(int i=0;i<N;i++){
         sum += pow(v[i]-mean,2.);
      }
      double var = sum/( (double) N);
      return var;
   }
   //______________________________________________________________________________
   double GetCovariance(int N,double x[],double y[]){
      double mean_x = GetMean(N,x);
      double mean_y = GetMean(N,y);
      double sum=0,diff_x=0,diff_y=0;
      for(int i=0;i<N;i++){
         diff_x = x[i]-mean_x;
         diff_y = y[i]-mean_y;
         sum   += diff_x*diff_y;
      }
      double cov = sum/( (double) N);
      return cov;
   }
   //______________________________________________________________________________
   double GetCovariance(std::vector<double> x,std::vector<double> y){
      double mean_x = GetMean(x);
      double mean_y = GetMean(y);
      double sum=0,diff_x=0,diff_y=0;
      const int N = x.size();
      for(int i=0;i<N;i++){
         diff_x = x[i]-mean_x;
         diff_y = y[i]-mean_y;
         sum   += diff_x*diff_y;
      }
      double cov = sum/( (double) N);
      return cov;
   }
   //______________________________________________________________________________
   double GetStandardDeviationOfTheMean(int N,double v[]){
      // get the standard deviation of the mean 
      double sd   = GetStandardDeviation(N,v);
      double sdom = sd/sqrt( (double)N );
      return sdom;
   }
   //______________________________________________________________________________
   double GetStandardDeviationOfTheMean(std::vector<double> v){
      // get the standard deviation of the mean 
      const int N = v.size();
      double sd   = GetStandardDeviation(v);
      double sdom = sd/sqrt( (double)N );
      return sdom;
   }
   //______________________________________________________________________________
   double GetRMS(int N,double v[]){
      double sum_sq = 0;
      for(int i=0;i<N;i++){
         sum_sq += pow(v[i],2.);
      }
      double arg = sum_sq/( (double)N );
      double rms = sqrt(arg);
      return rms;
   }
   //______________________________________________________________________________
   double GetRMS(std::vector<double> v){
      double sum_sq = 0;
      const int N = v.size();
      for(int i=0;i<N;i++){
         sum_sq += pow(v[i],2.);
      }
      double arg = sum_sq/( (double)N );
      double rms = sqrt(arg);
      return rms;
   }
   //______________________________________________________________________________
   double LinearInterpolationForY(double x,double x0,double y0,double x1,double y1){
      double b = (x-x0)/(x1-x0);
      double y = y0 + b*(y1-y0);
      return y;
   }
   //______________________________________________________________________________
   double LinearInterpolationForX(double y,double x0,double y0,double x1,double y1){
      double b = (y-y0)/(y1-y0);
      double x = x0 + b*(x1-x0);
      return x;
   }
   //______________________________________________________________________________
   int LeastSquaresFitting(int N,double x[],double y[],double &a,double &b,double &r){

      // linear regression to find slope b and y-intercept a of 
      // f(x) = a + bx 

      int ret_val=0;
      double num=0,rsq=0;

      double mean_x = GetMean(N,x);
      double mean_y = GetMean(N,y);
      double var_x  = GetVariance(N,x);
      double var_y  = GetVariance(N,y);
      double cov_xy = GetCovariance(N,x,y);

      double ss_xx = ( (double)N )*var_x;
      double ss_yy = ( (double)N )*var_y;
      double ss_xy = ( (double)N )*cov_xy;

      double den = ss_xx*ss_yy;
      if(den==0){
         // singular matrix. can't solve the problem.
         a       = 0;
         b       = 0;
         r       = 0;
         ret_val = 1;
      }else{
         b   = cov_xy/var_x;
         a   = mean_y - b*mean_x;
         num = ss_xy*ss_xy;
         rsq = num/den;
         r   = sqrt(rsq);
      }

      return ret_val;
   }
   //______________________________________________________________________________
   int LeastSquaresFitting(std::vector<double> x,std::vector<double> y,double &a,double &b,double &r){

      // linear regression to find slope b and y-intercept a of 
      // f(x) = a + bx 

      int ret_val=0;
      double num=0,rsq=0;

      int N         = x.size();
      double mean_x = GetMean(x);
      double mean_y = GetMean(y);
      double var_x  = GetVariance(x);
      double var_y  = GetVariance(y);
      double cov_xy = GetCovariance(x,y);

      double ss_xx = ( (double)N )*var_x;
      double ss_yy = ( (double)N )*var_y;
      double ss_xy = ( (double)N )*cov_xy;

      double den = ss_xx*ss_yy;
      if(den==0){
         // singular matrix. can't solve the problem.
         a       = 0;
         b       = 0;
         r       = 0;
         ret_val = 1;
      }else{
         b   = cov_xy/var_x;
         a   = mean_y - b*mean_x;
         num = ss_xy*ss_xy;
         rsq = num/den;
         r   = sqrt(rsq);
      }

      return ret_val;
   }
   //______________________________________________________________________________
   int StoreData(int verbosity,int i,int NPTS,NMRPulse *aPulse,double *X,double *Y,double *EY){

      int N     = aPulse->GetNumPoints(); 
      int start = i - NPTS/2;
      int end   = i + NPTS/2;

      double v_current = aPulse->GetVoltage(i); 

      if(v_current!=0){
         // do nothing
      }else{
         // voltage of the zero crossing is zero! 
         start = i - 3; 
         end   = i + 3; 
         if(verbosity>=3){  
            std::cout << "[NMRMath::StoreData]: Voltage at zero crossing is zero!" << std::endl;
            std::cout << "                              start = " << start << std::endl;
            std::cout << "                              end   = " << end   << std::endl;
         }
      }

      // prevent unrealistic bounds: use 6 data points for the fit 
      if(start < 0){
         start = i; 
         end   = i + 6; 
         if(verbosity>=3){ 
            std::cout << "[NMRMath::StoreData]: Invalid start point!  Setting to index = " << i << std::endl; 
            std::cout << "                              start = " << start << std::endl;
            std::cout << "                              end   = " << end   << std::endl;
         }
      }else if(start==0){
         start = 0; 
         end   = 7; 
         if(verbosity>=3){
            std::cout << "[NMRMath::StoreData]: Starting at index = " << start << std::endl; 
            std::cout << "                              start = " << start << std::endl;
            std::cout << "                              end   = " << end   << std::endl;
         }
      }

      if(end > N){
         start = N - NPTS; 
         end   = N;
      } 

      int k=0;
      for(int j=start;j<end;j++){  
         X[k]  = aPulse->GetTime(j); 
         Y[k]  = aPulse->GetVoltage(j);  
         EY[k] = aPulse->GetVoltageErr(j);
         k++; 
      }

      int NPTSUseable= NPTS; 

      if(k!=NPTS){
         NPTSUseable = k; 
         if(verbosity>=3){
            std::cout << "[NMRMath::StoreData]: WARNING!  Do not have the expected number of data points! " << std::endl;
            std::cout << "                              k    = " << k    << std::endl;
            std::cout << "                              NPTS = " << NPTS << std::endl;
            std::cout << "                              Using k data points in fit..." << std::endl;
         }
      }

      return NPTSUseable; 

   }
   //______________________________________________________________________________
   void ClearAnaArrays(int N,double *X,double *Y,double *EY){
      for(int i=0;i<N;i++){
         X[i]  = 0; 
         Y[i]  = 0; 
         EY[i] = 0; 
      }
   }
   //______________________________________________________________________________
   double GetTimeOfCrossing(int verbosity,int method,int NPTSUseable,double X[],double Y[],double EY[], 
                            double t_current,double v_current,double v_current_err,
                            double t_next   ,double v_next   ,double v_next_err){

      const int SIZE = NPTSUseable;
      // std::cout << "Data to use in fit: " << std::endl; 
      // for(int i=0;i<SIZE;i++){
      //    std::cout << X[i] << "\t" << Y[i] << std::endl;
      // }

      int ret_val=0; 
      double v0=0,t0=0,a=0,b=0,r=0;

      if(method==1){
         // method 1: take midpoint between t_current and t_next 
         t0 = (t_current + t_next)/2.;
      }else if(method==2){
         // method 2: get time at V = 0, linear interpolation  
         t0 = LinearInterpolationForX(v0,t_current,v_current,t_next,v_next);
         // std::cout << "linear interpolation: t_current = " << t_current << "\t" << "t_next = " << t_next << "\t" << "t0 = " << t0 << std::endl;
      }else if(method==3){
         // method 3: least squares fit to neighboring points
         // to find fit parameters a and b in f(x) = a + bx 
         ret_val = LeastSquaresFitting(SIZE,X,Y,a,b,r);
         if(b!=0){
            t0 = -a/b;
         }else{
            t0 = 0;
         }
         // make sure t0 is bound properly 
         if(t0<X[0] || t0>X[SIZE-1]){
            if(verbosity>=3){
               std::cout << "[NMRMath::GetTimeOfCrossing]: ERROR!  t0 is out of bounds!  Using linear interpolation instead..." << std::endl;
               std::cout << "                              t_min = " << X[0] << "\t" << "t_max = " << X[SIZE-1] << "\t" << "t0 = " << t0 << std::endl;
            }
            t0 = LinearInterpolationForX(v0,t_current,v_current,t_next,v_next);
            if(verbosity>=3) std::cout << "[NMRMath::GetTimeOfCrossing]: linear interpolation: t_current = " << t_current << "\t" 
                                  << " t_next = " << t_next << "\t" << "t0 = " << t0 << std::endl;
         }
      }else{
         // invalid method, set to -1
         t0 = -1; 
      }

      if(verbosity>=3){  
         if(t0<0){
            std::cout << "[NMRMath::GetTimeOfCrossing]: BAD CROSSING TIME!" << std::endl;
            std::cout << "                                      t0        = " << t0        << std::endl;
            std::cout << "                                      method    = " << method    << std::endl;
            std::cout << "                                      t_current = " << t_current << std::endl;
            std::cout << "                                      t_next    = " << t_next    << std::endl;
            if(method==3){
               std::cout << "                                      offset = " << a << std::endl;
               std::cout << "                                      slope  = " << b << std::endl;
               for(int i=0;i<SIZE;i++){
                  std::cout << "                                      t = " << X[i] << "\t" << "v = " << Y[i] << std::endl;
               }
            }
         }
      }

      return t0; 

   }
   //______________________________________________________________________________
   int CountZeroCrossings(int verbosity,int method,int NPTS,int step,
                          bool UseTimeRange,double tMin,double tMax,
                          NMRPulse *aPulse,
                          double *X,double *Y,double *EY, 
                          int *NCrossing,int *CrossingIndex,double *tCross,double *vCross){
                          // std::vector<int> &NCrossing,std::vector<int> &CrossingIndex,std::vector<double> &tCross,std::vector<double> &vCross){

      if(verbosity>=3) std::cout << "[NMRMath]: Counting zero crossings..." << std::endl;

      // NPTS = number of points for linear fit
      // Step = how many points to skip ahead in counting zero crossings 

      int NPTSUseable = 0;

      const int N  = aPulse->GetNumPoints();

      int cntr         = 0;
      int cntr_prev    = 0;

      double v0           = 0;
      double target       = 0;
      double t0           = 0;
      // double elapsed_time = 0;  

      double v_prod=0;
      double delta_v=0; 
      double v_current=0,v_previous=0,v_next=0;
      double t_current=0,t_previous=0,t_next=0;
      double v_current_err=0,v_next_err=0,v_previous_err=0;

      int i=0;  // index for NMRPulse data 
      do{
         t_current     = aPulse->GetTime(i);
         t_next        = aPulse->GetTime(i+1);
         v_current     = aPulse->GetVoltage(i);
         v_next        = aPulse->GetVoltage(i+1);
         v_current_err = aPulse->GetVoltageErr(i);
         v_next_err    = aPulse->GetVoltageErr(i+1);
         v_prod        = v_current*v_next;
         if(v_prod > target){
            // positive number, no crossing
            // increment i by 1 
            i++; 
         }else if( v_prod <= target ){
            // negative number or ZERO, we had a crossing
            if(UseTimeRange){
               // use the fit range
               if(t_current > tMin && t_next < tMax){ 
                  // count the crossing 
                  cntr++;
                  delta_v     = fabs(v_current-v_next); 
                  // fill X, Y, EY arrays for fit method 
                  NPTSUseable = StoreData(verbosity,i,NPTS,aPulse,X,Y,EY); 
                  // get time of crossing  
                  t0 = GetTimeOfCrossing(verbosity,method,NPTSUseable,X,Y,EY,t_current,v_current,v_current_err,t_next,v_next,v_next_err); 
                  // fill vectors 
                  // NCrossing.push_back(cntr);
                  // CrossingIndex.push_back(i); 
                  // tCross.push_back(t0);
                  // vCross.push_back(v0);
                  // fill arrays
                  NCrossing[cntr-1]     = cntr;
                  CrossingIndex[cntr-1] = i;
                  tCross[cntr-1]        = t0;  
                  vCross[cntr-1]        = v0;  
               }
            }else{
               // don't use the fit range 
               // count the crossing 
               cntr++;
               delta_v = fabs(v_current-v_next); 
               NPTSUseable = StoreData(verbosity,i,NPTS,aPulse,X,Y,EY); 
               // get time of crossing  
               t0 = GetTimeOfCrossing(verbosity,method,NPTSUseable,X,Y,EY,t_current,v_current,v_current_err,t_next,v_next,v_next_err); 
               // fill vectors 
               // NCrossing.push_back(cntr);
               // CrossingIndex.push_back(i); 
               // tCross.push_back(t0);
               // vCross.push_back(v0);
               // fill arrays
               NCrossing[cntr-1]     = cntr;
               CrossingIndex[cntr-1] = i;
               tCross[cntr-1]        = t0;  
               vCross[cntr-1]        = v0;  
            }
            // check t0
            if(t0<0 || delta_v>0.100){   // we shouldn't see a 100 mV jump during the zero crossing 
               if(verbosity>=4){
                  std::cout << "[NMRMath::CountZeroCrossings]: bad crossing for Zc = " 
                            << cntr << "!  Trying next crossing..." << std::endl;
                  std::cout << "                               t0      = " << t0      << std::endl;
                  std::cout << "                               delta_v = " << delta_v << std::endl;
               }
               cntr--;   // don't count the crossing, decrement cntr 
               i += step;   // move to next bin 
               // delete last entry of vector 
               // NCrossing.pop_back();
               // CrossingIndex.pop_back(); 
               // tCross.pop_back(); 
               // vCross.pop_back(); 
               // clear analysis arrays 
               ClearAnaArrays(NPTSUseable,X,Y,EY);           // clears X, Y, EY  (sets to zero) 
               if(verbosity>=4){ 
                  std::cout << "[NMRMath::CountZeroCrossings]: zero crossing counter reset to: " << cntr << std::endl;
                  std::cout << "[NMRMath::CountZeroCrossings]: moving to index:                " << i       << std::endl;
               }
               continue; 
            }
            // passed t0 check 
            i += step;  // move to next bin  
            // set up for next data point 
            ClearAnaArrays(NPTSUseable,X,Y,EY);             // clears X, Y, EY  (sets to zero) 
            cntr_prev      = cntr;
            t_previous     = t_current;
            v_previous     = v_current; 
            v_previous_err = v_current_err; 
         }
      }while( i<(N-1) ); 

      if(verbosity>=3) std::cout << "[NMRMath::CountZeroCrossings]: Done." << std::endl;
      ClearAnaArrays(NPTSUseable,X,Y,EY);                   // clears fX, fY, fEY  (sets to zero) 

      return cntr;   // return number of zero crossings  
   }

}

