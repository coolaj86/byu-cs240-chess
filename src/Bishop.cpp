#include "Bishop.h"

  Bishop::Bishop(PieceColor color) :
    Piece::Piece(color)
  {
    type = BISHOP;
  }
  Bishop::~Bishop()
  {
  }

  std::vector<Cell> Bishop::Moves()
  {
    std::vector<Cell> cells;
    // Diagonals
    _cells_advancing(cells, -1, 1);
    _cells_advancing(cells, 1, 1);
    _cells_advancing(cells, 1, -1);
    _cells_advancing(cells, -1, -1);
    return cells;
  }
