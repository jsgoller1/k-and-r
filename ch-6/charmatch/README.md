charmatch
---

### Problem Statement
Exercise 6-2. Write a program that reads a C program and prints in
alphabetical order each group of variable names that are identical in the
first 6 characters, but different somewhere thereafter. Don't count words
within strings and comments. Make 6 a parameter that can be set from the
command line.

### Strategy
The hardest part of this problem will be identifying the variable names in the program. To do this, we will use a finite state machine that keeps track of whether we are 1) in a part of the program where a valid var may occur, and 2) whether the specific token parsed is a variable or not.

In C, variable names always follow type names:
* `int x;`
* `int x, y;`
* `int x = 0, y = 0`
* `struct foo x;`

However, types can occur in places that do _not_ count as variable declarations:
* function delcarations / definitions
  * `int cleanup() {...}`
  * `int foobar(int x);`
* struct members and struct names
  * `struct foo { int x; int y;}`
* After `typedef`
  * `typedef int x`
  * `typedef struct foo bar;`
* Preprocessor macros
  * `#define integer int`
* Legitimate declarations using two type or more names:
  * `unsigned int x`
  * `signed long long x`

Additionally, preprocessor macros present a particularly tricky case:
```
#define INT int
#define integer INT
integer x;
```

**Step 1 - Determine if we should parse tokens**
We will read in each non-whitespace token of the input program with `getword()` from `common/`. To figure out if we are in a part of the program where tokens can count as variable names, we can use a big-but-necessary FSM to cover all necessary states, possibly delegating some cases to a sub-FSM (particularly for handling `struct`). Comments and string literals can be handled by keeping track of characters parsed, and causing token analysis to be paused until a closing `"`, `*/`, or newline is encountered.

**Step 2 - Determine if the parsed token is a type name**
We will keep two tables of type names - one for default C types (`int`, `char`, `short`, etc), and one for new names defined with `typedef` or `#define` - the second array can be resized with `realloc`. Once we determine that a token should be checked, we will compare the token to C type names, storing the following variable name if a match occurs.

**Step 3 - Store variable that match together**
Once we are certain the token is a variable, we will store it in a table of vars. The table will store string structs with pointers to the var name, and to other entries that share the same n characters. When parsing is complete, we will print each linked list of var names separately.

### Caveats / constraints
* `charmatch` does not work on invalid C programs.
* Cases I have ignored:
  * Same-line declaration / definition with complex C expressions:
    * `int c = 1 + 2 + result_of_foo();`
  * `struct` variables.
  * Variables with compound type names, e.g. `unsigned int` or `signed char`.
  * Parameters in function declarations are not treated as variables ONLY IF there is no whitespace between the function name and "(". This sucks but I (as of now) make no claims of skill with parsing / lexing.
