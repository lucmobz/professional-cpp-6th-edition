module spreadsheet_cell;

import std;


SpreadsheetCell::SpreadsheetCell(std::string_view text)
    : m_value{convertStringToDouble(text)} {}

auto SpreadsheetCell::convertDoubleToString(double value) -> std::string {
  return std::to_string(value);
}

auto SpreadsheetCell::convertStringToDouble(std::string_view text) -> double {
  auto value{0.0};
  [[maybe_unused]] auto convertResult{
      std::from_chars(text.data(), text.data() + text.size(), value)};

  if (convertResult.ec == std::errc{})
    return value;
  else
    return 0.0;
}
