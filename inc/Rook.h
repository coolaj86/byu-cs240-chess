#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.h"

class Rook : public Piece {
public:
  Rook(PieceColor);
  Piece * Clone();
  ~Rook();
  std::vector<Cell> Moves();
};

#endif
