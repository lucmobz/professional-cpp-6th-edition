import person;
import std;

Person createPerson() {
  Person p;
  p.setFirstName("Mr.");
  p.setLastName("Robot");
  return p;
}

auto main() -> int {
  Person p1;      // Default ctor
  Person p2{p1};  // Copy ctor
  Person p3{"Homer", "Simpson"};
  p3 = p1;                    // Copy assignment
  Person p4{createPerson()};  // Copy elision (NRVO)
  Person p5;
  p5 = createPerson();  // Copy elision of temporary (not of assignment)
  // Dtors
}