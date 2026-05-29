#include "nameSpace.h"
#include<iostream>

using namespace std;

float calculate(float x, float y) {
	return (x + y) / 2;
}
//
//float calculate(float x, float y) {
//	return (x + y);
//}
 
void nameSpace() {
	calculate (3.2f, 4.5f);
}