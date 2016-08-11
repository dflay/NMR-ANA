#include "../include/WeightedAverage.h"
//_________________________________________________________________
WeightedAverage::WeightedAverage(){
   Init();
}
//_________________________________________________________________
WeightedAverage::~WeightedAverage(){

}
//_________________________________________________________________
void WeightedAverage::Init(){
   fWAvg=0;
   fWAvgErr=0; 
}
//_________________________________________________________________
void WeightedAverage::ClearVectors(){
   fX.clear();
   fXErr.clear();
}
//_________________________________________________________________
void WeightedAverage::SetVectors(vector<double> x,vector<double> ex){
   int N = x.size();
   for(int i=0;i<N;i++){
      fX.push_back(x[i]);
      fXErr.push_back(ex[i]); 
   }
}
//_________________________________________________________________
void WeightedAverage::Calculate(){

   double num=0,den=0,err=0,err2=0,w=0; 

   int N = fX.size(); 
   for(int i=0;i<N;i++){
      err  = fXErr[i];
      err2 = err*err;
      w    = 1./err2; 
      if(err>0){ 
         den += w;  
         num += w*fX[i]; 
      }else{
         continue;
      }
   }

   if( (num!=0)&&(den!=0) ){
      fWAvg    = num/den; 
      fWAvgErr = sqrt(1.0/den); 
   }else{
      fWAvg    = 0;
      fWAvgErr = 0;
   }

}
