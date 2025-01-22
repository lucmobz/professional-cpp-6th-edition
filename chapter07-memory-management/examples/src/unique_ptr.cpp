import std;

#include <cassert>

// Used at the end
void deallocateFunc(int* ptr) {
  delete ptr;
  ptr = nullptr;
}

auto main() -> int {
  // std::unique_ptr grants unique ownership
  std::unique_ptr<int> ptr1{new int{42}};

  // Using auto is better, value-initialization is used (POD zero-initialized,
  // objects default-initialized)
  auto ptr2{std::make_unique<int>()};

  // Default initialization (POD uninitialized, objects default-initialized), no
  // wasted initialzation
  auto ptr3{std::make_unique_for_overwrite<int>()};
  *ptr3 = 42;

  // The template parameter is required (there is no CTAD, class template
  // argument deduction)
  // std::unique_ptr ptr4{new int{42}};  // Compiler error

  // At destruction/reset the resource is freed (example of RAII)
  ptr2.reset(nullptr);

  // This protects against thrown exceptions (because execution is immediately
  // halted)
  {
    struct Thrower {
      ~Thrower() { std::println("{}", __func__); }
      void throwException() { throw std::exception{}; }
    };

    auto* leaky{new Thrower{}};

    try {
      // It's hard to know if functions throw exceptions!
      leaky->throwException();
      // This is never executed because the program flow goes to the catch
      // statement
      delete leaky;
    } catch (const std::exception& e) {
    }

    auto nonLeaky{std::make_unique<Thrower>()};
    try {
      nonLeaky->throwException();
      // Destructor will be called
    } catch (const std::exception& e) {
    }
  }

  // Before C++17 there was no order for expressions given as function
  // arguments, after there was
  {
    struct Thrower {
      Thrower() { throw std::exception{}; }
    };

    struct NoThrower {};

    auto func = [](std::unique_ptr<Thrower> a, std::unique_ptr<NoThrower> b) {};

    try {
      // This could have leaked if the new NoThrower{} happens before the
      // exception is thrown (there are 4 operations roughly)
      func(std::unique_ptr<Thrower>{new Thrower{}},
           std::unique_ptr<NoThrower>{new NoThrower{}});
      // Could fix this in C++14 or less with std::make_unique(), which is a
      // single operation instead of two (the new and the std::unique_ptr
      // construction)
    } catch (const std::exception& e) {
    }
  }

  {
    auto leaky{std::make_unique<int>(42)};
    // This is a leak
    auto* nonLeaky{leaky.release()};
    assert(leaky == nullptr);
    // Not if we remember to keep the pointer and delete it
    delete nonLeaky;
    // Good practice to set this back to nullptr
    nonLeaky = nullptr;
  }

  {
    // Non-copyable type, but movable!
    auto ptr1{std::make_unique<int>(42)};
    // auto ptr2{ptr1}; // Compiler error
    //  This is nullptr
    std::unique_ptr<int> ptr3{};
    // ptr3 = ptr1; // Compiler error

    ptr3 = std::move(ptr1);
    // Also good practice
    ptr1 = nullptr;
  }

  {
    auto ptr1{std::make_unique<int>(42)};
    // For smart pointers the array notation is not valid
    // ptr1[0]; // Compiler error

    // This creates a smart pointer to an array, with array notation enabled
    auto ptr2{std::make_unique<int[]>(3)};
    ptr2[0] = ptr2[1] = ptr2[2] = 42;

    // This is not working, as in function arguments the 3 is ignored
    // auto ptr2{std::make_unique<int[3]>()}; // Compiler error
    // using ArrayType = int[3];
    // auto ptr3{std::make_unique<ArrayType>()}; // Compiler error

    // Just use a std::vector instead
  }

  // The reason there is no CTAD is because of custom deleters, by default
  // new/delete (new[]/delete[]) are used
  {
    // Since the whole point of std::make_unique is to call new and emplace the
    // arguments, custom deleters require user defined deallocations (and
    // allocations in some sense)
    auto allocate{[]() {
      std::println("allocating");
      return new int{42};
    }};

    auto deallocate{[](auto* ptr) {
      std::println("deallocating");
      delete ptr;
      ptr = nullptr;
    }};

    // Custom deleter is copied as a data member
    std::unique_ptr<int, decltype(deallocate)> ptr{allocate(), deallocate};

    // If using a function it is required to use decltype(&deallocateFunc)
    // because it stores a pointer
    // std::unique_ptr<int, decltype(deallocateFunc)*> ptr{allocate(),
    // deallocateFunc};
  }
}