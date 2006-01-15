/* ----------------------------------------------------------------------
   $Id: main.cpp,v 1.2 2006/01/15 11:21:53 r23 Exp $

   myFrac
   http://developer.berlios.de/projects/myfrac/

   Copyright (c) 2006 by r23
-------------------------------------------------------------------------
   Based on:

   Fraqtive Version 0.3.1
   http://www.mimec.w.pl

   Copyright (C) 2005 Michal Mecinski
-------------------------------------------------------------------------
   Released under the GNU General Public License
------------------------------------------------------------------------- */

/**************************************************************************
* This file is part of the Fraqtive program.
* Copyright (C) 2005 Michal Mecinski.
* This program is licensed under the GNU General Public License.
**************************************************************************/

#include "fraqtive.h"

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

int main(int argc, char** argv)
{
	KAboutData about("fraqtive", I18N_NOOP("Fraqtive"), "0.3.0",
		I18N_NOOP("Program for drawing Mandelbrot and Julia fractals."),
		KAboutData::License_GPL, "Copyright (C) 2005 Michal Mecinski", NULL,
		"http://www.mimec.w.pl",
		"mimec@users.sourceforge.net");
	about.addAuthor("Michal Mecinski", NULL, "mimec@users.sourceforge.net");
	KCmdLineArgs::init(argc, argv, &about);

	KApplication app;

	FraqtiveWindow wnd;
	app.setMainWidget(&wnd);
	wnd.show();

	return app.exec();
}
