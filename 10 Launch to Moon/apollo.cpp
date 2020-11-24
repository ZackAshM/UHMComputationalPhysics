/* earth-moon system equations of motion, */
/* P. Gorham, 4/10/2019 helper code for UH Physics 305 */
// g++ moon_around_earth.cpp VecFRK4.cpp -o ~/bin/moon_around_earth
// This program assumes apollo to be initially in parking orbit 175km above earth


#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include "Vector3D.h"
#include <string>


#define Tmax  10000            // seconds, not long enough yet
#define PI M_PI


double t0, theta0;

/*  global previous positions for the mass bodies--needed for acceleration functions */
Vector3D rtEold, rtMold;


#define Re  6.3710e6       /* radius of the earth, m */
#define G   6.6730e-11     /* m^3/km/s^2,   Gravitational constant */
#define Rm  1.73710e6	   /* mean radius of the Moon, m*/
#define Me  5.9736e24      /* 1 earth mass, kg */
#define Mm  7.3477e22      /* moon mass, kg*/
#define Dem 3.84403e8      /* m, mean distance earth to moon*/
#define LunarMonth (27.321662*86400)  /* Lunar month */

#define Ma (28881.+15188.) /* Apollo 13, Command+Service Module (28881 kg) + Lunar lander (15188 kg) */
#define R0A (Re+175.0e3)    /* 175 km altitude Earth parking orbit */
#define v0A  7820.0	   /* m/s spacecraft velocity in (circular) Earth parking orbit */


// This function is found in an external file: vecFRK4.cpp
Vector3D VecFRK4(int , Vector3D (*f_x)(int, double, Vector3D, Vector3D),
			  Vector3D (*f_v)(int, double, Vector3D, Vector3D),
			  int , double , Vector3D, Vector3D , double );



/* ---------- EARTH-MOON ----------- */
Vector3D f_rEM(int i, double t, Vector3D r, Vector3D v)  /* for Earth */
{
	return(v);
}

Vector3D f_rME(int i, double t, Vector3D r, Vector3D v)  /* for Moon */
{
	return(v);
}

Vector3D f_vEM(int i, double t, Vector3D r, Vector3D v)  /* for Earth, force from Moon */
{

	double REM;
	Vector3D  dvdt, DrEM, FgEM;

	/* this takes the rE-rM vector difference */
	DrEM =  r - rtMold;

	/* here is the magnitude of position vector differences */
	REM = DrEM.GetMagnitude(); // earth to moon

	/* here is the force */
	FgEM = (-G*Me*Mm/(pow(REM,3.))) * DrEM;

	/* return value: the acceleration */
	dvdt = (1./Me)*FgEM;

	return(dvdt); // return the acceleration
}

Vector3D f_vME(int i, double t, Vector3D r, Vector3D v)   /* for Moon, force due to Earth */
{

	double RME;
	Vector3D  dvdt, DrME, FgME;

	/* this takes the rM-rE vector difference */
	DrME = r - rtEold;

	/* here is the magnitude of position vector differences */
	RME = DrME.GetMagnitude(); // moon to earth

	/* here is the force */
	FgME = (-G*Me*Mm/(pow(RME,3.))) * DrME;

	/* return value: the acceleration */
	dvdt = (1./Mm)*FgME;

	return(dvdt);
}
/* -------------------------------- */

/* ------------ APOLLO -------------*/

Vector3D f_rA(int i, double t, Vector3D r, Vector3D v)
{
	return(v);
}

Vector3D f_vA(int i, double t, Vector3D r, Vector3D v)
{
	double REA, RMA;
	Vector3D  dvdt, DrEA, FgEA, DrMA, FgMA;

	/* this takes the rE-rA, rM-rA vector difference */
	DrEA =  r - rtEold;
	DrMA =  r - rtMold;

	/* here are the magnitudes of position vector differences */
	REA = DrEA.GetMagnitude(); // earth to apollo
	RMA = DrMA.GetMagnitude(); // moon to apollo

	/* here are the forces */
	FgEA = (-G*Me*Ma/(pow(REA,3.))) * DrEA;
	FgMA = (-G*Mm*Ma/(pow(RMA,3.))) * DrMA;

	/* return value: the acceleration */
	dvdt = (1./Ma)*( FgEA + FgMA );

	return(dvdt); // return the acceleration
}

/* -------------------------------- */


