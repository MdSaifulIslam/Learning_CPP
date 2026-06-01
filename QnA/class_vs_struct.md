# `class` vs `struct` in C++ — Similarities and Differences

---

## 1. The Bottom Line

In C++, `class` and `struct` are **almost identical**. There are exactly **two technical differences**:

| Aspect | `struct` | `class` |
|---|---|---|
| Default member access | **public** | **private** |
| Default inheritance | **public** | **private** |

That's it. Everything else is identical.

---

## 2. Default Member Access

```cpp
struct A {
    int x;             // public by default
    void foo() {}      // public by default
};

class B {
    int x;             // private by default
    void foo() {}      // private by default
};

int main() {
    A a;
    a.x = 5;           // OK - public
    a.foo();           // OK

    B b;
    b.x = 5;           // ERROR - private
    b.foo();           // ERROR - private
}
```

### Equivalent versions
```cpp
// These two are 100% equivalent
struct A {
private:
    int x;
public:
    void foo() {}
};

class A {
    int x;
public:
    void foo() {}
};
```

---

## 3. Default Inheritance

```cpp
struct Base { int x; };

// struct inheritance defaults to PUBLIC
struct D1 : Base { };
// Equivalent to: struct D1 : public Base { };

// class inheritance defaults to PRIVATE
class D2 : Base { };
// Equivalent to: class D2 : private Base { };

D1 d1;
d1.x = 5;     // OK - public inheritance keeps x public

D2 d2;
d2.x = 5;     // ERROR - private inheritance makes x private
```

```cpp
// To get the same behavior, be explicit:
class D1 : public Base { };    // now matches struct's default
struct D2 : private Base { };  // now matches class's default
```

---

## 4. Everything Else Is the Same

Both `struct` and `class` support all C++ features:

### Constructors, destructors, methods
```cpp
struct Car {
    float fuel;

    Car(float f) : fuel(f) {}   // constructor
    ~Car() { }                   // destructor
    void drive() { fuel--; }     // method
};

// Identical with class
class Car {
public:
    float fuel;
    Car(float f) : fuel(f) {}
    ~Car() { }
    void drive() { fuel--; }
};
```

### Access modifiers
```cpp
struct S {
private:
    int hidden;
public:
    int exposed;
protected:
    int forChildren;
};

class C {
private:
    int hidden;
public:
    int exposed;
protected:
    int forChildren;
};
// Same 3 access levels available in both
```

### Inheritance
```cpp
struct Animal { virtual void speak() = 0; };
struct Dog : Animal { void speak() override { cout << "Woof"; } };

class Animal { public: virtual void speak() = 0; };
class Dog : public Animal { public: void speak() override { cout << "Woof"; } };
```

### Virtual functions / polymorphism
```cpp
struct Shape {
    virtual double area() const = 0;   // pure virtual - works in struct
    virtual ~Shape() = default;
};

class Shape {
public:
    virtual double area() const = 0;   // same in class
    virtual ~Shape() = default;
};
```

### Templates
```cpp
template<typename T>
struct Container {     // template struct - works
    T value;
};

template<typename T>
class Container {      // identical with class
public:
    T value;
};
```

### Operator overloading
```cpp
struct Vector {
    int x, y;
    Vector operator+(const Vector& other) const {
        return {x + other.x, y + other.y};
    }
};

class Vector {
    int x, y;
public:
    Vector operator+(const Vector& other) const {
        return {x + other.x, y + other.y};
    }
};
```

### Friend declarations
```cpp
struct A {
    friend class Helper;     // works
    friend void func();      // works
};

class A {
    friend class Helper;     // works
    friend void func();      // works
};
```

### Static members
```cpp
struct Counter {
    static int count;
    static void increment() { count++; }
};

class Counter {
public:
    static int count;
    static void increment() { count++; }
};
```

---

## 5. The Convention — Not Enforced by Language

By **community convention** (not by the language):

### Use `struct` for:
- Simple data aggregates (POD-like)
- All members public
- Few or no methods
- "Bag of data" semantics

```cpp
struct Point { int x, y; };

struct Rectangle {
    Point topLeft;
    Point bottomRight;
};

struct Pixel { uint8_t r, g, b, a; };

struct HttpResponse {
    int statusCode;
    string body;
    map<string, string> headers;
};
```

### Use `class` for:
- Encapsulated objects with private state
- Public interface + hidden implementation
- Behavior-focused types
- Invariants to maintain

```cpp
class BankAccount {
    double balance;           // hidden invariant
    string owner;
public:
    BankAccount(string n, double b);
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
};

class FileHandle {
    FILE* handle;
public:
    explicit FileHandle(const string& path);
    ~FileHandle();
    void write(const string& data);
};
```

---

## 6. Mixing Them — Perfectly Legal

