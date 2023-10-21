#include <iostream>
#include <math.h>
#include <string>
#include <conio.h>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

void tulostinviiva();
void lampoTila(char unit, double temp);
void pituusMitta(int question, char unit, double measure);
void paino(char unit, double weight);
void kello();
void AMPM(int& tunti, string& am_pm);

enum OPTION{EXIT=5};

int main()
{
	int input = 0;

	while (input != EXIT)
	{
		string welcome = "**  Welcome to converter between metric and imperial units  **";

		cout << '\n';
		cout << string(welcome.length(), '*') << '\n';
		cout << "**" << string(welcome.length() - 4, ' ') << "**\n";
		cout << welcome << '\n';
		cout << "**" << string(welcome.length() - 4, ' ') << "**\n";
		cout << string(welcome.length(), '*') << "\n\n";

		cout << "Enter your desired conversion:\n";
		cout << "1. Temperature\n"
			 << "2. Length/Height\n"
			 << "3. Weight\n"
			 << "4. Time\n"
			 << EXIT << ". Exit\n";

		cin >> input;
		cout << '\n';
		double temp = 0.0;
		double measure = 0.0;
		double weight = 0.0;
		string anykey;

		switch (input)
		{
			int length_or_height;
			char unit;

		case 1:

			cout << "Enter the temperature in numbers: ";
			cin >> temp;
			cout << "Enter the units (c = Celsius, f = Fahrenheit): ";
			cin >> unit;

			if (unit != 'c' && unit != 'f')
			{
				cout << "Input error, try again!\n";
				cout << "Press any key to continue...\n";
				getch();
				break;
			}

			lampoTila(unit, temp);

			cout << "Press any key to continue...\n";
			getch();
			break;

		case 2:

			cout << "Do you want the measure in height or length? (h/l): \n"
				 << "1. Height\n"
				 << "2. Length\n";
			cin >> length_or_height;

			if (length_or_height == 2)
			{
				cout << "Enter the length in numbers: ";
			}
			else if (length_or_height == 1)
			{
				cout << "Enter the height in numbers: ";
			}

			cin >> measure;
			cout << "Enter the unit (m = meters, f = feet, c = centimeters, "
				 << "i = inches, k = kilometres, e = miles): ";
			cin >> unit;

			if (unit != 'm' && unit != 'f' && unit != 'c' && unit != 'i' && unit != 'k' && unit != 'e')
			{
				cout << "Input error.\n";
				break;
			}

			pituusMitta(length_or_height, unit, measure);

			cout << "Press any key to continue...\n";
			getch();
			break;

		case 3:

			cout << "Enter the weight in numbers: ";
			cin >> weight;
			cout << "Enter the unit (k = kilograms, l = lbs): ";
			cin >> unit;

			if (unit != 'k' && unit != 'l')
			{
				cout << "Input error, try again!\n";
				cout << "Press any key to continue...\n";
				getch();
				break;
			}

			paino(unit, weight);

			cout << "Press any key to continue...\n";
			getch();
			break;

		case 4:

			kello();
			cout << "Press any key to continue...\n";
			getch();
			break;

		case 5:
			continue;

		default:
			cout << "Error in choice, try again!\n";
			break;
		}
	}

	cout << "Thanks for using the converter!\n\n";
}

void tulostinviiva(){
	string erotinviiva = string(62, '-');
	cout << "\n" << erotinviiva << "\n" << endl;
}

void lampoTila(char unit, double temp)
{
	if (unit == 'f')
	{
		tulostinviiva();
		cout << "The temperature " << temp << " F is equal to " << setprecision(3) <<
				0.555 * (temp - 32) << " C.\n";
		tulostinviiva();
	}
	else if (unit == 'c')
	{
		tulostinviiva();
		cout << "The temperature " << temp << " C is equal to " << setprecision(3) <<
				temp * 1.8 + 32 << " F.\n";
		tulostinviiva();
	}
	else
	{
		cout << "Error in input, try again!\n";
	}
}

