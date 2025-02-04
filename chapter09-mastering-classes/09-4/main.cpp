#include <cassert>

import person;
import std;

auto main() -> int {
  Person p0{};
  Person p1{"Isaac", "Newton"};
  Person p2{"Gottfried", "Leibniz"};
  Person p3{p1};
  Person p4{std::move(p3)};
  p1 = p2;
  p0 = std::move(p1);
}