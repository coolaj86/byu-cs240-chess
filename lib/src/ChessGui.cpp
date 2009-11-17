// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//

#include "ChessGui.h"

#include <string>

#include <libglademm.h>
#include <sigc++/sigc++.h>



#include <gtkmm/imagemenuitem.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/main.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/paned.h>
#include <gtkmm/stock.h>

#include "ChessGuiImages.h"
#include "SelectDialog.h"

using namespace std;
using namespace Gtk;
using namespace Glib;



ChessGui::ChessGui(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& chXml) :
		 	Window(cobject),chessXml(chXml),statusbar(0),messageArea(0),
			messageWindow(0),top(0),bottom(0),board(0),messageAreaLastPosition(0)
{
	if(!ChessGuiImages::Loaded())
		ChessGuiImages::LoadDefaultImages();
	
	///depends on cs240chess.glade
	chessXml->get_widget("Chess_StatusBar",statusbar);
	chessXml->get_widget("Chess_MessageArea",messageArea);
	chessXml->get_widget("Chess_MessageArea_ScrolledWindow",messageWindow);
	chessXml->get_widget("Chess_TopLabel",top);
	chessXml->get_widget("Chess_BottomLabel",bottom);
	
		
	chessXml->get_widget_derived("ChessBoard_aspectframe",board);
		
	ConnectSignals();
	show_all();
	
	
	
	return;
}

ChessGui::~ChessGui()
{
	
	statusbar=0;
	//derived class	
	delete board; 
	board=0;
		
	top=0;
	bottom=0;
	messageArea=0;
	
}


void ChessGui::ConnectSignals()
{
	ConnectMenuSignals();
	ConnectToolBarSignals();
	
	//connect so that we can check for saving games if needed
	this->signal_delete_event().connect(sigc::mem_fun(*this,&ChessGui::on_main_delete_event));
	
}


void ChessGui::ConnectMenuSignals()
{
	ImageMenuItem * menuItem=0;
	
	///depends on cs240chess.glade	
	chessXml->get_widget("Chess_MenuBar_UndoMove",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_UndoMove));
	
	chessXml->get_widget("Chess_MenuBar_NewGame",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_NewGame));
	
	chessXml->get_widget("Chess_MenuBar_LoadGame",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_LoadGame));
	
	chessXml->get_widget("Chess_MenuBar_SaveGame",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_SaveGame));
	
	chessXml->get_widget("Chess_MenuBar_SaveGameAs",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_SaveGameAs));
	
	chessXml->get_widget("Chess_MenuBar_Quit",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_Quit));
	
	chessXml->get_widget("Chess_MenuBar_LoadImages",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_LoadImages));
	
        chessXml->get_widget("Chess_MenuBar_Messages_Hide",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_HideMessages));
	
	chessXml->get_widget("Chess_MenuBar_Messages_Clear",menuItem);
	menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_ClearMessages));
        
        chessXml->get_widget("Chess_MenuBar_About",menuItem);
        menuItem->signal_activate().connect(sigc::mem_fun(*this, &ChessGui::on_About));
	
	CheckMenuItem * checkItem=0;
	chessXml->get_widget("Chess_MenuBar_View_Toolbar",checkItem);
	checkItem->signal_toggled().connect(sigc::mem_fun(*this, &ChessGui::on_ToggleToolbarView));
	
	return;
}

void ChessGui::ConnectToolBarSignals()
{
	ToolButton * toolButton=0;
	
	///depends on cs240chess.glade	
	chessXml->get_widget("Chess_ToolBar_UndoMove",toolButton);
	toolButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessGui::on_UndoMove));
	
	chessXml->get_widget("Chess_ToolBar_NewGame",toolButton);
	toolButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessGui::on_NewGame));
	
	chessXml->get_widget("Chess_ToolBar_LoadGame",toolButton);
	toolButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessGui::on_LoadGame));
	
	chessXml->get_widget("Chess_ToolBar_SaveGame",toolButton);
	toolButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessGui::on_SaveGame));
		
	chessXml->get_widget("Chess_ToolBar_Quit",toolButton);
	toolButton->signal_clicked().connect(sigc::mem_fun(*this, &ChessGui::on_Quit));
	
	return;
}

