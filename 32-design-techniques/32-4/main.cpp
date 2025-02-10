import std;

auto main() -> int {
  // TODO: how to constrain generic lambdas parameters?
  auto func{[]<typename Value>(const Value& first, const Value& second) {
    return first + second;
  }};

  std::println("{}", func(1, 2));
  std::println("{}", func(1.1, 2.2));
  std::println("{}", func(std::string{"hello "}, std::string{"world"}));
  // func(1, 1.2); // ERROR: does not compile, different types
}