/***************************************************************************
                          presets.h
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

#ifndef PRESETS_H
#define PRESETS_H

#include "gradient.h"

#include <qstringlist.h>
#include <qvaluelist.h>

class KConfig;

/*!
* \brief A class for storing the default gradient and gradient presets.
*/
class Presets
{
public:
	/*!
	* \brief Constructor.
	*/
	Presets();

	/*!
	* \brief Destructor.
	*/
	~Presets();

public:
	/*!
	* \brief Load presets from application settings.
	*/
	void loadPresets(KConfig* config);

	/*!
	* \brief Store presets in application settings.
	*/
	void savePresets(KConfig* config);

	/*!
	* \brief Get the default gradient.
	*
	* \return The default gradient.
	*/
	const Gradient& getDefault() const
	{
		return _default;
	}

	/*!
	* \brief Set the default gradient.
	*
	* \param gradient The new default gradient.
	*/
	void setDefault(const Gradient& gradient)
	{
		_default = gradient;
	}

	/*!
	* \brief Return the number of presets.
	*
	* \return The number of presets.
	*/
	int getPresetsCnt() const
	{
		return _nameList.size();
	}

	/*!
	* \brief Get the name of the given preset.
	*
	* \param index The index of the preset.
	* \return      The name of the preset.
	*/
	const QString& getPresetName(int index)
	{
		return _nameList[index];
	}

	/*!
	* \brief Get the gradient of the given preset.
	*
	* \param index The index of the preset.
	* \return      The gradient of the preset.
	*/
	const Gradient& getPresetGradient(int index)
	{
		return _gradientList[index];
	}

	/*!
	* \brief Set the preset with the given name.
	*
	* \param name     The name of the preset to add or modify.
	* \param gradient The gradient of the preset.
	*/
	void setPreset(const QString& name, const Gradient& gradient);

	/*!
	* \brief Remove the preset with the given name.
	*
	* \param name     The name of the preset to remove.
	*/
	void removePreset(const QString& name);

private:
	typedef QStringList NameList;
	typedef QValueList<Gradient> GradientList;

	Gradient _default;
	NameList _nameList;
	GradientList _gradientList;
};

#endif
