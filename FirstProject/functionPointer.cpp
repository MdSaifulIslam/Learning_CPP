#include "functionPointer.h"
#include<iostream>

using namespace std;

void Print(int count, char ch) {
	for (int i = 0; i < count; i++) {
		cout << ch;
	}
	cout << "\n";
}

void endMessage() {
	cout << "Ending the program" << endl;
}

// A function that takes another function as input
void doTwice(void (*action)(int)) {
	action(1);
	action(2);
}

void print(int x) { cout << "print: " << x << endl; }
void square(int x) { cout << "square: " << x * x << endl; }

void functionPointer()
{
	/*
	Functions in C/C++ are SPECIAL:
  → A function NAME auto-converts to its address (function pointer)
  → A function POINTER auto-converts back when called

	So all of these resolve identically:
  Print          = address
  &Print         = address
  *Print         = function (auto re-decays to pointer)
  **Print        = same (decays again)
  ***Print       = same — you can keep going forever!

  Print()        = call
  (*Print)()     = call
  (**Print)()    = call
  (***Print)()   = call
  (***printPtr)  = call

	This is a quirk of C — functions are NOT real first-class values.
	
	*/
	atexit(endMessage);
	//doTwice(pri)
	Print(10, '#');
	(*Print)(15, '*');
	(**Print)(5, '&');
	(***Print)(60, '&');
	(&Print)(50, '*');
	void (*printPtr)(int, char) = Print;
	(*printPtr) (12, '+'); // invocked as pointer dereference
	printPtr(10, 'S');
	(*****printPtr) (12, '+');

	cout << "\nEnd message is: " << endl;
}