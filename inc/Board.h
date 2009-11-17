/*
king
make move
cycle through each piece to see if king is now in check



return array of possible moves
check square for other piece
check from square for check on king
getLegalMoves (can't put your own king in jepoerdy)
history.Add(Board * board);
history.ToXML(ostream * fileName); // Add current board to history
*/


/******************************************
 ******************************************
                  THE BOARD

                     X

       | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
   | 1 | 0   *   *   *   *   *   *   7

   | 2 | 8   *   *   *   *   *   *   15

   | 3 | 16  *   *   *   *   *   *   23

   | 4 | 24                          31
Y
   | 5 | 32                          39

   | 6 | 40                          47

   | 7 | 48                          55

   | 8 | 56                          63

 ******************************************
 ******************************************/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

#include "Square.h"
#include "Piece.h"

#define	NUM_SQUARES	64
#define BLACK_START 	-1
#define BLACK_END 	16
#define BLACK_STEP 	1
#define WHITE_START 	64
#define WHITE_END 	47
#define WHITE_STEP 	-1

class Board {
public:
	Board();
	~Board();
	/*
	operator =();
	Piece * PieceAt();
	bool IsSafe(Square *, int color);
	bool IsConquerable(Square *, int color);
	*/
	Piece & PieceAt(const Square & square) const;
	PieceName PieceNameAt(const Square & square) const;
	Piece & PieceAt(int row, int col) const;
	void PlacePieces(int pos, int dist);
	void UnitTest();
private:
	Piece * board[NUM_SQUARES];
	void Init();
	void Copy();
	void Clear();
	void InitPieces(int start, int end, int color);
};
#endif
