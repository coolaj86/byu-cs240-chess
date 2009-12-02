#include "Pawn.h"

  Pawn::Pawn(PieceColor color) :
    Piece::Piece(color)
  {
  }
  Piece * Pawn::Clone()
  {
    Pawn * pawn = new Pawn(color);
    pawn->type = type;
    pawn->row = row;
    pawn->col = col;
    pawn->board = board;
    return (Piece *) pawn;
  }
  Pawn::~Pawn()
  {
  }

  /*
   * Pawn can move forward if no piece is in front of it
   * or diagonal
   */
  std::vector<Cell> Pawn::Moves()
  {
    std::vector<Cell> cells;
    Cell origin = Cell(row, col);
    Cell cell = origin;
    Piece* piece;

    cell.row += color;
    if (board->ValidCell(cell) && NULL == board->PieceAt(cell)) {
      cells.push_back(cell);
      if (row == 1 || row == 6)
      {
        if (!(board->PieceAt(cell)))
        {
          cell.row += color;
          if (!(board->PieceAt(cell))) {
            cells.push_back(cell);
          }
        }
      }
    }

    cell = origin;
    cell.row += color;
    cell.col += 1;
    piece = board->PieceAt(cell);
    if (board->ValidCell(cell) && NULL != piece && piece->Color() != color)
    {
        cells.push_back(cell);
    }

    cell = origin;
    cell.row += color;
    cell.col -= 1;
    piece = board->PieceAt(cell);
    if (board->ValidCell(cell) && NULL != piece && piece->Color() != color)
    {
        cells.push_back(cell);
    }

    return cells;
  }
