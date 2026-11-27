#include <iostream>
#include <string_view>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <list>
#include <ranges>

using namespace std;

template<typename Container>
void Print(const Container& container, string_view message = "", string_view sep = " ") {
	cout << "#### " << (message.empty() ? "No Output" : message) << " ####" << endl;
	cout << "[ ";
	string_view tab = "";
	if (sep == "\n") {
		tab = "    ";
		cout << sep;
	}
	for (auto& e : container) {
		cout << tab << e << sep;
	}
	cout << "]" << endl << endl;
}

int main() {

	vector<int> data(20);
	iota(data.begin(), data.end(), 20);
	Print(data, "data");

	random_device rd;
	shuffle(data.begin(), data.end(), rd);
	Print(data, "Shuffeled Data");

	sort(data.begin(), data.end());
	Print(data, "Sorted Data");

	list<int> dest(10);
	auto out = copy(data.begin(), data.begin() + 5, dest.begin());
	Print(ranges::subrange{ dest.begin(), out });

	for_each(dest.begin(), out, [](int& x) { if (x % 2 != 0) x *= 2; });
	Print(ranges::subrange{ dest.begin(), out }, "Odd doubled");

	return 0;
}