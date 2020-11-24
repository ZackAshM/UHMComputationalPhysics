/*  test effects of subtractive cancellation */
// Based on Landau, Paez, Boredeuanu section 3.4(2)
// P. Gorham for Physics 305 1/23/19

using namespace std;
#include <iostream>        
#define _USE_MATH_DEFINES  
#include <cmath>
#include <cstdio>  //  c-style io
#include <iomanip> // to get setprecision if we need it

/*   LPB  give three versions of a single summation:
 * 1) the given sum S1 = \sum_{n=1}^{2N} (-1)^n \frac{n}{n+1}
 * 2) odd and even terms of S1 summed separately:
 *    S2 = -\sum_{n=1}^{N} \frac{2n-1}{2n}  + \sum_{n=1}^{N} \frac{2n}{2n+1}
 * 3) an analytic form that improves the summation:
 *    S3 = \sum_{n=1}^{N} \frac{1}{2n(2n+1)}
 * 
 * This program is intended to produce separate results for each
 * form of the summations above.
 * BUT FIRST THERE ARE SOME ERRORS YOU HAVE TO FIX! --PG
 */

// main() begins
main()		// Before: had ;
{

  int i=0,N=2,Nmax; // We never use i so I don't know why we need it here; want sums to start at 1, so set start N=2; Nmax to be chosen for highest term
  float S1sum=0.0, S2sumplus=0.0, S2summinus=0.0, S2sum=0.0, S3sum=0.0,S1frac; // Initialize sum values as 0, s1frac percent error of the sums
	
	
  cerr << "Enter maximum number of iterations:" << endl; 
  cin >> Nmax;
  
  cout << "# Number of iterations: " << Nmax << endl;

// while loop begins
  while(N<=Nmax){ 
  
    S1sum=S2sumplus=S2summinus=S3sum=0.0;  // re-initialize
    
    for(int n=1;n<=2*N;n++){		
    // Before correction: for(int n=1,n<=2*N;n++){ ie ; not ,
  		S1sum += pow(-1.0,n)*n/(n+1.0);
  		// Before: S1sum += pow((-1.0,n)*n/(n+1.0); extra parenthesis
    }

    for(int n=1;n<=N;n++){
 		S2sumplus += 2.0*n/(2.0*n+1.0);  // cumulate positive terms in S2
		S2summinus += (2.0*n-1)/(2.0*n);    // cumulate negative terms in S2
		// Before: S2summinus = (2.0*n-1)/(2.0*n); need to cumulate the terms ie +=
        S3sum += 1.0/(2.0*n*(2.0*n+1.0));  // cumulate the S3 sum
    }

    S2sum = S2sumplus-S2summinus;
    
	S1frac = fabs(S1sum-S3sum)/S1sum;   // we assume S3 is the exact sum.
	
     //Here is a standard C-type output statement (not c++) which
     //gives more control over the number of digits
    printf("%9d terms, S1= %20.18f S3= %20.18f S1fracerr= %e\n",N,S1sum,S3sum,S1frac);
	N*=2;
  }   
// while loop ends

}
// main() ends
