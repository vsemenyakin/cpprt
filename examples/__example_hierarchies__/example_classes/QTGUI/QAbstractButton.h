////////////////////////////////////////////////////////////////////////////////
//
// QAbstractButton.h
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef QABSTRACTBUTTON_H_
#define QABSTRACTBUTTON_H_

///////////////////////////////////////////////////////////////////////////////
#include "QWidget.h"

///////////////////////////////////////////////////////////////////////////////
class QAbstractButton : public QWidget {
	CPPRT_DECLARATION(QAbstractButton);

public:
	QAbstractButton();
	virtual ~QAbstractButton();

	virtual QAbstractButton *dcastQAbstractButton() { return this; }
};

///////////////////////////////////////////////////////////////////////////////
#endif /* QABSTRACTBUTTON_H_ */