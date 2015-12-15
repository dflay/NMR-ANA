#ifndef NMRINPUTMANAGER_H  
#define NMRINPUTMANAGER_H 

// keep track of the input file data 

#include <cstdlib>
#include <iostream>
#include <fstream> 
#include "NMRUtility.h"

class NMRInputManager{

   private:
      bool fUseZeroCrossing,fUseTimeFit,fUsePhaseFit,fUseIntegerCycles; 
 
      int fADCID;
      int fMonth,fDay,fYear;
      int fVerbosity,fOffsetOrder;
      int fRunNumber,fStartRun,fEndRun,fNumPulses;
      int fADCNumSamples; 

      double fStartTimeZC,fEndTimeZC;
      double fExpFreq,fSampleFreq,fLOFreq,fRFFreq; 
      double fBNCVoltage,fNTypeVoltage;
      double fADCSignalLength;

   public:
      // constructor and destructor 
      NMRInputManager();
      ~NMRInputManager();

      // copy constructors
      NMRInputManager(const NMRInputManager &a);
      NMRInputManager(const NMRInputManager *a);

      // assignment operator overload  
      NMRInputManager& operator=(const NMRInputManager &a);
      NMRInputManager* operator=(const NMRInputManager *a);

      void Print(); 
      void GetInputParameters(const char *);
      void ReadRunSummary(int); 
     
      bool GetZeroCrossingStatus()  const { return fUseZeroCrossing;  } 
      bool GetTimeFitStatus()       const { return fUseTimeFit;       } 
      bool GetPhaseFitStatus()      const { return fUsePhaseFit;      } 
      bool GetIntegerCycleStatus()  const { return fUseIntegerCycles; } 
 
      int GetMonth()                const { return fMonth;            } 
      int GetDay()                  const { return fDay;              } 
      int GetYear()                 const { return fYear;             } 
      int GetNumPulses()            const { return fNumPulses;        } 
      int GetRunNumber()            const { return fRunNumber;        } 
      int GetStartRunNumber()       const { return fStartRun;         } 
      int GetEndRunNumber()         const { return fEndRun;           } 
      int GetADCID()                const { return fADCID;            } 
      int GetVerbosity()            const { return fVerbosity;        } 
      int GetOffsetOrder()          const { return fOffsetOrder;      } 
      int GetNumSamples()           const { return fADCNumSamples;    } 

      double GetStartTimeZC()       const { return fStartTimeZC;      } 
      double GetEndTimeZC()         const { return fEndTimeZC;        } 
      double GetExpectedFrequency() const { return fExpFreq;          } 
      double GetSampleFrequency()   const { return fSampleFreq;       } 
      double GetLOFrequency()       const { return fLOFreq;           } 
      double GetRFFrequency()       const { return fRFFreq;           } 
      double GetSignalLength()      const { return fADCSignalLength;  } 
      double GetBNCVoltage()        const { return fBNCVoltage;       } 
      double GetNTypeVoltage()      const { return fNTypeVoltage;     } 

};

#endif  
