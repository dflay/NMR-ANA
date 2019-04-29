#include "NMRMath.h"
//______________________________________________________________________________
namespace NMRMath{
   //______________________________________________________________________________
   int IsNaN(double x){
      return isnan(x); 
   }
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

      if(method==kMidpoint){
         // method 1: take midpoint between t_current and t_next 
         t0 = (t_current + t_next)/2.;
      }else if(method==kLinearInterpolation){
         // method 2: get time at V = 0, linear interpolation  
         t0 = LinearInterpolationForX(v0,t_current,v_current,t_next,v_next);
         // std::cout << "linear interpolation: t_current = " << t_current << "\t" << "t_next = " << t_next << "\t" << "t0 = " << t0 << std::endl;
      }else if(method==kLeastSquares){
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

      // to get rid of warnings 
      ret_val += 0;
 
      return t0; 

   }
   //______________________________________________________________________________
   int AdjustTimeWindow(NMRPulse *aPulse,double &tStart,double &tStop){
     // adjust the start and stop times based on zero crossings 
     double prod=0,t0=0;
     double v_curr=0,v_prev=aPulse->GetVoltage(0);
     double t_curr=0,t_prev=aPulse->GetTime(0);
     const int N = aPulse->GetNumPoints();
     std::vector<double> tc;
     // rudimentary zero crossing to find all crossings 
     for(int i=1;i<N;i++){
       t_curr = aPulse->GetTime(i);
       v_curr = aPulse->GetVoltage(i);
       prod   = v_curr*v_prev;
       if(prod>0){
	 // no crossing 
       }else{
	 // found a crossing.  do linear interpolation to find the time 
	 t0 = LinearInterpolationForX(0.,t_prev,v_prev,t_curr,v_curr);
	 tc.push_back(t0);
       }
       // set up for next event 
       t_prev = t_curr;
       v_prev = v_curr;
     }

     // now adjust our start and stop times 
     const int M = tc.size();
     if(M==0) return 1;

     // window cuts around our start and stop times
     double delta=50E-6; 
     double start[2] = {tStart-delta,tStart+delta}; 
     double stop[2]  = {tStop-delta ,tStop+delta}; 

     // define start and stop times based on zero crossings 
     for(int i=0;i<M;i++){
       if( (tc[i]>start[0])&&(tc[i]<start[1]) ){
	 tStart = tc[i];
       }
       if( (tc[i]>stop[0])&&(tc[i]<stop[1]) ){
	 tStop  = tc[i];
       }
     }
     return 0;
   }
   //______________________________________________________________________________
   double GetT2Time(int startIndex,NMRPulse *aPulse){

     std::vector<double> tm,vm;
     int rc = FindLocalMaxima(startIndex,aPulse,tm,vm);   // first find local maxima 
     if(rc!=0) return -1; 

     double v=0,vmax=-300;
     const int ND = aPulse->GetNumPoints();

     // std::cout << "**** start = " << startIndex << " end = " << ND << std::endl;

     for(int i=startIndex;i<ND;i++){
       v = aPulse->GetVoltage(i); 
       if(vmax<v) vmax = v;
     }

     double t2_time=0;
     double e_const = exp(1);
     double v_lo    = 0.95*vmax/e_const;
     double v_hi    = 1.05*vmax/e_const;

     const int N = tm.size();
     if(N==0){
       std::cout << "[NMRMath::GetT2Time]: ERROR! No data for T2 time algorithm!  Returning -1" << std::endl;
       std::cout << "[NMRMath::GetT2Time]: Target voltage for T2 time is " << vmax/e_const << std::endl;
       std::cout << "                      window: lo = " << v_lo << " hi = " << v_hi << std::endl;
       return -1;
     }

     std::vector<double> tt,vv;
     for(int i=0;i<N;i++){
       if( fabs(vm[i])>v_lo && fabs(vm[i])<v_hi ){
	 tt.push_back(tm[i]);
	 vv.push_back(vm[i]);
       }
     }

     const int M = tt.size();
     if(M==0){
       std::cout << "[NMRMath::GetT2Time]: ERROR! No candidates for T2 times!  Returning -1" << std::endl;
       std::cout << "[NMRMath::GetT2Time]: Target voltage for T2 time is " << vmax/e_const << std::endl;
       std::cout << "                      window: lo = " << v_lo << " hi = " << v_hi << std::endl;
       return -1;
     }

     bool isBreak=false;

     double vdiff=0,vdiff_pct=0,tdiff=0;
     double v_prev = vv[0];
     double t_prev = tt[0];
     for(int i=1;i<M;i++){
       vdiff     = fabs(v_prev-vv[i]);
       vdiff_pct = vdiff/fabs(v_prev+vv[i]);
       tdiff     = fabs(t_prev-tt[i]);
       if(vdiff_pct>0.50 || tdiff>1E-3){   // greater than 50% change in voltage or larger than 1 ms step, probably junk
	 t2_time = tt[i-1];  // take previous time! 
	 isBreak = true;
	 break;
       }
       v_prev = vv[i];
       t_prev = tt[i];
     }

     // we went through all data, and haven't found a weird step that
     // warrants using the last reasonable time 
     if(!isBreak){
       // std::cout << "All candiates looked reasonable -- taking last one" << std::endl;
       t2_time = tt[M-1];
     }

     char msg[200];
     sprintf(msg,"The T2 time is: %.3lf ms",t2_time/1E-3);
     NMRUtility::PrintMessage("NMRMath::GetT2Time",msg); 

     return t2_time;
   }
   //______________________________________________________________________________
   double GetT2Time_v3(int start,NMRPulse *aPulse){
     // find the T2 time of the signal
     char msg[200]; 
     // find max amplitude
     double vmax=-300,v=0,t=0;
     const int N = aPulse->GetNumPoints();
     for(int i=start;i<N;i++){
       v = aPulse->GetVoltage(i); 
       if(vmax<v) vmax = v;
     }
     // find T2 ampl 
     double e_const = exp(1);
     double v_tgt   = vmax/e_const;
     double v_lo    = v_tgt - 1E-3;
     double v_hi    = v_tgt + 1E-3;
     sprintf(msg,"Target voltage (in mV) is %.3lf < v_tgt = %.3lf < %.3lf",v_lo/1E-3,v_tgt/1E-3,v_hi/1E-3); 
     // NMRUtility::PrintMessage("NMRMath::GetT2Time_v3",msg); 

     // now filter to get times and amplitudes close to the target 
     std::vector<double> tt,vv;
     for(int i=0;i<N;i++){
       t = aPulse->GetTime(i); 
       v = aPulse->GetVoltage(i); 
       if(v>0){
	 if( v>v_lo && v<v_hi ){
	   tt.push_back(t);
	   vv.push_back(v);
	 }
       }
     }

     const int NN = tt.size();
     if(NN==0){
       std::cout << "[GetT2Time_v3]: No T2 time candidates!" << std::endl;
       return -1;
     }else{
       // std::cout << "[GetT2Time_v3]: Found " << NN << " T2 time candidates" << std::endl;
       // for(int i=0;i<NN;i++) std::cout << Form("t = %.7lf ms, v = %.3lf mV",tt[i]/1E-3,vv[i]/1E-3) << std::endl;
     }

     // binary search to find the time we want 
     int lo=0,hi=0;
     NMRAlgorithm::BinarySearch(tt,v_tgt,lo,hi);
     double t2_time=0;
     double vdiff = fabs(vv[hi]-vv[lo]);
     if( vdiff<0.5E-3 ){
       // very small change in voltage; just take average of times  
       t2_time = 0.5*(tt[lo]+tt[hi]);
     }else{
       t2_time = LinearInterpolationForX(v_tgt,tt[lo],vv[lo],tt[hi],vv[hi]); // linear interpolation on the bounds  
     }
     // std::cout << Form("t[%d] = %.3lf ms, v[%d] = %.3lf mV",lo,tt[lo]/1E-3,lo,vv[lo]/1E-3) << std::endl;
     // std::cout << Form("t[%d] = %.3lf ms, v[%d] = %.3lf mV",hi,tt[hi]/1E-3,hi,vv[hi]/1E-3) << std::endl;
     
     sprintf(msg,"The T2 time is: %.3lf ms",t2_time/1E-3);
     NMRUtility::PrintMessage("NMRMath::GetT2Time_v3",msg); 

     return t2_time;

   }
   //______________________________________________________________________________
   double GetT2Time_old(double tStart,NMRPulse *aPulse){
      // find the T2 time of the signal
      // find max amplitude 
      double time=0,vmax=-300,v=0; 
      const int N = aPulse->GetNumPoints(); 
      for(int i=0;i<N;i++){
	time = aPulse->GetTime(i); 
	if(time>=tStart){             // avoid spurious samples in beginning 
	  v = aPulse->GetVoltage(i); 
	  if(vmax<v) vmax = v;
	}
      }
      // find T2 time 
      double t2_time=0;
      double e_const = exp(1);
      double v_lo    = vmax/e_const*(1. - 0.1);  
      double v_hi    = vmax/e_const*(1. + 0.1); 
      // std::vector<double> tt; // store T2 time candidates
      // std::cout << "***** VMAX = " << vmax << " VLO = " << v_lo << " VHI = " << v_hi << std::endl; 
      for(int i=0;i<N;i++){
         v = aPulse->GetVoltage(i); 
         if( fabs(v)>v_lo && fabs(v)<v_hi ){
	    // tt.push_back( aPulse->GetTime(i) ); 
            t2_time = aPulse->GetTime(i);
         } 
      }
      // std::cout << "***** T2 TIME IS " << t2_time << std::endl; 
      // std::cout << "T2 candidates: " << std::endl;
      // for(int i=0;i<tt.size();i++) std::cout << tt[i] << std::endl; 
      return t2_time;
   }
   //______________________________________________________________________________
   int FindLocalMaxima(int startIndex,NMRPulse *aPulse,std::vector<double> &T,std::vector<double> &V){
     // find all local maxima from a set of data
     const int N = aPulse->GetNumPoints();
     double v=0,vp=0,vn=0,t=0;
     std::vector<double> tt,vv;
     for(int i=startIndex;i<N;i++){
       t  = aPulse->GetTime(i); 
       v  = aPulse->GetVoltage(i);
       vp = aPulse->GetVoltage(i-1);
       vn = aPulse->GetVoltage(i+1);
       if(v>0){
	 // chop off all negative values to start 
	 if(v>vp && v>vn){
	   // is the value greater than preivous AND greater than the next entry?
	   // looks like a maximum, keep it 
	   tt.push_back(t);
	   vv.push_back(v);
	 }
       }
     }
     int stepSize = 10E+6*1.0E-6; // 10 MHz * 1.0 us 
     int rc = RebinData(stepSize,tt,vv,T,V);
     return rc;
   }
   //______________________________________________________________________________
   int RebinData(int stepSize,std::vector<double> x,std::vector<double> y,
                 std::vector<double> &X,std::vector<double> &Y){
     int cntr=0;
     double mx=0,my=0;
     const int N = x.size();
     std::vector<double> xx,yy;
     for(int i=0;i<N;i++){
       // gather data
       xx.push_back(x[i]);
       yy.push_back(y[i]);
       cntr++;
       if(cntr==stepSize){
	 // if we hit the stepSize limit, average over data  
	 mx = GetMean(xx);
	 my = GetMean(yy);
	 // store and clear for next samples 
	 X.push_back(mx);
	 Y.push_back(my);
	 xx.clear();
	 yy.clear();
	 cntr=0;
       }
     }
     return 0;
   }
   //______________________________________________________________________________
   int NonLinearLeastSquaresFitting(std::vector<double> xd,std::vector<double> yd,std::vector<double> dyd,
       int (*F)(const gsl_vector *x,void *data,gsl_vector *f),int (*DF)(const gsl_vector *x,void *data,gsl_matrix *J),
       std::vector<double> &par,std::vector<double> &parErr,const int NPAR,const int verbosity){
     // fit the data set (x,y) with uncertainties dy to the function F with jacobian DF  
     // par will have initial values to start 

     const int NPTS = xd.size();

     double chisq,chisq0;

     const double xtol = 1e-8;
     const double gtol = 1e-8;
     const double ftol = 0.0;

     gsl_rng *r;  // random number generator 
     gsl_rng_env_setup();
     r = gsl_rng_alloc(gsl_rng_default);

     // data set
     char msg[200];
     double xa[NPTS],ya[NPTS],weights[NPTS];

     if(verbosity>1) std::cout << "Input data: " << std::endl;
     for(int i=0;i<NPTS;i++){
       xa[i] = xd[i];
       ya[i] = yd[i];
       if(dyd[i]!=0){ 
	 weights[i] = 1./( dyd[i]*dyd[i] );
       }else{
	 weights[i] = 1.;
       }
       sprintf(msg,"i = %03d, x = %.5E, y = %.3lf",i,xa[i],ya[i]);
       if(verbosity>1) std::cout << msg << std::endl;
     }
     data_t d = {(size_t)NPTS,xa,ya};

     double parInit[NPAR]; // starting values
     for(int i=0;i<NPAR;i++) parInit[i] = par[i];
     gsl_vector_view xx  = gsl_vector_view_array(parInit,(size_t)NPAR);
     gsl_vector_view wts = gsl_vector_view_array(weights,(size_t)NPTS);

     if(NPTS<NPAR){
       std::cout << "[NMRMath::NonLinearLeastSquaresFitting]: ERROR: NPTS < NPAR!" << std::endl;
       std::cout << "NPTS = " << NPTS << std::endl;
       std::cout << "NPAR = " << NPAR << std::endl;
       return 1;
     }

     // define the function to be minimized 
     gsl_multifit_nlinear_fdf fitFunc;
     gsl_multifit_nlinear_parameters fitFunc_params = gsl_multifit_nlinear_default_parameters();
     fitFunc.f      = F;
     fitFunc.df     = DF;           // set to NULL for finite-difference Jacobian 
     fitFunc.fvv    = NULL;         // not using geodesic acceleration 
     fitFunc.n      = (size_t)NPTS; // number of data points 
     fitFunc.p      = (size_t)NPAR; // number of parameters
     fitFunc.params = &d;           // data object (NPTS, array of data).

     // allocate workspace with default parameters 
     gsl_multifit_nlinear_workspace *w;
     const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
     w = gsl_multifit_nlinear_alloc(T,&fitFunc_params,NPTS,NPAR);

     // initialize solver with starting point and weights 
     gsl_multifit_nlinear_winit(&xx.vector,&wts.vector,&fitFunc,w);

     // compute initial cost function 
     gsl_vector *f;
     f = gsl_multifit_nlinear_residual(w);
     gsl_blas_ddot(f,f,&chisq0);

     // solve the system with a maximum of 1000 iterations
     int info=-1;
     int status = gsl_multifit_nlinear_driver(5000,xtol,gtol,ftol,callbackFunction,NULL,&info,w);

     // compute covariance of best fit parameters 
     gsl_matrix *J;
     gsl_matrix *covar = gsl_matrix_alloc(NPAR,NPAR);
     J = gsl_multifit_nlinear_jac(w);
     gsl_multifit_nlinear_covar (J,0.0,covar);

     // compute final cost 
     gsl_blas_ddot(f,f,&chisq);

     std::string stopReason = "small step size";
     if(info!=1) stopReason = "small gradient";

     double dof = (double)(NPTS-NPAR);
     double c   = GSL_MAX_DBL( 1,sqrt(chisq/dof) );
     for(int i=0;i<NPAR;i++){
       par[i]    = gsl_vector_get(w->x,i);
       parErr[i] = c*sqrt( gsl_matrix_get(covar,i,i) );
     }

     if(verbosity>0){
       std::cout << "------------------ FIT SUMMARY ------------------" << std::endl;
       sprintf(msg,"Summary from method %s/%s",gsl_multifit_nlinear_name(w),gsl_multifit_nlinear_trs_name(w));
       std::cout << msg << std::endl;
       sprintf(msg,"Number of iterations: %zu",gsl_multifit_nlinear_niter(w) );
       std::cout << msg << std::endl;
       sprintf(msg,"Function evaluations: %zu",fitFunc.nevalf);
       std::cout << msg << std::endl;
       sprintf(msg,"Jacobian evaluations: %zu",fitFunc.nevaldf);
       std::cout << msg << std::endl;
       sprintf(msg,"Reason for stopping:  %s" ,stopReason.c_str());
       std::cout << msg << std::endl;
       sprintf(msg,"initial |f(x)|:       %.3lf",sqrt(chisq0) );
       std::cout << msg << std::endl;
       sprintf(msg,"final |f(x)|:         %.3lf",sqrt(chisq)  );
       std::cout << msg << std::endl;
       sprintf(msg,"status:               %s",gsl_strerror(status));
       std::cout << msg << std::endl;
       std::cout << "Fit results " << std::endl;
       sprintf(msg,"chisq = %.8lf",chisq);
       std::cout << msg << std::endl;
       sprintf(msg,"ndf = %.0lf",dof);
       std::cout << msg << std::endl;
       for(int i=0;i<NPAR;i++){
	 sprintf(msg,"par[%d] = %.5lf +/- %.5lf",i,par[i],parErr[i]);
	 std::cout << msg << std::endl;
       }
     }

     gsl_multifit_nlinear_free(w);
     gsl_matrix_free(covar);
     gsl_rng_free(r);

     return 0;
   }
   //______________________________________________________________________________
   void callbackFunction(const size_t iter,void *params,const gsl_multifit_nlinear_workspace *w){
     // function the user calls 
     gsl_vector *f = gsl_multifit_nlinear_residual(w);
     // gsl_vector *p = gsl_multifit_nlinear_position(w);

     // compute reciprocal condition number of J(x) 
     double rcond;
     gsl_multifit_nlinear_rcond(&rcond,w);
     double cond = 1./rcond; 
     double abs_f = gsl_blas_dnrm2(f); 

     // const int NPAR = 5; 
     // double par[NPAR];
     // for(int i=0;i<NPAR;i++) par[i] = gsl_vector_get(p,i);

     char msg[200];
     sprintf(msg,"iter %2zu: cond(J) = %.5lf, |f(x)| = %.5lf",iter,cond,abs_f);
     // std::cerr << msg << std::endl;
   }
   //______________________________________________________________________________
   int poly1(const gsl_vector *p,void *data,gsl_vector *f){
     // fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     double *ya = ( (data_t *)data )->y;
     // fit parameters 
     const int npar = 2;
     double par[npar];
     for(int i=0;i<npar;i++){
       par[i] = gsl_vector_get(p,i);
     }
     // compute chi^2 function 
     double iy=0;
     for(size_t i=0;i<n;i++){
       iy = par[0] + par[1]*xa[i];
       gsl_vector_set(f,i,iy-ya[i]);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly3(const gsl_vector *p,void *data,gsl_vector *f){
     // fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     double *ya = ( (data_t *)data )->y;
     // fit parameters 
     const int npar = 3;
     double par[npar];
     for(int i=0;i<npar;i++){
       par[i] = gsl_vector_get(p,i);
     }
     // compute chi^2 function 
     double iy=0;
     for(size_t i=0;i<n;i++){
       iy = par[0] + par[1]*xa[i] + par[2]*pow(xa[i],3.);
       gsl_vector_set(f,i,iy-ya[i]);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly5(const gsl_vector *p,void *data,gsl_vector *f){
     // fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     double *ya = ( (data_t *)data )->y;
     // fit parameters 
     const int npar = 4;
     double par[npar];
     for(int i=0;i<npar;i++){
       par[i] = gsl_vector_get(p,i);
     }
     // compute chi^2 function 
     double iy=0;
     for(size_t i=0;i<n;i++){
       iy = par[0] + par[1]*xa[i] + par[2]*pow(xa[i],3.) + par[3]*pow(xa[i],5.);
       gsl_vector_set(f,i,iy-ya[i]);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly7(const gsl_vector *p,void *data,gsl_vector *f){
     // fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     double *ya = ( (data_t *)data )->y;
     // fit parameters 
     const int npar = 5;
     double par[npar];
     for(int i=0;i<npar;i++){
       par[i] = gsl_vector_get(p,i);
     }
     // compute chi^2 function 
     double iy=0;
     for(size_t i=0;i<n;i++){
       iy = par[0] + par[1]*xa[i] + par[2]*pow(xa[i],3.) + par[3]*pow(xa[i],5.) + par[4]*pow(xa[i],7.);
       gsl_vector_set(f,i,iy-ya[i]);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly9(const gsl_vector *p,void *data,gsl_vector *f){
     // fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     double *ya = ( (data_t *)data )->y;
     // fit parameters 
     const int npar = 6;
     double par[npar];
     for(int i=0;i<npar;i++){
       par[i] = gsl_vector_get(p,i);
     }
     // compute chi^2 function 
     double iy=0;
     for(size_t i=0;i<n;i++){
       iy = par[0] + par[1]*xa[i] + par[2]*pow(xa[i],3.) + par[3]*pow(xa[i],5.) + par[4]*pow(xa[i],7.) + par[5]*pow(xa[i],9.);
       gsl_vector_set(f,i,iy-ya[i]);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly1_df(const gsl_vector *x,void *data,gsl_matrix *J){
     // Jacobian for fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     // compute jacobian for each data point  
     double arg_i0=0,arg_i1=0;
     for(size_t i=0;i<n;i++){
       arg_i0 = 1.0;
       arg_i1 = pow(xa[i],1.);
       gsl_matrix_set(J,i,0,arg_i0);
       gsl_matrix_set(J,i,1,arg_i1);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly3_df(const gsl_vector *x,void *data,gsl_matrix *J){
     // Jacobian for fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     // compute jacobian for each data point  
     double arg_i0=0,arg_i1=0,arg_i2=0;
     for(size_t i=0;i<n;i++){
       arg_i0 = 1.0;
       arg_i1 = pow(xa[i],1.);
       arg_i2 = pow(xa[i],3.);
       gsl_matrix_set(J,i,0,arg_i0);
       gsl_matrix_set(J,i,1,arg_i1);
       gsl_matrix_set(J,i,2,arg_i2);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly5_df(const gsl_vector *x,void *data,gsl_matrix *J){
     // Jacobian for fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     // compute jacobian for each data point  
     double arg_i0=0,arg_i1=0,arg_i2=0,arg_i3=0;
     for(size_t i=0;i<n;i++){
       arg_i0 = 1.0;
       arg_i1 = pow(xa[i],1.);
       arg_i2 = pow(xa[i],3.);
       arg_i3 = pow(xa[i],5.);
       gsl_matrix_set(J,i,0,arg_i0);
       gsl_matrix_set(J,i,1,arg_i1);
       gsl_matrix_set(J,i,2,arg_i2);
       gsl_matrix_set(J,i,3,arg_i3);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly7_df(const gsl_vector *x,void *data,gsl_matrix *J){
     // Jacobian for fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     // compute jacobian for each data point  
     double arg_i0=0,arg_i1=0,arg_i2=0,arg_i3=0,arg_i4=0;
     for(size_t i=0;i<n;i++){
       arg_i0 = 1.0;
       arg_i1 = pow(xa[i],1.);
       arg_i2 = pow(xa[i],3.);
       arg_i3 = pow(xa[i],5.);
       arg_i4 = pow(xa[i],7.);
       gsl_matrix_set(J,i,0,arg_i0);
       gsl_matrix_set(J,i,1,arg_i1);
       gsl_matrix_set(J,i,2,arg_i2);
       gsl_matrix_set(J,i,3,arg_i3);
       gsl_matrix_set(J,i,4,arg_i4);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int poly9_df(const gsl_vector *x,void *data,gsl_matrix *J){
     // Jacobian for fit function f(x) = p0 + p1*x + p2*x^3 + p3*x^5 + p4*x^7
     // data set 
     size_t n   = ( (data_t *)data )->n;
     double *xa = ( (data_t *)data )->x;
     // compute jacobian for each data point  
     double arg_i0=0,arg_i1=0,arg_i2=0,arg_i3=0,arg_i4=0,arg_i5=0;
     for(size_t i=0;i<n;i++){
       arg_i0 = 1.0;
       arg_i1 = pow(xa[i],1.);
       arg_i2 = pow(xa[i],3.);
       arg_i3 = pow(xa[i],5.);
       arg_i4 = pow(xa[i],7.);
       arg_i5 = pow(xa[i],9.);
       gsl_matrix_set(J,i,0,arg_i0);
       gsl_matrix_set(J,i,1,arg_i1);
       gsl_matrix_set(J,i,2,arg_i2);
       gsl_matrix_set(J,i,3,arg_i3);
       gsl_matrix_set(J,i,4,arg_i4);
       gsl_matrix_set(J,i,5,arg_i5);
     }
     return GSL_SUCCESS;
   }
   //______________________________________________________________________________
   int CountZeroCrossings(int verbosity,int method,int NPTS,int step,
                          bool UseT2Time,bool UseTimeRange,double tMin,double tMax,
                          NMRPulse *aPulse,
                          double *X,double *Y,double *EY, 
                          int *NCrossing,int *CrossingIndex,double *tCross,double *vCross){

      if(verbosity>=3) std::cout << "[NMRMath]: Counting zero crossings..." << std::endl;

      // NPTS = number of points for linear fit
      // Step = how many points to skip ahead in counting zero crossings 

      int NPTSUseable = 0;

      const int N  = aPulse->GetNumPoints();

      int cntr         = 0;
      // int cntr_prev   = 0;

      double v0        = 0;
      double target    = 0;
      double t0        = 0;
      // double elapsed_time = 0;  

      double tMax_orig = tMax; 

      // compute and use the T2 time if necessary. 
      // NOTE: this will replace the input endtime if the T2 boolean is true. 
      // int startIndex = (int)(10E+6*500E-6);  // for T2 time  
      if(UseT2Time){
         tMin = 500E-6;   // start at 500 us 
         // tMax = GetT2Time(startIndex,aPulse);
	 tMax = aPulse->GetT2Time(); 
         UseTimeRange = true; 
         if(verbosity>3) std::cout << "[NMRMath::CountZeroCrossings]: Using the T2 time for frequency extraction.  T2 = " << tMax/1E-3 << " ms" << std::endl;
	 // std::cout << "[NMRMath::CountZeroCrossings]: T2 = " << tMax/1E-3 << " ms" << std::endl;
      } 
       
      double v_prod=0;
      double delta_v=0; 
      double v_current=0,v_next=0;
      double t_current=0,t_next=0;
      double v_current_err=0,v_next_err=0;

      if(tMax<0){
	tMax = tMax_orig; 
	std::cout << "[NMRMath::CountZeroCrossings]: WARNING: stop time window is UNPHYSICAL!";
	std::cout << "  Defaulting to original stop time = " << tMax/1E-3 << " ms" << std::endl;
      }

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
            // cntr_prev      = cntr;
            // t_previous     = t_current;
            // v_previous     = v_current; 
            // v_previous_err = v_current_err; 
         }
      }while( i<(N-1) ); 

      if(verbosity>=3) std::cout << "[NMRMath::CountZeroCrossings]: Done." << std::endl;
      ClearAnaArrays(NPTSUseable,X,Y,EY);                   // clears fX, fY, fEY  (sets to zero) 

      // std::cout << "[NMRMath::CountZeroCrossings]: NumCrossings = " << cntr << std::endl; 
      return cntr;   // return number of zero crossings  
   }

}

