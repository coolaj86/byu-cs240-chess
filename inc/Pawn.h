#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"

class Pawn : public Piece{
public:
  Pawn(PieceColor);
  Piece * Clone();
  ~Pawn();
  std::vector<Cell> Moves();
private:
  bool firstMove;
};

#endif
