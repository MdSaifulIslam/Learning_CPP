# Copy Constructor in C++ — Complete Guide

---

## 1. What Is a Copy Constructor?

A constructor that creates a new object as a **copy** of an existing object of the same class.

```cpp
class Car {
public:
    Car(const Car& other);    // copy constructor signature
};
```

### Signature Breakdown
```
Car(const Car& other)
 ↑   ↑     ↑   ↑
 |   |     |   parameter name (anything)
 |   |     reference (& is MANDATORY)
 |   const (strongly recommended)
 the class type
```

---

## 2. Why `const Car&` (Not `Car` or `Car&`)?

### Why reference (`&`)?

```cpp
// Without reference - INFINITE RECURSION
Car(Car other) { ... }
//  ^^^^^^^^^
// Passing by value -> needs to copy 'other'
// Copying 'other' -> calls copy constructor
// Calls copy constructor -> needs to copy parameter
// ... infinite loop -> compiler ERROR
```

```cpp
// With reference - no copy needed to pass it
Car(const Car& other) { ... }   // OK - 'other' is just an alias
```

### Why `const`?

```cpp
Car(const Car& other);    // promises not to modify the source
                          // also accepts const objects as source
Car(Car& other);          // would refuse const objects:
                          // const Car c1; Car c2(c1); // ERROR
```

---

## 3. When the Copy Constructor Is Called

### Situation 1 — Direct Initialization
```cpp
Car c1;
Car c2(c1);     // calls copy constructor
```

### Situation 2 — Copy Initialization
```cpp
Car c1;
Car c2 = c1;    // calls copy constructor (NOT assignment!)
                // Looks like assignment but it's initialization
```

### Situation 3 — Pass by Value
```cpp
void process(Car c) { ... }    // takes Car by value

Car myCar;
process(myCar);    // copy constructor called to create 'c' from 'myCar'
```

### Situation 4 — Return by Value
```cpp
Car makeCar() {
    Car c;
    return c;       // potentially calls copy constructor for return value
}                   // (often elided by compiler - see RVO below)

Car result = makeCar();    // and/or here
```

### NOT called by assignment
```cpp
Car c1;
Car c2;
c2 = c1;        // calls COPY ASSIGNMENT operator (=), NOT copy constructor
                // c2 already exists - we're updating it, not creating it
```

---

## 4. Default Copy Constructor (Compiler-Generated)

If you don't write one, the compiler generates a default that does **member-wise copy**:

```cpp
class Point {
    int x;
    int y;
    string label;
};

// Compiler generates this automatically:
Point(const Point& other)
    : x(other.x), y(other.y), label(other.label) {}
//    ^^^^^^^^^   ^^^^^^^^^   ^^^^^^^^^^^^^^^^^^
// Copies each member using their respective copy mechanisms
```

```cpp
Point p1{5, 10, "first"};
Point p2 = p1;             // works fine - default copy is sufficient
// p2.x = 5, p2.y = 10, p2.label = "first"
```

---

## 5. The Shallow Copy Problem (Pointers)

The default copy constructor copies pointers **directly** — both objects point to the **same memory**:

```cpp
class Buffer {
    int* data;
    int size;
public:
    Buffer(int s) : size(s) {
        data = new int[size];     // allocate on heap
    }
    ~Buffer() {
        delete[] data;            // free heap memory
    }
    // No copy constructor written - default is shallow copy
};

int main() {
    Buffer b1(100);    // b1.data -> 0xABCD (heap memory)
    Buffer b2 = b1;    // b2.data -> 0xABCD (SAME memory!) - shallow copy
}   // Destructor called on b2 - deletes 0xABCD
    // Destructor called on b1 - tries to delete 0xABCD AGAIN
    // DOUBLE DELETE -> CRASH / undefined behavior
```

### Memory Picture
```
SHALLOW (default - DANGEROUS):       DEEP (custom - SAFE):

Stack:                                Stack:
  b1: {data, size}                      b1: {data, size}
       |                                     |
       v                                     v
Heap:                                 Heap:
  [array1]  <-- both point here       [array1]  <-- b1's data
       ^                                
       |                              [array2]  <-- b2's data
  b2: {data, size}                          ^
                                            |
                                       b2: {data, size}
                                       
TWO destructors free SAME array       Each destructor frees its OWN array
-> CRASH                              -> SAFE
```