std::string ChessGui::SelectSaveFile()
{
	g_debug("ChessGui::SelectSaveFile");
	
	Gtk::FileChooserDialog dialog("Save Game",Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.set_transient_for(*dynamic_cast<Gtk::Window *>( this));

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	
	//force overwrite confirmationg
	dialog.set_do_overwrite_confirmation(true);
	//Show the dialog and wait for a user response:
	int result = dialog.run();
	
	std::string filename;
	//Handle the response:
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
		{
			filename = dialog.get_filename();
			g_debug("Save Game::File selected: %s",filename.c_str());
			break;
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			g_debug( "Save Game::Cancel clicked");
			break;
		}
		default:
		{
			g_debug("Save Game::Unexpected button clicked.");
			break;
		}
	}
	
	return filename;
	
}

std::string ChessGui::SelectLoadFile()
{
	Gtk::FileChooserDialog dialog("Load Game",Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*dynamic_cast<Gtk::Window *>( this));

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	std::string filename;
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
		{
			filename = dialog.get_filename();
			g_debug("Load Game::File selected: %s",filename.c_str());
			break;
			
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			g_debug( "Load Game::Cancel clicked");
			break;
		}
		default:
		{
			g_debug("Load Game::Unexpected button clicked.");
			break;
		}
	}
	
	return filename;
	
	
}



void ChessGui::SetTopLabel(const std::string & text)
{
	top->set_label(text);
	return;
}
void ChessGui::SetBottomLabel(const std::string & text)
{
	bottom->set_label(text);
}
void ChessGui::ClearMessageArea()
{
	RefPtr<TextBuffer> buffer = messageArea->get_buffer();
	buffer->erase(buffer->begin(),buffer->end());
}
void ChessGui::WriteMessageArea(const std::string & message)
{
	//messageArea->get_
	messageArea->get_buffer()->insert_at_cursor(message);
	messageWindow->get_vadjustment()->set_value(messageWindow->get_vadjustment()->get_upper());
	
	return;
}

void ChessGui::SetStatusBar(const std::string & status)
{
	statusbar->push(status);
	return;
}
void ChessGui::HighlightSquare(signed int row,signed int col,guint32  color)
{
	board->HighlightSquare(row,col,color);
}
void ChessGui::UnHighlightSquare(signed int row,signed int col)
{
	board->UnHighlightSquare(row,col);
}
void ChessGui::PlacePiece(signed int row,signed int col, ImageName piece)
{
	board->PlacePiece(row,col,piece);
}
void ChessGui::ClearPiece(signed int row,signed int col)
{
	board->ClearPiece(row,col);
}
//signal accessors **************************************************************************
sigc::signal<void, int, int, int> ChessGui::signal_cell_selected()
{
	return board->signal_cell_selected();
}

sigc::signal<void> ChessGui::signal_new()
{
	return actionNewSignal;
}
sigc::signal<void> ChessGui::signal_save()
{
	return actionSaveSignal;
}
sigc::signal<void> ChessGui::signal_save_as()
{
	return actionSaveAsSignal;
}
sigc::signal<void> ChessGui::signal_load()
{
	return actionLoadSignal;
}
sigc::signal<void> ChessGui::signal_undo()
{
	return actionUndoSignal;
}
sigc::signal<void> ChessGui::signal_quit()
{
	return actionQuitSignal;
}


sigc::signal<void, int, int> ChessGui::signal_drag_start()
{
	return board->signal_drag_start();
}
sigc::signal<bool, int, int> ChessGui::signal_drag_end()
{
	return board->signal_drag_end();
	
}
//signal handlers ****************************************************************************
void ChessGui::on_UndoMove()
{
	g_debug("ChessGui::on_UndoMove");
	actionUndoSignal.emit();
	return;
}

void ChessGui::on_NewGame()
{
	g_debug("ChessGui::on_NewGame");
	actionNewSignal.emit();
	return;
}

void ChessGui::on_LoadGame()
{
	
	g_debug("ChessGui::on_LoadGame");
	actionLoadSignal.emit();
	return;
}

