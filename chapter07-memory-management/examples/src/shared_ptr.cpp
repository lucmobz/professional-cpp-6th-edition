import std;

#include <cstdio>

auto main() -> int {
  {
    // Same as std::unique_ptr (but copyable), it uses two allocations, one for
    // the data, one for the reference counter
    std::shared_ptr<int> ptr1{new int{42}};

    // Better with auto and std::make_shared, a single allocation is used
    auto ptr2{std::make_shared<int>(42)};
  }

  {
    auto* ptr1{new int{42}};
    std::shared_ptr<int> ptr2{ptr1};

    // Beware of creating std::shared_ptr from the same raw pointer (there will
    // be multiple reference counters!)
    // std::shared_ptr<int> ptr3{ptr1}; // Runtime error

    std::println("{}", ptr2.use_count());

    // delete will be called twice!
  }

  {
    // No need to specify the type of the custom deleter for a std::shared_ptr
    // as the deleter is not a template parameter
    auto deleter{[](auto* ptr) {
      delete ptr;
      ptr = nullptr;
    }};

    std::shared_ptr<int> ptr1{new int{42}, deleter};
  }

  {
    // std::shared_ptr custom deleters can be used to implement RAII for some
    // resource (can also be done with unique_ptr to be fair, or in-scope
    // structs with destructors without allocation of the reference counter)
    std::FILE* file{std::fopen("", "w")};
    std::shared_ptr<std::FILE> ptr1{file, [](auto* file) {
                                      if (file) std::fclose(file);
                                    }};

    int value{42};
    auto deleter{[](auto* ptr) { std::println("noop"); }};
    std::unique_ptr<int, decltype(deleter)> ptr2{&value, deleter};
  }

  {
    // Keep in mind that passing std::shared_ptr by value increases the
    // reference counter and is therefore slower, in general std::shared_ptr is
    // an anti-pattern
    std::shared_ptr<int> ptr{new int{42}};

    auto func{[](auto ptr) {}};
    // Reference counter increases
    func(ptr);
    // Reference counter decreases, the function does not need to mess with
    // ownership, use get (without template magic though)
    func(ptr.get());
  }

  // Polymorphism should work with smart pointers!

  {
    // std::shared_ptr is copyable and so it can be casted (a new pointer is
    // created and return)

    std::shared_ptr<const int> constPtr{new int{42}};
    auto ptr{std::const_pointer_cast<int>(constPtr)};
    // What will be the use count though? It will be increased as the resource
    // has a new pointer
    std::println("{}", constPtr.use_count());
    std::println("{}", ptr.use_count());
  }

  // std::shared_ptr supports aliasing (the get returned pointer is different
  // than the owned pointer)
  {
    auto ptr{std::make_shared<int>(new int{42})};
    // This pointer shares the reference counter but points to well, invalid
    // memory in this case
    std::shared_ptr<int> aliasedPtr{ptr, ptr.get() + 1};
    auto observingPtr{aliasedPtr.get()};
    // This could be UB, not sure, but logically it should be 42
    std::println("{}", observingPtr[-1]);

    // The stored pointer (get returned) could be pointing to a member of a
    // class
  }
}