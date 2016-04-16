////////////////////////////////////////////////////////////////////////////////
//
// CPPRTRuntime.cpp
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
////////////////////////////////////////////////////////////////////////////////
#include <cpprt/CPPRTRuntime.h>

#include <stddef.h> // for size_t
#include <string.h> // for strcmp

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
void CPPRTRuntime::ClassData::internal_initialize(
		const char *inFullName, IFabric *inFabric)
{
	//Setup name
	_fullName = inFullName;
	_namePointer = _fullName + strlen(_fullName) - 1;

	while(_fullName != _namePointer && *(_namePointer - 1) != ':') --_namePointer;

	//Setup fabric
	_fabric = inFabric;
}

void CPPRTRuntime::ClassData::internal_addParent(ClassData *inParent) {
	_parents.push_back(inParent);
	inParent->_children.push_back(this);
}

//-- Fabric method
ICPPRTManagedClass *CPPRTRuntime::ClassData::createObject() {
	//TODO: Though an exeption if is abstract
	return _fabric->createObject();
}

////////////////////////////////////////////////////////////////////////////////
//- Methods
CPPRTRuntime::CPPRTRuntime() : _classesManagers() { }

//-- Runtime helpers
CPPRTRuntime::ClassData *CPPRTRuntime::internal_dataByName(
		const char *inFullName)
{
	for (size_t theIndex = 0, theSize = _classesManagers.size();
			theIndex < theSize; ++theIndex)
	{
		ClassData *theManager = _classesManagers[theIndex];
		if (0 == strcmp(theManager->fullName(), inFullName)) return theManager;
	}
	return NULL;
}

//-- Public API
void CPPRTRuntime::internal_addWithFiltering(ClassData *inData,
		std::vector<ClassData *> &outRegistries, OservingFlags inOservingFlags)
{
	if (!((inOservingFlags & ObservingFlagWithoutInterface) &&
			!inData->isInterface()))
	{
		outRegistries.push_back(inData);
	}
}

void CPPRTRuntime::internal_observeChildsDirect(ClassData *inData,
		std::vector<ClassData *> &outRegistries, OservingFlags inOservingFlags)
{
	if (!(inOservingFlags & ObservingFlagIgnoreBase)) {
		internal_addWithFiltering(inData, outRegistries, inOservingFlags);
	}

	std::vector<ClassData *> &theChildren = inData->_children;
	for (size_t theIndex = 0, theSize = theChildren.size();
			theIndex < theSize; ++theIndex)
	{
		internal_addWithFiltering(
				theChildren[theIndex], outRegistries, inOservingFlags);
	}
}

void CPPRTRuntime::internal_observeChildsAll(ClassData *inData,
		std::vector<ClassData *> &outRegistries, OservingFlags inOservingFlags)
{
	std::vector<ClassData *> theObserving;

	// Base iteration
	if (!(inOservingFlags & ObservingFlagIgnoreBase))
		internal_addWithFiltering(inData, outRegistries, inOservingFlags);

	std::vector<ClassData *> &ins = inData->_children;
	theObserving.insert(theObserving.end(), ins.begin(), ins.end());

	// Other levels
	size_t theIndex = 0;
	size_t theSize = theObserving.size();

	while (theIndex < theSize) {
		for (; theIndex < theSize; ++theIndex) {
			ClassData *theData = theObserving[theIndex];
			internal_addWithFiltering(theData, outRegistries, inOservingFlags);

			std::vector<ClassData *> &ins = theData->_children;
			theObserving.insert(theObserving.end(), ins.begin(), ins.end());
		}

		theSize = theObserving.size();
	}
}

//-- Initialization API
CPPRTRuntime::ClassData *CPPRTRuntime::createClassData(
		const char *inFullName, IFabric *inFabric)
{
	ClassData *theData = new ClassData();
	_classesManagers.push_back(theData);
	theData->internal_initialize(inFullName, inFabric);

	return theData;
}

CPPRTRuntime::ClassData *CPPRTRuntime::createClassData(
		const char *inFullName, IFabric *inFabric,
		ClassData *inParent0)
{
	ClassData *theData = new ClassData();
	_classesManagers.push_back(theData);
	theData->internal_initialize(inFullName, inFabric);
	theData->internal_addParent(inParent0);
	return theData;
}

CPPRTRuntime::ClassData *CPPRTRuntime::createClassData(
		const char *inFullName, IFabric *inFabric,
		ClassData *inParent0, ClassData *inParent1)
{
	ClassData *theData = new ClassData();
	_classesManagers.push_back(theData);
	theData->internal_initialize(inFullName, inFabric);
	theData->internal_addParent(inParent0);
	theData->internal_addParent(inParent1);
	return theData;
}

//-- Public API
void CPPRTRuntime::observeChilds(ClassData *inBaseRegistry,
		std::vector<ClassData *> &outRegistries, OservingFlags inFlags)
{
	if (inBaseRegistry == NULL) {
		for (size_t theIndex = 0, theSize = _classesManagers.size();
				theIndex < theSize; ++theIndex)
		{
			ClassData *theData = _classesManagers[theIndex];
			if (inFlags & ObservingFlagRecursive) {
				internal_observeChildsAll(
						inBaseRegistry, outRegistries, inFlags);
			} else if (0 == _classesManagers[theIndex]->_parents.size()) {
				internal_addWithFiltering(theData, outRegistries, inFlags);
			}
		}
	} else {
		if (inFlags & ObservingFlagRecursive) {
			internal_observeChildsAll(
					inBaseRegistry, outRegistries, inFlags);
		} else {
			internal_observeChildsDirect(
					inBaseRegistry, outRegistries, inFlags);
		}
	}
}

CPPRTRuntime::ClassData *CPPRTRuntime::getClassData(const char *inFullName) {
	return internal_dataByName(inFullName);
}

ICPPRTManagedClass *CPPRTRuntime::createObject(const char *inFullName) {
	CPPRTRuntime::ClassData *theData = internal_dataByName(inFullName);
	//TODO: Through an exception if no class found
	return theData->createObject();
}

//------------------------------------------------------------------------------
CPPRTRuntime &cppRuntime() {
	static CPPRTRuntime sManager;
	return sManager;
}

////////////////////////////////////////////////////////////////////////////////
