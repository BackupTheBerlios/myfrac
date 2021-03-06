/***************************************************************************
                          gradient.h
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

#ifndef GRADIENT_H
#define GRADIENT_H

#include "spline.h"

#include <qstring.h>
#include <qcolor.h>

static const int GRADIENT_LENGTH = 4096;

/*!
* \brief The gradient of colors.
*
* The gradients consists of three splines which define the waveforms of the
* color components. The gradient may work in a RGB mode or HSV mode.
*/
class Gradient
{
public:
	/*!
	* \brief Constructor.
	*/
	Gradient();

	/*!
	* \brief Constructor.
	*
	* \param hsv Mode of the gradient, \c true - HSV, \c false - RGB.
	*/
	Gradient(bool hsv);

	/*!
	* \brief Destructor.
	*/
	~Gradient();

public:
	/*!
	* \brief Get the mode of the gradient.
	*
	* \return \c true if gradient is HSV, \c false if RGB.
	*/
	bool isHsv() const
	{
		return _isHsv;
	}

	/*!
	* \brief Get one of the splines of the gradient.
	*
	* \param index The spline index (0, 1 or 2).
	* \return The spline object.
	*/
	const Spline& getSpline(int index) const
	{
		return _spline[index];
	}

	/*!
	* \brief Get one of the splines of the gradient.
	*
	* \param index The spline index (0, 1 or 2).
	* \return The spline object.
	*/
	Spline& getSpline(int index)
	{
		return _spline[index];
	}

	/*!
	* \brief Generate the color table for the gradient.
	*
	* \param[out] buffer The array to fill.
	* \param      length The length of the array.
	* \param      data   The components array to use (3 x length). If \c NULL,
	*                    a temporary array is used.
	*/
	void fillGradient(QRgb* buffer, int length = GRADIENT_LENGTH, double* data = NULL) const;

	/*!
	* \brief Invert the gradient.
	*/
	void invert();

	/*!
	* \brief Calculate a color from HSV components.
	*
	* All components should be in range from 0 to 1.
	*
	* \param h The hue component.
	* \param s The saturation component.
	* \param v The value component.
	* \return  The calculated color.
	*/
	static QRgb hsvToRgb(double h, double s, double v)
	{
		double r, g, b;

		double sb = 128.0 * (1.0 - s);
		double va, vb;
		if (v > 0.5) {
			va = 2.0 - 2.0 * v;
			vb = 510.0 * v - 255.0;
		} else {
			va = 2.0 * v;
			vb = 0.0;
		}

		int hh = (int)(6.0 * h);
		double f = 6.0 * h - (double)hh;
		if (hh & 1)
			f = 1.0 - f;

		double m = (255.0 * s + sb) * va + vb;
		double n = sb * va + vb;
		double p = (255.0 * f * s + sb) * va + vb;

		switch (hh) {
		case 0: r = m; g = p; b = n; break;
		case 1: r = p; g = m; b = n; break;
		case 2: r = n; g = m; b = p; break;
		case 3: r = n; g = p; b = m; break;
		case 4: r = p; g = n; b = m; break;
		case 5: r = m; g = n; b = p; break;
		default: r = m; g = n; b = n; break;
		}

		return qRgb((int)r, (int)g, (int)b);
	}

private:
	bool _isHsv;
	Spline _spline[3];
};

#endif
