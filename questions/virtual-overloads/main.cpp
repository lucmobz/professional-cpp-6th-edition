// * Question: can you have both virtual and non-virtual overloads in a base
// class? What happens when a derived class overrides/hides one of them?

import std;

class Base {
 public:
  virtual void foo() const { std::println("base empty"); }
  void foo(int value) const { std::println("base {}", value); }
};

class Derived : public Base {
 public:
  // using Base::foo; // This is all or nothing
  void foo() const override { std::println("derived empty"); }
};

auto main() -> int {
  Base base;
  Derived derived;
  Base& disguised{derived};

  base.foo();
  base.foo(42);

  derived.foo();
  // derived.foo(42);  // Error: not available

  disguised.foo();
  disguised.foo(42);
}

// * Answer: yes, there is no problem as they can be considered different
// functions, however both overriding and hiding forbid access to other base
// overloads. `using Base::foo` can bring them all in similarly as with
// constructors