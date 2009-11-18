// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//
///@file SelectDialog.h  Interface for SelectDialog
///@ingroup selectbox

#ifndef SELECT_DIALOG_H
#define SELECT_DIALOG_H


#include <gtkmm/dialog.h>
#include <gtkmm/label.h>
#include <string>
#include <vector>


///@ingroup selectbox
///@brief Use SelectDialogRun to prompt user to select a response
///The select box function can be used to present a message to the
///user with a set of button responses.
///For example, it could be used to prompt the user upon pawn promotion,
///or ask if they would like to save their game before exiting,
///or to present an error message.
///@note It is NOT required to use this class to pass off the project.
///Its use is purely optional.
///Mostly it's here because I wanted it for my chess implementation so
///I might as well let you have it.
///@note SelectBox is modal in that it does not allow input to the rest
///of the GUI while it is open
class SelectDialog: public Gtk::Dialog
{
	private:
		///Area for displaying a message to the user
		Gtk::Label label;

		///The functionality of this class can only be a accessed through the static method
		SelectDialog(const std::string & title,
					 const std::string & message,
					 const std::vector<std::string> & buttons);

	public:
		///Instantiates a SelectDialog and retrieves the users response.
		///@returns an int defineing the selected response.
		///Automatically assigns the response to each button in order they are
		///in the vector buttons, starting with int 1
		///response = 0 if no response was selected (ie the close 'x' was clicked)
		///if buttons contins no elements, defaults to display button 'ok' with response 1
		///@param title will be placed in the windows titlebar
		///@param message will be displayed in the upper portion of the windows
		///@param buttons contains strings that will be used to label the buttons,
		///from left to right, displayed
		static signed int SelectDialogRun(const std::string & title,
										  const std::string & message,
										  const std::vector<std::string> & buttons);


};


#endif