void ChessGui::on_SaveGame()
{
	g_debug("ChessGui::on_SaveGame");
	actionSaveSignal.emit();
	return;
}

void ChessGui::on_SaveGameAs()
{
	g_debug("ChessGui::on_SaveGameAs");
	actionSaveAsSignal.emit();
	return;
}

void ChessGui::on_LoadImages()
{
	///Generates a Select Folder Dialog
	///Folder selected should contain image files
	///following the naming formated specified in ChessGuiImages::SetDefaultFileNames
	g_debug("ChessGui::on_LoadImages");
	Gtk::FileChooserDialog dialog("Select Images Folder",Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
	dialog.set_transient_for(*dynamic_cast<Gtk::Window *>( this));

	//Add response buttons the the dialog:
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	std::string path;
	switch(result)
	{
		case(Gtk::RESPONSE_OK):
		{
			path = dialog.get_filename();
			g_debug("Load Images::File selected: %s",path.c_str());
			break;
			
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			g_debug( "Load Images::Cancel clicked");
			break;
		}
		default:
		{
			g_debug("Load Images::Unexpected button clicked.");
			break;
		}
	}
	
	if(path.size()!=0)
	{
		ChessGuiImages::LoadImages(path);
		
		if(!ChessGuiImages::Loaded())
		{
			g_warning("Load Images failed");
		}
	}
	board->RefreshBoard();
	return;
}
void ChessGui::on_Quit()
{
	///activates the destroy process
	g_debug("ChessGui::on_Quit");
	actionQuitSignal.emit();
	Gtk::Main::quit();
	return;
}

bool ChessGui::on_main_delete_event(GdkEventAny* event)
{
	g_debug("ChessGui::on_main_delete_event");
	///emits signal_quit to allow for gracefull exiting when the 'x' button is activated
	actionQuitSignal.emit();
	return false;
}

void ChessGui::on_HideMessages()
{
	g_debug("ChessGui::on_HideMessages");
	
	///retrieves the Hpaned widget from chessXml
	HPaned * pane=0;
	chessXml->get_widget("Chess_hpaned",pane);
	int position =pane->property_position().get_value();
	int maxPosition =pane->property_max_position().get_value();
	
	///If the position property of the HPaned is not its max value,
	if(position!=maxPosition)
	{
		///it's current position is saved and then it is hidden.
		messageAreaLastPosition=position;
		pane->set_position(maxPosition);
	}
	else
	{
		///Else, it is restored to its last position
		///@todo Modify so that if the last position is not exactly the max,
		///but is small enough away as to be indestinguishable, 
		///that the messageArea is restored to the default position
		pane->set_position(messageAreaLastPosition);
		
	}
	
	pane=0;
	return;
	
}
void ChessGui::on_ClearMessages()
{
	g_debug("ChessGui::on_ClearMessages");
	ClearMessageArea();
	return;
}

void ChessGui::on_About()
{
     g_debug("ChessGui::on_About");
     Gtk::AboutDialog  about;
     about.set_transient_for(*dynamic_cast<Gtk::Window *>( this));
     
     about.set_name("CS 240 Chess");
     
     about.set_logo(ChessGuiImages::GetImage(W_KING));

     about.set_copyright("Copyright © 2008 Owen Merkling\n Copyright © SEMESTER CS 240 Student");
     
     about.set_comments("For use by students of CS 240 at BYU");

     std::list<std::string> authors;
     authors.push_back("Graphical User Interface: Owen Merkling");
     authors.push_back("Chess Logic: CS240 Student");
     about.set_authors(authors);
     
     about.run();
     return;
}

void ChessGui::on_ToggleToolbarView()
{
	g_debug("ChessGui::on_ToggleToolbarView");
        Gtk::Toolbar * toolBar=0;
        CheckMenuItem * checkItem=0;
        
        chessXml->get_widget("Chess_ToolBar",toolBar);
        chessXml->get_widget("Chess_MenuBar_View_Toolbar",checkItem);
        
        if(checkItem->get_active())
        {
             toolBar->show();
        }
        else
        {
             toolBar->hide();
        }

	return;
}




