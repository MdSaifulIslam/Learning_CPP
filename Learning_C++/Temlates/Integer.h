#pragma once
#include <iostream> 

using namespace std;

class Integer {
	int* m_pInt;
public:
	Integer();
	Integer(int value);
	Integer(const Integer& obj);
	Integer& operator=(const Integer& obj) noexcept;
	Integer(Integer&& obj) noexcept;
	Integer& operator=(Integer&& obj) noexcept;
	int getValue() const;
	void setValue(int value);
	~Integer();
};

ostream& operator<<(ostream& os, const Integer& obj);