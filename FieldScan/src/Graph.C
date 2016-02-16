TGraph *GetTGraph(vector<double>,vector<double>); 
TGraphErrors *GetTGraphErrors(vector<double> x,vector<double> y,vector<double> ey); 
TGraphAsymmErrors *GetTGraphAsymmErrors(vector<double> x,vector<double> y,vector<double> eyh); 
TGraphAsymmErrors *GetTGraphAsymmErrors(vector<double> x,vector<double> y,vector<double> eyl,vector<double> eyh);
void SetGraphParameters(TGraph *g,int Marker,int Color,int width = 1); 
void SetGraphParameters(TGraphErrors *g,int Marker,int Color,int width = 1); 
void SetGraphParameters(TGraphAsymmErrors *g,int Marker,int Color,int width = 1); 

//______________________________________________________________________________
// 
/// TGraph objects 
//______________________________________________________________________________
TGraph *GetTGraph(vector<double> x,vector<double> y){
   const int N = x.size();
   TGraph *g = new TGraph(N,&x[0],&y[0]); 
   return g;
}
//______________________________________________________________________________
TGraphErrors *GetTGraphErrors(vector<double> x,vector<double> y,vector<double> ey){
   const int N = x.size();
   vector<double> ex;
   for(int i=0;i<N;i++) ex.push_back(0); 
   TGraphErrors *g = new TGraphErrors(N,&x[0],&y[0],&ex[0],&ey[0]); 
   return g;
}
//______________________________________________________________________________
TGraphAsymmErrors *GetTGraphAsymmErrors(vector<double> x,vector<double> y,vector<double> eyh){
   const int N = x.size();
   vector<double> exl,exh,eyl;
   for(int i=0;i<N;i++){
      exl.push_back(0); 
      exh.push_back(0); 
      eyl.push_back(0); 
   }
   TGraphAsymmErrors *g = new TGraphAsymmErrors(N,&x[0],&y[0],&exl[0],&exh[0],&eyl[0],&eyh[0]); 
   return g;
}
//______________________________________________________________________________
TGraphAsymmErrors *GetTGraphAsymmErrors(vector<double> x,vector<double> y,vector<double> eyl,vector<double> eyh){
   const int N = x.size();
   vector<double> exl,exh;
   for(int i=0;i<N;i++){
      exl.push_back(0); 
      exh.push_back(0); 
   }
   TGraphAsymmErrors *g = new TGraphAsymmErrors(N,&x[0],&y[0],&exl[0],&exh[0],&eyl[0],&eyh[0]); 
   return g;
}
//______________________________________________________________________________
// 
/// Graph parameters 
//______________________________________________________________________________
void SetGraphParameters(TGraph *g,int Marker,int Color,int width = 1){
   g->SetMarkerStyle(Marker); 
   g->SetMarkerColor(Color); 
   g->SetLineColor(Color); 
   g->SetLineWidth(width); 
}
//______________________________________________________________________________
void SetGraphParameters(TGraphErrors *g,int Marker,int Color,int width = 1){
   g->SetMarkerStyle(Marker); 
   g->SetMarkerColor(Color); 
   g->SetLineColor(Color); 
   g->SetLineWidth(width); 
}
//______________________________________________________________________________
void SetGraphParameters(TGraphAsymmErrors *g,int Marker,int Color,int width = 1){
   g->SetMarkerStyle(Marker); 
   g->SetMarkerColor(Color); 
   g->SetLineColor(Color); 
   g->SetLineWidth(width); 
}
