#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece{
public:
	King(int);
	~King();
private:
	bool firstMove;
};

#endif
