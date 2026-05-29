#include "externTest.h"
/*
* 

When sqrt is an intrinsic, the compiler replaces every sqrt(x)
with the CPU instruction directly:

	cout << sqrt(2.3);
			  ↓
	sqrtsd xmm0, [2.3]    ← inlined CPU instruction, NO call

There is NO function call left to redirect to your code.
So your function body  { return x + x; }  has nowhere to plug in.

The compiler says:
  "sqrt is something I generate inline as hardware instructions.
   It is not a real callable function anymore.
   You cannot give it a body — that makes no sense."
  → C2169


DETAILS:
-------------------------------------------------------------------
An intrinsic function is one the compiler knows how to generate
DIRECTLY as CPU instructions — no function call needed.

Normal function:  sqrt(x) → call sqrt   (jump to a function body)

Intrinsic:        sqrt(x) → sqrtsd xmm0, xmm0
							↑ a single native x86 CPU instruction
							baked right into your code — no call at all


The CPU has a HARDWARE square-root instruction (sqrtsd).
The compiler knows this. So for sqrt, it can skip the function
entirely and emit that one instruction directly.

→ sqrt is "built into" the compiler = an intrinsic

DEBUG mode (/Od):
  → Intrinsics DISABLED
  → sqrt is treated as a NORMAL external function
  → your definition  double sqrt(double){...}  is ACCEPTED
  → linker uses your version (as I explained before)
  → output: 4.6 

RELEASE mode (/O2):
  → /O2 automatically enables /Oi  (generate intrinsic functions)
  → sqrt is now recognized as a BUILT-IN INTRINSIC
  → the compiler wants to emit the native sqrtsd instruction
  → you CANNOT define a function that IS an intrinsic
  → ERROR C2169 

*/
//extern "C" double sqrt(double x) {
//	using namespace std;
//
//	//std::cout << x << std::endl;
//
//	return x + x;
//}