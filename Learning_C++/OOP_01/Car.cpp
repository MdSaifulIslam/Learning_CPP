#include "Car.h"
#include<iostream>

int Car::totalCount = 0;

using namespace std;
Car::Car() {
	totalCount ++;
	cout << "Car()" << endl;
}
Car::Car(float fuel=0)
{
	totalCount++;
	cout << "Parameterized Car()" << endl;
	this->fuel = fuel;
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
