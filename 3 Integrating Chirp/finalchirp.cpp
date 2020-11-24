using namespace std;       
#include <iostream>       
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>           

#define max_in  100000 // gives stable value               /* max number of intervals */
#define vmin -6.0                        /* ranges of integration */
#define vmax 6.0			
//#define ME 2.7182818284590452354E0      /* Euler's number */
// Since we used the math defines above, we can just use M_E for Euler's number...
#define ME M_E

// Defining constants for new chirp function
#define c 340
#define p 1.2
#define w 2*M_PI

ofstream myfile;
// int max_in;
double f(double);
double int_trap(double min, double max);
double result;		 

main()
{

myfile.open("fchirp1.dat"); 
myfile << "i	t	sum" << endl;

// cout << "Enter the number of intervals: ";  
// cin >> max_in;

int_trap(vmin, vmax);

// cout << "E/A = " << result << endl;
cout << "data stored in fchirp1.dat" << endl;
myfile.close();

}

double f (double x)
{ 
return pow(cos(pow(w*x,3.))*exp(-pow(x/4.,8.)), 2.)/(p*c);
}

double int_trap(double min, double max)
{
double result = 0.0, dt, t;
dt = (max - min)/max_in;

for(int i=0; i<max_in; i++){
t = min + i*dt;
result += 0.5*dt*(f(t) + f(t + dt));

myfile << i << "\t" << t << "\t" << result << endl;
}
return result;

}


