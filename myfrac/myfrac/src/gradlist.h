/***************************************************************************
                          $FILENAME$  
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
