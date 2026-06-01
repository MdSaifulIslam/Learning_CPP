# `static` Functions in C++ — Complete Guide

The `static` keyword on a function means **different things** depending on where it appears:

| Context | What `static` Does |
|---|---|
| Inside a class | Function belongs to class, not instance (no `this`) |
| File scope (.cpp) | Internal linkage - file-private |
| Inside a function | (Applied to a variable - persists between calls) |

---

## 1. Static Member Function

A static member function belongs to the **class itself**, not to any individual object.

```cpp
class Counter {
    static int count;          // static member variable

public:
    static void increment() {   // static member function
        count++;
    }

    static int getCount() {
        return count;
    }
};

int Counter::count = 0;   // MUST be defined outside the class (one place only)

int main() {
    Counter::increment();
    Counter::increment();
    Counter::increment();
    cout << Counter::getCount();   // 3
}
```

### Key Properties
- No `this` pointer (no current object)
- Cannot access non-static members or call non-static methods
- Can access other static members
- Called via class name (`Counter::increment()`) or instance (`c.increment()`)
- Lives in code segment like a free function

---

## 2. Why No `this`?

A static function isn't tied to any specific object — there's nothing to point to:

```cpp
class Car {
    int speed;                  // each Car has its own speed
    static int totalCars;       // shared across all Cars

    void show() {                // non-static
        cout << this->speed;    // OK - 'this' points to specific car
    }

    static void showTotal() {    // static
        cout << this->speed;    // ERROR - no 'this' available
        cout << totalCars;       // OK - class-level data
    }
};
```

### Memory model

```
Each Car instance:        Class-level (shared):
+---------------+         +---------------+
| Car c1:       |         | totalCars     | <- one copy for ALL Cars
|  speed = 5    |         +---------------+
+---------------+
| Car c2:       |
|  speed = 8    |
+---------------+
| Car c3:       |
|  speed = 10   |
+---------------+

Non-static fn  -> operates on ONE specific instance (needs 'this')
Static fn      -> operates only on shared class-level data
```

---

## 3. Calling a Static Member Function

```cpp
class Math {
public:
    static int square(int x) { return x * x; }
};

// Both ways work:
int a = Math::square(5);    // via class name (preferred - clearer)

Math m;
int b = m.square(5);        // via instance (legal but misleading)
```

**Best practice**: Always use `ClassName::function()` to make it clear it's static.

---

## 4. Common Use Cases

### Use 1 — Factory Methods
```cpp
class Connection {
    string url;
    Connection(string u) : url(u) {}    // private constructor

public:
    // Static factory - controlled object creation
    static Connection createHttp(string host) {
        return Connection("http://" + host);
    }

    static Connection createHttps(string host) {
        return Connection("https://" + host);
    }
};

auto c1 = Connection::createHttp("example.com");
auto c2 = Connection::createHttps("secure.com");
// Cannot do: Connection c("..."); - constructor is private
```

### Use 2 — Utility/Helper Functions
```cpp
class StringUtils {
public:
    static string toUpper(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }

    static string trim(const string& s) {
        // ... trim implementation ...
    }

    static vector<string> split(const string& s, char delim) {
        // ... split implementation ...
    }
};

// Use without instance - utility namespace-style
auto upper = StringUtils::toUpper("hello");
auto parts = StringUtils::split("a,b,c", ',');
```

### Use 3 — Class-Level Counters
```cpp
class Widget {
    static int totalCount;
    int id;

public:
    Widget() {
        id = totalCount++;
    }

    static int howMany() { return totalCount; }
    int getId() const { return id; }
};
int Widget::totalCount = 0;

Widget w1, w2, w3;
cout << Widget::howMany();    // 3
cout << w1.getId();            // 0
cout << w2.getId();            // 1
cout << w3.getId();            // 2
```

