#include<iostream>

using namespace std;
using Comparator = bool(*)(int, int);

template<typename T, int size>
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

int main() {

	int arr[]{ 1, 6, 8, 4, 0 };
	for (auto a : arr) { cout << a << " "; }
	cout << endl;

	Sort(arr, CompGrater);

	for (auto a : arr) { cout << a << " "; }
	cout << endl;

	Sort(arr, CompLess);

	for (auto a : arr) { cout << a << " "; }
	cout << endl;

	return 0;
}