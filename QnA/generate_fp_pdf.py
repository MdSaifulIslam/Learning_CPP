"""
Generate Function Pointers PDF from the explanation.
"""
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import inch, cm
from reportlab.lib.colors import HexColor, black, white
from reportlab.lib.enums import TA_LEFT, TA_CENTER, TA_JUSTIFY
from reportlab.platypus import (
    SimpleDocTemplate, Paragraph, Spacer, PageBreak,
    Table, TableStyle, Preformatted, KeepTogether
)

OUTPUT = r"C:\Users\islam\Documents\Programming\c&c++\QnA\Function_Pointers_Cpp.pdf"

# ---------- Styles ----------
styles = getSampleStyleSheet()

title_style = ParagraphStyle(
    'TitleStyle', parent=styles['Title'],
    fontName='Helvetica-Bold', fontSize=24, textColor=HexColor('#1a1a2e'),
    spaceAfter=12, alignment=TA_CENTER
)

subtitle_style = ParagraphStyle(
    'Subtitle', parent=styles['Normal'],
    fontName='Helvetica-Oblique', fontSize=12, textColor=HexColor('#555555'),
    spaceAfter=24, alignment=TA_CENTER
)

h1_style = ParagraphStyle(
    'H1', parent=styles['Heading1'],
    fontName='Helvetica-Bold', fontSize=17, textColor=HexColor('#0b3d91'),
    spaceBefore=18, spaceAfter=10, borderPadding=4,
    borderColor=HexColor('#0b3d91'), borderWidth=0,
    leftIndent=0
)

h2_style = ParagraphStyle(
    'H2', parent=styles['Heading2'],
    fontName='Helvetica-Bold', fontSize=13, textColor=HexColor('#1a5490'),
    spaceBefore=12, spaceAfter=6
)

body_style = ParagraphStyle(
    'Body', parent=styles['Normal'],
    fontName='Helvetica', fontSize=10.5, textColor=HexColor('#202020'),
    leading=15, spaceAfter=8, alignment=TA_JUSTIFY
)

bullet_style = ParagraphStyle(
    'Bullet', parent=body_style,
    leftIndent=18, bulletIndent=6, spaceAfter=4
)

code_style = ParagraphStyle(
    'Code', parent=styles['Code'],
    fontName='Courier', fontSize=9, textColor=HexColor('#1a1a1a'),
    backColor=HexColor('#f4f4f4'), leading=12,
    leftIndent=8, rightIndent=8, spaceBefore=4, spaceAfter=10,
    borderColor=HexColor('#d0d0d0'), borderWidth=0.5, borderPadding=6
)

note_style = ParagraphStyle(
    'Note', parent=body_style,
    fontName='Helvetica-Oblique', textColor=HexColor('#0b3d91'),
    leftIndent=12, borderColor=HexColor('#0b3d91'), borderWidth=0,
    backColor=HexColor('#eef3fb'), borderPadding=8, spaceAfter=12
)


def p(text, style=body_style):
    return Paragraph(text, style)


def code(text):
    # Escape XML-special chars for Preformatted-as-paragraph
    return Preformatted(text, code_style)


def heading(text, level=1):
    return Paragraph(text, h1_style if level == 1 else h2_style)


def note(text):
    return Paragraph(f"<b>Note:</b> {text}", note_style)


# ---------- Build story ----------
story = []

# Title
story.append(p("Function Pointers in C++", title_style))
story.append(p("A Complete Guide from Every Angle", subtitle_style))

# Intro
story.append(p(
    "A function pointer is just like a variable pointer &mdash; but instead of pointing to "
    "<b>data</b>, it points to the <b>code (machine instructions)</b> of a function. "
    "Once you grasp this single idea, all of callbacks, dispatch tables, plug-in systems, "
    "and event handling fall into place."
))

# Section 1
story.append(heading("1. The Core Concept"))
story.append(p("Compare a data pointer with a function pointer side by side:"))
story.append(code("""int x = 5;
int* p = &x;                       // points to data in memory

void Print(int, char);
void (*fp)(int,char) = Print;      // points to FUNCTION CODE in memory"""))

