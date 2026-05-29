extern "C" int Add(int a, int b) { return a + b; }
int Add(float a, int b){ return a + b; }

void PrintA(double a){}
extern "C" void PrintA(int a) {}