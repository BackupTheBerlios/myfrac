
/* ----------------------------------------------------------------------
   $Id: gradlist.h,v 1.2 2006/01/15 11:21:53 r23 Exp $

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

#ifndef GRADLIST_H
#define GRADLIST_H

#include <qlistbox.h>

class Gradient;

/*!
* \brief A listbox widget containing gradients.
*/
class GradientList : public QListBox
{
	Q_OBJECT
public:
	/*!
	* \brief Constructor.
	*/
	GradientList(QWidget* parent=0, const char* name=0);

	/*!
	* \brief Destructor.
	*/
	~GradientList();

public:
	/*!
	* \brief Insert a gradient item.
	*
	* \param text     Name of the item.
	* \param gradient The item's gradient.
	*/
	void insertGradient(const QString& text, const Gradient& gradient);

	/*!
	* \brief Insert a separator item.
	*
	* \param text The separator label.
	*/
	void insertSeparator(const QString& text);

	/*!
	* \brief Change the gradient of the given item.
	*
	* \param index    Index of the item to change.
	* \param gradient The new gradient to set.
	*/
	void setGradient(int index, const Gradient& gradient);

signals:
	/*!
	* \brief Emitted when a gradient item was selected.
	*
	* \param gradient The selected gradient.
	*/
	void gradientSelected(const Gradient& gradient);

private slots:
	void onItemSelected(QListBoxItem* item);
};

#endif
