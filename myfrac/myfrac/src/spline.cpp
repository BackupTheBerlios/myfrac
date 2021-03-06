/***************************************************************************
                          spline.cpp
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

#include "spline.h"

#include <stdlib.h>

#include <qstringlist.h>

#include <cmath>

Spline::Spline()
{
}

Spline::~Spline()
{
}

int Spline::findNode(QSize gradSize, QPoint ptPos, QSize ptSize) const
{
	for (int i = 0; i < (int)_array.size(); i++) {
		int x = (int)(_array[i]._x * gradSize.width());
		int y = (int)((1.0 - _array[i]._y) * gradSize.height());
		if (abs(ptPos.x() - x) <= ptSize.width() && abs(ptPos.y() - y) <= ptSize.height())
			return i;
	}
	return -1;
}
	
int Spline::insertNode(double x, double y)
{
	for (int i = 0; i < (int)_array.size(); i++) {
		if (_array[i]._x > x) {
			_array.insert(_array.begin() + i, Coord(x, y));
			return i;
		}
	}
	_array.push_back(Coord(x, y));
	return (int)_array.size() - 1;
}

void Spline::invert()
{
	int nodes = _array.size();
	for (int i = 0; i < nodes / 2; i++) {
		double tx = _array[i]._x;
		double ty = _array[i]._y;
		_array[i]._x = 1.0 - _array[nodes - i - 1]._x;
		_array[i]._y = _array[nodes - i - 1]._y;
		_array[nodes - i - 1]._x = 1.0 - tx;		
		_array[nodes - i - 1]._y = ty;		
	}
	if (nodes % 2)
		_array[nodes / 2]._x = 1.0 - _array[nodes / 2]._x;
}

void Spline::generateSpline(double* buffer, int length) const
{
	int nodes = _array.size();

	if (nodes == 0) {
		for (int i = 0; i < length; i++)
			buffer[i] = 0.0;
		return;
	}
	if (nodes == 1) {
		for (int i = 0; i < length; i++)
			buffer[i] = _array[0]._y;
		return;
	}

	const int SUBSEGMENTS = 8;
	double h[SUBSEGMENTS+1][4];

	for (int i = 0; i <= SUBSEGMENTS; i++) {
		double s = (double)i / (double)SUBSEGMENTS;
		double s2 = s * s;
		double s3 = s2 * s;
		h[i][0] = 2*s3 - 3*s2 + 1;
		h[i][1] = -2*s3 + 3*s2;
		h[i][2] = s3 - 2*s2 + s;
		h[i][3] = s3 - s2;
	}

	for (int seg = 0; seg < nodes; seg++) {
		double p1x = _array[seg]._x;
		double p1y = _array[seg]._y;

		double p2x, p2y;
		if (seg < nodes - 1) {
			p2x = _array[seg + 1]._x;
			p2y = _array[seg + 1]._y;
		} else {
			p2x = _array[0]._x + 1.0;
			p2y = _array[0]._y;
		}

		double t1x, t1y;
		if (seg > 0) {
			t1x = p1x - _array[seg - 1]._x;
			t1y = p1y - _array[seg - 1]._y;
		} else {
			t1x = p1x - _array[nodes - 1]._x + 1.0;
			t1y = p1x - _array[nodes - 1]._y;
		}

		double t2x, t2y;
		if (seg < nodes - 2) {
			t2x = _array[seg + 2]._x - p2x;
			t2y = _array[seg + 2]._y - p2y;
		} else {
			t2x = _array[seg + 2 - nodes]._x - p2x + 1.0;
			t2y = _array[seg + 2 - nodes]._y - p2y;
		}

		double dx = std::fabs(p2x - p1x);
		double alfa = 0.45 * (dx < 0.15 ? dx / 0.15 : 1.0);

		int lx = -1;
		double ly = 0.0;

		for (int i=0; i <= SUBSEGMENTS; i++) {
			double py = h[i][0]*p1y + h[i][1]*p2y + (h[i][2]*t1y + h[i][3]*t2y) * alfa;
			double px = h[i][0]*p1x + h[i][1]*p2x + (h[i][2]*t1x + h[i][3]*t2x) * alfa;

			if (py < 0.0)
				py = 0.0;
			else if (py > 1.0)
				py = 1.0;

			int x = (int)(px * length + 0.5);
			int cx = x - lx;

			if (i > 0 && cx > 0) {
				double scale = (py - ly) / (double)cx;
				for (int ix = 0; ix < cx; ix++)
					buffer[(ix + lx) % length] = ly + ix * scale;
			}

			lx = x;
			ly = py;
		}
	}
}

QString Spline::toString() const
{
	QStringList list;

	for (int i = 0; i < (int)_array.size(); i++) {
		QString str;
		list.append(str.setNum(_array[i]._x));
		list.append(str.setNum(_array[i]._y));
	}

	return list.join(";");
}

void Spline::fromString(const QString& string)
{
	QStringList list = QStringList::split(';', string);

	_array.clear();

	double lx = 0.0;
	for (QStringList::iterator it = list.begin(); it != list.end(); ++it) {
		double x = (*it).toDouble();
		if (++it != list.end()) {
			double y = (*it).toDouble();
			if (x >= lx && x <= 1.0 && y >= 0.0 && y <= 1.0)
				_array.push_back(Coord(x, y));
		}
		lx = x;
	}
}
