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


main(int argc, char *argv[])
{

  if (argc<2){
  	cerr << "usage: harmo [dt in ms][filename]" << endl;
	exit(0);
  }
  
  double k,m,l,g,xt0,t0,vt0,w,vtii,xtii,t,dt,xti,vti, xtrue,vtrue, Etii, Etrue, dE, T;
   ofstream outfile;  
 
	outfile.open(argv[2]);
	outfile.precision(5);         // set the precision for output

	k = 1.0;                   // spring constant
	m = 1.0;                   // mass in kg
	l = 1.0;				  // length for pendulum in m
	g = 9.81;				  // gravity for pendulum in m/s2
	// w = sqrt(k/m);
	w = sqrt(g/l);
	T = (2.*M_PI)/w;
	// xt0 = 1.0;                 // initial position
	xt0 = 2.9;				// initial angle in radians for pendulum
	t0 = 0.0;                  // initial time
	vt0 = 0.0;                 // initial velocity / ang vel
	// dt = 0.001;		   // time interval, 0.001=1ms is default
	dt = atof(argv[1])*0.001;

	xti = xt0;               // set & print out the initial conditions
	vti = vt0;
	t = t0;
	
	// Etrue = 0.5*k*xt0*xt0 + 0.5*m*vt0*vt0;
	Etrue = 0.5*m*pow(vt0*l,2.0) + m*g*l*(1.0-cos(xt0));
	
	outfile << "# time  xtii  vtii  xtrue  vtrue  Etii  dE/T  t/T" << endl;
	outfile << t0 <<"  "<< xt0 <<"  "<< vt0 <<"  "<< xt0 <<"  "<< vt0 <<"  "<< Etrue <<"  "<< Etrue-Etrue <<"  "<< t0/T << endl;

/* Here is the loop that propagates the motion:
	vtii is the velocity at the new time, vti the previous step time;
	xtii is the new position, xti the previous;
	after each step is calculated, the old is set
	to the new, and the cycle is repeated  */

	for(t=t0; t<Tmax; t+= dt){
		// vtii = vti + dt*(-k/m)*xti;
		vtii = vti + dt*(-g/l)*sin(xti);
		xtii = xti + dt*vti;
		xti = xtii;  // set the old values to the new ones for next step
		vti = vtii;
		xtrue = xt0*cos(w*t);
		vtrue = vt0  + -w*sin(w*t);
		// Etii = 0.5*k*xtii*xtii + 0.5*m*vtii*vtii;
		Etii = 0.5*m*pow(vtii*l,2.0) + m*g*l*(1.0-cos(xtii));
		dE = fabs(Etii - Etrue)/Etrue;
		outfile << t <<"  "<< xtii <<"  "<< vtii <<"  "<< xtrue <<"  "<< vtrue <<"  "<< Etii <<"  "<< dE/T <<"  "<< t/T << endl;
	   }

}
