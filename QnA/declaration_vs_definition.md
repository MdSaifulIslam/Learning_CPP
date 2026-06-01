# Declaration vs Definition in C++ (with Static Members)

---

## 1. The Three Concepts

```
DECLARATION  ->  "this name and type exists somewhere"
                 (announcement / promise to the compiler)

DEFINITION   ->  "here is the actual thing - allocate memory for it"
                 (allocates storage / generates code)

ASSIGNMENT   ->  "store this value into an existing variable"
                 (modifies existing storage)
```

Most of the time **declaration and definition happen together** in one line:

```cpp
int a;          // BOTH declaration AND definition - memory reserved
a = 30;         // ASSIGNMENT - just updates value (memory already exists)
```

But for some things they must be SEPARATE — and that's where the confusion comes from.

---

## 2. The Static Member Case

```cpp
class Counter {
    static int count;     // DECLARATION only (line A)
};

int Counter::count = 0;   // DEFINITION (line B)
```

| Line | What it does | Memory? | Where it goes |
|---|---|---|---|
| A | Declaration | No | Inside the class (typically in header) |
| B | Definition | Yes | In exactly one `.cpp` file |

---

## 3. Why You Need the Type on the Definition

Every definition in C++ **must specify the type**. The type isn't borrowed from the declaration because the definition is syntactically a complete statement of its own.

```cpp
class Counter {
    static int count;     // declaration - announces type
};

int Counter::count = 0;   // definition - must repeat type
//^^^
// Why? Because this line IS where the variable is actually created.
// All variable creation requires the type at that point.
```

### Compare with normal globals (same pattern)
```cpp
// header.h
extern int globalScore;     // declaration only - no memory

// source.cpp
int globalScore = 0;        // definition - needs type
// Even though we declared above, the definition still needs 'int'
```

```
DECLARATION says:   "an int called globalScore EXISTS somewhere"
DEFINITION says:    "HERE is the int globalScore - allocate it now"

Each is a separate C++ statement with its own syntax rules.
Both require the type when written - the type is not "remembered".
```

---

## 4. Why the Static Member Can't Be Defined Inside the Class (Pre-C++17)

```cpp
// counter.h
class Counter {
    static int count = 0;   // ERROR pre-C++17: definition in header
};
```

```
If this header is included by main.cpp AND other.cpp:
  main.obj   gets a definition of Counter::count
  other.obj  gets a definition of Counter::count
  -> Linker sees TWO definitions -> LNK2005 error
```

```cpp
// Correct old-style way:
// counter.h
class Counter {
    static int count;       // declaration in header - all includers see this
};

// counter.cpp (ONLY ONE .cpp file)
int Counter::count = 0;     // definition - exactly one place
```

The C++ rule: **One Definition Rule (ODR)** — every entity must be defined in exactly one translation unit.

---

## 5. C++17 Solution — `inline static`

```cpp
class Counter {
    inline static int count = 0;     // OK in C++17 - declaration + definition
};
// No separate "int Counter::count = 0;" needed
```

```
The 'inline' keyword tells the linker:
  "Multiple translation units may define this.
   Merge them into one - no ODR violation."

Same purpose as 'inline' on functions defined in headers.
```

This is the modern way for new code.

---

## 6. All the Patterns Compared

```cpp
// 1. Local variable - declaration + definition together
void foo() {
    int a;          // declaration + definition (in one line)
    a = 30;         // assignment only
}

// 2. Global variable - declaration in header, definition in .cpp
// header.h
extern int globalX;           // declaration

// source.cpp
int globalX = 5;              // definition

// 3. Static class member - declaration in class, definition in .cpp
// header.h
class Counter {
    static int count;         // declaration
};

// source.cpp
int Counter::count = 0;       // definition

// 4. C++17 inline static - declaration + definition together
class Counter {
    inline static int count = 0;   // declaration + definition
};

// 5. constexpr static - implicitly inline since C++17
class Math {
    static constexpr double PI = 3.14159;   // C++17 - implicitly inline
};

// 6. const static int - special case (in-class init allowed since C++98)
class Buffer {
    static const int SIZE = 1024;    // in-class init OK for const int
};
// But still needed out-of-class if you take its address:
const int Buffer::SIZE;              // (may need definition)
```

---

## 7. Why `int a = 30;` Is "Declaration + Definition" but Looks Like Assignment

The `= 30` looks like assignment but it's not — it's **initialization** as part of the definition.

