#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.h"

class Knight : public Piece {
public:
	Knight(PieceColor);
	~Knight();
  std::vector<Cell> Moves();
};

#endif
