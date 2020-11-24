// simple harmonic oscillator using Euler's method 
// P. Gorham, updated March 2013 for UH Physics 305

#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
using namespace std;

#define Tmax  50     // seconds for integration

extern double FRK4xv(int, double (*)(double, double, double), 
				   double (*)(double, double, double), 
				   double ,double ,double ,double );
				   
double f_x(double, double, double), f_v(double, double, double);

main(int argc, char *argv[])
{

  if (argc<2){
  	cerr << "usage: harmo [dt in ms][filename]" << endl;
	exit(0);
  }
  
  double xt0,t0,vt0,vt,xt,t,dt,xtold,vtold; 
  double xtrue, vtrue, Et, Etrue, dE;
   ofstream outfile;  
 
	outfile.open(argv[2]);
	outfile.precision(5);         // set the precision for output

	double k=1.0, m=1.0;
	double w = sqrt(k/m);
	double T = (2.*M_PI)/w;
	
	xt0 = 1.0;                 // initial position
	t0 = 0.0;                  // initial time
	vt0 = 0.0;                 // initial velocity
	// dt = 0.001;		   // time interval, 0.001=1ms is default
	dt = atof(argv[1])*0.001;

	xtold = xt0;               // set & print out the initial conditions
	vtold = vt0;
	t = t0;
	
	Etrue = 0.5*k*xt0*xt0 + 0.5*m*vt0*vt0;
	
	outfile << "# time  xt  vt  xtrue  vtrue  Et  dE/T  t/T" << endl;
	outfile << t <<"  "<< xt0 <<"  "<< vt0 <<"  "<< xt0 <<"  "<< vt0 <<"  "<< Etrue <<"  "<< 0.0 <<"  "<< t/T << endl;

/* Here is the loop that propagates the motion:
	vt is the velocity at the new time, vtold the previous step time;
	xt is the new position, xtold the previous;
	after each step is calculated, the old is set
	to the new, and the cycle is repeated  */

	for(t=t0; t<Tmax; t+= dt){
		vt = vtold + FRK4xv(1,f_x,f_v,t,xtold,vtold,dt);
		xt = xtold + FRK4xv(0,f_x,f_v,t,xtold,vtold,dt);
		xtold = xt;  // set the old values to the new ones for next step
		vtold = vt;
		xtrue = xt0*cos(w*t);
		vtrue = vt0  + -w*sin(w*t);
		Et = 0.5*k*xt*xt + 0.5*m*vt*vt;
		dE = fabs(Et - Etrue)/Etrue;
		outfile << t <<"  "<< xt <<"  "<< vt <<"  "<< xtrue <<"  "<< vtrue <<"  "<< Et <<"  "<< dE/T <<"  "<< t/T << endl;
	   }

}

double f_x(double t, double x, double v)
{
	return(v);
}

// Force law definition
double f_v(double t, double x, double v)
{
	double k=1.0, m=1.0;
	return( -k/m*x );
}




