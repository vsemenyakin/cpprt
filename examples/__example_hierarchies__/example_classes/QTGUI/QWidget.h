////////////////////////////////////////////////////////////////////////////////
//
// QWidget.h
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef QWIDGET_H_
#define QWIDGET_H_

///////////////////////////////////////////////////////////////////////////////
#include "QObject.h"

///////////////////////////////////////////////////////////////////////////////
class QWidget : public QObject {
	CPPRT_DECLARATION(QWidget);

public:
	QWidget();
	virtual ~QWidget();

	virtual QWidget *dcastQWidget() { return NULL; }
};

///////////////////////////////////////////////////////////////////////////////
#endif /* QWIDGET_H_ */
