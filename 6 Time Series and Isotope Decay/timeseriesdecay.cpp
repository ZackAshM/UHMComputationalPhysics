// Simulation of times series of radioactive decays
// Zachary Martin, 2/20/2019 for Physics 305 

using namespace std;       
#include <iostream>       
#include <iomanip>   // required to use "setprecision" if needed
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>  

#define seed 2202019253
#define M 1000000

main(int argc, char *argv[])
{

   double *x, *y, dt=0.01; //dt is the time interval (ms)
   x = new double [M]();
   y = new double [M]();
   double q = .001;

   srand48(seed);

   ofstream outfile;
   outfile.open("timeseriesdecay.dat");
   
   outfile << "# x	t(s)  t(min)  y" << endl;

   for (int i=0; i<M; i++){
      x[i] = drand48();
      if (x[i] > q){
         y[i] = 0.;
      }else if (x[i] <= q){
         y[i] = 1.;
      }
      outfile << x[i] <<" "<< i*dt <<" "<< i*dt/60. <<" "<< y[i] << endl;	//i*dt [s], i*dt/60 [min]
   }

   cerr << "data stored in timeseriesdecay.dat" << endl;
   outfile.close();



}	//---------END OF MAIN-----------------



