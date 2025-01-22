import std;

void fillWithM(char* text) {
  int i{0};
  while (text[i] != '\0') {
    text[i] = 'm';
    ++i;
  }
}

void fillWithMModernized(std::string& text) {
  for (auto& glyph : text) glyph = 'm';
}

auto main() -> int {
  using namespace std::string_view_literals;
  std::string text{"hello"sv};
  fillWithMModernized(text);
}