/*  check of machine underflow and overflow */
// PG 1/23/2019

using namespace std;       // sets up some standard names
#include <iostream>        // I/O functions
#define _USE_MATH_DEFINES  // define standard math names
#include <cmath>           // C++ math functions
#include <iomanip>

main()    
{
	int N;  // no initialization since these are set later
	float over=1.0;  // these are floats (4 bytes) not doubles (8 bytes)
	float under=1.0;   
	// read in the value 
  	cerr << "Enter number of iterations:" << endl; 
  	cin >> N;
  	
  	cout << "#" << "Iteration	" << "Over	" << "Under" << endl;

	for(int i=0;i<N;i++){
	    over = over*2.0;
	    under = under/2.0;
		cout << setprecision(12) << i+1 << "	" << over << "	" << under <<endl;
	}    // end of for loop

 }   // end of main
