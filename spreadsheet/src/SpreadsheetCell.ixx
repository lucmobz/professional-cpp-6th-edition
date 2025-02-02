export module spreadsheet_cell;

import std;

// inline is not implicit for functions defined in-class with modules
export class SpreadsheetCell {
 public:
  SpreadsheetCell() = default; // Not sure constexpr/noexcept is needed[
  constexpr explicit SpreadsheetCell(double value) noexcept;
  explicit SpreadsheetCell(std::string_view text);

  [[nodiscard]] constexpr auto getValue() const noexcept -> double;
  [[nodiscard]] auto getString() const -> std::string;

  constexpr void set(double value) noexcept;
  void set(std::string_view text);

  // This template can be used to delete all implicit conversions except those
  // explicitly defined
  // template<typename Type> void set(Type) = delete;

 private:
  [[nodiscard]] static auto convertDoubleToString(double value) -> std::string;
  [[nodiscard]] static auto convertStringToDouble(std::string_view text)
      -> double;

  double m_value{0.0};
};

// inline/constexpr definitions must be available in the interface

constexpr SpreadsheetCell::SpreadsheetCell(double value) noexcept
    : m_value{value} {}

constexpr auto SpreadsheetCell::getValue() const noexcept -> double {
  return m_value;
}

inline auto SpreadsheetCell::getString() const -> std::string {
  return convertDoubleToString(m_value);
}

constexpr void SpreadsheetCell::set(double value) noexcept { m_value = value; }

inline void SpreadsheetCell::set(std::string_view text) {
  m_value = convertStringToDouble(text);
}
