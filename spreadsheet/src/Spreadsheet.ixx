export module spreadsheet;

export import spreadsheet_cell;
import std;

class Spreadsheet;

export class SpreadsheetApplication {
 public:
  SpreadsheetApplication() = default;
  SpreadsheetApplication(const SpreadsheetApplication&) {
    std::println("copy-ctor {}", __func__);
  }
  SpreadsheetApplication(SpreadsheetApplication&&) {
    std::println("move-ctor {}", __func__);
  }
  SpreadsheetApplication& operator=(const SpreadsheetApplication&) {
    std::println("copy-assign {}", __func__);
  }
  SpreadsheetApplication& operator=(SpreadsheetApplication&&) {
    std::println("move-assign {}", __func__);
  }
};

export class Spreadsheet {
  // These declarations are also exported
  friend void printSpreadsheet(const Spreadsheet& spreadsheet);

 public:
  using Index = std::size_t;

  static constexpr Index MaxWidth{100};
  static constexpr Index MaxHeight{100};

  // Marking this explicit will disable copy-list initialization
  Spreadsheet(const SpreadsheetApplication& app, Index width, Index height);
  Spreadsheet(const Spreadsheet& other);
  Spreadsheet(Spreadsheet&& other) noexcept;  // Move ctor needs ot be noexcept
                                              // for performance

  ~Spreadsheet();  // Dtor should never throw (else members are not freed
                   // properly), it is implicitly noexcpet if all sub-objects
                   // are noexcept

  // Ref-qualifying to lvalues to prevent useless assignment to temporaries
  auto operator=(const Spreadsheet& other) & -> Spreadsheet&;
  auto operator=(Spreadsheet&& other) & noexcept
      -> Spreadsheet&;  // Also noexcept

  void swap(Spreadsheet& other) noexcept;

  [[nodiscard]] constexpr auto getId() const noexcept;

  [[nodiscard]] auto getCellAt(Index x, Index y) -> SpreadsheetCell&;
  [[nodiscard]] auto getCellAt(Index x,
                               Index y) const -> const SpreadsheetCell&;

  void setCellAt(Index x, Index y, const SpreadsheetCell& cell);

 private:
  bool isInRange(Index x, Index y) const;

  static inline Index ms_idCounter{0};

  // Initialize this here and do not touch it in constructors
  const Index m_id{ms_idCounter++};
  const SpreadsheetApplication& m_app;
  Index m_width{0};
  Index m_height{0};
  SpreadsheetCell** m_cells{nullptr};
};

inline void swap(Spreadsheet& first, Spreadsheet& second) noexcept {
  first.swap(second);
}

constexpr auto Spreadsheet::getId() const noexcept { return m_id; }

inline bool Spreadsheet::isInRange(Index x, Index y) const {
  return x >= 0 && x < m_width && y >= 0 && y < m_height;
}
