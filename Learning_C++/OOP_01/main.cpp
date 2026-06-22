#include "Car.h"
#include<iostream>
#include "Integer.h"
#include "Operator.h"

using namespace std;

struct Point {
	int x;
	int y;
};

void drawLine(int x1, int y1, int x2, int y2) {
	cout << x1 << endl;
}

void drawLine(Point start, Point end) {
	cout << start.x << endl;
}

int main() {

	Vector2D pos1(5, 10);
	Vector2D pos2(3, 4);

	// 2. Use our custom '+' operator
	Vector2D totalPos = pos1 + pos2;

	// 3. Use our custom '<<' operator to print the objects smoothly
	std::cout << "Position 1: " << pos1 << "\n";
	std::cout << "Position 2: " << pos2 << "\n";
	std::cout << "Combined Position: " << totalPos << "\n";


	pos2 = pos1 + pos2;
	std::cout << "Updated Position -> pos2: " << pos2 << "\n";
	

	Interger i(5);
	Interger i2 = i;
	cout << i.getValue() << endl;
	cout << i2.getValue() << endl;

	Interger i3(55);
	i2 = i3; // it crushed because of no copy assignment constructor

	cout << i2.getValue() << endl;
	cout << i3.getValue() << endl;



	//Car c;
	//c.Dashboard();
	//cout << "\n" << endl;

	//Car cf(8);
	//cf.Dashboard();
	//Car::CarCount();
	//cout << "\n" << endl;

	//Car cfp(8, 100);
	//cfp.Dashboard();
	//Car::CarCount();
	//cout << "\n" << endl;

	//Point start(2, 4);
	//Point end(7, 5);
	//Point end2(7);
	//cout << end2.y << endl;

	//drawLine(start, end);
	//drawLine(start.x, start.y, end.x, end.y);
	//Car car(8);
	////car.fillFuel(6);
	//car.Accelerate();
	//car.Accelerate();
	//car.Accelerate();
	//car.Accelerate();
	//car.Accelerate();
	//car.Dashboard();

	return 0;
}
