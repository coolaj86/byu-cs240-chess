#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"

class Pawn : public Piece{
public:
  Pawn(PieceColor);
  ~Pawn();
  std::vector<Cell> Moves(Board&, int row, int col);			//!< Given a cell, returns the cells to which the piece can move from that cell
  std::vector<Cell> Moves();
private:
  bool firstMove;
};

#endif
