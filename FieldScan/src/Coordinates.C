void GetCoordinates(int slot,double &y,double &z); 
void GetCoordinates(int slot,int azi,double th0,double &x,double &y,double &z,double &th); 

void GetCoordinates(int slot,double &y,double &z){
   double y0    = 64.64;  // in mm 
   double yStep = 53.17;  // in mm 
   double zStep = 21.00;  // in mm 
   double slot_dbl = (double)slot;
   if(slot<=12){
      y = y0 + (slot_dbl-1.)*yStep;   
   }else if(slot>12){
      y = y0 + (24.-slot_dbl)*yStep;   
   } 
   z = slot_dbl*zStep; 
}
//______________________________________________________________________________
void GetCoordinates(int slot,int azi,double th0,double &x,double &y,double &z,double &th){
   double y0    = 0.00;  // in mm  
   double r     = 250.00;  // in mm 
   double zStep = 21.00;   // in mm 
   double DEG_TO_RAD = 0.0174533; 
   double slot_dbl = (double)slot;
   double hyp   = 0;
   double dth   = ( 360./32. );
   double thr   = 0; 
   th  = th0 + ( (double)(azi-1) )*dth; 
   thr = th*DEG_TO_RAD; 
   z   = (slot_dbl-1.)*zStep - 241.50; 
   hyp = TMath::Sqrt(r*r - z*z);   
   x   = hyp*TMath::Cos(thr); 
   y   = y0 + hyp*TMath::Sin(thr);  
}

