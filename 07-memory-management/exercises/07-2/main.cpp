import std;

auto main() -> int {
  constexpr auto NUMBER_OF_ELEMENTS{std::size_t{10}};
  std::vector<int> values(NUMBER_OF_ELEMENTS);

  // Set values to their index value.
  std::ranges::iota(values.begin(), values.end() - 1, 0);

  // Set last value to 99.
  values.back() = 99;

  // Print all values.
  std::println("{:n}", values);
}