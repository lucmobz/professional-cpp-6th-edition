import std;
import spreadsheet_cell;

auto main() -> int {
  SpreadsheetCell cell;
  cell.setValueString("42.69");
  printCell(cell);
}