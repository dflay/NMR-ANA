void CalculateB_rel(double B0,double B,double dB,double &Brel,double &dBrel); 

//______________________________________________________________________________
void CalculateB_rel(double B0,double B,double dB,double &Brel,double &dBrel){
   double ppm   = 1E-6;
   double ppb   = 1E-9;
   Brel         =  (B - B0)/B0/ppm;
   dBrel        = dB/B0/ppm;
}
