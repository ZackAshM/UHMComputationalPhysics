// Rocket launch
// Zachary Martin, Phys305
// 27 March 2019


using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include "Vector3D.h"

#define Tmax 3600               // s
#define G 6.67e-11			   // N m^2 kg^-2
#define Me 5.972e24		    	   // kg
#define Re 6.3781e6		  	   // m
#define ge 9.8066			   // m s^-2
		
		
/* ---------- PREAMBLE ---------- */

// we use a global time variable so the functions can use time
//   dependent accelerations if necessary
double t,t0, theta0;

extern Vector3D VecFRK4(int, Vector3D (*)(int, double, Vector3D, Vector3D),	// RK4 correction term
			  Vector3D (*)(int, double, Vector3D, Vector3D),
			  int, double, Vector3D, Vector3D, double);


/* ---------------
f_x gives the formal definition dx/dt = v;
f_v gives the appropriate acceleration or force law dv/dt;
f_g gives the gravitational force;
f_d gives the drag force;
f_p gives the thrust force;
f_n gives the initial normal force;
------------------ */
Vector3D f_x(int, double, Vector3D, Vector3D), f_v(int, double, Vector3D, Vector3D), f_g(double, Vector3D), f_d(Vector3D, Vector3D), f_p(double, Vector3D), f_n(double, Vector3D);

double *densities, *altitude;
double m(double), density(double), downrange(Vector3D);
double LinIntRho(double, double, double, double, double);	// Linear Interpolation for Density


/* LIST OF PARAMETERS */

double m0 = 15592.;	//kg		initial launch mass
double mf = 13326.; //kg		fuel mass
double tburn = 115.; //s		burnout time
double thrust = 26051.; //kg
double diameter = 1.32; //m
double Cd = 0.25; //		drag coeffcient
Vector3D R = Vector3D(0.0, 0.0, Re);	// Radial distance from center of earth to origin
double v0 = 0.0; //m s^-1	initial velocity
double tlaunch = 5.0; //s	initial time to thrust upwards (then move at angle afterwards)

/* -------------------*/




/* ---------------- START OF MAIN ----------------- */

main(int argc,char *argv[])
{

if(argc<3){
	cerr << "usage: rocket [theta0 (deg)][filename]" << endl;
	exit(0);
	}

cout << "Reading Atmosphere data..." << endl;

/* -------- DENSITY DATA --------- */
ifstream myfile("AtmosData.txt");
densities = new double [200]();
altitude = new double [200]();
for(int i=0;i<150;i++){
	double rho;
	myfile >> rho;
	densities[i] = rho*1000.0;
	altitude[i] = i*2.0*1000.0;
	}
/* --------------------------------*/


Vector3D xt,vt,xtold,vtold;
double dt;
int i = 0;

cout << "Opening outfile..." << endl;

ofstream outfile;
ofstream notefile;
outfile.open(argv[2]);
notefile.open("notes.dat");

cout << "Initializing Values..." << endl;
	
	theta0 = M_PI/180.0*atof(argv[1]);   		// initial angle, radians
	vtold = Vector3D(v0*cos(theta0), 0.0, v0*sin(theta0));		// initial velocity
	xtold = Vector3D(0.0, 0.0, Re);						// initial position at origin (on surface of earth)
	t0 = 0.0;                          		// initial time
	dt = 0.01;                         		// time step
	
	// Print out some initial forces:
	(f_g(0.01, Vector3D(0.0,0.0,1.0))).print();
	(f_d(xtold,vtold)).print();
	(f_p(0.0, vtold)).print();
	


// print out starting values 
	 outfile << "# t  x  y  z  vx  vy  vz  downrange" << endl;
	 outfile << t << "  " << xtold.Getx() << "  " << xtold.Gety() << "  " << xtold.Getz()-Re << "  " << vtold.Getx() << "  " << vtold.Gety() << "  " << vtold.Getz() << "  " << downrange(xtold) << endl;

cout << "Beginning RK4 Loop..." << endl;

/* ---- Begin RK4 Loop ---- */
	for(t=t0; t<Tmax; t+= dt){

		xt = xtold + VecFRK4(0,f_x,f_v,i,t,xtold,vtold,dt);
		vt = vtold + VecFRK4(1,f_x,f_v,i,t,xtold,vtold,dt);

		xtold = xt;
		vtold = vt;
		
		double height = xtold.GetMagnitude() - Re;
		notefile<<"t = "<<t<<endl;
		notefile<<"Fg = "<<f_g(t, xtold).printt()<<endl;
		notefile<<"Fd = "<<f_d(xtold, vtold).printt()<<endl;
		notefile<<"Fp = "<<f_p(t, vtold).printt()<<endl;
		notefile<<"dv/dt = "<<f_v(i, t, xtold, vtold).printt()<<endl<<endl;

// Output results
		if(height<0.0){
		 	 outfile << t+dt << "  " << xtold.Getx() << "  " << xtold.Gety() << "  " << xtold.Getz()-Re << "  " << vtold.Getx() << "  " << vtold.Gety() << "  " << vtold.Getz() << "  " << downrange(xt) << endl;
			 break;
			 }
 		outfile << t+dt << "  " << xtold.Getx() << "  " << xtold.Gety() << "  " << xtold.Getz()-Re << "  " << vtold.Getx() << "  " << vtold.Gety() << "  " << vtold.Getz() << "  " << downrange(xt) << endl;
	   }
/* ---- End of RK4 Loop ---- */

cout << "RK4 Loop finished. Finishing program..." << endl;


delete densities, altitude;		// erase large arrays

cout << "Program finished." << endl;

}
/* --------------- END OF MAIN -------------- */


