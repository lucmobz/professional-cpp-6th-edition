module spreadsheet_cell;

import std;

SpreadsheetCell::SpreadsheetCell(double value) : m_value{value} {}

SpreadsheetCell::SpreadsheetCell(std::string_view text)
    : m_value{convertStringToDouble(text)} {}

auto SpreadsheetCell::getValue() const -> double { return m_value; }

void SpreadsheetCell::setValue(double value) { m_value = value; }

auto SpreadsheetCell::getValueString() const -> std::string {
  return convertDoubleToString(m_value);
}

void SpreadsheetCell::setValueString(std::string_view text) {
  m_value = convertStringToDouble(text);
}

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

void printCell(const SpreadsheetCell& cell) {
  std::print("[{}]", cell.getValue());
}
