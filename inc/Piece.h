#ifndef _PIECE_H_
#define _PIECE_H_

#include <assert.h>
#include "ChessDebug.h"
#include "Cell.h"

#include <set>

#define BLACK	1
#define WHITE	-1


/*
 *  TODO Change these enums to be useful for bitwise calculations
 */

enum PieceName {
  NO__PIECE=0,BACK__GRND=1,
  WHITE__TILE=2,BLACK__TILE=3,
  W__PAWN=4,B__PAWN=5,
  W__ROOK=6,B__ROOK=7,
  W__KNIGHT=8,B__KNIGHT=9,
  W__BISHOP=10,B__BISHOP=11,
  W__KING=12,B__KING=13,
  W__QUEEN=14,B__QUEEN=15,
  NUM__PIECE__NAMES=16
  };

enum PieceType {
  NO_TYPE=0,
  PAWN=1,
  ROOK=2,
  KNIGHT=3,
  BISHOP=4,
  KING=5,
  QUEEN=6,
  NUM_TYPE_NAMES=7
  };

enum PieceColor {
  NO_COLOR=0,
  _BLACK_=1,
  _WHITE_=-1,
  NUM_COLOR_NAMES=3
  };

class Piece {
public:
  Piece(int);
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
  //virtual set<Cell> Moves(int row, int col);			//!< Given a cell, returns the cells to which the piece can move from that cell

protected:
  PieceName type;
  // PieceColor color;
  int color;
  int direction; // TODO nix this, the color knows which direction to go
  void Init(); // TODO fix style to match other private methods
  void Copy();
  void Clear();
};
#endif
