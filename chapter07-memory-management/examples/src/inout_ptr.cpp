import std;

// Old C-style function used below
int oldFunction(int** ptr) {
  // allocate to ptr
  *ptr = new int{42};
  return 42;
}

auto main() -> int {
  std::unique_ptr<int> ptr{nullptr};

  // Can use std::out_ptr if the pointer is ensured to be nullptr
  if (oldFunction(std::inout_ptr(ptr)) == 42) {
    return 42;
  }

  return 0;
}