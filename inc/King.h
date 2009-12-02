#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece {
public:
  King(PieceColor);
  ~King();
  Piece * Clone();
  std::vector<Cell> Moves();

private:
  bool firstMove;
};

#endif
