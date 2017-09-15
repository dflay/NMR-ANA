#ifndef NMR_EVENT_H
#define NMR_EVENT_H

// data struct that attaches to the NMR-DAQ event struct 
 
typedef struct NMRDAQEvent { 
   unsigned long long timestamp;      // UTC timestamp [ns] 
   double temperature;                // from Keithley [Ohms]  
   double x;                          // radial coordinate [cm] 
   double y;                          // vertical coordinate [cm]
   double z;                          // azimuthal coordinate [cm] 
   int chNum;                         // channel number (mechanical switch port) 
   int pulseNum;                      // overall pulse number 

   NMRDAQEvent ():
     timestamp(0),
     temperature(0),
     x(0),
     y(0),
     z(0),
     chNum(0),
     pulseNum(0) {}
} NMRDAQEvent_t;

#endif 
