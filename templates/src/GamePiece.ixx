export module game_piece;

import std;

export class GamePiece {
 public:
  GamePiece() = default;
  GamePiece(const GamePiece&) = default;
  GamePiece(GamePiece&&) noexcept = default;

  virtual ~GamePiece() = default;

  // Restore these becuase they are deleted by the virtual destructor
  GamePiece& operator=(const GamePiece&) = default;
  GamePiece& operator=(GamePiece&&) noexcept = default;

  // Usin auto because the actual type for ordering is determined by members
  auto operator<=>(const GamePiece&) const = default;

  virtual auto clone() const -> std::unique_ptr<GamePiece> = 0;
};

export class ChessPiece : public GamePiece {
 public:
  // This clone method is used to produce copies in a polymorphic context
  auto clone() const -> std::unique_ptr<GamePiece> override {
    return std::make_unique<ChessPiece>(*this);
  }
};
