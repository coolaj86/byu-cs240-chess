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

vector<Cell> Game::WhereCanPieceMoveFrom(int row, int col)
{
  cout << "WhereCanPieceMoveFrom" << endl;
  // TODO limit
  vector<Cell> cells;

  Piece* piece = board.PieceAt(row, col);
  if (NULL == piece)
    return cells;

  cells = piece->Moves();
  return cells;
  cout << "WhereCanPieceMoveFrom End" << endl;
}

bool Game::MoveFromTo(int row1, int col1, int row2, int col2)
{
  Piece* piece = board.PieceAt(row1, col1);
  if (NULL == piece)
    return false;

  Cell cell(row2, col2);
  vector<Cell> cells = piece->Moves();
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

int Game::WhoseTurn() const
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

  board.PlacePiece(7, 0, new Rook(WHITE));
  board.PlacePiece(7, 1, new Knight(WHITE));
  board.PlacePiece(7, 2, new Bishop(WHITE));
  board.PlacePiece(7, 3, new Queen(WHITE));
  board.PlacePiece(7, 4, new King(WHITE));
  board.PlacePiece(7, 5, new Bishop(WHITE));
  board.PlacePiece(7, 6, new Knight(WHITE));
  board.PlacePiece(7, 7, new Rook(WHITE));
  for (int i = 0; i < 8; i++) { board.PlacePiece(6, i, new Pawn(WHITE)); }

  /* TODO Queens face each other or no? */
  board.PlacePiece(0, 0, new Rook(BLACK));
  board.PlacePiece(0, 1, new Knight(BLACK));
  board.PlacePiece(0, 2, new Bishop(BLACK));
  board.PlacePiece(0, 3, new Queen(BLACK));
  board.PlacePiece(0, 4, new King(BLACK));
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