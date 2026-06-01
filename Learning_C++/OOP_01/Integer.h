#pragma once
class Interger {
	int* m_pInt;
public:
	Interger();
	Interger(int value);
	Interger(const Interger& obj);
	int getValue() const;
	void setValue(int value);
	~Interger();
};