#include <iostream>

using namespace std;



int main() {

	cout << "Welcome, this is a Cpk calculator for Quality and Measurements." << endl;

	int arraySize = 0;

	// Take the number of measurements to define the array
	cout << "Input the number of measurements done: ";
	cin >> arraySize;
	
	double measurements[arraySize];
	
	// Fill the array with user's measurements
	for ( int i = 0; i < arraySize; i++ ) {
		cout << "Input your measurement number " << i << ": ";
		cin >> measurements[i];
	}

}