#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

void CpkCalculator(double measurements[], int arraySize, double designMeasure, double upperLimit,
					double lowerLimit);
void CpCalculator(double upperLimit, double lowerLimit, double standardDeviation);
void OutsideRange(double measurements[], int arraySize, double upMeasure, double lowMeasure);

int main() {

	cout << string(79, '#') << endl;
	cout << '#' << string(77, ' ') << '#' << endl;
	cout << '#' << "  ";
	cout << "Welcome, this is a calculator for quality control key numbers Cpk and Cp.";
	cout << "  " << '#' << endl;
	cout << '#' << string(77, ' ') << '#' << endl;
	cout << string(79, '#') << endl;
	cout << endl;
	
	// Take the drawing measurement and tolerance boundaries for the process
	double designMeasure = 0.0;
	double upperLimit = 0.0;
	double lowerLimit = 0.0;
	cout << "Input the design value for the measure: ";
	cin >> designMeasure;
	cout << "Input the upper tolerance limit of the process: ";
	cin >> upperLimit;
	cout << "Input the lower tolerance limit of the process: ";
	cin >> lowerLimit;
	cout << endl;

	// Take the number of measurements to define the array
	int arraySize = 0;
	cout << "Input the number of measurements done: ";
	cin >> arraySize;
	
	double measurements[arraySize];
	
	// Fill the array with user's measurements
	for ( int i = 0; i < arraySize; i++ ) {
		cout << "Input the measurement of part number " << i+1 << ": ";
		cin >> measurements[i];
	}

	// Decorate the output
	cout << endl;
	cout << string(79, '-') << endl;
	cout << endl;
	CpkCalculator(measurements, arraySize, designMeasure, upperLimit, lowerLimit);
	cout << endl;
	cout << string(79, '-') << endl;
	cout << endl;
	
	// Keep it alive until the user has read the results 
	string endInput;
	while ( endInput != "exit" && endInput != "quit" && endInput != "0" ) {
		cout << "Type \"exit\" or \"quit\" to end the program: ";
		cin >> endInput;
	}
}

void CpkCalculator(double measurements[], int arraySize, double designMeasure, double upperLimit,
					double lowerLimit) {
	
	// Calculating the mean average measure X
	double sum = 0;
	for ( int i = 0; i < arraySize; i++ ) {
		sum += measurements[i];
	}
	
	double averageMeasure = 0;
	averageMeasure = sum/arraySize;
	
	// Calculate the deviations from average measurement
	double sigma = 0;
	for ( int i = 0; i < arraySize; i++ ) {
		sigma += pow(measurements[i] - averageMeasure, 2);
	}
	
	// Calculating the standard deviation s/alpha
	double standardDeviation = 0.0;
	standardDeviation = sqrt(sigma/(arraySize-1));
	
	// Calculating the upper and lower Cpk number
	double CpkUpper = 0.0;
	double CpkLower = 0.0;
	double upMeasure = designMeasure + upperLimit;
	double lowMeasure = designMeasure + lowerLimit;
	CpkUpper = (upMeasure - averageMeasure) / (3 * standardDeviation);
	cout << "Your system's upper Cpk value is: " << fixed << setprecision(2) << CpkUpper << endl;
	CpkLower = (averageMeasure - lowMeasure) / (3 * standardDeviation);
	cout << "Your system's lower Cpk value is: " << fixed << setprecision(2) << CpkLower << endl;

	CpCalculator(upperLimit, lowerLimit, standardDeviation);
	OutsideRange(measurements, arraySize, upMeasure, lowMeasure);
}

void CpCalculator (double upperLimit, double lowerLimit, double standardDeviation) {
	
	// Calculating the tolerance range
	double toleranceRange = upperLimit - lowerLimit;
	
	// Calculating the Cp number
	double Cp = 0.0;
	Cp = toleranceRange / (6 * standardDeviation);
	cout << "Your system's Cp value is: " << setprecision(2) << Cp << endl;
}

void OutsideRange (double measurements[], int arraySize, double upMeasure, double lowMeasure) {
	
	// Counting the number of measurements outside the tolerance range
	int outside = 0;
	for ( int i = 0; i < arraySize; i++ ) {
		if ( measurements[i] < upMeasure || measurements[i] < lowMeasure ) {
			++outside;
		}
	}
	cout << endl;
	cout << "You have " << outside << " measurements out of " << arraySize << " outside the tolerance range."
	<< endl;
}