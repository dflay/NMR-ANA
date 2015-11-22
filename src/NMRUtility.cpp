#include "NMRUtility.h"
//______________________________________________________________________________
namespace NMRUtility{ 
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
}
