#include "Car.h"
#include<iostream>
#include "Integer.h"

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
	Interger i(5);
	Interger i2 = i;
	cout << i.getValue() << endl;
	cout << i2.getValue() << endl;


	//Car c;
	//c.Dashboard();

	//Car cp(8);
	//cp.Dashboard();
	//Car::CarCount();

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
