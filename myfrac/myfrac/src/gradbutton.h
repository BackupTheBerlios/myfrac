/***************************************************************************
                          gradbutton.h
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

#ifndef GRADBUTTON_H
#define GRADBUTTON_H

#include <qpushbutton.h>

class Gradient;

/*!
* \brief A simple gradient preview widget.
*/
class GradientButton : public QPushButton
{
	Q_OBJECT
public:
	/*!
	* \brief Constructor.
	*/
	GradientButton(QWidget* parent=0, const char* name=0);

	/*!
	* \brief Destructor.
	*/
	~GradientButton();

public slots:
	/*!
	* \brief Set the displayed gradient.
	*
	* \param data   The gradient's color table.
	* \param scale  Not used.
	* \param offset Not used.
	*/
	void setGradient(const QRgb* data, double scale, double offset);

protected:
	void drawButtonLabel(QPainter* p);
	QSize sizeHint() const;

private:
	const QRgb* _gradientData;
};

#endif
