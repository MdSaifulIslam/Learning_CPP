#pragma once
class Integer {
	int* m_pInt;
public:
	Integer();
	Integer(int value);
	Integer(const Integer& obj);
	Integer& operator=(const Integer& obj);
	Integer(Integer&& obj);
	Integer& operator=(Integer&& obj);
	int getValue() const;
	void setValue(int value);
	~Integer();
};