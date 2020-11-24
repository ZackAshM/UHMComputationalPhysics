/* 3-vector cartesian include file */
/* P. Gorham 4/10/13 */

#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include <cmath>

/* this structure type is for a 3-d vector */
typedef struct {
		double x, y, z;
		} vec3;

/*  general vector functions */

vec3  vec3sum( vec3 , vec3 );  // sum of two vectors

vec3  vec3diff( vec3 , vec3 );  // difference of two vectors

vec3  scalar_vec3sum( double , vec3 ); // sum of scalar and vector


double vec3mag (vec3 );  // _magnitude of vector

vec3 vec3zero();	// create zero vector


vec3  scalar_vec3mult( double , vec3 );  // scalar times vector

double vec3dot ( vec3 , vec3  );  // dot product

vec3 vec3cross ( vec3 , vec3  );  // cross product


vec3 vec3norm ( vec3  );  // return unit vector for _A 


// add 3 vectors at once
vec3  vec3sum3( vec3 , vec3 , vec3 );

// add 4 vectors at once
vec3  vec3sum4( vec3 , vec3 , vec3 , vec3 );

// print vector, insert inside cout
void vec3print( vec3 );


#endif
