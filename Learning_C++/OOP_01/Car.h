#pragma once
class Car {
private:
	float fuel{ 0 };
	float speed{ 0 };
	int passengers{ 0 };
	static int totalCount;

public:
	Car();
	Car(float fuel);
	~Car();
	void fillFuel(float amount);
	void Accelerate();
	void Break();
	void AddPassengers(int count);
	void Dashboard() const;
	static void CarCount();
};