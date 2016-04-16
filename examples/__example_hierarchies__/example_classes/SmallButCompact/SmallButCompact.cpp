////////////////////////////////////////////////////////////////////////////////
//
// SmallButCompact.cpp
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
///////////////////////////////////////////////////////////////////////////////
#include "SmallButCompact.h"

///////////////////////////////////////////////////////////////////////////////
CPPRT_CLASS_IMPLEMENTATION_BASE_0(Base)

CPPRT_CLASS_IMPLEMENTATION_BASE_1(Base_Child1, Base)
CPPRT_INTERFACE_IMPLEMENTATION_BASE_1(IBase_Child2, Base)

CPPRT_CLASS_IMPLEMENTATION_BASE_2(Base_Child1AndChild2_Child, Base_Child1,\
		IBase_Child2)

CPPRT_CLASS_IMPLEMENTATION_BASE_1(Base_Child1AndChild2_Child_Child,\
		Base_Child1AndChild2_Child)

// IUnregistered1 <<<--- Is not registered
// Here we don't register inheritance from IUnregistered1:
CPPRT_INTERFACE_IMPLEMENTATION_BASE_1(IBase_Child1_Child, Base_Child1)

// IUnregistered2 <<<--- Is not registered
// Here we don't register inheritance from IUnregistered2:
CPPRT_CLASS_IMPLEMENTATION_BASE_1(Base_Child2_Child, IBase_Child2)

CPPRT_CLASS_IMPLEMENTATION_BASE_1(Base_Child1_Child_Child, IBase_Child1_Child)

//-----------------------------------------------------------------------------
CPPRT_CLASS_IMPLEMENTATION_BASE_1(NamespaceTests::Base_ChildContainer, Base)
CPPRT_CLASS_IMPLEMENTATION_BASE_1(\
		NamespaceTests::Base_ChildContainer::Inner_Child, Base)

CPPRT_CLASS_IMPLEMENTATION_BASE_1(\
		NamespaceTests::Base_ChildContainer::Inner_Child_Child,
		NamespaceTests::Base_ChildContainer::Inner_Child)

///////////////////////////////////////////////////////////////////////////////
