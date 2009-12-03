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
  vector<Cell> moves;

  Piece* piece = board.PieceAt(row, col);
  if (NULL == piece)
    return moves;

  Cell location = piece->Location();
  moves = piece->Moves();

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

bool Game::MoveFromTo(Cell from, Cell to)
{
  return MoveFromTo(from.row, from.col, to.row, to.col);
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

void Game::Save(ostream& xml)
{
  xml << "<chessgame>" << endl;
  xml << "\t<board>" << endl;
  Piece * piece;
  for (int _row = 0; _row < 8; _row++)
  {
    for (int _col = 0; _col < 8; _col++)
    {
      Cell cell = Cell(_row, _col);
      if ((piece = board.PieceAt(cell)))
      {
        xml << "\t\t" << piece->ToString() << endl;
      }
    }
  }
  xml << "\t</board>" << endl;
  xml << "\t<history>" << endl;
  for (int i = 0; i < board.history.size(); i++)
  {
    xml << "\t\t<move>" << endl;
    vector< Piece* > pieces = board.history[i];
    xml << "\t\t\t" << pieces[0]->ToString() << endl;
    xml << "\t\t\t" << pieces[1]->ToString() << endl;
    if (3 == pieces.size()) // opponent
    {
      xml << "\t\t\t" << pieces[2]->ToString() << endl;;
    }
    xml << "\t\t</move>" << endl;
  }
  xml << "\t</history>" << endl;
  xml << "</chessgame>" << endl;
}

void Game::Load(istream& xml)
{
  board.Clear();
  //http://www.gskinner.com/RegExr/
  std::string str((std::istreambuf_iterator<char>(xml)), std::istreambuf_iterator<char>());

  // remove excessive whitespace
  boost::regex ws_re("[\\s\n\r]+");
  str = regex_replace(str, ws_re, " ");

  // remove carrot whitespace
  ws_re = boost::regex("<\\s+");
  str = regex_replace(str, ws_re, "<");
  ws_re = boost::regex("</\\s+");
  str = regex_replace(str, ws_re, "</");
  ws_re = boost::regex("\\s+>");
  str = regex_replace(str, ws_re, ">");

  string::const_iterator begin;
  string::const_iterator end;

  boost::regex
    board_re("<\\s*chessgame\\s*>.*?<\\s*board\\s*>(.*?)</\\s*board>.*?</\\s*chessgame\\s*>",
      boost::regex::perl|boost::regex::icase),
    history_re("<\\s*chessgame\\s*>.*?<\\s*history\\s*>(.*?)</\\s*history>.*?</\\s*chessgame\\s*>",
      boost::regex::perl|boost::regex::icase),
    move_re("<\\s*move\\s*>(.*?)</\\s*move\\s*>", boost::regex::perl|boost::regex::icase),
    piece_re("<\\s*piece.*?\\/>", boost::regex::perl|boost::regex::icase);

  boost::match_results<string::const_iterator> matches;

  begin = str.begin();
  end = str.end();
  if (!(regex_search(begin, end, matches, board_re)))
  {
    std::cout << "didn't find board" << endl;
    return;
  }
  std::string board_str = matches[1];

  std::string history_str;
  if (regex_search(begin, end, matches, history_re))
  {
    history_str = matches[1];
  }
  else
  {
    std::cout << "did find history" << endl;
  }
  str.clear();


  // TODO make function
  begin = board_str.begin();
  end = board_str.end();
  if (!(regex_search(begin, end, matches, piece_re)))
  {
    std::cout << "didn't find pieces" << endl;
    return;
  }
  while (regex_search(begin, end, matches, piece_re))
  {
    std::string piece_str = matches[0];
    //std::cout << "found piece " << piece_str << endl;

    Piece * piece = Piece::FromString(piece_str);

    board.PlacePiece(piece);
    begin = matches[0].second;
  }

  // TODO make function
  begin = history_str.begin();
  end = history_str.end();
  if (!(regex_search(begin, end, matches, move_re)))
  {
    std::cout << "didn't find moves\n" << history_str << endl;
    return;
  }
  while (regex_search(begin, end, matches, move_re))
  {
    std::string move_str = matches[0];
    std::cout << "found move " << endl;

    std::vector<Piece *> move;
    boost::match_results<string::const_iterator> piece_matches;
    string::const_iterator move_begin = move_str.begin();
    string::const_iterator move_end = move_str.end();
    while (regex_search(move_begin, move_end, piece_matches, piece_re))
    {
      std::string piece_str = piece_matches[0];
      std::cout << "found moving piece: " << piece_str << endl;
      move.push_back(Piece::FromString(piece_str));
      move_begin = piece_matches[0].second;
    }

    board.history.push_back(move);
    begin = matches[0].second;
  }
  if (board.history.size() > 0)
  {
    whose_turn = board.history[board.history.size()-1][0]->Color() == WHITE ? BLACK : WHITE;
  }
}

PieceName Game::WhatPieceIsAt(int row, int col) const
{
  assert((row > BLACK_START && row < BLACK_END)
      || (row < WHITE_START && row > WHITE_END));
  return PieceNameAt(row, col);
}
