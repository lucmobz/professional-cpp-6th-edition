# Professional C++ (6th Edition)

A lot of these comments assume C++20 or C++23 even

## References

* https://github.com/Professional-CPP/edition-6


## Generic Observations

* In the `main` function signature `argv[0]` can contain the name of the program or be empty (not granted by the standard)
* `print` and `println` are the efficient way to print to the console, they both format and tell the OS to display the output. For the format step `std::format` can be used
* Always use `enum class` and C++23 `std::to_underlying()` to get the underlying type already converted without a `static_cast`, `using enum MyEnum` avoids to have to scope the values of an `enum class` (useful in massive switch cases inside limited scopes)
* Putting `static` functions in a module and using `export` does not work (so modules are not really headers)
* Inside the scope of a switch statement `using enum MyEnum` avoids to have to scope an `enum class`
* When switching over an enumerations always list all enumerators instead of using a `default` case to force new enumerators to be handled explicitly
* Use the `[[nodiscard]]` attribute for functions returning error codes to force a warning if the error code is not checked
* Use `std::optional` to avoid functions that return a bool and fill a non-const reference as the output parameter (`std::nullopt` is the empty optional value). Use `has_value()` or test the optional like a pointer to see if there is a value. To get the value dereference the variable with `*` or use `value()`
* `std::string` is actually a type alias (with `using`) of `std::basic_string<char>` because it is very common
* When infering a pointer type always use `auto*`, this is clearer and gives compiler errors if there is a switch from value to reference semantic (think about iterating over a container of pointer that becomes a container of value-types)
le* Using copy-list initialization, `auto x = {1, 2}` makes x into `initializer_list<int>`, while using direct list initialization is an error `auto x{1, 2}` (nobody uses `initializer_list<int>` like that though)

## Strings

* When string literals are used to initialize an array `char str[]{"hello"}` they are not put in the read-only section of the program. There is just the code that initializes the array. In this case `const char* str{"hello"}` the literal is put in the read-only section of the program
* Raw string literals `R"(hello)"` treat escaped text as is (there is a way to use different delimiters)
* `std::string::compare` method is similar to `strcmp` that it returns 0 if the strings match (prefer `==` operator, or `<=>` operator for a three-way comparison)
* `c_str` returns a `const char*` always, while `data` returns a `char*` if called on a non-const `std::string` (since C++17)
* Use `std::string` literal notation `auto str{"hello"s}` for use with `auto`
* `inline namespace ns` makes all names available in the upper namespace

## Coding Style

* Names that have double underscores (`my__name`) and start with and underscore followed by a capital letter (`_Name`) are reserved by the standard library. Global names that starts with underscores are reserved (`_name`)
* In expressions it's UB (undefined behaviour) to reuse a variable that has side effects, `i++ + ++i`. Assigments, `a[i] = ++i`, are guaranteed to work since C++17. Avoid anyway

## Design Introduction

* Handle all possible system's errors (out of memory, invalid pointers, etc.), most user errors should be recoverable

## UML Appendix

* Inheritance (closed arrow) implements the is-a relationship
* Realization/implemention (dashed line with closed arrow) when a class implements an interface
* Aggregation (empty diamond, with multiplicities) implements the has-a relationship between classes, if the object aggregating other subobjects is destroyed, the subobjects are not (a `vector` of allocated pointers)
* Composition (full diamond) is the same as aggregation, but the lifetime of the subobjects is the same as the master object (a `vector` that holds objects by value, like an UI window with buttons)
* Association (simple line, with multiplicities) implements a bidirectional reference relationship between classes
* Dependency (dashed line, open arrow), when a class creates another class, so when a class appears in the methods of another class

## Design C++ Classes

* Has-a is preferred over is-a when the relationship is in doubt (think of the `map` and `multimap` example, where the multimap is a kind of map but could be implement better containing a map so that when inserting a new value, this is put in a collection that is then put into the map). Has-a is better because adding a base class behaviour impacts all derived classes that would need to override it. Inheritance adds more coupling than aggregation/composition. It is a code smell when inherting and some methods don't make much sense unless heavily overridden
* Liskov substitution principle (LSP) is the ability to substitute base classes with derived without altering the behaviour of the code
* Overriding should not be the default, unless a class is pure-virtual. It is a code smell when there is too much overriding
* Multiple inheritance is messy if there are functions from two base classes with the same name, or if two base classes themselves inherit from another common base (is this duplicated?), the diamond inheritance problem
* Mixin classes are classes used with inheritance to extend behaviour (the base classes implement some specific behaviour instead of a more general classification?). They are mixed in with normal classes to add to their behaviour

## Design for reuse

* Design by contract (regarding designing with safeguards) is based on the partition of responsibility, the main concept are preconditions (user responsible), postconditions and invariants (coder responsible). Example `std::vector` access operator grants access to elements provided the user has put enough element inside
* An alternative is to handle all safety cases (coder has all responsibility)
* Open/closed principle, design classes/components that are easy to extend (adding behaviour or properties) but hard to modify (should not have to change the implementations)
* Easy interfaces come from using C++ idioms, so constructors/destructors instead of initialize/finalize methods. Assignment to a new object instead of a reset method
* Dependency injection principle example where instead of having a global logger entity usable everywhere, it should be passed in as an argument of the constructor/inherited from to let a component use loggings
* ISP (interface segregation principle) is realized when a component uses another only through an interface that is limited in scope (components should not have huge interfaces, interfaces should be split/segregated and given to other components as needed)
* DIP (dependency inversion principle) is realized when high-level modules are independent of low level modules. For example when a high-level error logger interface is used by components, and a low-level specific implementation is injected when needed into those components (this dependency can be injected using the constructor). So that those components depend only on the high-level interface

## Memory Management

* Calling delete/free on a `nullptr` is valid (it does nothing)
* `malloc` does not call the constructor `new`/`new[]` do. `free` does not call the destructor (`delete` does, `delete[]` does on each element)
* In most cases it is fine to not recover from an out-of-memory exception thrown by `new`. Use `new(nothrow)` to just return a `nullptr` in case of failure
* When using `new int`/`new int[N]` with POD, the return memory is uninitialized. With classes the default constructor is called. To be sure use the `{}` initialization
* `delete`/`delete[]` will not call destructors recursively on pointers obviously
* If `int arr[2][3]` then `decltype(arr[0])` is a reference type instead of `int[3]` as one could expect
* When using the array version of `new[]`, only the first dimension can be dynamic, as the others are used for a well-defined type `new[n][3][4]`. `new[n][m][4]` will not compile. Dynamically allocated multidimensional array are obtainable with arrays of pointers (but in this case flat arrays are just better)
* When declaring functions arrays decay to pointers `void func(int arr[2])`, the 2 is ignored. `void func(int (&arr)[2])` by taking a reference works only on arrays of size 2