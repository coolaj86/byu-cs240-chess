#ifndef _PIECE_H_
#define _PIECE_H_

#include <assert.h>
#include "ChessDebug.h"

#define BLACK	1
#define WHITE	-1
enum PieceName{NO__PIECE=0,BACK__GRND=1,
                WHITE__TILE=2,BLACK__TILE=3,
                W__PAWN=4,B__PAWN=5,
                W__ROOK=6,B__ROOK=7,
                W__KNIGHT=8,B__KNIGHT=9,
                W__BISHOP=10,B__BISHOP=11,
                W__KING=12,B__KING=13,
                W__QUEEN=14,B__QUEEN=15,
                NUM__PIECE__NAMES=16};

class Piece {
public:
	//Piece();
	Piece(int _color);
	~Piece();
	PieceName Name();
	bool IsFoe(int _color);
	bool IsFoe(Piece * _piece);
	void UnitTest();
	/*
	void operator =();
	Set<Square> Moves(Board * board);	// Return squares for valid moves
	*/
private:
	PieceName type;
	int color;
	//int direction;
	void Init();
	void Copy();
	void Clear();
};
#endif
