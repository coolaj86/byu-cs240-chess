#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <assert.h>
#include "ChessDebug.h"

#define INVALID -1;

/*
 * The purpose of this class is to handle the translation
 * of X/Y co-ordinates to the array, including bounds and
 * error handling.
 */
class Square {
public:
	Square(int row, int col);
	Square(const Square & _square);
	~Square();
	//operator =();
	int ToInt() const;
	int Forward(int i);		// These functions bounds check
	int ForwardRight(int i);
	int ForwardLeft(int i);
	int Backward(int i);
	int BackwardRight(int i);
	int BackwardLeft(int i);
	int Left(int i);
	int Right(int i);
	// bool IsSafe(Board *);
	// bool IsConquerable(Board *);
	int Row();
	int Col();
	bool IsValid() const;
	void UnitTest();
private:
	//int color;
	int posX;
	int posY;
	void Init();
	void Copy();
	void Clear();
};
#endif
