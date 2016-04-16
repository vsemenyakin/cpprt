////////////////////////////////////////////////////////////////////////////////
//
// SimpleExamples.cpp
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
////////////////////////////////////////////////////////////////////////////////
// Cpprt includes
#include <cpprt/CPPRTRuntime.h>

// Output
#include <iostream>

//----------------------------- Classes ----------------------------------------
// Animal [ICPPRTManagedClass]
// | -Mammal
// | | -Dog
// | | -Cat
// | -Birds
// | | -Parrot
// | | -Crow
// | -Fish

//-
// IAnimal.h
class IAnimal : public ICPPRTManagedClass {
	CPPRT_DECLARATION(IAnimal)

public:
	virtual void saySomething() = 0;
};

// IAnimal.cpp
CPPRT_INTERFACE_IMPLEMENTATION_BASE_0(IAnimal)

//--
// IMammal.h
class IMammal : public IAnimal {
	CPPRT_DECLARATION(IMammal)

public:
	// virtual void saySomething() = 0; <<<--- not implemented
};

// IMammal.cpp
CPPRT_INTERFACE_IMPLEMENTATION_BASE_1(IMammal, IAnimal)

//---
// Dog.h
class Dog : public IMammal {
	CPPRT_DECLARATION(Dog)

public:
	virtual void saySomething() {
		std::cout << "howl-howl" << std::endl;
	}
};

// Dog.cpp
CPPRT_CLASS_IMPLEMENTATION_BASE_1(Dog, IMammal)

//---
// Cat.h
class Cat : public IMammal {
	CPPRT_DECLARATION(Cat)

public:
	virtual void saySomething() {
		std::cout << "mew-mew" << std::endl;
	}
};

// Cat.cpp
CPPRT_CLASS_IMPLEMENTATION_BASE_1(Cat, IMammal)

//--
// IBird.h
class IBird : public IAnimal {
	CPPRT_DECLARATION(IBird)

public:
	// virtual void saySomething() = 0; <<<--- not implemented
};

// IBird.cpp
CPPRT_INTERFACE_IMPLEMENTATION_BASE_1(IBird, IAnimal)

//---
// Parrot.h
class Parrot : public IBird {
	CPPRT_DECLARATION(Parrot)

public:
	virtual void saySomething() {
		std::cout << "hello, richard" << std::endl;
	}
};

// Parrot.cpp
CPPRT_CLASS_IMPLEMENTATION_BASE_1(Parrot, IBird)

//---
// Crow.h
namespace Poe {

	class Crow : public IBird {
		CPPRT_DECLARATION(Crow)

	public:
		virtual void saySomething() {
			std::cout << "never-r mor-re!!!" << std::endl;
		}
	};

}

// Crow.cpp
CPPRT_CLASS_IMPLEMENTATION_BASE_1(Poe::Crow, IBird)

//--
// Fish.h
class Fish : public IAnimal {
	CPPRT_DECLARATION(Fish)

public:
	virtual void saySomething() {
		std::cout << " " << std::endl;
	}
};

// Fish.cpp
CPPRT_CLASS_IMPLEMENTATION_BASE_1(Fish, IAnimal)

//----------------------------- Main -------------------------------------------
int main() {
	// Get ClassData of all animal childs
	std::cout << "--------------------------------------------------" <<
		std::endl;
	std::cout << "There was next animal ecosystem in out programm: " <<
		std::endl;

	std::vector<CPPRTClassData *> theClassDatas;

	cppRuntime().observeChilds(IAnimal::gClassData, theClassDatas,
			CPPRTRuntime::ObservingFlagRecursive |
			CPPRTRuntime::ObservingFlagIgnoreBase);

	for (size_t theIndex = 0, theSize = theClassDatas.size();
			theIndex < theSize; ++theIndex)
	{
		CPPRTClassData *theClassData = theClassDatas[theIndex];
		
		std::cout << "- " << theClassData->fullName() << " (" <<
			theClassData->name() << ")";

		if (theClassData->isInterface()) std::cout << " is abstract";
		
		std::cout << std::endl;
	}

	// Some other tests
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "Animals was created and said something" << std::endl;

	IAnimal *theAnimal = NULL;

	theAnimal = static_cast<IAnimal *>(cppRuntime().createObject("Dog"));

	std::cout << theAnimal->getClassDataRT()->name() << " said: ";
	theAnimal->saySomething(); // howl-howl
	delete theAnimal;

	theAnimal = static_cast<IAnimal *>(cppRuntime().createObject("Cat"));

	std::cout << theAnimal->getClassDataRT()->name() << " said: ";
	theAnimal->saySomething(); // mew-mew
	delete theAnimal;

	theAnimal = static_cast<IAnimal *>(cppRuntime().createObject("Parrot"));

	std::cout << theAnimal->getClassDataRT()->name() << " said: ";
	theAnimal->saySomething(); // hello, richard
	delete theAnimal;

	theAnimal = static_cast<IAnimal *>(cppRuntime().createObject("Fish"));

	std::cout << theAnimal->getClassDataRT()->name() << " said: ";
	theAnimal->saySomething(); // 
	delete theAnimal;

	theAnimal = static_cast<IAnimal *>(cppRuntime().createObject("Poe::Crow"));

	std::cout << theAnimal->getClassDataRT()->name() << " said: ";
	theAnimal->saySomething(); // never-r mor-re!!!
	delete theAnimal;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////
