// /* earth-moon system equations of motion, and the Apollo 13 spacecraft*/
/* P. Gorham, updated 4/5/2016 for UH Physics 305 */
// This version uses vector class
//  g++ VecFRK4.cpp initialize_atmosphere.cpp earth_moonV3.cpp -o ~/bin/earth_moonV3

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include "Vector3D.h"

double t;

/*  global previous positions for the mass bodies--needed for acceleration functions */
Vector3D rtEold, rtMold;
ofstream notefile;


#define Re  6.3710e6       /* radius of the earth, m */
#define G   6.6730e-11     /* m^3/kg/s^2,   Gravitational constant */
#define Rm  1.73710e6	   /* mean radius of the Moon */
#define Me  5.9736e24      /* 1 earth mass, kg */
#define Mm  7.3477e22      /* moon mass, kg*/
#define Dem 3.84403e8      /* m, mean distance earth to moon*/
#define Ma (28881.+15188.) /* Apollo 13, Command+Service Module (28881 kg) + Lunar lander (15188 kg) */
#define R0A (Re+175.0e3)    /* 175 km altitude Earth parking orbit */
#define v0A  7820.0	   /* m/s spacecraft velocity in (circular) Earth parking orbit */
#define Tem 2.36e6		/* sidereal period of earth and moon, in seconds */


// This function is found in an external file: vecFRK4.cpp
extern Vector3D VecFRK4(int , Vector3D (*f_x)(int, double, Vector3D, Vector3D),
			  Vector3D (*f_v)(int, double, Vector3D, Vector3D),
			  int , double , Vector3D, Vector3D , double );

// this function is complete: gives the formal definition dx/dt=v
Vector3D f_x(int i, double t, Vector3D r, Vector3D v)
{
	return(v);
}

/*

// this function should return the mass of the satellite throughout launch
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

// drag force on satellite ----------------------------------
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

// this function should return the force/mass=acceleration as a 
// function of the position and velocity vectors, based on the force law
Vector3D f_v(int i, double t, Vector3D r, Vector3D v)
{
    Vector3D dvdt;
//	acceleration law: dvdt = 1./m_t(t) * ( (Fg(r)+Fn(t)) + Fb(v,r) + Fp(m_t(t),v,t)  );

	dvdt = (1./m_t(t)) * (Fgn(r,t) + Fb(v,r,t) + Fp(m_t(t),v,t));		
        return(dvdt);

}

*/

Vector3D f_rEM(int i, double t, Vector3D r, Vector3D v)  /* for Earth */
{
	return(v);
}



Vector3D f_vEM(int i, double t, Vector3D r, Vector3D v)  /* for Earth, force from Moon */
{

	double REM;
	Vector3D  dvdt, DrEM, FgEM;

	/* this takes the rE-rM vector difference */
	DrEM = r - rtMold;

	/* here is the magnitude of position vector differences */
	REM = DrEM.GetMagnitude(); // earth to moon

	/* here is the force in each case */
	FgEM = -G*Me*Mm / pow(REM, 3.0) * DrEM;

	/* return value: the acceleration */
	dvdt = FgEM*(1.0/Me);

	return(dvdt); // return the acceleration
}

Vector3D f_rME(int i, double t, Vector3D r, Vector3D v)  /* for Moon */
{
	return(v);
}



Vector3D f_vME(int i, double t, Vector3D r, Vector3D v)   /* for Moon, force due to Earth */
{

	double RME;
	Vector3D  dvdt, DrME, FgME;

	/* this takes the rM-rE vector difference */
	DrME = r - rtEold;

	/* here is the magnitude of position vector differences */
	RME = DrME.GetMagnitude(); // moon to earth

	/* here are the forces in each case */
	FgME = -G*Me*Mm*DrME * (1.0/pow(RME, 3.0));

	/* return value: the acceleration */
	dvdt = FgME*(1.0/Mm);


	return(dvdt);
}

// Testers -----------------------------------

