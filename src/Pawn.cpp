#include "Pawn.h"

	Pawn::Pawn(PieceColor color) : 
    Piece::Piece(color)
  {
  }
  Pawn::~Pawn()
  {
  }

	/* A pawn can only move forward into a null spot on the board */
	/*Set<Square> Pawn::Moves(const Board board, Square _square) {
		Square square();
		Set<Square> result;
		square = _square;
		while (!board[square.ToInt()]) {
			if ( square = square.Forward(color))
				result.Add(square);
		}

		square = _square;
		while (!board[square.ToInt()]) {
			if ( square = square.Down())
				result.Add(square);
		}

		square = _square;
		if (firstMove) {
			if (!board[(square = square.Forward(color)).ToInt()] 
				&& !board[(square = square.Forward(color)).ToInt()])
				result.Add(square);
		}

		result.Add(Attack())
		return result;
	}
  */
	/* A pawn can only attack a forward-facing diagonal foe  */
  /*
	Set<Square> Pawn::Attack(Square _square) {
		Square square();
		Set<Square> result;

		square = _square;
		square = square.Forward(color);
		square = square.Right(color);
		if (board[square.ToInt()].IsFoe(color))
			result.Add(square);

		square = _square;
		square = square.Forward(color);
		square = square.Left(color);
		if (board[square.ToInt()].IsFoe(color))
			result.Add(square);
	}
  */
