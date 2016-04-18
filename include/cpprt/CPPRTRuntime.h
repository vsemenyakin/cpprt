////////////////////////////////////////////////////////////////////////////////
//
// CPPRTRuntime.h
//
// Copyright (c) 2016 Semenyakin Vladimir (semenyakinVS@gmail.com)
//
// Distributed under the MIT (See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT)
//
////////////////////////////////////////////////////////////////////////////////
#ifndef CPPRTRUNTIME_H_
#define CPPRTRUNTIME_H_

////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <stddef.h> // for NULL constant

//NB: There are several places in library, that author (Semenyakin
// Vladimir) uses in his project. This places are marked with DEMIURG_PROJECT.
// Please, read a comment before editing code in this places.
// Thank you in advance!

//DEMIURG_PROJECT: Please, don't touch code between brackets {
#ifdef USE_WITH_DEMIURG
#include "../../serializing/ITypedBinding.h"
#define BINDING_BASE : public IDBindableObject
#else
#define BINDING_BASE
#endif // USE_WITH_DEMIURG
//}

////////////////////////////////////////////////////////////////////////////////
class ICPPRTManagedClass;

//=============================== Runtime ======================================
class CPPRTRuntime {
public:
	//- Types
	//-- Registry
	class IFabric {
	public:
		virtual ICPPRTManagedClass *createObject() = 0;
	};

	template<typename T_Type>
	class Fabric : public IFabric {
	public:
		virtual ICPPRTManagedClass *createObject() { return new T_Type(); }
	};

	class ClassData {
	private:
		//- State
		const char *_fullName;
		const char *_namePointer;

		IFabric *_fabric;

		std::vector<ClassData *> _parents;
		std::vector<ClassData *> _children;

		//- Methods
		//-- Initialization: Called from CPPRT
	    friend class CPPRTRuntime;

		void internal_initialize(const char *inFullName, IFabric *inFabric);
	    void internal_addParent(ClassData *inParent);

	public:
		const char *fullName() const { return _fullName; }
		const char *name() const { return _namePointer; }

		bool isInterface() { return !_fabric; }

		//-- Fabric method
		ICPPRTManagedClass *createObject();
	};

	//- Types
	//TODO: Use "class manager iterator" for observing classes interrelashanship
    enum ObservingFlag {
		ObservingFlagWithoutInterface	= 1 << 0,
		ObservingFlagRecursive			= 1 << 1,
		ObservingFlagIgnoreBase			= 1 << 2
    };

    typedef char OservingFlags;

private:
	//- State
    std::vector<ClassData *> _classesManagers;

	//- Methods
	//-- Runtime helpers
    ClassData *internal_dataByName(const char *inFullName);

	//--- Observing
	void internal_addWithFiltering(ClassData *inData,
    		std::vector<ClassData *> &outRegistries, OservingFlags inFlags);

	void internal_observeChildsDirect(ClassData *inData,
			std::vector<ClassData *> &outRegistries, OservingFlags inFlags);

	void internal_observeChildsAll(ClassData *inData,
			std::vector<ClassData *> &outRegistries, OservingFlags inFlags);

public:
	CPPRTRuntime();

	//-- Initialization API
	ClassData *createClassData(const char *inFullName, IFabric *inFabric);
	ClassData *createClassData(const char *inFullName, IFabric *inFabric,
			ClassData *inParent0);
	ClassData *createClassData(const char *inFullName, IFabric *inFabric,
			ClassData *inParent0, ClassData *inParent1);

	//-- Public API
    void observeChilds(ClassData *inBaseRegistry,
    		std::vector<ClassData *> &outRegistries,
			OservingFlags inInheritFlags = 0);

    ClassData *getClassData(const char *inFullName);
    ICPPRTManagedClass *createObject(const char *inFullName);
};

typedef CPPRTRuntime::ClassData CPPRTClassData;

//------------------------------------------------------------------------------
CPPRTRuntime &cppRuntime();

//=========================== User base class ==================================
//DEMIURG_PROJECT: Please, don't remove BINDING_BASE macro here
class ICPPRTManagedClass BINDING_BASE {
public:
	virtual ~ICPPRTManagedClass() { }
    virtual CPPRTRuntime::ClassData *getClassDataRT() const = 0;
};

////////////////////////////////////////////////////////////////////////////////
#define CPPRT_DECLARATION(M_ClassName)                                         \
	public:																       \
		static CPPRTClassData *__cpprtRegisteringAccess();		   			   \
    public:                                                                    \
		static CPPRTClassData *gClassData;							           \
        virtual CPPRTClassData *getClassDataRT() const { return gClassData; }  \
    protected:                                                                 \

//------------------------------------------------------------------------------
//0 parents
#define __CPPRT_BASE_0(M_Class, M_FullName, M_Fabric)                          \
CPPRTClassData *M_Class::__cpprtRegisteringAccess() {             			   \
    if (!gClassData) {                                                         \
        gClassData = cppRuntime().createClassData(M_FullName, M_Fabric);       \
    }                                                                          \
    return gClassData;                                                         \
}                                                                              \
CPPRTClassData *M_Class::gClassData = M_Class::__cpprtRegisteringAccess();     \

#define CPPRT_CLASS_IMPLEMENTATION_BASE_0(C)\
	__CPPRT_BASE_0(C, #C, new CPPRTRuntime::Fabric<C>())

#define CPPRT_INTERFACE_IMPLEMENTATION_BASE_0(C)\
	__CPPRT_BASE_0(C, #C, NULL)

//------------------------------------------------------------------------------
//1 parent
#define __CPPRT_BASE_1(M_Class, M_FullName, M_Fabric, M_Base0)                 \
CPPRTClassData *M_Class::__cpprtRegisteringAccess() {                          \
    if (!gClassData) {                                                         \
        gClassData = cppRuntime().createClassData(M_FullName, M_Fabric,		   \
				M_Base0::__cpprtRegisteringAccess());       				   \
    }                                                                          \
    return gClassData;                                                         \
}                                                                              \
CPPRTClassData *M_Class::gClassData = M_Class::__cpprtRegisteringAccess();     \

#define CPPRT_CLASS_IMPLEMENTATION_BASE_1(C, B0)\
	__CPPRT_BASE_1(C, #C, new CPPRTRuntime::Fabric<C>(), B0)

#define CPPRT_INTERFACE_IMPLEMENTATION_BASE_1(C, B0)\
	__CPPRT_BASE_1(C, #C, NULL, B0)

//------------------------------------------------------------------------------
//2 parents
#define __CPPRT_BASE_2(M_Class, M_FullName, M_Fabric, M_Base0, M_Base1)        \
CPPRTClassData *M_Class::__cpprtRegisteringAccess() {                          \
    if (!gClassData) {                                                         \
        gClassData = cppRuntime().createClassData(M_FullName, M_Fabric,		   \
				M_Base0::__cpprtRegisteringAccess(),						   \
				M_Base1::__cpprtRegisteringAccess());       				   \
    }                                                                          \
    return gClassData;                                                         \
}                                                                              \
CPPRTClassData *M_Class::gClassData = M_Class::__cpprtRegisteringAccess();     \

#define CPPRT_CLASS_IMPLEMENTATION_BASE_2(C, B0, B1)\
	__CPPRT_BASE_2(C, #C, new CPPRTRuntime::Fabric<C>(), B0, B1)

#define CPPRT_INTERFACE_IMPLEMENTATION_BASE_2(C, B0, B1)\
	__CPPRT_BASE_2(C, #C, NULL, B0, B1)

///////////////////////////////////////////////////////////////////////////////
#endif /* CPPRTRUNTIME_H_ */
