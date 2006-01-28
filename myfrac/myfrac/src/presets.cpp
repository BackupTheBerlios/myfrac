/***************************************************************************
                          presets.cpp
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

#include "presets.h"

#include <kconfig.h>

Presets::Presets() :
	_default(true)
{
	_default.getSpline(0).addNode(0.0, 0.0);
	_default.getSpline(0).addNode(1.0, 1.0);
	_default.getSpline(1).addNode(0.5, 0.75);
	_default.getSpline(2).addNode(0.0, 0.0);
	_default.getSpline(2).addNode(0.25, 1.0);
	_default.getSpline(2).addNode(0.5, 0.0);
	_default.getSpline(2).addNode(0.75, 1.0);
}

Presets::~Presets()
{
}

void Presets::loadPresets(KConfig* config)
{
	config->setGroup("Gradient Presets");

	QStringList list = config->readListEntry("Default");
	if (list.size() == 4) {
		Gradient gradient(list[0] == "hsv");
		gradient.getSpline(0).fromString(list[1]);
		gradient.getSpline(1).fromString(list[2]);
		gradient.getSpline(2).fromString(list[3]);
		setDefault(gradient);
	}

	int count = config->readNumEntry("Count", 0);
	for (int i = 0; i < count; i++) {
		QStringList list = config->readListEntry(QString("Preset %1").arg(i));
		if (list.size() == 5) {
			Gradient gradient(list[1] == "hsv");
			gradient.getSpline(0).fromString(list[2]);
			gradient.getSpline(1).fromString(list[3]);
			gradient.getSpline(2).fromString(list[4]);
			setPreset(list[0], gradient);
		}
	}
}

void Presets::savePresets(KConfig* config)
{
	config->setGroup("Gradient Presets");

	QStringList list;
	list.append(_default.isHsv() ? "hsv" : "rgb");
	list.append(_default.getSpline(0).toString());
	list.append(_default.getSpline(1).toString());
	list.append(_default.getSpline(2).toString());

	config->writeEntry("Default", list);

	int oldCount = config->readNumEntry("Count", 0);
	int newCount = (int)_nameList.size();

	config->writeEntry("Count", newCount);
	for (int i = 0; i < newCount; i++) {
		QStringList list;
		list.append(_nameList[i]);
		list.append(_gradientList[i].isHsv() ? "hsv" : "rgb");
		list.append(_gradientList[i].getSpline(0).toString());
		list.append(_gradientList[i].getSpline(1).toString());
		list.append(_gradientList[i].getSpline(2).toString());
		config->writeEntry(QString("Preset %1").arg(i), list);
	}
	for (int i = newCount; i < oldCount; i++)
		config->deleteEntry(QString("Preset %1").arg(i));
}

void Presets::setPreset(const QString& name, const Gradient& gradient)
{
	NameList::iterator nameIt = _nameList.begin();
	GradientList::iterator gradIt = _gradientList.begin();

	for (; nameIt != _nameList.end(); ++nameIt, ++gradIt) {
		if (*nameIt == name) {
			*gradIt = gradient;
			return;
		} else if (*nameIt > name) {
			_nameList.insert(nameIt, name);
			_gradientList.insert(gradIt, gradient);
			return;
		}
	}

	_nameList.append(name);
	_gradientList.append(gradient);
}

void Presets::removePreset(const QString& name)
{
	int i = _nameList.findIndex(name);
	if (i >= 0) {
		_nameList.remove(_nameList.at(i));
		_gradientList.remove(_gradientList.at(i));
	}
}
