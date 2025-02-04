#include <cassert>

import person;
import std;

auto main() -> int {
  auto name{Person{"Isaac", "Newton"}.getFirstName()};
  auto initials{Person{"Gottfried", "Leibniz"}.getInitials()};

  Person person{"Leonhard", "Euler"};
  auto otherName{person.getLastName()};
}