```cpp
int a;          // definition, default-initialized (garbage value for int)
int a = 30;     // definition with initializer (memory allocated AND set to 30)
a = 30;         // assignment - memory already exists, just update value
```

```
int a = 30;     <- one statement: defining 'a' AND giving initial value
a = 30;         <- different statement: 'a' must already exist
```

For static class members, the definition line works the same way:
```cpp
int Counter::count = 0;
//                  ^^
// This is INITIALIZATION (part of definition), not assignment
```

---

## 8. Why a Class Declaration Is Not Enough

```cpp
class Counter {
    static int count;     // declaration - "an int named count will exist"
};
```

This line:
- Reserves NO memory
- Just tells the compiler "this class has a static int member named count"
- Could be in a header included by 100 files - everyone sees the SAME declaration
- But there's still no actual variable in memory yet

For there to be a runtime variable, someone has to actually allocate the memory. That's what the definition does:

```cpp
int Counter::count = 0;
// "Now create the actual storage for Counter::count, initialize it to 0"
```

This must happen in **exactly one** translation unit (one .cpp file).

---

## 9. Memory Picture

```
Without out-of-class definition:
+----------------------------+
| Code Segment               |
|   Counter class info       |
|   "has static int count"   | <- just metadata, no actual variable
+----------------------------+
| Data Segment               |
|   [nothing for count]      | <- no memory yet!
+----------------------------+
-> LINKER ERROR when you try to use Counter::count


With out-of-class definition (int Counter::count = 0;):
+----------------------------+
| Code Segment               |
|   Counter class info       |
+----------------------------+
| Data Segment               |
|   Counter::count = 0       | <- actual memory exists!
+----------------------------+
-> All uses of Counter::count refer to this one location
```

---

## 10. Special Cases You Should Know

### Case 1: `const static int` — In-Class Init Allowed (Old Rule)
```cpp
class Buffer {
    static const int SIZE = 1024;    // OK since C++98
};
// Optional out-of-class definition needed if you take its address:
const int Buffer::SIZE;              // no initializer, just defines storage
```

### Case 2: `constexpr static` — Implicitly Inline Since C++17
```cpp
class Math {
    static constexpr double PI = 3.14159;   // C++17+: implicitly inline
};
// No out-of-class definition needed in C++17+
```

### Case 3: `inline static` (C++17+) — Universal Solution
```cpp
class Counter {
    inline static int count = 0;
    inline static string name = "default";
    inline static map<int, string> registry;
};
// All defined in-class, no separate definitions needed
```

### Case 4: Static Member of Class Type
```cpp
class Logger {
    static Config config;
};

// Out-of-class definition needed
Config Logger::config{"app.log"};   // calls Config constructor
```

---

## 11. Why C++ Was Designed This Way

```
The separation of declaration and definition exists because:

1. Headers are included by MANY .cpp files
   -> Declarations are SAFE to repeat (just announcements)
   -> Definitions are NOT (each one allocates memory)

2. Compilation is per .cpp file (translation unit)
   -> Compiler needs declarations to compile each file
   -> Linker combines the actual definitions at the end

3. ODR (One Definition Rule) ensures each entity has
   exactly ONE definition in the whole program

4. Static member declarations belong with the class structure
   (in the header so everyone sees the same interface)

5. Static member definitions belong in one .cpp file
   (so memory is allocated exactly once)
```

---

## 12. Summary

```
THREE OPERATIONS:
  Declaration  ->  introduce a name and type (no memory)
  Definition   ->  create the actual storage (memory + init)
  Assignment   ->  store a value into existing storage

NORMAL VARIABLE:
  int a;             <- declaration + definition combined
  a = 30;            <- assignment (memory already there)

STATIC CLASS MEMBER:
  class C { static int x; };    <- DECLARATION (in class)
  int C::x = 0;                 <- DEFINITION (in .cpp, needs type)

WHY THE TYPE IN DEFINITION:
  Every definition statement in C++ must specify the type.
  The definition is a fresh, complete declaration of its own.
  The class header's declaration is just an "advertisement";
  the actual variable creation needs its own complete declaration.

C++17 SHORTCUT:
  class C { inline static int x = 0; };  <- declaration + definition together
  No separate .cpp definition needed.

MENTAL MODEL:
  A static class member is a GLOBAL variable in the class's namespace.
  Like all globals, it needs:
    - A declaration where used (header)
    - A definition exactly once (one .cpp file)
  The definition needs the type because it CREATES the variable.
```
