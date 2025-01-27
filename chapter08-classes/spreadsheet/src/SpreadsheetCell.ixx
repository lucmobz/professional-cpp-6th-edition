export module spreadsheet_cell;

import std;

export class SpreadsheetCell {
 public:
  SpreadsheetCell() = default;
  explicit SpreadsheetCell(double value);
  explicit SpreadsheetCell(std::string_view text);

  [[nodiscard]] auto getValue() const -> double;
  void setValue(double value);

  [[nodiscard]] auto getValueString() const -> std::string;
  void setValueString(std::string_view text);

 private:
  [[nodiscard]] static auto convertDoubleToString(double value) -> std::string;
  [[nodiscard]] static auto convertStringToDouble(std::string_view text)
      -> double;

  double m_value{0.0};
};

export void printCell(const SpreadsheetCell& cell);