// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//
#ifndef CHESS_GUI_IMAGES_H
#define CHESS_GUI_IMAGES_H


#include <vector>
#include <string>
#include <gdkmm/pixbuf.h>
#include <gtkmm/image.h>
#include "ChessGuiDefines.h"

///@ingroup chessgui
///Provides a static repository for Gdk::Pixbuf that are used throughout the GUI.
///Allows for dynamically loading and switching images during the runtime of the program.
///Allows the finished chess program to be run from any directory,
///and not only the one it was compiled in
///@todo use Gdk::Pixbuf::create_from_data functionality to include default images in the binary

class ChessGuiImages
{
	private:
		///Static repository of images. Indexed using  ImageName
                ///index NO_IMAGE always contains a transparent pixubf square
		static std::vector<Glib::RefPtr<Gdk::Pixbuf> >  images;

		///Default Image Not Found/Error icon
		///Image is compiled in
		static Glib::RefPtr<Gdk::Pixbuf> error;
		///vector holding the paths to the source file for each image
		static std::vector<std::string> imagePaths;
		///status variable indicating if the last load failed or succeeded
		static bool loaded;


	public:
		///Loads images using the default names (SetDefaultFileNames)
		///and a default path set at compile time
		static void LoadDefaultImages();
		///looks in directory defined by path for images following default naming (SetDefaultFileNames)
		///@param path path to the directory containing the image files
		static void LoadImages(const std::string & path);
		///Loads individual image with file located at path.
		///If the image cannot be loaded, it is set to be the same as ImageName::NO_IMAGE
		///@param path complete path, including filename, to the image
		///@param image The ImageName that will be associated with the image
		static void LoadImage(const std::string & path, ImageName image);

		///@returns loaded
		static bool Loaded();
		///@returns true if image has been loaded and is not equal to NO_IMAGE
		static bool isLoaded(ImageName image);


		///@returns a referemce to the Pixbuf stored matching the identifier images
		///@param image The ImageName of the desired image
		static const Glib::RefPtr<Gdk::Pixbuf> & GetImage(ImageName image);

		///@returns a reference to the default error image
		static const Glib::RefPtr<Gdk::Pixbuf> & GetErrorImage();

	private:
		///this class has no individual instantiation
		ChessGuiImages();

		///Checks to see if a tile image was provided, if not,
		///sets the tile to use BLACK_SQUARE or WHITE_SQUARE as needed
		static void SetTilePatternImages();
		 ///loads  default filenames into imagePaths
		static void SetDefaultFileNames();
		///Prepends path to the contents of imagePaths
		///Does not modify any element of imagePaths that is empty (no default image/image desired)
		static void CombinePathAndFileName(std::string  path);
		///Attempts to load the values of imagePaths as Gdk::Pixbufs into images, matching indexes
		static void LoadImageFiles();

};

#endif
