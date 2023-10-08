#include <iostream>
#include <math.h>
#include <string>

using namespace std;

void lampoTila(char unit, double temp) {
	if (unit == 'f') {
		cout << "The temperature " << temp << " F is equal to " << 0.555*(temp-32) << " C." << endl << endl;
	}
	else if (unit == 'c') {
		cout << "The temperature " << temp << " C is equal to " << temp * 1.8 + 32 << " F." << endl << endl;
	}
	else {
		cout << "Error in input, try again!" << endl;
	}

}

void pituusMitta(char question, char unit, double measure) {

	if (question == 'h') {
		if (unit == 'm') {
			int feet = measure / 0.3048;
			int inches = (measure - (feet * 0.3048)) / 0.0254;
			cout << "The height " << measure << " m is equal to " << feet<< " feet " << inches << " inches." << endl << endl;
		}
		else if (unit == 'f') {
			cout << "The height " << measure << " feet is equal to " << measure * 0.3048 << " m or " << measure*0.3048/100 << " centimeters" << endl << endl;
		}
		else if (unit == 'c') {
			int feet = measure * 0.03281;
			int inches = (measure - (feet / 0.03281)) / 2.54;
			cout << "The height " << measure << " cm is equal to " << feet << " feet " << inches << " inches." << endl << endl;
		}
		else if (unit == 'i') {
			cout << "The height " << measure << " inches is equal to " << measure*2.54 << " cm." << endl << endl;
		}
	}
	else if (question == 'l') {
		if (unit == 'm') {
			cout << "The length " << measure << " m is equal to " << measure / 0.3048 << " feet." << endl << endl;
		}
		else if (unit == 'f') {
			cout << "The length " << measure << " feet is equal to " << measure * 0.3048 << " m." << endl << endl;
		}
		else if (unit == 'c') {
			cout << "The length " << measure << " cm is equal to " << measure / 2.54 << " inches." << endl << endl;
		}
		else if (unit == 'i') {
			cout << "The length " << measure << " inches is equal to " << measure * 2.54 << " cm." << endl << endl;
		}
		else if (unit == 'e') {
			cout << "The length " << measure << " miles is equal to " << measure * 1.609 << " kilometres." << endl << endl;
		}
		else if (unit == 'k') {
			cout << "The length " << measure << " kilometers is equal to " << measure /1.609 << " miles." << endl << endl;
		}
	}
	else {
		cout << "Error in input, try again!" << endl;
	}
}

void paino(char unit, double weight) {
	if (unit == 'k') {
		cout << "The weight " << weight << " kg is equal to " << weight/0.453 << " lbs." << endl;
	}
	else if (unit == 'l') {
		cout << "The weight " << weight << " lbs is equal to " << weight*0.453 << " kg." << endl;
	}
	else {
		cout << "Error in input, try again!" << endl;
	}

	cout << endl;
	cout << "Do you also want a daily protein intake recommendation for your bodyweight for training? (y/n): ";
	char question;
	cin >> question;
	cout << endl;

	if (question == 'y') {

		double fat = 0.0;
		double upper_limit = 0.0;

		if (unit == 'k') {
			cout << "The daily protein intake recommendation for you would be roughly from " << weight * 1.3 << " to " << weight * 2 << " grams of protein per day." << endl;
			fat = weight * 0.6;
			upper_limit = weight * 2.2;
		}
		else if (unit == 'l') {
			cout << "The daily protein intake recommendation for you would be roughly from " << weight * 1.3/0.453 << " to " << weight * 2/0.453 << " grams of protein per day." << endl;
			fat = weight * 0.3;
			upper_limit = weight;
		}

		cout << "Notice that more than 2,2 grams/kg or 1 grams/lbs of bodyweight in protein (" << upper_limit << " grams for you)" << endl;
		cout << "doesn't give any additional benefits, but aim a bit higher than normal if you're dropping weight" << endl;
		cout << "to avoid unnecessary muscle loss." << endl << endl;
		cout << "A fat intake anywhere from 0,6 g/kg or 0,3 g/lbs (" << fat << " grams for you) upwards easily covers your daily need for fats. " << endl;
		cout <<	"For training purposes filling the rest of the calorie intake with carbs gives plenty of energy." << endl << endl;
		cout << "However, remember that the human body is able to work in wide range of conditions " << endl;
		cout << "and the required daily intakes of macro nutrients for living are very low." << endl;
		cout << "The rest of the calorie intake can be filled to your needs and desires and just convenience." << endl;
		cout << "So don't get stressed about matching the planned macros every day to a gram." << endl << endl;
	}
}


int main() {
	
	char input = 'a';
	double temp = 0.0;
	double measure = 0.0;
	double weight = 0.0;

	while (input != 'q') {

		cout << "Enter your desired conversion (t = temperature, l = length/height measure, w = weight, quit = q): ";
		cin >> input;

		switch (input) {

			char length_question;
			char unit;

			case 't':

				cout << "Enter the temperature in numbers: ";
				cin >> temp;
				cout << "Enter the units (c = Celsius, f = Fahrenheit): ";
				cin >> unit;

				if (unit != 'c' && unit != 'f') {
					cout << "Input error, try again!" << endl;
					return 0;
				}

				lampoTila(unit, temp);

				break;

			case 'l':

				cout << "Do you want the measure in height or length? (h/l): ";
				cin >> length_question;

				if (length_question == 'l') {
					cout << "Enter the length in numbers: ";
				}
				else if (length_question == 'h') {
					cout << "Enter the height in numbers: ";
				}

				cin >> measure;
				cout << "Enter the unit (m = meters, f = feet, c = centimeters, i = inches, k = kilometres, e = miles): ";
				cin >> unit;

				if ( unit != 'm' && unit != 'f' && unit != 'c' && unit != 'i' && unit != 'k' && unit != 'e' ) {
					cout << "Input error" << endl;
					cout << "Press any key...";
					char key;
					cin >> key;
					return 0;
				}

				pituusMitta(length_question, unit, measure);

				break;

			case 'w':

				cout << "Enter the weight in numbers: ";
				cin >> weight;
				cout << "Enter the unit (k = kilograms, l = lbs): ";
				cin >> unit;

				if (unit != 'k' && unit != 'l') {
					cout << "Input error, try again!" << endl;
					return 0;
				}

				paino(unit, weight);

				break;

			case 'q':
				continue;

			default:
				cout << "Error in choice, try again!" << endl;
				break;
		}
	}

	cout << "Kiitos muuntimen käytöstä!" << endl;

}