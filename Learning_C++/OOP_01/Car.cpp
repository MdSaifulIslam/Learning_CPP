#include "Car.h"
#include<iostream>

int Car::totalCount = 0;

using namespace std;
Car::Car():Car(0) {
	cout << "Car()" << endl;
}

Car::Car(float fuel=0):Car(fuel, 0)
{
	cout << "Parameterized Car(fuel)" << endl;
}

Car::Car(float fuel, int pass)
{
	cout << "Parameterized Car(fuel, passengers)" << endl;
	totalCount++;
	this->fuel = fuel;
	this->passengers = pass;
	this->speed = 0;
}

Car::~Car() {
	totalCount --;
	cout << "Ending ~Car()" << endl;
}

void Car::fillFuel(float amount)
{
	fuel = amount;
}

void Car::Accelerate()
{
	speed++;
	fuel -= .5f;
}

void Car::Break()
{
	speed = 0;
}

void Foo(const Car &car){}

void Car::AddPassengers(int count)
{
	passengers = count;
	Foo(*this);
}

void Car::Dashboard() const
{
	std::cout << "Fuel: " << fuel << std::endl;
	std::cout << "Speed: " << speed << std::endl;
	std::cout << "Passengers: " << passengers << std::endl;
}

void Car::CarCount()
{
	std::cout << "total Cars:" << Car::totalCount << endl;
}
