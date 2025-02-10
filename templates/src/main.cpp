import game_board;
import grid;

auto main() -> int {
  {
    GameBoard gameBoard{8, 8};

    auto king{std::make_unique<ChessPiece>()};

    // Put on the board
    gameBoard.at(0, 0) = std::move(king);

    // Remove from the board
    auto gamePiece{std::move(gameBoard.at(0, 0))};

    // There is no dynamic_cast for std::unique_ptr, dynamic_cast on the release
    // call could leak memory if the cast fails so this requires two steps
    auto chessPiecePtr{dynamic_cast<ChessPiece*>(gamePiece.get())};

    if (chessPiecePtr) {
      gamePiece.release();
      king.reset(chessPiecePtr);
    }
  }

  {
    Grid<int, 8, 8> grid;
    auto value{grid.at(0, 0).value_or(0)};
    if (value == 0) grid.at(0, 0) = 42;
  }
}