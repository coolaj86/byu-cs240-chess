// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//

#include "ChessGuiBoard.h"

#include "ChessGui.h"
#include "ChessGuiImages.h"
#include <gtkmm/stock.h>
#include <gdkmm/cursor.h>


#include <sstream>
#include <stdio.h>
#include <cassert>


ChessGuiBoard::ChessGuiBoard(BaseObjectType* cobject,
							 const Glib::RefPtr<Gnome::Glade::Xml>& chessXml):
							 Gtk::AspectFrame(cobject),curCellRow(-1),curCellCol(-1)
{
	width= DEFAULT_BOARD_WIDTH;
	height = DEFAULT_BOARD_HEIGHT;

	//init rows
	for(int row =0;row<NUM_ROW;row++)
	{
		//init column
		for(int col=0;col<NUM_COL;col++)
		{
			InitCell(chessXml,row,col);
		}

	}

	//for board resizing
	Gtk::EventBox * eventbox;
	chessXml->get_widget("ChessBoard_eventbox",eventbox);
	eventbox->signal_size_allocate().connect(sigc::mem_fun(*this,
											 &ChessGuiBoard::on_board_size_allocate));
}


ChessGuiBoard::~ChessGuiBoard()
{
	//rows
	for(int row =0;row<NUM_ROW;row++)
	{
		//columns
		for(int col=0;col<NUM_COL;col++)
		{
			delete board[row][col];
			board[row][col] =0 ;
		}

	}
}


//generates a string using the name scheme "ChessBoard_Row%d_Col%d" row,col
std::string ChessGuiBoard::GenStringName(int row,int col)
{
/*
///@todo Figure out this bug with generating a string name ???

	std::ostringstream name;
	name<<"ChessBoard_Row"<<row<<"_Col"<<col;


	g_debug("ChessGuiBoard::GenStringName::name=%s",name.str().c_str());

	return name.str();
*/


	char buffer[30];
	sprintf(buffer,"ChessBoard_Row%d_Col%d",row,col);
	return std::string(buffer);
}

void ChessGuiBoard::InitCell(const Glib::RefPtr<Gnome::Glade::Xml> & chessXml,int row,int col)
{
	g_debug("ChessGuiBoard::initCell row:%d col:%d",row,col);
	//cell is out of range
	assert((row>-1) || (row<NUM_ROW) || (col>-1) || (col < NUM_COL));


	///Retrieve widget from Glade::Xml and place on board
	ChessGuiBoardCell * & cell = board[row][col];
	std::string cellName=GenStringName(row+1,col+1);
	chessXml->get_widget_derived(cellName,cell);

	if(!cell)
	{
		g_error("InitCell::Failed to retrieve %s from chessXml",cellName.c_str());
	}
	///retrieve EventBox container for this widget and connect event signals
	Gtk::EventBox * eb;
	cellName.append("_eb");
	chessXml->get_widget(cellName,eb);
	ConnectCellSignals(cell, eb,row,col);
	eb=0;

	///set background layer
	cell->SetBackGroundLayer(ChessGuiImages::GetImage(BACK_GRND));
	///set tile pattern
	  //odd rows
	if(row!=0 && row%2!=0)
	{
		//even columns black
		if(col==0 || col%2 == 0)
		{
			cell->SetTileLayer(ChessGuiImages::GetImage(BLACK_TILE));
		}
		else //odd columns white
		{
			cell->SetTileLayer(ChessGuiImages::GetImage(WHITE_TILE));

		}
	}
	else if(col!=0 && col %2 != 0) //even rows, odd columns black
	{
		cell->SetTileLayer(ChessGuiImages::GetImage(BLACK_TILE));
	}
	else //even columns white
	{
		cell->SetTileLayer(ChessGuiImages::GetImage(WHITE_TILE));

	}

	cell->UpdateImage();


	return;
}

