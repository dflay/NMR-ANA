#! /usr/bin/python 

import Tkinter  
import os
from decimal import Decimal 
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
      self.Year         = ['Year',2015,2016,2017,2018] 

      MechSwName   = ['Mechanical Switch 1','Mechanical Switch 2','Mechanical Switch 3','Mechanical Switch 4']

      # ----------------------------------------------------------------------------------
      # header label
      self.RunInfoLabel_str = Tkinter.StringVar()
      self.RunInfoLabel_str.set("RUN PARAMETERS") 
      self.RunInfoLabel     = Tkinter.Label(self,textvariable=self.RunInfoLabel_str,anchor="w",font="Helvetica 14 bold") 
      self.RunInfoLabel.grid(column=ColumnOffset+0,row=RowOffset+0) 

      # ----------------------------------------------------------------------------------
      # date 
      self.DateLabel_str = Tkinter.StringVar() 
      self.DateLabel_str.set("Date") 
      self.DateLabel     = Tkinter.Label(self,textvariable=self.DateLabel_str,anchor="w") 
      self.DateLabel.grid(column=ColumnOffset+0,row=RowOffset+1)   

      # pull down menu
      mon_str   = Tkinter.StringVar()
      day_str   = Tkinter.StringVar()
      year_str  = Tkinter.StringVar()

      mon_str.set("Month") 
      day_str.set("Day") 
      year_str.set("Year") 

      # month 
      self.month_opt = Tkinter.OptionMenu(self,mon_str,*self.Month)
      self.month_opt.grid(column=ColumnOffset+1,row=RowOffset+1) 
      # day 
      self.day_opt = Tkinter.OptionMenu(self,day_str,*self.Day)
      self.day_opt.grid(column=ColumnOffset+2,row=RowOffset+1) 
      # year 
      self.year_opt_mech_3 = Tkinter.OptionMenu(self,year_str,*self.Year)
      self.year_opt_mech_3.grid(column=ColumnOffset+3,row=RowOffset+1) 

      # # ----------------------------------------------------------------------------------
      # start run info 
      # label
      self.StartRunLabel_str = Tkinter.StringVar()
      self.StartRunLabel_str.set("Start Run") 
      self.StartRunLabel     = Tkinter.Label(self,textvariable=self.StartRunLabel_str,anchor="w") 
      self.StartRunLabel.grid(column=ColumnOffset+0,row=RowOffset+2) 
      # entry field
      self.StartRunEntry     = Tkinter.StringVar()  
      self.StartRunEntryField = Tkinter.Entry(self,textvariable=self.StartRunEntry) 
      self.StartRunEntryField.grid(column=ColumnOffset+1,row=RowOffset+2,sticky='EW')
      # # ----------------------------------------------------------------------------------
      # end run info 
      # label
      self.EndRunLabel_str = Tkinter.StringVar()
      self.EndRunLabel_str.set("End Run") 
      self.EndRunLabel     = Tkinter.Label(self,textvariable=self.EndRunLabel_str,anchor="w") 
      self.EndRunLabel.grid(column=ColumnOffset+0,row=RowOffset+3) 
      # entry field
      self.EndRunEntry     = Tkinter.StringVar()  
      self.EndRunEntryField = Tkinter.Entry(self,textvariable=self.EndRunEntry) 
      self.EndRunEntryField.grid(column=ColumnOffset+1,row=RowOffset+3,sticky='EW')
      # # ----------------------------------------------------------------------------------
      # number of pulses 
      # label
      self.NPulsesLabel_str = Tkinter.StringVar()
      self.NPulsesLabel_str.set("Pulses Per Run") 
      self.NPulsesLabel     = Tkinter.Label(self,textvariable=self.NPulsesLabel_str,anchor="w") 
      self.NPulsesLabel.grid(column=ColumnOffset+0,row=RowOffset+4) 
      # entry field
      self.NPulsesEntry      = Tkinter.StringVar()  
      self.NPulsesEntryField = Tkinter.Entry(self,textvariable=self.NPulsesEntry) 
      self.NPulsesEntryField.grid(column=ColumnOffset+1,row=RowOffset+4,sticky='EW')

      # # ----------------------------------------------------------------------------------
      # expected frequency  
      # label
      self.ExpFreqLabel_str = Tkinter.StringVar()
      self.ExpFreqLabel_str.set("Expected Frequency") 
      self.ExpFreqLabel     = Tkinter.Label(self,textvariable=self.ExpFreqLabel_str,anchor="w") 
      self.ExpFreqLabel.grid(column=ColumnOffset+0,row=RowOffset+7) 
      # entry field
      self.unit_str_exp_freq = Tkinter.StringVar() 
      self.unit_str_exp_freq.set('kHz')
      self.ExpFreqEntry      = Tkinter.StringVar()  
      self.ExpFreqEntryField = Tkinter.Entry(self,textvariable=self.ExpFreqEntry) 
      self.ExpFreqEntryField.grid(column=ColumnOffset+1,row=RowOffset+7,sticky='EW')
      # pull down menu
      self.opt_exp_freq = Tkinter.OptionMenu(self,self.unit_str_exp_freq,*ExpFreqUnitChoices) 
      self.opt_exp_freq.grid(column=ColumnOffset+2,row=RowOffset+7) 
      # # ----------------------------------------------------------------------------------
      # sampling frequency  
      # label
      self.SampleFreqLabel_str = Tkinter.StringVar()
      self.SampleFreqLabel_str.set("Sampling Frequency") 
      self.SampleFreqLabel     = Tkinter.Label(self,textvariable=self.SampleFreqLabel_str,anchor="w") 
      self.SampleFreqLabel.grid(column=ColumnOffset+0,row=RowOffset+8) 
      # sampling frequency (value)  
      self.adc_freq_val = Tkinter.StringVar() 
      self.adc_freq_val.set('1')
      self.opt_adc_freq_val = Tkinter.OptionMenu(self,self.adc_freq_val,*FreqValues) 
      self.opt_adc_freq_val.grid(column=ColumnOffset+1,row=RowOffset+8)  
      # sampling frequency (unit)  
      self.unit_str_adc_freq = Tkinter.StringVar() 
      self.unit_str_adc_freq.set('MHz')
      self.opt_adc_freq = Tkinter.OptionMenu(self,self.unit_str_adc_freq,*FreqUnitChoices) 
      self.opt_adc_freq.grid(column=ColumnOffset+2,row=RowOffset+8)  
      # ----------------------------------------------------------------------------------
      # header label
      self.AnaOptLabel_str = Tkinter.StringVar()
      self.AnaOptLabel_str.set("ANALYSIS OPTIONS") 
      self.AnaOptLabel     = Tkinter.Label(self,textvariable=self.AnaOptLabel_str,anchor="w",font="Helvetica 14 bold") 
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
      self.UtilOptLabel     = Tkinter.Label(self,textvariable=self.UtilOptLabel_str,anchor="w",font="Helvetica 14 bold") 
      self.UtilOptLabel.grid(column=ColumnOffset+0,row=RowOffset+15) 
      # ----------------------------------------------------------------------------------
      # ADC ID  
      # label
      self.ADCLabel_str = Tkinter.StringVar()
      self.ADCLabel_str.set("Struck ADC ID") 
      self.ADCLabel     = Tkinter.Label(self,textvariable=self.ADCLabel_str,anchor="w") 
      self.ADCLabel.grid(column=ColumnOffset+0,row=RowOffset+16) 
      # pull down menu 
      self.adc_val = Tkinter.StringVar() 
      self.adc_val.set('3316')
      self.opt_adc_val = Tkinter.OptionMenu(self,self.adc_val,*self.ADCChoices) 
      self.opt_adc_val.grid(column=ColumnOffset+1,row=RowOffset+16)  
      # ----------------------------------------------------------------------------------
      # Offset correction   
      # label
      self.OffsetLabel_str = Tkinter.StringVar()
      self.OffsetLabel_str.set("Offset Correction Order") 
      self.OffsetLabel     = Tkinter.Label(self,textvariable=self.OffsetLabel_str,anchor="w") 
      self.OffsetLabel.grid(column=ColumnOffset+0,row=RowOffset+17) 
      # pull down menu 
      self.offset_val = Tkinter.StringVar() 
      self.offset_val.set('0')
      self.opt_offset_val = Tkinter.OptionMenu(self,self.offset_val,*self.OffsetChoices) 
      self.opt_offset_val.grid(column=ColumnOffset+1,row=RowOffset+17)  
      # ----------------------------------------------------------------------------------
      # Verbosity   
      # label
      self.VerbosityLabel_str = Tkinter.StringVar()
      self.VerbosityLabel_str.set("Verbosity") 
      self.VerbosityLabel     = Tkinter.Label(self,textvariable=self.VerbosityLabel_str,anchor="w") 
      self.VerbosityLabel.grid(column=ColumnOffset+0,row=RowOffset+18) 
      # pull down menu 
      self.verb_val = Tkinter.StringVar() 
      self.verb_val.set('0')
      self.opt_verb_val = Tkinter.OptionMenu(self,self.verb_val,*self.VerbChoices) 
      self.opt_verb_val.grid(column=ColumnOffset+1,row=RowOffset+18)  

      # ----------------------------------------------------------------------------------
      # make buttons 

      # load config 
      self.buttonImportConfig = Tkinter.Button(self,text=u"Import Configuration...",command=self.ImportConfig) 
      self.buttonImportConfig.grid(column=ColumnOffset+6,row=RowOffset+17,columnspan=4,sticky='EW') 
      # print config to files  
      self.buttonConfig = Tkinter.Button(self,text=u"Apply Configuration",command=self.PrintToFile) 
      self.buttonConfig.grid(column=ColumnOffset+6,row=RowOffset+18,columnspan=4,sticky='EW',) 
      # run  
      # self.buttonRun = Tkinter.Button(self,text=u"Run",command=self.RunDAQ) 
      self.buttonRun = Tkinter.Button(self,text=u"Run",command=self.CheckHardware) 
      self.buttonRun.grid(column=ColumnOffset+6,row=RowOffset+19,columnspan=4,sticky='EW') 
      # turn off FPGA and function generator  
      # self.buttonStop = Tkinter.Button(self,text=u"Stop") 
      # self.buttonStop.grid(column=ColumnOffset+5,row=RowOffset+19,columnspan=1,sticky='EW') 
      # quit the program 
      self.buttonQuit = Tkinter.Button(self,text=u"Quit",command=quit) 
      self.buttonQuit.grid(column=ColumnOffset+6,row=RowOffset+20,columnspan=4,sticky='EW') 

      # # ----------------------------------------------------------------------------------
      # # comments field  
      # self.entryCommentsVar = Tkinter.StringVar() 
      # self.entryCommentsVar.set(u"Enter run comments") 
      # self.entryComments    = Tkinter.Entry(self,textvariable=self.entryCommentsVar) 
      #                                  # anchor="w",fg="black",bg="white") 
      # self.entryComments.grid(column=ColumnOffset+7,row=RowOffset+6,columnspan=3,rowspan=2,sticky='EW') 

      # ----------------------------------------------------------------------------------
      # status field  
      self.StatusVariable = Tkinter.StringVar() 
      self.StatusVariable.set(u"Fill out the fields above before clicking 'Apply Configuration' and then 'Run.'  Be sure your entries are correct.") 
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
   def CheckHardware(self): 
       self.CHWindow = Tkinter.Toplevel(self)
       Message       = Tkinter.Label(self.CHWindow, text="Is everything powered on correctly?\nClick Yes to start the run.")
       Message.grid(column=0,row=0,sticky='ew') 
       # some buttons 
       yesButton     = Tkinter.Button(self.CHWindow, text='Yes',command=self.RunDAQ)
       yesButton.grid(column=0,row=2,columnspan=1) 
       # quit child window and return to root window
       # the button is optional here, simply use the corner x of the child window
       noButton = Tkinter.Button(self.CHWindow, text='No', command=self.CHWindow.destroy) 
       noButton.grid(column=0,row=3,columnspan=1) 
   def ImportConfig(self): 
       self.counter += 1
       self.LCWindow = Tkinter.Toplevel(self)
       self.LCWindow.wm_title("Import Configuration")
       # Label      = Tkinter.Label(self.LCWindow, text="This is window #%s" % self.counter)
       # Label.grid(column=0,row=0,sticky='ew') 
       Label = Tkinter.Label(self.LCWindow,text="Configuration",anchor="w") 
       Label.grid(column=0,row=1) 
       # # fpga 
       # fpgaLabel  = Tkinter.Label(self.LCWindow, text="FPGA",anchor="w")
       # fpgaLabel.grid(column=0,row=1)
       # fgLabel    = Tkinter.Label(self.LCWindow, text="Function Generator",anchor="w")
       # fgLabel.grid(column=0,row=2)
       # # adc 
       # adcLabel    = Tkinter.Label(self.LCWindow, text="ADC",anchor="w")
       # adcLabel.grid(column=0,row=3)
       # # utilities
       # utilLabel   = Tkinter.Label(self.LCWindow, text="Utilities",anchor="w")
       # utilLabel.grid(column=0,row=4)

       self.ConfVar = Tkinter.StringVar() 
       self.ConfVar.set("a-configuration.conf") 
       entryConf = Tkinter.Entry(self.LCWindow,textvariable=self.ConfVar); 
       entryConf.grid(column=1,row=1)  

       # # FPGA data 
       # self.fpgaFNVar = Tkinter.StringVar() 
       # self.fpgaFNVar.set("pulse-data.dat")  
       # entryFPGA = Tkinter.Entry(self.LCWindow,textvariable=self.fpgaFNVar)
       # entryFPGA.grid(column=1,row=1)
       # # Function generator data 
       # self.fgFNVar = Tkinter.StringVar() 
       # self.fgFNVar.set("sg382.dat") 
       # entryFuncGen = Tkinter.Entry(self.LCWindow,textvariable=self.fgFNVar)
       # entryFuncGen.grid(column=1,row=2)
       # # ADC data 
       # self.adcFNVar = Tkinter.StringVar() 
       # self.adcFNVar.set("struck_adc.dat") 
       # entryADC = Tkinter.Entry(self.LCWindow,textvariable=self.adcFNVar)
       # entryADC.grid(column=1,row=3)
       # # utility data 
       # self.utilFNVar = Tkinter.StringVar() 
       # self.utilFNVar.set("utilities.dat") 
       # entryUtil = Tkinter.Entry(self.LCWindow,textvariable=self.utilFNVar)
       # entryUtil.grid(column=1,row=4)
       # button to go get a file  
       confButton = Tkinter.Button(self.LCWindow, text='Choose file...', command=self.GetFileNameConf)
       confButton.grid(column=2,row=1,columnspan=1) 

       # fpgaButton = Tkinter.Button(self.LCWindow, text='Choose file...', command=self.GetFileNameFPGA)
       # fpgaButton.grid(column=2,row=1,columnspan=1) 
       # fgButton   = Tkinter.Button(self.LCWindow, text='Choose file...', command=self.GetFileNameFG)
       # fgButton.grid(column=2,row=2,columnspan=1) 
       # adcButton  = Tkinter.Button(self.LCWindow, text='Choose file...', command=self.GetFileNameADC)
       # adcButton.grid(column=2,row=3,columnspan=1) 
       # utilButton  = Tkinter.Button(self.LCWindow, text='Choose file...', command=self.GetFileNameUtil)
       # utilButton.grid(column=2,row=4,columnspan=1) 

       # some buttons 
       loadButton = Tkinter.Button(self.LCWindow, text='Load Data', command=self.LoadData)
       loadButton.grid(column=0,row=5,columnspan=3) 
       # quit child window and return to root window
       # the button is optional here, simply use the corner x of the child window
       closeButton = Tkinter.Button(self.LCWindow, text='Close Window', command=self.LCWindow.destroy) 
       closeButton.grid(column=0,row=6,columnspan=3) 
       # # update status banner 
       # self.StatusVariable.set("Importing configuration...") 
   def GetFileNameConf(self):
       initdir = self.MyHOME + "input/configs/" 
       fn = askopenfilename(initialdir=initdir) # show an "Open" dialog box and return the path to the file
       self.ConfVar.set(fn) 
   def GetFileNameFPGA(self):
       initdir = self.MyHOME + "input/configs/" 
       fn = askopenfilename(initialdir=initdir) # show an "Open" dialog box and return the path to the file
       self.fpgaFNVar.set(fn) 
   def GetFileNameFG(self):
       initdir = self.MyHOME + "input/configs/" 
       fn = askopenfilename(initialdir=initdir) # show an "Open" dialog box and return the path to the file
       self.fgFNVar.set(fn) 
   def GetFileNameADC(self):
       initdir = self.MyHOME + "input/configs/" 
       fn = askopenfilename(initialdir=initdir) # show an "Open" dialog box and return the path to the file
       self.adcFNVar.set(fn) 
   def GetFileNameUtil(self):
       initdir = self.MyHOME + "input/configs/" 
       fn = askopenfilename(initialdir=initdir) # show an "Open" dialog box and return the path to the file
       self.utilFNVar.set(fn) 
   def LoadData(self): 
       self.StatusVariable.set("Loading configuration...") 
       fn = self.ConfVar.get() 
       fileConf = open(fn,'r') 
       config_name = fileConf.readline().strip() 
       fileConf.close() 
       self.ConfVarLabel.set(config_name) 
       self.StatusVariable.set("Loading configuration...") 
       # general vars 
       eof   = "end_of_file" 
       start = "#"
       global_on_off = "global_on_off"
       fn_prefix = self.MyHOME + "input/configs/files/" 

       # fpga  
       mech_sw_1  = "mech_sw_1"  
       mech_sw_2  = "mech_sw_2"  
       mech_sw_3  = "mech_sw_3"  
       mech_sw_4  = "mech_sw_4" 
       rf_sw_1    = "rf_sw_1" 
       rf_sw_2    = "rf_sw_2" 
       rf_sw_3    = "rf_sw_3" 
       rf_gate    = "rf_gate"
       # fn = self.fpgaFNVar.get() 
       fn = fn_prefix + "pulse-data_" + self.ConfVarLabel.get() + ".dat" 
       fileFPGA = open(fn, 'r')
       for line in fileFPGA:
          entry = line.split() # puts every entry of a line in an array called entry
          # print entry 
          if entry[0]!=start and entry[0]!=eof: 
             if entry[0]==global_on_off: 
                if entry[1]=="on":  self.chk_global_var.set(1) 
                if entry[1]=="off": self.chk_global_var.set(0) 
             elif entry[0]==mech_sw_1: 
                self.entryMechOffsetVariable[0].set(entry[2])       
                self.entryMechDurationVariable[0].set(entry[3])      
                self.unit_str_mech[0].set(entry[4])
                if entry[1]=="on":  self.chk_var_mech[0].set(1)
                if entry[1]=="off": self.chk_var_mech[0].set(0)
             elif entry[0]==mech_sw_2: 
                self.entryMechOffsetVariable[1].set(entry[2])       
                self.entryMechDurationVariable[1].set(entry[3])      
                self.unit_str_mech[1].set(entry[4])
                self.chk_var_mech[1].set(entry[1])
                if entry[1]=="on":  self.chk_var_mech[1].set(1)
                if entry[1]=="off": self.chk_var_mech[1].set(0)
             elif entry[0]==mech_sw_3: 
                self.entryMechOffsetVariable[2].set(entry[2])       
                self.entryMechDurationVariable[2].set(entry[3])      
                self.unit_str_mech[2].set(entry[4])
                if entry[1]=="on":  self.chk_var_mech[2].set(1)
                if entry[1]=="off": self.chk_var_mech[2].set(0)
             elif entry[0]==mech_sw_4: 
                self.entryMechOffsetVariable[3].set(entry[2])       
                self.entryMechDurationVariable[3].set(entry[3])      
                self.unit_str_mech[3].set(entry[4])
                if entry[1]=="on":  self.chk_var_mech[3].set(1)
                if entry[1]=="off": self.chk_var_mech[3].set(0)
             if entry[0]==rf_sw_1: 
                self.entryRFOffsetVariable[0].set(entry[2])       
                self.entryRFDurationVariable[0].set(entry[3])      
                self.unit_str_rf[0].set(entry[4])
                if entry[1]=="on":  self.chk_var_rf[0].set(1)
                if entry[1]=="off": self.chk_var_rf[0].set(0)
             elif entry[0]==rf_sw_2: 
                self.entryRFOffsetVariable[1].set(entry[2])       
                self.entryRFDurationVariable[1].set(entry[3])      
                self.unit_str_rf[1].set(entry[4])
                if entry[1]=="on":  self.chk_var_rf[1].set(1)
                if entry[1]=="off": self.chk_var_rf[1].set(0)
             elif entry[0]==rf_sw_3: 
                self.entryRFOffsetVariable[2].set(entry[2])       
                self.entryRFDurationVariable[2].set(entry[3])      
                self.unit_str_rf[2].set(entry[4])
                if entry[1]=="on":  self.chk_var_rf[2].set(1)
                if entry[1]=="off": self.chk_var_rf[2].set(0)
             elif entry[0]==rf_gate:
                self.entryRFOffsetVariableGate.set(entry[2]) 
                self.entryRFDurationVariableGate.set(entry[3])  
                self.unit_str_rf_gate.set(entry[4])
                if entry[1]=="on":  self.chk_var_rf_gate.set(1)
                if entry[1]=="off": self.chk_var_rf_gate.set(0)
       fileFPGA.close()
       # function generator 
       bnc       = "bnc"
       ntype     = "ntype"
       freq      = "frequency"
       freq_val  = "0"
       freq_unit = "ND"
       volt_unit = "ND"
       # fn = self.fgFNVar.get() 
       fn = fn_prefix + "sg382_" + self.ConfVarLabel.get() + ".dat" 
       fileFG = open(fn, 'r')
       for line in fileFG:
          entry = line.split() # puts every entry of a line in an array called entry
          if entry[0]!=start and entry[0]!=eof: 
             if entry[0]==bnc: 
                self.entryFGBNCVoltVariable.set(entry[2]) 
                self.unit_str_volt_fg_bnc.set(entry[3]) 
                if entry[1]=="on":  self.chk_fg_bnc_var.set(1) 
                if entry[1]=="off": self.chk_fg_bnc_var.set(0) 
             elif entry[0]==ntype: 
                self.entryFGNTypeVoltVariable.set(entry[2]) 
                self.unit_str_volt_fg_ntype.set(entry[3]) 
                if entry[1]=="on":  self.chk_fg_ntype_var.set(1) 
                if entry[1]=="off": self.chk_fg_ntype_var.set(0) 
             elif entry[0]==freq: 
                freq_val  = entry[2]; 
                freq_unit = entry[3];  
       self.entryFGFreqVariable.set(freq_val)  
       self.unit_str_freq_fg.set(freq_unit) 
       fileFG.close() 
       # ADC 
       id_num        = "adc_id"
       ch_num        = "channel_number"
       nof           = "number_of_events"
       freq          = "frequency"
       ext_clk       = "external_clock"
       ext_freq_val  = 0
       ext_freq_unit = "ND"
       # fn = self.adcFNVar.get() 
       fn = fn_prefix + "struck_adc_" + self.ConfVarLabel.get() + ".dat" 
       fileADC = open(fn, 'r')
       for line in fileADC:
          entry = line.split() # puts every entry of a line in an array called entry
          if entry[0]!=start and entry[0]!=eof: 
             if entry[0]==id_num:  
                self.entryADCNumVariable.set(entry[1]) 
             elif entry[0]==ch_num: 
                self.entryADCchVariable.set(entry[1])
             elif entry[0]==nof: 
                self.entryADCPulseVariable.set(entry[1]) 
             elif entry[0]==freq: 
                freq_val      = entry[1]; 
                freq_unit     = entry[2]; 
             elif entry[0]==ext_clk: 
                ext_freq_val  = entry[1]; 
                ext_freq_unit = entry[2];
       if ext_freq_val>0: 
          self.adc_freq_val.set(ext_freq_val)
          self.unit_str_adc_freq.set(ext_freq_unit) 
          self.chk_adc_clk_type_var.set(1)
       elif ext_freq_val<=0: 
          self.adc_freq_val.set(freq_val)
          self.unit_str_adc_freq.set(freq_unit) 
          self.chk_adc_clk_type_var.set(0)
       fileADC.close() 
       # utilities 
       debug    = "debug_mode"
       verb     = "verbosity"
       test     = "test_mode"
       ref_freq = "rf_frequency"
       ref_freq_val = 0
       ref_freq_str = "0" 
       # fn = self.utilFNVar.get() 
       fn = fn_prefix + "utilities_" + self.ConfVarLabel.get() + ".dat" 
       fileUtil = open(fn, 'r')
       for line in fileUtil:
          entry = line.split() # puts every entry of a line in an array called entry
          # print entry 
          if entry[0]!=start and entry[0]!=eof: 
             if entry[0]==debug: 
                if entry[1]=="1": self.util_debug_val.set("on") 
                if entry[1]=="0": self.util_debug_val.set("off") 
             elif entry[0]==verb: 
                self.util_verb_val.set(entry[1]) 
             elif entry[0]==test: 
                self.util_test_val.set(entry[1]) 
             elif entry[0]==ref_freq: 
                ref_freq_val = float(entry[1]) 
       # convert to MHz (when would it ever not be?) 
       ref_freq_str = ref_freq_val/1E+6 
       self.entryUtilRefFreqVariable.set(ref_freq_str)  
       self.util_ref_freq_unit_val.set("MHz")   
       fileUtil.close()
       # update status bar 
       self.StatusVariable.set("Configuration loaded.") 
   def PrintToFile(self):   
       # init vars 
       fpga_header  = "# ID     on/off     time offset     pulse time     units"
       fg_header    = "# type   state      value           units"
       adc_header   = "# ID     value      units"
       util_header  = "# ID     value"
       EOF          = "end_of_file"
       ZERO         = "0" 
       NINETYNINE   = "99"
       MIN1         = "-1"
       blSTATE      = "--"
       ND           = "ND"
       mech_state   = [0,0,0,0] 
       rf_state     = [0,0,0,0] 
       global_str   = "none"  
       mech_list    = ["none","none","none","none"] 
       rf_list      = ["none","none","none","none"]
       eof_fpga_str = "%-20s %-20s %-20s %-20s %-20s" %(EOF,blSTATE,ZERO,MIN1,ND)
       eof_fg_str   = "%-20s %-20s %-20s %-20s" %(EOF,blSTATE,ZERO,ND)
       eof_adc_str  = "%-20s %-20s %-20s" %(EOF,ZERO,ND)
       eof_util_str = "%-20s %-20s " %(EOF,NINETYNINE)
       # grab values 
       # FPGA 
       global_str        = self.GetFPGAString(0,0)
       for i in xrange(0,3):  
           mech_list[i]  = self.GetFPGAString(1,i) 
           mech_state[i] = self.GetFPGAState(1,i) 
       for i in xrange(0,3):  
           rf_list[i]    = self.GetFPGAString(2,i) 
           rf_state[i]   = self.GetFPGAState(2,i) 
       tomco             = self.GetFPGAString(3,4)
       tomco_state       = self.GetFPGAState(3,0)
       # function generator 
       bnc_str         = self.GetFuncGenString(1)  
       ntype_str       = self.GetFuncGenString(2)  
       freq_str        = self.GetFuncGenString(3) 
       # ADC 
       adc_id_str      = self.GetADCString(1) 
       ch_num_str      = self.GetADCString(2) 
       pulse_num_str   = self.GetADCString(3) 
       sample_freq_str = self.GetADCString(4) 
       # signal_len_str  = self.GetADCString(5)
       extern_clk_str  = self.GetADCString(6) 
       # utilities
       debug_str       = self.GetUtilString(1)  
       verb_str        = self.GetUtilString(2)  
       test_str        = self.GetUtilString(3)  
       rf_str          = self.GetUtilString(4)  
       # comments
       com_str        = self.entryCommentsVar.get()  
       # get file names ready  
       self.prefix    = "input/configs/files/"
       # configuration file 
       self.conf_fn   = self.entryUtilFNVar.get() + ".conf"
       self.fpga_fn   = "pulse-data_" + self.entryUtilFNVar.get() + ".dat" # self.entryFPGAFNVar.get()
       self.fg_fn     = "sg382_"      + self.entryUtilFNVar.get() + ".dat" # self.entryFuncGenFNVar.get() 
       self.adc_fn    = "struck_adc_" + self.entryUtilFNVar.get() + ".dat" # self.entryADCFNVar.get()
       self.util_fn   = "utilities_"  + self.entryUtilFNVar.get() + ".dat" # self.entryADCFNVar.get()
       self.com_fn    = "comments_"   + self.entryUtilFNVar.get() + ".txt" 
       self.conf_path = self.MyHOME + "input/configs/" + self.conf_fn 
       self.fpga_path = "./" + self.prefix + self.fpga_fn 
       self.fg_path   = "./" + self.prefix + self.fg_fn 
       self.adc_path  = "./" + self.prefix + self.adc_fn 
       self.util_path = "./" + self.prefix + self.util_fn 
       self.com_path  = "./" + self.prefix + self.com_fn 
       confFile       = open(self.conf_path,"w") 
       fpgaFile       = open(self.fpga_path,"w")
       fgFile         = open(self.fg_path  ,"w")
       adcFile        = open(self.adc_path ,"w")
       utilFile       = open(self.util_path,"w")
       commentFile    = open(self.com_path ,"w") 
       # print to screen 
       # print "-----------------------------------------------------"
       # print self.fpga_fn 
       # print fpga_header
       # print global_str 
       # for i in xrange(0,3):
       #    if mech_state[i]: print mech_list[i] 
       # for i in xrange(0,3):   
       #    if rf_state[i]: print rf_list[i] 
       # if tomco_state: print tomco 
       # print eof_fpga_str
       # writing to the file  
       conf_label = self.entryUtilFNVar.get() 
       confFile.write(conf_label +"\n")
       fpgaFile.write(fpga_header+"\n")
       fpgaFile.write(global_str +"\n")
       for i in xrange(0,3):
          if mech_state[i]: fpgaFile.write( mech_list[i] +"\n") 
       for i in xrange(0,3):   
          if rf_state[i]: fpgaFile.write( rf_list[i] +"\n")  
       # if tomco_state: fpgaFile.write(tomco+"\n") 
       fpgaFile.write(tomco+"\n")   # always print the TOMCO information to file 
       fpgaFile.write(eof_fpga_str+"\n")  
       # print "-----------------------------------------------------"
       # print self.fg_fn 
       # print fg_header
       # print freq_str
       # print bnc_str
       # print ntype_str 
       # print eof_fg_str 
       # write to file 
       fgFile.write(fg_header +"\n") 
       fgFile.write(freq_str  +"\n")
       fgFile.write(bnc_str   +"\n")
       fgFile.write(ntype_str +"\n")
       fgFile.write(eof_fg_str+"\n") 
       # print "-----------------------------------------------------"
       # print self.adc_fn 
       # print adc_header
       # print pulse_num_str
       # print sample_freq_str
       # print signal_len_str 
       # print eof_adc_str 
       # write to file  
       adcFile.write(adc_header      +"\n")
       adcFile.write(adc_id_str      +"\n")
       adcFile.write(ch_num_str      +"\n")
       adcFile.write(pulse_num_str   +"\n")
       adcFile.write(sample_freq_str +"\n")
       # adcFile.write(signal_len_str  +"\n")
       adcFile.write(extern_clk_str  +"\n")
       adcFile.write(eof_adc_str     +"\n") 
       # utilities 
       utilFile.write(util_header  + "\n")        
       utilFile.write(debug_str    + "\n")        
       utilFile.write(verb_str     + "\n")        
       utilFile.write(test_str     + "\n")        
       utilFile.write(rf_str       + "\n")        
       utilFile.write(eof_util_str + "\n")        
       # comments
       commentFile.write(com_str+"\n") 
       # close the files 
       confFile.close() 
       fpgaFile.close() 
       fgFile.close() 
       adcFile.close()
       commentFile.close()  
       # update status banner 
       self.StatusVariable.set("Configuration printed to file.") 
   #----------------------------------------------------------------------------
   def GetFPGAString(self,type,index):
      # gather all values and put into a string  
      MechSwLabel = ['mech_sw_1','mech_sw_2','mech_sw_3','mech_sw_4']
      RFSwLabel   = ['rf_sw_1'  ,'rf_sw_2'  ,'rf_sw_3'  ,'rf_clear']
      state       = "off"
      units       = "ND" 
      t_offset    = "none" 
      t_duration  = "none" 
      # adjust array index  
      i = index   
      # get values
      if type==0:   # global on/off 
         if self.chk_global_var.get(): state = "on"
         label      = "global_on_off" 
         t_offset   = "0" 
         t_duration = "0"
      elif type==1:  # mechanical switch
         if self.chk_var_mech[i].get(): state = "on"
         label      = MechSwLabel[i]
         t_offset   = self.entryMechOffsetVariable[i].get()  
         t_duration = self.entryMechDurationVariable[i].get()  
         units      = self.unit_str_mech[i].get()
      elif type==2: # RF 
         if self.chk_var_rf[i].get(): state = "on"
         label      = RFSwLabel[i]
         t_offset   = self.entryRFOffsetVariable[i].get()  
         t_duration = self.entryRFDurationVariable[i].get()  
         units      = self.unit_str_rf[i].get()
      elif type==3: # TOMCO gate 
         if self.chk_var_rf_gate.get(): state = "on"
         label      = "rf_gate"
         t_offset   = self.entryRFOffsetVariableGate.get() 
         t_duration = self.entryRFDurationVariableGate.get() 
         units      = self.unit_str_rf_gate.get()
      # build string 
      if(units == "units"): units = "ND" 
      my_str = "%-20s %-20s %-20s %-20s %-20s" %(label,state,t_offset,t_duration,units) 
      return my_str  
   #----------------------------------------------------------------------------
   def GetFPGAState(self,type,index): 
      # get the state of the FPGA variable: is it on (1) or off (0)   
      # adjust array index  
      i = index 
      # our return variable  
      state = 0  
      # get values
      if type==0:   # global on/off 
         state = self.chk_global_var.get() 
      elif type==1: # mechanical switch
         state = self.chk_var_mech[i].get()
      elif type==2: # RF 
         state = self.chk_var_rf[i].get()
      elif type==3: # TOMCO gate 
         state = self.chk_var_rf_gate.get()
      return state 
   #----------------------------------------------------------------------------
   def GetFuncGenString(self,type):
      bnc_state       = "off"
      ntype_state     = "off"
      label           = "none"
      value           = "none"
      state           = "none"
      units           = "none"
      if self.chk_fg_bnc_var.get():   bnc_state   = "on"
      if self.chk_fg_ntype_var.get(): ntype_state = "on"
      freq            = self.entryFGFreqVariable.get()  
      freq_unit       = self.unit_str_freq_fg.get() 
      bnc_volt        = self.entryFGBNCVoltVariable.get()  
      bnc_volt_unit   = self.unit_str_volt_fg_bnc.get() 
      ntype_volt      = self.entryFGNTypeVoltVariable.get()  
      ntype_volt_unit = self.unit_str_volt_fg_ntype.get() 
      # bnc_freq        = self.entryFGBNCFreqVariable.get()  
      # ntype_freq      = self.entryFGNTypeFreqVariable.get()  
      # bnc_freq_unit   = self.unit_str_freq_fg_bnc.get() 
      # ntype_freq_unit = self.unit_str_freq_fg_ntype.get() 
      if type==1: 
         label = "bnc"
         value = bnc_volt 
         state = bnc_state 
         units = bnc_volt_unit 
      elif type==2: 
         label = "ntype"
         value = ntype_volt 
         state = ntype_state 
         units = ntype_volt_unit
      elif type==3:
         label = "frequency"
         value = freq 
         state = "--" 
         units = freq_unit 
      my_str = "%-20s %-20s %-20s %-20s" %(label,state,value,units)
      return my_str  
   #----------------------------------------------------------------------------
   def GetADCString(self,type): 
      adc_id_val = self.entryADCNumVariable.get() 
      ch_num     = self.entryADCchVariable.get()
      pulse_num  = self.entryADCPulseVariable.get() 
      freq       = self.adc_freq_val.get()
      # event_len  = self.entryADCLengthVariable.get()
      freq_unit  = "MHz"
      # event_unit = self.unit_str_adc_length.get() 
      label      = "none"
      value      = "none"
      unit       = "ND" 
      extern_clk = self.chk_adc_clk_type_var.get() 
      if type==1: 
         label = "adc_id"
         value = adc_id_val  
         unit  = "ND"
      elif type==2: 
         label = "channel_number"
         value = ch_num 
         unit  = "ND"
      elif type==3: 
         label = "number_of_events"
         value = pulse_num 
         unit  = "ND"
      elif type==4: 
         label = "frequency"
         value = freq
         unit  = freq_unit
      # elif type==5: 
      #    label = "signal_length"
      #    value = event_len 
      #    unit  = event_unit
      elif type==6:
         label = "external_clock"
         if extern_clk:     value = freq 
         if not extern_clk: value = "-" + freq 
         unit  = freq_unit 
      my_str   = "%-20s %-20s %-20s" %(label,value,unit)
      return my_str 
   #----------------------------------------------------------------------------
   def GetUtilString(self,type): 
      debug_str = self.util_debug_val.get() 
      debug_val = "0"
      verb_val  = self.util_verb_val.get() 
      test_val  = self.util_test_val.get()
      freq      = self.entryUtilRefFreqVariable.get()
      freq_unit = self.util_ref_freq_unit_val.get()
      freq_dbl  = float(freq) 
          
      if debug_str=="off": debug_val = "0"
      if debug_str=="on":  debug_val = "1"
     
      if freq_unit=="kHz": freq_dbl = freq_dbl*1.E+3  
      if freq_unit=="MHz": freq_dbl = freq_dbl*1.E+6  
      if freq_unit=="GHz": freq_dbl = freq_dbl*1.E+9  

      freq = freq_dbl

      if type==1:  
         label = "debug_mode"
         value = debug_val  
      elif type==2: 
         label = "verbosity"
         value = verb_val 
      elif type==3: 
         label = "test_mode"
         value = test_val 
      elif type==4: 
         label = "rf_frequency"
         value = freq
      my_str   = "%-20s %-20s" %(label,value)
      return my_str 
   #----------------------------------------------------------------------------
   def RunDAQ(self):  
      # run the DAQ: first create symbolic links to the current configuration,
      # then run the system (bash script that starts the C code)  
      HOME      = self.MyHOME 
      cd_input  = "cd " + HOME + "input/"
      cd_home   = "cd " + HOME
      symlink   = "ln -s " 
      # define the source files 
      fpga_src  = HOME + self.prefix + self.fpga_fn
      fg_src    = HOME + self.prefix + self.fg_fn 
      adc_src   = HOME + self.prefix + self.adc_fn 
      util_src  = HOME + self.prefix + self.util_fn 
      com_src   = HOME + self.prefix + self.com_fn 
      # define targets: note here that the names are hard-coded.  
      # this is done because these file names NEVER change
      fpga_tgt  = HOME + "input/" + "pulse-data.dat" 
      fg_tgt    = HOME + "input/" + "sg382.dat"
      adc_tgt   = HOME + "input/" + "struck_adc.dat"
      util_tgt  = HOME + "input/" + "utilities.dat"
      com_tgt   = HOME + "input/" + "comments.txt"
      # remove commands
      rm_fpga   = "rm " + fpga_tgt 
      rm_fg     = "rm " + fg_tgt 
      rm_adc    = "rm " + adc_tgt 
      rm_util   = "rm " + util_tgt 
      rm_com    = "rm " + com_tgt 
      # check for existing files 
      fpga_is_alive = os.path.isfile(fpga_tgt)
      fg_is_alive   = os.path.isfile(fg_tgt)
      adc_is_alive  = os.path.isfile(adc_tgt)
      util_is_alive = os.path.isfile(util_tgt)
      com_is_alive  = os.path.isfile(com_tgt)
      # delete current symbolic links if necessary 
      if fpga_is_alive: os.system( rm_fpga ) 
      if fg_is_alive:   os.system( rm_fg   ) 
      if adc_is_alive:  os.system( rm_adc  ) 
      if util_is_alive: os.system( rm_util ) 
      if com_is_alive:  os.system( rm_com  ) 
      # define the commands 
      fpga_cmd  = symlink + fpga_src + " " + fpga_tgt   # symbolic link for FPGA 
      fg_cmd    = symlink + fg_src   + " " + fg_tgt     # symbolic link for function generator  
      adc_cmd   = symlink + adc_src  + " " + adc_tgt    # symbolic link for ADC 
      util_cmd  = symlink + util_src + " " + util_tgt   # symbolic link for utilities 
      com_cmd   = symlink + com_src  + " " + com_tgt    # symbolic link for comments
      run_cmd   = "./run_nmr.sh"                        # runs the C code 
      # print fpga_cmd 
      # print fg_cmd 
      # print adc_cmd 
      # print run_cmd 
      # symbolically link files
      os.system(cd_input) 
      os.system(fpga_cmd)
      os.system(fg_cmd)
      os.system(adc_cmd)
      os.system(util_cmd)
      os.system(com_cmd)
      # check to see if commands succeeded 
      fpga_is_alive = os.path.isfile(fpga_tgt)
      fg_is_alive   = os.path.isfile(fg_tgt)
      adc_is_alive  = os.path.isfile(adc_tgt)
      util_is_alive = os.path.isfile(util_tgt)
      com_is_alive  = os.path.isfile(com_tgt)
      if fpga_is_alive: print "[NMRDAQ]: symbolic link from %s to %s created." % (fpga_src,fpga_tgt) 
      if fg_is_alive:   print "[NMRDAQ]: symbolic link from %s to %s created." % (fg_src  ,fg_tgt  )  
      if adc_is_alive:  print "[NMRDAQ]: symbolic link from %s to %s created." % (adc_src ,adc_tgt )  
      if util_is_alive: print "[NMRDAQ]: symbolic link from %s to %s created." % (util_src,util_tgt)   
      if com_is_alive:  print "[NMRDAQ]: symbolic link from %s to %s created." % (com_src ,com_tgt )  
      # cd back to main dir
      os.system(cd_home)
      # start the C code 
      self.StatusVariable.set("DAQ is running") 
      os.system(run_cmd) 
      self.StatusVariable.set("Acquisition complete.") 
#--------------------------------------------------------------------------------

if __name__ == "__main__": 
   app = daq(None) 
   app.title('NMR Analysis')
   app.mainloop()
