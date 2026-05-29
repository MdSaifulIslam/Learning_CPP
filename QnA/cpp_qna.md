# C++ Q&A

---

## 1. Why is `vector` undefined?

**Question:** Why is `vector` undefined in this code?
```cpp
using namespace std;
vector<int> v = { 1, 2, 3, 4, 5 };
```

**Answer:**
You're missing the `#include <vector>` header. `using namespace std;` only brings names from the `std` namespace into scope — it doesn't include the standard library headers themselves.

```cpp
#include <vector>   // required
using namespace std;

vector<int> v = { 1, 2, 3, 4, 5 };
```

Every standard library type needs its corresponding `#include`:
- `vector`  → `#include <vector>`
- `string`  → `#include <string>`
- `cout` / `cin` → `#include <iostream>`

---

## 2. How to format C++ code in Visual Studio?

**Keyboard Shortcuts**
- Format entire document: `Ctrl + K`, `Ctrl + D`
- Format selected code only: `Ctrl + K`, `Ctrl + F`

**Menu**
- `Edit` → `Advanced` → `Format Document` or `Format Selection`

**Auto-format on save**
- Go to `Tools` → `Options` → `Text Editor` → `C/C++` → `Code Style` → `Formatting`
- Enable **"Run ClangFormat on save"**

**Customize formatting rules**
- `Tools` → `Options` → `Text Editor` → `C/C++` → `Code Style` → `Formatting`
- Or add a `.clang-format` file to your project root

---

## 3. Why is `const` required before `string` in `pair<const string, int>&`?

**Question:** Why is `const` required before `string` in this code?
```cpp
for (pair<const string, int>& p : scores) {
    cout << p.first << " " << p.second << endl;
}
```

**Answer:**
Because `scores` is a `map<string, int>`, and `map` internally stores its elements as `pair<const Key, Value>` — the key is always `const` by design.

**Why does `map` make the key `const`?**
`map` keeps keys sorted in a specific order (balanced BST internally). If you could modify a key through a reference, it would corrupt the map's internal structure.

So `map<string, int>::value_type` is literally `pair<const string, int>`, not `pair<string, int>`.

**Without `const` — type mismatch:**
```cpp
// Type mismatch — map stores pair<const string, int>
for (pair<string, int>& p : scores) { ... }  // error or creates a copy
```

**Cleaner solution — use `auto`:**
```cpp
for (auto& p : scores) {
    cout << p.first << " " << p.second << endl;
}

// C++17 structured bindings
for (auto& [name, score] : scores) {
    cout << name << " " << score << endl;
}
```

---

## 4. How to check/search a string key in a `map`?

```cpp
map<string, int> scores = { {"alice", 95}, {"bob", 87} };
```

**1. Check if a key exists**
```cpp
if (scores.count("alice")) {
    cout << "alice exists" << endl;
}

// C++20
if (scores.contains("alice")) {
    cout << "alice exists" << endl;
}
```

**2. Check the value of a key**
```cpp
if (scores["alice"] == 95) {
    cout << "alice scored 95" << endl;
}
```

**3. Check key is const (during iteration)**
```cpp
for (auto& [name, score] : scores) {
    // name is const string& — read only
    cout << name << endl;   // ok
    // name = "charlie";    // compile error — const
}
```

**4. Safe lookup without inserting — use `find()`**
```cpp
// scores["xyz"] would INSERT "xyz" with value 0 if not found
auto it = scores.find("xyz");
if (it != scores.end()) {
    cout << it->second << endl;
}
```

---

## 5. Why is a semicolon required after the last `}`?

**Answer:**
A semicolon after a function's closing `}` is **NOT required** — it's just an empty statement that the compiler ignores.

```cpp
int squareMain(int x) {
    return x * x;
};   // unnecessary, but not an error
```

**Where semicolon IS required:**
```cpp
class MyClass { int x; };    // required
struct Point { int x, y; };  // required
enum Color { RED, GREEN };   // required
```

**Summary:**

| Construct | Semicolon needed? |
|-----------|------------------|
| `class` / `struct` | Yes |
| `enum` | Yes |
| Function definition | No (but allowed) |
| `if` / `for` / `while` | No |
| `namespace` | No |

