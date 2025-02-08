import std;

// struct Horrible {
//   auto asShared() { return std::make_shared<Horrible>(this); }
// };

// This class can only be instanced through a std::shared_ptr if one uses
// asShared (storing in a std::shared_ptr before using asShared works)
struct Weird : std::enable_shared_from_this<Weird> {
  auto asShared() { return shared_from_this(); }
  // This returns nullptr if the object is not stored through a
  // std::shared_ptr yet
  auto asWeak() { return weak_from_this(); }
};

auto main() -> int {
  {
    // auto horrible{std::make_shared<Horrible>()};

    //// Reference counters are different
    // auto other{horrible->asShared()};
    // auto other2{horrible->asShared()};
  }

  {
    // This works if the object is originally allocated as a std::shared_ptr
    auto weird{std::make_shared<Weird>()};

    // Reference counters are the same
    auto ptr1{weird->asShared()};
    auto ptr2{weird->asShared()};

    // This is 3
    std::println("{}", weird.use_count());
  }

  {
    // It does not work becuase this is not a std::shared_ptr
    auto weird{new Weird};

    try {
      auto ptr1{weird->asShared()};  // Runtime error
    } catch (const std::bad_weak_ptr& e) {
      std::println("{}", e.what());
    }
  }
}