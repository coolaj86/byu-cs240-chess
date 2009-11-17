// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//
#ifndef CHESS_GUI_DEFINES_H
#define CHESS_GUI_DEFINES_H

/**@file ChessGuiDefines.h
   @brief Collection of defines and enums used in the BYU CS240 class Chess project
   @ingroup chessgui
 
*/


///@def CELL_PAD 
///@brief Pixel pad to make sure that no gaps appear between board cells
///@todo Modify code so that this is not needed OR is only used by the background layer
///@ingroup chessgui
#define CELL_PAD 10

///@def NUM_ROW
///@brief Number of rows on a chess board
///@ingroup chessgui
#define NUM_ROW 8

///@def NUM_COL
///@brief Number of columns on a chess board
///@ingroup chessgui
#define NUM_COL 8

///@def DEFAULT_CELL_SIZE
///@brief Default size of a square(cell) on the chess board
///@ingroup chessgui
#define DEFAULT_CELL_SIZE 50

///@def DEFAULT_BOARD_WIDTH
///@brief Calculated default width of a chess board
///@ingroup chessgui
#define DEFAULT_BOARD_WIDTH (DEFAULT_CELL_SIZE * NUM_COL)

///@def DEFAULT_BOARD_HEIGHT
///@brief Calculated default height of a chess board
///@ingroup chessgui
#define DEFAULT_BOARD_HEIGHT (DEFAULT_CELL_SIZE * NUM_ROW)


///Used in setting graphics to various layer of a ChessGuiBoardCell.
/// Layers are rendered in ascending order.
///@ingroup chessgui
enum CellLayer{BACK_GRND_LAYER =0,TILE_LAYER=1,HIGHLIGHT_LAYER=2,PIECE_LAYER=3,MAX_LAYER=4};


///For dynamically accessing image files and placeing pieces on the board
///@ingroup chessgui
enum ImageName{NO_IMAGE=0,BACK_GRND=1,
		WHITE_TILE=2,BLACK_TILE=3,
		W_PAWN=4,B_PAWN=5,
		W_ROOK=6,B_ROOK=7,
		W_KNIGHT=8,B_KNIGHT=9,
		W_BISHOP=10,B_BISHOP=11,
		W_KING=12,B_KING=13,
		W_QUEEN=14,B_QUEEN=15,
		NUM_IMAGE_NAMES=16};

///@def TILE_ALPHA
///@brief Default opacity of tile pattern
///@ingroup chessgui
#define TILE_ALPHA 0xb5

///@def BITS_PER_SAMPLE
///@brief Used for creating Gdk::Pixbuf
///@ingroup chessgui
#define BITS_PER_SAMPLE 8
		
///@defgroup colors Highlight Colors
///@ingroup chessgui
///Colors follow the format 0xRRGGBBAA
///Highlight colors are  slightly transparent.
///You may define more colors
///@{
///@def CLEAR_SQUARE
///@def WHITE_SQUARE	
///@def BROWN_SQUARE	
///@def BLACK_SQUARE
///@def RED_SQUARE	
///@def GREEN_SQUARE	
///@def BLUE_SQUARE
///@def YELLOW_SQUARE	
///@}
#define CLEAR_SQUARE  0xffffff00
#define WHITE_SQUARE  0xffffff66    
#define BROWN_SQUARE  0x804000AA
#define BLACK_SQUARE  0x000000AA
#define RED_SQUARE    0xff0000AA
#define GREEN_SQUARE  0x00ff00AA
#define BLUE_SQUARE   0x0000ffAA
#define YELLOW_SQUARE 0xffff00AA




#endif
