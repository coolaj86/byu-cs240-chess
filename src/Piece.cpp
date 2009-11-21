/*
 * Piece.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */

#include "Piece.h"

  Piece::Piece(int _color) {
    assert (WHITE == _color || BLACK == _color);
    color = _color;
    if (WHITE == color)
      type = W__PAWN;
    else
      type = B__PAWN;
  }
  Piece::~Piece() {
    return;
  }

  PieceName Piece::Name() {
    return type;
  }

/*
  static bool Piece::UnitTest() {
    TEST(Piece * piece = new Piece(BLACK));
    TEST(delete piece && piece = new Piece(WHITE));
    TEST(piece->Name());
  }
*/
