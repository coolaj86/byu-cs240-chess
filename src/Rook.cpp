#include "Rook.h"

  Rook::Rook(PieceColor color) :
    Piece::Piece(color)
  {
    type = ROOK;
  }
  Piece * Rook::Clone()
  {
    Rook * rook = new Rook(color);
    rook->type = type;
    rook->row = row;
    rook->col = col;
    rook->board = board;
    return (Piece *) rook;
  }
  Rook::~Rook()
  {
  }

  std::vector<Cell> Rook::Moves()
  {
    std::vector<Cell> cells;
    // Forward / BackWard
    _cells_advancing(cells, 1, 0);
    _cells_advancing(cells, -1, 0);
    // Left / Right
    _cells_advancing(cells, 0, 1);
    _cells_advancing(cells, 0, -1);
    return cells;
  }
