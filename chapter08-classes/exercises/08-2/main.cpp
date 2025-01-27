import person;
import std;

auto main() -> int {
  Person persons[3];  // Does not work until a default constructor is available.
                      // POD are uninitialized but objects are
                      // default-initialized
}