void pituusMitta(int question, char unit, double measure)
{
	if (question == 1)
	{
		if (unit == 'm')
		{
			int feet = measure / 0.3048;
			int inches = (measure - (feet * 0.3048)) / 0.0254;
			tulostinviiva();
			cout << "The height " << measure << " m is equal to " << feet << " feet " <<
					inches << " inches.\n";
			tulostinviiva();
		}
		else if (unit == 'f')
		{
			tulostinviiva();
			cout << "The height " << measure << " feet is equal to " << setprecision(3) <<
					measure * 0.3048 << " m or " << setprecision(3) <<
					measure * 0.3048 / 100 << " centimeters.\n";
			tulostinviiva();
		}
		else if (unit == 'c')
		{
			int feet = measure * 0.03281;
			int inches = (measure - (feet / 0.03281)) / 2.54;
			tulostinviiva();
			cout << "The height " << measure << " cm is equal to " << feet << " feet " <<
					inches << " inches.\n";
			tulostinviiva();
		}
		else if (unit == 'i')
		{
			tulostinviiva();
			cout << "The height " << measure << " inches is equal to " << measure * 2.54 <<
					" cm.\n";
			tulostinviiva();
		}
	}
	else if (question == 2)
	{
		if (unit == 'm')
		{
			tulostinviiva();
			cout << "The length " << measure << " m is equal to " << setprecision(3) <<
				measure / 0.3048 << " feet.\n";
			tulostinviiva();
		}
		else if (unit == 'f')
		{
			tulostinviiva();
			cout << "The length " << measure << " feet is equal to " << setprecision(3) <<
				measure * 0.3048 << " m.\n";
			tulostinviiva();
		}
		else if (unit == 'c')
		{
			tulostinviiva();
			cout << "The length " << measure << " cm is equal to " << setprecision(3) <<
				measure / 2.54 << " inches.\n";
			tulostinviiva();
		}
		else if (unit == 'i')
		{
			tulostinviiva();
			cout << "The length " << measure << " inches is equal to " << setprecision(3) <<
				measure * 2.54 << " cm.\n";
			tulostinviiva();
		}
		else if (unit == 'e')
		{
			tulostinviiva();
			cout << "The length " << measure << " miles is equal to " << setprecision(3) <<
				measure * 1.609 << " kilometres.\n";
			tulostinviiva();
		}
		else if (unit == 'k')
		{
			tulostinviiva();
			cout << "The length " << measure << " kilometers is equal to " << setprecision(3) <<
				measure / 1.609 << " miles.\n";
			tulostinviiva();
		}
	}
	else
	{
		cout << "Error in input, try again!\n";
		cout << "Press any key to continue...\n";
		getch();
	}
}

void paino(char unit, double weight)
{
	if (unit == 'k')
	{
		tulostinviiva();
		cout << "The weight " << weight << " kg is equal to " << setprecision(3) <<
			weight / 0.453 << " lbs.\n";
		tulostinviiva();
	}
	else if (unit == 'l')
	{
		tulostinviiva();
		cout << "The weight " << weight << " lbs is equal to " << setprecision(3) <<
				weight * 0.453 << " kg.\n";
		tulostinviiva();
	}
	else
	{
		cout << "Error in input, try again!\n";
		cout << "Press any key to continue...\n";
		getch();
	}

	cout << '\n';
	cout << "Do you also want a daily protein intake recommendation for your bodyweight for training? (y/n): ";
	char question;
	cin >> question;
	cout << '\n';

	if (question == 'y')
	{

		double fat = 0.0;
		double upper_limit = 0.0;

		if (unit == 'k')
		{
			tulostinviiva();
			cout << "The daily protein intake recommendation for you would be roughly from " << weight * 1.3 << " to " << weight * 2 << " grams of protein per day." << endl;
			tulostinviiva();
			fat = weight * 0.6;
			upper_limit = weight * 2.2;
		}
		else if (unit == 'l')
		{
			tulostinviiva();
			cout << "The daily protein intake recommendation for you would be roughly from " << weight * 1.3 / 0.453 << " to " << weight * 2 / 0.453 << " grams of protein per day." << endl;
			tulostinviiva();
			fat = weight * 0.3;
			upper_limit = weight;
		}

		cout << "Notice that more than 2,2 grams/kg or 1 grams/lbs of bodyweight in protein (" << upper_limit << " grams for you)\n";
		cout << "doesn't give any additional benefits, but aim a bit higher than normal if you're dropping weight\n";
		cout << "to avoid unnecessary muscle loss.\n\n";
		cout << "A fat intake anywhere from 0,6 g/kg or 0,3 g/lbs (" << fat << " grams for you) upwards easily covers your daily need for fats. \n";
		cout << "For training purposes filling the rest of the calorie intake with carbs gives plenty of energy.\n\n";
		cout << "However, remember that the human body is able to work in wide range of conditions \n";
		cout << "and the required daily intakes of macro nutrients for living are very low.\n";
		cout << "The rest of the calorie intake can be filled to your needs and desires and just convenience.\n";
		cout << "So don't get stressed about matching the planned macros every day to a gram.\n\n";
	}
}

