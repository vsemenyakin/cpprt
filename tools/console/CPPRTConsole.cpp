////////////////////////////////////////////////////////////////////////////////
//
// CPPRTConsole.cpp
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
////////////////////////////////////////////////////////////////////////////////
// Cpprt includes
#include <cpprt/CPPRTRuntime.h>

// Objects storing
#include <map>

// Work with command line
#include <iostream>
#include <vector>
#include <string>

// Test classes hierarchy

//NB: Uncomment next includes to test hierarchies
#include <example_classes/QTGUI/QTGUI.h>
#include <example_classes/SmallButCompact/SmallButCompact.h>

using namespace std;

//----------------------------- Global state -----------------------------------
static const size_t kCommandTextMaxSize = 1000;

typedef std::map<std::string, ICPPRTManagedClass *> ObjectsStorage;
typedef ObjectsStorage::iterator ObjectsIterator;

ObjectsStorage gObjects;

//----------------------------- Utils ------------------------------------------
//- - - - - - - - - - - - - - - Error handling - - - - - - - - - - - - - - - - -
void printUndefinedCommandError(const char *inCommandName) {
	std::cout << "ERROR: There is no such command {" << inCommandName << "}" <<
			". Use \"help\" command to see supported commands." <<
					std::endl;
}

void printClassError(const char *inClassName) {
	std::cout << "ERROR: Class with name {" << inClassName << "} "
			"wasn\'t registered" << std::endl;
}

enum ObjectErrorType {
	ObjectErrorTypeNoObjectFound,
	ObjectErrorTypeObjectCurrentlyExists
};

void printObjectError(const char *inObjectName, ObjectErrorType inErrorType) {
	switch(inErrorType) {
	case ObjectErrorTypeNoObjectFound:
		std::cout << "ERROR: Can\'t find object with name {" << inObjectName <<
				"}" << std::endl;
		return;

	case ObjectErrorTypeObjectCurrentlyExists:
		std::cout << "ERROR: Object with name {" << inObjectName <<
				"} is currently exists" << std::endl;
		return;
	}
}

//- - - - - - - - - - - - - - - Object actions - - - - - - - - - - - - - - - - -
void printObject(const ObjectsIterator &inIterator) {
	std::cout << "[name=\"" << inIterator->first << "\" type=\"" <<
			inIterator->second->getClassDataRT()->fullName() << "\"]";
}

void removeObject(const ObjectsIterator &inIterator) {
	std::cout << "Removing object {" << inIterator->first <<
			"} if type {" << inIterator->second->getClassDataRT()->fullName() <<
					"}" << std::endl;
	gObjects.erase(inIterator);
}

//----------------------------- Commands ---------------------------------------
//- - - - - - - - - - - - - - - Create - - - - - - - - - - - - - - - - - - - - -
void performCreateCommand() {
	const char *theClassName = strtok(NULL, " ");
	CPPRTClassData *theData = cppRuntime().getClassData(theClassName);
	if (!theData) {
		printClassError(theClassName);
		return;
	}

	const char *theObjectName = strtok(NULL, " ");
	if (gObjects.find(theObjectName) != gObjects.end()) {
		printObjectError(theClassName, ObjectErrorTypeObjectCurrentlyExists);
		return;
	}

	gObjects[theObjectName] = theData->createObject();
}

//- - - - - - - - - - - - - - - Delete - - - - - - - - - - - - - - - - - - - - -
void performDeleteCommand() {
	const char *theObjectName = strtok(NULL, " ");

	ObjectsIterator theIterator = gObjects.find(theObjectName);

	if (theIterator == gObjects.end()) {
		printObjectError(theObjectName, ObjectErrorTypeNoObjectFound);
		return;
	}

	removeObject(theIterator);
}

//- - - - - - - - - - - - - - - Print - - - - - - - - - - - - - - - - - - - - -
void printClassRecursive(CPPRTClassData *inClassManager, size_t inLevel) {
	if (0 == inLevel) {
		//TODO: Create small class/interface print function
		if (inClassManager->isInterface()) std::cout << "<i> ";
		std::cout << inClassManager->fullName() << std::endl;
	} else {
		for (size_t theIndex = 0; theIndex < inLevel; ++theIndex) {
			std::cout << '|';
		}
		//TODO: Create small class/interface print function
		std::cout << "-[";
		if (inClassManager->isInterface()) std::cout << "{i} ";
		std::cout << inClassManager->fullName() << "]" << std::endl;
	}

	std::vector<CPPRTClassData *> theClassManagers;
	cppRuntime().observeChilds(inClassManager, theClassManagers,
			CPPRTRuntime::ObservingFlagIgnoreBase);
	for (size_t theIndex = 0, theSize = theClassManagers.size();
			theIndex < theSize; ++theIndex)
	{
		printClassRecursive(theClassManagers[theIndex], inLevel + 1);
	}
}


void performPrintCommand() {
	const char *theFirstWord = strtok(NULL, " ");

	if (theFirstWord && (0 == strcmp(theFirstWord, "-c"))) {
		const char *theName = strtok(NULL, " ");

		if (NULL == theName) {
			//Print all classes if no class name provided
			std::vector<CPPRTClassData *> theClassManagers;
			cppRuntime().observeChilds(NULL, theClassManagers);
			for (size_t theIndex = 0, theSize = theClassManagers.size();
			theIndex < theSize; ++theIndex)
			{
				printClassRecursive(theClassManagers[theIndex], 0);
			}
			return;
		}

		CPPRTClassData *theData = cppRuntime().getClassData(theName);
		if (!theData) {
			printClassError(theName);
			return;
		}

		printClassRecursive(theData, 0);
		return;
	}

	size_t theCounter = 1;
	std::map<std::string, ICPPRTManagedClass *>::iterator theIterator =
			gObjects.begin();
	for (; theIterator != gObjects.end(); ++theIterator, ++theCounter) {
		std::cout << "#" << theCounter << ": ";
		printObject(theIterator);
		std::cout << std::endl;
	}
}

//- - - - - - - - - - - - - - - Help - - - - - - - - - - - - - - - - - - - - - -
void performHelpCommand() {
	//TODO: Use here formating
	std::cout << "Cpp Runtime Console support next commands:" << std::endl;
	std::cout << "create\t\t\tObjects creation" << std::endl;
	std::cout << "delete\t\t\tObjects deleting" << std::endl;
	std::cout << "print\t\t\tPriting of objects and classes info" << std::endl;
	std::cout << "help\t\t\tPrinting of this help" << std::endl;
	std::cout << "exit\t\t\tCommand for exit from Console" << std::endl;
}

//----------------------------- Main -------------------------------------------
int main() {
	char theCommandText[kCommandTextMaxSize];

	while(true) {
		std::cout << "> ";
		cin.getline(theCommandText, kCommandTextMaxSize, '\n');

		char *theCommand = strtok(theCommandText, " ");
		if (0 == strcmp(theCommand, "create")) {
			performCreateCommand();
		} else if (0 == strcmp(theCommand, "delete")) {
			performDeleteCommand();
		} else if(0 == strcmp(theCommand, "print")) {
			performPrintCommand();
		} else if(0 == strcmp(theCommand, "help")) {
			performHelpCommand();
		} else if (0 == strcmp(theCommand, "exit")) {
			break;
		} else {
			printUndefinedCommandError(theCommand);
		}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
