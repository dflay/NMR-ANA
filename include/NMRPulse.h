#ifndef NMRPULSE_H
#define NMRPULSE_H 

// a generic NMR pulse 

#include <cstdlib> 
#include <cstdio> 
#include <iostream> 

class NMRPulse{

   protected:                    // can access these if one inherits from NMRPulse 
      int fVerbosity; 
      int fNumPoints; 
      int fPulseNumber;
      double fAmpl,fNoiseRMS,fSNR,fTimeStamp;
      double *fTime,*fVoltage,*fVoltageErr; 

   public:
      // constructor and destructor 
      NMRPulse(int PulseNumber=0,int NPTS=1);
      ~NMRPulse();

      // copy constructors 
      NMRPulse(const NMRPulse &aPulse);         
      NMRPulse(const NMRPulse *aPulse);         

      // overload assignment operator  
      NMRPulse& operator=(const NMRPulse &aPulse);  
      NMRPulse* operator=(const NMRPulse *aPulse); 

      void Print();  
      void ClearData();
      void ClearVectorData();
      void SetNumPoints(int p);   
      void SetData(int N,double t[],double v[],double ev[]); 
      void SetDataPoint(int i,double t,double v,double ev); 
      void SetPulseNumber(int p)                             {fPulseNumber = p;     } 
      void SetTimeStamp(double t)                            {fTimeStamp   = t;     } 
      void SetAmplitude(double a)                            {fAmpl        = a;     }
      void SetNoiseRMS(double n)                             {fNoiseRMS    = n;     }
      void SetSignalToNoiseRatio(double snr)                 {fSNR         = snr;   }
      void SetVerbosity(int v)                               {fVerbosity   = v;     } 

      int GetNumPoints()                               const {return fNumPoints;    } 
      int GetPulseNumber()                             const {return fPulseNumber;  }  

      double GetAmplitude()                            const {return fAmpl;         }
      double GetNoiseRMS()                             const {return fNoiseRMS;     }
      double GetSignalToNoiseRatio()                   const {return fSNR;          }
      double GetTimeStamp()                            const {return fTimeStamp;    } 
      double GetTime(int i)                            const {return fTime[i];      } 
      double GetVoltage(int i)                         const {return fVoltage[i];   } 
      double GetVoltageErr(int i)                      const {return fVoltageErr[i];} 

}; 

#endif 
