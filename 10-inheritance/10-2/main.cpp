#include <cassert>

import person;
import std;

auto main() -> int {
  using namespace HR;

  Employee e1{"Leonhard", "Euler", 42};
  Manager m1{"Isaac", "Newton", 1};
  Director d1{"Gottfried", "Leibniz", 0};

  std::println("{}", e1.toString());
  std::println("{}", m1.toString());
  std::println("{}", d1.toString());
}