Vector3D f_vEMt(int i, double t, Vector3D r, Vector3D v)  /* for Earth, force from Moon */
{

	double REM;
	Vector3D  dvdt, DrEM, FgEM;

	/* this takes the rE-rM vector difference */
	DrEM = r - rtMold;
	notefile << "earth vector = " << r.printt() << endl;
	notefile << "moon vector = " << rtMold.printt() << endl;
	notefile << "distance vector rE-rM = " << DrEM.printt() << endl;


	/* here is the magnitude of position vector differences */
	REM = DrEM.GetMagnitude(); // earth to moon
	notefile << "distance from earth to moon = " << REM << endl;

	/* here is the force in each case */
	FgEM = -G*Me*Mm / pow(REM, 3.0) * DrEM;

	/* return value: the acceleration */
	dvdt = FgEM*(1.0/Me);
	notefile << "dvdt = ";

	return(dvdt); // return the acceleration
}

Vector3D f_vMEt(int i, double t, Vector3D r, Vector3D v)   /* for Moon, force due to Earth */
{

	double RME;
	Vector3D  dvdt, DrME, FgME;

	/* this takes the rM-rE vector difference */
	DrME = r - rtEold;
	notefile << "rM = " << r.printt() << endl;
	notefile << "rtEold = " << rtEold.printt() << endl;

	/* here is the magnitude of position vector differences */
	RME = DrME.GetMagnitude(); // moon to earth

	/* here are the forces in each case */
	FgME = -G*Me*Mm*DrME * (1.0/pow(RME, 3.0));

	/* return value: the acceleration */
	dvdt = FgME*(1.0/Mm);
	notefile << "dvdt = ";


	return(dvdt);
}

// ----------------------------------------------------

Vector3D f_rA(int i, double t, Vector3D r, Vector3D v)
{
	return(v);
}



Vector3D f_vA(int i, double t, Vector3D r, Vector3D v) /* for Apollo, forces from Earth and Moon */
{

	double RAM,RAE;
	Vector3D  dvdt, DrAM,DrAE, FgAM, FgAE;

	/* this takes the rE-rM vector difference */
	DrAM = r - rtMold;
	/* this takes the rE-rA vector difference */
	DrAE = r - rtEold;

	/* here is the magnitude of position vector differences */
	RAM = DrAM.GetMagnitude(); // satellite to moon
	RAE = DrAE.GetMagnitude(); // satellite to earth

	/* here are the forces in each case */
	FgAM = G*Ma*Mm*DrAM * (1.0/pow(RAM, 3.0));

	FgAE = G*Me*Ma*DrAE * (1.0/pow(RAE, 3.0));

	/* return value: the acceleration */
	dvdt = (1./Ma)*(FgAM + FgAE);

	return(dvdt);
}



