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

#include "genthread.h"
#include "generator.h"

GeneratorThread generatorThread;

GeneratorThread::GeneratorThread()
{
}

GeneratorThread::~GeneratorThread()
{
}

void GeneratorThread::run()
{
	_queueMutex.lock();

	for (;;) {
		while (!_queue.isEmpty()) {
			Generator* generator = _queue.first();
			_queue.removeFirst();
			_queueMutex.unlock();
			generator->generate();
			_queueMutex.lock();
		}

		if (_abort)
			break;

		_condition.wait(&_queueMutex);
	}
	
	_queueMutex.unlock();
}

void GeneratorThread::wakeUp()
{
	_condition.wakeOne();
}

void GeneratorThread::abort()
{
	_queueMutex.lock();
	_queue.clear();
	_queueMutex.unlock();
	_abort = true;
	_condition.wakeOne();
	wait();
}

void GeneratorThread::addToQueue(Generator* generator, bool highPriority)
{
	_queueMutex.lock();
	if (highPriority)
		_queue.prepend(generator);
	else
		_queue.append(generator);
	_queueMutex.unlock();
	_condition.wakeOne();
}
