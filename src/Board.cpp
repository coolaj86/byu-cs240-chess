#include "Board.h"

#include <iostream>
using namespace std;

Board::Board() {
  _init();
}

Board::~Board() {

}

void Board::_init() {
  board = new Piece * [NUM_SQUARES];
  for (int i = 0; i < NUM_SQUARES; i++) { board[i] = NULL; }
  //memset(board, 0, sizeof(Piece*) * NUM_SQUARES);
}

// TODO Does this require a pointer to maintain Rook-ness?
// I'd prefer that the creation occur here by reference
// otherwise I violate "the class that creates also destroys"
void Board::PlacePiece(int row, int col, Piece* piece)
{
  // TODO history (i.e. handle pawn promotion)
  if (board[(row * 8) + col])
    delete board[(row * 8) + col];
  board[(row * 8) + col] = piece;
}

void Board::MoveFromTo(int row1, int col1, int row2, int col2)
{
  if (!board[(row1 * 8) + col1])
    return;
  // TODO history
  if (board[(row2 * 8) + col2])
    delete board[(row2 * 8) + col2];
  board[(row2 * 8) + col2] = board[(row1 * 8) + col1];
  board[(row1 * 8) + col1] = NULL;
}

Piece& Board::PieceAt(int row, int col) const {
  //assert(square.ToInt() > -1 && square.ToInt() < 64);
  // TODO (row * 8) + col
  return *(board[(row * 8) + col]);
}

/*
  bool Square::IsValid() const {
    return (posY > -1 && posY < 8) && (posX > -1 && posX < 8);
  }

  int Square::ToInt() const {
    assert (IsValid());
    return (posY * 8) + posX;
  }
 */

/*
void	Clear() {
  for i < length {
    if i < index
      delete board[i];
    board[i] = NULL;
  }
  board[i] = NULL;
  delete [] board;
  board = NULL;
}

*/