story.append(p("Memory layout:"))
story.append(code("""Memory:
+------------------------------+
|  Code Segment                |
|   +---------------------+    |
|   |  Print function     | @ 0x401234  <- address of the function
|   |   for loop ...      |              (where its machine code lives)
|   |   cout << ch ...    |
|   +---------------------+    |
+------------------------------+
|  Stack                       |
|   fp = 0x401234              |  <- function pointer holds that address
+------------------------------+"""))

# Section 2
story.append(heading("2. Why They Exist &mdash; The Real Need"))
story.append(p(
    "A regular function call is <b>hardcoded at compile time</b>. The compiler bakes in "
    "<i>CALL 0x401234</i>. A function pointer call is <b>resolved at runtime</b> &mdash; "
    "whatever address the pointer holds right now gets called."
))
story.append(p("This unlocks:"))
for item in [
    "<b>Callbacks</b> &mdash; pass a function to be called later",
    "<b>Customization</b> &mdash; different behavior without changing code",
    "<b>Plug-in systems</b> &mdash; load and call functions discovered at runtime",
    "<b>Tables of choices</b> &mdash; dispatch tables, state machines",
    "<b>Event handlers</b> &mdash; 'when X happens, call this function'",
]:
    story.append(Paragraph(f"&bull; {item}", bullet_style))

# Section 3
story.append(heading("3. The Syntax &mdash; How to Read It"))
story.append(code("""void (*printPtr)(int, char) = Print;
//   ^    ^       ^
//   |    |       +-- parameters the function takes
//   |    +-- pointer name (and the * makes it a pointer)
//   +-- return type"""))

story.append(p("Read it in this order:"))
story.append(code("""   void   (*printPtr)   (int, char)
    A          A             A
    |          |             |
    +-- 3 -----+             |
               |             |
               +-- 1 --------+
                             |
                             +-- 2

1. printPtr is a POINTER       (innermost)
2. ... to a function taking (int, char)
3. ... returning void"""))

story.append(p("Practice reading these:"))
story.append(code("""int  (*fp)(int)               // fp: pointer to function(int) returning int
char (*fp)(int, int)          // fp: pointer to function(int,int) returning char
void (*fp)()                  // fp: pointer to function() returning void
double (*fp)(double, double)  // fp: pointer to function(double,double) returning double"""))

story.append(note(
    "The parentheses around <font face='Courier'>(*fp)</font> are <b>mandatory</b>. "
    "Without them, the <font face='Courier'>*</font> binds to the return type and the "
    "declaration becomes a <i>function returning a pointer</i> instead of "
    "<i>a pointer to a function</i>."
))
story.append(code("""void (*fp)(int);    // POINTER to function taking int, returning void
void  *fp(int);     // DIFFERENT - function taking int, returning void*"""))

story.append(PageBreak())

# Section 4
story.append(heading("4. Your Code &mdash; Line by Line"))
story.append(code("""void functionPointer()
{
    atexit(endMessage);                          // line 19
    Print(10, '#');                              // line 20
    void (*printPtr)(int, char) = Print;         // line 21
    (*printPtr) (12, '+');                       // line 22
    printPtr(10, 'S');                           // line 23
    cout << "\\nEnd message is: " << endl;       // line 25
}"""))

story.append(heading("Line 19 &mdash; atexit(endMessage)", 2))
story.append(p(
    "This is a real-world function-pointer use. You pass the function <b>itself</b> "
    "(its address) &mdash; <b>not</b> its result. Note the absence of parentheses after "
    "<font face='Courier'>endMessage</font>; adding them would call it now."
))
story.append(code("""atexit(endMessage);
//      ^
// Passing the FUNCTION ITSELF (its address) - not calling it
//
// atexit's signature:  int atexit(void (*func)())
// It stores the pointer; at program exit, registered functions run (LIFO order)

Print     -> the function (its address) - a pointer value
Print()   -> CALL the function - get a result"""))

