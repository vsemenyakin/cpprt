////////////////////////////////////////////////////////////////////////////////
//
// QThread.h
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef QTHREAD_H_
#define QTHREAD_H_

///////////////////////////////////////////////////////////////////////////////
#include "QObject.h"

///////////////////////////////////////////////////////////////////////////////
class QThread : public QObject {
	CPPRT_DECLARATION(QThread);

public:
	QThread();
	virtual ~QThread();

	virtual QThread *dcastQThread() { return this; }
};

///////////////////////////////////////////////////////////////////////////////
#endif /* QTHREAD_H_ */
