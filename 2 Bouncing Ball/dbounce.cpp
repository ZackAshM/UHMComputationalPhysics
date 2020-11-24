/*  calculate bouncing ball behavior */
// P. Gorham for UH Physics 305, spring 2016

#include <iostream>       
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>  

using namespace std; 

#define H0 1.0 // meters
#define g 9.80665 // local gravity
#define m 1.0 // kg

// Function declarations:
double tbounce(double);	// half-time of a bounce cycle
double ybounce(double);	// height of a bounce

// start of main program -------------------
main()
{
    int k=0,n=0,Nmax;	// n = number of half bounces
    double C, yterm=0,ysum=0,tterm=0,tsum=0;	// C = restoration coeffcient factor; y/t term = dist / time on specific bounce, y/t sum = total dist / time 
   
	// Here we use a different stream cerr so these prompts don't go into our data file
    cerr << "Enter coefficient of restoration: " << endl;
    cin >> C;
    cerr <<"Enter maximum number of bounces: " << endl;
    cin >> Nmax;
	
	// now print out a data header, the leading hash helps indicate this is not data
	cout << "# Coefficient of restoration: " << C << endl;
	cout << "# Max number of bounces: " << Nmax << endl;
	cout << "#  n    t      tsum      E      y       ysum " << endl;
   
    // Here is the loop calculation of the bounce series, using functions
	// We start by setting the initial energy E, which is pure potential in this moment
	double E = m*g*H0;
	
	// Print out the initial conditions
	// "setprecision" to control number of output digits
	cout <<setprecision(20)<<"  "<< n << " " << tterm << " " << tsum << " " << E << " " << yterm << " " << ysum << endl;	
	// For the intial part of the motion, ball falls before the bounce
	// so we use only half the up-down time -- up-down since the energy is conserved until
	// the next bounce
	tterm = tbounce(E); // this is time for 1/2 round trip. 
	tsum += tterm;
	yterm = ybounce(E); // distance for 1/2 round trip. 
	ysum += yterm;
	n++; // This is going to be the half-round-trip counter
	cout <<setprecision(20)<<"  "<< n << " " << tterm << " " << tsum << " " << E << " " << yterm << " " << ysum << endl;
	E *= C;  // at the bounce energy is fractionally decreased
    for(k=0;k<Nmax;k++){
        tterm = tbounce(E);
		tsum += 2.*tterm; // up then down gives factor of 2
		yterm = ybounce(E);
		ysum += 2.*yterm;
		n += 2;  // add two half-bounces to the total
	cout <<setprecision(20)<<"  "<< n << " " << tterm << " " << tsum << " " << E << " " << yterm << " " << ysum << endl;
		E *= C;
        }
} // end of main ------------------------------

/* FUNCTION DEFINITIONS FOLLOW */
//-------------------------------------------

double tbounce(double Eb) 
{
    double t =  pow(2*Eb/m, 0.5)/g; // calculate the time for half a round trip
    return(t);
}

//-------------------------------------------

double ybounce(double Eb)
{
    double y = Eb/(m*g);  // calculate the distance for half a round trip
    return (y);
}
