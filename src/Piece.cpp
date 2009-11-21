/*
 * Piece.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */

#include "Piece.h"

  Piece::Piece(PieceColor _color) :
    type(PAWN)
  {
    assert (WHITE == _color || BLACK == _color);
    color = _color;
  }

  Piece::~Piece() {
    return;
  }

  PieceName Piece::Name() {
    return (PieceName) (type + color);
  }

  PieceType Piece::Type() {
    return type;
  }

  PieceColor Piece::Color() {
    return color;
  }

/*
  static bool Piece::UnitTest() {
    TEST(Piece * piece = new Piece(BLACK));
    TEST(delete piece && piece = new Piece(WHITE));
    TEST(piece->Name());
  }
*/
