// ballistic missile 
// P. Gorham, 
// march 2017 Physics 305
// To compile:
//  g++ VecFRK4.cpp initialize_atmosphere.cpp missileV3.cpp -o ~/bin/missileV3

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include "Vector3D.h"

#define Tmax  1000.0                // seconds
#define PI M_PI
#define Diam 1.320  // meters for the rocket
#define Am  (PI*Diam*Diam/4.)
#define Cd  0.25
#define tb   115.0     // seconds
#define m0   15592.    // kg
#define mf   13326.  // kg initial fuel
#define G    6.67384e-11  // gravity
#define Re   6335437.0  // meters
#define Me   5.972E24  // kg
#define Thrust (9.80665*26051.) //Newtons

#define STARTALT  2000.0  // meters to CG from sea level at launch


// global variable for wind velocity
Vector3D W0(0,0,0);	

Vector3D InitialThrustDir(0.,0.,1.);

double hkm[1500],rhovh[1500];  // atmosphere table parameters

// mass function vs. time ----------------------------------

double m_t(double t)
{
	double m;
	if(t<tb){
		m = m0 - mf*(t/tb);
	   }else{
		m = m0 - mf;
		}
	return(m);
}

double rho(double h) // h in meters, returns density ----------------------------------
{
	int ih;
	double density,x1,x2,y1,y2,slope;
	
	if(h>298e3) return(density=0);
	// the following does a linear interpolation
	ih = ((int)(h/2000.));	// density file in 2km steps
	y2 = rhovh[ih+1];
	y1 = rhovh[ih];
	x2 = hkm[ih+1]*1000;
	x1 = hkm[ih]*1000;
	slope = (y2-y1)/(x2-x1); // kg/m^3 per meter
	density = y1 + slope*(h-x1);
	return(density);
}

// gravitational + normal force at start ----------------------------------
Vector3D Fgn(Vector3D r, double t)  // r is the vector location of rocket
{
	Vector3D fg;
	double R = r.GetMagnitude();
	double Fmag = -G*Me*m_t(t)/(R*R);
	Vector3D Fdir = r.unitVector3D();  // lies along radial direction	
	fg = Fmag * Fdir;
	 return(fg);

}

// drag force ----------------------------------
Vector3D Fb(Vector3D v, Vector3D r, double t)
{
	double _h = r.GetMagnitude()-Re;
	Vector3D vapp = (v-W0); 
	double vmag = vapp.GetMagnitude();
	double bmag = 0.5*rho(_h)*Cd*Am;
	Vector3D fdrag = (-bmag*vmag) * vapp;	
	return(fdrag);
}

//  thrust force ----------------------------------
Vector3D Fp(double m, Vector3D v, double t)
{
	Vector3D thrust,thrdir;
	double thrmag;
	
	if(t<=tb){
		thrmag = Thrust;
	}else{
	  	thrmag = 0.0;
	}
	thrdir = InitialThrustDir;
	thrust = thrmag * thrdir;
	//thrust.print();
	return(thrust);

}

// This function is found in an external file: vecFRK4.cpp
Vector3D VecFRK4(int , Vector3D (*f_x)(int, double, Vector3D, Vector3D),
			  Vector3D (*f_v)(int, double, Vector3D, Vector3D),
			  int , double , Vector3D, Vector3D , double );

// this function is complete: gives the formal definition dx/dt=v
Vector3D f_x(int i, double t, Vector3D r, Vector3D v)
{
	return(v);
}

// this function should return the force/mass=acceleration as a 
// function of the position and velocity vectors, based on the force law
Vector3D f_v(int i, double t, Vector3D r, Vector3D v)
{
    Vector3D dvdt;
//	acceleration law: dvdt = 1./m_t(t) * ( (Fg(r)+Fn(t)) + Fb(v,r) + Fp(m_t(t),v,t)  );

	dvdt = (1./m_t(t)) * (Fgn(r,t) + Fb(v,r,t) + Fp(m_t(t),v,t));		
        return(dvdt);

}




extern void initialize_atmosphere(char* ,double*, double*);


int main(int argc,char *argv[])
{
  Vector3D xt,vt,Fg1,Fp1,Fb1;
  double t, dt, nO, nN2, nO2;
  double vt0,v0,theta0,t0;
  int i;
   ofstream outfile; 
   ifstream inFile;
   
	if(argc<3){
		cerr << "usage: missileV3 [theta0 from vertical (deg)][density file][outfile]" << endl;
		exit(0);
		}
 
	outfile.open(argv[3]);

	initialize_atmosphere(argv[2],hkm,rhovh);
	
	
	theta0 = PI/180.0*(90.-atof(argv[1]));   // initial angle, converted to radians from horizontal
	InitialThrustDir.update(cos(theta0),0.0,sin(theta0));
	InitialThrustDir.print();
	v0 = 0.0;                // initial velocity, m/s
	t0 = 0.0;
	Vector3D vtold(v0*cos(theta0),0.0,v0*sin(theta0));          // x and z components of velocity
	Vector3D xtold(0.0,0.0,Re+STARTALT);                        // altitude to CG assumed
	Vector3D atold(0.,0.,0.),at;

	dt = 0.001;                         // time step

	// Print out some initial forces:
	(Fgn(xtold,0.0)).print();
	(Fb(vtold,xtold,0.0)).print();
	(Fp(m0,vtold,0.0)).print();

	// print out starting values 

	 outfile << t0 << " " << xtold.Getx() << " " << setprecision(9) << xtold.Getz()-Re 
	 << " " << vtold.Getx() << " " << vtold.Getz() << " " << atold.Getx() << " " 
	 << atold.Getz() << endl;

	 int ii=0;
	for(t=0.0; t<Tmax; t+= dt){

		xt =  xtold + VecFRK4(0,f_x,f_v,ii,t,xtold,vtold,dt) ;
		vt =  vtold + VecFRK4(1,f_x,f_v,ii,t,xtold,vtold,dt) ;	
		at = f_v(ii,t,xtold,vtold);  // for reference

		xtold = xt;
		vtold = vt;
		atold = at;
		ii++;  // generic index if needed
	
		if((xt.GetMagnitude())<=Re){
		 	 outfile << t << " " << xtold.Getx() << " " << setprecision(9) << xtold.Getz()-Re 
		 	 << " " << vtold.Getx() << " " << vtold.Getz() << " " << atold.Getx() << " " 
	 			<< atold.Getz() << endl; 
			 break;  // this means we hit the earth
			 }
		if(fmod(t,1.0) < dt){	 
 		outfile << t+dt << " " << xtold.Getx() << " " << setprecision(9) << xtold.Getz()-Re 
 		<< " " << vtold.Getx() << " " << vtold.Getz() << " " << atold.Getx() << " " 
	 			<< atold.Getz() << endl;
		}
	}  // end of main loop over time

	  outfile.close();

}
