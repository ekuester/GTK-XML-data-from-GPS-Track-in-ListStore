//$Id: main.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "xmltablewindow.h"

#ifndef NLS
#define NLS 1
#define PROGRAMNAME_LOCALEDIR "."
#define GETTEXT_PACKAGE "xmlTableView"
#endif

using namespace std;

int main(int argc, char *argv[])
{
#ifdef NLS
	setlocale(LC_ALL, "");
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif

    // with german locale ustring -> double not possible (has decimal comma)
    //std::locale::global(std::locale(""));

    auto app = Gtk::Application::create(argc, argv, "org.kuester.application");

    XMLTableWindow window(app);

    //Shows the window and returns when it is closed.
    return app->run(window);
}

