#include "NMRPulse.h"
//______________________________________________________________________________
NMRPulse::NMRPulse(int PulseNumber,int NPTS){
   fPulseNumber      = PulseNumber;
   fNumPoints        = NPTS; 
   fTimeStamp        = 0.;  
   fAmpl             = 0.; 
   fNoiseRMS         = 0.; 
   fTemperature      = 0.;
   fT2Time           = 0.; 
   fVerbosity        = 0;
   fChannelNumber    = 0; 
   const int N       = NPTS;
   fTime             = new double[N]; 
   fVoltage          = new double[N]; 
   fVoltageErr       = new double[N]; 
   ClearVectorData(); 
}
//______________________________________________________________________________
NMRPulse::NMRPulse(const NMRPulse &aPulse){
   // copy constructor
   // shallow copy 
   fPulseNumber      = aPulse.GetPulseNumber();
   fNumPoints        = aPulse.GetNumPoints(); 
   fTimeStamp        = aPulse.GetTimeStamp(); 
   fAmpl             = aPulse.GetAmplitude();
   fT2Time           = aPulse.GetT2Time(); 
   fNoiseRMS         = aPulse.GetNoiseRMS();
   fTemperature      = aPulse.GetTemperature(); 
   fChannelNumber    = aPulse.GetChannelNumber(); 
   // deep copy 
   const int N       = fNumPoints;
   if(N>0){
      fTime       = new double[N]; 
      fVoltage    = new double[N]; 
      fVoltageErr = new double[N]; 
      for(int i=0;i<N;i++){
         fTime[i]       = aPulse.GetTime(i); 
         fVoltage[i]    = aPulse.GetVoltage(i); 
         fVoltageErr[i] = aPulse.GetVoltageErr(i); 
      }
   }
}
//______________________________________________________________________________
NMRPulse::NMRPulse(const NMRPulse *aPulse){
   // copy constructor
   // shallow copy 
   fPulseNumber      = aPulse->GetPulseNumber();
   fNumPoints        = aPulse->GetNumPoints(); 
   fTimeStamp        = aPulse->GetTimeStamp(); 
   fAmpl             = aPulse->GetAmplitude(); 
   fT2Time           = aPulse->GetT2Time(); 
   fNoiseRMS         = aPulse->GetNoiseRMS(); 
   fTemperature      = aPulse->GetTemperature(); 
   fChannelNumber    = aPulse->GetChannelNumber(); 
   // deep copy 
   const int N       = fNumPoints; 
   if(N>0){   
      fTime       = new double[N]; 
      fVoltage    = new double[N]; 
      fVoltageErr = new double[N]; 
      for(int i=0;i<N;i++){
         fTime[i]       = aPulse->GetTime(i); 
         fVoltage[i]    = aPulse->GetVoltage(i); 
         fVoltageErr[i] = aPulse->GetVoltageErr(i); 
      }
   }else{
      fTime       = 0;
      fVoltage    = 0;
      fVoltageErr = 0;
   }


}
//______________________________________________________________________________
NMRPulse& NMRPulse::operator=(const NMRPulse &aPulse){
   // check for self-assignment 
   if(this==&aPulse) return *this; 
   // deallocate any data in time and voltage arrays
   delete[] fTime; 
   delete[] fVoltage; 
   delete[] fVoltageErr; 
   // do same as in our copy constructor 
   // shallow copy 
   fPulseNumber      = aPulse.GetPulseNumber();
   fNumPoints        = aPulse.GetNumPoints(); 
   fTimeStamp        = aPulse.GetTimeStamp(); 
   fAmpl             = aPulse.GetAmplitude(); 
   fT2Time           = aPulse.GetT2Time(); 
   fNoiseRMS         = aPulse.GetNoiseRMS(); 
   fTemperature      = aPulse.GetTemperature(); 
   fChannelNumber    = aPulse.GetChannelNumber(); 
   // deep copy 
   const int N       = fNumPoints;
   if(N>0){  
      fTime       = new double[N]; 
      fVoltage    = new double[N]; 
      fVoltageErr = new double[N]; 
      for(int i=0;i<N;i++){
         fTime[i]       = aPulse.GetTime(i); 
         fVoltage[i]    = aPulse.GetVoltage(i); 
         fVoltageErr[i] = aPulse.GetVoltageErr(i); 
      }
   }else{
      fTime       = 0;
      fVoltage    = 0;
      fVoltageErr = 0;
   }

   return *this; 
}
//______________________________________________________________________________
NMRPulse* NMRPulse::operator=(const NMRPulse* aPulse){
   // check for self-assignment 
   if(this==aPulse) return this; 
   // deallocate any data in time and voltage arrays
   delete[] fTime; 
   delete[] fVoltage; 
   delete[] fVoltageErr; 
   // do same as in our copy constructor 
   // shallow copy 
   fPulseNumber   = aPulse->GetPulseNumber();
   fNumPoints     = aPulse->GetNumPoints(); 
   fTimeStamp     = aPulse->GetTimeStamp(); 
   fAmpl          = aPulse->GetAmplitude(); 
   fT2Time        = aPulse->GetT2Time(); 
   fNoiseRMS      = aPulse->GetNoiseRMS(); 
   fTemperature   = aPulse->GetTemperature(); 
   fChannelNumber = aPulse->GetChannelNumber(); 
   // deep copy 
   const int N    = fNumPoints;
   if(N>0){   
      fTime       = new double[N]; 
      fVoltage    = new double[N]; 
      fVoltageErr = new double[N]; 
      for(int i=0;i<N;i++){
         fTime[i]       = aPulse->GetTime(i); 
         fVoltage[i]    = aPulse->GetVoltage(i); 
         fVoltageErr[i] = aPulse->GetVoltageErr(i); 
      }
   }else{
      fTime       = 0;
      fVoltage    = 0;
      fVoltageErr = 0;
   }

   return this; 
}
//______________________________________________________________________________
NMRPulse::~NMRPulse(){
   delete[] fTime;
   delete[] fVoltage;  
   delete[] fVoltageErr;
}
//______________________________________________________________________________
void NMRPulse::SetNumPoints(int p){
   // set number of data points; 
   // this will CLEAR current data and make new arrays of size p.  
   if(fVerbosity>=3) std::cout << "[NMRPulse]: Resetting the number of data points to " << p << "..." << std::endl;
   fNumPoints = p;
   delete[] fTime; 
   delete[] fVoltage;
   delete[] fVoltageErr;
   const int N = fNumPoints;
   fTime       = new double[N]; 
   fVoltage    = new double[N]; 
   fVoltageErr = new double[N]; 
   ClearVectorData(); 
   if(fVerbosity>=3) std::cout << "[NMRPulse]: New number of points = " << fNumPoints << std::endl;
}
//______________________________________________________________________________
void NMRPulse::ClearData(){
   fTimeStamp        = 0.;  
   fAmpl             = 0.; 
   fNoiseRMS         = 0.; 
   for(int i=0;i<fNumPoints;i++){
      fTime[i]       = 0;
      fVoltage[i]    = 0;
      fVoltageErr[i] = 0;
   }
}
//______________________________________________________________________________
void NMRPulse::ClearVectorData(){
   for(int i=0;i<fNumPoints;i++){
      fTime[i]       = 0;
      fVoltage[i]    = 0;
      fVoltageErr[i] = 0;
   }
}
//______________________________________________________________________________
void NMRPulse::SetData(int N,double t[],double v[],double ev[]){
   for(int i=0;i<N;i++){
      fTime[i]       = t[i]; 
      fVoltage[i]    = v[i]; 
      fVoltageErr[i] = ev[i]; 
   }
}
//______________________________________________________________________________
void NMRPulse::SetDataPoint(int i,double t,double v,double ev){
   fTime[i]       = t; 
   fVoltage[i]    = v; 
   fVoltageErr[i] = ev; 
}
//______________________________________________________________________________
void NMRPulse::Print(){
   printf("================ NMR Pulse ================ \n");
   printf("PulseNumber      = %d      \n"  ,fPulseNumber);
   printf("ChannelNumber    = %d      \n"  ,fChannelNumber);
   printf("NumPoints        = %d      \n"  ,fNumPoints  );
   printf("TimeStamp        = %llu    \n"  ,fTimeStamp  );
   printf("Amplitude        = %.3lf V \n"  ,fAmpl       );
   printf("Noise RMS        = %.3lf mV \n" ,fNoiseRMS/1E-3);
   printf("T2 time          = %.3lf ms\n"  ,fT2Time/1E-3); 
   printf("Temperature      = %.3lf Ohms\n",fTemperature); 
   // for(int i=0;i<fNumPoints;i++){
   //    printf("time = %.7f s \t voltage = %.7f V \t voltage err = %.7f V \n",fTime[i],fVoltage[i],fVoltageErr[i]); 
   // }
}
