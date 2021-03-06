#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"

class Queen : public Piece {
public:
  Queen(PieceColor);
  Piece * Clone();
  ~Queen();

  std::vector<Cell> Moves();

};

#endif
