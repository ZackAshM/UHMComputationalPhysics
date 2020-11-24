// Program to approximate pi using N terms of the Wallis formula
// Zachary Martin
// 20 January 2019
// P305 UH Manoa

using namespace std;  
#include <iostream> 
#define _USE_MATH_DEFINES  
#include <cmath>

double percent_error(double x){	// Defines percent error function for pi
	return 100*abs(x - M_PI)/M_PI;
}

int wallis_pi_approx(int Nmax){		// Define function for approximating pi

double Wpro = 1.0;		// Defines product value of Wallis
	
for(int j = 1; j <= Nmax; j++){
	double Wnterm = (2.0*j)*(2.0*j)/(2.0*j-1.0)/(2.0*j+1.0);
	Wpro = Wpro * Wnterm;
	}
	
cout << "N = " << Nmax << endl;
   cout << "Pi = " << 2.0*Wpro << endl;
   cout << "Pi_err = " << percent_error(2.0*Wpro) << endl << endl;

}

int main(){

for(int i = 1; i <= 10; i++){
	wallis_pi_approx(i);
}
for(int k = 100; k <=10000; k = 10*k){
	wallis_pi_approx(k);
}
   
cout << endl << "Good bye!" << endl << endl;
   
return 0;
	
}

