# `this` and `*this` in C++

---

## 1. What `this` Is

Inside every non-static member function, the compiler secretly passes a hidden pointer to the current object called `this`.

```cpp
class Car {
    int speed;
public:
    void show() {
        // What you write:
        cout << speed;

        // What the compiler actually does:
        cout << this->speed;
    }
};
```

```
this    -> Car*   (pointer to the current Car object)
*this   -> Car&   (the current Car object itself, dereferenced)
&(*this) -> Car*  (same as this)
```

---

## 2. The Three Equivalent Ways to Access Members

```cpp
class Car {
    int speed;
public:
    void show() {
        speed;          // shorthand - compiler adds this->
        this->speed;    // explicit using pointer
        (*this).speed;  // explicit using dereferenced object
    }
};
```

All three produce identical code. The shorthand is most common; the explicit forms are used when needed for clarity or disambiguation.

---

## 3. Why Parentheses `(*this)`?

Operator precedence — without parens, `*` and `.` would parse incorrectly:

```cpp
*this.member      // WRONG - parses as *(this.member) due to precedence
(*this).member    // CORRECT - dereference first, then access member
this->member      // CORRECT - shorthand for the above
```

```
(*this).member    is identical to    this->member
```

The `->` operator was invented as a shortcut specifically to avoid writing `(*ptr).` everywhere.

---

## 4. The Hidden `this` Parameter

Member functions are NOT magic — they're regular functions that take a hidden first parameter:

```cpp
// What you write:
class Car {
    int speed;
public:
    void accelerate() {
        speed++;
    }
};

// What the compiler generates (conceptually):
void Car_accelerate(Car* this) {
    this->speed++;
}

// Calling:
Car c;
c.accelerate();
// becomes:
Car_accelerate(&c);
```

### For `const` member functions:
```cpp
void Dashboard() const { ... }
// becomes:
void Dashboard(const Car* this) { ... }
//              ^^^^^^^^^
// 'this' becomes const Car* - cannot modify members
```

---

## 5. The 4 Most Common Uses of `*this`

### USE 1 — Method Chaining (Most Important)

Return `*this` by reference so methods can be chained:

```cpp
class Builder {
    string result;
public:
    Builder& add(const string& s) {
        result += s;
        return *this;       // <- return current object by reference
    }
    Builder& separator(char c) {
        result += c;
        return *this;
    }
    string build() { return result; }
};

string s = Builder()
            .add("Hello")
            .separator(' ')
            .add("World")
            .build();
// "Hello World"
```

**Why this enables chaining:**
- Each method returns `Builder&` (a reference to the same object)
- The next method call applies to that returned object (the same one)
- The chain continues through any number of calls

**Without `return *this`:**
```cpp
Builder& add(...) { ... }    // returns void
b.add("a").add("b");          // ERROR - can't call .add() on void
```

### USE 2 — Self-Assignment Check in `operator=`

```cpp
class Array {
    int* data;
    int size;
public:
    Array& operator=(const Array& other) {
        // Self-assignment check - compare addresses
        if (this == &other) return *this;
        //  ^^^^    ^^^^^^
        //  this = my address
        //  &other = the other object's address
        //  if same -> assigning to myself -> skip the work

        delete[] data;
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];

        return *this;
    }
};

Array a;
a = a;   // self-assignment - the check prevents bugs
```

**Why this matters:**
- Without the check, `delete[] data` would destroy the data you're trying to copy
- Then `new int[size]` would allocate fresh memory
- The copy loop would read from FREED memory (undefined behavior)

### USE 3 — Passing the Current Object to a Free Function

```cpp
void serializeCar(const Car& c);    // free function

class Car {
    int speed;
public:
    void save() {
        serializeCar(*this);    // <- pass myself as parameter
        //           ^^^^^
        // *this gives the actual Car object to pass by reference
    }
};
```

```cpp
// Real example - registering with an observer
class EventBus {
public:
    void registerListener(Listener& l);
};

class MyWidget : public Listener {
    EventBus& bus;
public:
    void start() {
        bus.registerListener(*this);   // register myself with the bus
    }
};
```

### USE 4 — Returning the Object from Operators

By convention, mutation operators return `*this`:

```cpp
class Vec {
    int x, y;
public:
    Vec& operator+=(const Vec& v) {
        x += v.x;
        y += v.y;
        return *this;       // enables chaining like a += b += c;
    }

    Vec& operator-=(const Vec& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vec& operator*=(int scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
};

Vec a, b, c;
a += b += c;             // chain works because += returns *this
(a += b) *= 2;           // also works
```

---

## 6. Why `this` is a Pointer (Not a Reference)

```cpp
// You might wonder: why "this->speed" and not "this.speed"?
// Why is it a POINTER and not a REFERENCE?

// Historical reason:
// 'this' was added to C++ BEFORE references existed in the language.
// By the time references were added, changing 'this' would have broken everything.
// So 'this' stayed as a pointer for backward compatibility.
```

