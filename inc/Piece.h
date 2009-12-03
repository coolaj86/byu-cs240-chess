#ifndef _PIECE_H_
#define _PIECE_H_

#include <assert.h>
#include "ChessDebug.h"
#include "Cell.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/regex.hpp>

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

class Board;

class Piece {
  friend class Board;
public:
  Piece(PieceColor);
  ~Piece();

  static Piece * Create(PieceType, PieceColor);
  static Piece * Create(PieceType type, PieceColor color, int row, int col);
  static Piece * FromString(std::string);
  PieceName Name() const;
  PieceType Type() const;
  PieceColor Color() const;
  std::string TypeString() const;
  std::string ColorString() const;
  std::string ToString() const;

  void UpdateLocation(int row, int col);
  void UpdateLocation(Cell const&);

  void Test();

  virtual std::vector<Cell> Moves();	   										       				//!< Returns the cells to which a piece can currently move
  virtual Piece * Clone();																								//!< Returns a specific type of piece
  bool CouldTake(Cell);
  bool CanSaveKing();
  Cell Location();

protected:
  Board* board;
  PieceType type;
  PieceColor color;
  int row;
  int col;

  void _cells_advancing(std::vector<Cell>& cells, int f_b, int l_r);			//!< Gather cells while advancing in the direction of front,back,left,right.
  void _cell_advancing(std::vector<Cell>& cells, int f_b, int l_r);				//!< Gather cells while advancing in the direction of front,back,left,right.

  void _init();
  void _copy();
  void _clear();
};
class King;

#include "Board.h"
#endif
