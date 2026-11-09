#include <iostream>
#include <set>
#include <functional>

using namespace std;

void Set(){

	multiset<int, greater<int> > s{ 8,4, 6, 7, 9, 0, 1 };
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(8);

	auto itr = s.begin();
	while (itr != s.end()) {
		cout << *itr++ << " ";
	}

	cout << endl;

	s.erase(0);
	cout << *s.begin() + 4 << endl;

	itr = s.begin();
	while (itr != s.end()) {
		cout << *itr++ << " ";
	}

	cout << endl;

	itr = s.find(99);
	if (itr != s.end()) {
		cout << "Found" << endl;
	}
	else {
		cout << "Not found" << endl;
	}

	auto found = s.equal_range(3);
	while (found.first != found.second) {
		cout << *found.first++ << " ";
	}
}

int main() {

	Set();

	return 0;
}