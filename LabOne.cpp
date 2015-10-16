// LabOne.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	double doubleInput;
	int intOutput;
	cout << "Please input a decimal number" << endl;
	cin >> doubleInput;
	cout << static_cast<int>(doubleInput) << endl;
	intOutput = static_cast<int>(doubleInput);

	ofstream stored_file("data.txt");

	stored_file << intOutput;
	stored_file.close();

	cout << "The variable that stores your number as a integer is intOutput " << endl;

	return 0;
}