#ifndef _CELL_H_
#define _CELL_H_

/* Because it's faster that learning to use structs. The end */
class Cell
{
  public:
    Cell();
    Cell(int row, int col);
    ~Cell();

    int row;
    int col;
};

#endif