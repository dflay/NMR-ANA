#define GAMMA_p   42.576E+6 

double GetMean(vector<double> x); 
double GetStandardDeviation(vector<double> x); 
double GetRMS(vector<double> x); 
double GetStandardErrorOfTheMean(vector<double> x); 

//______________________________________________________________________________
double GetMean(vector<double> x){
   const int N = x.size();
   double sum=0;
   for(int i=0;i<N;i++){
      sum += x[i];
   }
   double avg = sum/( (double)N ); 
   return avg;
}
//______________________________________________________________________________
double GetRMS(vector<double> x){
   const int N = x.size();
   double sum=0;
   for(int i=0;i<N;i++){
      sum += x[i]*x[i];
   }
   double avg = TMath::Sqrt(sum)/( (double)N ); 
   return avg;
}
//______________________________________________________________________________
double GetStandardDeviation(vector<double> x){
   const int N = x.size();
   double avg = GetMean(x); 
   double sum=0;
   for(int i=0;i<N;i++){
      sum += TMath::Power(x[i] - avg,2.);
   }
   double sd = TMath::Sqrt(sum/( (double)N ) ); 
   return sd;
}
//______________________________________________________________________________
double GetStandardErrorOfTheMean(vector<double> x){
   int N      = x.size(); 
   double sd  = GetStandardDeviation(x); 
   double err = sd/TMath::Sqrt(N);  
   return err;
}
