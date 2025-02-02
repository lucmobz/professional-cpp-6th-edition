#include <cassert>

import person;
import std;

auto main() -> int {
  Person p1{"Isaac", "Newton"};
  Person p2{"Gottfried", "Leibniz"};

  assert(p1 == p1);
  assert(p1 != p2);
  assert(p1 < p2);
  assert(p1 <= p2);
  assert(p2 > p1);
  assert(p2 >= p1);

  auto ordering{p1 <=> p2};

  std::println("Who is the best math person? {} {}",
               std::is_lt(ordering) ? p2.getFirstName() : p1.getFirstName(),
               std::is_gt(ordering) ? p1.getLastName() : p2.getLastName());
}