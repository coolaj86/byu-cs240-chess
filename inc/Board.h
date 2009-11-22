#ifndef _BOARD_H_
#define _BOARD_H_

//#include <stdio.h> memset???
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


#define	NUM_SQUARES	64
#define BLACK_START 	-1
#define BLACK_END 	16
#define BLACK_STEP 	1
#define WHITE_START 	64
#define WHITE_END 	47
#define WHITE_STEP 	-1

/******************************************
 ******************************************
                  THE BOARD

                     X

       | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
   | 1 | 0   *   *   *   *   *   *   7

   | 2 | 8   *   *   *   *   *   *   15

   | 3 | 16                          23

   | 4 | 24                          31
Y
   | 5 | 32                          39

   | 6 | 40                          47

   | 7 | 48  *   *   *   *   *   *   55

   | 8 | 56  *   *   *   *   *   *   63

 ******************************************
 ******************************************/

using namespace std;

/*!
 * Handles Memory Management and Mapping for the Board array and all pieces
 * Allows safe manipulation of the board in any way.
 *
 * No logic is stored at this level. You could totally create your own game
 * with any pieces of type Piece and any upper layer of type Game
 */
class Board {
public:
  Board();																									//!< Creates a clear board
  Board(Board&);																						//!< Copy contructor
  Board& operator=(Board&);																	//!< Copy assignment
  ~Board();																									//!< Clears the board

  Piece* PieceAt(int row, int col) const;										//!< Retrieve the piece
  Piece* PieceAt(Cell) const;
  void RemovePieceAt(int row, int col);											//!< Remove and delete the piece
  void PlacePiece(int row, int col, Piece *);								//!< Place a piece at row,col; removing existing piece if necessary
  void MoveFromTo(int row1, int col1, int row2, int col2);	//!< Safetly (memory) moves piece from one square to another and updates history
  bool ValidCell(int row, int col) const;										//!< The cell is in the bounds of the array
  bool ValidCell(Cell) const;
  bool Undo();

  void Clear();
  void Test();																							//!< Runs Unit Tests on the Board

private:
  Piece** board;																						//!< Flat array, which is mapped
  // TODO handle pawn promotion without adding setup to history
  vector< vector< Piece* > > history;														//!< An undoable history of moves

  void _init();																							//!< Setup a new board
  int	_map(int row, int col) const;													//!< Maps row,col to array, doesn't Bounds check
  void _copy();																							//!< Copy helper
  void _clear();																						//!< Free all memory in the board

};
#endif
