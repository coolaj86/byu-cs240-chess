#include "Knight.h"

  Knight::Knight(PieceColor color) :
    Piece::Piece(color)
  {
    type = KNIGHT;
  }
  Knight::~Knight()
  {
  }

  std::vector<Cell> Knight::Moves()
  {
    std::vector<Cell> cells;
    _cell_advancing(cells, 1, 2);
    _cell_advancing(cells, -1, 2);
    _cell_advancing(cells, -1, -2);

    _cell_advancing(cells, 2, 1);
    _cell_advancing(cells, -2, 1);
    _cell_advancing(cells, -2, -1);
    return cells;
  }
