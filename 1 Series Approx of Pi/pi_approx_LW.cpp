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

int pi_approx_Leibniz(){		// Define function for approximating pi

int Nmax;		// Define max term variable
cout << "Enter the number of terms: ";  
while(true){		// Catches negative integer selection
	cin >> Nmax;
	if(Nmax < 0){
		cout << "Please enter a positive integer: ";
	}
	else{
		break;
	}
}

double Lsum = 0.0;		// Defines sum value of Leibniz series
	
for(int j = 1; j <= Nmax; j++){
	double Lnterm = 4*pow(-1, j+1)/(2*j-1);
	Lsum += Lnterm;
	}
	
cout << "For N = " << Nmax << " terms, the approximation for pi is" << endl << endl;
   cout << "Pi = " << Lsum << endl << endl << "and the percent error is" << endl << endl;
   cout << "Pi_err = " << percent_error(Lsum) << endl << endl;

}

int pi_approx_Wallis(){		// Define function for approximating pi

int Nmax;		// Define max term variable
cout << "Enter the number of factors: ";  
while(true){		// Catches negative integer selection
	cin >> Nmax;
	if(Nmax < 0){
		cout << "Please enter a positive integer: ";
	}
	else{
		break;
	}
}

double Wpro = 1.0;		// Defines product value of Wallis
	
for(int j = 1; j <= Nmax; j++){
	double Wnterm = (2.0*j)*(2.0*j)/(2.0*j-1.0)/(2.0*j+1.0);
	Wpro = Wpro * Wnterm;
	}
	
cout << "For N = " << Nmax << " factors, the Wallis approximation for pi is" << endl << endl;
   cout << "Pi = " << 2.0*Wpro << endl << endl << "and the percent error is" << endl << endl;
   cout << "Pi_err = " << percent_error(2.0*Wpro) << endl << endl;

}


int main(){

cout << "This program approximates pi using integer N terms of the Leibniz series or integer N factors in the Wallis formula." << endl;

char choice = 'n';
char answer = 'n';
do {	
	cout << endl << "Which approximation for pi would you like to use?" << endl << "Leibniz (L) or Wallis (W)? ";
	cin >> choice;
	if((choice == 'l') || (choice == 'L')) {
		pi_approx_Leibniz();
	}
	else if((choice == 'w') || (choice == 'W')){
		pi_approx_Wallis();
	}
	else{
		cout << endl << "Invalid option. Terminating..." << endl << endl;
		return 0;
	}
	cout << "Would you like to try another value? (Press Y): " << endl;
	cin >> answer;
	} while ((answer == 'y') || (answer == 'Y'));
   
cout << endl << "Good bye!" << endl << endl;
   
return 0;
	
}