story.append(heading("Line 20 &mdash; Print(10, '#')", 2))
story.append(p("A regular, direct, hardcoded call. The compiler emits a CALL to Print's address."))

story.append(heading("Line 21 &mdash; Create the pointer", 2))
story.append(code("""void (*printPtr)(int, char) = Print;
//                            ^
// "Print" without () means the ADDRESS of Print.
// You could also write:  = &Print  (both are equivalent for functions)

void (*p1)(int,char) = Print;    // implicit address-of
void (*p2)(int,char) = &Print;   // explicit address-of
// Both store the same address - same machine code location."""))

story.append(heading("Line 22 &mdash; Classic dereference call", 2))
story.append(code("""(*printPtr)(12, '+');
// Treats printPtr like a regular pointer:
//   *printPtr -> the function it points to
//   then ()    -> call it"""))

story.append(heading("Line 23 &mdash; Modern direct call", 2))
story.append(code("""printPtr(10, 'S');
// Function pointers can be called DIRECTLY - no need for *
// The compiler auto-dereferences."""))

story.append(p("All four of these are valid and do the same thing:"))
story.append(code("""Print(10, '#');          // direct call
(*Print)(10, '#');       // dereference call (Print decays to pointer)
printPtr(10, '#');       // call through pointer (modern)
(*printPtr)(10, '#');    // call through pointer (classic)"""))

# Section 5
story.append(heading("5. Why Both Calling Forms Work"))
story.append(p(
    "Functions in C/C++ are special: a function <b>name</b> auto-converts to its "
    "<b>address</b>, and a function <b>pointer</b> auto-converts back when called."
))
story.append(code("""Print          = address
&Print         = address
*Print         = function (auto re-decays to pointer)
**Print        = same (decays again)
***Print       = same - you can keep going forever!

Print()        = call
(*Print)()     = call
(**Print)()    = call
(***Print)()   = call

This is a quirk of C - functions are NOT true first-class values."""))

story.append(PageBreak())

# Section 6
story.append(heading("6. Cleaner Syntax &mdash; typedef and using"))
story.append(p("The raw syntax is ugly. Use type aliases to make code readable:"))
story.append(code("""// Hard to read
void (*printPtr)(int, char) = Print;
void (*signal(int, void (*)(int)))(int);   // real signal() signature

// typedef (old style)
typedef void (*PrintFunc)(int, char);
PrintFunc printPtr = Print;

// using (modern, C++11) - same meaning, easier to read
using PrintFunc = void(*)(int, char);
PrintFunc printPtr = Print;"""))

story.append(code("""// Use PrintFunc anywhere - like any type:
PrintFunc fp = Print;
void callTwice(PrintFunc fn) {     // pass as parameter - clean!
    fn(5, '*');
    fn(3, '!');
}"""))

# Section 7
story.append(heading("7. Function Pointers as Parameters &mdash; Callbacks"))
story.append(p("This is the #1 real-world use of function pointers."))
story.append(code("""// A function that takes another function as input
void doTwice(void (*action)(int)) {
    action(1);
    action(2);
}

void print(int x)  { cout << "print: " << x << endl; }
void square(int x) { cout << "square: " << x*x << endl; }

int main() {
    doTwice(print);   // -> print: 1   print: 2
    doTwice(square);  // -> square: 1  square: 4
    // SAME doTwice, DIFFERENT behavior based on what you pass
}"""))

story.append(p("STL algorithms use this pattern everywhere:"))
story.append(code("""#include <algorithm>

bool descending(int a, int b) { return a > b; }
bool ascending (int a, int b) { return a < b; }

vector<int> v = {3, 1, 4, 1, 5, 9};
sort(v.begin(), v.end(), descending);  // pass function pointer
sort(v.begin(), v.end(), ascending);   // different sort by passing different fn"""))