---

## 6. Writing a Deep Copy Constructor

```cpp
class Buffer {
    int* data;
    int size;
public:
    Buffer(int s) : size(s) {
        data = new int[size];
    }

    // Deep copy constructor
    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];                  // allocate NEW memory
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];            // copy each element
    }

    ~Buffer() {
        delete[] data;
    }
};

Buffer b1(100);
Buffer b2 = b1;    // deep copy - b2 gets its OWN copy of the data
                    // both can be destroyed safely
```

---

## 7. Rule of Three / Five / Zero

### Rule of Three (C++98+)
If you need to write any one of these, you usually need all three:

```cpp
class Resource {
public:
    Resource(/* ... */);                          // normal constructor
    ~Resource();                                  // 1. Destructor
    Resource(const Resource& other);              // 2. Copy constructor
    Resource& operator=(const Resource& other);   // 3. Copy assignment
};
```

### Rule of Five (C++11+) - Add Move Semantics
```cpp
class Resource {
public:
    Resource(/* ... */);
    ~Resource();                                  // 1. Destructor
    Resource(const Resource& other);              // 2. Copy constructor
    Resource& operator=(const Resource& other);   // 3. Copy assignment
    Resource(Resource&& other) noexcept;          // 4. Move constructor
    Resource& operator=(Resource&& other) noexcept; // 5. Move assignment
};
```

### Rule of Zero (Modern Best Practice)
Use RAII classes (`std::unique_ptr`, `std::vector`, `std::string`) so you don't need to write any of these:

```cpp
class Buffer {
    std::vector<int> data;     // manages its own memory
public:
    Buffer(int s) : data(s) {}
    // NO destructor, copy constructor, etc. needed!
    // Compiler-generated versions work correctly because vector handles itself
};
```

---

## 8. Disabling Copying

For classes that shouldn't be copied (singletons, file handles, unique resources):

```cpp
class Singleton {
public:
    // Forbid copy constructor and copy assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton a;
Singleton b = a;    // COMPILE ERROR: copy constructor deleted
```

### Old C++98 way (worse)
```cpp
class Singleton {
private:
    Singleton(const Singleton&);              // declared private, not defined
    Singleton& operator=(const Singleton&);
};
// Causes linker error instead of compile error - less clear
```

---

## 9. Copy Constructor with Initializer List (Efficient)

Using member initializer list avoids default-construction + assignment:

```cpp
class Integer {
    int* m_pInt;

public:
    Integer() : m_pInt(new int(0)) {}             // default
    Integer(int v) : m_pInt(new int(v)) {}        // parameterized

    // INEFFICIENT - default-constructs then assigns
    Integer(const Integer& other) {
        m_pInt = new int(*other.m_pInt);
    }

    // EFFICIENT - direct initialization
    Integer(const Integer& other) : m_pInt(new int(*other.m_pInt)) {}

    ~Integer() { delete m_pInt; }
};
```

For `int*` it's a tiny difference. For complex members (vectors, strings, classes), initializer list is **significantly faster**.

---

## 10. Copy Constructor vs Copy Assignment

```cpp
class Car { };

Car c1;
Car c2(c1);     // copy CONSTRUCTOR  - creates new object from existing
Car c3 = c1;    // copy CONSTRUCTOR  - same as above (despite the = sign)

Car c4;
c4 = c1;        // copy ASSIGNMENT   - c4 already exists, updates it
```

```
Copy CONSTRUCTOR:  creates a new object
Copy ASSIGNMENT:   modifies an existing object
```

### Both signatures
```cpp
class Car {
public:
    Car(const Car& other);                  // copy constructor
    Car& operator=(const Car& other);       // copy assignment
};
```

---

## 11. RVO and NRVO — Compiler Optimization

Modern compilers often **skip** the copy constructor through Return Value Optimization:

```cpp
Car makeCar() {
    Car c;
    return c;          // expected: copy constructor called
}

Car result = makeCar();
// What ACTUALLY happens with RVO:
// 'c' is constructed DIRECTLY in 'result's memory
// No copy constructor call at all - just direct construction
```

