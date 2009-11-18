// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//
///@file ChessGuiBoardCell.h Low level Widget for the CS240 %Chess project GUI
///@ingroup chessgui
#ifndef CHESS_GUI_BOARD_CELL_H
#define CHESS_GUI_BOARD_CELL_H

#include <sigc++/sigc++.h>
#include <libglademm.h>

#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>

#include "ChessGuiDefines.h"

///@ingroup chessgui
///Provides functionality for drawing layered images to each cell of a ChessGuiBoard
///@note Depends heavily on cs240chess.glade
class ChessGuiBoardCell : public Gtk::Image
{
	friend class ChessGuiBoard;

	public:
		///This format of constructor is necessary for this constructor to be automatically used
		///by the Glade::Xml::get_derived_widget() function.
		///See @link cs240chess.glade "Glade File" @endlink
		///@param cobject initialize Gtk::Window
		///@param refGlade is generated beforehand using libglademm
		ChessGuiBoardCell(BaseObjectType* cobject, const Glib::RefPtr<Gnome::Glade::Xml>& refGlade);
	private:
		///Currnet width of visible image. Initializes to #DEFAULT_CELL_SIZE
		int width;
		///Currnet width of visible image. Initializes to #DEFAULT_CELL_SIZE
		int height;

		///@name Visible Image Data
		///Data is coordinated using the enum CellLayer as indexing values
		///@{

		///vector of pointers to References to PixBufs (for easy image switching)
		///Original references are stored by ChessGuiImages.
		///When the images in ChessGuiImages are modified and the cell is refreshed,
		///the Image will be automatically updated.
		///Memory is freed by RefPtr
		std::vector<const Glib::RefPtr<Gdk::Pixbuf> * > layers;
		///ChessGuiImages does not store highligts (too many possibilities) so the cell does
		Glib::RefPtr<Gdk::Pixbuf> highlight;  //no universal repository for highlight

		///layer_visible[i] stores weather the PixBuf at layers[i] should be drawn
		std::vector<bool>  layer_visible;
		///opacity of layer i 0(transparent)-255(opaque)
		std::vector<signed int> layer_alpha;
		///@}
	private:
		~ChessGuiBoardCell();

		///@name Image Manipulation
		///No changes appear to image until a call to UpdateImage is made
		///@{

		///Draw all visible layers to image
		void UpdateImage();

		///@param pix a Gdk::Pixbuf that will be set at layer
		///@param layer as defined by CellLayer
		///@param visible whether this layer should be shown, default = true
		///@param alpha  level of transparency 0-255 of this layer (255 is opaque)
		void SetLayer(const Glib::RefPtr<Gdk::Pixbuf> & pix,
				      CellLayer layer,
				      bool visible = true,
				      signed int alpha =255);

		///sets wheter a layer should be drawn or not
		///@param layer layer to be set
		///@param visible wether the layer will be drawn to Image on the next call to UpdateImage
		void SetLayerVisible(CellLayer layer, bool visible =true);

		///Passes appropriate arguments to SetLayer
		void SetBackGroundLayer(const Glib::RefPtr<Gdk::Pixbuf> & bg);

		///Passes appropriate arguments to SetLayer
		void SetTileLayer(const Glib::RefPtr<Gdk::Pixbuf> & color);

		///creates a Gdk::Pixbuf of color
		///Passes appropriate arguments to SetLayer
		///@param color @link ChessGuiDefines.h predefined colors here @endlink
		void SetHiglightLayer(guint color);
		///Passes appropriate arguments to SetLayer
		void SetPieceLayer(const Glib::RefPtr<Gdk::Pixbuf> & piece);

		///@}
};

#endif
