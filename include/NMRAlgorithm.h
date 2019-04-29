#ifndef NMRALGORITHM_H
#define NMRALGORITHM_H

// miscellaneous helpful algorithms  

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <sstream>
#include <iterator>
#include <algorithm> 
#include <math.h>  

namespace NMRAlgorithm{
   // templated functions
   //______________________________________________________________________________
   template <typename T> 
      void SortedRemoveDuplicates(std::vector<T> &x){
	 std::sort( x.begin(),x.end() ); // sort first
	 x.erase( std::unique( x.begin(), x.end() ), x.end() ); 
      }
   //______________________________________________________________________________
   template <typename T>
      void ReverseVector(std::vector<T> &x){
	 const int N = x.size();
	 std::vector<T> y;
	 for(int i=0;i<N;i++) y.push_back(x[i]);
	 x.clear();
	 for(int i=N-1;i>=0;i--) x.push_back(y[i]);
      }
   //______________________________________________________________________________
   template <typename T>
      void BinarySearch(int N,T *array,T key,int &lowerbound,int &upperbound){
	 int comparisonCount = 1;    //count the number of comparisons (optional)
	 lowerbound          = 0;
	 upperbound          = N-1;

	 // To start, find the subscript of the middle position.
	 int position = (lowerbound + upperbound) / 2;

	 while( (array[position]!=key) && (lowerbound <= upperbound)){
	    comparisonCount++;
	    if (array[position] > key){
	       // decrease position by one.
	       upperbound = position - 1;
	    }else{
	       // else, increase position by one.
	       lowerbound = position + 1;
	    }
	    position = (lowerbound + upperbound) / 2;
	 }

	 // T lo=0,hi=0,mid=0;
	 int dump = lowerbound;
	 if (lowerbound <= upperbound){
	    // Here we have an exact match to the key
	    lowerbound = position;
	    upperbound = position+1;
	 }else{
	    // Here the lower bound surpassed the upper
	    lowerbound = upperbound;
	    upperbound = dump;
	 }
	 // to safeguard against values that are outside the boundaries of the grid 
	 if(upperbound>=N){
	    upperbound = N-1;
	    lowerbound = N-2;
	 }
	 if(upperbound==0){
	    lowerbound = 0;
	    upperbound = 1;
	 }
      }
   //______________________________________________________________________________
   template <typename T>
      void BinarySearch(std::vector<T> array,T key,int &lowerbound,int &upperbound){
	 const int N         = array.size();
	 int comparisonCount = 1;    //count the number of comparisons (optional)
	 lowerbound          = 0;
	 upperbound          = N-1;

	 // To start, find the subscript of the middle position.
	 int position = (lowerbound + upperbound) / 2;

	 while( (array[position]!=key) && (lowerbound <= upperbound)){
	    comparisonCount++;
	    if (array[position] > key){
	       // decrease position by one.
	       upperbound = position - 1;
	    }else{
	       // else, increase position by one.
	       lowerbound = position + 1;
	    }
	    position = (lowerbound + upperbound) / 2;
	 }

	 // T lo=0,hi=0,mid=0;
	 int dump = lowerbound;
	 if (lowerbound <= upperbound){
	    // Here we have an exact match to the key
	    lowerbound = position;
	    upperbound = position+1;
	 }else{
	    // Here the lower bound surpassed the upper
	    lowerbound = upperbound;
	    upperbound = dump;
	 }
	 // to safeguard against values that are outside the boundaries of the grid 
	 if(upperbound>=N){
	    upperbound = N-1;
	    lowerbound = N-2;
	 }
	 if(upperbound==0){
	    lowerbound = 0;
	    upperbound = 1;
	 }
      } 
   //______________________________________________________________________________
   template <typename T>
      int Convert(std::string sx,T &x){
	 // convert a string to an int, double, or float 
	 int rc = -1;
	 if( std::is_arithmetic<T>::value ){
	    if( std::is_integral<T>::value ){
	       // it's an integer or boolean 
	       x = std::atoi( sx.c_str() );
	    }else{
	       // it's a double or float 
	       x = std::atof( sx.c_str() );
	    }
	    rc = 0; // arithmetic type  
	 }else{
	    rc = 1; // it's a string
	 }
	 return rc;
      }
   //______________________________________________________________________________
   template< typename T >
      int DeleteElements(std::vector<int> badIndex,std::vector<T> x,std::vector<T> &y){
	 // delete elements based on the vector badIndex
	 int cntr=0;
	 int N = x.size();
	 int M = badIndex.size();
	 bool skip=false;
	 for(int i=0;i<N;i++){
	    for(int j=0;j<M;j++){
	       if(i==badIndex[j]){
		  // found a bad index; toggle the boolean and break the loop
		  cntr++;
		  skip = true;
		  break;
	       }
	    }
	    if(skip){
	       // reset and move on 
	       skip = false;
	       continue;
	    }else{
	       // this index is good, save the data
	       y.push_back(x[i]);
	    }
	 }
	 // return the number of elements skipped
	 return cntr;
      }
} // ::NMRAlgorithm 


#endif 
