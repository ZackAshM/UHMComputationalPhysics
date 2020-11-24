// Random coordinate generator with command line arguments

using namespace std;  
#include <string>     
#include <iostream> 
#include <iomanip>   
#include <fstream>
#define _USE_MATH_DEFINES  
#include <cmath>   
#include <cstdlib> 
#include <ctime>

int seed = 262019230;

int main(int argc, char** argv)
{

	int seedchange = atoi(argv[2]);
	if(seedchange > 1) {
     	seed = seedchange; 
     	cerr << "Using user seed= "<< seed <<endl;     
  	}else{
     	cerr << "Using default seed= "<< seed <<endl;
  	}
  	
  	srand48(seed); 	// Use srand() when not using drand()

   	int N = atoi(argv[1]);
   
	cout << "# x		y		pair notation" << endl;
	std::string p[N];
	for(int i=0;i<N;i++) p[i] = "";
	
	for(int i=0;i<N;i++){
	double x = drand48();	// Use random() for random integers
	double y = drand48();
	p[i] = "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	cout << x << "\t" << y << "\t";
	std::cout << p[i];
	cout << "\t" << endl;
	}

}
