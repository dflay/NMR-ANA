#include "NMRUtility.h"
//______________________________________________________________________________
namespace NMRUtility{
  //______________________________________________________________________________
  std::string GetStringTimeStampFromUTC(unsigned long unix_time){
    time_t     utime = unix_time;
    struct tm  ts;
    char       buf[100];
    // Format time as "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&utime);
    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    std::string timeStamp = buf;
    return timeStamp;
  }
  //______________________________________________________________________________
  int AreEquivStrings(const char *s1,const char *s2){
    int ret_val = 0;
    int res = strcmp(s1,s2);
    if(res==0){
      ret_val = 1;
    }else if(res==1){
      ret_val = 0;
    }
    return ret_val;
  }
  //______________________________________________________________________________
  int PrintMessage(const char *funcName,const char *msg,const int lineNo){
    if(lineNo>=0){
      std::cout << "[" << funcName << "]: line " << lineNo << ": " << msg << std::endl;
    }else{
      std::cout << "[" << funcName << "]: " << msg << std::endl;
    }
    return 0;
  }
}