void ChessGuiBoard::ConnectCellSignals(ChessGuiBoardCell * cell,
									   Gtk::EventBox * eb,
									   int row,
									   int col)
{
	g_debug("ChessGuiBoard::ConnectCellSignals::image=%s row=%d col=%d",
			cell->get_name().c_str(), row, col);

	///connect button pressed/released events
	eb->signal_button_release_event().connect(
					sigc::bind( sigc::mem_fun( *this,&ChessGuiBoard::on_button_released), row,col) );
	eb->signal_button_press_event().connect(
				 	sigc::bind(sigc::mem_fun(*this,&ChessGuiBoard::on_button_pressed), row,col) );

	///set cell as drag-and-dropable
	std::vector<Gtk::TargetEntry> targets;
	targets.push_back(Gtk::TargetEntry("STRING"));
	targets.push_back(Gtk::TargetEntry("ImageNameEnum"));
        eb->drag_source_set(targets,
        		            Gdk::BUTTON1_MASK|Gdk::BUTTON2_MASK|Gdk::BUTTON3_MASK,Gdk::ACTION_MOVE );
        eb->drag_dest_set(targets,Gtk::DEST_DEFAULT_MOTION|Gtk::DEST_DEFAULT_DROP,Gdk::ACTION_MOVE);

	/// set up drag/drop handlers
	eb->signal_drag_begin().connect(sigc::bind(sigc::mem_fun(*this,
									&ChessGuiBoard::on_cell_drag_begin), row,col) );
	eb->signal_drag_drop().connect(sigc::bind(sigc::mem_fun(*this,
									&ChessGuiBoard::on_cell_drag_drop), row,col) );
	eb->signal_drag_leave().connect(sigc::bind(sigc::mem_fun(*this,
									&ChessGuiBoard::on_cell_drag_leave), row,col) );
	eb->signal_drag_motion().connect(sigc::bind(sigc::mem_fun(*this,
									&ChessGuiBoard::on_cell_drag_motion), row,col) );


}


/*********************************************************************************signal handllers*/
bool ChessGuiBoard::on_button_released(GdkEventButton* event,int row,int col)
{
	g_debug("ChessGuiBoard::on_button_released row=%d col=%d curRow=%d curCol=%d",
			row, col, curCellRow, curCellCol);

	if(curCellRow==row && curCellCol==col && !dragStarted)
	{
		signal_cell_selected().emit(row,col,event->button);
	}
	else if(dragStarted && curCellRow==-1 && curCellCol==-1)
	{
		signal_drag_end().emit(row,col);
	}
	curCellRow=-1;
	curCellCol=-1;
	return false;
}


bool ChessGuiBoard::on_button_pressed(GdkEventButton* event,int row,int col)
{
	g_debug("ChessGuiBoard::button_pressed row=%d col=%d button=%d",row,col, event->button);
	///set curCellRow and curCellCol
	curCellRow=row;
	curCellCol=col;
        dragStarted=false;
	return false;
}

void ChessGuiBoard::on_cell_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context,
									   int row,
									   int col)
{
	g_debug("ChessGuiBoard::drag_begin row=%d col=%d",row,col);


	///Set the Drag Icon
	if(board[row][col]->layer_visible[PIECE_LAYER] && board[row][col]->layers[PIECE_LAYER])
	{

		context->set_icon(
			(*(board[row][col]->layers[PIECE_LAYER]))->scale_simple(40,
																	40,
																	Gdk::INTERP_BILINEAR),
																	15,
																	15);

		///@todo Get move cursor to change completely
		/*
		Glib::RefPtr<Gdk::Window> window = get_window();
		window->set_cursor(Gdk::Cursor(Gdk::Display::get_default(),
					Gdk::Pixbuf::create(
					Gdk::COLORSPACE_RGB, true, 8, 1, 1),
					0, 0));*/
	}
	else
		context->set_icon(Gtk::Stock::STOP.id,0,0);

	///set curCellRow and curCellCol
	curCellRow=row;
	curCellCol=col;
	dragStarted=true;


	///emit signal_drag_start()
        ///@todo allow drag start to specify which button is dragging
	signal_drag_start().emit(row,col);
}

