# generate a list of numbers from a string delimited by commas and dashes; 
# dashes imply that we want to include all numbers in between
# example: "25,56-60,90" yields a list containing: 25 56 57 58 59 60 90 

import csv

class StringParser:
    #_______________________________________________________________________ 
    def __init__(self,string):  
       self.fList      = [] 
       self.fString    = string
       self.fVerbosity = 0 
    #_______________________________________________________________________ 
    def Clear(self): 
       self.fList   = [] 
       self.fString = "" 
    #_______________________________________________________________________ 
    def GenerateList(self):  
       if self.fVerbosity>0: 
          print "String to parse is: %s" %(self.fString) 
       # first, split on the comma into a list  
       arr_com = self.fString.split(",")
       for entry_1 in arr_com:
          # now split each entry on a dash
          arr_dash = entry_1.split("-") 
          N = len(arr_dash)
          if N==1:
             # no range, add the single entry 
             self.fList.append(entry_1)
          else:  
             # find first and last entries,  
             # add each to the list 
             first = int( float(arr_dash[0]) )   
             last  = int( float(arr_dash[1]) )  
             for i in range(first,last+1):     # need the +1 since range works as first <= i < last  
                self.fList.append( str(i) )
       if self.fVerbosity>0: 
          print "Generated run list: "
          for entry in self.fList: 
             print entry 
#_______________________________________________________________________ 
class RunListReader:
   def __init__(self):
      self.List = [] 
   #_______________________________________________________________________ 
   def ReadFile(self,fileName,field1,field2):
      csvFile = csv.DictReader( open(fileName) )
      for row in csvFile: 
	 self.List.append(row[field1]+"-"+row[field2]) 
   #_______________________________________________________________________ 

