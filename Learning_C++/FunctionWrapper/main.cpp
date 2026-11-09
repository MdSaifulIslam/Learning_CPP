#include <iostream>
#include <functional>

using namespace std;

int Square(int x) { return x * x; }
int AddFive(int x) { return x + 5; }
int Add(int x, int y) { return x + y; }
int Subtract(int x, int y) { return x - y; }
struct Max {
	int operator()(int x, int y)const { return x > y ? x : y; }
};

int Operation(int x, int y, function<int(int, int)> callback) {
	return callback(x, y);
}

int main() {

	try
	{
		function<int(int, int)> fun = Add;
		cout << Operation(5, 3, fun) << endl;

		fun = Subtract;
		cout << Operation(5, 3, fun) << endl;

		cout << Operation(5, 3, [](int x, int y) { return x * y;}) << endl;

		//function<int(int)> f_squ = Square;
		//cout << f_squ(7) << endl;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	//try
	//{
	//	function<int(int)> f_squ;
	//	if (f_squ)
	//	{
	//		cout << f_squ(7) << endl;
	//	}
	//	else {
	//		cout << "No target to invoke!" << endl;
	//	}

	//	Max m{};
	//	function<int(int, int)> f2 = m;
	//	cout << f2(3, 7) << endl;

	//	function<bool(int)> f3 = [](int x) { return x % 2 == 0 ? true : false;};
	//	cout << "is Even ? " << f3(77) << endl;
	//}
	//catch (const std::exception& ex)
	//{
	//	cout << ex.what() << endl;
	//}

	return  0;
}