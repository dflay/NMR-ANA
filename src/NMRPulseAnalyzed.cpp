#include "NMRPulseAnalyzed.h"
//______________________________________________________________________________
NMRPulseAnalyzed::NMRPulseAnalyzed(int PulseNumber,int NPTS){
   fPulseNumber      = PulseNumber;
   fTimeStamp        = 0; 
   fNumZeroCrossings = 0;
   fAmpl             = 0;
   fNoiseRMS         = 0;
   fNumCycles        = 0;
   fSNR              = 0;
   fFREQ_fit         = 0;
   fFREQ_ph          = 0;
   fB_fit            = 0;
   fB_ph             = 0;
   fVerbosity        = 0; 
   fNumPoints        = NPTS; 
   const int N3      = 3; 
   fFREQ_zc          = new double[N3]; 
   fB_zc             = new double[N3]; 
   for(int i=0;i<N3;i++) fFREQ_zc[i] = 0.;  
   for(int i=0;i<N3;i++) fB_zc[i]    = 0.;  
}
//______________________________________________________________________________
NMRPulseAnalyzed::NMRPulseAnalyzed(const NMRPulseAnalyzed &aPulse): NMRPulse(aPulse){  
   // copy constructor: be aware of the initialization of NMRPulse(). 
   // shallow copy 
   fPulseNumber      = aPulse.GetPulseNumber();
   fNumZeroCrossings = aPulse.GetNumZeroCrossings();
   fTimeStamp        = aPulse.GetTimeStamp(); 
   fFREQ_fit         = aPulse.GetFrequencyFit(); 
   fFREQ_ph          = aPulse.GetFrequencyPhaseFit(); 
   fB_fit            = aPulse.GetFieldFit(); 
   fB_ph             = aPulse.GetFieldPhaseFit(); 
   fAmpl             = aPulse.GetAmplitude();
   fNoiseRMS         = aPulse.GetNoiseRMS();
   fNumCycles        = aPulse.GetNumCycles();
   fSNR              = aPulse.GetSignalToNoiseRatio();
   fNumPoints        = aPulse.GetNumPoints(); 
   // deep copy: base constructor does this (for times and voltages) 
   const int N3 = 3; 
   fFREQ_zc     = new double[N3]; 
   fFREQ_zc[0]  = aPulse.GetFrequencyZeroCrossingMidpoint(); 
   fFREQ_zc[1]  = aPulse.GetFrequencyZeroCrossingLinearInterp(); 
   fFREQ_zc[2]  = aPulse.GetFrequencyZeroCrossingLeastSquares(); 
   fB_zc        = new double[N3]; 
   fB_zc[0]     = aPulse.GetFieldZeroCrossingMidpoint(); 
   fB_zc[1]     = aPulse.GetFieldZeroCrossingLinearInterp(); 
   fB_zc[2]     = aPulse.GetFieldZeroCrossingLeastSquares(); 
}
//______________________________________________________________________________
NMRPulseAnalyzed::NMRPulseAnalyzed(const NMRPulseAnalyzed *aPulse): NMRPulse(aPulse){
   // copy constructor: be aware of the initialization of NMRPulse(). 
   // shallow copy 
   fPulseNumber      = aPulse->GetPulseNumber();
   fTimeStamp        = aPulse->GetTimeStamp(); 
   fNumZeroCrossings = aPulse->GetNumZeroCrossings();
   fFREQ_fit         = aPulse->GetFrequencyFit(); 
   fFREQ_ph          = aPulse->GetFrequencyPhaseFit();
   fB_fit            = aPulse->GetFieldFit(); 
   fB_ph             = aPulse->GetFieldPhaseFit(); 
   fAmpl             = aPulse->GetAmplitude();
   fNoiseRMS         = aPulse->GetNoiseRMS();
   fNumCycles        = aPulse->GetNumCycles();
   fSNR              = aPulse->GetSignalToNoiseRatio();
   fNumPoints        = aPulse->GetNumPoints(); 
   // deep copy: base constructor does this (for times and voltages)  
   const int N3 = 3; 
   fFREQ_zc     = new double[N3]; 
   fFREQ_zc[0]  = aPulse->GetFrequencyZeroCrossingMidpoint(); 
   fFREQ_zc[1]  = aPulse->GetFrequencyZeroCrossingLinearInterp(); 
   fFREQ_zc[2]  = aPulse->GetFrequencyZeroCrossingLeastSquares(); 
   fB_zc        = new double[N3]; 
   fB_zc[0]     = aPulse->GetFieldZeroCrossingMidpoint(); 
   fB_zc[1]     = aPulse->GetFieldZeroCrossingLinearInterp(); 
   fB_zc[2]     = aPulse->GetFieldZeroCrossingLeastSquares(); 
}
//______________________________________________________________________________
NMRPulseAnalyzed& NMRPulseAnalyzed::operator=(const NMRPulseAnalyzed &aPulse){
   // do same as in our copy constructor 
   // shallow copy 
   fPulseNumber      = aPulse.GetPulseNumber();
   fTimeStamp        = aPulse.GetTimeStamp(); 
   fNumZeroCrossings = aPulse.GetNumZeroCrossings();
   fFREQ_fit         = aPulse.GetFrequencyFit(); 
   fFREQ_ph          = aPulse.GetFrequencyPhaseFit(); 
   fB_fit            = aPulse.GetFrequencyFit(); 
   fB_ph             = aPulse.GetFrequencyPhaseFit(); 
   fAmpl             = aPulse.GetAmplitude();
   fNoiseRMS         = aPulse.GetNoiseRMS();
   fNumCycles        = aPulse.GetNumCycles();
   fSNR              = aPulse.GetSignalToNoiseRatio();
   fNumPoints        = aPulse.GetNumPoints(); 
   // deep copy (a lot of this is done in the NMRPulse class)  
   const int N3 = 3; 
   fFREQ_zc     = new double[N3]; 
   fFREQ_zc[0]  = aPulse.GetFrequencyZeroCrossingMidpoint(); 
   fFREQ_zc[1]  = aPulse.GetFrequencyZeroCrossingLinearInterp(); 
   fFREQ_zc[2]  = aPulse.GetFrequencyZeroCrossingLeastSquares(); 
   fB_zc        = new double[N3]; 
   fB_zc[0]     = aPulse.GetFieldZeroCrossingMidpoint(); 
   fB_zc[1]     = aPulse.GetFieldZeroCrossingLinearInterp(); 
   fB_zc[2]     = aPulse.GetFieldZeroCrossingLeastSquares(); 

   return *this; 
}
//______________________________________________________________________________
NMRPulseAnalyzed* NMRPulseAnalyzed::operator=(const NMRPulseAnalyzed* aPulse){
   // shallow copy 
   fPulseNumber      = aPulse->GetPulseNumber();
   fTimeStamp        = aPulse->GetTimeStamp(); 
   fNumZeroCrossings = aPulse->GetNumZeroCrossings();
   fFREQ_fit         = aPulse->GetFrequencyFit(); 
   fFREQ_ph          = aPulse->GetFrequencyPhaseFit(); 
   fB_fit            = aPulse->GetFieldFit(); 
   fB_ph             = aPulse->GetFieldPhaseFit(); 
   fAmpl             = aPulse->GetAmplitude();
   fNoiseRMS         = aPulse->GetNoiseRMS();
   fNumCycles        = aPulse->GetNumCycles();
   fSNR              = aPulse->GetSignalToNoiseRatio();
   fNumPoints        = aPulse->GetNumPoints(); 
   // deep copy (a lot of this is done in the NMRPulse class)  
   const int N3 = 3; 
   fFREQ_zc     = new double[N3]; 
   fFREQ_zc[0]  = aPulse->GetFrequencyZeroCrossingMidpoint(); 
   fFREQ_zc[1]  = aPulse->GetFrequencyZeroCrossingLinearInterp(); 
   fFREQ_zc[2]  = aPulse->GetFrequencyZeroCrossingLeastSquares(); 
   fB_zc        = new double[N3]; 
   fB_zc[0]     = aPulse->GetFieldZeroCrossingMidpoint(); 
   fB_zc[1]     = aPulse->GetFieldZeroCrossingLinearInterp(); 
   fB_zc[2]     = aPulse->GetFieldZeroCrossingLeastSquares(); 

   return this; 
}
//______________________________________________________________________________
NMRPulseAnalyzed::~NMRPulseAnalyzed(){
   // I think the base class destructor is called... 
   delete[] fFREQ_zc;  
   delete[] fB_zc;  
}
//______________________________________________________________________________
void NMRPulseAnalyzed::ClearData(){
   fNumZeroCrossings = 0;
   fTimeStamp        = 0; 
   fAmpl             = 0;
   fNoiseRMS         = 0;
   fNumCycles        = 0;
   fSNR              = 0;
   fFREQ_fit         = 0; 
   fFREQ_ph          = 0; 
   fB_fit            = 0; 
   fB_ph             = 0; 
   for(int i=0;i<fNumPoints;i++){
      fTime[i]       = 0;
      fVoltage[i]    = 0;
      fVoltageErr[i] = 0;
   }
   for(int i=0;i<3;i++) fFREQ_zc[i] = 0; 
   for(int i=0;i<3;i++) fB_zc[i]    = 0; 
}
//______________________________________________________________________________
void NMRPulseAnalyzed::Print(){
   printf("================ NMR Pulse ================ \n");
   printf("PulseNumber        = %d         \n",fPulseNumber     );
   printf("TimeStamp          = %.7lf s    \n",fTimeStamp       );
   printf("NumPoints          = %d         \n",fNumPoints       );
   printf("NumZeroCrossings   = %d         \n",fNumZeroCrossings);
   printf("NumCycles          = %.3lf      \n",fNumCycles       );
   printf("Ampl               = %.7lf V    \n",fAmpl            );
   printf("NoiseRMS           = %.7lf V    \n",fNoiseRMS        );
   printf("SNR                = %.7lf      \n",fSNR             );
   printf("Freq (ZC midpoint) = %.7lf Hz   \n",fFREQ_zc[0]      );
   printf("Freq (ZC linear)   = %.7lf Hz   \n",fFREQ_zc[1]      );
   printf("Freq (ZC least sq) = %.7lf Hz   \n",fFREQ_zc[2]      );
   printf("Freq (Fit)         = %.7lf Hz   \n",fFREQ_fit        );
   printf("Freq (Phase Fit)   = %.7lf Hz   \n",fFREQ_ph         );
   printf("B Field (ZC midpoint) = %.7lf T \n",fB_zc[0]         );
   printf("B Field (ZC linear)   = %.7lf T \n",fB_zc[1]         );
   printf("B Field (ZC least sq) = %.7lf T \n",fB_zc[2]         );
   printf("B Field (Fit)         = %.7lf T \n",fB_fit           );
   printf("B Field (Phase Fit)   = %.7lf T \n",fB_ph            );
   // for(int i=0;i<fNumPoints;i++){
   //    std::cout << "time = " << fTime[i] << "\t" << "voltage = " << fVoltage[i] << "\t" << "voltage err = "<< fVoltageErr[i] << std::endl;
   // }
}
