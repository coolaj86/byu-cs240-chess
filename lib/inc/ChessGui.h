// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//

///@file ChessGui.h Toplevel widget of the cs240 %Chess project GUI frontend
///@ingroup chessgui


#ifndef GHESS_GUI_H
#define GHESS_GUI_H

#include <sigc++/sigc++.h>
#include <sigc++/trackable.h>
#include <libglademm.h>
#include <glibmm/refptr.h>

#include <gtkmm/window.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/label.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>

#include "ChessGuiDefines.h"
#include "ChessGuiBoard.h"


///@file cs240chess.glade
///@ingroup chessgui
///File generated using Glade that determines attributes of the GUI look and feel and the
///creation of widgets.


//class: ChessGui
///@brief Toplevel Widget of the CS240 Chess Project.
///
///Signals emitted by this class will be handled by the students in the Chess class.
///
///The exact look and feel of the window depends on
///the file ///See @link cs240chess.glade "" @endlink
///@ingroup chessgui
class ChessGui: public Gtk::Window
{
	private:

		///See @link cs240chess.glade "Glade File" @endlink
		Glib::RefPtr<Gnome::Glade::Xml> chessXml;

		///@name widget access variables
		///allow for quick access to parts of chessXml.  Memory managed by Glade::Xml structure.
		///@{
		Gtk::Statusbar * statusbar;
		Gtk::TextView * messageArea;
		Gtk::ScrolledWindow * messageWindow;
		Gtk::Label * top;
		Gtk::Label * bottom;
		ChessGuiBoard *	board;
		///@}
		///contains position of hpane seperator before last call to HideMessages
		int messageAreaLastPosition;

		///@name signals
		///@{
		sigc::signal<void, int, int, int> cellSelectSignal;
		//sigc::signal<void,ActionType> actionSelectSignal;
		sigc::signal<void> actionNewSignal;
		sigc::signal<void> actionSaveSignal;
		sigc::signal<void> actionSaveAsSignal;
		sigc::signal<void> actionLoadSignal;
		sigc::signal<void> actionUndoSignal;
		sigc::signal<void> actionQuitSignal;
		///@}


	public:
		///This format of constructor is necessary for this constructor to be automatically used
		///by the Glade::Xml::get_derived_widget() function.
		///See @link cs240chess.glade "Glade File" @endlink
		///@param cobject initialize Gtk::Window
		///@param chXml is generated beforehand using libglademm
		ChessGui(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& chXml);

		///Glade::Xml handles destroying Widgets
		~ChessGui();


	   ///@defgroup chessguiconv Chess Gui Convenience Functions
	   ///@ingroup chessgui
	   ///These functions allow for a simple use of the ChessGui interface.

	   ///@name Chess Gui Convenience Functions
	   ///@{

		///Place text in area above the chess board
		///@ingroup chessguiconv
		///@param text
		void SetTopLabel(const std::string & text);
		///Place text in area below the chess board
		///@ingroup chessguiconv
		///@param text
		void SetBottomLabel(const std::string & text);

		///Clear all data in the Message Area
		///@ingroup chessguiconv
		void ClearMessageArea();
		///Write a string to the Message Area
		///@ingroup chessguiconv
		///@param message
		void WriteMessageArea(const std::string & message);

		///Set text in the Statusbar located at the bottom of the ChessGui
		///@ingroup chessguiconv
		///@param status
		void SetStatusBar(const std::string & status);

		///Opens a Gtk::FileChooserDialog in the FILE_SAVE mode
		///@ingroup chessguiconv
		///@return Path to the file selected
		std::string SelectSaveFile();
		///Opens a Gtk::FileChooserDialog in the FILE_OPEN mode
		///@ingroup chessguiconv
		///@return Path to the file selected
		std::string SelectLoadFile();


		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		///@param color RRGGBBAA hexadecimal value see @link ChessGuiDefines.h @endlink
		void HighlightSquare(signed int row,signed int col,guint32  color);

		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		void UnHighlightSquare(signed int row,signed int col);

		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		///@param piece valid piece as define in ImageName
		void PlacePiece(signed int row,signed int col, ImageName piece);

		///@ingroup chessguiconv
		///@param row 0 <= row < NUM_COL, top to bottom
		///@param col  0 <= row < NUM_COL, left to right
		void ClearPiece(signed int row,signed int col);
	   ///@}


		///Overides Gtk::Window::on_main_delete_event
		///Use if needed for last minute cleanup
		bool on_main_delete_event(GdkEventAny* event);

		///@name Signal Accessor Functions
		///@{

		///emited when a butten is pressed over a square
		///@note If the button 1 is pressed and a drag is initiated,
		///signal will only be emitted if the drage terminates in the same square
		///@note signal handler has form void on_cell_selected(int row, int col, int button);
		sigc::signal<void, int, int, int> signal_cell_selected();

		///Emited when New Game is selected
		sigc::signal<void> signal_new();

		///Emited when Save Game is selected
		sigc::signal<void> signal_save();

		///Emited when Save Game As is selected
		sigc::signal<void> signal_save_as();

		///Emited when Load Game is selected
		sigc::signal<void> signal_load();

		///Emited when Undo Move is selected
		sigc::signal<void> signal_undo();

		///Emited when Quit Game is selected
		sigc::signal<void> signal_quit();


		///emited when button 1 is pressed, held, and then the mouse is moved
		///@note signal handler has the form void on_drag_start(int startRow, int endRow);
		sigc::signal<void, int, int> signal_drag_start();
		///emited after a drag has been initiated and the button has been released
		///@note signal handler has the form bool on_drag_end(int endRow, int endCol);
		///@note signal handler should return false if drag was invalid
		sigc::signal<bool, int, int> signal_drag_end();
		///@}




	private:

		///@name Initialization sub-functions
		///@{

		void ConnectSignals();
		void ConnectMenuSignals();
		void ConnectToolBarSignals();
		///@}

		///@name Internal Signal Handlers
		///@{
		void on_UndoMove();
		void on_NewGame();
		void on_LoadGame();
		void on_SaveGame();
		void on_SaveGameAs();
		void on_LoadImages();
		void on_Quit();
		void on_HideMessages();
		void on_ClearMessages();
                void on_About();
		void on_ToggleToolbarView();
		///@}

};


#endif
