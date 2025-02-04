import std;

auto main() -> int {
  std::println("Enter numbers, enter 0 to stop:");

  std::vector<float> numbers{};

  while (true) {
    auto number{0.0f};
    std::cin >> number;

    if (number == 0.0f) break;

    numbers.push_back(number);
  }

  for (auto number : numbers) {
    std::println("{0:<16g}\t{0:<-#16e}\t{0:^16.2f}\t{0:>#16a}", number);
  }
}