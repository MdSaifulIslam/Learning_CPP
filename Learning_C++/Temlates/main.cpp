#include<iostream>

using namespace std;

template<typename T, typename S>
typename conditional<(sizeof(T) > sizeof(S)), T, S>::type Max(T x, S y) {
	cout << sizeof(T) << " " << sizeof(S) << endl;
	return x > y ? x : y;
}

int main() {
	
	cout << Max(244.0f, 3.7) << endl;

	return 0;
}