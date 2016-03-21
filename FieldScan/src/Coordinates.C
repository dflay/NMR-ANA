void GetCoordinates(int slot,double &y,double &z); 
void GetCoordinates(int r_dsv,int slot,int azi,double th0,double &x,double &y,double &z,double &th); 
void GetCoordinates20cm(int slot,int azi,double th0,double &x,double &y,double &z,double &th); 
void GetCoordinates50cm(int slot,int azi,double th0,double &x,double &y,double &z,double &th); 

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
void GetCoordinates(int r_dsv,int slot,int azi,double th0,double &x,double &y,double &z,double &th){
   if(r_dsv==20) GetCoordinates20cm(slot,azi,th0,x,y,z,th); 
   if(r_dsv==50) GetCoordinates50cm(slot,azi,th0,x,y,z,th); 
}
//______________________________________________________________________________
void GetCoordinates50cm(int slot,int azi,double th0,double &x,double &y,double &z,double &th){
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
//______________________________________________________________________________
void GetCoordinates20cm(int slot,int azi,double th0,double &x,double &y,double &z,double &th){
   double y0    = 0.00;  // in mm  
   double r     = 0.00;  // in mm 
   double DEG_TO_RAD = 0.0174533; 
   double slot_dbl = (double)slot;
   double hyp   = 0;
   double dth   = ( 360./32. );
   double thr   = 0; 
   // clear previous results
   x  = -1E+3;
   y  = -1E+3;
   z  = -1E+3; 
   th = -1E+3; 
   // azimuthal angle  
   th  = th0 + ( (double)(azi-1) )*dth; 
   thr = th*DEG_TO_RAD;
   // z coordinate  
   if(slot==1) z = -9.510565163E-02/1E-3; 
   if(slot==2) z = -8.090169944E-02/1E-3; 
   if(slot==3) z = -5.877852523E-02/1E-3; 
   if(slot==4) z = -3.090169944E-02/1E-3; 
   if(slot==5) z = -6.123233996E-18/1E-3; 
   if(slot==6) z =  3.090169944E-02/1E-3; 
   if(slot==7) z =  5.877852523E-02/1E-3; 
   if(slot==8) z =  8.090169944E-02/1E-3; 
   if(slot==9) z =  9.510565163E-02/1E-3; 
   // r coordinate 
   if(slot==1) r =  3.090169944e-02/1E-3; 
   if(slot==2) r =  5.877852523e-02/1E-3; 
   if(slot==3) r =  8.090169944e-02/1E-3; 
   if(slot==4) r =  9.510565163e-02/1E-3; 
   if(slot==5) r =  1.000000000e-01/1E-3; 
   if(slot==6) r =  9.510565163e-02/1E-3; 
   if(slot==7) r =  8.090169944e-02/1E-3; 
   if(slot==8) r =  5.877852523e-02/1E-3; 
   if(slot==9) r =  3.090169944e-02/1E-3; 
   x = r*TMath::Cos(thr);
   y = r*TMath::Sin(thr);
}

