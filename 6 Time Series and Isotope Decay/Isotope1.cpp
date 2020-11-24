/* Isotope1.cpp: program to simulate radioactive decay
 * -- P. Gorham for UH Physics 305 2/24/14 
 * g++ Isotope1.cpp -o Isotope1
 */

using namespace std;       // sets up some standard names for things
#include <iostream>        // This is  library containing input-output functions
#include <iomanip>   // this is required to use "setprecision" 
#include <fstream>
#define _USE_MATH_DEFINES  // tells the compiler to define math constants (like pi) for you
#include <cmath>
#include <cstdio>     // for the  useful old C-standard stuff 
#include <cstdlib>    

#define LONGENOUGH  10000 // fill this in with an integer time in secs that is long enough
    
main(int argc, char *argv[])
{
 
	if(argc<2){
		cerr << "usage: Isotope1 [Natoms][Half-life]" << endl;
		exit(0);
		}
	
    int Natoms = atoi(argv[1]); // number of atoms to start with
    double Lifetime = atof(argv[2])/log(2);

    double *DecayArr, *RemainArr;   
    double dt = 0.1;  // the time resolution of our clock, seconds
    double bindt = 10.0; //size of each larger count bin in seconds
    double dt_DecayProb = dt/Lifetime;  // differential decay probability per atom per dt
    int Ndecay, Nt;
    int TotalTime = LONGENOUGH; // TotalTime is a parameter we need to set long enough     
  
    srand48(1299811); // a large prime  
    double tt = 0.0;   // our overall clock time

    Nt = Natoms;  // starting number of atoms for a given isotope
    int Ndeltat = LONGENOUGH/bindt;   
    DecayArr = new double [Ndeltat]();  // initialize our decay counter array
    RemainArr = new double [Ndeltat](); // this will keep track of remaining atoms

    while(tt < TotalTime) {          
        Ndecay = 0;  // reset the atom decay counter for each dt time interval

       // now loop over all of our atoms, check if any decay in this dt interval
        for(int i=0;i<Nt;i++){ 
        int idecay = drand48() <= dt_DecayProb ? 1 : 0 ;  // conditional statement
           if(idecay){
              DecayArr[(int)(tt/bindt)] += 1.0; // here the index is modulo bindt=10sec
              Ndecay += 1;
            }
          }      // end of our atom-decay check loop
        Nt -= Ndecay;  // remove the incremental number of decayed atoms from the total number
        RemainArr[(int)(tt/bindt)] = Nt;
        
        tt += dt;      
    }  // end of our outer time loop
   
    for(int i=0;i<Ndeltat;i++){
        cout << (i+0.5)*bindt <<" "<<DecayArr[i]<<" "<<RemainArr[i]<<" "<< sqrt(DecayArr[i] + 0.75)+1 <<endl;  
        }

}	