bool ChessGuiBoard::on_cell_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context,
									  int x,
									  int y,
									  guint time,
									  int row,
									  int col)
{
	g_debug("ChessGuiBoard::drag_drop row=%d col=%d",row,col);
	dragStarted=false;

	///emits signal_drag_end
        return signal_drag_end().emit(row,col);
}
void ChessGuiBoard::on_cell_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context,
									   guint time,
									   int row,
									   int col)
{
	g_debug("ChessGuiBoard::drag_leave row=%d col=%d",row,col);
	Glib::RefPtr<Gdk::Window> window = get_window();
	curCellRow=-1;
	curCellCol=-1;

}
bool ChessGuiBoard::on_cell_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context,
										int x,
										int y,
										guint time,
										int row,
										int col)
{
	g_debug("ChessGuiBoard::drag_motion row=%d col=%d",row,col);
	///updates curCellRow and curCellCol
	curCellRow=row;
	curCellCol=col;
	return false;
}


void ChessGuiBoard::on_board_size_allocate(Gtk::Allocation& allocation)
{

	g_debug("ChessGui::on_Board_size_allocate");
	ResizeBoard(allocation.get_width(),allocation.get_height());
	return;
}

/*********************************************************************************signal accessors*/
sigc::signal<void, int, int, int> ChessGuiBoard::signal_cell_selected()
{
	return cellSelectSignal;
}
sigc::signal<void, int, int> ChessGuiBoard::signal_drag_start()
{
	return dragStartSignal;
}
sigc::signal<bool, int, int> ChessGuiBoard::signal_drag_end()
{
	return dragEndSignal;
}


/*****************************************************************************convenience and init*/

void ChessGuiBoard::ResizeBoard(int w,int h)
{
	g_debug("width=%d height=%d",width,height);
	///Does not resize if board is already same size
	if(w!=width && h!=height)
	{
		width=w;
		height=h;
		int cellWidth =(width/NUM_COL)+CELL_PAD;
		int cellHeight =( height/NUM_ROW)+CELL_PAD;

		for(int row =0;row<NUM_ROW;row++)
		{

			for(int col=0;col<NUM_COL;col++)
			{
				board[row][col]->width=cellWidth;
				board[row][col]->height=cellHeight;
				board[row][col]->UpdateImage();
			}

		}
	}
}

void ChessGuiBoard::RefreshBoard()
{
	for(int i=0;i<NUM_ROW;i++)
	{
		for( int k = 0; k<NUM_COL;k++)
		{
			board[i][k]->UpdateImage();
		}
	}

}


void ChessGuiBoard::HighlightSquare(signed int row,signed int col,guint32  color)
{
	if( (row<0) || (row>=NUM_ROW) || (col<0) || (col >= NUM_COL))
	{
		g_warning("ChessGuiBoard::HighlightSquare::Cell is out of range");
		return;
	}
	else
	{
		board[row][col]->SetHiglightLayer(color);
		board[row][col]->UpdateImage();

	}
}

void ChessGuiBoard::UnHighlightSquare(signed int row,signed int col)
{
	if( (row<0) || (row>=NUM_ROW) || (col<0) || (col >= NUM_COL))
	{
		g_warning("ChessGuiBoard::UnhighligthSquare::Cell is out of range");
	}
	else
	{
		board[row][col]->SetLayerVisible(HIGHLIGHT_LAYER,false);
		board[row][col]->UpdateImage();

	}
}

void ChessGuiBoard::PlacePiece(signed int row,signed int col, ImageName piece)
{

	if( (row<0) ||
		(row>=NUM_ROW) ||
		(col<0) ||
		(col >= NUM_COL) ||
		piece<W_PAWN ||
		piece >NUM_IMAGE_NAMES )
	{
		g_warning("ChessGuiBoard::PlacePiece::Invalid Paramaters");
	}
	else
	{
		board[row][col]->SetPieceLayer(ChessGuiImages::GetImage(piece));
		board[row][col]->UpdateImage();

	}
}

void ChessGuiBoard::ClearPiece(signed int row,signed int col)
{
	if( (row<0) || (row>=NUM_ROW) || (col<0) || (col >= NUM_COL))
	{
		g_warning("ChessGuiBoard::ClearPiece::Cell is out of range");
	}
	else
	{
		board[row][col]->SetLayerVisible(PIECE_LAYER,false);
		board[row][col]->UpdateImage();

	}
}
