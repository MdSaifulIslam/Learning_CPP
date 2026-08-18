#include<iostream>
#include<sstream>

using namespace std;

enum class Color : long { RED = 5, GREEN, BLUE };

void FillColor(Color color) {

	if (color == Color::RED) {
		cout << "Red" << endl;
	}
	else if (color == Color::GREEN) {
		cout << "Green" << endl;
	}else if (color == Color::BLUE) {
		cout << "Blue" << endl;
	}
}

enum class TrafficLight :char { RED = 'b', GREEN, YELLOW };

int main() {

	string s = "hello";
	s[0] = 'W';
	char ch = s[2];

	cout << s << endl;
	//cin >> s;
	cout << s.length() << endl;

	string s1{ "hello" }, s2{ "world" };
	s = s1 + s2;
	s += s1;
	cout << s << endl;

	s.insert(6, "New Insert");
	cout << s << endl;

	s.erase();
	s.clear();

	stringstream ss;
	int a{ 5 }, b{ 6 };
	int sum = a + b;

	ss << "Sum of " << a << " & " << b << " is: " << sum << endl;
	cout << ss.str() << endl;

	string intData = "12 15 80, abc, 77";
	ss.str(intData);

	while (ss >> a) {
		cout << a << endl; // it will print till 80;
	}

	//Color c = Color::RED;
	//FillColor(c);
	//FillColor(Color::GREEN);
	//FillColor(static_cast<Color>(2));

	//int x = static_cast<int>(Color::RED);
	//cout << x << endl;

	//char tc = static_cast<char>(TrafficLight::RED);
	//cout << tc << endl;

	//tc = static_cast<int>(TrafficLight::RED);
	//cout << tc << endl;

	return 0;
}