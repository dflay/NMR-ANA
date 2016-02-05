#include "NMRAnalysis.h"
//______________________________________________________________________________
NMRAnalysis::NMRAnalysis(){
   fUseZeroCrossing = false; 
   fUseFit          = false;
   fUsePhaseFit     = false;
   fVerbosity       = 0; 
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
void NMRAnalysis::CalculateFrequency(NMRPulse *aPulse,NMRPulseAnalyzed *aPulseAnalyzed){

   int zc=0,zc_mid=0,zc_lin=0,zc_lsq=0;
   double nc=0,nc_mid=0,nc_lin=0,nc_lsq=0;
   double freq_mid=0,freq_lin=0,freq_lsq=0,freq_fit=0,freq_ph=0; 

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
      freq_mid = ZeroCrossing->GetFrequencyMidpoint(); 
      freq_lin = ZeroCrossing->GetFrequencyLinearInterp(); 
      freq_lsq = ZeroCrossing->GetFrequencyLeastSquares();
      zc_mid   = ZeroCrossing->GetNumZeroCrossingsMidpoint(); 
      zc_lin   = ZeroCrossing->GetNumZeroCrossingsLinearInterp(); 
      zc_lsq   = ZeroCrossing->GetNumZeroCrossingsLeastSquares(); 
      nc_mid   = ZeroCrossing->GetNumCyclesMidpoint(); 
      nc_lin   = ZeroCrossing->GetNumCyclesLinearInterp(); 
      nc_lsq   = ZeroCrossing->GetNumCyclesLeastSquares(); 
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
void NMRAnalysis::CalculateField(NMRPulseAnalyzed *aPulse){

   int zc=0,zc_mid=0,zc_lin=0,zc_lsq=0;
   double nc=0,nc_mid=0,nc_lin=0,nc_lsq=0;
   double freq_mid=0,freq_lin=0,freq_lsq=0,freq_fit=0,freq_ph=0;
   double B_mid=0,B_lin=0,B_lsq=0; 

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

   // field calculation 

   if(fUseZeroCrossing){
      freq_mid = aPulse->GetFrequencyZeroCrossingMidpoint();  
      freq_lin = aPulse->GetFrequencyZeroCrossingLinearInterp();  
      freq_lsq = aPulse->GetFrequencyZeroCrossingLeastSquares(); 
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

   delete[] value; 

}

