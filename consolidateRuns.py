#! /usr/bin/python
# consolidate NMR-ANA output into a single csv file for external processing 

import csv
import sys
from parse import StringParser 

num_args = len(sys.argv) 
if (num_args<3): 
  print "Usage: python {0} [nmr-daq run string] [midas run]".format(sys.argv[0]) 
  sys.exit(0)  

runStr   = sys.argv[1] 
midasRun = int(sys.argv[2])  

myStrParser = StringParser(runStr)
myStrParser.GenerateList()
runList = []
runList = myStrParser.fList

print "processing runs {0}".format(runList) 

# lists to store data 
run_number  = []
pulseNumber = []
ampl        = [] 
noise       = []
nzc         = []
ncy         = []
freqMid     = []
freqLin     = []
freqLsq     = []
freqMidPh   = []
freqLinPh   = []
freqLsqPh   = []

# header
header = "#runNumber,pulseNumber,ampl,noise,nzc,ncycles,freqMid,freqLin,freqLsq,freqMidPh,freqLinPh,freqLsqPh"

for run in runList: 
   path = "./output/run-{:05d}/results_pulse-stats.dat".format( int(run) ) 
   dataFile = open(path,'r')
   reader   = csv.reader(dataFile,delimiter='\t')
   for line in reader:
      for entry in line: 
         event = entry.split()
         run_number.append( int(event[0]) ) 
         pulseNumber.append( int(event[1]) )
         ampl.append( float(event[2]) )
         noise.append( float(event[3]) )
         nzc.append( int(event[4]) ) 
         ncy.append( float(event[5]) ) 
         freqMid.append( float(event[6]) ) 
         freqLin.append( float(event[7]) ) 
         freqLsq.append( float(event[8]) ) 
         freqMidPh.append( float(event[9]) ) 
         freqLinPh.append( float(event[10]) ) 
         freqLsqPh.append( float(event[11]) )
   dataFile.close() 

outpath = "midas_run-{:05d}.csv".format(midasRun) 

outFile = open(outpath,'w')
outFile.write(header+"\n") 
N = len(run_number) 
for i in xrange(0,N): 
   outFile.write("{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11} \n".format(run_number[i],pulseNumber[i],ampl[i],noise[i],nzc[i],ncy[i],freqMid[i],freqLin[i],freqLsq[i],freqMidPh[i],freqLinPh[i],freqLsqPh[i]) ) 
outFile.close() 
