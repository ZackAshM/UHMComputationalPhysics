// hypersphereMC: a monte-carlo integration of a hypersphere volume 
// P. Gorham, updated 2/10/2015 for Physics 305 
// requires student completion 

using namespace std;       
#include <iostream>       
#include <iomanip>   // required to use "setprecision" if needed
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>  

// parameters for volume integration
#define max_in 500000	// max number of intervals
#define vmin 0		// range of integration
#define vmax M_PI/2

main(int argc, char *argv[])
{
	double f(double x, int y);
	double int_trap(double min, double max, int y);
	
	double hit,xi,R,Rsq,D,R_D,Vtot,Vsphere;
	double Vtrue=0.0,result,integproduct=1.0;
	int n,i,NDIM=3, Ntrials=1000000;
	
	srand48(1299811); // a large prime

	/* usage: NDIM = # of dimensions, NMAX=number of sample points */
	if(argc<2){
		cerr<< "usage: hypersphereMC [NDIM][NMAX]"<<endl;
		exit(0);
		}
	
	NDIM = atoi(argv[1]); // number of dimensions
	Ntrials = atoi(argv[2]); // number of trials



	D= 2.0;		// side of hypercube needed to contain hypersphere
	R_D = 1.0;	// radius of hypersphere
	hit = 0.0;	// the counter for events within sphere
	n=0;		// initialize the loop counter
	
	//-------this is the main loop----------------------

	while(n<Ntrials){  // continue generating coordinates up to Ntrials
	    Rsq = 0.0;  // this variable accumulates the square of each coordinate
	    for(i=0;i<NDIM;i++){
		   xi = (drand48()-0.5)*2.;  // uniform random value +/-[0,1] in each coordinate
		   Rsq += xi*xi;  // sum up the squares to get distance from origin
		} // end of NDIM loop------------

	        hit += Rsq <=1.0 ? 1.0 : 0.0; // check if distance Rsq falls within R_D boundary, 
	          //                   increment hit counter if it does

	    n++;	// counter for Ntrials while loop
	    }  //---------END OF WHILE LOOP-----------------

	Vtot = D;	// Vtot=D for 1-dimensional "hypercube" (a line)
	 for(i=1;i<NDIM;i++){
	        Vtot *= D;  //iterative multiplication to get N-dim hypercube
	    }

	 /* get ratio of volumes */
	 Vsphere = hit/Ntrials*Vtot;  // determine the hit ratio & estimated Volume
	 
	 // calculating volume analytically
	 for (int j=3; j<=NDIM; j++){
	 integproduct *= int_trap(vmin, vmax, j);	// iterative integral product
	 }
	 Vtrue = pow(2., NDIM-2.)*M_PI*integproduct; // true volume from analytic formula


	 cout << NDIM <<" dimensions"<<endl <<"Vsphere= "<< Vsphere <<endl<< "Vtot= "<<Vtot<<endl<< "Vtrue= "<<Vtrue<<endl<< "fractional error= "<<fabs(Vtrue-Vsphere)/Vtrue<<endl;

}	//---------END OF MAIN-----------------


// iterative integral function for true volume
double f (double x, int y)
{ 
   return pow(cos(x), y);	// y is the iterative index from 3 to n
}


// trapezoidal method of integration
double int_trap(double min, double max, int y)
{
   double result = 0.0, dt, t;
   dt = (max - min)/max_in;

   for(int i=0; i<max_in; i++){
      t = min + i*dt;
      result += 0.5*dt*(f(t, y) + f((t + dt), y));
}
   return result;
}


