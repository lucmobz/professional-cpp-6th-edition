#include <cassert>

import person;
import std;

auto main() -> int {
  Person p1{"Isaac", "Newton"};
  Person p2{"Gottfried", "Leibniz"};

  assert(p1 == p1);
  assert(p1 != p2);
  assert(p2 < p1);
  assert(p2 <= p1);
  assert(p1 > p2);
  assert(p1 >= p2);
}