/***************************************************************************
                          main.cpp  -  initialization
                             -------------------
    begin                : Do Jan 12 2006
    copyright            : (C) 2006 by r23
    email                : info@r23.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/**************************************************************************
* This file is part of the Fraqtive program.
* Copyright (C) 2005 Michal Mecinski.
* This program is licensed under the GNU General Public License.
**************************************************************************/

#include "myfrac.h"

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>


static const char *description =
	I18N_NOOP("Program for drawing Mandelbrot and Julia fractals.");
static const char *text =
	I18N_NOOP("Based on Fraqtive, (C) 2005 Michal Mecinski.");

int main( int argc, char** argv)
{
	KAboutData aboutData( "myfrac", I18N_NOOP("MyFrac"),
				"-dev", description, KAboutData::License_GPL,
				"Copyright (C) 2006 r23", text,
				"http://www.myoos.de/fraktal/",
				"myfrac@r23.de");
	aboutData.addAuthor("r23", "Current maintainer", "info@r23.de");
	aboutData.addAuthor("Michal Mecinski", "Original author", "mimec@users.sourceforge.net");
        KCmdLineArgs::init(argc, argv, &aboutData);

	KApplication app;

	MyFracWindow wnd;
	app.setMainWidget(&wnd);
	wnd.show();

	return app.exec();
}
