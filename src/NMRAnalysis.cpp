#include "NMRAnalysis.h"
//______________________________________________________________________________
NMRAnalysis::NMRAnalysis(){
   fUseZeroCrossing = false; 
   fUseFit          = false;
   fUsePhaseFit     = false;
   fVerbosity       = 0;
   fFreq_ref        = 0; 
   ZeroCrossing     = new NMRZeroCrossing();
   fFileManager     = new NMRFileManager(); 
}
//______________________________________________________________________________
NMRAnalysis::~NMRAnalysis(){
   delete ZeroCrossing;
   delete fFileManager;  
}
//______________________________________________________________________________
void NMRAnalysis::InitializeAnalysis(){

   // general parameters 
   bool UseZC        = fFileManager->InputManager->GetZeroCrossingStatus();
   bool UseIntCycles = fFileManager->InputManager->GetIntegerCycleStatus(); 

   fVerbosity        = fFileManager->InputManager->GetVerbosity(); 
   fFreq_ref         = fFileManager->InputManager->GetRFFrequency(); 

   double tmin_zc    = fFileManager->InputManager->GetStartTimeZC();  
   double tmax_zc    = fFileManager->InputManager->GetEndTimeZC();  
   double ExpFreq    = fFileManager->InputManager->GetExpectedFrequency();  
   double SampleFreq = fFileManager->InputManager->GetSampleFrequency();  
  
   // zero crossing 
   if(UseZC){
      UseZeroCrossing(); 
      ZeroCrossing->SetVerbosity(fVerbosity); 
      ZeroCrossing->UseIntegerCycles(UseIntCycles); 
      ZeroCrossing->UseAll();  
      ZeroCrossing->UseTimeRange(); 
      ZeroCrossing->SetTimeRange(tmin_zc,tmax_zc);
      ZeroCrossing->SetSampleFrequency(SampleFreq); 
      ZeroCrossing->SetExpectedFrequency(ExpFreq); 
      ZeroCrossing->UpdateParameters(); 
      ZeroCrossing->SetupForRun(); 
   }

   // time fit 
   // TODO 
 
   // phase fit 
   // TODO 

}
//______________________________________________________________________________
void NMRAnalysis::UpdateAnalysis(){
   // update the analysis (if anything's changed in the FileManager, for instance) 
   InitializeAnalysis();
}
//______________________________________________________________________________
void NMRAnalysis::CalculateFrequency(NMRPulse *aPulse,NMRPulseAnalyzed *aPulseAnalyzed){

   int zc=0,zc_mid=0,zc_lin=0,zc_lsq=0;
   double nc=0,nc_mid=0,nc_lin=0,nc_lsq=0;
   double freq_mid=0,freq_lin=0,freq_lsq=0,freq_fit=0,freq_ph=0; 
   double freq_mid_ph=0,freq_lin_ph=0,freq_lsq_ph=0;   // from fitting the phase of the zero crossing time  

   // general pulse data 
   int pulse_num    = aPulse->GetPulseNumber(); 
   double ampl      = aPulse->GetAmplitude(); 
   double noise_rms = aPulse->GetNoiseRMS();
   double snr       = ampl/noise_rms; 
   double ts        = aPulse->GetTimeStamp(); 

   aPulseAnalyzed->SetPulseNumber(pulse_num);
   aPulseAnalyzed->SetAmplitude(ampl); 
   aPulseAnalyzed->SetNoiseRMS(noise_rms); 
   aPulseAnalyzed->SetSignalToNoiseRatio(snr); 
   aPulseAnalyzed->SetTimeStamp(ts); 

   // frequency analyses 

   if(fUseZeroCrossing){
      ZeroCrossing->Calculate(aPulse); 
      freq_mid    = ZeroCrossing->GetFrequencyMidpoint(); 
      freq_lin    = ZeroCrossing->GetFrequencyLinearInterp(); 
      freq_lsq    = ZeroCrossing->GetFrequencyLeastSquares();
      freq_mid_ph = ZeroCrossing->GetFrequencyMidpointPhaseFit(); 
      freq_lin_ph = ZeroCrossing->GetFrequencyLinearInterpPhaseFit(); 
      freq_lsq_ph = ZeroCrossing->GetFrequencyLeastSquaresPhaseFit();
      zc_mid      = ZeroCrossing->GetNumZeroCrossingsMidpoint(); 
      zc_lin      = ZeroCrossing->GetNumZeroCrossingsLinearInterp(); 
      zc_lsq      = ZeroCrossing->GetNumZeroCrossingsLeastSquares(); 
      nc_mid      = ZeroCrossing->GetNumCyclesMidpoint(); 
      nc_lin      = ZeroCrossing->GetNumCyclesLinearInterp(); 
      nc_lsq      = ZeroCrossing->GetNumCyclesLeastSquares(); 
      if( zc_mid== zc_lin && zc_mid==zc_lsq){
         // we're fine, do nothing
         zc = zc_mid; 
         nc = nc_mid; 
      }else{
         std::cout << "[NMRAnalysis::CalculateFrequency]: Number of zero crossings CHANGES based on t0 method (it shouldn't!)  Defaulting to midpoint numbers." << std::endl; 
         zc = zc_mid; 
         nc = nc_mid; 
     }
      aPulseAnalyzed->SetNumZeroCrossings(zc); 
      aPulseAnalyzed->SetNumCycles(nc); 
      aPulseAnalyzed->SetFrequencyZeroCrossingMidpoint(freq_mid); 
      aPulseAnalyzed->SetFrequencyZeroCrossingLinearInterp(freq_lin); 
      aPulseAnalyzed->SetFrequencyZeroCrossingLeastSquares(freq_lsq); 
      aPulseAnalyzed->SetFrequencyZeroCrossingMidpointPhaseFit(freq_mid_ph); 
      aPulseAnalyzed->SetFrequencyZeroCrossingLinearInterpPhaseFit(freq_lin_ph); 
      aPulseAnalyzed->SetFrequencyZeroCrossingLeastSquaresPhaseFit(freq_lsq_ph); 
   }

   if(fUseFit){
      // TODO: do stuff
      freq_fit = 0; 
   }

   if(fUsePhaseFit){
      // TODO: do stuff
      freq_ph = 0; 
   }

}
//______________________________________________________________________________
void NMRAnalysis::CalculateMagneticField(NMRPulseAnalyzed *aPulse){

   double freq_mid=0,freq_lin=0,freq_lsq=0;
   double freq_mid_ph=0,freq_lin_ph=0,freq_lsq_ph=0;
   double freq_fit=0,freq_ph=0;
   double B_mid=0,B_lin=0,B_lsq=0;
   double B_mid_ph=0,B_lin_ph=0,B_lsq_ph=0;
   double B_fit,B_ph=0; 

   if(fUseZeroCrossing){
      freq_mid    = aPulse->GetFrequencyZeroCrossingMidpoint();  
      freq_lin    = aPulse->GetFrequencyZeroCrossingLinearInterp();  
      freq_lsq    = aPulse->GetFrequencyZeroCrossingLeastSquares();
      B_mid       = CalculateField(freq_mid);  
      B_lin       = CalculateField(freq_lin);  
      B_lsq       = CalculateField(freq_lsq);  
      freq_mid_ph = aPulse->GetFrequencyZeroCrossingMidpointPhaseFit();  
      freq_lin_ph = aPulse->GetFrequencyZeroCrossingLinearInterpPhaseFit();  
      freq_lsq_ph = aPulse->GetFrequencyZeroCrossingLeastSquaresPhaseFit();
      B_mid_ph    = CalculateField(freq_mid_ph);  
      B_lin_ph    = CalculateField(freq_lin_ph);  
      B_lsq_ph    = CalculateField(freq_lsq_ph);  
      aPulse->SetFieldZeroCrossingMidpoint(B_mid); 
      aPulse->SetFieldZeroCrossingLinearInterp(B_lin); 
      aPulse->SetFieldZeroCrossingLeastSquares(B_lsq); 
      aPulse->SetFieldZeroCrossingMidpointPhaseFit(B_mid_ph); 
      aPulse->SetFieldZeroCrossingLinearInterpPhaseFit(B_lin_ph); 
      aPulse->SetFieldZeroCrossingLeastSquaresPhaseFit(B_lsq_ph); 
   }

   if(fUseFit){
      // TODO: do stuff
      freq_fit = 0; 
      B_fit    = CalculateField(freq_fit);  
      aPulse->SetFieldFit(B_fit); 
   }

   if(fUsePhaseFit){
      // TODO: do stuff
      freq_ph = 0; 
      B_ph    = CalculateField(freq_ph);  
      aPulse->SetFieldPhaseFit(B_ph); 
   }

}
//______________________________________________________________________________
double NMRAnalysis::CalculateField(double Freq_fid){
   double B0 = fFreq_ref/NMRConstants::gamma_1H;
   double B  = 0; 
   if(Freq_fid!=0) B = B0*(1. + Freq_fid/fFreq_ref); 
   return B;  
}
//______________________________________________________________________________
void NMRAnalysis::CalculateStatistics(NMRRun *aRun){

   // compute statistics on a run 

   const int N = aRun->GetNumPulses();  
   double *value = new double[N]; 

   // get mean amplitude
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseAmplitude(i); 
   double mean_ampl = NMRMath::GetMean(N,value); 
   double sig_ampl  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanAmplitude(mean_ampl); 
   aRun->SetSigmaAmplitude(sig_ampl); 
   // get mean RMS noise 
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseNoiseRMS(i); 
   double mean_noise_rms = NMRMath::GetMean(N,value); 
   double sig_noise_rms  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanNoiseRMS(mean_noise_rms); 
   aRun->SetSigmaNoiseRMS(sig_noise_rms); 
   // get mean SNR 
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseSignalToNoiseRatio(i); 
   double mean_snr = NMRMath::GetMean(N,value); 
   double sig_snr  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanSignalToNoiseRatio(mean_snr); 
   aRun->SetSigmaSignalToNoiseRatio(sig_snr); 
   // get mean freq (zc, midpoint)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyZeroCrossingMidpoint(i); 
   double mean_freq_zc_mid = NMRMath::GetMean(N,value); 
   double sig_freq_zc_mid  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyZeroCrossingMidpoint(mean_freq_zc_mid); 
   aRun->SetSigmaFrequencyZeroCrossingMidpoint(sig_freq_zc_mid); 
   // get mean freq (zc, linear interp)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyZeroCrossingLinearInterp(i); 
   double mean_freq_zc_lin = NMRMath::GetMean(N,value); 
   double sig_freq_zc_lin  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyZeroCrossingLinearInterp(mean_freq_zc_lin); 
   aRun->SetSigmaFrequencyZeroCrossingLinearInterp(sig_freq_zc_lin); 
   // get mean freq (zc, least squares)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyZeroCrossingLeastSquares(i); 
   double mean_freq_zc_lsq = NMRMath::GetMean(N,value); 
   double sig_freq_zc_lsq  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyZeroCrossingLeastSquares(mean_freq_zc_lsq); 
   aRun->SetSigmaFrequencyZeroCrossingLeastSquares(sig_freq_zc_lsq); 
   // get mean freq (zc, midpoint phase)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyZeroCrossingMidpointPhaseFit(i); 
   double mean_freq_zc_mid_ph = NMRMath::GetMean(N,value); 
   double sig_freq_zc_mid_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyZeroCrossingMidpointPhaseFit(mean_freq_zc_mid_ph); 
   aRun->SetSigmaFrequencyZeroCrossingMidpointPhaseFit(sig_freq_zc_mid_ph); 
   // get mean freq (zc, linear interp phase)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyZeroCrossingLinearInterpPhaseFit(i); 
   double mean_freq_zc_lin_ph = NMRMath::GetMean(N,value); 
   double sig_freq_zc_lin_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyZeroCrossingLinearInterpPhaseFit(mean_freq_zc_lin_ph); 
   aRun->SetSigmaFrequencyZeroCrossingLinearInterpPhaseFit(sig_freq_zc_lin_ph); 
   // get mean freq (zc, least squares phase)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyZeroCrossingLeastSquaresPhaseFit(i); 
   double mean_freq_zc_lsq_ph = NMRMath::GetMean(N,value); 
   double sig_freq_zc_lsq_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyZeroCrossingLeastSquaresPhaseFit(mean_freq_zc_lsq_ph); 
   aRun->SetSigmaFrequencyZeroCrossingLeastSquaresPhaseFit(sig_freq_zc_lsq_ph); 
   // get mean freq (fit)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyFit(i); 
   double mean_freq_fit = NMRMath::GetMean(N,value); 
   double sig_freq_fit  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyFit(mean_freq_fit); 
   aRun->SetSigmaFrequencyFit(sig_freq_fit); 
   // get mean freq (phase fit)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFrequencyPhaseFit(i); 
   double mean_freq_ph = NMRMath::GetMean(N,value); 
   double sig_freq_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFrequencyPhaseFit(mean_freq_ph); 
   aRun->SetSigmaFrequencyPhaseFit(sig_freq_ph); 
   // get mean b (zc, midpoint)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldZeroCrossingMidpoint(i); 
   double mean_b_zc_mid = NMRMath::GetMean(N,value); 
   double sig_b_zc_mid  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldZeroCrossingMidpoint(mean_b_zc_mid); 
   aRun->SetSigmaFieldZeroCrossingMidpoint(sig_b_zc_mid); 
   // get mean b (zc, linear interp)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldZeroCrossingLinearInterp(i); 
   double mean_b_zc_lin = NMRMath::GetMean(N,value); 
   double sig_b_zc_lin  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldZeroCrossingLinearInterp(mean_b_zc_lin); 
   aRun->SetSigmaFieldZeroCrossingLinearInterp(sig_b_zc_lin); 
   // get mean b (zc, least squares)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldZeroCrossingLeastSquares(i); 
   double mean_b_zc_lsq = NMRMath::GetMean(N,value); 
   double sig_b_zc_lsq  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldZeroCrossingLeastSquares(mean_b_zc_lsq); 
   aRun->SetSigmaFieldZeroCrossingLeastSquares(sig_b_zc_lsq); 
   // get mean b (zc, midpoint phase)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldZeroCrossingMidpointPhaseFit(i); 
   double mean_b_zc_mid_ph = NMRMath::GetMean(N,value); 
   double sig_b_zc_mid_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldZeroCrossingMidpointPhaseFit(mean_b_zc_mid_ph); 
   aRun->SetSigmaFieldZeroCrossingMidpointPhaseFit(sig_b_zc_mid_ph); 
   // get mean b (zc, linear interp phase)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldZeroCrossingLinearInterpPhaseFit(i); 
   double mean_b_zc_lin_ph = NMRMath::GetMean(N,value); 
   double sig_b_zc_lin_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldZeroCrossingLinearInterpPhaseFit(mean_b_zc_lin_ph); 
   aRun->SetSigmaFieldZeroCrossingLinearInterpPhaseFit(sig_b_zc_lin_ph); 
   // get mean b (zc, least squares phase)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldZeroCrossingLeastSquaresPhaseFit(i); 
   double mean_b_zc_lsq_ph = NMRMath::GetMean(N,value); 
   double sig_b_zc_lsq_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldZeroCrossingLeastSquaresPhaseFit(mean_b_zc_lsq_ph); 
   aRun->SetSigmaFieldZeroCrossingLeastSquaresPhaseFit(sig_b_zc_lsq_ph); 
   // get mean b (fit)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldFit(i); 
   double mean_b_fit = NMRMath::GetMean(N,value); 
   double sig_b_fit  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldFit(mean_b_fit); 
   aRun->SetSigmaFieldFit(sig_b_fit); 
   // get mean b (phase fit)  
   for(int i=0;i<N;i++) value[i] = aRun->GetPulseFieldPhaseFit(i); 
   double mean_b_ph = NMRMath::GetMean(N,value); 
   double sig_b_ph  = NMRMath::GetStandardDeviation(N,value); 
   aRun->SetMeanFieldPhaseFit(mean_b_ph); 
   aRun->SetSigmaFieldPhaseFit(sig_b_ph); 

   delete[] value; 

}

