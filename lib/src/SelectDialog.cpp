// Author: Owen Merkling,,, <omerkling@gmail.com>, (C) 2008
//
// Copyright: For use by the students of CS 240 at BYU
//
//

#include <SelectDialog.h>


SelectDialog::SelectDialog(const std::string & title,
						   const std::string & message,
						   const std::vector<std::string> & buttons)
	:Dialog(title,true),label(message)
{
	//pack label
	Gtk::VBox * vbox = get_vbox();
	vbox->pack_start(label,false,false,4);
	label.show();
	//set up buttons
	if(!buttons.size()>0) // ok response set
	{
		add_button("OK",1);
	}
	else
	{
		for( unsigned int i=0;i<buttons.size();i++)
		{
			add_button(buttons[i],i+1);
		}
	}
}

signed int SelectDialog::SelectDialogRun(const std::string & title,
										 const std::string & message,
										 const std::vector<std::string> & buttons)
{
	SelectDialog dialog(title,message,buttons);

	int result = dialog.run();
	if(result == Gtk::RESPONSE_NONE)
	{
		g_message("No Response Selected");
		return 0;
	}
	else if( (result<0) || result>int(buttons.size()))
	{
		g_warning("SelectDialogRun::Unexpected Response");
		return 0;
	}
	else
		return (signed int)result;

}

