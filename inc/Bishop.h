#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "Piece.h"

class Bishop : public Piece {
public:
  Bishop(PieceColor);
  ~Bishop();
  std::vector<Cell> Moves();
};

#endif
