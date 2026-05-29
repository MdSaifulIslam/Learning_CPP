/*
* NAMESPACE
* 
* Named declarative region used for declaring types
* The types are not visible outside the namespace, it makes a region  for thous types
* Prevents name clashes
* Standard library is in std namespace
* Helps modularize code
*		namespace <name>{
			(namespace, class, structure, function, variable, etc)
		}

* NAMESPACE ACCESS
* Types inside a namespace have a scope
* Cannot be accessed outside the namespace
* Either open the namespace or the type
*	use the global using the declarative and open the entire namespace
*		using namespace std;
*	use the using declarative and open a specific type
*		using std::cout;
*	using the full qualified name
*		std::cout << "C++" << std::endl;

*/

/*
* 
*/

void nameSpace();