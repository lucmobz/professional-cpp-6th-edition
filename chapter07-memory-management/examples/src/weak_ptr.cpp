import std;

// Used later as example of cyclic dependency that would never call destructors
struct Cyclic2;

struct Cyclic1 {
  ~Cyclic1() { std::println("{}", __func__); }
  std::shared_ptr<Cyclic2> other;
};

struct Cyclic2 {
  ~Cyclic2() { std::println("{}", __func__); }
  std::shared_ptr<Cyclic1> other;
};

// Used later as example of breaking cyclic dependencies
struct NonCyclic2;

struct NonCyclic1 {
  ~NonCyclic1() { std::println("{}", __func__); }
  std::weak_ptr<NonCyclic2> other;
};

struct NonCyclic2 {
  ~NonCyclic2() { std::println("{}", __func__); }
  std::shared_ptr<NonCyclic1> other;
};

auto main() -> int {
  {
    auto ptr{std::make_shared<int>(42)};
    // std::weak_ptr is a non-owning pointer that points to a std::shared_ptr
    // resource, it is used to break cyclic references that would never call
    // delete
    std::weak_ptr<int> weak{
        ptr};  // only takes std::shared_ptr or another std::weak_ptr

    // This if-declaration trick is in C++98 by the way, in C++17 there is
    // another option for a different test condition
    if (auto shared{weak.lock()}) {
      // The reference counter is non-zero
      std::println("{}", *shared);
    }

    // Constructing a std::shared_ptr can throw
    try {
      std::shared_ptr<int> otherShared{weak};
    } catch (const std::bad_weak_ptr& e) {
      std::println("{}", e.what());
    }
  }

  // Case of cyclic dependency (leak)
  {
    auto cyclic1{std::make_shared<Cyclic1>()};
    auto cyclic2{std::make_shared<Cyclic2>()};
    // Reference counters go up due to copy
    cyclic1->other = cyclic2;
    cyclic2->other = cyclic1;
    // Destructors never called!
  }

  // Case of breaking cyclic dependency (non-leak, one class does not own)
  {
    auto nonCyclic1{std::make_shared<NonCyclic1>()};
    auto nonCyclic2{std::make_shared<NonCyclic2>()};
    // Reference counters go up due to copy
    nonCyclic1->other = nonCyclic2;
    nonCyclic2->other = nonCyclic1;
    // Destructors never called!
  }

  // There are problems when a std::weak_ptr is pointing to a std::shared_ptr
  // allocated with std::make_shared (single allocation block case), to keep
  // alive the reference counter for the std::weak_ptr, also the data memory is
  // not deallocated
}