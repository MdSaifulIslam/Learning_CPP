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

template<typename T, int size, typename Callback>
void ForEach(T(&arr)[size], Callback operation) {
	for (int i = 0; i < size; i++) {
		operation(arr[i]);
	}
}

class Product {
	string name;
	float price;
public:
	Product(const string &n, float p):name(n), price(p){}
	void AssignFinalPrice() {
		float taxes[]{ 12, 5, 5 };
		float basePrice{ price };
		ForEach(taxes, [basePrice, this](float tax) {
			float taxedPrice = basePrice * tax / 100;
			price += taxedPrice;
			});
	}
	float GetPrice() { return price; }
};

int main() {

	// nasted lambda
	[](int x) {
		x *= 2;
		[](int x) {
			cout << x << endl;
			}(x);
		}(5);

	static int i = 1000001;
	atexit([]() {cout << i << endl;});

	//Product product{"Watch", 500};
	//product.AssignFinalPrice();
	//cout << product.GetPrice() << endl;

	AtExit handler{};
	//atexit(handler);
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
	cout << "Printitng normal print ... \n";
	for (auto a : arr) { cout << a << " "; }
	cout << endl;

	//Sort(arr, [](auto x, auto y) { return x < y;});

	auto fnP = [](auto x, auto y) { return x < y;};
	Sort(arr, fnP);

	auto Cout = [](auto x) {cout << x << " ";};
	cout << "Printitng after first sort x < y ... \n";
	ForEach(arr, Cout);
	cout << endl;

	Sort(arr, CompGrater);

	cout << "Printitng after second sort x > y ... \n";
	ForEach(arr, Cout);
	cout << endl;

	int offset = 5;
	ForEach(arr, [&offset](auto& x) {
		x += offset;
		++ offset;
		});

	cout << "Printitng after offset add ++offset + x ... \n";
	ForEach(arr, Cout);
	cout << " \nEnd of main ..." << endl;

	return 0;
}