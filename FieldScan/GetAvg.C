#include "./src/Math.C"
#include "./src/WeightedAverage.C"
#include "./src/Import.C"

void GetAvg(){

   vector<double> x,dx;

   double ppm = 1E-6; 
   double ppb = 1E-9; 

   int sw = 2; 

   TString inpath = Form("./input/bnl-probe-rot.dat");
   // ImportDataAlt2(inpath,sw,x); 
   ImportDataAlt3(inpath,x,dx); 

   WeightedAverage *WA = new WeightedAverage(); 

   WA->SetVectors(x,dx); 
   WA->Calculate();

   double x_avg_wt = WA->GetResult();  
   double x_err_wt = WA->GetResultErr();  
   double x_sd     = GetStandardDeviation(x);

   cout << "mean = " << Form("%.3lf",x_avg_wt) << endl;
   cout << "err  = " << Form("%.3lf",x_err_wt) << endl;
   cout << "sd   = " << Form("%.3lf",x_sd)     << endl;

   WA->ClearVectors(); 
   
   delete WA; 

   // // double x0    = 61.754E+6/GAMMA_p; 
   // double x0    = 61.723E+6; 
   // double x_avg = x0 + GetMean(x); 
   // double x_err = GetStandardErrorOfTheMean(x);

   // cout << Form("%.15lf",x_avg) << " +/- " << Form("%.3lf",x_err) << endl;

   // // double x_err_ppb = x_err/x_avg/ppb;  

   // // double x_rel     = (x_avg-x0)/x0/ppm; 
   // // double x_rel_err = x_err/x0/ppm; 

   // // cout << Form("B0    = %.15lf",x0) << endl;
   // // cout << Form("B     = %.15lf",x_avg) << " +/- " 
   // //      << Form("%.15lf",x_err) 
   // //      << Form(" (%.3lf ppb)",x_err_ppb) << endl;
   // // cout << Form("B_rel = %.15lf",x_rel) << " +/- " 
   // //      << Form("%.15lf",x_rel_err) << endl;


}
