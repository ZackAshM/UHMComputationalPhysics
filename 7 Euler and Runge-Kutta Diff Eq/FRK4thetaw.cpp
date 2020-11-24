/* FRK4thetaw: a function to calculate fourth-order Runge-Kutta
   for 1-dimensional F = dp/dt = f(theta(t),w(t)) (Newton force law) 
   the user must supply the functions f_theta, f_w which determine
   the return walue.
   Both theta and w increments must be calculated at each step in 
   the integration of the equation, and thetaold and wold must be
   reset after each step 

--P. Gorham: updated 3/19/2007 for Physics 305, add ethetaplicit time dependence,
correct error in prewious wersion */

double FRK4thetaw(int ytype, double (*f_theta)(double, double, double), 
			 double (*f_w)(double, double, double),
               		 double t,double thetaold,double wold,double dt)

/* ytype = 0 for theta(t) increment, 1 for w(t) increment,
thetaold, wold, prewious position and welocity
   t=time wariable, dt = step size

   double (*f_theta)(double, double ,double) ==> pointer to a function of
   three doubles that returns a double. Note the order: the f_theta function
   comes first in the argument list.
*/

{
	double k1theta, k2theta, k3theta, k4theta, k1w, k2w, k3w, k4w, k5;

		k1theta = dt*(*f_theta)(t, thetaold, wold);
		k1w = dt*(*f_w)(t, thetaold, wold);
		k2theta = dt*(*f_theta)(t+dt/2.0, thetaold+k1theta/2.0, wold+k1w/2.0);
		k2w = dt*(*f_w)(t+dt/2.0, thetaold+k1theta/2.0, wold+k1w/2.0);
		k3theta = dt*(*f_theta)(t+dt/2.0, thetaold+k2theta/2.0, wold+k2w/2.0);
		k3w = dt*(*f_w)(t+dt/2.0, thetaold+k2theta/2.0, wold+k2w/2.0);
		k4theta = dt*(*f_theta)(t+dt, thetaold+k3theta, wold+k3w);
		k4w = dt*(*f_w)(t+dt, thetaold+k3theta, wold+k3w);
	if(ytype==0){
		k5 = (k1theta + 2.0*k2theta + 2.0*k3theta + k4theta)/6.0;
		}else{  /* ytype = 1 */
		k5 = (k1w + 2.0*k2w + 2.0*k3w + k4w)/6.0;
	}
	
	return(k5);  // add this value to the previous w or theta
}


/* the following are examples of the form of the functions needed.
  In practice you should put the relevant functions in the source
  code that contains the loop for integration of the position
  and velocity */

/*the dtheta/dt function only requires returning the velocity--no action 
double f_theta (double theta, double w)
{
	return (w);
}
// Here is the actual force law
double f_dwdt( double theta, double w)
{
insert the proper force law into the return value
	double retval;
	return( retval );
}
*/