# Section 8
story.append(heading("8. Arrays of Function Pointers &mdash; Dispatch Tables"))
story.append(code("""// Calculator with operation table
double add (double a, double b) { return a + b; }
double sub (double a, double b) { return a - b; }
double mul (double a, double b) { return a * b; }
double divv(double a, double b) { return a / b; }

// Array of function pointers
double (*ops[4])(double, double) = { add, sub, mul, divv };
// Cleaner with using:
// using Op = double(*)(double, double);
// Op ops[4] = { add, sub, mul, divv };

int main() {
    cout << ops[0](10, 3);   // add -> 13
    cout << ops[1](10, 3);   // sub -> 7
    cout << ops[2](10, 3);   // mul -> 30
    cout << ops[3](10, 3);   // div -> 3.33

    int choice = 2;
    cout << ops[choice](5, 5);   // -> 25 (mul)
    // No if/switch chain - pure data-driven dispatch.
}"""))

story.append(PageBreak())

# Section 9
story.append(heading("9. Function Pointer as Return Type"))
story.append(code("""// Function that RETURNS a function pointer
// Raw syntax - extremely ugly:
int (*getOperation(char op))(int, int) {
    if (op == '+') return add;
    if (op == '-') return sub;
    return nullptr;
}

// Same thing with using - readable:
using IntOp = int(*)(int, int);
IntOp getOperation(char op) {
    if (op == '+') return add;
    if (op == '-') return sub;
    return nullptr;
}

int main() {
    auto fn = getOperation('+');
    cout << fn(3, 4);   // 7
}"""))

# Section 10 - Comparison table
story.append(heading("10. Function Pointers vs Modern C++ Alternatives"))

comparison_data = [
    ["Feature",          "Function Pointer", "std::function",  "Lambda"],
    ["Syntax",           "void(*fp)(int)",   "function<void(int)>", "[](int x){...}"],
    ["Captures vars?",   "No",               "Yes",            "Yes"],
    ["Type-safe?",       "Limited",          "Yes",            "Yes"],
    ["Performance",      "Fastest",          "Slower (heap maybe)", "Often inlined"],
    ["Class members?",   "Special syntax",   "Yes",            "Yes"],
    ["Header needed",    "none",             "<functional>",   "none"],
    ["C compatibility",  "Yes",              "No (C++ only)",  "No (C++ only)"],
]

t = Table(comparison_data, colWidths=[3.5*cm, 4.0*cm, 4.5*cm, 4.0*cm])
t.setStyle(TableStyle([
    ('BACKGROUND', (0, 0), (-1, 0), HexColor('#0b3d91')),
    ('TEXTCOLOR',  (0, 0), (-1, 0), white),
    ('FONTNAME',   (0, 0), (-1, 0), 'Helvetica-Bold'),
    ('FONTSIZE',   (0, 0), (-1, -1), 9),
    ('ALIGN',      (0, 0), (-1, -1), 'LEFT'),
    ('VALIGN',     (0, 0), (-1, -1), 'MIDDLE'),
    ('GRID',       (0, 0), (-1, -1), 0.4, HexColor('#888888')),
    ('ROWBACKGROUNDS', (0, 1), (-1, -1), [white, HexColor('#f4f4f4')]),
    ('FONTNAME',   (0, 1), (-1, -1), 'Helvetica'),
    ('TOPPADDING', (0, 0), (-1, -1), 5),
    ('BOTTOMPADDING', (0, 0), (-1, -1), 5),
]))
story.append(t)
story.append(Spacer(1, 12))

story.append(p("Same task &mdash; three ways:"))
story.append(code("""// 1. Function pointer (old style, fastest, C compatible)
void (*fp)(int, char) = Print;
fp(5, '*');

// 2. std::function (most flexible, can hold ANY callable)
#include <functional>
std::function<void(int, char)> sf = Print;
sf(5, '*');

// 3. Lambda (modern, can capture context)
auto lam = [](int n, char c) {
    for (int i = 0; i < n; i++) cout << c;
};
lam(5, '*');"""))

