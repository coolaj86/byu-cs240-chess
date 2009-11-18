// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//

#include <vector>
#include <gtkmm/stock.h>
#include "ChessGuiBoardCell.h"
#include "ChessGuiImages.h"

using namespace Gdk;
using namespace Glib;

ChessGuiBoardCell::ChessGuiBoardCell(BaseObjectType* cobject,
				     const Glib::RefPtr<Gnome::Glade::Xml>& refGlade):Gtk::Image(cobject)
{
	width=DEFAULT_CELL_SIZE;
	height =DEFAULT_CELL_SIZE;
	//create layers
	layers.resize(MAX_LAYER,0);
	layer_visible.resize(MAX_LAYER,false);
	layer_alpha.resize(MAX_LAYER,255);

}

ChessGuiBoardCell::~ChessGuiBoardCell()
{
	return;
}


void ChessGuiBoardCell::UpdateImage()
{
	//g_debug("ChessGuiBoardCell::updateImage");


	//scale and copy background
	RefPtr<Pixbuf>  drawImage;
        drawImage= (*layers[BACK_GRND_LAYER])->scale_simple(width,height,INTERP_BILINEAR);



        RefPtr<Gdk::Pixbuf> scaled;
	//for each layer visible, scale and draw
	for(signed int l=BACK_GRND_LAYER+1;l<MAX_LAYER;l++)
	{
		if(layer_visible[l])
		{
			if(layers[l]!=0 && (*layers[l])!= ChessGuiImages::GetImage(NO_IMAGE))
				scaled=(*layers[l])->scale_simple(width-CELL_PAD,height-CELL_PAD,Gdk::INTERP_NEAREST);
			else
			{
        			g_debug("ChessGuiBoardCell::updateImage::Image Not Found");
				scaled=
				 ChessGuiImages::GetErrorImage()->scale_simple(width,height,INTERP_BILINEAR);
				//set(Gtk::Stock::MISSING_IMAGE,Gtk::ICON_SIZE_DND );
				//return;
			}
			scaled->composite(drawImage,
				0,0,width,height,
				(CELL_PAD/2),(CELL_PAD/2),1,1,
				INTERP_BILINEAR,
				layer_alpha[l]);
		}
	}

	set(drawImage);

	return;
}


void ChessGuiBoardCell::SetLayerVisible(CellLayer layer, bool visible)
{
	if(!(layer<MAX_LAYER && layer >=0))
	{
		 g_warning("ChessGuiBoardCell::SetLayerVisible::layer out of range");
		 return;
	}

	layer_visible[layer]=visible;
}
void ChessGuiBoardCell::SetLayer(const Glib::RefPtr<Gdk::Pixbuf> & pix,CellLayer layer,
			bool visible,signed int alpha )
{
	if(layer<MAX_LAYER && pix && alpha<=255)
	{
		layers[layer] = &pix;
		layer_visible[layer] = visible;
		layer_alpha[layer]=alpha;
		return;

	}
	else
	{
		g_warning("ChessGuiBoardCell::SetLayer::Arguments out of range");
	}
}

void ChessGuiBoardCell::SetBackGroundLayer(const Glib::RefPtr<Gdk::Pixbuf> & bg)
{
	SetLayer(bg, BACK_GRND_LAYER);
	return;
}

void ChessGuiBoardCell::SetTileLayer(const Glib::RefPtr<Gdk::Pixbuf> & tile)
{
	SetLayer(tile, TILE_LAYER,true,TILE_ALPHA);
	return;
}

void ChessGuiBoardCell::SetHiglightLayer(guint color)
{
	highlight = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB,
					true,BITS_PER_SAMPLE,
					DEFAULT_CELL_SIZE,DEFAULT_CELL_SIZE);

	highlight->fill(color);
	SetLayer(highlight,HIGHLIGHT_LAYER,true,TILE_ALPHA);
}
void ChessGuiBoardCell::SetPieceLayer(const Glib::RefPtr<Gdk::Pixbuf> & piece)
{
	SetLayer(piece,PIECE_LAYER);
	return;
}
