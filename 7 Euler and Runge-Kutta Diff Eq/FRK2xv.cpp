/* FRK2xv: a function to calculate second-order Runge-Kutta
   for 1-dimensional F = dp/dt = f(x(t),v(t)) (Newton force law) 
   the user must supply the functions f_x, f_v which determine
   the return value.
   Both x and v increments must be calculated at each step in 
   the integration of the equation, and xold and vold must be
   reset after each step 

--P. Gorham: updated 3/19/2007 for Physics 305, add explicit time dependence,
correct error in previous version */

double FRK2xv(int ytype, double (*f_x)(double, double, double), 
			 double (*f_v)(double, double, double),
               		 double t,double xold,double vold,double dt)

/* ytype = 0 for x(t) increment, 1 for v(t) increment,
xold, vold, previous position and velocity
   t=time variable, dt = step size

   double (*f_x)(double, double ,double) ==> pointer to a function of
   three doubles that returns a double. Note the order: the f_x function
   comes first in the argument list.
*/

{
	double k1x, k1v, k2;

		k1x = dt*(*f_x)(t, xold, vold);
		k1v = dt*(*f_v)(t, xold, vold);
	if(ytype==0){
		k2 = dt*(*f_x)( t, xold+k1x/2.0, vold+k1v/2.0 );
		}else{  /* ytype = 1 */
		k2 = dt*(*f_v)( t, xold+k1x/2.0, vold+k1v/2.0 );
	}
	
	return(k2);  // add this value to the previous v or x
}


/* the following are examples of the form of the functions needed.
  In practice you should put the relevant functions in the source
  code that contains the loop for integration of the position
  and velocity */

/*the dx/dt function only requires returning the velocity--no action 
double f_x (double x, double v)
{
	return (v);
}
// Here is the actual force law
double f_dvdt( double x, double v)
{
insert the proper force law into the return value
	double retval;
	return( retval );
}
*/
