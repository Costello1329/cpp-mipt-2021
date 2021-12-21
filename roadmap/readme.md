# Course roadmap


## Block 1: Basics of C++ 03 and C++07

### General informations:
- What is C++
- C++ versions, other related languages
- What is program
- Program structure:
    - Alphabet of the language
    - Main function
- Types of errors in C++:
    - Compilation error (`CE`):
        - Lexical error
        - Syntax error
        - Semantic error
    - Runtime errors (`RE`)
    - Undefined behaviour (`UB`)

### Declarations & Definitions:
- Fundamental types
- Identifiers
- Literals
- Variable definition, declaration point
- Implicit type conversions
- Visibility scope and variable lifetime
- Signed and usigned integer variables
- Functions:
    - Declaration vs definition
    - One definition rule
    - Passing arguments and getting the result from functions
    - Recursion
    - `void` type
    - `return` keyword
- `const` qualifier:
    - Variables
    - Rule: everything that can be const __must__ be const
- ASCII table

### Expressions:
- Operators:
    - Assignment operator, concept of lvalue and rvalue in C ++ 03
    - Arythmetical operators
    - Сompound assignment operators
    - Increment and decrement operators
    - Comparison operators
    - Logical operators
    - Operator sizeof
    - Bitwise operators, storing integer types in memory
    - ternary operator
    - C-style case
    - Scope resolution operator
    - Function call operator
    - Comma operator
    - Operator precedence and associativity
    - Function call operator
    - Cast operators: `static_cast`, `reinterpret_cast`, `const_cast`, `dynamic_cast`

### Control sequences:
- If, else if, else
- Loops: for, while, do while
- Switch/case
- Continue
- Continue

### Arrays and pointers:
- Arrays
- `operator []`
- Initializing arrays using initializer list
- Declaration point of array
- What happens at the physycal level with stack memory:
    - When defining variables
    - When defining arrays
    - Stack (in memory):
        - Grows from top to bottom
        - Size restrictions
- Address in memory
- Unary `operator &`
- Pointers, how to create them
- `Operator *`
- Implementation of `operator []` through `operator *` when working with arrays
- `const` qualified pointers: `const pointer` VS `pointer to const` VS `const pointer to const`
- Operations with pointers pointer arythmetics
- Dynamic memory
    - Operators `new`, `new []`, `delete`, `delete []`
    - Memory leak, double deallocation problem
- Passing arguments by value vs by pointer

### References:
- The swap function implementation on pointers
- The concept of reference
- The assignment dilemma: **to create a reference when assigning** or **to copy an object**, difference of approaches in **Python**, **Java**, **Javascript** and **C ++**
- Passing aruments inside the function by references
- Swap function implementation on references
- Common mistake: returning a reference to a local object from a function (why this is bad)
- `const` qualified references

## Block 2: Introduction to OOP

**Classes and structures**
- Structures: motivation (example: `coordinates`), other examples (examples: `std::vector`, `std::cin`, `std::cout`, `std::string`)
- Member-fields (variables)
- Methods, `static` methods, `const` methods
- Object (aka instance of struct) VS struct itself.
- Keyword `this`
- Constructors:
    - Default
    - Copy constructor
    - Shadowing, solution to the problem:
        - Renaming
        - Using keyword `this`
        - Initializer list (also the solution to the problem of initializing constants and references)
    - Rules for default generation of constructors by the compiler
    - The default and delete keywords (also for methods)
    - The `explicit` keyword
    - Delegating constructors
- Destructors.
- `const` qualified member fields and references as member fields, problem with initilizing them (problem: default constructor is deleted if const field is uninitilized)
    - solution 1: `default initialization`
    - solution 2: Constructor initializer list
