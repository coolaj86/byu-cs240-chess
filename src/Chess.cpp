// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
// Contributor:  Students Name
//
// Copyright: For use by the students of CS 240 at BYU
//
//

#include <iostream>

#include "SelectDialog.h"
#include "Chess.h"

using namespace std;

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
  logId = g_log_set_handler(0,GLogLevelFlags(G_LOG_LEVEL_MASK| G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION),log_handler,gui);


  //***************************************
  //set your init code here***********************************************************

  _init();

  //**********************************************************************************

}
void Chess::_init()
{
  _deselect_piece();
  gui->WriteMessageArea("Ready!\n");
  gui->WriteMessageArea("Set!\nGo!\n");
  gui->SetTopLabel("Black");
  gui->SetBottomLabel("White");
  _update_board();
}

Chess::~Chess()
{
  //set you clean up code here****

  // That was easy...

  //******************************
  g_log_remove_handler(0,logId);//remove reference to data
  delete gui;
  gui=0;



}


void Chess::_update_board()
{
  // TODO have the board switch sides based on color
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      gui->UnHighlightSquare(row, col);
      gui->ClearPiece(row, col);
      gui->PlacePiece(row, col, _to_image_name(game.WhatPieceIsAt(row, col)));
      /*
      if (NULL == game.WhatPieceIsAt(row, col))
      {
        gui->ClearPiece(row, col);
      }
      else
      {
        gui->PlacePiece(row, col, game.WhatPieceIsAt(row, col));
      }
      */
    }
  }

  string banner = (WHITE == game.WhoseTurn()) ? "White" : "Black";
  banner.append(" - it's your turn!");
  gui->SetStatusBar(banner.c_str());
}

bool Chess::_piece_is_selected()
{
  return -1 != cur_row;
}

void Chess::_deselect_piece()
{
  cur_row = -1;
  cur_col = -1;
  _unhighlight_all();
}

/*
 * Highlight the piece green if it can move, along with it's moves
 * otherwise highlight the piece yellow
 * store the fact that the piece is selected
 */
void Chess::_select_piece(int row, int col)
{
  if(!game.HasTurn(row, col)) { return; }

  cur_row = row;
  cur_col = col;
  gui->HighlightSquare(row,col, YELLOW_SQUARE);

  vector<Cell> cells = game.WhereCanPieceMoveFrom(row, col);
  if (cells.size() > 0)
  {
    gui->HighlightSquare(row,col, GREEN_SQUARE);
    for (int i = 0; i < cells.size(); i++)
    {
      gui->HighlightSquare(cells[i].row, cells[i].col, GREEN_SQUARE);
    }
  }
}

void Chess::_unhighlight_all()
{
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      gui->HighlightSquare(row,col, CLEAR_SQUARE);
    }
  }
}

ImageName Chess::_to_image_name(const PieceName piece) const
{
  switch(piece) {
  case NO__PIECE:
    return NO_IMAGE;

  case B__ROOK:
    return B_ROOK;
  case B__KNIGHT:
    return B_KNIGHT;
  case B__BISHOP:
    return B_BISHOP;
  case B__QUEEN:
    return B_QUEEN;
  case B__KING:
    return B_KING;
  case B__PAWN:
    return B_PAWN;

  case W__ROOK:
    return W_ROOK;
  case W__KNIGHT:
    return W_KNIGHT;
  case W__BISHOP:
    return W_BISHOP;
  case W__QUEEN:
    return W_QUEEN;
  case W__KING:
    return W_KING;
  case W__PAWN:
    return W_PAWN;

  default:
    return NO_IMAGE;
  }
}

/********Implement These*****************************/

/*
 * Clear the highlights
 *
 * If no piece is selected
 * 	select the piece (if it's that piece's turn) |green : none
 * 	show the (im)possible moves |green : red
 * If a piece is selected
 * 	case invalid move
 * 		deselect and attempt new select
 * 	case enemy_square
 * 		capture
 * 	case friendly_square
 *
 * 	commit a move or deselect the piece
 */
