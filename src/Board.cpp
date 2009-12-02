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

bool Board::MoveFromTo(Cell const& from, Cell const& to)
{
  return MoveFromTo(from.row, from.col, to.row, to.col);
}

bool Board::MoveFromTo(int row1, int col1, int row2, int col2)
{
  if (!ValidCell(row1, col1) || !ValidCell(row2, col2))
    {std::cout << "silly1" << std::endl; return false;}
  if (!board[_map(row1, col1)]) // can't move a nothing to a something
    {std::cout
      << " row1: " << row1 << " col1: " << col1
      << " row2: " << row2 << " col2: " << col2
      << " sillyness..." << std::endl; return false;}

  vector<Piece*> move;
  Piece* opponent = NULL;
  if (board[_map(row2, col2)])
  {
    opponent = board[_map(row2, col2)];
  }
  board[_map(row2, col2)] = board[_map(row1, col1)];
  board[_map(row1, col1)] = NULL;

  Piece* piece = board[_map(row2, col2)];
  Piece* copy = piece->Clone();
  move.push_back(copy);											// original
  piece->UpdateLocation(row2, col2);
  copy = piece->Clone();
  move.push_back(copy);											// new loc
  if (opponent)
  {
    move.push_back(opponent->Clone());		// deleted opponent
    delete opponent;
  }

  history.push_back(move);
  return true;
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
  if (opponent) { PlacePiece(opponent->row, opponent->col, opponent); }
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

King* Board::FriendKing(Piece const* piece) const {
  return FriendKing(piece->Color());
}
King* Board::FriendKing(PieceColor piece_color) const {
  Piece * king;
  for (int _row = 0; _row < 8; _row++)
  {
    for (int _col = 0; _col < 8; _col++)
    {
      if ((king = PieceAt(_row,_col))
        && KING == king->type
        && piece_color == king->color)
      { return (King*) king; }
    }
  }
  // a little game logic exception...
  // perhaps out of place, but I don't care
  throw new exception();
  return NULL;
}

King* Board::EnemyKing(Piece const* piece) const {
  return EnemyKing(piece->Color());
}
King* Board::EnemyKing(PieceColor piece_color) const {
  Piece * king;
  for (int _row = 0; _row < 8; _row++)
  {
    for (int _col = 0; _col < 8; _col++)
    {
      if ((king = PieceAt(_row,_col))
        && KING == king->type
        && piece_color != king->color)
      { return (King*) king; }
    }
  }
  // a little game logic exception...
  // perhaps out of place, but I don't care
  throw new exception();
  return NULL;
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