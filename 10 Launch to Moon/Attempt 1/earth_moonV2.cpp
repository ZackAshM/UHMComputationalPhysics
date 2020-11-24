/* earth-moon system equations of motion, and the Apollo 13 spacecraft*/
/* P. Gorham, updated 4/10/2013 for UH Physics 305 */
// g++ earth_moon.cpp 3Vector.o vecFRK4xv.o -o ~/bin/earth_moon

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include "3Vector.h"
// note that the 3vector functions are found in 3vector.cpp

#define Tmax  10000            // seconds, not long enough yet to get to moon
#define PI M_PI


double t0, theta0;

/*  global previous positions for the mass bodies--needed for acceleration functions */
vec3 rtEold, rtMold;


#define Re  6.3710e6       /* radius of the earth, m */
#define G   6.6730e-11     /* m^3/km/s^2,   Gravitational constant */
#define Rm  1.73710e6	   /* mean radius of the Moon */
#define Me  5.9736e24      /* 1 earth mass, kg */
#define Mm  7.3477e22      /* moon mass, kg*/
#define Dem 3.84403e8      /* m, mean distance earth to moon*/
#define Tem 2.36e6		/* sidereal period of earth and moon, in seconds */

#define Ma (28881.+15188.) /* Apollo 13, Command+Service Module (28881 kg) + Lunar lander (15188 kg) */
#define R0A (Re+175.0e3)    /* 175 km altitude Earth parking orbit */
#define v0A  7820.0	   /* m/s spacecraft velocity in (circular) Earth parking orbit */


vec3 f_rEM(double t, vec3 r, vec3 v)  /* for Earth */
{
	return(v);
}



vec3 f_vEM(double t, vec3 r, vec3 v)  /* for Earth, force from Moon */
{

	double REM;
	vec3  dvdt, DrEM, FgEM;

	/* this takes the rE-rM vector difference */
	DrEM = vec3diff( r, rtMold);


	/* here is the magnitude of position vector differences */
	REM = vec3mag(DrEM); // earth to moon


	/* here are the forces in each case */
	FgEM.x = -G*Me*Mm / pow(REM, 3.0) * DrEM.x;
	FgEM.y = -G*Me*Mm / pow(REM, 3.0) * DrEM.y;
	FgEM.z = 0.0;



	/* return value: the acceleration */
	dvdt.x = (FgEM.x)/Me;
	dvdt.y = (FgEM.y)/Me;
	dvdt.z = 0.0;

	return(dvdt); // return the acceleration
}

vec3 f_rME(double t, vec3 r, vec3 v)  /* for Moon */
{
	return(v);
}



vec3 f_vME(double t, vec3 r, vec3 v)   /* for Moon, force due to Earth */
{

	double RME;
	vec3  dvdt, DrME, FgME;

	/* this takes the rM-rE vector difference */
	DrME = vec3diff( r, rtEold);

	/* here is the magnitude of position vector differences */
	RME = vec3mag(DrME); // moon to earth

	/* here are the forces in each case */
	FgME.x = -G*Me*Mm / pow(RME, 3.0) * DrME.x;
	FgME.y = -G*Me*Mm / pow(RME, 3.0) * DrME.y;
	FgME.z = 0.0;



	/* return value: the acceleration */
	dvdt.x = (FgME.x)/Mm;
	dvdt.y = (FgME.y)/Mm;
	dvdt.z = 0.0;

	return(dvdt);
}

vec3 f_rA(double t, vec3 r, vec3 v)
{
	return(v);
}


//vec3 f_vA(double t, vec3 r, vec3 v) /* for Apollo, forces from Earth and Moon */
//{

//	double RAM,RAE;
//	vec3  dvdt, DrAM,DrAE, FgAM, FgAE;

//	/* this takes the rE-rM vector difference */
//	DrAM = vec3diff( r, rtMold));
//	/* this takes the rE-rA vector difference */
//	DrAE = vec3diff( r, rtEold));

//	/* here is the magnitude of position vector differences */
//	RAM = vec3mag(DrAM); // satellite to moon
//	RAE = vec3mag(DrAE); // satellite to earth

//	/* here are the forces in each case */
//	FgAM.x = _____________________________;
//	FgAM.y = _____________________________;
//	FgAM.z = 0.0;

//	FgAE.x = _____________________________;
//	FgAE.y = _____________________________;
//	FgAE.z = 0.0;

//	/* return value: the acceleration */
//	dvdt.x = __________________;
//	dvdt.y = __________________;
//	dvdt.z = 0.0;


//	return(dvdt);
//}

// This function is found in an external file: vecFRK4xv.cpp
extern vec3 vecFRK4xv(int ytype, vec3 (*f_x)(double, vec3, vec3),
			  vec3 (*f_v)(double, vec3, vec3), 
			double t, vec3 xold,vec3 vold,double dt);

