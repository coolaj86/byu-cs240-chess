/*
 * Test.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */

#include "Board.h"

void PieceTest() {
	Piece * piece = new Piece(BLACK);
	piece->Name();
	assert (!piece->IsFoe(BLACK));
	assert (piece->IsFoe(WHITE));
	delete piece;
}

void SquareTest() {
	Square * square;
	square = new Square(0,0);
	assert(0 == square->ToInt());
	delete square;
	square = new Square(7,7);
	assert(63 == square->ToInt());
	delete square;
	square = new Square(0,7);
	assert(7 == square->ToInt());
	delete square;
	square = new Square(7,0);
	assert(56 == square->ToInt());
	delete square;
	/*
	try {
		square = new Square(-1,7);
		delete square;
		assert(false);
	} catch (...) {
		assert(true);
	}
	try {
		square = new Square(7,-1);
		delete square;
		assert(false);
	} catch (...) {
		assert(true);
	}
	try {
		square = new Square(8,0);
		delete square;
		assert(false);
	} catch (...) {
		assert(true);
	}
	try {
		square = new Square(0,8);
		delete square;
		assert(false);
	} catch (...) {
		assert(true);
	}
	*/
	square = new Square(0,0);
	delete square;
}

void BoardTest() {
	Board * board = new Board();
	Square * square = new Square(0,0);
	board->PieceNameAt(*square);
	delete square;
	Square & squareB = new Square(7,7);
	board->PieceNameAt(&squareB);
}

int main(int argc,char ** argv) {
	printf("\nPieceTest:");
	PieceTest();
	printf("\nSquareTest:");
	SquareTest();
	printf("\nBoardTest:");
	BoardTest();
	printf("\n");
	return 0;
}
