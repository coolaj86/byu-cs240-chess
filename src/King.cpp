#include "King.h"
#include <iostream>
  King::King(PieceColor color) :
    Piece::Piece(color)
  {
    type = KING;
  }
  Piece * King::Clone()
  {
    King * king = new King(color);
    king->type = type;
    king->row = row;
    king->col = col;
    king->board = board;
    return (Piece *) king;
  }
  King::~King()
  {
  }

  std::vector<Cell> King::Moves()
  {
    std::vector<Cell> cells;
    // Forward / BackWard
    _cell_advancing(cells, 1, 0);
    _cell_advancing(cells, -1, 0);
    // Left / Right
    _cell_advancing(cells, 0, 1);
    _cell_advancing(cells, 0, -1);

    // Diagonals
    _cell_advancing(cells, -1, 1);
    _cell_advancing(cells, 1, 1);
    _cell_advancing(cells, 1, -1);
    _cell_advancing(cells, -1, -1);
    return cells;
  }
