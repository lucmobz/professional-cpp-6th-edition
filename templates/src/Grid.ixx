export module grid;

import std;

export template <typename ValueType, std::size_t WIDTH = 10,
                 std::size_t HEIGHT = 10>
class Grid {
 private:
  using StoredType = std::optional<ValueType>;

 public:
  Grid() = default;
  virtual ~Grid() = default;

  // Copy
  Grid(const Grid&) = default;
  auto operator=(const Grid&) -> Grid& = default;

  // Move
  Grid(Grid&&) noexcept = default;
  auto operator=(Grid&&) noexcept -> Grid& = default;

  constexpr auto getWidth() const noexcept { return WIDTH; }
  constexpr auto getHeight() const noexcept { return HEIGHT; }

  [[nodiscard]] auto at(std::size_t x, std::size_t y) -> StoredType& {
    return const_cast<StoredType&>(std::as_const(*this).at(x, y));
  }
  [[nodiscard]] auto at(std::size_t x,
                        std::size_t y) const -> const StoredType& {
    verifyCoordinates(x, y);
    return m_grid[x][y];
  }

 private:
  void verifyCoordinates(std::size_t x, std::size_t y) const {
    if (x >= WIDTH || y >= HEIGHT)
      throw std::out_of_range{
          std::format("Trying to access grid at {}, {} when bounds are {}, {}",
                      x, y, getWidth(), getHeight())};
  }

  StoredType m_grid[WIDTH][HEIGHT]{};
  // This verifies that storage is column wise
  static_assert(std::is_same_v<std::remove_cvref_t<decltype(m_grid[0])>,
                               StoredType[HEIGHT]>);
};
