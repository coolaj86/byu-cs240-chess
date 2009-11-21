#include "King.h"

	King::King(int color) : 
    Piece::Piece(color)
  {
  }
  King::~King()
  {
  }

	/* A king can move in any direction to a null spot on the board where he cannot be attacked*/
/*
	Set<Square> King::Moves(const Board board, Square _square) {
		_square.GoTeam(color);
		Square square();
		Set<Square> result;
		
		if  	 ( square = _square.Forward()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if       ( square = _square.Forward()
			&& square = square.Right()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if  	 ( square = _square.Right()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if       ( square = _square.Backward()
			&& square = square.Right()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if  	 ( square = _square.Backward()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if       ( square = _square.Backward()
			&& square = square.Left()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if       ( square = _square.Left()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if       ( square = _square.Left()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		if       ( square = _square.Forward()
			&& square = square.Left()
			&& square.IsSafe() 
			&& square.IsConquerable() )
			result.Add(square);
		return result;
	}
*/