```cpp
struct Base { virtual void foo() = 0; };
class Derived : public Base {       // OK - mix freely
    void foo() override { }
};

class Container { };
struct ContainerWrapper : Container { };   // also OK
```

You can even forward-declare with the wrong keyword (most compilers warn but allow):

```cpp
// header.h
class MyType;   // forward declaration

// source.cpp
struct MyType { int x; };   // defined as struct - usually still works
                             // (some compilers issue warning C4099)
```

---

## 7. C `struct` vs C++ `struct` — Different Things!

C's `struct` is much more limited:

| Feature | C `struct` | C++ `struct` |
|---|---|---|
| Member variables | Yes | Yes |
| Member functions | NO | YES |
| Constructors/destructors | NO | YES |
| Inheritance | NO | YES |
| Access modifiers | NO | YES |
| Static members | NO | YES |
| Templates | NO | YES |
| Default access | (no concept) | public |

```c
// C - just data, no methods
struct Point {
    int x;
    int y;
};
// Usage: struct Point p; (or typedef to avoid the 'struct' keyword)
```

```cpp
// C++ - can have methods, constructors, inheritance, etc.
struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
    double length() const { return sqrt(x*x + y*y); }
};
Point p(3, 4);   // no 'struct' keyword needed
```

---

## 8. POD and Aggregate Concepts

Both `struct` and `class` can be POD (Plain Old Data) or aggregates if they meet certain criteria. The KEYWORD doesn't matter — only the contents do.

```cpp
// Both are aggregates (can use brace initialization, no constructors)
struct A { int x; int y; };
class  B { public: int x; int y; };

A a = {1, 2};   // OK - aggregate initialization
B b = {1, 2};   // OK - aggregate initialization (class works too!)

// Both can be "trivial" types
static_assert(std::is_trivial_v<A>);
static_assert(std::is_trivial_v<B>);

// Both can be "standard layout"
static_assert(std::is_standard_layout_v<A>);
static_assert(std::is_standard_layout_v<B>);
```

The concept of POD/aggregate is about **structure**, not the keyword used.

---

## 9. Inheritance Access Demonstration

```cpp
struct Base {
    int pub;
protected:
    int prot;
private:
    int priv;
};

// struct default = public inheritance
struct D1 : Base {
    void test() {
        pub  = 1;    // OK
        prot = 2;    // OK
        // priv = 3; // ERROR - private to Base regardless
    }
};

D1 d1;
d1.pub = 5;   // OK - still public in D1

// class default = private inheritance
class D2 : Base {
    void test() {
        pub  = 1;    // OK (accessible inside D2)
        prot = 2;    // OK
    }
};

D2 d2;
d2.pub = 5;   // ERROR - pub became PRIVATE in D2 due to private inheritance!
```

---

## 10. When Does the Choice Actually Matter?

### When access matters (most common)
```cpp
// If you want public-by-default - use struct (less typing)
struct Pair { int first; int second; };

// If you want encapsulation - use class
class Account { double balance; public: ... };
```

### When you need explicit aggregate/POD semantics
```cpp
// Use struct - it signals "this is plain data"
struct Configuration { string host; int port; };
```

### When dealing with C interop
```cpp
// Use struct - matches C's struct layout expectations
extern "C" struct CData { int field1; int field2; };
```

---

## 11. Common Misconceptions

```
MYTH: struct is C, class is C++
FACT: C++ supports both fully. struct has just the access default change.

MYTH: struct can't have methods
FACT: C++ struct can have anything class can.

MYTH: struct is for stack, class is for heap
FACT: Both can be allocated on stack OR heap. The keyword doesn't dictate.

MYTH: struct can't inherit
FACT: C++ struct can inherit fully, with any access specifier.

MYTH: struct is faster than class
FACT: Identical performance. Compiler treats them the same.

MYTH: struct is a value type, class is a reference type
FACT: That's C# / Swift. NOT C++. Both are value types in C++.
```

---

## 12. Summary

```
SIMILARITIES (almost everything):
  - Both support constructors, destructors, methods
  - Both support inheritance, virtual functions, polymorphism
  - Both support templates
  - Both support operator overloading
  - Both support friend declarations
  - Both support static members
  - Both support all access modifiers (public/protected/private)
  - Both have identical memory layout and performance

DIFFERENCES (only two):
  - Default member access:    struct = public,   class = private
  - Default inheritance:      struct = public,   class = private

CONVENTION (community, not language):
  struct -> plain data containers (POD-like, public-by-default)
  class  -> encapsulated objects (private state + public interface)

GOLDEN RULES:
  1. Use struct for "bag of data" (Point, Rectangle, Config)
  2. Use class when you have invariants to protect (BankAccount, FileHandle)
  3. Choosing one over the other is a STYLE decision, not technical
  4. The compiler doesn't care which you pick - both produce identical code
```
