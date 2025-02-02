import person;
import std;

Person createPerson() {
  // The temporary std::string is destroyed at the end of the full expression
  // (so at the ;), it is therefore safe to bind a std::string_view parameter to
  // this temporary
  Person p{std::string{"Gottfried"}, "Leibniz"};
  return p;
}

auto main() -> int {
  Person p1{"Isaac", "Newton"};
  auto p2{std::move(p1)};
  p1 = std::move(p2);

  Person p3{createPerson()};
  p1.swap(p3);

  std::println("{} {}", p1.getFirstName(), p1.getLastName());
  std::println("{} {}", p2.getFirstName(), p2.getLastName());
  std::println("{} {}", p3.getFirstName(), p3.getLastName());
}
