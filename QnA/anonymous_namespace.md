# Anonymous (Unnamed) Namespace in C++

---

## 1. What It Is

A namespace **without a name** — and it has a special meaning:
**everything inside it is private to that `.cpp` file (translation unit).**

```cpp
namespace {
    void innerFunction() {
        return;
    }
}
```

```
You write:                          Compiler treats it as:
namespace {                         namespace __unique_random_id_for_this_file {
    void innerFunction();               void innerFunction();
}                                   }
                                    using namespace __unique_random_id_for_this_file;
```

So the compiler **invents a unique name** for it that no other file can possibly know. Result: the function exists in this file only.

---

## 2. The Problem It Solves — File-Private Scope

Without anonymous namespaces, here's what happens:

```cpp
// file_a.cpp
void helper() { /* version A */ }

// file_b.cpp
void helper() { /* version B */ }
// → LINKER ERROR: helper multiply defined (LNK2005)
```

**Three ways to fix this** — and only one is the modern best practice:

```cpp
// OPTION 1 — static (C-style, works but old-school)
static void helper() { /* version A */ }   // file-private

// OPTION 2 — anonymous namespace (modern C++ way)
namespace {
    void helper() { /* version A */ }      // file-private
}

// OPTION 3 — put in a named namespace and hope nobody clashes (bad)
namespace myFileStuff {
    void helper() { ... }
}
```

---

## 3. Internal vs External Linkage

```
External linkage  →  symbol visible to the LINKER from other .cpp files
Internal linkage  →  symbol exists ONLY in this .cpp file
                     (anonymous namespace and static give this)
```

```cpp
// file_a.cpp
void publicFunc() {}              // external linkage - visible everywhere

namespace {
    void privateFunc() {}         // internal linkage - file_a.cpp only
}

static int privateInt = 5;        // internal linkage - file_a.cpp only

// file_b.cpp
void publicFunc();                 // can declare and use it
void privateFunc();                // LINKER ERROR - not visible
extern int privateInt;             // LINKER ERROR - not visible
```

---

## 4. Why `namespace {}` is Preferred Over `static`

Both make functions file-local. But the anonymous namespace has **two important advantages**:

### Advantage 1 — Works for ANYTHING, Not Just Functions/Variables

```cpp
// static works for functions and variables
static void helper() {}      // OK
static int counter = 0;      // OK

static class Helper { };     // ERROR - cannot make a class static
static struct Config { };    // ERROR
static enum Color { };       // ERROR

// Anonymous namespace works for ALL of these
namespace {
    void helper() {}         // OK
    int counter = 0;         // OK
    class Helper { };        // OK - private class to this file
    struct Config { };       // OK - private struct
    enum Color { Red, Blue };// OK - private enum
    using IntPtr = int*;     // OK - private type alias
    template<typename T>     // OK - private template
    void process(T value) {}
}
```

### Advantage 2 — Better Type System Behavior

```cpp
// static functions: each one is independent
// Anonymous namespace: gets a consistent unique namespace identity
// (useful for template instantiations and ADL)
```

---

## 5. Real-World Use Cases

### Use Case 1 — Private Helper Functions in a `.cpp`

```cpp
// car.cpp
#include "car.h"

namespace {
    // Helper functions only the Car implementation needs.
    // Hidden from the rest of the program.

    float calculateFuelEfficiency(float distance, float fuel) {
        return distance / fuel;
    }

    bool isFuelLow(float fuel) {
        return fuel < 1.0f;
    }

    constexpr int MAX_PASSENGERS = 5;
}

void Car::drive(float distance) {
    if (isFuelLow(fuel)) {
        cout << "Fill fuel!" << endl;
        return;
    }
    float eff = calculateFuelEfficiency(distance, fuel);
    // ...
}
```

```
Benefits:
- Other .cpp files cannot accidentally call these helpers
- No linker name clashes if another file also has isFuelLow()
- Clear intent: "these belong only to this file's implementation"
```

### Use Case 2 — File-Local Constants

```cpp
// renderer.cpp
namespace {
    constexpr int   MAX_VERTICES   = 65536;
    constexpr float DEFAULT_FOV    = 60.0f;
    constexpr char  SHADER_PATH[]  = "shaders/default.glsl";
}

void Renderer::init() {
    fov = DEFAULT_FOV;
    // ...
}
```

