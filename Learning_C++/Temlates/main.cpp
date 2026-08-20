#include<iostream>
#include <utility>

using namespace std;

template<typename T, typename S>
typename conditional<(sizeof(T) > sizeof(S)), T, S>::type Max(T x, S y) {
	cout << sizeof(T) << " " << sizeof(S) << endl;
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
 

int main() {

	float a = 244;
	double b = 3.7;
	
	cout << Max(a, b) << endl;

	int arr[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	cout << ArraySum(arr, 10) << endl;
	cout << MaxNumArr(arr, 10) << endl;

	auto [lowest, highest] = MaxMin(arr, 10);
	cout << "Min: " << lowest << " | Max: " << highest << endl;

	return 0;
}