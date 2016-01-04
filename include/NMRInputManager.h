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
 
      int fADCID,fADCChannelNumber;
      int fMonth,fDay,fYear;
      int fVerbosity,fOffsetOrder;
      int fNumRuns,fRunNumber,fStartRun,fEndRun,fNumPulses;
      int fADCNumSamples;

      double fStartTimeZC,fEndTimeZC;
      double fExpFreq,fSampleFreq,fLOFreq,fRFFreq; 
      double fBNCVoltage,fNTypeVoltage;
      double fADCSignalLength;

      int *fRunList;

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
      void PrintRunList(); 
      void PrintRunSummary(); 
      void GetInputParameters(const char *);
      void GetRunList(const char *);
      void ReadRunSummary(int); 

      void Update(const NMRInputManager &a); 
      void Update(const NMRInputManager *a); 
  
      void SetZeroCrossingStatus  (bool v)   { fUseZeroCrossing  = v; } 
      void SetTimeFitStatus       (bool v)   { fUseTimeFit       = v; } 
      void SetPhaseFitStatus      (bool v)   { fUsePhaseFit      = v; } 
      void SetIntegerCycleStatus  (bool v)   { fUseIntegerCycles = v; } 
      void SetADCID               (int v)    { fADCID            = v; } 
      void SetADCChannelNumber    (int v)    { fADCChannelNumber = v; } 
      void SetMonth               (int v)    { fMonth            = v; } 
      void SetDay                 (int v)    { fDay              = v; } 
      void SetYear                (int v)    { fYear             = v; } 
      void SetVerbosity           (int v)    { fVerbosity        = v; } 
      void SetOffsetOrder         (int v)    { fOffsetOrder      = v; } 
      void SetRunNumber           (int v)    { fRunNumber        = v; } 
      void SetStartRun            (int v)    { fStartRun         = v; } 
      void SetEndRun              (int v)    { fEndRun           = v; } 
      void SetNumPulses           (int v)    { fNumPulses        = v; } 
      void SetStartTimeZC         (double v) { fStartTimeZC      = v; } 
      void SetEndTimeZC           (double v) { fEndTimeZC        = v; } 
      void SetExpFreq             (double v) { fExpFreq          = v; } 
      void SetSampleFreq          (double v) { fSampleFreq       = v; } 
      void SetLOFreq              (double v) { fLOFreq           = v; } 
      void SetRFFreq              (double v) { fRFFreq           = v; } 
      void SetADCNumSamples       (int v)    { fADCNumSamples    = v; } 
      void SetADCSignalLength     (double v) { fADCSignalLength  = v; } 
      void SetBNCVoltage          (double v) { fBNCVoltage       = v; } 
      void SetNTypeVoltage        (double v) { fNTypeVoltage     = v; } 

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
      int GetADCChannelNumber()     const { return fADCChannelNumber; } 
      int GetVerbosity()            const { return fVerbosity;        } 
      int GetOffsetOrder()          const { return fOffsetOrder;      } 
      int GetNumSamples()           const { return fADCNumSamples;    } 
      int GetRun(int i)             const { return fRunList[i];       } 
      int GetNumberOfRuns()         const { return fNumRuns;          }  

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
