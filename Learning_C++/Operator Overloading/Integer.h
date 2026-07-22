#pragma once
class Integer {
	int* m_pInt;
public:
	Integer();
	Integer(int value);
	Integer(const Integer& obj);
	Integer& operator=(const Integer& obj);
	Integer(Integer&& obj) noexcept;
	Integer& operator=(Integer&& obj) noexcept;
	int getValue() const;
	void setValue(int value);
	~Integer();

	Integer operator + (const Integer& a) const;
	Integer& operator ++();
	Integer operator ++(int)const;
	bool operator ==(const Integer& obj) const;
};