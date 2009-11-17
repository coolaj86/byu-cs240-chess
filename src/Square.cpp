/*
 * Square.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */
#include "Square.h"

	Square::Square(int row, int col) {
		assert(row > -1 && row < 8);
		assert(col > -1 && col < 8);
		posX = col;
		posY = row;
	}
	/*
	Square::Square(const Square & _square) {
	}
	*/
	Square::~Square() {
	}

	int Square::ToInt() const {
		assert (IsValid());
		return (posY * 8) + posX;
	}

	bool Square::IsValid() const {
		return (posY > -1 && posY < 8) && (posX > -1 && posX < 8);
	}