void Chess::on_CellSelected(int row, int col, int button)
{
  cout << "Chess::on_CellSelected nsth" << endl;
  g_debug("Chess::on_CellSelected (%d,%d)",row,col);

  if (_piece_is_selected())
  {
    if (cur_row == row && cur_col == col)
    {
      //TODO _deselect_piece(); // fix board logic, then add this back in
      return;
    }
    cout << "Using prev" << endl;
    g_debug("Using previous selection");
    if (game.MoveFromTo(cur_row, cur_col, row, col))
    {
      cout << "Moved" << endl;
      g_debug("Moved Piece");
      _deselect_piece();
      _update_board();
    }
    else
    {
      cout << "Couldn't move" << endl;
      g_debug("Could not complete move");
      _deselect_piece();
      _select_piece(row, col);
    }
  }
  else
  {
    cout << "Selected" << endl;
    g_debug("Made selection");
    _deselect_piece();
    _select_piece(row, col);
  }
  /*
    Each square of the chess board is reffered to in the GUI code as a cell.
  This Function is called whenever the uses clicks and releases the mouse button over
  a cell without initiating a drag. Row and Column coordinates begin in the top left corner.
  The button paramter tells which mouse button was clicked(1 for left, 2 for middle, 3 for right).
  You do not need to worry about wich button was used to complete the project.
  */
}

void Chess::on_DragStart(int row,int col)
{
  g_debug("Chess::on_DragStart (%d,%d)",row,col);
  on_CellSelected(row, col, 1);
  /*
    When a drag is initiated, this function will be called instead of on_CellSelected().
  The paramaters row and col are the coordinates of the cell where the drag was initiated.
  All three buttons may initiate the drag, but for our purposes can be treated the same and so
  that paramater is not included.
  */
}
bool Chess::on_DragEnd(int row,int col)
{
  g_debug("Chess::on_DragEnd (%d,%d)",row,col);
  on_CellSelected(row, col, 1);
  /*
    Same as on_DragStart() except the coordinates represent the ending cell of
  the drag. If the drag terminates off the playing board, this will be called with
  the initial coordinates of the drag.
  */

  //by convention, this should return a boolean value indicating if the drag was accepted or not.
  return false;
}

/*
 * Called when someone selects 'New' from the toolbar, 'Game' menu, or presses 'Ctrl-N'.
 */
void Chess::on_NewGame()
{
  g_debug("Chess::on_NewGame");
  game.NewGame();
  _update_board();
}

/*
 *	Called when someone selects 'Save' from the toolbar, 'Game' menu, or presses 'Ctrl-S'.
 */
void Chess::on_SaveGame()
{
  g_debug("Chess::on_SaveGame");
  if (filename.size() == 0) { filename = gui->SelectSaveFile(); }
  game.Save(filename);
}

void Chess::on_SaveGameAs()
{
  g_debug("Chess::on_SaveGameAs");
  filename = gui->SelectSaveFile();
  game.Save(filename);
  /*
  Called when someone selects 'Save As' from the 'Game' menu, or presses 'Shift-Ctrl-S'.
  */
}
void Chess::on_LoadGame()
{
  g_debug("Chess::on_LoadGame");
  game.Load(gui->SelectLoadFile());
  /*
  Called when someone selects 'Open' from the toolbar, 'Game' menu, or presses 'Ctrl-O'.
  */
}

void Chess::on_UndoMove()
{
  g_debug("Chess::on_UndoMove");
  game.Undo();
  /*
  Called when someone selects 'Undo' from the toolbar, 'Game' menu, or presses 'Ctrl-Z'.
  */
}


void Chess::on_QuitGame()
{
  g_debug("Chess::on_QuitGame");
  /*It is not required to implement this function*/

  /*
    Called when someone selects 'Quit' from the toolbar, 'Game' menu, presses 'Ctrl-Q', or closes the window.<br>
  on_QuitGame() does not need to be implemented to fulfill the requirements of the project, but is available for your
  use.
  */
}





/**********You Do Not Need To Touch These Functions***********************************/


void Chess::run(Gtk::Main & app)
{
  app.run(*gui);
}



void log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
{
        ///@todo Provide more info
  std::string output= std::string(message?message:"");
  bool fatal=false;

  if(log_level & G_LOG_FLAG_FATAL) fatal=true;

  //if a level is set in the LOG_LEVEL_HIDE_MASK it will fall through to the
  //default case and so will not be printed
  int level = log_level & (~LOG_LEVEL_HIDE_MASK & G_LOG_LEVEL_MASK);

  switch(level)
  {
    case G_LOG_LEVEL_DEBUG:
        output = std::string("DEBUG::")+output;
      break;
    case G_LOG_LEVEL_ERROR:
      output = std::string("ERROR::")+output;
      break;
    case G_LOG_LEVEL_CRITICAL:
      output = std::string("CRITICAL::")+output;
      break;
    case G_LOG_LEVEL_WARNING:
      output = std::string("WARNING::")+output;
      break;
    case G_LOG_LEVEL_MESSAGE:
      output = std::string("MESSAGE::")+output;
      break;
    case G_LOG_LEVEL_INFO:
      output = std::string("INFO::")+output;
      break;
    default:
      output="";
  }

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
  else {}
  return;
}
/**************************************************************************/
