import person;
import std;

auto main() -> int { Person p{"Homer", "Simpson"};
  std::println("This is {} {}, a.k.a. {} {}", p.getFirstName(),
               p.getLastName(), p.getFirstNameInitial(), p.getLastNameInitial());
}