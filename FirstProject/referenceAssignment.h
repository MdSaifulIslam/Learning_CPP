
void add(int a, int b, int& ref);
void fact(int a, int& ref);
void swap(int& a, int& b);
void runRefAssignment();
int& fun();


void add(int a, int b, int& ref) {
	ref = a + b;
}

void fact(int a, int& ref) {
	for (int i = 1; i <= a; i++)
		ref = ref * i;
}

void swap(int& a, int& b) {
	a = a + b;
	b = a - b;
	a = a - b;
}