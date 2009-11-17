/*
 * Facade.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */

#include "Facade.h"

Facade::Facade() {
	NewGame();
}
Facade::~Facade() {

}

void Facade::NewGame() {
	board = new Board();
	//history = new MoveHistory();
}

ImageName const Facade::ImageAt(int row, int col) {
	assert((row > BLACK_START && row < BLACK_END)
			|| (row < WHITE_START && row > WHITE_END));
	Square square(row, col);
	return PieceToImageName(board->PieceNameAt(square));
}

ImageName Facade::PieceToImageName(const PieceName piece) const {
	switch(piece) {
	case NO__PIECE:
		return NO_IMAGE;

	case B__ROOK:
		return B_ROOK;
	case B__KNIGHT:
		return B_KNIGHT;
	case B__BISHOP:
		return B_BISHOP;
	case B__QUEEN:
		return B_QUEEN;
	case B__KING:
		return B_KING;
	case B__PAWN:
		return B_PAWN;

	case W__ROOK:
		return W_ROOK;
	case W__KNIGHT:
		return W_KNIGHT;
	case W__BISHOP:
		return W_BISHOP;
	case W__QUEEN:
		return W_QUEEN;
	case W__KING:
		return W_KING;
	case W__PAWN:
		return W_PAWN;

	default:
		return NO_IMAGE;
	}
}

/*
Move * Undo() {

}

*/
