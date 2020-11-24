// projectile motion 
// P. Gorham, updated 3/14/17 for UH Physics 305 
// March 2013, updated to minimal c++ --PG


using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include "3Vector.h"

#define Tmax  500                // seconds
#define PI M_PI

// this structure type for 3-vectors 
// typedef struct {
//		double x, y, z;
//		} vec3;
		
// we use a global time variable so the functions can use time
//   dependent accelerations if necessary
double t,t0, theta0;

extern vec3 vecFRK4xv(int, vec3 (*)(double, vec3, vec3),
			  vec3 (*)(double, vec3, vec3),
			  double ,vec3, vec3,double );


vec3 f_x(double, vec3, vec3), f_v(double, vec3, vec3);
double dragc(double);


main(int argc,char *argv[])
{
  vec3 xt,vt,xtold,vtold;
  double dt;
  double vt0,v0, range;
   ofstream outfile;  
   
	if(argc<4){
		cerr << "usage: projectile [theta0 (deg)][v0 (m/s)][filename]" << endl;
		exit(0);
		}
 
   
	outfile.open(argv[3]);
	
	theta0 = PI/180.0*atof(argv[1]);   // initial angle, radians
	v0 = atof(argv[2]);                // initial velocity, m/s
	vtold.x = v0*cos(theta0);          // x and z components of velocity
	vtold.z = v0*sin(theta0);
	vtold.y = 0.0;                     //  in plane motion only here
	t0 = 0.0;                          // initial time
	xtold.x = 0.0;                     // initial position at origin
	xtold.y = 0.0;
	xtold.z = 0.0;
	dt = 0.01;                         // time step


	// print out starting values 
	 outfile << "t  x  y  z  vx  vy  vz  range" << endl;
	 outfile << t << "  " << xtold.x << "  " << xtold.y << "  " << xtold.z << "  " << vtold.x << "  " << vtold.y << "  " << vtold.z << "  " << 0.0 << endl;

	for(t=t0; t<Tmax; t+= dt){

		xt = vec3sum( xtold , vecFRK4xv(0,f_x,f_v,t,xtold,vtold,dt) );
		vt = vec3sum( vtold , vecFRK4xv(1,f_x,f_v,t,xtold,vtold,dt) );

		xtold = xt;
		vtold = vt;
		range = sqrt(xtold.x*xtold.x + xtold.y*xtold.y);

		if(xt.z<0.0){
		 	 outfile << t << "  " << xtold.x << "  " << xtold.y << "  " << xtold.z << "  " << vtold.x << "  " << vtold.y << "  " << vtold.z << "  " << range << endl;
			 break;
			 }
 		outfile << t << "  " << xtold.x << "  " << xtold.y << "  " << xtold.z << "  " << vtold.x << "  " << vtold.y << "  " << vtold.z << "  " << range << endl;
	   }


}


// this function is complete: gives the formal definition dx/dt=v
vec3 f_x(double t, vec3 x, vec3 v)
{
	return(v);
}


// this function should return the force/mass=acceleration as a 
// function of the position and velocity vectors, based on the force law
vec3 f_v(double t, vec3 x, vec3 v)
{
	double  g=9.8, m=0.145, r=0.0369;
	double b = 0.5*M_PI*pow(r, 2.0)*dragc(x.z);
	//b = 0.0;	// (un)comment to turn on/off drag
	vec3 W = scalar_vec3mult(-6.7056, vec3norm(v)); //= vec3zero();	// wind
	// W.x = ; W.y = ; W.z = ;
	vec3 vapp = vec3diff(v, W);
	
    vec3 retval;
        retval.x = -(b/m)*vec3mag(vapp)*vapp.x; // x is forward
        retval.y = -(b/m)*vec3mag(vapp)*vapp.y; // y is side-to-side
        retval.z = -g - (b/m)*vec3mag(vapp)*vapp.z;  // z is vertical, gravity only in *absence* of drag
        return(retval);

}


// this function should return the drag coeffcient as a function of altitude H
// accounting for the density of air using an exponential scale height
double dragc(double H)
{
	double Cd = 0.30, rho0 = 1.22, h0 = 8300.;
	double Cdrho = Cd*rho0*exp(-H/h0);
	return(Cdrho);
}





	
	
	
	

