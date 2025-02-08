// NOTE: The official solution interprets the problem in a different way, by
// providing each class with a converting constructor to "promote" objects.
// Instead here I used diamond virtual inheritance to create a hybrid class

#include <cassert>

import hr;
import std;

auto main() -> int {
  using namespace HR;

  std::vector<std::unique_ptr<Person>> persons;
  persons.reserve(3);

  persons.push_back(std::make_unique<Person>("Random", "Guest"));
  persons.push_back(std::make_unique<Employee>("Leonhard", "Euler", 42));
  persons.push_back(std::make_unique<Manager>("Isaac", "Newton", 1000));
  persons.push_back(std::make_unique<Director>("Gottfried", "Leibniz", 1001));
  persons.push_back(
      std::make_unique<DirectorManager>("Carl Friedrich", "Gauss", 1002));

  for (auto& person : persons) std::println("{}", person->toString());
}
