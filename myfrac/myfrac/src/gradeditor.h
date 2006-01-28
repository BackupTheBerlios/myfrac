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

#ifndef GRADEDITOR_H
#define GRADEDITOR_H

#include "gradient.h"

#include <qdialog.h>

class Presets;
class GradientWidget;
class GradientList;

/*!
* \brief The gradient editor dialog box.
*/
class GradientEditor : public QDialog
{
	Q_OBJECT
public:
	/*!
	* \brief Constructor.
	*
	* \param presets  The list of presets to use and edit.
	* \param gradient The current gradient to edit.
	*/
	GradientEditor(Presets* presets, const Gradient& gradient, QWidget* parent=0, const char* name=0);

	/*!
	* \brief Destructor.
	*/
	~GradientEditor();

signals:
	/*!
	* \brief Apply a new gradient.
	*
	* Emitted when the Apply or OK button was pressed.
	*
	* \param gradient The gradient to apply.
	*/
	void applyGradient(const Gradient& gradient);

private slots:
	// button slots
	void onSaveAs();
	void onSetDefault();
	void onDelete();
	void onApply();
	void onOK();

private:
	// fill the presets list
	void fillList();

private:
	Presets* _presets;
	Gradient _currentGradient;

	GradientWidget* _gradientWidget;
	GradientList* _gradientList;
};

#endif
