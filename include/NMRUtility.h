#ifndef UTIL_H
#define UTIL_H

#include <cstdlib> 
#include <cstdio>
#include <string> 
#include <string.h> 

namespace NMRUtility{
  std::string GetStringTimeStampFromUTC(unsigned long unix_time);
  int AreEquivStrings(const char *s1,const char *s2); 
}

#endif 
