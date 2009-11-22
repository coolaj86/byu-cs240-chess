#ifndef _CELL_H_
#define _CELL_H_

/* Because it's faster that learning to use structs. The end */
class Cell
{
  public:
    Cell();
    Cell(Cell const&);
    Cell(int row, int col);
    ~Cell();

    Cell& operator=(Cell const&);
    bool operator==(Cell const&) const;

    int row;
    int col;

  private:
    void _init();
    void _clear();
    void _copy(Cell const&);
};

#endif