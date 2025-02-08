import person;
import std;

auto main() -> int {
  Person stackPerson{"Homer", "Simpson"};
  stackPerson.setFirstName("Max").setLastName("Power");

  auto heapPerson{std::make_unique<Person>("Peter", "Griffin")};

  std::println("{} {} is on the stack, while {} {} is on the heap!\n",
               stackPerson.getFirstName(), stackPerson.getLastName(),
               heapPerson->getFirstName(), heapPerson->getLastName());
}