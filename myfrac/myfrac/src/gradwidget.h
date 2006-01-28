/***************************************************************************
                          gradwidget.h
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

#ifndef GRADCONTROL_H
#define GRADCONTROL_H

#include "gradient.h"

#include <qwidget.h>
#include <qrect.h>

/*!
* \brief A widget for editing the gradient splines.
*/
class GradientWidget : public QWidget
{
	Q_OBJECT
public:
	/*!
	* \brief Constructor.
	*/
	GradientWidget(QWidget* parent=0, const char* name=0);

	/*!
	* \brief Destructor.
	*/
	~GradientWidget();

public:
	/*!
	* \brief Return the minimum size of the widget.
	*/
	QSize minimumSizeHint() const;

	/*!
	* \brief Return the recommended size of the widget.
	*/
	QSize sizeHint() const;

	/*!
	* \brief Get the current gradient.
	*
	* \return The gradient object.
	*/
	const Gradient& getGradient() const
	{
		return _gradient;
	}

public slots:
	/*!
	* \brief Set the gradient to edit.
	*
	* \param gradient The gradient object.
	*/
	void setGradient(const Gradient& gradient);

	/*!
	* \brief Set a default RGB gradient.
	*/
	void newRgb();

	/*!
	* \brief Set a default HSV gradient.
	*/
	void newHsv();

	/*!
	* \brief Invert the current gradient.
	*/
	void invert();

private:
	// process events
	void paintEvent(QPaintEvent* e);
	void resizeEvent(QResizeEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);

	// layout the area rectangles
	void calcRects();

private:
	Gradient _gradient;

	// area rectangles
	QRect _gradRect;
	QRect _splineRect[3];

	// node dragging
	int _dragSpline;
	int _dragNode;
	bool _dragRemove;
};

#endif