### Use 4 — Singleton Pattern
```cpp
class Logger {
    Logger() {}                          // private constructor
    Logger(const Logger&) = delete;      // no copying

public:
    static Logger& getInstance() {
        static Logger instance;          // created once on first call
        return instance;
    }

    void log(const string& msg) {
        cout << "[LOG] " << msg << endl;
    }
};

Logger::getInstance().log("Application started");
Logger::getInstance().log("Processing...");
// Same Logger instance every time
```

### Use 5 — Callbacks for C APIs
```cpp
class Window {
    static void onKeyPress(int key) {     // matches C function pointer signature
        cout << "Key pressed: " << key;
    }

public:
    void init() {
        // C API expects a plain function pointer - static fits!
        glfwSetKeyCallback(handle, onKeyPress);
    }
};
```

---

## 5. Restrictions on Static Member Functions

### Cannot access non-static members
```cpp
class Car {
    int speed;              // non-static
    static int totalCars;   // static

    static void show() {
        cout << speed;       // ERROR - which car?
        cout << totalCars;   // OK
    }
};
```

### Cannot be `virtual`
```cpp
class Base {
    static virtual void foo();   // ERROR - no virtual + static
};
```

Why? Virtual dispatch requires `this` pointer to look up the vtable. Static has no `this`.

### Cannot be `const`
```cpp
class Car {
    static void show() const;   // ERROR - const modifies 'this', no this
};
```

### Cannot be called on null pointer (well, technically can - UB anyway)
```cpp
Car* c = nullptr;
c->show();   // technically works for static (since no 'this' deref)
             // but UNDEFINED BEHAVIOR per standard - don't do it
Car::show(); // CORRECT way
```

---

## 6. Static Free Function (File-Private)

When applied to a function outside any class, `static` gives it **internal linkage**:

```cpp
// file_a.cpp
static int helper(int x) {        // internal linkage
    return x * 2;
}

void publicFunc() {
    int y = helper(10);            // OK - same file
}

// file_b.cpp
extern int helper(int);            // ERROR - helper not visible
// Each file's static functions are completely independent
```

### Why Use File-Static?
```cpp
// Without static - two files defining the same name = LINKER ERROR
// file_a.cpp
int normalize(int x) { return x % 256; }

// file_b.cpp
int normalize(int x) { return abs(x); }
// -> LNK2005: 'normalize' already defined
```

```cpp
// With static - each is file-private, no collision
// file_a.cpp
static int normalize(int x) { return x % 256; }

// file_b.cpp
static int normalize(int x) { return abs(x); }   // independent
```

### Modern C++ Alternative
```cpp
// Prefer anonymous namespace for file-private functions
namespace {
    int helper(int x) { return x * 2; }   // file-private
}
```

Anonymous namespace works for classes, types, templates too — not just functions/variables.

---

## 7. Static Local Variables (Bonus)

Inside any function (member or free), a static local variable persists between calls:

```cpp
void counter() {
    static int count = 0;    // initialized ONCE, lives until program ends
    count++;
    cout << count << endl;
}

counter();  // 1
counter();  // 2
counter();  // 3
// Each call increments the same persistent variable
```

```cpp
// Useful for caching/memoization
int fibonacci(int n) {
    static map<int, int> cache;
    if (cache.count(n)) return cache[n];

    if (n < 2) return n;
    int result = fibonacci(n-1) + fibonacci(n-2);
    cache[n] = result;
    return result;
}

// First call: O(2^n). Subsequent calls: O(1) thanks to cache.
```

```cpp
// Singleton trick (Meyers Singleton)
Logger& getLogger() {
    static Logger instance;   // thread-safe initialization (C++11+)
    return instance;
}
```

### Static Local Initialization
```cpp
void foo() {
    static int x = expensiveComputation();   // runs ONCE on first call
    cout << x;
}

foo();   // initializes x, prints value
foo();   // skips initialization, prints same value
foo();   // skips initialization, prints same value
```

---

## 8. Differences Summary

