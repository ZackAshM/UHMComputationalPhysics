using namespace std;
    #include <iostream>
    #include <fstream>
    #include <string>
    
int main() {
    	ifstream myfile("AtmosData.txt");
    	double *densities, *altitude;
	densities = new double [200]();
	altitude = new double [200]();
	for(int i=0;i<150;i++){
	double rho;
	myfile >> rho;
	densities[i] = rho;
	altitude[i] = i*2.0;
	}
	
	for(int j=0;j<150;j++){
	cout << altitude[j] << ", " << densities[j] << endl;
	}
	
	delete densities, altitude;
}
