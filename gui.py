#! /usr/bin/python 

import os
import Tkinter  
from parse        import StringParser
from confmgr      import ConfigManager
from decimal      import Decimal 
from tkFileDialog import askopenfilename

#--------------------------------------------------------------------------------
class daq(Tkinter.Tk): 

   def __init__(self,parent): 
      Tkinter.Tk.__init__(self,parent)
      self.parent = parent # reference to the parent 
      self.initialize() 

   def initialize(self): 
      self.grid() 
 
      self.counter = 0 
      # self.MyHOME = "/home/gm2cal/Desktop/dflay/gui/"
      self.MyHOME = os.getcwd() + "/"  
      self.ConfVarLabel = Tkinter.StringVar()   

      # variables and lists  
      TickBox            = ""
      self.TimeChoices   = ['units','s','ms','us']
      self.DebugChoices  = ['off','on']
      self.ADCChoices    = ['3302','3316']
      self.ADCChChoices  = ['1','2' ,'3' ,'4' ,'5' ,'6' ,'7' ,'8',
                            '9','10','11','12','13','14','15','16']
      self.VerbChoices   = ['0','1','2','3','4']
      self.OffsetChoices = ['0','1','2','3','4']
      FreqValues         = ['1','10','25','50','100','125','250']
      ExpFreqUnitChoices = ['kHz','MHz']
      FreqUnitChoices    = ['MHz']
      VoltChoices        = ['units','Vpp','rms','dBm']
      RowOffset          = 0 
      ColumnOffset       = 0

      self.Month        = ['Month','Jan','Feb','Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec']
      self.Day          = ['Day',1,2,3,4,5,6,7,8,9,10,
                           11,12,13,14,15,16,17,18,19,20,
                           21,22,23,24,25,26,27,28,29,30,31]
      self.Year         = ['Year',2015,2016,2017,2018,2019,2020] 

      # ----------------------------------------------------------------------------------
      # header label
      self.RunInfoLabel_str = Tkinter.StringVar()
      self.RunInfoLabel_str.set("RUN PARAMETERS") 
      self.RunInfoLabel     = Tkinter.Label(self,textvariable=self.RunInfoLabel_str,anchor="w",font="Helvetica 12 bold") 
      self.RunInfoLabel.grid(column=ColumnOffset+0,row=RowOffset+0) 

      # ----------------------------------------------------------------------------------
      # date 
      self.DateLabel_str = Tkinter.StringVar() 
      self.DateLabel_str.set("Date") 
      self.DateLabel     = Tkinter.Label(self,textvariable=self.DateLabel_str,anchor="w") 
      self.DateLabel.grid(column=ColumnOffset+0,row=RowOffset+1)   

      # pull down menu
      self.mon_str   = Tkinter.StringVar()
      self.day_str   = Tkinter.StringVar()
      self.year_str  = Tkinter.StringVar()

      self.mon_str.set("Month") 
      self.day_str.set("Day") 
      self.year_str.set("Year") 

      # month 
      self.month_opt = Tkinter.OptionMenu(self,self.mon_str,*self.Month)
      self.month_opt.grid(column=ColumnOffset+1,row=RowOffset+1) 
      # day 
      self.day_opt = Tkinter.OptionMenu(self,self.day_str,*self.Day)
      self.day_opt.grid(column=ColumnOffset+2,row=RowOffset+1) 
      # year 
      self.year_opt = Tkinter.OptionMenu(self,self.year_str,*self.Year)
      self.year_opt.grid(column=ColumnOffset+3,row=RowOffset+1) 

      # # ----------------------------------------------------------------------------------
      # start run info 
      # label
      self.RunLabel_str  = Tkinter.StringVar()
      self.RunLabel_str.set("Run Range") 
      self.RunLabel      = Tkinter.Label(self,textvariable=self.RunLabel_str,anchor="w") 
      self.RunLabel.grid(column=ColumnOffset+0,row=RowOffset+2) 
      # entry field
      self.RunEntry      = Tkinter.StringVar()  
      self.RunEntryField = Tkinter.Entry(self,textvariable=self.RunEntry) 
      self.RunEntryField.grid(column=ColumnOffset+1,row=RowOffset+2,sticky='EW')
  
      # ----------------------------------------------------------------------------------
      # header label
      self.AnaOptLabel_str = Tkinter.StringVar()
      self.AnaOptLabel_str.set("ANALYSIS OPTIONS") 
      self.AnaOptLabel     = Tkinter.Label(self,textvariable=self.AnaOptLabel_str,anchor="w",font="Helvetica 12 bold") 
      self.AnaOptLabel.grid(column=ColumnOffset+0,row=RowOffset+9) 
      # # ----------------------------------------------------------------------------------
      # start time  
      # label
      self.TStartLabel_str = Tkinter.StringVar()
      self.TStartLabel_str.set("Start Time") 
      self.TStartLabel     = Tkinter.Label(self,textvariable=self.TStartLabel_str,anchor="w") 
      self.TStartLabel.grid(column=ColumnOffset+0,row=RowOffset+10) 
      # entry field
      self.TStartEntry      = Tkinter.StringVar()  
      self.TStartEntryField = Tkinter.Entry(self,textvariable=self.TStartEntry) 
      self.TStartEntryField.grid(column=ColumnOffset+1,row=RowOffset+10,sticky='EW')
      # pull down menu 
      self.tstart_unit_val = Tkinter.StringVar() 
      self.tstart_unit_val.set('s')
      self.opt_tstart_unit_val = Tkinter.OptionMenu(self,self.tstart_unit_val,*self.TimeChoices) 
      self.opt_tstart_unit_val.grid(column=ColumnOffset+2,row=RowOffset+10)  
      # ----------------------------------------------------------------------------------
      # end time  
      # label
      self.TEndLabel_str = Tkinter.StringVar()
      self.TEndLabel_str.set("End Time") 
      self.TEndLabel     = Tkinter.Label(self,textvariable=self.TEndLabel_str,anchor="w") 
      self.TEndLabel.grid(column=ColumnOffset+0,row=RowOffset+11) 
      # entry field
      self.TEndEntry      = Tkinter.StringVar()  
      self.TEndEntryField = Tkinter.Entry(self,textvariable=self.TEndEntry) 
      self.TEndEntryField.grid(column=ColumnOffset+1,row=RowOffset+11,sticky='EW')
      # pull down menu 
      self.tend_unit_val = Tkinter.StringVar() 
      self.tend_unit_val.set('s')
      self.opt_tend_unit_val = Tkinter.OptionMenu(self,self.tend_unit_val,*self.TimeChoices) 
      self.opt_tend_unit_val.grid(column=ColumnOffset+2,row=RowOffset+11)  
      # ----------------------------------------------------------------------------------
      # Zero crossing (check box)  
      # label
      self.ZeroCrossingLabel_str = Tkinter.StringVar()
      self.ZeroCrossingLabel_str.set("Zero Crossing") 
      self.ZeroCrossingLabel     = Tkinter.Label(self,textvariable=self.ZeroCrossingLabel_str,anchor="w") 
      self.ZeroCrossingLabel.grid(column=ColumnOffset+0,row=RowOffset+12) 
      # check box  
      self.zc_chk_var = Tkinter.IntVar()
      self.zc_chk = Tkinter.Checkbutton(self,text=TickBox,variable=self.zc_chk_var) 
      self.zc_chk.grid(column=ColumnOffset+1,row=RowOffset+12)
      # # ----------------------------------------------------------------------------------
      # Time Fit (check box)  
      # label
      self.TimeFitLabel_str = Tkinter.StringVar()
      self.TimeFitLabel_str.set("Time Fit") 
      self.TimeFitLabel     = Tkinter.Label(self,textvariable=self.TimeFitLabel_str,anchor="w") 
      self.TimeFitLabel.grid(column=ColumnOffset+0,row=RowOffset+13) 
      # check box  
      self.time_fit_chk_var = Tkinter.IntVar()
      self.time_fit_chk = Tkinter.Checkbutton(self,text=TickBox,variable=self.time_fit_chk_var) 
      self.time_fit_chk.grid(column=ColumnOffset+1,row=RowOffset+13)
      # # ----------------------------------------------------------------------------------
      # Phase Fit (check box)  
      # label
      self.PhaseFitLabel_str = Tkinter.StringVar()
      self.PhaseFitLabel_str.set("Phase Fit") 
      self.PhaseFitLabel     = Tkinter.Label(self,textvariable=self.PhaseFitLabel_str,anchor="w") 
      self.PhaseFitLabel.grid(column=ColumnOffset+0,row=RowOffset+14) 
      # check box  
      self.phase_fit_chk_var = Tkinter.IntVar()
      self.phase_fit_chk = Tkinter.Checkbutton(self,text=TickBox,variable=self.phase_fit_chk_var) 
      self.phase_fit_chk.grid(column=ColumnOffset+1,row=RowOffset+14)
      # ----------------------------------------------------------------------------------
      # header label
      self.UtilOptLabel_str = Tkinter.StringVar()
      self.UtilOptLabel_str.set("UTILITY OPTIONS") 
      self.UtilOptLabel     = Tkinter.Label(self,textvariable=self.UtilOptLabel_str,anchor="w",font="Helvetica 12 bold") 
      self.UtilOptLabel.grid(column=ColumnOffset+0,row=RowOffset+15) 
 
      # ----------------------------------------------------------------------------------
      # Offset correction   
      # label
      self.OffsetLabel_str = Tkinter.StringVar()
      self.OffsetLabel_str.set("Offset Correction Order") 
      self.OffsetLabel     = Tkinter.Label(self,textvariable=self.OffsetLabel_str,anchor="w") 
      self.OffsetLabel.grid(column=ColumnOffset+0,row=RowOffset+18) 
      # pull down menu 
      self.offset_val = Tkinter.StringVar() 
      self.offset_val.set('0')
      self.opt_offset_val = Tkinter.OptionMenu(self,self.offset_val,*self.OffsetChoices) 
      self.opt_offset_val.grid(column=ColumnOffset+1,row=RowOffset+18)  
      # ----------------------------------------------------------------------------------
      # Verbosity   
      # label
      self.VerbosityLabel_str = Tkinter.StringVar()
      self.VerbosityLabel_str.set("Verbosity") 
      self.VerbosityLabel     = Tkinter.Label(self,textvariable=self.VerbosityLabel_str,anchor="w") 
      self.VerbosityLabel.grid(column=ColumnOffset+0,row=RowOffset+19) 
      # pull down menu 
      self.verb_val = Tkinter.StringVar() 
      self.verb_val.set('0')
      self.opt_verb_val = Tkinter.OptionMenu(self,self.verb_val,*self.VerbChoices) 
      self.opt_verb_val.grid(column=ColumnOffset+1,row=RowOffset+19)  

      # ----------------------------------------------------------------------------------
      # make buttons 

      # print config to files  
      self.buttonConfig = Tkinter.Button(self,text=u"Apply Configuration",command=self.PrintToFile) 
      self.buttonConfig.grid(column=ColumnOffset+6,row=RowOffset+18,columnspan=4,sticky='EW',) 
      # run  
      self.buttonRun = Tkinter.Button(self,text=u"Analyze",command=self.RunDAQ) 
      # self.buttonRun = Tkinter.Button(self,text=u"Calculate",command=self.CheckHardware) 
      self.buttonRun.grid(column=ColumnOffset+6,row=RowOffset+19,columnspan=4,sticky='EW') 
      # quit the program 
      self.buttonQuit = Tkinter.Button(self,text=u"Quit",command=quit) 
      self.buttonQuit.grid(column=ColumnOffset+6,row=RowOffset+20,columnspan=4,sticky='EW') 

      # ----------------------------------------------------------------------------------
      # status field  
      self.StatusVariable = Tkinter.StringVar() 
      self.StatusVariable.set(u"Fill out the fields above before clicking 'Apply Configuration' and then 'Analyze.' ") 
      self.Status  = Tkinter.Label(self,textvariable=self.StatusVariable,
                                   anchor="w",fg="white",bg="blue") 
      self.Status.grid(column=ColumnOffset+0,row=RowOffset+24,columnspan=10,sticky='ew') 
      # ----------------------------------------------------------------------------------
      # sizing details 
      self.grid_columnconfigure(0,weight=1)  
      # set so that you can only resize horizontally 
      # self.resizable(True,False)  # horizontal resizing 
      # self.resizable(False,True)  # vertical resizing 
      # self.resizable(True,True)   # horizontal and vertical resizing 
      self.resizable(False,False)   # no resizing  
      # restrict window size to one size 
      self.update()
      self.geometry(self.geometry()) 
      # auto-select the text field upon an event 
      # self.entry.focus_set()
      # self.entry.selection_range(0,Tkinter.END) 
      # ----------------------------------------------------------------------------------

      # ----------------------------------------------------------------------------------
      # event actions
   def PrintToFile(self):   
       # init vars 
       header  = "# ID \t value"
       EOF          = "end_of_file"
       NINETYNINE   = "99"
       eof_str      = "%-20s    %-20s" %(EOF,NINETYNINE)
       # grab values 
       # date
       month        = "" 
       mon_val      = self.mon_str.get()
       if mon_val == "Jan": month = "1" 
       if mon_val == "Feb": month = "2" 
       if mon_val == "Mar": month = "3" 
       if mon_val == "Apr": month = "4" 
       if mon_val == "May": month = "5" 
       if mon_val == "Jun": month = "6" 
       if mon_val == "Jul": month = "7" 
       if mon_val == "Aug": month = "8" 
       if mon_val == "Sep": month = "9" 
       if mon_val == "Oct": month = "10" 
       if mon_val == "Nov": month = "11" 
       if mon_val == "Dec": month = "12" 
       day          = self.day_str.get()
       year         = self.year_str.get()
       # run range
       # convert to a regular string, don't use StringVar in the class StringParser
       run_str      = str( self.RunEntry.get() )   
       # print run_str 
       myStrParser  = StringParser(run_str) 
       myStrParser.GenerateList() 
       RunList = [] 
       RunList = myStrParser.fList  
       # start and end times of analysis 
       t_start      = self.TStartEntry.get() 
       t_start_dbl  = float(t_start) 
       t_start_unit = self.tstart_unit_val.get() 
       t_end        = self.TEndEntry.get() 
       t_end_dbl    = float(t_end) 
       t_end_unit   = self.tend_unit_val.get() 
       # make adjustments for units 
       if t_start_unit == "ms": 
          t_start_dbl = t_start_dbl*1E-3 
       elif t_start_unit == "us": 
          t_start_dbl = t_start_dbl*1E-6 
       if t_end_unit == "ms": 
          t_end_dbl = t_end_dbl*1E-3 
       elif t_end_unit == "us": 
          t_end_dbl = t_end_dbl*1E-6 
       # utilities  
       verb    = self.verb_val.get()                   # verbosity 
       offset  = self.offset_val.get()                 # offset correction order  
       # analysis options  
       zc_status        = self.zc_chk_var.get()        # zero crossing 
       time_fit_status  = self.time_fit_chk_var.get()  # time fit 
       phase_fit_status = self.phase_fit_chk_var.get() # phase fit 
       # build strings for parameter file 
       line1            = "month                   %s"   %(month)
       line2            = "day                     %s"   %(day)
       line3            = "year                    %s"   %(year)
       line4            = "t_start                 %.2E" %(t_start_dbl)
       line5            = "t_end                   %.2E" %(t_end_dbl)
       line6            = "verbosity               %s"   %(verb)
       line7            = "offset_correction_order %s"   %(offset)
       line8            = "zero_crossing           %d"   %(zc_status)
       line9            = "time_fit                %d"   %(time_fit_status)
       line10           = "phase_fit               %d"   %(phase_fit_status)
       paramList        = [header,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,eof_str] 
       # get file names ready  
       param_fn         = "parameters.dat"
       run_fn           = "runlist.dat"
       self.prefix      = "input/"
       paramFile_path   = "./" + self.prefix + param_fn
       runFile_path     = "./" + self.prefix + run_fn
       # open files 
       paramFile        = open(paramFile_path,"w") 
       runFile          = open(runFile_path  ,"w") 
       # print to screen 
       # for entry in paramList: 
       #    print entry 
       # for entry in RunList: 
       #    print entry 
       # writing to file 
       for entry in paramList: 
          paramFile.write(entry+"\n")
       for entry in RunList: 
          runFile.write(entry+"\n") 
       # close files 
       paramFile.close() 
       runFile.close() 
   #----------------------------------------------------------------------------
   def RunDAQ(self): 
      run_cmd = "./nmr_ana" 
      # start the C code 
      self.StatusVariable.set("Running calculations...") 
      os.system(run_cmd) 
      self.StatusVariable.set("Analysis complete.") 
#--------------------------------------------------------------------------------

if __name__ == "__main__": 
   app = daq(None) 
   app.title('NMR Analysis')
   app.mainloop()
