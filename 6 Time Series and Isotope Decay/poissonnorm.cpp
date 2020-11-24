using namespace std;       
#include <iostream>       
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>           

// #define max_in variable (dep on vmax)             /* max number of intervals */
#define vmin 0                        /* ranges of integration */
// vmax variable		
//#define ME 2.7182818284590452354E0      /* Euler's number */
// Since we used the math defines above, we can just use M_E for Euler's number...
#define ME M_E


int fact(int n);
double f(int k);
double int_trap(double min, double max);

double mu=1.0;
int max_in=10000, vmax=1;	 

main(int argc, char** argv)
{

if (argc>1){	// choosing vmax
vmax = atoi(argv[1]);
}
cout << "vmax = " << vmax << endl;
max_in = 10000*vmax;

if (argc>2){	// choosing mean value
mu = atoi(argv[2]);
}
cout << "mean = " << mu << endl;

cout << "p("<<mu<<", "<<vmax<<") = " << int_trap(vmin, vmax) << endl;

}

int fact(int n)
{
int product=1;
for(int i=0;i<n;i++){
product *= n-i;
}
return product;
}

double f(int k)	// integral function
{ 
return pow(mu, k)*exp(-mu) / fact(k);	// y is the iterative index from 3 to n
}

double int_trap(double min, double max)	// trapezoidal method of integration
{
double result = 0.0, dt, t;
dt = (max - min)/max_in;

for(int i=0; i<max_in; i++){
t = min + i*dt;
result += 0.5*dt*(f(t) + f(t + dt));

}
return result;
}


