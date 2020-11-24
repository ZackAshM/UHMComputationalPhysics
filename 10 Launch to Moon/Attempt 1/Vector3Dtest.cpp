// Vector3D test

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#define USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> 
#include "Vector3D.h"

int main(){

	Vector3D A, B, C;
	A = Vector3D(2.0, -4.0, 3.0);
	B = Vector3D(1.0, 0.0, 7.0);
	C = Vector3D(-3.0, -1.0, 2.0);
	
	Vector3D AplusB, BplusA, CminusA, AminusC, twoA, Btwo, Cdivthree, divthreeC;
	AplusB = A + B;
	BplusA = B + A;
	CminusA = C - A;
	AminusC = A - C;
	twoA = 2.0*A;
	Btwo = B*2.0;
	Cdivthree = C*(1.0/3.0);
	divthreeC = (1.0/3.0)*C;
	
	cout << "AplusB (3.0, -4.0, 10.0) = "<<AplusB.printt()<<endl
		<< "BplusA (3.0, -4.0, 10.0) = "<<BplusA.printt()<<endl
		<< "CminusA (-5.0, 3.0, -1.0) = "<<CminusA.printt()<<endl
		<< "AminusC (5.0, -3.0, 1.0) = "<<AminusC.printt()<<endl
		<< "twoA (4.0, -8.0, 6.0) = "<<twoA.printt()<<endl
		<< "Btwo (2.0, 0.0, 14.0) = "<<Btwo.printt()<<endl
		<< "Cdivthree (-1.0, -0.33, 0.66) = "<<Cdivthree.printt()<<endl
		<< "divthreeC (-1.0, -0.33, 0.66) = "<<divthreeC.printt()<<endl;


}
