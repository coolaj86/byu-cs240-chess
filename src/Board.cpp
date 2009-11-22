#include "Board.h"

#include <iostream>
using namespace std;

Board::Board()
{
  _init();
}
void Board::_init()
{
  board = new Piece * [NUM_SQUARES];
  for (int i = 0; i < NUM_SQUARES; i++) { board[i] = NULL; }
  //memset(board, 0, sizeof(Piece*) * NUM_SQUARES);
}

Board::~Board()
{
  _clear();
}
void Board::_clear()
{
  for (int i = 0; i < NUM_SQUARES; i++)
  {
    if (board[i]) { delete board[i]; }
    board[i] = NULL;
  }
  delete [] board;
}

void Board::Clear()
{
  _clear();
  _init();
}

// TODO Does this require a pointer to maintain Rook-ness?
// I'd prefer that the creation occur here by reference
// otherwise I violate "the class that creates also destroys"
void Board::PlacePiece(int row, int col, Piece* piece)
{
  // TODO history (i.e. handle pawn promotion)
  if (!ValidCell(row, col)) { throw new exception(); }
  delete board[_map(row, col)];
  board[_map(row, col)] = piece;
  piece->board = this;
  piece->UpdateLocation(row, col);
}

void Board::MoveFromTo(int row1, int col1, int row2, int col2)
{
  if (!ValidCell(row1, col1) || !ValidCell(row2, col2))
    return;
  if (!board[(row1 * 8) + col1])
    return;

  vector<Piece*> move;
  Piece* opponent = NULL;
  if (board[_map(row2, col2)])
  {
    opponent = board[_map(row2, col2)];
  }
  board[_map(row2, col2)] = board[_map(row1, col1)];
  board[_map(row1, col1)] = NULL;

  Piece* piece = board[_map(row2, col2)];
  Piece* copy = new Piece(*piece);
  move.push_back(copy);											// original
  piece->UpdateLocation(row2, col2);
  copy = new Piece(*piece);
  move.push_back(copy);											// new loc
  if (opponent)
  {
    move.push_back(new Piece(*opponent));		// deleted opponent
    delete opponent;
  }

  history.push_back(move);
}
bool Board::Undo()
{
  if (history.size() < 1) { return false; }
  // The is not En Passant or Castling safe!!
  Piece * piece = NULL;
  Piece * opponent = NULL;
  vector<Piece*>& move = history[history.size()-1];
  if (move.size() == 3) {
    opponent = move[2];										// opponent
  }
  piece = move[1];												// new location
  RemovePieceAt(piece->row, piece->col);
  if (opponent) { PlacePiece(opponent->row, opponent->col, piece); }
  piece = move[0];												// original location
  PlacePiece(piece->row, piece->col, piece);

  history.pop_back();
  return true;
}
// TODO make a separate one which does / doesn't history based on privacy
void Board::RemovePieceAt(int row, int col)
{
  delete board[_map(row, col)];
  board[_map(row, col)] = NULL;
}

Piece* Board::PieceAt(int row, int col) const {
  if (!ValidCell(row, col))
  {
    return NULL; //TODO define -1
  }
  return board[(row * 8) + col];
}

Piece* Board::PieceAt(Cell cell) const {
  return PieceAt(cell.row, cell.col);
}


bool Board::ValidCell(Cell cell) const {
  return ValidCell(cell.row, cell.col);
}

bool Board::ValidCell(int row, int col) const {
  return (row > -1 && row < 8) && (col > -1 && col < 8);
}

int Board::_map(int row, int col) const {
  return (row * 8) + col;
}