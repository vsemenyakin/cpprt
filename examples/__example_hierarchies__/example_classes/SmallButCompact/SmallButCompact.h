////////////////////////////////////////////////////////////////////////////////
//
// SmallButCompact.h
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
///////////////////////////////////////////////////////////////////////////////
#ifndef SMALL_BUT_COMPACT_H_
#define SMALL_BUT_COMPACT_H_

///////////////////////////////////////////////////////////////////////////////
#include <cpprt/CPPRTRuntime.h>

///////////////////////////////////////////////////////////////////////////////
class Base : public ICPPRTManagedClass {
	CPPRT_DECLARATION(Base);
};

class Base_Child1 : public virtual Base {
	CPPRT_DECLARATION(Base_Child1);
};

class IBase_Child2 : public virtual Base {
	CPPRT_DECLARATION(IBase_Child2);
public:
	// virtual void shouldBeImplemented0() = 0;  <<<<--- not implemented
};

class Base_Child1AndChild2_Child : public Base_Child1, public IBase_Child2 {
	CPPRT_DECLARATION(Base_Child1AndChild2_Child);
public:
	virtual void shouldBeImplemented0() { } // <<<<--- implemented!!!
};

class Base_Child1AndChild2_Child_Child : public Base_Child1AndChild2_Child {
	CPPRT_DECLARATION(Base_Child1AndChild2_Child_Child);
};

class IUnregistered1 {
public:
	virtual void shouldBeImplemented1() = 0;
};

class IBase_Child1_Child : public Base_Child1, public IUnregistered1 {
	CPPRT_DECLARATION(IBase_Child1_Child);
public:
	// virtual void shouldBeImplemented1() = 0;  <<<<--- not implemented
};

class Unregistered2 { };

class Base_Child2_Child : public IBase_Child2, public Unregistered2 {
	CPPRT_DECLARATION(Base_Child2_Child);
public:
	virtual void shouldBeImplemented0() { } // <<<<--- implemented!!!
};

class Base_Child1_Child_Child : public IBase_Child1_Child {
	CPPRT_DECLARATION(Base_Child1_Child_Child);
public:
	virtual void shouldBeImplemented1() { } // <<<<--- implemented!!!
};

//-----------------------------------------------------------------------------
namespace NamespaceTests {
	class Base_ChildContainer : public Base {
		CPPRT_DECLARATION(Base_ChildContainer);
		
	public:
		class Inner_Child : public Base {
			CPPRT_DECLARATION(Inner_Child);
		};

		class Inner_Child_Child : public Inner_Child {
			CPPRT_DECLARATION(Inner_Child_Child);
		};
	};
}

///////////////////////////////////////////////////////////////////////////////
#endif /* SMALL_BUT_COMPACT_H_ */
