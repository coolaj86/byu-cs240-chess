// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
// Contributor:  Students Name
//
// Copyright: For use by the students of CS 240 at BYU
//
//

#include <set>
#include <iostream>
#include "SelectDialog.h"
#include "Chess.h"


Chess::Chess(std::string gladefile):gui(0),logId(0)
{
	Glib::RefPtr<Gnome::Glade::Xml> chessXml = Gnome::Glade::Xml::create(gladefile);
	chessXml->get_widget_derived("Chess_Main",gui);

	gui->signal_cell_selected().connect(sigc::mem_fun(*this,&Chess::on_CellSelected));


	gui->signal_new().connect(sigc::mem_fun(*this,&Chess::on_NewGame));
	gui->signal_save().connect(sigc::mem_fun(*this,&Chess::on_SaveGame));
	gui->signal_save_as().connect(sigc::mem_fun(*this,&Chess::on_SaveGameAs));
	gui->signal_load().connect(sigc::mem_fun(*this,&Chess::on_LoadGame));
	gui->signal_undo().connect(sigc::mem_fun(*this,&Chess::on_UndoMove));
	gui->signal_quit().connect(sigc::mem_fun(*this,&Chess::on_QuitGame));


	gui->signal_drag_start().connect(sigc::mem_fun(*this,&Chess::on_DragStart));
	gui->signal_drag_end().connect(sigc::mem_fun(*this,&Chess::on_DragEnd));

	//Set g_log to print to the message area
	logId = g_log_set_handler(0,
							  GLogLevelFlags(G_LOG_LEVEL_MASK|
											 G_LOG_FLAG_FATAL|
											 G_LOG_FLAG_RECURSION),
							  log_handler,gui);



	//some examples, may be deleted*********

	gui->WriteMessageArea("Ready!");
	gui->WriteMessageArea("Set!\nGo!\n");
	/*gui->WriteMessageArea(
	"Some of the features of the using the GUI are shown as an example.
	They may be viewed and then deleted from the 'Chess' constructor"); */
	gui->SetStatusBar("StatusBar");
	gui->SetTopLabel("Top");
	gui->SetBottomLabel("Bottom");

	gui->PlacePiece(0,0,B_ROOK);
	gui->PlacePiece(7,7,W_ROOK);
	/*
	gui->HighlightSquare(4,4,RED_SQUARE);
	gui->HighlightSquare(4,5,GREEN_SQUARE);
	gui->HighlightSquare(5,4,0xFF00FFAA);   //a one time custom color using hexadecimal
	gui->HighlightSquare(5,5,0xFB9312FF);
	*/
	//***************************************
	//set your init code here***********************************************************




	//**********************************************************************************
}

Chess::~Chess()
{
	//set you clean up code here****



	//******************************
	g_log_remove_handler(0,logId);//remove reference to data
	delete gui;
	gui=0;



}



/********Implement These*****************************/


void Chess::on_CellSelected(int row, int col, int button)
{
	g_debug("Chess::on_CellSelected (%d,%d)",row,col);
	/*
	  Each square of the chess board is reffered to in the GUI code as a cell.
	This Function is called whenever the uses clicks and releases the mous button over
	a cell without initiating a drag. Row and Column coordinates begin in the top left corner.
	The button paramter tells which mouse button was clicked
	(1 for left, 2 for middle, 3 for right).
	You do not need to worry about wich button was used to complete the project.
	*/
}

void Chess::on_DragStart(int row,int col)
{
	g_debug("Chess::on_DragStart (%d,%d)",row,col);
	/*
	  When a drag is initiated, this function will be called instead of on_CellSelected().
	The paramaters row and col are the coordinates of the cell where the drag was initiated.
	All three buttons may initiate the drag, but for our purposes can be treated
	the same and so	that paramater is not included.
	*/
}
bool Chess::on_DragEnd(int row,int col)
{
	g_debug("Chess::on_DragEnd (%d,%d)",row,col);
	/*
	  Same as on_DragStart() except the coordinates represent the ending cell of
	the drag. If the drag terminates off the playing board, this will be called with
	the initial coordinates of the drag.
	*/

	//by convention, this should return a boolean value indicating if the drag was accepted or not.
	return false;
}


void Chess::on_NewGame()
{
	g_debug("Chess::on_NewGame");
	/*
	Called when someone selects 'New' from the toolbar, 'Game' menu, or presses 'Ctrl-N'.
	*/
}

void Chess::on_SaveGame()
{
	g_debug("Chess::on_SaveGame");
	/*
	Called when someone selects 'Save' from the toolbar, 'Game' menu, or presses 'Ctrl-S'.
	*/
}

void Chess::on_SaveGameAs()
{
	g_debug("Chess::on_SaveGameAs");
	/*
	Called when someone selects 'Save As' from the 'Game' menu, or presses 'Shift-Ctrl-S'.
	*/
}
void Chess::on_LoadGame()
{
	g_debug("Chess::on_LoadGame");
	/*
	Called when someone selects 'Open' from the toolbar, 'Game' menu, or presses 'Ctrl-O'.
	*/
}

void Chess::on_UndoMove()
{
	g_debug("Chess::on_UndoMove");
	/*
	Called when someone selects 'Undo' from the toolbar, 'Game' menu, or presses 'Ctrl-Z'.
	*/
}


void Chess::on_QuitGame()
{
	g_debug("Chess::on_QuitGame");
	/*It is not required to implement this function*/

	/*
		Called when someone selects 'Quit' from the toolbar,
		'Game' menu, presses 'Ctrl-Q', or closes the window.<br>

	on_QuitGame() does not need to be implemented to fulfill the
	requirements of the project, but is available for your
	use.
	*/
}





/**********You Do Not Need To Touch These Functions***********************************/


void Chess::run(Gtk::Main & app)
{
	app.run(*gui);
}

std::string format_log(GLogLevelFlags log_level,std::string & message)
{
	//if a level is set in the LOG_LEVEL_HIDE_MASK it will fall through to the
	//default case and so will not be printed
	int level = log_level & (~LOG_LEVEL_HIDE_MASK & G_LOG_LEVEL_MASK);
	std::string output;
	switch(level)
	{
		case G_LOG_LEVEL_DEBUG:
				output = std::string("DEBUG::")+message;
			break;
		case G_LOG_LEVEL_ERROR:
			output = std::string("ERROR::")+message;
			break;
		case G_LOG_LEVEL_CRITICAL:
			output = std::string("CRITICAL::")+message;
			break;
		case G_LOG_LEVEL_WARNING:
			output = std::string("WARNING::")+message;
			break;
		case G_LOG_LEVEL_MESSAGE:
			output = std::string("MESSAGE::")+message;
			break;
		case G_LOG_LEVEL_INFO:
			output = std::string("INFO::")+message;
			break;
		default:
			output="";
	}
	return output;
}

void log_handler(const gchar *log_domain,
				 GLogLevelFlags log_level,
				 const gchar *message, gpointer user_data)
{
    ///@todo Provide more info
	std::string output= std::string(message?message:"");
	bool fatal=false;

	if(log_level & G_LOG_FLAG_FATAL) fatal=true;

	output = format_log(log_level,output);

	if(fatal)
	{
		std::cerr<<"FATAL ERROR::TERMINATING::"<<output<<std::endl;
		exit(1);
	}
	else if(output != "")
	{
		if(user_data)
		{
			//user data must be ChessGui!!!
			static_cast<ChessGui *>(user_data)->WriteMessageArea(output+"\n");
		}
		else
		{
			std::cerr<<output<<std::endl;
		}
	}
	else //do nothing

	return;
}
/**************************************************************************/