### Use Case 3 — Implementation-Detail Classes (Pimpl Helpers)

```cpp
// database.cpp
namespace {
    // Internal connection pool - not exposed in database.h
    class ConnectionPool {
        vector<Connection> pool;
    public:
        Connection acquire() { /* ... */ }
        void release(Connection& c) { /* ... */ }
    };

    ConnectionPool g_pool;   // file-local global
}

void Database::query(string sql) {
    auto conn = g_pool.acquire();
    // ... use conn
    g_pool.release(conn);
}
```

### Use Case 4 — Lookup Tables / State Machines

```cpp
// parser.cpp
namespace {
    using StateHandler = void(*)(char);

    void handleStart(char c)   { /* ... */ }
    void handleString(char c)  { /* ... */ }
    void handleNumber(char c)  { /* ... */ }
    void handleComment(char c) { /* ... */ }

    StateHandler stateTable[] = {
        handleStart, handleString, handleNumber, handleComment
    };
}

void Parser::parse(const string& input) {
    for (char c : input) stateTable[currentState](c);
}
```

### Use Case 5 — Avoiding Symbol Collisions Across Libraries

```cpp
// libA/utils.cpp
namespace {
    int normalize(int x) { return x % 256; }   // libA's version
}

// libB/utils.cpp
namespace {
    int normalize(int x) { return abs(x); }    // libB's version
}

// Both libraries compile and link cleanly - no collision.
// Each normalize() lives in its own translation unit only.
```

---

## 6. Comparison Table — `static` vs Anonymous Namespace

| Feature                  | `static`                                | Anonymous Namespace |
|--------------------------|-----------------------------------------|---------------------|
| Functions                | Yes                                     | Yes                 |
| Variables                | Yes                                     | Yes                 |
| Classes / structs        | No                                      | Yes                 |
| Enums                    | No                                      | Yes                 |
| Type aliases             | No                                      | Yes                 |
| Templates                | No                                      | Yes                 |
| Recommended by Standard  | Deprecated for this use (C++03 era)     | Modern way          |
| Used in C                | Yes                                     | No (no namespaces)  |

---

## 7. Important Rules and Pitfalls

### Never Use in Header Files

```cpp
// helper.h - BAD
namespace {
    int counter = 0;
}

// If this header is included by 10 .cpp files,
// each file gets its OWN private 'counter' variable.
// You think you have ONE counter, but actually have 10.
// Silent bug - very hard to find!
```

```cpp
// Anonymous namespace belongs ONLY in .cpp files.
```

### Internal Linkage Means No External References

```cpp
// foo.cpp
namespace {
    void bar() {}
}

// other.cpp
extern void bar();   // won't find it - has internal linkage
```

### Each File's Anonymous Namespace is Unique

```cpp
// file_a.cpp
namespace { class Widget {}; }
void useA() { Widget w; }    // file_a's Widget

// file_b.cpp
namespace { class Widget {}; }
void useB() { Widget w; }    // file_b's Widget (DIFFERENT type!)

// These are completely unrelated types, even though same name.
```

---

## 8. Your Code — Analysis

```cpp
namespace {
    void innerFunction() {
        return;
    }
}
```

```
What this does:
- Creates innerFunction with internal linkage
- Only the .cpp file where this code appears can call innerFunction
- No other .cpp file can declare/call it
- No linker collision if another file also defines innerFunction
- Effectively a "private function" for this translation unit

When to use this pattern:
- Helper functions you don't want to expose in your .h file
- Implementation details that should stay hidden
- Avoiding pollution of the global namespace
```

---

## 9. Summary

```
ANONYMOUS NAMESPACE  =  "private to this .cpp file"

namespace { ... }   ->  internal linkage for everything inside
                       (compiler invents a unique hidden name)

PURPOSE:
  - Hide implementation details
  - Prevent linker name clashes across files
  - Modern C++ replacement for file-scope static

WORKS FOR:
  functions, variables, classes, structs, enums,
  type aliases, templates - EVERYTHING

DOES NOT WORK FOR:
  - Header files (creates duplicate copies in every includer)
  - Anything you want other .cpp files to access

GOLDEN RULE:
  If a helper is only used in ONE .cpp file -> put it in an
  anonymous namespace in that file. Keep your .h files clean.
```
