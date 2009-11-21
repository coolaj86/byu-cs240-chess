#ifndef _PIECE_H_
#define _PIECE_H_

#include <assert.h>
#include "ChessDebug.h"
#include "Cell.h"

#include <set>

/*
 *  TODO Change these enums to be useful for bitwise calculations
 */

enum PieceName {
  NO__PIECE=0,
  BACK__GRND=1,
  WHITE__TILE=2,
  BLACK__TILE=3,

  W__PAWN=1,
  B__PAWN=3,
  W__ROOK=5,
  B__ROOK=7,
  W__KNIGHT=9,
  B__KNIGHT=11,
  W__BISHOP=13,
  B__BISHOP=15,
  W__KING=17,
  B__KING=19,
  W__QUEEN=21,
  B__QUEEN=23,

  NUM__PIECE__NAMES=16
  };

enum PieceType {
  NO_TYPE=0,
  PAWN=2,
  ROOK=6,
  KNIGHT=10,
  BISHOP=14,
  KING=18,
  QUEEN=22,
  };

enum PieceColor {
  NO_COLOR=0,
  BLACK=1,
  WHITE=-1
  };

class Piece {
public:
  Piece(PieceColor);
  ~Piece();

  PieceName Name();
  PieceType Type();
  PieceColor Color();

  void Test();

  /*
   * I don't like how the piece assumes things
   * about the board... but I don't know a cleaner
   * way to do this simply.
   *
   * Bleh! C and it's no multiple return types!
   * Give me a real /programming/ language next
   * time will ya? We're hardly CEs y'know.
   */
  /*!
   * The piece assumes an 8x8 board.
   * given a row, col it will return cells
   * to which it can move (depending on the color, the Game will handle
   * the logic from that point on
   */
  //virtual set<Cell> Moves(int row, int col, board);			//!< Given a cell, returns the cells to which the piece can move from that cell

protected:
  PieceType type;
  PieceColor color;

  void _init();
  void _copy();
  void _clear();
};
#endif
