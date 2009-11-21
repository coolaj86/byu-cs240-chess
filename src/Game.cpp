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
  NewGame();
}

Game::~Game() {
  _clear();
}
void Game::_clear()
{
}

void Game::NewGame() {
  //board = Board(); 					// done by constructor
  //history = vector<Move>;
  whose_turn = WHITE;
  _init_pieces();
}

vector<Cell> Game::WhereCanPieceMoveFrom(int row, int col)
{
  cout << "WhereCanPieceMoveFrom" << endl;
  // TODO limit
  vector<Cell> cells;
  for (int i = 2; i < 6; i++)
    for (int j = 2; j < 6; j++)
      cells.push_back(Cell(i,j));
  return cells;
  cout << "WhereCanPieceMoveFrom End" << endl;
}

bool Game::MoveFromTo(int row1, int col1, int row2, int col2)
{
  // TODO limit
  board.MoveFromTo(row1, col1, row2, col2);
  whose_turn = (whose_turn == WHITE) ? BLACK : WHITE;
  return true;
}

int Game::WhoseTurn() const
{
  return whose_turn;
}

bool Game::HasTurn(int row, int col) const
{
    return (whose_turn == WhatColorIsAt(row, col));
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
  Piece& piece = board.PieceAt(row, col);
  if (NULL != &piece)
    return piece.Name();
  else
    return NO__PIECE;
}

void Game::Undo()
{
  //board.undo
}

void Game::Save(string filename)
{
  // loop through
}

void Game::Load(string filename)
{
  // loop through
}

ImageName Game::_convert_piece_to_image_name(const PieceName piece) const
{
  switch(piece) {
  case NO__PIECE:
    return NO_IMAGE;

  case B__ROOK:
    return B_ROOK;
  case B__KNIGHT:
    return B_KNIGHT;
  case B__BISHOP:
    return B_BISHOP;
  case B__QUEEN:
    return B_QUEEN;
  case B__KING:
    return B_KING;
  case B__PAWN:
    return B_PAWN;

  case W__ROOK:
    return W_ROOK;
  case W__KNIGHT:
    return W_KNIGHT;
  case W__BISHOP:
    return W_BISHOP;
  case W__QUEEN:
    return W_QUEEN;
  case W__KING:
    return W_KING;
  case W__PAWN:
    return W_PAWN;

  default:
    return NO_IMAGE;
  }
}

ImageName Game::WhatPieceIsAt(int row, int col) const
{
  assert((row > BLACK_START && row < BLACK_END)
      || (row < WHITE_START && row > WHITE_END));
  return _convert_piece_to_image_name(PieceNameAt(row, col));
}

PieceColor Game::WhatColorIsAt(int row, int col) const
{
  // if NO_PIECE return NO_PIECE
  // return (P_WHITE & board.PieceNameAt(row, col)) ? WHITE : BLACK
  switch(PieceNameAt(row, col)) {
  case NO__PIECE:
    return NO_COLOR;

  case B__ROOK:
  case B__KNIGHT:
  case B__BISHOP:
  case B__QUEEN:
  case B__KING:
  case B__PAWN:
    return _BLACK_;

  case W__ROOK:
  case W__KNIGHT:
  case W__BISHOP:
  case W__QUEEN:
  case W__KING:
  case W__PAWN:
    return _WHITE_;

  default:
    return NO_COLOR;
  }
  return NO_COLOR;
}

PieceType Game::WhatTypeIsAt(int row, int col) const
{
  switch(PieceNameAt(row, col)) {
  case NO__PIECE:
    return NO_TYPE;

  case B__ROOK:
  case W__ROOK:
    return ROOK;

  case B__KNIGHT:
  case W__KNIGHT:
    return KNIGHT;

  case B__BISHOP:
  case W__BISHOP:
    return BISHOP;

  case B__QUEEN:
  case W__QUEEN:
    return QUEEN;

  case B__KING:
  case W__KING:
    return KING;

  case B__PAWN:
  case W__PAWN:
    return PAWN;

  default:
    return NO_TYPE;
  }
  return NO_TYPE;
}