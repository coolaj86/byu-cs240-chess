#include "Queen.h"

  Queen::Queen(PieceColor color) :
    Piece::Piece(color)
  {
    type = QUEEN;
  }
  Piece * Queen::Clone()
  {
    Queen * queen = new Queen(color);
    queen->type = type;
    queen->row = row;
    queen->col = col;
    queen->board = board;
    return (Piece *) queen;
  }
  Queen::~Queen()
  {
  }

  std::vector<Cell> Queen::Moves()
  {
    std::vector<Cell> cells;
    // Forward / BackWard
    _cells_advancing(cells, 1, 0);
    _cells_advancing(cells, -1, 0);
    // Left / Right
    _cells_advancing(cells, 0, 1);
    _cells_advancing(cells, 0, -1);

    // Diagonals
    _cells_advancing(cells, -1, 1);
    _cells_advancing(cells, 1, 1);
    _cells_advancing(cells, 1, -1);
    _cells_advancing(cells, -1, -1);
    return cells;
  }
