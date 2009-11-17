#ifndef _FACADE_H_
#define _FACADE_H_

#include <stdlib.h>
#include <assert.h>

#include "ChessGuiDefines.h"
#include "Board.h"
#include "Square.h"

class Facade {
public:
	Facade();
	~Facade();
	//void operator =();
	void NewGame();					// calls Clear, Init on all classes
	ImageName const ImageAt(int row, int col);
	/*const Move * Undo();				// Pops history and recreates board
	void Save(const string filename);		// Writes history to xml
	void SaveAs(const string _filename);		// Accepts name and passes along
	void Load(ostream * file);			// Undo first from history
	const Set<Move> * GetMoves(Square &);		// Finds piece, returns moves
	const Board * Move(Square & to, Square & from);	// From, To
	*/
	void UnitTest();
private:
	Board * board;
	/*
	string filename;
	MoveHistory * history;
	*/
	void Init();
	void Copy();
	void Clear();
	ImageName PieceToImageName(const PieceName piece) const;
};
#endif
