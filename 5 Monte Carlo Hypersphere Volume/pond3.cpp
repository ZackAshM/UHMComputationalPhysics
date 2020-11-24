// pond2.cpp to check MC integration of unit radius circle area
// P. Gorham 2/10/15 for Physics 305 UH Manoa
// Based on Landau Paez & Bordeianu code ch. 11
using namespace std;       
#include <iostream>       
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath> 
#include <cstdlib> 
                     
#define PI  M_PI
// #define max 1000
#define seed 681111

main(int argc, char** argv)
{
   int max = 1000;
   if(argc > 1){
   	max = atoi(argv[1]);
   	cerr << "Using user no. of trials: " << max << endl;
   }else{
   	cerr << "Using default no. of trials: " << max << endl;
   }
   
   double x[max], y[max], z[max], r[max];  // allocate arrays
   double  hits=0.0, ntrials=0.0;
   double sphere = (4. / 3.)*PI;
   
   ofstream outfile;  
   outfile.open("pond3_"+std::to_string(max)+".dat");
   
   outfile << "# x y z" << endl; 
   
   srand48(seed);                       // seed the number generator 
   
      for (int i=0; i<max; i++){
         x[i] = (drand48()-0.5)*2.;      // x,y,z between 
         y[i] = (drand48()-0.5)*2.;      // -1 and 1
         z[i] = (drand48()-0.5)*2.; 
         r[i] = sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);        // distance from origin 
	 hits += r[i]<=1.0 ? 1.0 : 0.0;  // conditional expression
	 ntrials += 1.0;
      }
    double volume = hits/ntrials*8.0;
   cout << "Volume of inscribed sphere= "<< setprecision(9) <<
   		volume <<" , fractional error= "<< fabs((volume-sphere)/sphere) <<endl;
      
   for (int i=0; i<max; i++){		// write results into file, hits within circle     
     if(r[i]<=1.0)outfile << x[i]<<" "<< y[i]<<" "<< z[i] <<endl;
   }
   outfile << "\n\n";
   for (int i=0; i<max; i++){		// write results into file, hits outside circle      
     if(r[i]>1.0) outfile << x[i]<<" "<< y[i]<<" "<< z[i] <<endl;
   } 
 

	cerr << "data stored in pond3_"+std::to_string(max)+".dat" << endl;
   outfile.close();
 
}
 

