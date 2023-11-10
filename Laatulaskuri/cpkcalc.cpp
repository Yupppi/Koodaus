#include <iostream>
#include <string>
#include <cstring>	// to use const char* instead of string and save memory
#include <iomanip>	// result decimals
#include <vector>
#include <numeric>	// for accumulate() and for each()
#include <cmath>	// for sqrt()

// MEM 1 for memory usage messages, MEM 0 = off
#define MEM 0
// SAMPLE 1 to use sample data instead of user input, SAMPLE 0 = off
#define SAMPLE 0

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
	s_AllocationMetrics.TotalAllocated += size;

	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s_AllocationMetrics.TotalFreed += size;
	
	free(memory);
}

static void PrintMemoryUsage()
{
	std::cout << "Memory usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

class Part
{
public:
	Part() = default;

	double designMeasure;
	double upperLimit;
	double lowerLimit;
    double upMeasure;
    double lowMeasure;
	double toleranceRange;

    void Tolerances()
    {
		// the upper and lower tolerance measures as well as the tolerance range
        upMeasure = designMeasure + upperLimit;
        lowMeasure = designMeasure + lowerLimit;
		toleranceRange = upperLimit - lowerLimit;
    }
};

void Welcome();
void DesignCollector(Part& part);
void MeasurementCollector(std::vector<double>& measurements);
void OutPut(const std::vector<double>& measurements, const Part&);
void CpkCalculator(const std::vector <double>& measurements, const Part& part);
void CpCalculator(const Part& part, const double& standardDeviation);
void OutsideRange(const std::vector<double>& measurements, const Part& part);

int main() {
	#if MEM
	PrintMemoryUsage();
	#endif
	// Welcome message
	Welcome();
	
	// Create a part entity
    Part part;
	
	#if SAMPLE
	// sample design information, change SAMPLE 1 at the top if you want to use this
	part = { 451.5, 0.3, -0.2 };
	part.Tolerances();
	#endif

	#if MEM
	PrintMemoryUsage();
	#endif
	// Take the drawing measurement and tolerance boundaries for the process
	#if !SAMPLE
	DesignCollector(part);
	#endif

	// Take the number of measurements to define the array
	std::vector<double> measurements;

	#if SAMPLE
	// sample vector for testing purposes
	std::vector<double> sample = { 451.1, 451.7, 451.5, 452.0,
								451.7, 452.3, 452.4, 450.9};
	measurements = sample;
	#endif

	#if MEM
	PrintMemoryUsage();
	#endif
	// Fill the array with user's measurements
	#if !SAMPLE
	MeasurementCollector(measurements);
	#endif

	// Decorate the output and call the calculattor functions
	OutPut(measurements, part);

	#if MEM
	PrintMemoryUsage();
	#endif
	// Keep it alive until the user has read the results 
	std::string endInput;
	while ( endInput != "exit" && endInput != "quit" && endInput != "0" ) {
		std::cout << "Type \"exit\" or \"quit\" to end the program: ";
		std::cin >> endInput;
	}
}

void Welcome(){
	// const char* instead of string to save some memory
	const char* hello = "Welcome, this is a calculator for quality"
						" control key numbers Cpk and Cp.";
	std::cout << '\n';
	std::cout << std::string(strlen(hello)+ 6, '#') << '\n';
	std::cout << '#' << std::string(strlen(hello) + 4, ' ') << "#\n";
	std::cout << '#' << "  ";
	std::cout << hello;
	std::cout << "  " << "#\n";
	std::cout << '#' << std::string(strlen(hello) + 4, ' ') << "#\n";
	std::cout << std::string(strlen(hello) + 6, '#') << '\n';
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

void MeasurementCollector(std::vector<double>& measurements){

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
	std::cout << '\n';
	std::cout << std::string(79, '-') << '\n';
	std::cout << std::endl;
	CpkCalculator(measurements, part);
	std::cout << '\n';
	std::cout << std::string(79, '-') << '\n';
	std::cout << std::endl;
}

void CpkCalculator(const std::vector <double>& measurements, const Part& part) {
	// Calculating the mean average measure X
	double sum = std::accumulate(measurements.begin(), measurements.end(), 0.0);
	double mean = sum / measurements.size();

	// Calculate the deviations from average measurement
	double sigma = std::accumulate(measurements.begin(), measurements.end(), 0.0,
						 			[&](double sum, const double x){
		return sum + (x - mean) * (x - mean);
	});

	// Calculating the standard deviation s or sigma with the corrected
	// standard deviation equation where instead of n we use n-1 to correct
	// the bias from both data and square root
	double standardDeviation = sqrt( sigma / ( measurements.size() - 1 ) );
	
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
	// Calculating the Cp number
	double Cp = 0.0;
	Cp = part.toleranceRange / (6 * standardDeviation);
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
	std::cout << "You have " << outside << " measurements out of " << measurements.size()
	 		  << " outside the tolerance range." << std::endl;
	#if MEM
	PrintMemoryUsage();
	#endif
}