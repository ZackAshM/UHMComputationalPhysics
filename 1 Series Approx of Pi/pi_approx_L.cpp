// Program to approximate pi using N terms of the Leibniz series
// Zachary Martin
// 16 January 2019
// P305 UH Manoa

using namespace std;  
#include <iostream> 
#define _USE_MATH_DEFINES  
#include <cmath>

double percent_error(double x){	// Defines percent error function for pi
	return 100*abs(x - M_PI)/M_PI;
}

int pi_approx(int Nmax){		// Define function for approximating pi

double Lsum = 0.0;		// Defines sum value of Leibniz series
	
for(int j = 1; j <= Nmax; j++){
	double Lnterm = 4*pow(-1, j+1)/(2*j-1);
	Lsum += Lnterm;
	}
	
cout << "N = " << Nmax << endl;
   cout << "Pi = " << Lsum << endl;
   cout << "Pi_err = " << percent_error(Lsum) << endl << endl;

}

int main(){

for(int i = 1; i <= 10; i++){
	pi_approx(i);
}
for(int k = 100; k <=10000; k = 10*k){
	pi_approx(k);
}
   
cout << endl << "Good bye!" << endl << endl;
   
return 0;
	
}

