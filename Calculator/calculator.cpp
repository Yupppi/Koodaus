#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <conio.h>

using namespace std;

const double PI = 3.1415926535;

void Tervehdys();
void Menu();
void Erotinviiva();
void Desimaalit(int &accuracy);
void AnyKey();

double Hypotenuusa();
double Sivu();
void Koordinatit(double &a, double &b);
double Kulma();
long int Potenssi();
double Square();

enum OPTION{EXIT=7};

int main()
{
	Tervehdys();
	int choice = 0;

	while (choice != EXIT)
	{

		Menu();
		double a, b, c, alpha = 0.0;
		int accuracy = 0;
		cin >> choice;

		switch (choice)
		{
			case 1:
				c = Hypotenuusa();
				Desimaalit(accuracy);
				Erotinviiva();
				cout << "The length of the hypotenuse is " << fixed << setprecision(accuracy) << c << "\n\n";
				Erotinviiva();
				AnyKey();
				break;

			case 2:
				b = Sivu();
				Desimaalit(accuracy);
				Erotinviiva();
				cout << "The length of the side is " << fixed << setprecision(accuracy) << b << "\n\n";
				Erotinviiva();
				AnyKey();
				break;

			case 3:
				Koordinatit(a, b);
				Desimaalit(accuracy);
				Erotinviiva();
				cout << "The x component is " << fixed << setprecision(accuracy) << a << "i" << '\n';
				cout << "The y component is " << fixed << setprecision(accuracy) << b << "j" << "\n\n";
				Erotinviiva();
				AnyKey();
				break;

			case 4:
				alpha = Kulma();
				Desimaalit(accuracy);
				Erotinviiva();
				cout << "The angle is " << fixed << setprecision(accuracy) << alpha << "\n\n";
				Erotinviiva();
				AnyKey();
				break;

			case 5:
				a = Potenssi();
				Erotinviiva();
				cout << "The power is " << a << ".\n\n";
				Erotinviiva();
                AnyKey();
				break;

			case 6:
				a = Square();
				Desimaalit(accuracy);
				Erotinviiva();
				cout << "The square root is " << a << ".\n\n";
				Erotinviiva();
                AnyKey();
				break;

            // binäärimuunnin
            
            // hex-muunnin

			case EXIT:
				cout << "\nThanks for using the calculator!\n\n";
				break;

			default:
				cout << "Invalid number, try again!\n";
				break;
		}
	}
}

void Tervehdys()
{
	cout << string(61, '#') << '\n';
	cout << '#' << string(59, ' ') << "#\n";
	cout << "#  ";
	cout << "Welcome to solve vectors and trigonometry!";
	cout << "  #\n";
	cout << '#' << string(59, ' ') << "#\n";
	cout << string(61, '#') << '\n'
		 << endl;
}

void Menu()
{
	cout << "Select what you want to solve\n"
		 <<	"1. Vector length\n"
		 << "2. The length of sides\n"
		 << "3. Vector coordinates\n"
		 << "4. An Angle\n"
		 << "5. Power\n"
		 << "6. Square\n"
		 << EXIT << ". Exit\n";
}

void Erotinviiva()
{
	cout << string(61, '-') << '\n'
		 << endl;
}

void Desimaalit(int &accuracy)
{
	cout << "How many decimals you want to be printed: ";
	cin >> accuracy;
	cout << '\n';
}

void AnyKey(){
	cout << "Press any key to continue...\n";
	getch();
}

double Hypotenuusa()
{
	double a, b, c, kulma = 0.0;
	int option = 0;
	cout << "\nDo you want to solve with:\n"
		 << "1. Components\n"
		 << "2. Angle\n";
	cin >> option;

	if (option == 1){
		cout << "\nEnter the x component: ";
		cin >> a;
		cout << "Enter the y component: ";
		cin >> b;
		c = hypot(a, b);
	}
	if (option == 2){
		cout << "\nDo you have x or y component?\n"
			 << "1. X\n"
			 << "2. Y\n";
		cin >> option;
		cout << "\nEnter the component's length: ";
		cin >> a;
		cout << "Enter the angle: ";
		cin >> kulma;
		kulma = kulma * PI / 180;

		if (option == 1){
			c = a / cos(kulma);
		}
		if (option == 2){
			c = a / sin(kulma);
		}
	}
	return c;
}

