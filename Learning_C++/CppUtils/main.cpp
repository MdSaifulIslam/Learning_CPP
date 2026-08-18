#include<iostream>

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

	Color c = Color::RED;
	FillColor(c);
	FillColor(Color::GREEN);
	FillColor(static_cast<Color>(2));

	int x = static_cast<int>(Color::RED);
	cout << x << endl;

	char tc = static_cast<char>(TrafficLight::RED);
	cout << tc << endl;

	tc = static_cast<int>(TrafficLight::RED);
	cout << tc << endl;

	return 0;
}