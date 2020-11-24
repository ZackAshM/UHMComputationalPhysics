// c++ program to calculate area of a circle, P. Gorham for Physics 305 UHM
// to compile, use ' g++ area.cpp -o area '

// Change 1: While loop

using namespace std;  
#include <iostream> 
#define _USE_MATH_DEFINES  
#include <cmath>           

int main() 
{

	double r;  
	r= 1.0;
	while(r>=0.0) 
		{	// 

		cout << "Enter the radius of the circle:" << endl;  
		cin >> r;
		double A = M_PI*pow(r,2.);
		cout << "For radius " << r << " the Area is " << A << endl;
    		    cout << endl << endl << "Bye!" << endl;
        
      	}

	return 0; 

}
