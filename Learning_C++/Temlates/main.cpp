#include<iostream>
#include <utility>
#include <string>
#include "Integer.h"

using namespace std;

template<typename T, typename S>
typename conditional<(sizeof(T) > sizeof(S)), T, S>::type Max(T x, S y) {
	return x > y ? x : y;
}

template < typename intPointer, typename intSize>
auto ArraySum(intPointer arr_pointer, intSize array_size) {
	int sum{};
	for (int i = 0; i < array_size; ++i) {
		sum += arr_pointer[i];
	}

	return sum;
}

template < typename intPointer, typename intSize>
auto MaxNumArr(intPointer arr_pointer, intSize array_size) {
	int max{INT_MIN};
	for (int i = 0; i < array_size; ++i) {
		if(arr_pointer[i]> max) max = arr_pointer[i];
	}

	return max;
}

template < typename intPointer, typename intSize>
auto MaxMin(intPointer arr_pointer, intSize array_size) {
	int max{ INT_MIN };
	int min{ INT_MAX };
	for (int i = 0; i < array_size; ++i) {
		if (arr_pointer[i] > max) max = arr_pointer[i];
		if (arr_pointer[i] < min) min = arr_pointer[i];
	}

	return make_pair(min, max);
}
 
template char Max(char x, char y);

// Explicit Specialization
template <>
const char* Max<const char*>(const char* x, const char* y) {
	return strcmp(x, y) > 0 ? x : y;
}

// Non type template arguments
template<typename T, int size>
T Sum(T(&parr)[size]) {
	T sum{};
	for (int i = 0; i < size; i++) {
		sum += parr[i];
	}
	return sum;
}

class Empolyee {
	string m_Name;
	Integer m_ID;

public:
	//Empolyee(const string& name, const Integer& id) :
	//	m_Name{ name },
	//	m_ID{ id } {
	//	cout << "Employee(const string& name, const Integer& id)" << endl;
	//}
	template<typename T1, typename T2>
	Empolyee(T1 && name, T2 && id) :
		m_Name{ forward<T1>(name) },
		m_ID{ forward<T2>(id) } {
		cout << "Employee(const string&& name, const Integer&& id)" << endl;
	}
};

template<typename T1, typename T2>
Empolyee* Create(T1&& a, T2&& b) {
	return new Empolyee(forward<T1>(a), forward<T2>(b));
}

int main() {

	//Empolyee emp{ "Saiful", Integer{100} }; // even r-value, it calles copy constructor
	//string name = "Saiful";
	//Integer val{ 100 };
	//Empolyee emp2{ name, val };
	auto emp = Create("Saiful", Integer{ 100 });

	//float a = 244;
	//double b = 3.7;
	
	//cout << Max(a, b) << endl;

	//const char* arrA{ "B" };
	//const char* arrB{ "A" };

	//cout << Max(arrA, arrB) << endl;

	//int (*pfn)(int, int) = Max;

	//int arr[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//cout << ArraySum(arr, 10) << endl;
	//cout << MaxNumArr(arr, 10) << endl;
	//int* p = arr;
	//cout << Sum(arr) << endl;

	//auto [lowest, highest] = MaxMin(arr, 10);
	//cout << "Min: " << lowest << " | Max: " << highest << endl;

	return 0;
}