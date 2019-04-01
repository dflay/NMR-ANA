#ifndef UTIL_H
#define UTIL_H

#include <cstdlib> 
#include <cstdio>
#include <iostream>
#include <string> 
#include <string.h> 

namespace NMRUtility{
  std::string GetStringTimeStampFromUTC(unsigned long unix_time);
  int AreEquivStrings(const char *s1,const char *s2);
  int PrintMessage(const char *funcName,const char *msg,const int lineNo=-1);
}

#endif 