void kello()
{
	int location = 0;
	cout << "Are you in:\n" << "1. Brazil\n" << "2. Finland\n" << "3. USA\n";
	cin >> location;

	using namespace std::chrono;
	system_clock::time_point moment = system_clock::now();
	time_t tt = system_clock::to_time_t (moment);
	tm local_tm = *localtime(&tt);

	int hour = local_tm.tm_hour;
	int min = local_tm.tm_min;
	int brazil_h;
	int finland_h;
	int usa_h;
	string bra;
	string fin;
	string US;

	switch(location){
	
		case 1:
			finland_h = hour+6;
			if ( finland_h > 24 ){
				finland_h = finland_h-24;
			}
			usa_h = hour-1;
			if ( usa_h < 0 ){
				usa_h = 24+usa_h;
			}
			tulostinviiva();
			cout << "It's " << hour << ":" << setfill('0') << setw(2) << min << " right now in Brazil.\n";
			cout << "The time in Finland is " << finland_h << ":" << setfill('0') << setw(2) << min << " right now.\n";
			cout << "The time in USA is " << usa_h << ":" << setfill('0') << setw(2) << min << " right now.\n";
			tulostinviiva();
			break;

		case 2:
			brazil_h = hour-6;
			if ( brazil_h < 0 ){
				brazil_h = 24+brazil_h;
			}
			usa_h = hour-7;
			if ( usa_h < 0 ){
				usa_h = 24+usa_h;
			}

			tulostinviiva();
			cout << "It's " << hour << ":" << setfill('0') << setw(2) << min << " right now in Finland.\n";
			cout << "The time in Brazil is " << brazil_h << ":" << setfill('0') << setw(2) << min << " right now.\n";
			cout << "The time in USA is " << usa_h << ":" << setfill('0') << setw(2) << min << " right now.\n";
			tulostinviiva();
			break;

		case 3:
			brazil_h = hour+1;
			AMPM(brazil_h, bra);
			finland_h = hour+7;
			AMPM(finland_h, fin);
			usa_h = hour;
			AMPM(usa_h, US);

			tulostinviiva();
			cout << "It's " << usa_h << ":" << setfill('0') << setw(2) << min << US << " right now in USA.\n";;
			cout << "The time in Brazil is " << brazil_h << ":" << setfill('0') << setw(2) << min << bra << " right now.\n";
			cout << "The time in Finland is " << finland_h << ":" << setfill('0') << setw(2) << min << fin << " right now.\n";
			tulostinviiva();
			break;
	
		default:
			cout << "Your mother was a hamster and your father smelled of elderberries\n";
			break;

	}
}

void AMPM(int& tunti, string& am_pm){
	if ( tunti < 0 ) {
		tunti = tunti-24;
	}
	if ( tunti > 12 ) {
		tunti = tunti - 12;
		am_pm = " pm";
	}
	else {
		am_pm = " am";
	}
}