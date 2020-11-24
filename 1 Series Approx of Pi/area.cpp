// c++ program to calculate area of a circle, P. Gorham for Physics 305 UHM
// to compile, use ' g++ area.cpp -o area '

using namespace std;       // sets up some standard names for things
#include <iostream>        // This is  library containing input-output functions you need
#define _USE_MATH_DEFINES  // tells the compiler to define math constants (like pi) for you
#include <cmath>           // The standard C library math.h, has lots of pre-defined math functions

int main() // "main" is the name always used for the main body of the program,
	   // that is, the part that operates sequentially when we call the program to create a result.
{                  // begin the main program body, tab everything in to make it distinct
	double r;  // here we declare the existence of a new variable, which is created for us

	// next two lines are standard input/output functions:
	cout << "Enter the radius of the circle:" << endl;  // cout and cin are standard "streams" of information
	       // think of << or >> as being  information "flow" operators, sending text data out to the terminal or
	       // bringing response data into the variable r
	cin >> r;  
	//double A = M_PI*r*r; // M_PI is the computer math library's name for pi=3.14159....
	double A = M_PI*pow(r,2.);  // pow(base,exponent) is the way that C++ does powers
	cout << "For radius " << r << " the Area is " << A << endl;
        cout << endl << endl << "Bye!" << endl;

	return 0;  // don't really need this, 
		   //  but it tells the operating system that all is well

}  // this curly brace closes main()
