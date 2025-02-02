module;

#include <cassert>

module spreadsheet;

import std;

Spreadsheet::Spreadsheet(const SpreadsheetApplication& app, Index width,
                         Index height)
    : m_app{app},
      m_width{std::min(width, MaxWidth)},
      m_height{std::min(height, MaxHeight)} {
  // Degenerate spreadsheets are not allowed, only the 0x0 spreadsheet is
  // allowed
  if (m_width <= 0 || m_height <= 0) {
    m_width = 0;
    m_height = 0;
    throw std::invalid_argument{
        std::format("Trying to create a degenerate spreadsheet of size {}, {}",
                    width, height)};
  }

  m_cells = new SpreadsheetCell*[m_width];

  for (std::size_t y{0}; y < m_width; ++y)
    m_cells[y] = new SpreadsheetCell[m_height]{};
}

Spreadsheet::Spreadsheet(const Spreadsheet& other)
    : Spreadsheet{other.m_app, other.m_width, other.m_height} {
  // NOTE: Delegating constructor does initialization, then the copy happens,
  // this could be cache-unfriendly
  for (std::size_t x{0}; x < m_width; ++x)
    std::copy(other.m_cells[x], other.m_cells[x] + m_height, m_cells[x]);
}

Spreadsheet::Spreadsheet(Spreadsheet&& other) noexcept : m_app{other.m_app} {
  // This object is default constructed using in-class initializers
  swap(other);
  // Moved object is in valid state of default construction
}

Spreadsheet::~Spreadsheet() {
  if (!m_cells) return;

  for (std::size_t y{0}; y < m_width; ++y) delete[] m_cells[y];
  delete[] m_cells;
  m_cells = nullptr;  // Done for security reasons
}

auto Spreadsheet::operator=(const Spreadsheet& other) & -> Spreadsheet& {
  // Self assignment check is not the common case and can be removed
  // if (this == &other) return *this;

  // Using the copy-swap idiom, this is strongly exception safe (exceptions
  // thrown have no effect on this object)
  auto tmp{other};  // Need lvalue reference
  swap(tmp);
  // Clean up is done by the temporary destructor

  return *this;
}

auto Spreadsheet::operator=(Spreadsheet&& other) & noexcept -> Spreadsheet& {
  // Self-assignment is not the common case, moving is also cheap
  // if (this == &other) return *this;

  auto tmp{std::move(other)};  // Moved object is in default state
  swap(tmp);
  // temporary destructor prevents leaking of internal state of this object

  return *this;
}

void Spreadsheet::swap(Spreadsheet& other) noexcept {
  // Swapping will not pass ownership between applications
  std::swap(m_width, other.m_width);
  std::swap(m_height, other.m_height);
  std::swap(m_cells, other.m_cells);
}

auto Spreadsheet::getCellAt(Index x, Index y) -> SpreadsheetCell& {
  // This is Scott Meyers' const_cast pattern, using const_cast for the
  // non-const version is better than the other way around, as in that case the
  // non-const version needs to guarantee an implicit constness, while in this
  // case it is forced by the compiler
  return const_cast<SpreadsheetCell&>(std::as_const(*this).getCellAt(x, y));
}

auto Spreadsheet::getCellAt(Index x, Index y) const -> const SpreadsheetCell& {
  if (!isInRange(x, y)) {
    throw std::out_of_range{
        std::format("Trying to get cell at {}, {} when size is {}, {}", x, y,
                    m_width, m_height)};
  }

  return m_cells[x][y];
}

void Spreadsheet::setCellAt(Index x, Index y, const SpreadsheetCell& cell) {
  getCellAt(x, y) = cell;
}

void printSpreadsheet(const Spreadsheet& spreadsheet) {
  // std::print("{:^2}", "");

  // for (std::size_t x{0}; x < spreadsheet.m_width; ++x) {
  //   std::print("{:^10}", x);
  // }

  // std::println("");

  // for (std::size_t y{0}; y < spreadsheet.m_height; ++y) {
  //   std::print("{:^2}", y);

  //  for (std::size_t x{0}; x < spreadsheet.m_width; ++x) {
  //    auto& cell{spreadsheet.getCellAt(x, y)};
  //    std::print("[{:^8.1f}]", cell.getValue());
  //  }

  //  std::println("");
  //}
}