This is called **Copy Elision**. C++17 made it mandatory in many cases.

```cpp
// Even without RVO, modern C++ uses MOVE semantics here
// → Move constructor (cheap) instead of copy constructor (expensive)
```

---

## 12. Preventing Implicit Copies — `explicit` Hint

```cpp
class Buffer {
public:
    explicit Buffer(const Buffer& other);    // explicit copy constructor (rare)
};

Buffer b1;
Buffer b2(b1);    // OK - explicit copy
Buffer b3 = b1;   // ERROR - implicit copy not allowed
```

Usually copy constructors are NOT marked explicit (you want copies to be easy). This is unusual.

---

## 13. Self-Assignment in Copy Constructor?

A copy constructor creates a NEW object. The new object can't be the source — they're different objects. So no self-check needed:

```cpp
Buffer(const Buffer& other) {
    // 'this' is a fresh, uninitialized object
    // 'other' is an existing different object
    // They can't be the same - no self-check needed
    data = new int[other.size];
    // ... copy ...
}
```

(Self-check IS needed in copy ASSIGNMENT, not copy CONSTRUCTOR.)

---

## 14. Copy Constructor for Derived Classes

```cpp
class Base {
    int x;
public:
    Base(const Base& other) : x(other.x) {}
};

class Derived : public Base {
    int y;
public:
    // Must explicitly call Base's copy constructor in init list
    Derived(const Derived& other)
        : Base(other),       // copy Base part
          y(other.y) {}      // copy Derived part
    // Forgetting Base(other) calls Base() default constructor - usually wrong!
};
```

---

## 15. Common Pitfalls

### Pitfall 1 - Forgetting copy constructor with pointer members
```cpp
class Owns {
    int* data;
public:
    Owns() : data(new int[100]) {}
    ~Owns() { delete[] data; }
    // Default copy = shallow = double delete = crash
};
```

**Fix**: write a deep copy constructor (Rule of Three).

### Pitfall 2 - Pass-by-value when you meant pass-by-reference
```cpp
void process(Car c) { ... }      // copies the car (expensive)
void process(const Car& c) { ... } // passes by reference (cheap)
```

### Pitfall 3 - Slicing
```cpp
class Base { int x; };
class Derived : public Base { int y; };

Derived d;
Base b = d;     // SLICING - only Base part of 'd' is copied
                // 'y' is lost - silent bug
```

**Fix**: use pointers or references for polymorphic types.

### Pitfall 4 - Throwing in copy constructor
```cpp
Buffer(const Buffer& other) {
    data = new int[size];     // might throw bad_alloc
    // If throws here, 'this' is partially constructed
    // Destructor will NOT be called
    // → potential resource leak if multiple resources
}
```

**Fix**: use RAII members (smart pointers, std::vector) that clean up automatically.

---

## 16. Complete Cheat Sheet

```
SIGNATURE:
  ClassName(const ClassName& other);

CALLED WHEN:
  - Direct init:    Type a(b);
  - Copy init:      Type a = b;
  - Pass by value:  func(a);
  - Return by value: return a;  (often elided)

NOT CALLED FOR:
  - Assignment:     a = b;       (calls operator=)
  - Move:           Type a = std::move(b);  (calls move ctor)

DEFAULT COMPILER VERSION:
  - Auto-generated if you don't write one
  - Member-wise copy
  - DANGEROUS for classes managing raw resources (pointers)

WHEN TO WRITE YOUR OWN:
  - Class manages raw pointers / file handles / resources
  - Need deep copy instead of shallow
  - Rule of Three: if you write ~Class(), also write copy ctor & copy assign

WHEN TO DISABLE (= delete):
  - Singletons
  - File handles / unique resources
  - RAII types that own non-copyable resources

PREFER:
  - Rule of Zero: use std::vector / std::unique_ptr to avoid writing these
  - Initializer lists for efficient member initialization
  - const Class& parameter (never Class - infinite recursion!)

GOLDEN RULES:
  1. Always make the parameter 'const Class&'
  2. Never pass by value to a copy constructor (recursion)
  3. If your class has 'new' anywhere - write deep copy or = delete
  4. Modern C++: use RAII, follow Rule of Zero
```
