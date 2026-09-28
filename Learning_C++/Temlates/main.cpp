#include<iostream>
#include <utility>
#include <string>
#include<vector>
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

void Print() {
	cout << endl;
}
template<typename T, typename... Params>
void Print(T &&a, Params&&... args) {
	cout << a;
	if (sizeof... (args) != 0) cout << ", ";
	Print(forward<Params>(args)...);
}

template<typename T, int size>
class Stack {
	T m_Buffer[size];
	int m_Top{ -1 };
public:
	Stack() = default;
	Stack(const Stack& obj) {
		m_Top = obj.m_Top;
		for (int i = 0; i <= m_Top; i++) {
			m_Buffer[i] = obj.m_Buffer[i];
		}
	}
	void Push(const T &elem) {
		m_Buffer[++m_Top] = elem;
	}
	void Pop();
	bool isEmpty() const {
		return m_Top <= -1;
	}
	const T& Top() const {
		return m_Buffer[m_Top];
	}
	static Stack Create();
};

template<typename T, int size>
void Stack<T, size>::Pop() {
	--m_Top;
}

template<typename T, int size>
Stack<T, size> Stack<T, size>::Create() {
	return Stack<T, size>();
}

template<typename T>
class Printer {
	T* m_pData;
public:
	Printer(T* data) :m_pData(data) {

	}
	void Print() {
		cout << "{ " << *m_pData << " }" << endl;
	}
	T* getData() {
		return m_pData;
	}
};

template<>
void Printer<vector<int>>::Print() {
	cout << "{ ";
	for (const auto &x : *m_pData) {
		cout << x << " ";
	}
	cout << "}" << endl;
}
//template<>
//class Printer<char> {
//	char* m_pData;
//public:
//	Printer(char* data) : m_pData(data) {}
//	void Print() {
//		cout << "{ " << m_pData << " }" << endl;   // pass char* → string overload
//	}
//	char* getData() {
//		return m_pData;
//	}
//};

int main() {

	int data = 10;
	float f = 77.77;
	const char* p{ "Hello World" };
	Printer<const char *> p1(&p);
	p1.Print();
	cout << p << " " << &p << " " << *(&p) << " " << **(&p) << endl;
	cout << *(p1.getData()) << endl;
	char buf[] = "Hello World buffer";
	cout << buf << " " << &buf << " " << *(&buf) << " " << **(&buf) << endl;
	Printer<char[19]> p2(&buf);
	p2.Print();
	cout << *(p2.getData()) << endl;

	vector<int> v{ 1, 2, 3, 4, 5 };
	Printer<vector<int>> pv(&v);
	pv.Print();
	auto p_pv = pv.getData();

	for (const auto& x : *p_pv) {
		cout << x << " ";
	}


	//Stack<string, 100> s;
	//s.Push("77fgfgfdg");
	//s.Push("37fdgdfg");
	//s.Push("33tyrtyrty");

	//auto s2(s);

	//while (!s2.isEmpty()) {
	//	cout << s2.Top() << " ";
	//	s2.Pop();
	//}

	//Integer val{ 100 };
	//Print(0, val, Integer{ 2 });

	//Print(1, 2, 3, 4, "abc", 's');
	//Empolyee emp{ "Saiful", Integer{100} }; // even r-value, it calles copy constructor
	//string name = "Saiful";
	//Integer val{ 100 };
	//Empolyee emp2{ name, val };
	//auto emp = Create("Saiful", Integer{ 100 });

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