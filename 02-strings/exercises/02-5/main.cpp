import std;

auto main() -> int {
  std::println("Enter words, enter * to stop:");

  std::vector<std::string> words{};

  while (true) {
    std::string word{};
    std::cin >> word;

    if (word == "*") break;

    words.emplace_back(std::move(word));
  }

  auto compare{[](const std::string& lhs, const std::string& rhs) {
    return lhs.size() < rhs.size();
  }};

  auto result{std::max_element(words.begin(), words.end(), compare)};
  auto maxSize{result->size()};

  for (auto i{0}; const auto& word : words) {
    if (i != 0 && i % 5 == 0) std::println("");
    std::print("{:^{}}", word, maxSize);
    if ((i + 1) % 5 != 0) std::print("|");

    ++i;
  }
}