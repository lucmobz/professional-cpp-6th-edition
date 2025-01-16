import std;

static auto findNeedleInHaystack(std::string haystack, std::string_view needle,
                                 const std::string_view replacement)
    -> std::string {
  auto position{haystack.find(needle)};
  auto sizeNeedle{needle.size()};
  auto sizeReplacement{replacement.size()};

  while (position != std::string::npos) {
    haystack.replace(position, sizeNeedle, replacement);
    position = haystack.find(needle, position + sizeReplacement);
  }

  return haystack;
}

auto main() -> int {
  std::string haystack;
  std::string needle;
  std::string replacement;

  std::println("Enter haystack: ");
  std::getline(std::cin, haystack);

  std::println("Enter needle: ");
  std::getline(std::cin, needle);

  std::println("Enter replacement: ");
  std::getline(std::cin, replacement);

  std::println("Haystack: {}\nNeedle: {}\nReplacement: {}\nResult: {}",
               haystack, needle, replacement,
               findNeedleInHaystack(haystack, needle, replacement));
}