```
*this   -> the object  (Car&)
this    -> a pointer   (Car*)
this->  -> access via pointer
.        -> access via object
```

---

## 7. The Famous Stream Example

```cpp
cout << "Hello" << " " << "World" << endl;
//   ↑       ↑       ↑           ↑
//   |       |       |           |
//   Each << returns the stream by reference (return *this)
//   so the NEXT << can apply to it

// The implementation looks like:
class ostream {
public:
    ostream& operator<<(const string& s) {
        // ... write s ...
        return *this;     // return THIS stream so chain continues
    }
    ostream& operator<<(int n) {
        // ... write n ...
        return *this;
    }
    // etc.
};
```

```
cout << "Hello" << " " << "World";
                ↑
   First <<:  cout.operator<<("Hello") returns cout (by ref)
                                ↑
   Second <<: cout.operator<<(" ")    returns cout (by ref)
                                            ↑
   Third <<:  cout.operator<<("World") returns cout
```

This is THE quintessential method-chaining example in C++.

---

## 8. `*this` Returned by Value vs by Reference

```cpp
// BY REFERENCE - chain operates on the SAME object
Builder& add(...) { return *this; }
// Caller chains:    b.add().add().add();   // all on same b

// BY VALUE - each call returns a COPY (rare, usually a bug)
Builder add(...) { return *this; }
// Caller chains:    b.add().add().add();   // each call on a different copy!
// Original b never gets the changes!
```

**Almost always use `return *this;` with the return type `ClassName&` (reference).**

---

## 9. `*this` with `const` Member Functions

```cpp
class Car {
    int speed;
public:
    // Non-const version - can return non-const ref
    Car& accelerate() {
        speed++;
        return *this;       // type of *this is Car&
    }

    // Const version - must return const ref
    const Car& show() const {
        cout << speed;
        return *this;       // type of *this is const Car& (because of const fn)
    }
};

Car c;
c.accelerate().accelerate();    // OK

const Car cc;
cc.show().show();               // OK - const Car&.show() is allowed
// cc.accelerate();             // ERROR - non-const fn on const object
```

---

## 10. Pitfalls

### Pitfall 1 - Returning `*this` by value loses chaining benefits
```cpp
Builder add(...) { return *this; }   // BY VALUE - bug!
b.add("x").add("y");                  // .add("y") modifies a TEMP copy, lost!
```

### Pitfall 2 - Capturing `this` in a lambda (lifetime issues)
```cpp
class Widget {
    int data;
public:
    auto getCallback() {
        return [this]() { cout << data; };
        //      ^^^^^
        // Captures 'this' pointer - if Widget is destroyed,
        // the lambda has a dangling pointer!
    }
};

// Modern alternative (C++17): [*this] copies the whole object
auto getCallback() {
    return [*this]() { cout << data; };   // safer - lambda owns a copy
}
```

### Pitfall 3 - Comparing `this == &other` is for SELF-CHECK only
```cpp
// In operator=
if (this == &other) return *this;   // self-assignment check - CORRECT

// Not for equality testing
if (this == &otherObj) {            // tests if SAME object (same address)
    // NOT testing if objects are equal!
}
```

---

## 11. Member Function vs Free Function — The `this` Difference

```cpp
// Member function - has hidden 'this'
class Car {
public:
    void show() {                // implicit this parameter
        cout << speed;            // = this->speed
    }
};

// Free function - no 'this', must pass object explicitly
void showCar(const Car& c) {     // c is the "this" here, explicit
    cout << c.speed;
}

Car c;
c.show();        // 'this' is implicit
showCar(c);     // 'this' equivalent (c) is explicit
```

---

## 12. Summary

```
this    -> Pointer to current object (Car*)
*this   -> The current object itself (Car&)
this->  -> Shorthand for (*this).

THE 4 MAIN USES OF *this:
  1. Method chaining     ->  return *this; (return Class&)
  2. Self-assignment     ->  if (this == &other) return *this;
  3. Pass to free fn     ->  freeFunc(*this);
  4. Operator overload   ->  return *this; in +=, -=, etc.

KEY FACTS:
  - this is a pointer (historical, predates references)
  - this is implicit in every non-static member function
  - this is const in a const member function (const Car*)
  - You cannot reassign 'this' (it's like a const pointer)
  - this is NULL only in undefined behavior (calling member fn on null ptr)

METHOD CHAINING PURPOSE:
  - Eliminate repetitive code (no need to retype object name)
  - Enable fluent / builder-style APIs
  - Allow cascading expressions (cout <<, +=, etc.)
  - Make code read like a recipe (top-to-bottom)

GOLDEN RULE:
  When designing setters or mutators, return *this by REFERENCE
  to enable chaining and make your API fluent.
```
