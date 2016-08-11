#include "./src/Coordinates.C"
#include "./src/Math.C"
#include "./src/Graph.C" 

#define GAMMA_p   42.576E+6 

double FREQ_REF = 61.9277E+6; 

void ParseData(int run,vector<double> Ampl,vector<double> B,vector<double> &B1,vector<double> &B2); 
void ParseDataAlt(int run,vector<double> Ampl,vector<double> Noise,vector<double> B,vector<double> &B1,vector<double> &B2); 
void ImportData2(TString inpath,int Run,vector<double> &Ampl,vector<double> &Noise);
void ImportData(TString inpath,int RunNumber,vector<double> &B); 
void CalculateB_rel(double B0,double B,double dB,double &Brel,double &dBrel); 
void DeleteZeroes(vector<double> &v); 

struct FieldData{
   double x;
   double y;
   double z;
   double B;
   double dB; 
};

void FieldScan(){

   int RunStart=8;
   int RunEnd=31;

   vector<double> Ampl,Noise;
   vector<double> Y1,Y2; 
   vector<double> Z1,Z2; 
   vector<double> B,B1,B2; 
   vector<double> B1R,dB1R;  
   vector<double> B1A,dB1A;  
   vector<double> B2R,dB2R;  
   vector<double> B2A,dB2A;  

   TString inpath_1 = Form("./output/2016/02_16/02_05_16/results_pulse-stats-field.dat");
   TString inpath_2 = Form("./output/2016/02_16/02_05_16/results_pulse-stats.dat");

   int cntr=0; 
   double z_offset = 0;
   double y_val_1=0,z_val_1=0;
   double y_val_2=0,z_val_2=0;

   double z_start = -241.5; // in mm 

   double y1=0,z1=0,y2=0,z2=0;
   GetCoordinates(1,y1,z1);  
   GetCoordinates(2,y2,z2);  

   cout << "Probe 1 y = " << y1 << "\t" << "z = " << z1 << " mm" << endl;
   cout << "Probe 2 y = " << y2 << "\t" << "z = " << z2 << " mm" << endl;

   double B0 = FREQ_REF/GAMMA_p; 
   double B1_avg=0,B1_err=0;
   double B2_avg=0,B2_err=0;
   double B1_rel=0,B1_rel_err=0;
   double B2_rel=0,B2_rel_err=0;

   cout << "REFERENCE: F = " << FREQ_REF/1E+6 << " MHz, B = " << B0 << " T" << endl; 

   int M1=0,M2=0;
   for(int i=RunStart;i<=RunEnd;i++){
      cout << "RUN " << i << endl;
      z_offset = ( (double)cntr )*21.00;
      z_val_1 = z_start + z_offset + z1; 
      z_val_2 = z_start + z_offset + z2; 
      Y1.push_back(y1); 
      Y2.push_back(y2);
      Z1.push_back(z_val_1); 
      Z2.push_back(z_val_2);
      ImportData(inpath_1,i,B); 
      ImportData2(inpath_2,i,Ampl,Noise);
      M1 = B.size(); 
      M2 = Ampl.size();
      cout << M1 << "\t" << M2 << endl; 
      for(int j=0;j<M1;j++){
	 if(i==28) cout << j << "\t" << Form("%.7lf",Ampl[j]) << "\t" << Form("%.15lf",B[j]) << endl;
      }      
      ParseDataAlt(i,Ampl,Noise,B,B1,B2);
      B1_avg = GetMean(B1);  
      B1_err = GetStandardErrorOfTheMean(B1);  
      B2_avg = GetMean(B2);  
      B2_err = GetStandardErrorOfTheMean(B2); 
      CalculateB_rel(B0,B1_avg,B1_err,B1_rel,B1_rel_err); 
      CalculateB_rel(B0,B2_avg,B2_err,B2_rel,B2_rel_err);
      cout << "z1 = " << Form("%.3lf",z_val_1)  << "\t" 
           << "y1 = " << Form("%.3lf",y1     )  << "\t" 
           << "B = "  << Form("%.10lf",B1_avg ) << " +/- " << Form("%.10lf",B1_err) 
           << " (" << Form("%.3E",B1_rel) << " +/- " << Form("%.3E",B1_rel_err) << " ppm)" << "\t" 
           << "z2 = " << Form("%.3lf",z_val_2)  << "\t" 
           << "y2 = " << Form("%.3lf",y2     )  << "\t" 
           << "B = "  << Form("%.10lf",B2_avg ) << " +/- " << Form("%.10lf",B2_err) 
           << " (" << Form("%.3E",B2_rel) << " +/- " << Form("%.3E",B2_rel_err) << " ppm)" << endl; 
      cntr++; 
      B1A.push_back(B1_avg);  
      dB1A.push_back(B1_err);  
      B2A.push_back(B2_avg);  
      dB2A.push_back(B2_err);  
      B1R.push_back(B1_rel);  
      dB1R.push_back(B1_rel_err);  
      B2R.push_back(B2_rel);  
      dB2R.push_back(B2_rel_err);  
      Ampl.clear();
      Noise.clear();
      B.clear();
      B1.clear();
      B2.clear();
   }

   TGraphErrors *gB1A = GetTGraphErrors(Z1,B1A,dB1A); 
   TGraphErrors *gB2A = GetTGraphErrors(Z2,B2A,dB2A); 

   TGraphErrors *gB1R = GetTGraphErrors(Z1,B1R,dB1R); 
   TGraphErrors *gB2R = GetTGraphErrors(Z2,B2R,dB2R); 
 
   SetGraphParameters(gB1A,20,kBlack); 
   SetGraphParameters(gB2A,20,kRed); 

   SetGraphParameters(gB1R,20,kBlack); 
   SetGraphParameters(gB2R,20,kRed); 

   TMultiGraph *mga = new TMultiGraph();
   mga->Add(gB1A,"p"); 
   mga->Add(gB2A,"p"); 

   TMultiGraph *mgr = new TMultiGraph();
   mgr->Add(gB1R,"p"); 
   mgr->Add(gB2R,"p"); 
 
   TLegend *L = new TLegend(0.6,0.6,0.8,0.8); 
   L->SetFillColor(kWhite);
   L->SetFillStyle(0);
   L->SetBorderSize(0);
   L->AddEntry(gB1A,Form("y = %.2lf mm",y1),"p");
   L->AddEntry(gB2A,Form("y = %.2lf mm",y2),"p");

   TCanvas *c1 = new TCanvas("c1","Field Map vs z (absolute)",0,0,1200,800);
   c1->SetFillColor(kWhite);

   c1->cd();
   mga->Draw("A"); 
   mga->SetTitle("Magnetic Field Along Axis"); 
   mga->GetXaxis()->SetTitle("z (mm)"); 
   mga->GetXaxis()->CenterTitle(); 
   mga->GetYaxis()->SetTitle("B (T)"); 
   mga->GetYaxis()->CenterTitle(); 
   mga->Draw("A");
   L->Draw("same"); 
   c1->Update(); 

   TCanvas *c2 = new TCanvas("c2","Field Map vs z (relative)",0,0,1200,800);
   c2->SetFillColor(kWhite);

   c2->cd();
   mgr->Draw("A"); 
   mgr->SetTitle("Magnetic Field Along Axis"); 
   mgr->GetXaxis()->SetTitle("z (mm)"); 
   mgr->GetXaxis()->CenterTitle(); 
   mgr->GetYaxis()->SetTitle("B (ppm)"); 
   mgr->GetYaxis()->CenterTitle(); 
   mgr->Draw("A");
   L->Draw("same"); 
   c2->Update(); 

   TCanvas *c3 = new TCanvas("c3","3D Field Map",0,0,1200,800);
   c3->SetFillColor(kWhite);
   c3->cd(); 

   const int N = B1R.size(); 

   TGraph2D *dt = new TGraph2D();
   for(int i=0;i<N;i++){
      dt->SetPoint(i,Y1[i],Z1[i],B1R[i]);
      dt->SetPoint(i,Y2[i],Z2[i],B2R[i]);
   }
   dt->SetTitle("Field Map (x = 0 cm)"); 
   dt->GetXaxis()->SetTitle("y (mm)"); 
   dt->GetXaxis()->CenterTitle(); 
   dt->GetYaxis()->SetTitle("z (mm)"); 
   dt->GetYaxis()->CenterTitle(); 
   dt->GetZaxis()->SetTitle("B (ppm)"); 
   dt->GetZaxis()->CenterTitle(); 
   dt->GetXaxis()->SetLimits(-120,120); 
   dt->GetYaxis()->SetRangeUser(-300,300); 
   dt->GetZaxis()->SetRangeUser(-300,300); 
   gStyle->SetPalette(1);
   dt->Draw("surf1");
   c2->Update();

}
//______________________________________________________________________________
void CalculateB_rel(double B0,double B,double dB,double &Brel,double &dBrel){
   double ppm   = 1E-6; 
   double ppb   = 1E-9; 
   Brel  =  (B - B0)/B0/ppm; 
   dBrel = dB/B0/ppm; 
}
//______________________________________________________________________________
void ImportData(TString inpath,int Run,vector<double> &B){

   int cntr=0;
   double irun,ipulse,iB_mid,iB_lin,iB_lsq,iB_fit,iB_ph;

   const int NLines = 1; 
   const int SIZE = 2048; 
   char buf[SIZE]; 

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      // for(int i=0;i<NLines;i++) infile.getline(buf,SIZE);
      while( !infile.eof() ){
	 infile >> irun >> ipulse >> iB_mid >> iB_lin >> iB_lsq >> iB_fit >> iB_ph; 
         if(irun==Run){
	    cntr++;
	    if(irun==28) cout << cntr << "\t" << irun << "\t" << Form("%.15lf",iB_lsq) << endl;
	    B.push_back(iB_lsq);
         } 
      }
      infile.close(); 
      // B.pop_back();
   }

}
//______________________________________________________________________________
void ImportData2(TString inpath,int Run,vector<double> &Ampl,vector<double> &Noise){

   int irun=0,ipulse=0;
   int cntr=0;
   double iampl,inoise,izc,inc,ifa,ifb,ifc,ifd,ife;

   ifstream infile;
   infile.open(inpath);
   if( infile.fail() ){
      cout << "Cannot open the file: " << inpath << endl;
      exit(1);  
   }else{
      // for(int i=0;i<NLines;i++) infile.getline(buf,SIZE);
      while( !infile.eof() ){
	 infile >> irun >> ipulse >> iampl >> inoise >> izc >> inc >> ifa >> ifb >> ifc >> ifd >> ife; 
         if(irun==Run){
	    cntr++;
	    // cout << cntr << "\t" << irun << "\t" << Form("%.15lf",iB_lsq) << endl;
	    Ampl.push_back(iampl);
	    Noise.push_back(inoise); 
         } 
      }
      infile.close(); 
      // B.pop_back();
   }

}
//______________________________________________________________________________
void ParseData(int run,vector<double> Ampl,vector<double> B,vector<double> &B1,vector<double> &B2){

   const int N = B.size();

   vector<double> a,b; 

   int cntr=0;
   double arg=0;

   // probe 1
   for(int i=0;i<N;i+=2){
      B1.push_back(B[i]); 
   }
   // probe 2 
   for(int i=1;i<N;i+=2){
      B2.push_back(B[i]); 
   }

}
//______________________________________________________________________________
void ParseDataAlt(int run,vector<double> Ampl,vector<double> Noise,vector<double> B,vector<double> &B1,vector<double> &B2){

   const int N = B.size();

   vector<double> a,b;
   vector<double> A1,A2;  

   int cntr=0;
   double arg=0;

   // choose all entries with a reasonable voltage
 
   cout << "SORTING" << endl;

   for(int i=0;i<N;i++){
      if( (Ampl[i]>0.1) && (Ampl[i]<2) && (B[i]!=0) && (Ampl[i]>Noise[i])  ){
	 b.push_back(B[i]);
	 a.push_back(Ampl[i]); 
	 // cout << i << "\t" << Form("%.5lf",Ampl[i]) << "\t" << Form("%.15lf",B[i]) << "\t" << cntr << "\t" << Form("%.15lf",b[cntr]) << endl;
	 cntr++;
      } 
   }

   cout << cntr << endl;

   // special sorting: if the amplitude for entry i is less than that of entry i-1, it's 
   // entry i is for probe 2, and vice-versa. 

   int M = b.size(); 
   for(int i=1;i<M-2;i+=2){
      if(a[i]<a[i-1]){
	 B2.push_back(b[i]); 
	 B1.push_back(b[i-1]); 
	 A2.push_back(a[i]); 
	 A1.push_back(a[i-1]); 
      }else{
	 B2.push_back(b[i-1]); 
	 B1.push_back(b[i]); 
	 A2.push_back(a[i-1]); 
	 A1.push_back(a[i]); 
      } 
   }

   // now delete all zeroes 
   DeleteZeroes(B1);
   DeleteZeroes(B2);

   int M1 = B1.size();
   int M2 = B2.size();

   if(M1==M2){
	 for(int i=0;i<M1;i++){
	    cout << Form("%.15lf",A1[i]) << "\t" << Form("%.15lf",B1[i]) << "\t" 
	         << Form("%.15lf",A2[i]) << "\t" << Form("%.15lf",B2[i]) << endl; 
	 }
   }else{
      do{
	 if(M1>M2) B1.pop_back();
	 if(M2>M1) B2.pop_back();
	 M1 = B1.size();
	 M2 = B2.size();
	 cout << "M1 = " << M1 << "\t" << "M2 = " << M2 << endl;
      }while(M1!=M2); 
   }
    

}
//______________________________________________________________________________
void DeleteZeroes(vector<double> &v){
   int N = v.size();
   vector<double> w; 
   for(int i=0;i<N;i++){
      if(v[i]!=0) w.push_back(v[i]); 
   }
   v.clear(); 
   int M = w.size();
   for(int i=0;i<M;i++) v.push_back(w[i]); 
}

