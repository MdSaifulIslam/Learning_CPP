#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void Write() {
	ofstream out{ "data.txt" };
	out << "This is the 1st line." << endl;
	out << "This is the 2nd line." << endl;
	out << "This is the 1st line." << endl;
	out << "Total line is: " << endl;
	out << 3 << endl;
	out << 3.1416f << endl;

	out.close();
}

void Read() {
	ifstream input{ "data.txt" };
	string messages[4];
	getline(input, messages[0]);
	getline(input, messages[1]);
	getline(input, messages[2]);
	getline(input, messages[3]);

	int line_number;
	float PI;

	input >> line_number;
	input >> PI;
	//input >> PI;

	if (input.fail()) { cout << "Could not read" << endl; }

	if (input.good()) {
		cout << "IO successful" << endl;
	}
	else
	{
		cout << "Some IO failed" << endl;
	}

	input.close();

	cout << messages[0] << " " 
		<< messages[1] << " " 
		<< messages[2] << " " 
		<< messages[3] << " " 
		<< line_number << " " 
		<< PI << endl;

	input.open("data.txt");
	if (!input.is_open()) { cout << "Could not open file" << endl; return; }
	
	string line;
	cout << "\nPrint using loop ... " << endl;

	while (getline(input, line)) {
		cout << line << endl;
	}
	input.close();
}

int main() {

	Write();
	Read();

	return 0;
}