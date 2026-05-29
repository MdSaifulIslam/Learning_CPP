
/*
1. change optimization to any sutable debug and test via disassembly window

* A function that is marked with inline keyword
* Such function are defined in header file
* Request the compiler to replace the call with the function body
* The overhead of the function call is avoided 
*		stack memory of for the arguments not required
*		no need to save the return address
* May improve the performance of the code
* 
*		inline void Function(arguments){
*			//implementation
*		}

*/

/*
IMPORTANT POINTS

* Only a request to the compiler
* Certain function may not be inlined
*		large function
*		funtions have too many conditional statements
*		recursive function
*		functions invocked through pointers
* 
* Different compiler have different rules
* Modern compiler may automatically inline even non-inline function
* Execssive inlining may increase binary size

*/

/*
MACROS VS INLINE FUNCTIONS

* MACRO														INLINE FUNCTIONS
* Word through test substitutin							The call is replaced with function body
* Error prone due to substitution						Save to use as it has function semantics
* nature
* Does not have an address								Has an address
* Can not be used for the member functions				Class menber function can be inline
* of a class
*/

inline int square(int x);
void inlineFun();