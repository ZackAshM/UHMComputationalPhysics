// example of how to use typedef for a 3vector, along with
//some vector function definitions --P. Gorham 3/10/03 for P305 
// updated to c++ March 2013

#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
using namespace std;

#include "3Vector.h"

		
// these are general vector routines. Functions that return vectors must be returned to a vector
// , must pass vectors back and forth



vec3  vec3sum( vec3 _A, vec3 _B)  // sum of two vectors
{
	vec3 _tmp;
	_tmp.x = _A.x + _B.x;
	_tmp.y = _A.y + _B.y;
	_tmp.z = _A.z + _B.z;
	return(_tmp);
}
vec3  vec3diff( vec3 _A, vec3 _B)  // difference of two vectors
{
	vec3 _tmp;
	_tmp.x = _A.x - _B.x;
	_tmp.y = _A.y - _B.y;
	_tmp.z = _A.z - _B.z;
	return(_tmp);
}
vec3  scalar_vec3sum( double _A, vec3 _B) // sum of scalar and vector
{
	vec3 _tmp;
	_tmp.x = _A + _B.x;
	_tmp.y = _A + _B.y;
	_tmp.z = _A + _B.z;
	return(_tmp);
}

double vec3mag (vec3 _A)  // _magnitude of vector
{
	return( sqrt(_A.x*_A.x+_A.y*_A.y+_A.z*_A.z));
}

vec3 vec3zero()	// create zero vector
{
	vec3 _tmp;
	_tmp.x = 0.0;
	_tmp.y = 0.0;
	_tmp.z = 0.0;
	return(_tmp);
}

vec3  scalar_vec3mult( double _A, vec3 _B)  // scalar times vector
{
	vec3 _tmp;
	_tmp.x = _A*_B.x;
	_tmp.y = _A*_B.y;
	_tmp.z = _A*_B.z;
	return(_tmp);
}
double vec3dot ( vec3 _A, vec3 _B )  // dot product
{
	double _tmp;
	_tmp = _A.x*_B.x + _A.y*_B.y + _A.z*_B.z;
	return(_tmp);
}
vec3 vec3cross ( vec3 _A, vec3 _B )  // cross product
{
	vec3 _tmp;
	_tmp.x = _A.y*_B.z - _A.z*_B.y;
	_tmp.y = _A.z*_B.x - _A.x*_B.z;
	_tmp.z = _A.x*_B.y - _A.y*_B.x;
	return(_tmp);
}

vec3 vec3norm ( vec3 _A )  // return unit vector for _A 
{	
	vec3 _tmp;
	double _mag;
	_mag = sqrt(_A.x*_A.x+_A.y*_A.y+_A.z*_A.z);
	_tmp.x = _A.x/_mag;
	_tmp.y = _A.y/_mag;
	_tmp.z = _A.z/_mag;
	return(_tmp);
}

// add 3 vectors at once
vec3  vec3sum3( vec3 X, vec3 Y, vec3 Z)
{
	vec3 tmp;
	tmp.x = X.x+Y.x+Z.x;
	tmp.y = X.y+Y.y+Z.y;
	tmp.z = X.z+Y.z+Z.z;
	return(tmp);
}
// add 4 vectors at once
vec3  vec3sum4( vec3 W, vec3 X, vec3 Y, vec3 Z)
{
	vec3 tmp;
	tmp.x = W.x+X.x+Y.x+Z.x;
	tmp.y = W.y+X.y+Y.y+Z.y;
	tmp.z = W.z+X.z+Y.z+Z.z;
	return(tmp);
}

// insert inside cout
void vec3print(vec3 X)
{
	cout <<"("<<X.x<<", "<<X.y<<", "<<X.z<<")";
}
