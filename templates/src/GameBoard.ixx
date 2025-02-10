export module game_board;

export import game_piece;

import std;

export class GameBoard {
 public:
  explicit GameBoard(std::size_t width = DefaultWidth,
                     std::size_t height = DefaultHeight)
      : m_width{width}, m_height{height} {
    m_grid.reserve(m_width * m_height);

    for (std::size_t i{0}; i < m_width * m_height; ++i)
      m_grid.emplace_back(nullptr);
  }

  GameBoard(const GameBoard& other)
      : m_width{other.m_width}, m_height{other.m_height} {
    m_grid.reserve(m_width * m_height);

    for (auto& gamePiece : other.m_grid)
      m_grid.emplace_back(std::move(gamePiece->clone()));
  }

  GameBoard(GameBoard&&) = default;

  virtual ~GameBoard() = default;

  auto operator=(const GameBoard& other) -> GameBoard& {
    auto tmp{other};
    swap(tmp);
    return *this;
  }

  auto operator=(GameBoard&&) -> GameBoard& = default;

  void swap(GameBoard& other) noexcept {
    m_width = other.m_width;
    m_height = other.m_height;
    std::swap(m_grid, other.m_grid);
  }

  friend void swap(GameBoard& first, GameBoard& second) noexcept {
    first.swap(second);
  }

  constexpr auto getWidth() const noexcept { return m_width; }
  constexpr auto getHeight() const noexcept { return m_height; }

  [[nodiscard]] auto at(std::size_t x,
                        std::size_t y) -> std::unique_ptr<GamePiece>& {
    return const_cast<std::unique_ptr<GamePiece>&>(
        std::as_const(*this).at(x, y));
  }
  [[nodiscard]] auto at(std::size_t x, std::size_t y) const
      -> const std::unique_ptr<GamePiece>& {
    verifyCoordinates(x, y);
    return m_grid[x + y * m_width];
  }

  static constexpr std::size_t DefaultWidth{10};
  static constexpr std::size_t DefaultHeight{10};

 private:
  void verifyCoordinates(std::size_t x, std::size_t y) const {
    if (x >= m_width || y >= m_height)
      throw std::out_of_range{
          std::format("Trying to access grid at {}, {} when bounds are {}, {}",
                      x, y, getWidth(), getHeight())};
  }

  std::size_t m_width{0};
  std::size_t m_height{0};
  std::vector<std::unique_ptr<GamePiece>> m_grid{};
};