main(int argc,char *argv[])
{
  double t, dt, Ttot, v0E, v0M,R, rE, rM, Ee, Em, Etot;
  vec3 rtE,rtM,rtA,rtAold,vtE,vtM,vtA,vtEold,vtMold,vtAold;
  ofstream outfile; 
  int ii; 	//counting index


	if(argc<3){
		fprintf(stderr, "usage: e_m2 [total time][outfile]\n");
		exit(0);
		}

	Ttot = atof(argv[1]);
	outfile.open(argv[2]);
	
	t0 = 0.0;     			   // initial time
	dt = 0.1;                         // time step, is this small enough?

	
	rE = Mm*Dem / (Me+Mm);   // this is the distance from earth center to Earth-Moon barycenter
	rM = Me*Dem / (Me+Mm);   // distance of Moon center to barycenter

	/* calculate velocities based on the known sidereal Earth-Moon orbital period of 27.322 days */
	v0E = 2.*M_PI*rE / Tem;  // earth initial velocity, m/s
	v0M = 2.*M_PI*rM / Tem;  // moon initial velocity, m/s;

	/* all orbits here are PROGRADE: counterclockwise looking from above N pole */
	/* earth's initial velocity */
	vtEold.x = v0E;                     // components of velocity
	vtEold.y = 0.0;
	vtEold.z = 0.0;                     //  in plane motion only here

	/* earth's initial position: CHANGE THIS to put the barycenter at origin!! */
	rtEold.x = 0.0;
	rtEold.y = -rE;   // put it at the "bottom" of cartesian plane
	rtEold.z = 0.0;

	/* moon initial position, YOU MUST MODIFY for barycentric origin!!  */
	rtMold.x = 0.0;
	rtMold.y = rM;   // put it at the 'top' in cartesian plane
	rtMold.z = 0.0;

	/* moon's initial velocity */
	vtMold.x = -v0M;                     // components of velocity
	vtMold.y = 0.0;
	vtMold.z = 0.0;                     // in plane motion only here


	/* initial position of spacecraft, use Earth parking orbit */
	rtAold.x = 0.0;
	rtAold.y = 0.0;//___;   // put it "above" the Earth initially in line with Earth-Moon barycenter
	rtAold.z = 0.0;

	/* Apollo 13 initial velocity rel. to Earth, use Earth parking orbit velocity */
	vtAold.x = -v0A;                     // components of velocity
	vtAold.y = 0.0;
	vtAold.z = 0.0;                     // in plane motion only here
	//vtAold = ___________;  // to get spacecraft barycentric velocity, need to add Earth v!
	
	outfile << "# t  xE  yE  vxE  vyE  xM  yM  vxM  vyM  xA  yA  vxA  vyA  Etot" << endl;

/* here is the main integration loop, note we are using doubles for indices, OK with care! */
	ii = 0;
	for(t=t0; t<Ttot; t+= dt){

	/* These lines update the position and velocity of Earth */
		rtE = vec3sum( rtEold , vecFRK4xv(0,f_rEM,f_vEM,t,rtEold,vtEold,dt) );
		vtE = vec3sum( vtEold , vecFRK4xv(1,f_rEM,f_vEM,t,rtEold,vtEold,dt) );

	/* These lines update the position and velocity of the Moon */
		rtM = vec3sum( rtMold , vecFRK4xv(0,f_rME,f_vME,t,rtMold,vtMold,dt) );
		vtM = vec3sum( vtMold , vecFRK4xv(1,f_rME,f_vME,t,rtMold,vtMold,dt) );

	/* These lines update the position and velocity of the spacecraft */
		//rtA = _______________________________________________________________;
		//vtA = _______________________________________________________________;

	/* set the old values to the new updated values for next iteration */
		rtEold = rtE;
		vtEold = vtE;

		rtMold = rtM;
		vtMold = vtM;

		//rtAold = rtA;
		//vtAold = vtA;
		
		Ee = 0.5*Me*vec3mag(vtEold)*vec3mag(vtEold) + G*Mm/vec3mag(rtEold);
		Em = 0.5*Mm*vec3mag(vtMold)*vec3mag(vtMold) + G*Me/vec3mag(rtMold);
		Etot = Ee + Em;

	/* we only print values every 100 seconds, but calculate them on a finer scale */
	int div = 100/dt;
	if(ii%div == 0){
	
	outfile << t << " " << rtE.x <<  " " << rtE.y <<  " " << vtE.x << " " <<  vtE.y 
			<< " " << rtM.x << " "  << rtM.y << " "  << vtM.x << " " <<  vtM.y 
			<< " " << rtA.x <<  " " << rtA.y <<  " " << vtA.x << " " << vtA.y << " " << Etot << endl;
		}
	if(ii%100000 == 0){cerr << "Calculating... at t = " << t << "..." << endl;}
	ii++;

	   }  /* end of update loop */


}  /* end of main */


