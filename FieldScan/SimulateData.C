// Create fake data to test field scan plotting code   

#include "TRandom.h"
#include "./src/Coordinates.C"
#include "./src/Math.C"
#include "./src/Graph.C"
#include "./src/Import.C"
#include "./src/Parse.C"
#include "./src/Generate.C"

void SimulateData(){

   gRandom->SetSeed(0);

   TString prefix = Form("./input/test/"); 

   double B  = 1.4513; 
   double dB = B*1E-6;  

   int RunMax = 5;
   int NPTS = 100;  

   int slot_a=0,slot_b=0; 

   int NA = 32; 
   int NS = 24; 

   int azi=0;
   int run=1; 

   double th0=0,th_a=0,th_b=0; 
   double x_a=0,y_a=0,z_a=0; 
   double x_b=0,y_b=0,z_b=0; 
 
   for(int i=0;i<NA;i++){                                   // azimuth loop 
      azi = i + 1;
      for(int j=0;j<NS-1;j=j+2){                            // run loop 
         slot_a = j + 1; 
         slot_b = slot_a + 1;
         GetCoordinates(slot_a,azi,th0,x_a,y_a,z_a,th_a); 
         GetCoordinates(slot_b,azi,th0,x_b,y_b,z_b,th_b); 
         GenerateRunList(prefix,run,slot_a,slot_b,azi); 
	 GenerateData(prefix,run,NPTS,B,dB);
         cout << "Run: " << run << endl;
         cout << "COORDINATES: " << endl;
         cout << "azimuth: " << azi << " (" << th_a << " deg)" << endl;
         cout << "slot a: " << slot_a << "\t x = " << Form("%.3lf",x_a) << " mm" << " y = " << Form("%.3lf",y_a) << " mm" << " z = " << Form("%.3lf",z_a) << " mm" << endl;
         cout << "slot b: " << slot_b << "\t x = " << Form("%.3lf",x_b) << " mm" << " y = " << Form("%.3lf",y_b) << " mm" << " z = " << Form("%.3lf",z_b) << " mm" << endl;
         cout << "=====================================================================================================" << endl;
	 run++;
      }
   }


}
