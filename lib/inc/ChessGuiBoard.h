// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//
///@file ChessGuiBoard.h  Midlevel container widget for the CS 240 %Chess project GUI.
///@ingroup chessgui
#ifndef CHESS_GUI_BOARD_H
#define CHESS_GUI_BOARD_H

#include <sigc++/sigc++.h>

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include <libglademm.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/aspectframe.h>

#include <vector>
#include <string>
#include "ChessGuiDefines.h"
#include "ChessGuiBoardCell.h"

class ChessGui;

///@ingroup chessgui
///ChessGuiBoard is a data structure for manipulating a 2d array of ChessGuiBoardCell.
///It's  functionality is completely wrapped inside of the ChessGui class and so never
///needs to be accessed directly by the student
///@note Depends heavily on cs240chess.glade
class ChessGuiBoard : public Gtk::AspectFrame
{
	private:

		///Current width of the AspectFrame as assigned by the parent widget
		int width;
		///Current height of the AspectFrame  as assigned by the parent widget
		int height;
		///row of the last cell that activated a button_pressed event.
		///Used for drag and drop/cell selection
		int curCellRow;
		///col of the last cell that activated a button_pressed event.
		///Used for drag and drop/cell selection
		int curCellCol;
        ///indicates wether a drag has been initiated.
		///Prevents emission of both dragEnd and  cellSelect signals
		bool dragStarted;

		ChessGuiBoardCell * board[NUM_ROW][NUM_COL];


		///@name signals
		///@{
		sigc::signal<void, int, int, int> cellSelectSignal;
		sigc::signal<void, int, int> dragStartSignal;
		sigc::signal<bool, int, int> dragEndSignal;
		///@}


	public:
		///This format of constructor is necessary for this constructor to be automatically used
		///by the Glade::Xml::get_derived_widget() function.
		///See @link cs240chess.glade "Glade File" @endlink
		///@param cobject initialize Gtk::Window
		///@param refGlade is generated beforehand using libglademm
		ChessGuiBoard(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
		///Glade::Xml handles destroying Widgets
		~ChessGuiBoard();

		///@param width total width (of all cells) of the board
		///@param height total height (of all cells) of the board
		void ResizeBoard(int width,int height);
		///UpdateImage for each cell in board
		void RefreshBoard();



		///@name Cell Manipulation
		///@{

		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		///@param color RRGGBBAA hexadecimal value see @link ChessGuiDefines.h @endlink
		void HighlightSquare(signed int row,signed int col,guint32  color);

		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		void UnHighlightSquare(signed int row,signed int col);

		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		///@param piece valid piece as define in ImageName
		void PlacePiece(signed int row,signed int col, ImageName piece);

		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		void ClearPiece(signed int row,signed int col);
		///@}

		///@name Signal Accessors
		///@{

		///emited when a butten is pressed over a square
		///@note If the button 1 is pressed and a drag is initiated,
		///signal will only be emitted if the drage terminates in the same square
		///@note signal handler has form void on_cell_selected(int row, int col, int button);
		sigc::signal<void, int, int, int> signal_cell_selected();

		///emited when button 1 is pressed, held, and then the mouse is moved
		///@note signal handler has the form void on_drag_start(int startRow, int endRow);
		sigc::signal<void, int, int> signal_drag_start();

		///emited after a drag has been initiated and the button has been released
		///@note signal handler has the form bool on_drag_end(int endRow, int endCol);
		///@note signal handler should return false if drag was invalid
		///@note if the drag is terminated outside of the playing area,
		///the intial squares coordinates are returned
		sigc::signal<bool, int, int> signal_drag_end();
		///@}

	private:

		///@name Internal Signal Handlers
		///@todo Make sure drag and on_button_released don't cause conflicting signals
		///@{

		///Connected to the signal_size_allocate emmited by an EventBox containing this widget
		void on_board_size_allocate(Gtk::Allocation& allocation);

		///Emits signal_cell_selected if a drag hasn't been initiated and then
		///terminated outside of this square
		bool on_button_released(GdkEventButton* event,int row,int col);


		bool on_button_pressed(GdkEventButton* event,int row,int col);

		void on_cell_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context,
								int row,
								int col);

		bool on_cell_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context,
							   int x,
							   int y,
							   guint time,
							   int row,
							   int col);

		void on_cell_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context,
								guint time,
								int row,
								int col);

		bool on_cell_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context,
								 int x,
								 int y,
								 guint time,
								 int row,
								 int col);
		///@}


		///Generates a string using the name scheme ("ChessBoard_Row%d_Col%d", row,col)
		///Used in retrieving widgets from refGlade
		///@param row 1-8
		///@param col 1-8
		static std::string GenStringName(int row,int col);

		void InitCell(const Glib::RefPtr<Gnome::Glade::Xml> & chessXml,int row,int col);
		void ConnectCellSignals(ChessGuiBoardCell * cell, Gtk::EventBox * eb,int row,int col);

};

#endif
