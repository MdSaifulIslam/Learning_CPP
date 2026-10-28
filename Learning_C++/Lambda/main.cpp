#include<iostream>

using namespace std;
//using Comparator = bool(*)(int, int);

template<typename T, int size, typename Comparator>
void Sort(T(&arr)[size], Comparator comp) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (comp(arr[j], arr[j + 1])) {
				T temp = move(arr[j]);
				arr[j] = move(arr[j + 1]);
				arr[j + 1] = move(temp);
			}
		}
	}
}

bool CompGrater(int x, int y) { return x > y; }
bool CompLess(int x, int y) { return x < y; }
struct CompFunObj {
	bool operator()(int x, int y) { return x > y; }
};

struct AtExit
{
	void operator()()const { cout << "Called after main()\n"; }
	static void Internal() { return AtExit{}(); }
	typedef void(*Fn)();
	operator Fn()const { return Internal; }
};

struct Unnamed
{
	int operator()(int x, int y)const { return x + y; }
	static int Internal(int x, int y) { return Unnamed{}(x, y); }
	typedef int(*Fn)(int, int);
	operator Fn()const { return Internal; }
};

int main() {

	AtExit handler{};
	atexit(handler);
	//atexit([]() { cout << "End of program";});

	[]() { cout << "This is a lambda function" << endl; }();
	auto fn = []() { cout << "This is a lambda function named as FN" << endl; };
	fn();

	void (*p)() = handler;
	p = fn;

	auto sum = [](int x, int y)->int { return x + y; };
	cout << sum(2, 3) << endl;

	int arr[]{ 1, 6, 8, 4, 0 };
	CompFunObj compFunObj;

	compFunObj(2, 3);
	for (auto a : arr) { cout << a << " "; }
	cout << endl;

	Sort(arr, compFunObj);

	for (auto a : arr) { cout << a << " "; }
	cout << endl;

	Sort(arr, CompLess);

	for (auto a : arr) { cout << a << " "; }
	cout << "\nEnd of main ..." << endl;

	return 0;
}