// c++ program to test 3Vector typedef
using namespace std;       
#include <iostream>        
#define _USE_MATH_DEFINES  
#include <cmath>  
#include "3Vector.h"        

int main()
{                  // begin the main program body
	 vec3 v1,v2,v3;
	 v1.x = 3.0; v1.y = 6.0; v1.z = 9.0;
	 v2.x = 1.0; v2.y = 5.0; v2.z = 7.5;
	 v3.x = 2.0; v3.y = 4.0; v3.z = 6.0;
	 	 
	double v1dotv3 = vec3dot(v1,v3);
	cout << "v1 = "; vec3print(v1); cout<<endl;
	cout << "v2 = "; vec3print(v2); cout<<endl;
	cout << "v3 = "; vec3print(v3); cout<<endl;
	
	cout << "v1 dot v3 = "<<v1dotv3<<endl;
	cout << "norm v1 = "; vec3print(vec3norm(v1)); cout<<endl;
	cout << "v1 cross v2 = "; vec3print(vec3cross(v1, v2)); cout<<endl;
	cout << "mag (v1 cross v2) = " << vec3mag(vec3cross(v1, v2)) <<endl;
	vec3 v0 = vec3zero();
	cout << "zero vector = "; vec3print(v0); cout<<endl;
	
}  
