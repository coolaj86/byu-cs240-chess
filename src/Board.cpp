#include "Board.h"

Board::Board() {
	Init();
}

Board::~Board() {

}

void Board::Init() {
	InitPieces(BLACK_START, BLACK_STEP, BLACK);
	InitPieces(WHITE_START, WHITE_STEP, WHITE);
	for (int i = BLACK_END; i < WHITE_END+1; ++i) {
		board[i] = NULL;
	}
	board[32] = new Piece(BLACK);
	board[31] = new Piece(WHITE);
}

void Board::InitPieces(int pos, int dist, int color) {
	assert(-1 == pos || 64 == pos);
	/*
	board[pos+dist] = new Rook();
	board[pos+dist] = new Knight();
	board[pos+dist] = new Bishop();
	board[pos+dist] = new King();
	board[pos+dist] = new Queen();
	board[pos+dist] = new Bishop();
	board[pos+dist] = new Knight();
	board[pos+dist] = new Rook();
	*/
	for (int i = 0; i < 8; i++) {
		board[pos+dist] = new Piece(color);
	}
	for (int i = 0; i < 8; i++) {
		board[pos+dist] = new Piece(color);
		//board[pos+dist] = new Pawn();
	}
}

PieceName Board::PieceNameAt(const Square & square) const {
	printf("Here I Am");
	Piece & piece = PieceAt(square);
	if (NULL != &piece)
		return piece.Name();
	else
		return NO__PIECE;
}
Piece & Board::PieceAt(const Square & square) const {
	assert(square.ToInt() > -1 && square.ToInt() < 64);
	return *board[square.ToInt()];
}

/*
void	Clear() {
	for i < length {
		if i < index
			delete board[i];
		board[i] = NULL;
	}
	board[i] = NULL;
	delete [] board;
	board = NULL;
}

Piece * ReplaceAt(Square * square, Piece * piece) {
	int position = square->ToInt();
	Piece * result = board[position];
	board[position] = piece;
}
*/

