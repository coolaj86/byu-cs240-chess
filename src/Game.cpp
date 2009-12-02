/*
 * Game.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */

#include "Game.h"

#include <iostream>
using namespace std;

Game::Game() {
  _init();
}
void Game::_init()
{
  board.Clear();
  //history = vector<Move>;
  whose_turn = WHITE;
  _init_pieces();
}

Game::~Game() {
  _clear();
}
void Game::_clear()
{
  board.Clear();
}

void Game::NewGame() {
  _clear();
  _init();
}

vector<Cell> Game::ValidMoves(Cell cell)
{
  return ValidMoves(cell.row, cell.col);
}

vector<Cell> Game::ValidMoves(int row, int col)
{
  cout << "ValidMoves" << endl;
  // TODO limit
  vector<Cell> moves;

  Piece* piece = board.PieceAt(row, col);
  if (NULL == piece)
    return moves;

  Cell location = piece->Location();
  moves = piece->Moves();

  std::cout << "Number of Moves: " << moves.size() << std::endl;
  std::vector<Cell> filtered_moves;
  for (int i = 0; i < moves.size(); i++)
  {
    // this should never take the king
    if (!(board.MoveFromTo(location, moves[i]))) { continue; }
    if (!Check(WhoseTurn()))
    {
      filtered_moves.push_back(moves[i]);
    }
    else
    {
      std::cout << "The King is in danger if I move" << std::endl;
    }
    whose_turn = (whose_turn == WHITE) ? BLACK : WHITE;
    Undo();
  }

  return filtered_moves;
}

bool Game::MoveFromTo(int row1, int col1, int row2, int col2)
{
  Piece* piece = board.PieceAt(row1, col1);
  if (NULL == piece)
    return false;

  Cell cell(row2, col2);
  vector<Cell> cells = ValidMoves(row1, col1);
  for (int i = 0; i < cells.size(); i++)
  {
    if (cells[i] == cell)
    {
      board.MoveFromTo(row1, col1, row2, col2);
      // TODO
      /*
      if (_king_in_check())
      {
        board.Undo();
      }
      */
      //TODO replace with method
      whose_turn = (whose_turn == WHITE) ? BLACK : WHITE;
      return true;
    }
  }

  return false;
}

// TODO change to PieceColor
PieceColor Game::WhoseTurn() const
{
  return whose_turn;
}

bool Game::HasTurn(int row, int col) const
{
  Piece* piece = board.PieceAt(row, col);
  if (NULL != piece)
    return (whose_turn == piece->Color());
  else
    return false;
}

void Game::_init_pieces() {

  // The board manages the memory for these
  board.PlacePiece(7, 0, new Rook(WHITE));
  board.PlacePiece(7, 1, new Knight(WHITE));
  board.PlacePiece(7, 2, new Bishop(WHITE));
  board.PlacePiece(7, 3, new King(WHITE));
  board.PlacePiece(7, 4, new Queen(WHITE));
  board.PlacePiece(7, 5, new Bishop(WHITE));
  board.PlacePiece(7, 6, new Knight(WHITE));
  board.PlacePiece(7, 7, new Rook(WHITE));
  for (int i = 0; i < 8; i++) { board.PlacePiece(6, i, new Pawn(WHITE)); }

  board.PlacePiece(0, 0, new Rook(BLACK));
  board.PlacePiece(0, 1, new Knight(BLACK));
  board.PlacePiece(0, 2, new Bishop(BLACK));
  board.PlacePiece(0, 3, new King(BLACK));
  board.PlacePiece(0, 4, new Queen(BLACK));
  board.PlacePiece(0, 5, new Bishop(BLACK));
  board.PlacePiece(0, 6, new Knight(BLACK));
  board.PlacePiece(0, 7, new Rook(BLACK));
  for (int i = 0; i < 8; i++) { board.PlacePiece(1, i, new Pawn(BLACK)); }
}

PieceName Game::PieceNameAt(int row, int col) const {
  Piece* piece = board.PieceAt(row, col);
  if (NULL != piece)
    return piece->Name();
  else
    return NO__PIECE;
}

bool Game::Check(PieceColor color) const
{
  King * king = board.FriendKing(color);
  Piece * piece;

  for (int _row = 0; _row < 8; _row++)
  {
    for (int _col = 0; _col < 8; _col++)
    {
      Cell cell = Cell(_row, _col);
      if ((piece = board.PieceAt(cell))
        && (piece->Color() != king->Color())
        && (piece->CouldTake(king->Location()))) // TODO move in moves
        {
          std::cout << king->Color() << " King can be attacked by "
            << " Name: " << piece->Name()
            << " Color: " << piece->Color()
            << " Type: " << piece->Type()
            << std::endl;
          return true; }
    }
  }
  return false;
}


// I am in check and I can't move any piece to get out of check
EndGameType Game::GameOver()
{
  Piece * piece;
  //bool king_can_be_saved = false;
  for (int _row = 0; _row < 8; _row++)
  {
    for (int _col = 0; _col < 8; _col++)
    {
      if ((piece = board.PieceAt(_row, _col))
        && WhoseTurn() == piece->Color()
        && 0 < ValidMoves(piece->Location()).size())
        { return PLAY; }
    }
  }
  return Check(WhoseTurn()) ? CHECKMATE : STALEMATE;
}

void Game::Undo()
{
  if (board.Undo())
  {
    whose_turn = (whose_turn == WHITE) ? BLACK : WHITE;
  }
}

void Game::Save(string filename)
{
  // loop through
}

void Game::Load(string filename)
{
  // loop through
}

PieceName Game::WhatPieceIsAt(int row, int col) const
{
  assert((row > BLACK_START && row < BLACK_END)
      || (row < WHITE_START && row > WHITE_END));
  return PieceNameAt(row, col);
}