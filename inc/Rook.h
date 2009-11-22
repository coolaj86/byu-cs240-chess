#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.h"

class Rook : public Piece {
public:
  Rook(PieceColor);
  ~Rook();
  std::vector<Cell> Moves();
};

#endif
