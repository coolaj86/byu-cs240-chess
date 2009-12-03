/*
 * Piece.cpp
 *
 *  Created on: Mar 29, 2009
 *      Author: coolaj86
 */

#include "Piece.h"

  Piece::Piece(PieceColor _color) :
    type(PAWN)
  {
    assert (WHITE == _color || BLACK == _color);
    color = _color;
  }
  Piece * Piece::Clone()
  {
    throw new exception();
    return NULL;
  }

  Piece::~Piece() {
    return;
  }

  PieceName Piece::Name() const {
    return (PieceName) (type + color);
  }

  PieceType Piece::Type() const {
    return type;
  }

  PieceColor Piece::Color() const {
    return color;
  }

  std::string Piece::TypeString() const {
    switch (type)
    {
      case PAWN:
        return "pawn";
        break;
      case ROOK:
        return "rook";
        break;
      case BISHOP:
        return "bishop";
        break;
      case KNIGHT:
        return "knight";
        break;
      case KING:
        return "king";
        break;
      case QUEEN:
        return "queen";
        break;
      case NO_TYPE:
        break;
    }
    return string("error");
  }

  std::string Piece::ColorString() const {
    switch (color)
    {
      case WHITE:
        return std::string("white");
         break;
      case BLACK:
        return std::string("black");
        break;
      case NO_COLOR:
        break;
    }
    return string("error");
  }

  Piece * Piece::Create(PieceType type, PieceColor color)
  {
    return Create(type, color, -1, -1);
  }

  Piece * Piece::Create(PieceType type, PieceColor color, int row, int col)
  {
    Piece * piece;
    switch (type)
    {
      case PAWN:
        piece = new Pawn(color);
        break;
      case ROOK:
        piece = new Rook(color);
        break;
      case KNIGHT:
        piece = new Knight(color);
        break;
      case BISHOP:
        piece = new Bishop(color);
        break;
      case KING:
        piece = new King(color);
        break;
      case QUEEN:
        piece = new Queen(color);
        break;
      case NO_TYPE:
        throw new exception();
        break;
    }
    piece->UpdateLocation(row, col);
    return piece;
  }

  Piece * Piece::FromString(std::string piece_str)
  {
    string::const_iterator piece_begin = piece_str.begin();
    string::const_iterator piece_end = piece_str.end();

    boost::match_results<string::const_iterator> matches;

    boost::regex
      //piece_re("<\\s*piece.*?\\/>", boost::regex::perl|boost::regex::icase),
      row_re("row\\s*=\\s*(['\"]?)(.*?)\\1", boost::regex::perl|boost::regex::icase),
      col_re("column\\s*=\\s*(['\"]?)(.*?)\\1", boost::regex::perl|boost::regex::icase),
      color_re("color\\s*=\\s*(['\"]?)(.*?)\\1", boost::regex::perl|boost::regex::icase),
      type_re("type\\s*=\\s*(['\"]?)(.*?)\\1", boost::regex::perl|boost::regex::icase);

    if (!(regex_search(piece_begin, piece_end, matches, type_re)))
      { std::cout << "error parsing piece" << std::endl; return NULL; }
    std::string type_str = matches[2];

    if (!(regex_search(piece_begin, piece_end, matches, color_re)))
      { std::cout << "error parsing piece" << std::endl; return NULL; }
    std::string color_str = matches[2];

    if (!(regex_search(piece_begin, piece_end, matches, row_re)))
      { std::cout << "error parsing piece" << std::endl; return NULL; }
    std::string row = matches[2];

    if (!(regex_search(piece_begin, piece_end, matches, col_re)))
      { std::cout << "error parsing piece" << std::endl; return NULL; }
    std::string col = matches[2];

  PieceColor color = (color_str == "white") ? WHITE : BLACK;

  PieceType type = NO_TYPE;
  type = (type_str == "pawn") ? PAWN : type;
  type = (type_str == "rook") ? ROOK : type;
  type = (type_str == "bishop") ? BISHOP : type;
  type = (type_str == "knight") ? KNIGHT : type;
  type = (type_str == "king") ? KING : type;
  type = (type_str == "queen") ? QUEEN : type;

  return Create(type, color, atoi(row.c_str()), atoi(col.c_str()));
  }

  std::string Piece::ToString() const {
    std::stringstream xml;
    xml << "<piece ";
    xml << "type=\"" << TypeString() << "\" ";
    xml << "color=\"" << ColorString() << "\" ";
    xml << "column=\"" << col << "\" ";
    xml << "row=\"" << row << "\" ";
    xml << "/>";
    return xml.str();
  }

  void Piece::UpdateLocation(int _row, int _col)
  {
    row = _row;
    col = _col;
  }
  void Piece::UpdateLocation(Cell const& other)
  {
    row = other.row;
    col = other.col;
  }

  Cell Piece::Location()
  {
    return Cell(row, col);
  }

  bool Piece::CouldTake(Cell cell)
  {
    std::vector<Cell> moves = Moves();
    for (int i = 0; i < moves.size(); i++)
    {
      if (moves[i] == cell) { return true; }
    }
    return false;
  }

  std::vector<Cell> Piece::Moves()
  {
    return std::vector<Cell>();
  }

  void Piece::_cells_advancing(std::vector<Cell>& cells, int _row, int _col)
  {
    Cell cell(row + _row, col + _col);
    //std::cout << "cells advance (" << cell.row << "," << cell.col << ")" << std::endl;
    while (board->ValidCell(cell) && NULL == board->PieceAt(cell))
    {
      //std::cout << "valid (" << cell.row << "," << cell.col << ")" << std::endl;
      cells.push_back(cell);
      cell.row += _row;
      cell.col += _col;
      //std::cout << "????? (" << cell.row << "," << cell.col << ")" << std::endl;
    }
    if (board->ValidCell(cell) && board->PieceAt(cell)->Color() != this->color)
    {
      //std::cout << "attackable (" << cell.row << "," << cell.col << ")" << std::endl;
      cells.push_back(cell);
    }
  }

  void Piece::_cell_advancing(std::vector<Cell>& cells, int _row, int _col)
  {
    Cell cell(row + _row, col + _col);
    if (board->ValidCell(cell) && (NULL == board->PieceAt(cell) || board->PieceAt(cell)->Color() != this->color))
    {
      cells.push_back(cell);
    }
  }

/*
  static bool Piece::UnitTest() {
    TEST(Piece * piece = new Piece(BLACK));
    TEST(delete piece && piece = new Piece(WHITE));
    TEST(piece->Name());
  }
*/
