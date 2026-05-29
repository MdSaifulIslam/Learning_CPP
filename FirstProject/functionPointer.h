/*
* FUNCTION POINTER
* 
* Pointer that holds the addess of the function
* The type is same as the signature of the function (return type & arguments)
* Can be used to indirectly invock the function even if the function name is unknown
* Used by algorithms and classes for customization
* 
*		<ret>(*funPtr)(args) = &Funtion
*		int (*ptrAdd) (int, int) = &Add

*/

void functionPointer();
void Print(int count, char ch);
