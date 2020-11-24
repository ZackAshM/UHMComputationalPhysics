/* earth-moon system equations of motion, */
/* P. Gorham, 4/10/2019 helper code for UH Physics 305 */
// g++ moon_around_earth.cpp VecFRK4.cpp -o ~/bin/moon_around_earth


#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include "Vector3D.h"


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
//#define Mm Me				/* testing equal mass */
#define Dem 3.84403e8      /* m, mean distance earth to moon*/
#define LunarMonth (27.321662*86400)  /* Lunar month */


// This function is found in an external file: vecFRK4.cpp
Vector3D VecFRK4(int , Vector3D (*f_x)(int, double, Vector3D, Vector3D),
			  Vector3D (*f_v)(int, double, Vector3D, Vector3D),
			  int , double , Vector3D, Vector3D , double );



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


int main(int argc,char *argv[])
{
  double t, dt, Ttot, v0E, v0M,R, rE, rM, Ee, Em, Etot, dist_mag;
  Vector3D rtE,rtM,rtA,vtE,vtM,vtA, dist;
  ofstream outfile;


	if(argc<3){
		fprintf(stderr, "usage: moon_around_earth [total time][outfile]\n");
		exit(0);
		}

	Ttot = atof(argv[1]);

	outfile.open(argv[2]);

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
//	Vector3D vtMold(-v0M,0.0,0.0);
	Vector3D vtMold(-(4./10.)*v0M,0.0,0.0);		// testing
	
//	Vector3D vtMold(0.0,0.0,0.0);		// testin: falling into each other
//	Vector3D vtEold(0.0,0.0,0.0);

	outfile << "# t   Ex   Ey   vEx   vEy   Mx   My   vMx   vMy   Etot" << endl;

/* here is the main integration loop, note we are using doubles for indices, OK with care! */
	int ii=0;
	for(t=t0; t<Ttot; t+= dt){

	/* These lines update the position and velocity of Earth */
		rtE = rtEold + VecFRK4(0,f_rEM,f_vEM,ii,t,rtEold,vtEold,dt);
		vtE = vtEold + VecFRK4(1,f_rEM,f_vEM,ii,t,rtEold,vtEold,dt);

	/* These lines update the position and velocity of the Moon */
		rtM = rtMold + VecFRK4(0,f_rME,f_vME,ii,t,rtMold,vtMold,dt);
		vtM = vtMold + VecFRK4(1,f_rME,f_vME,ii,t,rtMold,vtMold,dt);


	/* set the old values to the new updated values for next iteration */
		rtEold = rtE;
		vtEold = vtE;

		rtMold = rtM;
		vtMold = vtM;
		
		Ee = 0.5*Me*pow(vtEold.GetMagnitude(), 2.0) + G*Mm*Me / rtEold.GetMagnitude();
		Em = 0.5*Mm*pow(vtMold.GetMagnitude(), 2.0) + G*Mm*Me / rtMold.GetMagnitude();
		Etot = Ee + Em;

	dist = rtEold - rtMold;
	dist_mag = dist.GetMagnitude();
	if(dist_mag<(Re+Rm)){		// do they run into each other?
		outfile << t+dt << " " << " " << rtE.Getx() <<  " " << rtE.Gety() <<  " " << vtE.Getx() << " " <<  vtE.Gety()
			<< " " << rtM.Getx() << " "  << rtM.Gety() << " "  << vtM.Getx() << " " <<  vtM.Gety() << " " << Etot << endl;
		break;
	}

	/* we only print values every 50 seconds, but calculate them on a finer scale */
	int div = (int)(50/dt);
	if(ii%div == 0){		// 500 since dt=0.1
		outfile << t+dt << " " << " " << rtE.Getx() <<  " " << rtE.Gety() <<  " " << vtE.Getx() << " " <<  vtE.Gety()
			<< " " << rtM.Getx() << " "  << rtM.Gety() << " "  << vtM.Getx() << " " <<  vtM.Gety() << " " << Etot << endl;
		}
	
	if(ii%(1000000) == 0){		// note every 1e5 seconds
		cerr << "Calculating... t = " << t+dt << " ..." << endl;
	}
	ii++;


	  }  /* end of update loop */


}  /* end of main */