int main(int argc,char *argv[])
{
  Vector3D xt,vt,Fg1,Fp1,Fb1;
  Vector3D rtE, vtE, rtM, vtM, rtA, vtA;
  double t, dt, nO, nN2, nO2;
  double vt0,v0,theta0,t0,Ttot;
  double rE, rM, v0E, v0M; 
  int i;
  double Ee, Em, Etot;
   ofstream outfile; 
   ifstream inFile;
   
	if(argc<3){
		cerr << "usage: e_m [total time][outfile]" << endl;
		exit(0);
		}
 
 	Ttot = atof(argv[1]);
	outfile.open(argv[2]);
	notefile.open("em_notes.dat");
	
	t0 = 0.0;     			   // initial time
	dt = 0.01;                   // time step, is this small enough?

	rE = Mm*Dem / (Me+Mm);   // this is the distance from earth center to Earth-Moon barycenter
	rM = Me*Dem / (Me+Mm);   // distance of Moon center to barycenter

	/* calculate velocities based on the known sidereal Earth-Moon orbital period of 27.322 days */
	v0E = 2.*M_PI*rE / Tem;  // earth initial velocity, m/s
	v0M = 2.*M_PI*rM / Tem;  // moon initial velocity, m/s;
	
	v0 = 0.0;                // initial velocity, m/s
	t0 = 0.0;
	
	Vector3D vtEold(0.0,0.0,0.0);          // Earth initials
	rtEold = Vector3D(rE,0.0,0.0);
	Vector3D vtMold(0.0,0.0,0.0);          // Moon initials
	rtMold = Vector3D(-rM,0.0,0.0);
	Vector3D vtAold(0.0,0.0,0.0);          // Apollo initials, make sure in barycentric frame!
	Vector3D rtAold(0.0,0.0,0.0);	
	
	notefile << "initials: CM-E dist, CM-M dist, rtEold, rtMold = " << rE<<", "<<rM<<", "<<rtEold.printt()<<", "<<rtMold.printt() << endl;
	
	Ee = 0.5*Me*pow(vtEold.GetMagnitude(), 2.0) + G*Mm*Me / rtEold.GetMagnitude();
	Em = 0.5*Mm*pow(vtMold.GetMagnitude(), 2.0) + G*Mm*Me / rtMold.GetMagnitude();
	Etot = Ee + Em;


	// print out starting values for Earth, Moon, and Apollo
	
	 outfile << "# t  xE  yE  xM  yM  xA  yA  Etot" << endl;
	 outfile << t0 <<"  "<< rtEold.Getx() <<"  "<< rtEold.Gety() <<"  "<< rtMold.Getx() <<"  "<< rtMold.Gety() <<"  "<< rtAold.Getx() <<"  "<< rtAold.Gety() << Etot << endl;

	 int ii=0;
	for(t=0.0; t<Ttot; t+= dt){

		rtE =  rtEold + VecFRK4(0,f_rEM,f_vEM,ii,t,rtEold,vtEold,dt);
		vtE =  vtEold + VecFRK4(0,f_rEM,f_vEM,ii,t,rtEold,vtEold,dt);		
	
		rtM =  rtMold + VecFRK4(0,f_rME,f_vME,ii,t,rtMold,vtMold,dt);
		vtM =  vtMold + VecFRK4(0,f_rME,f_vME,ii,t,rtMold,vtMold,dt);		
		
	/* These lines update the position and velocity of the spacecraft */
//		rtA = 0.0;
//		vtA = 0.0;
		
	/* set the old values to the new updated values for next iteration */
		rtEold = rtE;
		vtEold = vtE;

		rtMold = rtM;
		vtMold = vtM;

//		rtAold = rtA;
//		vtAold = vtA;

	// Energy
		Ee = 0.5*Me*pow(vtEold.GetMagnitude(), 2.0) + G*Mm*Me / rtEold.GetMagnitude();
		Em = 0.5*Mm*pow(vtMold.GetMagnitude(), 2.0) + G*Mm*Me / rtMold.GetMagnitude();
		Etot = Ee + Em;
		
		ii++;  // generic index if needed
		
		notefile << "t = " << t << endl;
		notefile << "Earth: "<<endl<< f_vEMt(ii, t, rtEold, vtEold).printt() << endl;
		notefile << "Moon: "<<endl<< f_vMEt(ii, t, rtMold, vtMold).printt() << endl << endl;

/* test: earth and moon falling into each other */	
	if(rtEold.Getx()<=0.0){
		outfile << t <<"  "<< rtEold.Getx() <<"  "<< rtEold.Gety() <<"  "<< rtMold.Getx() <<"  "<< rtMold.Gety() <<"  "<< rtAold.Getx() <<"  "<< rtAold.Gety() << Etot << endl;
		break;
	}
		
	// print out calculated values for Earth, Moon, and Apollo 

	 outfile << t <<"  "<< rtEold.Getx() <<"  "<< rtEold.Gety() <<"  "<< rtMold.Getx() <<"  "<< rtMold.Gety() <<"  "<< rtAold.Getx() <<"  "<< rtAold.Gety() << Etot << endl;
	

	}  // end of main loop over time

	  outfile.close();
	  notefile.close();

}


