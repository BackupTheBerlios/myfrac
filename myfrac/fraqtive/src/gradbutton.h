/* ----------------------------------------------------------------------
   $Id: gradbutton.h,v 1.2 2006/01/15 11:21:53 r23 Exp $

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