/* -------------- FUNCTION DEFINITIONS ------------- */

// this function is complete: gives the formal definition dx/dt=v
Vector3D f_x(int i, double t, Vector3D x, Vector3D v)
{
	return(v);
}

// this function should return the force/mass=acceleration as a 
//     function of the position and velocity vectors, based on the force law
Vector3D f_v(int i, double t, Vector3D x, Vector3D v)
{
	Vector3D retval = (f_g(t, x) + f_d(x, v) + f_p(t, v))*(1.0/m(t));
	return(retval);
}


// this should return the gravitational force + normal.
// position vector with respect to center of Earth
Vector3D f_g(double t, Vector3D x)
{	
	double Rmag = x.GetMagnitude();
	Vector3D rad = x.unitVector3D();
	double Fmag = -G*Me*m(t)/(Rmag*Rmag);
	if(t==0.0){
		return(Vector3D());
	}else{
		if(x.GetMagnitude() <= Re){
			return(Vector3D());
		}else return(Fmag*rad);
	}
}

// this should return the drag force
Vector3D f_d(Vector3D x, Vector3D v)
{
	double height = x.GetMagnitude() - Re;
	double area = M_PI*diameter*diameter*0.25;
	double b = fabs(0.5*Cd*area*density(height));
	//b = 0.0;				// (un)comment to turn on/off drag
	Vector3D W = Vector3D(0.0, 0.0, 0.0);	//wind
	Vector3D vapp = v - W;		//apparent velocity
	double vmag = vapp.GetMagnitude();
	return((-b*vmag)*vapp);
}

// this should return the thrust force
Vector3D f_p(double t, Vector3D v)
{	
	double p;
	if(t<tburn){
		p = ge*thrust;
	}else p = 0.0;
	Vector3D InitialDirection = Vector3D(cos(theta0), 0.0, sin(theta0));
	return(p*InitialDirection);
}

// initial normal force
//Vector3D f_n(double t, Vector3D x)
//{
//	Vector3D zeroVec = Vector3D();
//	Vector3D dist = R + x;		// radial distance from center of earth
//	if(t<=0.05){
//		return((G*Me/pow(dist.GetMagnitude(), 3.0))*m(t)*dist);
//	}else return(zeroVec);
//}

/* --SUBFUNCTIONS-- */

// this function should return the density using the lookup table from
// the atmosphere data using linear interpolation
double density(double H)
{
	if(H>298e3) return(0);
	int lower = floor(H/2.0);
	int upper = ceil(H/2.0);
	double dens = LinIntRho(H, lower, upper, densities[lower], densities[upper]);
	return(dens);
}

// linear interpolation for density(H) function
double LinIntRho(double h, double lower, double upper, double densL, double densU)
{
	if(upper == lower){
		return(densL);
	}else{
		return(densL + (h - lower)*(densU - densL)/(upper - lower));
	}
}

// this should return the time dependent mass as fuel exits the rocket
double m(double t)
{
	if(t<tburn){
		return(m0 - mf*(t - t0)/tburn);
	}else{
		return(m0 - mf);
	}
}

// returns the downrange
double downrange(Vector3D x)
{
	double radAng = acos(R.dot(x)/(R.GetMagnitude()*x.GetMagnitude()));
	return(Re*radAng);
}


/* ----- END ----- */