It's a common habit from writing classes — cleaner to omit it from functions.

---

## 6. Why does `auto` with `vector<bool>` print `1 0` but is not recommended?

**Question:**
```cpp
vector<bool> v = { true, false, true };
auto val1 = v[0]; // not recommended
bool val2 = v[1];
cout << val1 << " " << val2 << endl;
```

**Answer:**
Output is correct (`1 0`) here, but the danger is hidden.

**`vector<bool>` is special:**
`vector<bool>` is a special template specialization that packs bits to save memory.
```cpp
vector<int>  → stores actual ints  (4 bytes each)
vector<bool> → stores bits         (1 bit each!)
```

So `v[0]` does NOT return a real `bool&` — it returns a **proxy object**:
```cpp
auto val1 = v[0];  // type = vector<bool>::reference (proxy!)
bool val2 = v[1];  // proxy is converted to real bool
```

**Why `auto` is dangerous:**
```cpp
vector<bool> v = { true, false, true };
auto val1 = v[0];   // proxy pointing INTO the vector

v.clear();          // vector destroyed!
cout << val1;       // UNDEFINED BEHAVIOR — proxy is dangling!
```

**Safe alternatives:**
```cpp
bool val1 = v[0];        // converts proxy to real bool
auto val1 = (bool)v[0];  // explicit cast
auto val1 = bool(v[0]);  // same
```

**Summary:**

| Code | Type | Safe? |
|------|------|-------|
| `auto val = v[0]` | `vector<bool>::reference` (proxy) | Dangerous |
| `bool val = v[0]` | `bool` (real value) | Safe |

> **Rule:** Never use `auto` with `vector<bool>` — always explicitly write `bool`.

---

## 7. How to see generated/mangled code in Visual Studio?

**1. View Assembly Code**
- Run in Debug mode → `Debug` → `Windows` → `Disassembly`
- Or press `Ctrl + Alt + D`

```asm
?squareMain@@YAHH@Z    ; int squareMain(int)
?print@@YAXH@Z         ; void print(int)
```

**2. Generate Assembly File (.asm)**
- `Project` → `Properties` → `C/C++` → `Output Files`
- Set **Assembler Output** → `Assembly With Source Code (/FAs)`
- Build → `.asm` file appears in output folder

**3. Use `dumpbin` (Command Line)**
```bash
dumpbin /SYMBOLS your_file.obj
```

**4. Undecorate/Demangle a name**
```bash
undname ?squareMain@@YAHH@Z
# output: int __cdecl squareMain(int)
```

**5. Preprocessor Output**
- `Project` → `Properties` → `C/C++` → `Preprocessor`
- Set **Preprocess to a File** → `Yes (/P)`
- Generates `.i` file with all macros expanded

**Name Mangling Example:**
```cpp
void print(int x)    → ?print@@YAXH@Z
void print(float x)  → ?print@@YAXM@Z
void print(double x) → ?print@@YAXN@Z
```
This is how **function overloading** works — each overload gets a unique mangled name.

---

## 8. Is there any mode needed for Disassembly in Visual Studio?

**Answer:**
No special mode needed — **Debug mode is enough**.

```
Top toolbar → change "Release" to "Debug"
```

| | Debug | Release |
|---|---|---|
| Mangled names visible | Yes | Sometimes stripped |
| Optimizations | Off | On (code may change) |
| Symbols (.pdb file) | Yes | Usually no |
| Best for inspection | Yes | No |

> Always use **Debug mode** when inspecting assembly — Release mode may inline, optimize, or remove functions entirely.

---

## 9. Disassembly window shows no effect on `Ctrl + Alt + D`?

**Answer:**
You need to **hit a breakpoint first** before `Ctrl + Alt + D` works.

**Steps:**
1. Click on the left margin next to any line in `main()` → red dot appears
2. Press `F5` to start debugging
3. Program pauses at breakpoint (yellow arrow appears)
4. Now press `Ctrl + Alt + D` → Assembly code appears

**Why it didn't work:**

| State | Disassembly works? |
|---|---|
| Program running normally | No |
| Program paused at breakpoint | Yes |
| Program not started | No |

> The debugger must be **paused at a breakpoint** for Disassembly to show anything.

---
