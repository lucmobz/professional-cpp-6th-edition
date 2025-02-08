import std;

int main() {
  std::string firstString{};
  std::string secondString{};

  std::println("First: ");
  std::getline(std::cin, firstString);

  std::println("Second: ");
  std::getline(std::cin, secondString);

  auto comparison{firstString <=> secondString};

  if (std::is_lt(comparison))
    std::println("First is less than second");
  else if (std::is_eq(comparison))
    std::println("First is equal to second");
  else if (std::is_gt(comparison))
    std::println("First is greater than second");
}
