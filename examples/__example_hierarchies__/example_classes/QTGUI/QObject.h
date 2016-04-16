////////////////////////////////////////////////////////////////////////////////
//
// QObject.h
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef QOBJECT_H_
#define QOBJECT_H_

///////////////////////////////////////////////////////////////////////////////
#include <cpprt/CPPRTRuntime.h>

#include <cstddef> // for NULL constnat

///////////////////////////////////////////////////////////////////////////////
class QAbstractButton;
class QAbstractScrollArea;
class QCheckBox;
class QFrame;
class QGraphicsView;
class QLabel;
class QObject;
class QProgressBar;
class QPushButton;
class QRadioButton;
class QTextEdit;
class QThread;
class QWidget;

///////////////////////////////////////////////////////////////////////////////
class QObject : public ICPPRTManagedClass {
	CPPRT_DECLARATION(QObject);

public:
	QObject();
	virtual ~QObject();

	virtual QAbstractButton *dcastQAbstractButton() { return NULL; }
	virtual QAbstractScrollArea *dcastQAbstractScrollArea() { return NULL; }
	virtual QCheckBox *dcastQCheckBox() { return NULL; }
	virtual QFrame *dcastQFrame() { return NULL; }
	virtual QGraphicsView *dcastQGraphicsView() { return NULL; }
	virtual QLabel *dcastQLabel() { return NULL; }
	virtual QObject *dcastQObject() { return NULL; }
	virtual QProgressBar *dcastQProgressBar() { return NULL; }
	virtual QPushButton *dcastQPushButton() { return NULL; }
	virtual QRadioButton *dcastQRadioButton() { return NULL; }
	virtual QTextEdit *dcastQTextEdit() { return NULL; }
	virtual QThread *dcastQThread() { return NULL; }
	virtual QWidget *dcastQWidget() { return NULL; }
};

///////////////////////////////////////////////////////////////////////////////
#endif /* QOBJECT_H_ */