| Feature | Regular Member Fn | Static Member Fn | Static Free Fn |
|---|---|---|---|
| Has `this` pointer | Yes | **No** | N/A |
| Access non-static members | Yes | **No** | N/A |
| Access static members | Yes | Yes | N/A |
| Called via object | Yes | Yes (legal but unusual) | N/A |
| Called via class name | No | **Yes** (preferred) | N/A |
| Can be `virtual` | Yes | **No** | N/A |
| Can be `const` | Yes | **No** | N/A |
| Linkage | external | external | **internal** |
| Modern alternative | - | - | anonymous namespace |

---

## 9. Static vs Non-Static — When to Use Which

```
USE STATIC MEMBER FUNCTION when:
  - The operation doesn't need any object state
  - Factory methods (creating objects)
  - Utility functions related to the class
  - Singleton access
  - Counting class-level statistics
  - C callback adapters

USE NON-STATIC MEMBER FUNCTION when:
  - The operation works on a specific object's data
  - Reading or modifying instance state
  - Polymorphic behavior (virtual functions need this)
  - Most "normal" methods

USE STATIC FREE FUNCTION (or anonymous namespace) when:
  - Helper used only within one .cpp file
  - Want to prevent linker name collisions
  - Implementation details that shouldn't be exposed
```

---

## 10. Pitfalls and Gotchas

### Pitfall 1 - Forgetting to define static member variables
```cpp
class Counter {
    static int count;          // declaration only
public:
    static void inc() { count++; }
};
// Forgot: int Counter::count = 0;
// LINKER ERROR: undefined reference to Counter::count
```

**Fix in C++17+:**
```cpp
class Counter {
    inline static int count = 0;    // inline static - no out-of-class def needed
};
```

### Pitfall 2 - Static initialization order fiasco
```cpp
// file_a.cpp
extern int b;
int a = b + 1;     // depends on b

// file_b.cpp
extern int a;
int b = a + 1;     // depends on a

// Initialization order across files is UNDEFINED
// One of them initializes with garbage - bug!
```

**Fix**: Use static local + function (Meyers singleton):
```cpp
int& getA() { static int a = ...; return a; }
int& getB() { static int b = ...; return b; }
// Initialization happens on first call, in dependency order
```

### Pitfall 3 - Thinking static fn modifies the object
```cpp
class Car {
    int speed;
public:
    static void accelerate() {
        speed++;   // ERROR - which car's speed?
    }
};
```

**Fix**: Either remove static (and use `this`), or make speed static (shared).

### Pitfall 4 - Mistaking file-static for class-static
```cpp
// In some_file.cpp - this is FILE-static, not class-static
static int globalCount = 0;

class Counter {
public:
    void increment() {
        globalCount++;     // works, but...
    }
};
// Other files don't see globalCount.
// If you want class-shared, use static member of the class instead.
```

---

## 11. Summary

```
STATIC MEMBER FUNCTION:
  - Belongs to the class, not instances
  - No 'this' pointer
  - Cannot access non-static members
  - Called via Class::fn() (or obj.fn(), but unusual)
  - Uses: factories, utilities, counters, singletons, C callbacks

STATIC FREE FUNCTION:
  - Internal linkage (file-private)
  - Prevents linker collisions across files
  - Modern alternative: anonymous namespace

STATIC LOCAL VARIABLE (bonus):
  - Persists between function calls
  - Initialized once on first call
  - Useful for caching, Meyers Singleton

KEY MENTAL MODEL:
  Static = "belongs to the class/file/program itself, not to an instance"
  No 'this', no instance, only class-level or file-level scope

GOLDEN RULES:
  1. Use Class:: prefix when calling static member functions
  2. Use static member fn when no instance data is needed
  3. Prefer anonymous namespace over file-static in modern C++
  4. Initialize static member variables outside the class (or use inline static in C++17+)
  5. Watch out for static initialization order across translation units
```
