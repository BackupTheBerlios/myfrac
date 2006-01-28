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

#ifndef GENTHREAD_H
#define GENTHREAD_H

#include <qptrlist.h>
#include <qthread.h>
#include <qwaitcondition.h>
#include <qmutex.h>

class Generator;

/*!
* \brief The thread used for generating data asynchronously.
*/
class GeneratorThread : public QThread
{
public:
	/*!
	* \brief Constructor.
	*/
	GeneratorThread();

	/*!
	* \brief Destructor.
	*/
	~GeneratorThread();

public:
	/*!
	* \brief Wake the thread to check its generator queue.
	*/
	void wakeUp();

	/*!
	* \brief Notify and wait for the thread to end.
	*/
	void abort();

	/*!
	* \brief Add the generator to the queue and wake the thread.
	*
	* \param generator    The generator to process.
	* \param highPriority If \c true, the generator is added to the front of
	*                     the queue. If \c false, the generator is added to the back.
	*/
	void addToQueue(Generator* generator, bool highPriority);

protected:
	void run();

private:
	typedef QPtrList<Generator> GeneratorQueue;

	bool _abort;

	// a condition to put the thread to sleep
	QWaitCondition _condition;

	// a protection mutex for the queue
	QMutex _queueMutex;

	// the generator queue to process
	GeneratorQueue _queue;
};

extern GeneratorThread generatorThread;

#endif
