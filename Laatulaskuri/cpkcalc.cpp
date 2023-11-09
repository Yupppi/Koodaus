#include <iostream>
#include <string>
#include <iomanip>	// result decimals
#include <vector>
#include <numeric>	// for accumulate() and for each()
#include <cmath>	// for sqrt()

struct Part {
	double designMeasure;
	double upperLimit;
	double lowerLimit;
    double upMeasure;
    double lowMeasure;

    void Tolerances()
    {
        upMeasure = designMeasure + upperLimit;
        lowMeasure = designMeasure + lowerLimit;        
    }
};

void Welcome();
void DesignCollector(Part& part);
void MeasurementCollector(std::vector<double>& measurements, int& vectorSize);
void OutPut(const std::vector<double>& measurements, const Part&);
void CpkCalculator(const std::vector <double>& measurements, const Part& part);
void CpCalculator(const Part& part, const double& standardDeviation);
void OutsideRange(const std::vector<double>& measurements, const Part& part);

int main() {
	// welcome message
	Welcome();
	
    Part part;
	// Take the drawing measurement and tolerance boundaries for the process
	DesignCollector(part);


	// Take the number of measurements to define the array
	int vectorSize = 0;
	std::vector<double> measurements;

	// sample vector for testing purposes, comment MeasurementCollector out if you use this
	// std::vector<double> sample = { 451.1, 451.7, 451.5, 452.0,
								// 451.7, 452.3, 452.4, 450.9};
	// measurements = sample;
	
	// Fill the array with user's measurements
	MeasurementCollector(measurements, vectorSize);

	// Decorate the output
	OutPut(measurements, part);

	// Keep it alive until the user has read the results 
	std::string endInput;
	while ( endInput != "exit" && endInput != "quit" && endInput != "0" ) {
		std::cout << "Type \"exit\" or \"quit\" to end the program: ";
		std::cin >> endInput;
	}
}

void Welcome(){
	std::cout << '\n';
	std::cout << std::string(79, '#') << '\n';
	std::cout << '#' << std::string(77, ' ') << "#\n";
	std::cout << '#' << "  ";
	std::cout << "Welcome, this is a calculator for quality control key numbers Cpk and Cp.";
	std::cout << "  " << "#\n";
	std::cout << '#' << std::string(77, ' ') << "#\n";
	std::cout << std::string(79, '#') << '\n';
	std::cout << std::endl;
}

void DesignCollector(Part& part){
	std::cout << "Enter the design value for the measure: ";
	std::cin >> part.designMeasure;
	std::cout << "Enter the upper tolerance limit of the process: ";
	std::cin >> part.upperLimit;
	std::cout << "Enter the lower tolerance limit of the process: ";
	std::cin >> part.lowerLimit;
    part.Tolerances();
	std::cout << std::endl;
};

void MeasurementCollector(std::vector<double>& measurements, int& vectorSize){
	// std::cout << "Enter the number of measurements done: ";
	// std::cin >> vectorSize;
	// for ( int i = 0; i < vectorSize; i++ ) {
		// static double measure = 0.0;
		// std::cout << "Enter the measurement for part number " << i+1 << ": ";
		// std::cin >> measure;
		// measurements.emplace_back(measure);
	// }
	std::cin.exceptions(std::ios_base::failbit);
	while (true) {
		static int i = 0;
		static double measure = 0.0;
		try{
			std::cout << "Enter the measurement for part number " << i+1 << " (q to stop): ";
			std::cin >> measure;
			measurements.emplace_back(measure);
			++i;
		}
		catch(std::exception E){
			std::cin.clear();
			std::cin.ignore();
			break;
		}
	}
}

void OutPut(const std::vector<double>& measurements, const Part& part){
    std::cout << std::endl;
	std::cout << std::string(79, '-') << std::endl;
	std::cout << std::endl;
	CpkCalculator(measurements, part);
	std::cout << std::endl;
	std::cout << std::string(79, '-') << std::endl;
	std::cout << std::endl;
}

void CpkCalculator(const std::vector <double>& measurements, const Part& part) {

	// Calculating the mean average measure X

	double sum = std::accumulate(measurements.begin(), measurements.end(), 0.0);
	double mean = sum / (measurements.size());

	// Calculate the deviations from average measurement
	double sigma = std::accumulate(measurements.begin(), measurements.end(), 0.0,
						 			[&](double sum, const double x){
		return sum + (x - mean) * (x - mean);
	});

	// can't get reduce to work
	// double sigma = std::reduce(measurements.begin(), measurements.end(), 0.0,
						 			// [&](double sigmasum, const double x){
		// return sigmasum + (x - mean) * (x - mean);
	// });

	// these is a cruder attempt to calculate the s^2
	// double sigma = 0.0;
	// std::for_each(measurements.begin(), measurements.end(), [&](const double x) {
		// sigma += (x - mean) * (x - mean);
	// });

	// Calculating the standard deviation s or sigma with the corrected
	// standard deviation equation where instead of n we use n-1 to correct
	// the bias from both data and square root
	double standardDeviation = 0.0;
	standardDeviation = sqrt( sigma / ( measurements.size() - 1 ) );
	
	// Calculating the upper and lower Cpk number
	double CpkUpper = (part.upMeasure - mean) / (3 * standardDeviation);
	std::cout << "Your system's upper Cpk value is: " << std::fixed << std::setprecision(2)
			  << CpkUpper << std::endl;
	double CpkLower = (mean - part.lowMeasure) / (3 * standardDeviation);
	std::cout << "Your system's lower Cpk value is: " << std::fixed << std::setprecision(2)
			  << CpkLower << std::endl;

	CpCalculator(part, standardDeviation);
	OutsideRange(measurements, part);
}

void CpCalculator (const Part& part, const double& standardDeviation) {
	
	// Calculating the tolerance range
	double toleranceRange = part.upperLimit - part.lowerLimit;
	
	// Calculating the Cp number
	double Cp = 0.0;
	Cp = toleranceRange / (6 * standardDeviation);
	std::cout << "Your system's Cp value is: " << std::setprecision(2) << Cp << std::endl;
}

void OutsideRange (const std::vector <double>& measurements, const Part& part) {
	
	// Counting the number of measurements outside the tolerance range
	int outside = 0;
	for ( const double& values : measurements ) {
		if ( values > part.upMeasure || values < part.lowMeasure ) {
			++outside;
		}
	}
	std::cout << std::endl;
	std::cout << "You have " << outside << " measurements out of " << measurements.size() <<
	 " outside the tolerance range." << std::endl;
}