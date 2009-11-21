#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece{
public:
	King(PieceColor);
	~King();
private:
	bool firstMove;
};

#endif
