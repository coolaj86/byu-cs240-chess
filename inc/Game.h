#ifndef _GAME_H_
#define _GAME_H_

#include <stdlib.h>
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <boost/regex.hpp>

#include "ChessGuiDefines.h"
#include "Board.h"
#include "Cell.h"

using namespace std;

enum EndGameType {
  PLAY = 500,
  CHECKMATE = 100,
  STALEMATE = -100
};

class Game {
public:
  Game();
  //Game(int Rules);																					//!< 'OR'ed representation of rules (allow En Passant, etc)
  ~Game();

  void NewGame();																							//!< Frees memory of old game and allocates a new one
  // TODO use bitwise OR-ing to simplify these three
  PieceName WhatPieceIsAt(int row, int col) const;						//!< Returns int value (ImageName) of Piece
  PieceType WhatTypeIsAt(int row, int col) const;							//!< Returns int value (PieceType) of Piece
  PieceColor WhatColorIsAt(int row, int col) const;						//!< Returns int value (PieceColor) of Piece
  PieceName PieceNameAt(int row, int col) const;							//!< Get just the name of the piece
  PieceColor PieceColorAt(int row, int col) const;						//!< Get just the color of the piece
  PieceType PieceTypeAt(int row, int col) const;							//!< Get just the type of the piece

  /*
   * Ask the piece where it can normally move
   * and then check the board to see if it is empty
   * has an enemy, or a friend, and add to the vector
   * accordingly (will probably change to set)
   */
  vector<Cell> ValidMoves(int row, int col);									//!< Get a set of cell coordinates which imply legal moves
  vector<Cell> ValidMoves(Cell);

  bool MoveFromTo(int row1, int col1, int row2, int col2);		//!< Moves a piece, if any, and returns true if possible and updates history, changes the turn on success
  bool MoveFromTo(Cell, Cell);
  PieceColor WhoseTurn() const;																			//!< Return whose turn it is
  bool HasTurn(int row, int col) const;												//!< (PieceColor == TurnColor) ? true : false
  bool Check(PieceColor) const;
  EndGameType GameOver();

  void Undo();																								//!< Pops move from history and performs the reverse
  void Save(ostream&);																				//!< Writes history to xml
  void Load(istream&);																				//!< Clears the game and loads history

  void Test();																								//!< Runs Unit Tests

private:
  Board board;
  PieceColor whose_turn;

  void _init();
  void _init_pieces();
  void _clear();

};
#endif