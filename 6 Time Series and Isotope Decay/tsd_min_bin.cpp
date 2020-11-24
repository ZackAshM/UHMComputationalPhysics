// Simulation of times series of radioactive decays
// Zachary Martin, 2/20/2019 for Physics 305 

using namespace std;       
#include <iostream>       
#include <iomanip>   // required to use "setprecision" if needed
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>  

#define seed 2202019253
#define M 1000000

main(int argc, char *argv[])
{

   double *x, *y, *m, dt=0.01; //dt is the time interval (ms)
   int *N;
   x = new double [M]();		// random number array
   y = new double [M]();		// probability 0 or 1 array
   m = new double [200]();	// minute interval bins
   N = new int [20]();		// the count array (how many minute bins have l decays)
   double q = .001;			// probability
   int minutes = M/6000;

   srand48(seed);

   ofstream outfile;
   outfile.open("tsd_mb.dat");
   
   outfile << "# possible count error" << endl;

   for (int i=0; i<M; i++){
      x[i] = drand48();
      int jminutes = i/6000;
      if (x[i] > q){
         y[i] = 0.;
      }else if (x[i] <= q){
         y[i] = 1.;
      }
      m[jminutes] += y[i];
   }
   
   // Re-binning data
   for(int j=0;j<minutes;j++){
   	// outfile << j+1 <<" "<< m[j];
   	for(int l=0;l<20;l++){	// counting how many minute bins have l decays
   	   if(m[j]==l){
   	   N[l] += 1;
   	   }else{}
   	}
   }
   
   for(int l=0;l<20;l++){
   	outfile << l <<" "<< N[l] <<" "<< sqrt(N[l])+1. << endl;
   }

   cerr << "data stored in tsd_mb.dat" << endl;
   outfile.close();



}	//---------END OF MAIN-----------------



