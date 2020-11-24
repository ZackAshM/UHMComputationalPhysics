// c++ program to calculate area of a circle, P. Gorham for Physics 305 UHM
// to compile, use ' g++ area.cpp -o area '

// Change 1: While loop
// Change 2: For loop: repeat result 10x, each time radius doubled

using namespace std;  
#include <iostream> 
#define _USE_MATH_DEFINES  
#include <cmath>           

int main() 
{
	
	int i;
	double A=0;
	double r=1.0;

	cout << "Enter the radius of the circle:" << endl;  
	cin >> r; // read in the initial radius
	
	// begin for loop
	for(i=0; i<10; i++){
		A = M_PI*pow(r,2.);
		cout << "For radius " << r << " the Area is " << A << endl;
    	   	r = r*2.0;
		}
		
	cout << endl << "Bye!" << endl;
	
	return 0; 

}
