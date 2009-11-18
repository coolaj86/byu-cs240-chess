// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//
///@file Chess.h Interface for the Chess class
///@ingroup backend

#ifndef CHESS_H
#define CHESS_H


#include <string>
#include <vector>
#include <map>
#include <glibmm/refptr.h>
#include <libglademm.h>
#include <sigc++/sigc++.h>
#include <gtkmm/main.h>

#include "ChessGuiDefines.h"
#include "ChessGui.h"


///@def LOG_LEVEL_HIDE_MASK
///@brief Set the log levels (using the Glib log levels)
///that will be ignored by the Chess logging function.
///
///This mask will hide messages from being displayed in the ChessGui message box,
///it will not prevent them from being sent to the command line when not using
///the GUI.  Set this flag at compile time using
///the compiler directive -D and OR-ed values of the Glib log levels. For example:
///@code
///g++ -g -o Chess.o (options) -DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO) Chess.cpp
///@endcode
///will prevent debug and info messages from being displayed.
#ifndef LOG_LEVEL_HIDE_MASK
#define LOG_LEVEL_HIDE_MASK (0)
#endif


//add you defines here*****************************************************************************



///@brief This class is the main interface between the Students code and the provided GUI
///
///The Student will implement each of the signal handlers found in this class.
///It is permitted to add member data and functions.
//The constructor and the destructor should be finished to suit the needs
///of the student.
///@note Access the @link chessguiconv convenience functions @endlink
///using the pointer Chess::gui
///@ingroup backend
class Chess
{
	private:

		///Access to the user interface
		ChessGui * gui;
		///Log-id (for memory management)
		guint logId;


		///@name Add your variables here
		///@{

		///@}

	public:
		///@param gladefile See @link cs240chess.glade "Glade File" @endlink
		Chess(std::string gladefile);
		~Chess();

		///allows Gtk::Main to handle showing and hiding the window on exit
		void run(Gtk::Main & app);

		///@name Student Implemented Functions
		///@{

		///Connected to (activated by) ChessGui::signal_cell_selected()
		///@param row 1-8, top to bottom
		///@param col 1-8, left to right
		///@param button 1=left mouse button, 2=middle mouse button, 3=right mouse  button
		void on_CellSelected(int row, int col, int button);


		///Connected to (activated by) ChessGui::signal_new_selected()
		void on_NewGame();

		///Connected to (activated by) ChessGui::signal_save_selected()
		void on_SaveGame();

		///Connected to (activated by) ChessGui::signal_save_as_selected()
		void on_SaveGameAs();

		///Connected to (activated by) ChessGui::signal_load_selected()
		void on_LoadGame();

		///Connected to (activated by) ChessGui::signal_undo_selected()
		void on_UndoMove();

		///Connected to (activated by) ChessGui::signal_quit_selected()
		void on_QuitGame();


		///@param row where drag began
		///@param col where drag began
		void on_DragStart(int row,int col);

		///@param row where drag ended
		///@param col where drag ended
		///@return true if the drag resulted in a successful drop
		bool on_DragEnd(int row,int col);
		///@}
	private:
		///@name Add your functions here
		///@{


		///@}

};

///Log handler to be set to g_log
///user_data must be a valid pointer to an initiated ChessGui
void log_handler(const gchar *log_domain,
				 GLogLevelFlags log_level,
				 const gchar *message, gpointer user_data);


#endif
