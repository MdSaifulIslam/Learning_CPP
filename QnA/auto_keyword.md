# `auto` Keyword in C++ — Complete Guide

---

## 1. What `auto` Does

Tells the compiler: **"You figure out the type — at compile time."**

```cpp
auto x = 5;          // int
auto y = 3.14;       // double
auto z = 3.14f;      // float
auto c = 'A';        // char
auto b = true;       // bool
auto s = "Hello";    // const char*  (NOT std::string!)

// auto is compile-time, NOT dynamic typing
auto x = 5;
x = "hi";   // ERROR - x is int forever
```

---

## 2. CRITICAL RULE — `auto` Drops const and References

```cpp
int        x   = 5;
const int  cx  = 10;
int&       ref = x;
const int& cr  = x;

auto a = x;     // int          - plain copy
auto b = cx;    // int          - const DROPPED
auto c = ref;   // int          - reference DROPPED
auto d = cr;    // int          - both DROPPED
```

`auto` always makes a COPY by default. It strips top-level const and references.

---

## 3. Adding const and `&` Manually

```cpp
int x = 5;
const int cx = 10;

auto& r = x;            // int&         - reference
auto& cr = cx;          // const int&   - low-level const KEPT
const auto a = x;       // const int
const auto& r2 = x;     // const int&   - READ-ONLY ref, no copy (best for reading)

// Pointers
auto p = &x;            // int*
auto* p2 = &x;          // int* - explicit pointer syntax (clearer)
const auto* p3 = &cx;   // const int*
```

---

## 4. The Golden Pattern — `const auto&`

```cpp
string name = "Alice";

auto        copy = name;   // string         - FULL COPY (expensive)
auto&       ref  = name;   // string&        - reference, can modify
const auto& cref = name;   // const string&  - read-only, NO COPY (BEST for reading)
```

---

## 5. Range-Based For Loops — Where `auto` Shines

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// Copy each element - expensive for large types
for (auto x : v) { x = 99; }              // modifies COPY only

// Reference - modifies originals
for (auto& x : v) { x = 99; }             // modifies v

// Const reference - read-only, no copy (BEST for reading)
for (const auto& x : v) { cout << x; }    // efficient + safe

// Structured binding (C++17)
map<string, int> scores = {{"Alice", 95}};
for (const auto& [name, score] : scores) {
    cout << name << ": " << score;
}
```

---

## 6. Function Return Type Deduction (C++14)

```cpp
auto add(int a, int b) {
    return a + b;     // compiler deduces: int
}

// All return paths must return the SAME type
auto f(bool flag) {
    if (flag) return 1;       // int
    else return 2.0;          // ERROR - inconsistent
}
```

### Trailing Return Type (C++11)

```cpp
auto multiply(int a, double b) -> double {
    return a * b;
}

// Essential when return type depends on template args
template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
```

---

## 7. `auto` with Lambdas

```cpp
// Lambda type is unnamed - auto is the ONLY way
auto square = [](int x) { return x * x; };

// Generic lambda (C++14)
auto print = [](auto x) { cout << x; };
print(42);        // int
print(3.14);      // double
print("Hello");   // const char*
```

---

## 8. `auto` with Complex Types — Where It's Essential

```cpp
// Without auto - painful
map<string, vector<pair<int, double>>>::iterator it = data.begin();

// With auto - clean
auto it = data.begin();

// STL find / algorithms
auto found = find(v.begin(), v.end(), target);
```

---

## 9. Structured Bindings (C++17)

```cpp
// Unpack pair
pair<string, int> p = {"Alice", 95};
auto [name, score] = p;

// Unpack tuple
tuple<int, double, string> t = {1, 3.14, "hello"};
auto [i, d, s] = t;

// Unpack struct
struct Point { int x; int y; };
Point pt = {10, 20};
auto [x, y] = pt;

// With map (most common)
for (const auto& [key, value] : myMap) { ... }
```

---

## 10. `auto` vs `decltype`

```cpp
int x = 5;
int& ref = x;

auto       a = ref;   // int    - reference DROPPED
decltype(ref) b = x;  // int&   - reference KEPT

// decltype preserves exact type, auto drops top-level qualifiers
```

---

## 11. C++20 — `auto` in Function Parameters

```cpp
// Same as template
void print(auto x) {
    cout << x;
}

// Equivalent to:
template<typename T>
void print(T x) {
    cout << x;
}
```

---

## 12. When NOT to Use `auto`

```cpp
// Type not obvious - hurts readability
auto result = process();    // what type is this?

// Proxy types - auto gives wrong result
vector<bool> v = {true, false};
auto val = v[0];    // NOT bool! It's vector<bool>::reference (proxy)
bool val = v[0];    // CORRECT

// API/interface code - explicit type documents intent
int userAge = getAge();    // clear
auto userAge = getAge();   // mystery
```

---

## 13. Common Mistakes

```cpp
// Mistake 1 - thinking auto preserves const/ref
const int x = 5;
auto y = x;          // int, not const int!
y = 10;              // OK (surprise!)

// Mistake 2 - initializer list trap
auto arr = {1, 2, 3};   // initializer_list<int>, NOT int[]

// Mistake 3 - uninitialized
auto x;             // ERROR - nothing to deduce from

// Mistake 4 - forgetting const for read-only function args
void process(auto& item) { ... }      // can modify
void process(const auto& item) { ... } // read-only - prefer this for reading
```

---

## 14. Complete Cheat Sheet

```
SYNTAX                    DEDUCED TYPE          NOTES
──────────────────────────────────────────────────────────────────
auto x = expr             T                     copy, drops const/ref
auto& x = expr            T&                    reference, keeps low const
const auto& x = expr      const T&              read-only ref, NO copy
auto* x = &expr           T*                    pointer
const auto* x = &expr     const T*              read-only pointer
auto [a,b] = pair         T1, T2                structured binding C++17
auto fn = lambda          lambda type           only way to store lambda
auto f() -> T             T                     trailing return type
auto f() { return expr }  deduced from return   C++14 return deduction
void f(auto x)            template<T> f(T x)    C++20 abbreviated template

GOLDEN RULES:
  const auto& -> the best pattern for read-only access (no copy)
  auto&       -> when you need to modify the original
  auto        -> when you want a copy
  Always ask: "Is the type obvious to someone reading this line?"
```
