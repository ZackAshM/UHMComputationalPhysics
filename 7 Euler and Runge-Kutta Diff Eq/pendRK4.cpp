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

extern double FRK4thetaw(int, double (*)(double, double, double), 
				   double (*)(double, double, double), 
				   double ,double ,double ,double );
				   
double f_theta(double, double, double), f_w(double, double, double);

main(int argc, char *argv[])
{

  if (argc<3){
  	cerr << "usage: harmo [dt in ms][angle in degrees][filename]" << endl;
	exit(0);
  }
  
  double thetat0,t0,wt0,wt,thetat,t,dt,thetatold,wtold; 
  double thetatrue, wtrue, Et, Etrue, dE;
   ofstream outfile;  
 
	outfile.open(argv[3]);
	outfile.precision(5);         // set the precision for output

	double l=1.0, g=9.81, m=1.0;
	double w = sqrt(g/l);
	double T = (2.*M_PI)/w;
	
	// thetat0 = 1.0;                 // initial angle in degrees
	thetat0 = atof(argv[2])*M_PI/180.0;
	t0 = 0.0;                  // initial time
	wt0 = 0.0;                 // initial ang. velocity
	// dt = 0.001;		   // time interval, 0.001=1ms is default
	dt = atof(argv[1])*0.001;

	thetatold = thetat0;               // set & print out the initial conditions
	wtold = wt0;
	t = t0;
	
	thetatrue = thetat0*cos(w*t0);	// small angle approx solution
	wtrue = wt0 + -thetat0*w*sin(w*t0);
	
	Etrue = 0.5*m*pow(wt0*l, 2.0) + m*g*l*(1.0-cos(thetat0));
	
	outfile << "# time  thetat  wt  thetasmall  wsmall  Et  dE/T  t/T" << endl;
	outfile << t <<"  "<< thetat0 <<"  "<< wt0 <<"  "<< thetatrue <<"  "<< wtrue <<"  "<< Etrue <<"  "<< 0.0 <<"  "<< t/T << endl;

/* Here is the loop that propagates the motion:
	wt is the ang velocity at the new time, wtold the previous step time;
	thetat is the new angle, thetatold the previous;
	after each step is calculated, the old is set
	to the new, and the cycle is repeated  */

	for(t=t0; t<Tmax; t+= dt){
		wt = wtold + FRK4thetaw(1,f_theta,f_w,t,thetatold,wtold,dt);
		thetat = thetatold + FRK4thetaw(0,f_theta,f_w,t,thetatold,wtold,dt);
		thetatold = thetat;  // set the old values to the new ones for next step
		wtold = wt;
		thetatrue = thetat0*cos(w*t);
		wtrue = wt0 + -thetat0*w*sin(w*t);
		Et = 0.5*m*pow(wt*l, 2.0) + m*g*l*(1.0-cos(thetat));
		dE = fabs(Et - Etrue)/Etrue;
		outfile << t <<"  "<< thetat <<"  "<< wt <<"  "<< thetatrue <<"  "<< wtrue <<"  "<< Et <<"  "<< dE/T <<"  "<< t/T << endl;
	   }

}

double f_theta(double t, double theta, double w)
{
	return(w);
}

// Force law definition
double f_w(double t, double theta, double w)
{
	double l=1.0,g=9.81;
	return( -g/l*sin(theta) );
}