double Sivu()
{
	int option = 0;
	double a, b, c, alpha, beta = 0.0;
	cout << "Do you want to solve with:\n"
		 << "1. Pythagoras"
		 << "2. Law of sines"
		 << "3. Law of cosines";
	cin >> option;
	if (option == 1) {
		cout << "\nInput the hypotenuse: ";
		cin >> c;
		cout << "Input the side: ";
		cin >> a;
		b = sqrt(pow(c, 2) - pow(a, 2));
	}
	if (option == 2) {
		cout << "\nEnter your first length: ";
		cin >> a;
		cout << "\nEnter your first angle: ";
		cin >> alpha;
		cout << "\nEnter the opposite angle: ";
		cin >> beta;
		alpha = alpha * PI / 180;
		beta = beta * PI / 180;
		b = a*sin(beta) / sin(alpha); 
	}
	if (option == 3) {
		cout << "\nEnter your first length: ";
		cin >> a;
		cout << "Enter your second length: ";
		cin >> c;
		cout << "Enter the opposite angle: ";
		cin >> alpha;
		alpha = alpha * PI / 180;
		b = sqrt(pow(a, 2) + pow(b, 2) - 2 * a * c * cos(alpha));
	}
	else {
		cout << "\nInput error, try again!\n";
	}
	
	return b;
}

void Koordinatit(double &a, double &b)
{
	double c, alpha = 0.0;
	cout << "\nInput the length: ";
	cin >> c;
	cout << "Input the angle: ";
	cin >> alpha;

	if (alpha > 90)
	{
		alpha = ((alpha - 90) * PI) / 180.0;
		a = -c * sin(alpha);
		b = c * cos(alpha);
	}
	else if (alpha < 0 && alpha > -90)
	{
		alpha = (-alpha * PI) / 180.0;
		a = c * sin(alpha);
		b = -c * cos(alpha);
	}
	else if (alpha < -90)
	{
		alpha = (-(alpha + 90) * PI) / 180.0;
		cout << alpha << endl;
		a = -c * sin(alpha);
		cout << a << endl;
		b = -c * cos(alpha);
		cout << b << endl;
	}
	else
	{
		alpha = (alpha * PI) / 180;
		a = c * cos(alpha);
		b = c * sin(alpha);
	}
}

double Kulma()
{
	int option = 0;
	double a, b, c, kulma, alpha = 0.0;
	cout << "\nDo you want to solve with\n"
		 <<	"1. Cos()\n"
		 << "2. Sin()\n"
		 << "3. Tan()\n"
		 << "4. Law of sines\n"
		 << "5. Law of cosines\n";
	cin >> option;

	switch(option)
	{
		case 1:
			cout << "\nEnter your side length: ";
			cin >> a;
			cout << "Enter your hypotenuse: ";
			cin >> c;
			kulma = acos(a / c);
			break;
		case 2:
			cout << "\nEnter your opposite length: ";
			cin >> a;
			cout << "Enter your hypotenuse: ";
			cin >> c;
			kulma = asin(a / c);
			break;
		case 3:
			cout << "\nEnter your opposite length: ";
			cin >> a;
			cout << "Enter your side length: ";
			cin >> b;
			kulma = atan(a / b);
			break;
		case 4:
			cout << "\nEnter your first length: ";
			cin >> a;
			cout << "Enter your second length: ";
			cin >> b;
			cout << "Enter your first angle: ";
			cin >> alpha;
			alpha = alpha * PI / 180;
			kulma = asin(a / (b * sin(alpha)));
			break;
		case 5:
			cout << "\nEnter your first length: ";
			cin >> a;
			cout << "Enter your second length: ";
			cin >> c;
			cout << "Enter the third length: ";
			cin >> alpha;
			b = sqrt(pow(a, 2) + pow(b, 2) - 2 * a * c * cos(alpha));
			kulma = acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
			break;

		default:
			cout << "\nError, try again!\n";
			break;
	}

	return kulma;
}

long int Potenssi(){
	int number, power = 0;
	cout << "\nEnter the base number: ";
	cin >> number;
	cout << "Enter the power: ";
	cin >> power;
	number = pow(number, power);

	return number;
}

double Square(){
	double number = 0.0;
	cout << "\nEnter the number: ";
	cin >> number;
	number = sqrt(number);

	return number;
}