int main(int argc,char *argv[])
{
  double t, dt, Ttot, v0E, v0M,R, rE, rM, Ee, aA, vA,Dam;
  Vector3D rtE,rtM,rtA,vtE,vtM,vtA,rtAM;
  ofstream outfile;


	if(argc<5){
		fprintf(stderr, "usage: moon_around_earth [total time][angle in degrees][velocity m/s][outfile]\n");
		exit(0);
		}

	Ttot = atof(argv[1]);
	
	aA = (-1.)*atof(argv[2])*M_PI/180.;			// initial launch angle below +x axis
	vA = atof(argv[3]);			// initial launch velocity, assumed instantaneous
	/* Launch note: want ~16.8m/s orbital speed around moon
	   Escape velocity of Earth at parked orbit: ~11033m/s */

	outfile.open(argv[4]);

	t0 = 0.0;     			   // initial time
	dt = 0.1;                  // time step, is this small enough?


	rE = 4670.e3;   // this is the distance from earth center to Earth-Moon barycenter
	rM = Dem-rE;   // distance of Moon center to barycenter

	/* calculate velocities based on the known sidereal Earth-Moon orbital period of 27.322 days */
	v0E = 2.*PI*rE/LunarMonth;  // earth initial velocity around the barycenter, m/s
	v0M = 2.*PI*rM/LunarMonth;  // moon initial velocity around the barycenter, m/s;

	/* all orbits here are PROGRADE: counterclockwise looking from above N pole */
	/* earth's initial velocity */
	Vector3D vtEold(v0E,0.0,0.0);

	/* earth's initial position:  barycenter at origin!! */
	rtEold.update(0.0,-rE,0.0);

	/* moon initial position,  barycentric origin!!  */
	rtMold.update(0.0,rM,0.0);

	/* moon's initial velocity */
	Vector3D vtMold(-v0M,0.0,0.0);
	
	/* apollo's initial position */
	Vector3D rtAold(rE+R0A,0.0,0.0);
	
	/* apollo's initial velocity */
	Vector3D vtAold(v0E,v0A,0.0); 	// need to add earth's velocity for barycentric velocity
	
	/* launch velocity */
	Vector3D launch(vA*cos(aA), vA*sin(aA), 0.0);
	
	/* launch! */
	vtAold = vtAold + launch;

	outfile << "# t   Ex   Ey   Mx   My   Ax   Ay   vA   Dam    angle=" + to_string(aA) + ", vel=" + to_string(vA) << endl;

/* here is the main integration loop, note we are using doubles for indices, OK with care! */
	int ii=0;
	for(t=t0; t<Ttot; t+= dt){

	/* These lines update the position and velocity of Earth */
		rtE = rtEold + VecFRK4(0,f_rEM,f_vEM,ii,t,rtEold,vtEold,dt);
		vtE = vtEold + VecFRK4(1,f_rEM,f_vEM,ii,t,rtEold,vtEold,dt);

	/* These lines update the position and velocity of the Moon */
		rtM = rtMold + VecFRK4(0,f_rME,f_vME,ii,t,rtMold,vtMold,dt);
		vtM = vtMold + VecFRK4(1,f_rME,f_vME,ii,t,rtMold,vtMold,dt);
		
	/* These lines update the position and velocity of Apollo */
		rtA = rtAold + VecFRK4(0,f_rA,f_vA,ii,t,rtAold,vtAold,dt);
		vtA = vtAold + VecFRK4(1,f_rA,f_vA,ii,t,rtAold,vtAold,dt);
		
	/* This records the distance between apollo and the moon */
		rtAM = rtA - rtM;
		Dam = rtAM.GetMagnitude();
		if(Dam<Rm){		// hitting the moon
			outfile << t+dt << " " << " " << rtE.Getx() <<  " " << rtE.Gety() <<  " " << rtM.Getx() << " "  << rtM.Gety() << " "  << rtA.Getx() << " " <<  rtA.Gety() << " " << vtA.GetMagnitude() << " " << Dam << endl;
			break;
		}


	/* set the old values to the new updated values for next iteration */
		rtEold = rtE;
		vtEold = vtE;

		rtMold = rtM;
		vtMold = vtM;
		
		rtAold = rtA;
		vtAold = vtA;
		
//		Ee = 0.5*Me*pow(vtEold.GetMagnitude(), 2.0) + G*Mm*Me / rtEold.GetMagnitude();
//		Em = 0.5*Mm*pow(vtMold.GetMagnitude(), 2.0) + G*Mm*Me / rtMold.GetMagnitude();
//		Etot = Ee + Em;

//	if(ii == 10*2246150){		// correct to orbit moon
//		vtAold = (1.0/10.0)*vtAold;
//	}

	/* we only print values every 50 seconds, but calculate them on a finer scale */
	int div = (int)(50/dt);
	if(ii%div == 0){		// 500 since dt=0.1
		outfile << t+dt << " " << " " << rtE.Getx() <<  " " << rtE.Gety() <<  " " << rtM.Getx() << " "  << rtM.Gety() << " "  << rtA.Getx() << " " <<  rtA.Gety() << " " << vtA.GetMagnitude() << " " << Dam << endl;
		}
	
	if(ii%(1000000) == 0){		// note every 1e5 seconds
		cerr << "Calculating... t = " << t+dt << " ..." << endl;
	}
	ii++;


	  }  /* end of update loop */


}  /* end of main */
