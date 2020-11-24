/* 
************************************************************************
*  integ.c:  Integration using trapezoid, Simpson rules      *
*								       *
*  taken from: "Projects in Computational Physics" by Landau and Paez  * 
*	       copyrighted by John Wiley and Sons, New York            *      
*                                                                      *
*  written by: students in PH465/565, Computational Physics,           *
*	       at Oregon State University                              *
*              code copyrighted by RH Landau                           *
*  supported by: US National Science Foundation, Northwest Alliance    *
*                for Computational Science and Engineering (NACSE),    *
*                US Department of Energy 	                       *
*								       *
*  UNIX (DEC OSF, IBM AIX): cc integ.c -lm                             *
*    			                                               *
*  comment: The derivation from the theoretical result for each method *
*           is saved in x y1 y2 y3 format.			       *
*       
*   Modified 1/21/2013 to c++ for Physics 305, UH Manoa, P. Gorham             *
************************************************************************
*/

using namespace std;       
#include <iostream>       
#include <iomanip>   // this is required to use "setprecision" below
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>           

#define max_in  10000                  /* max number of intervals */
#define vmin -6.0                        /* ranges of integration */
#define vmax 6.0			
//#define ME 2.7182818284590452354E0      /* Euler's number */
// Since we used the math defines above, we can just use M_E for Euler's number...
#define ME M_E

// Defining constants for new chirp function
#define c 340
#define p 1.2
#define w 2*M_PI

double trapez  (int no, double min, double max);    /* trapezoid rule */
double simpson (int no, double min, double max);    /* Simpson's rule */
double f(double);		        	/*  contains function to integrate */

main()
{		 
   double result1, result2, sum1=0.0, sum2=0.0; // declare this within scope of main
   ofstream myfile;  // declare a new instance of an output stream, call it "myfile"
   
 
   myfile.open("finalchirp.dat");  // open is now a method within ofstream class instance outfile
   
   myfile << "# i	Trapez_int	Trapez_sum	Simpson" << endl;
   
   for (int i=3; i<=max_in; i+=2){	   // Simpson's rule requires odd number of intervals
      result1 = trapez(i, vmin, vmax);
      sum1 += result1;
      myfile << i <<"\t"<< setprecision(9) << result1 <<"\t" << setprecision(9) << sum1 << "\t";  // "\t" here gives a tab
      result2 = simpson(i, vmin, vmax);
      sum2 += result2;
      myfile << setprecision(9) << result2 << endl;
   }
   cout << "trapezoidal integral: " << sum1 << endl << "Simpson integral: " << sum2 << endl;
   cout << "data stored in finalchirp.dat" << endl;
   myfile.close();  // close the file, disable any more writing to it, button it up.
}
/*------------------------end of main program-------------------------*/

/* the function we want to integrate */
double f (double x)
{ 
return pow(cos(pow(w*x,3.))*exp(-pow(x/4.,8.)), 2.)/(p*c); // for E/A
// return cos(pow(x,5.))*exp(-pow(x/4.,8.));  // this function for chirp
// return (exp(-x));    // this is exponential
}

/* Integration using trapezoid rule */
double trapez (int no, double min, double max)
{			
   double interval, sum=0., x;		 

   interval = ((max-min) / (no-1));  // this is equivalent to "dt" or "dx" in integral
   
   sum += 0.5 * f(min) * interval; // add the first point
   for (int n=2; n<no; n++)           	/* sum the midpoints */
   {
      x = min + interval * (n-1);      
      sum += f(x)*interval;
   }
   sum += 0.5 *f(max) * interval;	/* add the endpoint */

   return (sum);
}      

/* Integration using Simpson's rule */ 
double simpson (int no, double min, double max)
{  				 
   double interval, sum=0., x;
   interval = ((max -min) /(no-1));
   
   for (int n=2; n<no; n+=2)                /* loop for odd points  */
   {
       x = min + interval * (n-1);
       sum += 4 * f(x);
   }
   for (int n=3; n<no; n+=2)                /* loop for even points  */
   {
      x = min + interval * (n-1);
      sum += 2 * f(x);
   }   
   sum +=  f(min) + f(max);	 	/* add first and last value */          
   sum *= interval/3.;        		/* then multilpy by interval*/
   
   return (sum);
}  
