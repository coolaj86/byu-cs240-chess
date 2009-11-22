#include "Cell.h"

  Cell::Cell() :
    row(-1), col(-1)
  {
    return;
  }
  Cell::Cell(int row, int col) :
    row(row), col(col)
  {
    return;
  }
  Cell::Cell(Cell const& other)
  {
    _copy(other);
    return;
  }
  Cell& Cell::operator=(Cell const& other)
  {
    _copy(other);
    return *this;
  }
  void Cell::_copy(Cell const& other)
  {
    row = other.row;
    col = other.col;
  }


  Cell::~Cell()
  {
    return;
  }

  bool Cell::operator==(Cell const& other) const
  {
    return (row == other.row) && (col == other.col);
  }