# Section 11
story.append(heading("11. Class Member Function Pointers &mdash; A Different Beast"))
story.append(code("""class Car {
public:
    void honk()  { cout << "Beep!"; }
    void brake() { cout << "Stop!"; }
};

// Special syntax - note the ClassName::
void (Car::*memFp)() = &Car::honk;
//     ^       ^           ^
//     class   member ptr  MUST use &Class::method (no auto-decay!)

Car c;
(c.*memFp)();     // call through object  - note: .*
                  // prints: Beep!

Car* pc = &c;
(pc->*memFp)();   // call through pointer - note: ->*
                  // prints: Beep!"""))

story.append(note(
    "Member function pointers are <b>not</b> the same as regular function pointers. "
    "They need their own special syntax with <font face='Courier'>.*</font> and "
    "<font face='Courier'>-&gt;*</font>."
))

story.append(PageBreak())

# Section 12
story.append(heading("12. Common Real-World Uses"))
story.append(code("""// 1. atexit - your example
atexit(cleanup);    // call cleanup when program ends

// 2. qsort - C-style sort
int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }
qsort(arr, n, sizeof(int), cmp);

// 3. signal handlers - OS signals
signal(SIGINT, [](int s){ cout << "Ctrl+C pressed!"; });

// 4. Event callbacks - GUI/game frameworks
button.onClick(handleClick);
window.onClose(saveData);

// 5. Thread function entry point
pthread_create(&t, nullptr, threadFunc, args);

// 6. Plugin systems - function loaded at runtime
auto fn = (void(*)())dlsym(handle, "plugin_init");

// 7. State machines
using StateFn = void(*)();
StateFn currentState = idleState;
currentState();   // dispatches to current state's handler"""))

# Section 13
story.append(heading("13. Complete Cheat Sheet"))
story.append(code("""DECLARATION:
  return_type (*name)(params) = function;
  void (*fp)(int, char) = Print;

ASSIGNMENT:
  fp = Print;       implicit address
  fp = &Print;      explicit address - same result

CALLING (both work):
  fp(args);         modern, clean
  (*fp)(args);      classic, explicit dereference

CLEAN ALIAS:
  using FnType = void(*)(int, char);
  FnType fp = Print;

AS PARAMETER (callback):
  void run(void (*cb)(int)) { cb(5); }

ARRAY OF FUNCTION POINTERS:
  void (*table[4])(int) = { fnA, fnB, fnC, fnD };
  table[i](42);

KEY RULES:
  - Function name without () = address
  - () around (*name) is MANDATORY
  - Signatures must match EXACTLY (return + params + qualifiers)
  - Can't bind to member functions (need Class::* syntax)
  - Cannot capture variables (use lambda/std::function instead)"""))

# Output of user's program
story.append(heading("Output of YOUR Program"))
story.append(code("""##########               <- Print(10, '#')
++++++++++++             <- (*printPtr)(12, '+')
SSSSSSSSSS               <- printPtr(10, 'S')

End message is:
Ending the program       <- atexit fired endMessage on program exit"""))

# Closing note
story.append(Spacer(1, 8))
story.append(Paragraph(
    "<b>The big picture:</b> A function pointer turns a function from a hardcoded "
    "jump-target into a <b>value</b> you can store, pass, and choose at runtime. "
    "This single concept underlies callbacks, event systems, plug-ins, dispatch tables, "
    "and the entire <font face='Courier'>&lt;algorithm&gt;</font> library. Modern C++ adds "
    "<font face='Courier'>std::function</font> and lambdas as more powerful alternatives "
    "&mdash; but function pointers remain the lightest, fastest, and most C-compatible "
    "way to refer to 'a piece of code I want to call later.'",
    note_style
))

# Build
doc = SimpleDocTemplate(
    OUTPUT, pagesize=A4,
    leftMargin=2*cm, rightMargin=2*cm,
    topMargin=2*cm, bottomMargin=2*cm,
    title="Function Pointers in C++",
    author="QnA Notes"
)
doc.build(story)
print(f"PDF created: {OUTPUT}")
