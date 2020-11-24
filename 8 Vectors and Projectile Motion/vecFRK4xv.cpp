/* vecFRK4xv: a function to calculate fourth-order Runge-Kutta
   for 1-dimensional F = dp/dt = f(x(t),v(t)) (Newton force law) 
   
   Both x and v increments must be calculated at each step in 
   the integration of the equation, and xold and vold must be
   reset after each step 
 --P. Gorham: updated 3/20/2007 for Physics 305, add explicit time dependence,
correct error in previous version  */
// this version for c++ usage

#include "3Vector.h"

// Here is the primary function

vec3 vecFRK4xv(int ytype, vec3 (*f_x)(double, vec3, vec3),
			  vec3 (*f_v)(double, vec3, vec3),
			  double t,vec3 xold,vec3 vold,double dt)

/*	ytype = 0 for x-equation, 1 for v-equation
  	f_x = user supplied function for dx/dt=v
	f_v: force equation as noted above
	t=time, xold, vold, prior position and velocity
   	dt = step size

   vec3 (*f_xv)(double, vec3, vec3) ==> pointer to a function of
   two vec3s that returns a vec3. Either dv/dt or dx/dt.

	4th order general form:
    y(t+dt) = y(t) + 1/6 * (k1 + 2k2 + 2k3 + k4)
			k1 = dt * f(t,y)
                      	k2 = dt * f(t+dt/2, y(t) + k1/2)
                        k3 = dt * f(t+dt/2, y(t) + k2/2)
                	k4 = dt * f(t+dt, y(t) + k3)

Error in k4 term corrected below --PG 4/24/07
*/

{
	vec3 k1x,k2x,k3x,k1v,k2v,k3v,k4x,k4v,k2x2,k2v2,k3x2,k3v2;

		k1x = scalar_vec3mult(dt, (*f_x)(t, xold, vold));
		k1v = scalar_vec3mult(dt, (*f_v)(t, xold, vold));
		
		k2x = scalar_vec3mult(dt, (*f_x)(t+dt/2.0,
			vec3sum(xold,scalar_vec3mult(0.5,k1x)),
			vec3sum(vold,scalar_vec3mult(0.5,k1v))));
		k2v = scalar_vec3mult(dt, (*f_v)(t+dt/2.0,
			vec3sum(xold,scalar_vec3mult(0.5,k1x)),
			vec3sum(vold,scalar_vec3mult(0.5,k1v))));
		
		k3x = scalar_vec3mult(dt, (*f_x)(t+dt/2.0,
			vec3sum(xold,scalar_vec3mult(0.5,k2x)),
			vec3sum(vold,scalar_vec3mult(0.5,k2v))));
		k3v = scalar_vec3mult(dt, (*f_v)(t+dt/2.0,
			vec3sum(xold,scalar_vec3mult(0.5,k2x)),
			vec3sum(vold,scalar_vec3mult(0.5,k2v))));

		k4x = scalar_vec3mult(dt, (*f_x)(t+dt,
			vec3sum(xold,k3x),
			vec3sum(vold,k3v)));
		k4v = scalar_vec3mult(dt, (*f_v)(t+dt,
			vec3sum(xold,k3x),
			vec3sum(vold,k3v)));

		k2x2 = scalar_vec3mult(2.0,k2x);
		k2v2 = scalar_vec3mult(2.0,k2v);
		k3x2 = scalar_vec3mult(2.0,k3x);
		k3v2 = scalar_vec3mult(2.0,k3v);

	if(ytype==0){
		return( scalar_vec3mult((1.0/6.0),
				vec3sum4(k1x,k2x2,k3x2,k4x)) ); 
		} else { 
		return( scalar_vec3mult((1.0/6.0),
				vec3sum4(k1v,k2v2,k3v2,k4v)) ); 
	}
}