- `static` member (motivation and example)
- Encapsulation
- Sections: `private` & `public`
- `class` vs `struct`
- Passing objects by const reference (how and why)
- Allocating instances on heap, array of instances
- Operators `.` and `->`, details
- Getters (returning `const` reference vs `non-const`) and setters
- Differently qualified methods (example: method `std::vector::at`)
- Operator overloading:
    - Assignment operator, it's signature and common implementation. Rule of three.
    - The idea of overloading operators
    - Operator overloading using the classes `vector` (3D math vector, not `std::vector` analogue) and `array` (`std::array` analogue) as an example:
        - Arithmetic operators.
            - The problem with the correctness of expressions like `x + y = z;`.
            - The problem in the case when the left operand is not a class object (expressions like `5 + x`).
        - Compound assignments, correct signatures
        - Overloading logical operators.
        - Overloading bitwise operators, including overloading operators << and >> using stream I / O as an example.
        - Comparison operators overloading.
    - Overloading of the `operator[]`: `const` and `non-const` versions.
    - Overloading of C-style cast operator. Another use for the `explicit` keyword.
    - Overloading the `operator()`. Why is it n-ary? What's the signature? The concept of the functor.
- `using namespace std::` (and why it is bad), solution: `using std::...`
- Using built-in classes: `std::vector`, `std::array`, `std::string`, type `size_t`.
- `enums`, using `switch/case` on enums
- Anti-patterns: `friend keyword`, `mutable keyword`
- Using operator `sizeof` on classes and structures
- Operator `alignof`
- Specifier `alignas`
- Pointers to functions
- Pointers to members

**Templates**
- Functions specialization
- What are templates (motivation):
    - Template classes and functions, exampels
- Template specializations:
    - The principle: `particular is preferable to general`.
    - Partial and full specializations
    - The principle is `the exact match is better`
    - Function specialization vs template function specialization
    - Compiler selection rules for specialization and overloading candidates 
- Template parameters that are not types (example: `std::array`). Template template parameters
- `typedef` keyword
- `using` keyword
    - template `using`
    - in-class `using`
    - in-scope `using`

<!--
**Exceptions:**
- General idea:
    - Motivation for using exceptions.
    - The throw statement and the try ... catch construct.
    - Examples of standard operators that throw exceptions.
- Difference between exceptions and runtime errors. Errors that are not exceptions and exceptions that are not errors.
- Rules for catching and re-throwing exceptions, casting types when catching exceptions. Catching all exceptions. The rules for choosing a catch block by the compiler in the case when different blocks are suitable.
- Copying when throwing and catching exceptions. Features of catching exceptions by value and by reference.
- Old-style exception specifications and their problems, unexpected exceptions. C ++ 11 style exception specifications, noexcept operator and specifier. Conditional noexcept.
- Exceptions in constructors and the problem of memory leaks on exceptions.
- Exceptions in destructors.
- Security guarantees for exceptions: basic and strict.

**Inheritance**
- Inheritance declaration:
    - Protected access modifier.
    - Difference between private, public and protected inheritance.
    - Difference between class inheritance and structs.
    - Final keyword
- Finding names when inheriting:
    - Hiding names of the base class methods.
    - Explicit call of the parent methods of the inheritor (Using ::).
    - The order in which constructors and destructors are called in inheritance. The problem with the initialization of the parents when defining the constructor of the inheritor, again using the initializer lists.
    - Multiple inheritance, ambiguity with it, diamond inheritance problem. Examples of disambiguation using type conversions and the operator::.
- Typecasting between parent and child:
    - Trimming when copying, casting pointers, casting references.
    - Dynamic_cast operator (unlike static_cast)
- Virtual functions, their general idea and difference from non-virtual ones:
    - Features of allocation of classes with virtual functions in memory
    - Virtual inheritance.
    - Concept of the virtual function table
    - Virtual destructor and its purpose
- The concept of dynamic polymorphism, polymorphic classes
- Placement in memory of classes
- Abstract classes:
    - Pure virtual functions, their features.
    - Pure virtual destructor (and why it causes the linker error).
    - Override keyword.
    - `Final` keyword (for methods)
-->

