#===============================================================================================
# Head
#
cmake_minimum_required(VERSION 2.8.8)

option(BUILD_ALL "Build cpprt tools" OFF)

option(BUILD_TOOLS "Build cpprt tools" ${BUILD_ALL})
option(CONSOLE_WITH_EXAMPLE "Add examples to console" ON)

option(BUILD_EXAMPLES "Build cpprt examples" ${BUILD_ALL})

#-----------------------------------------------------------------------------------------------
### - cpprt code
#
project(cpprt_projects)

set(CPPRT_ROOT_PATH .)
set(CPPRT_SOURCES_PATH ${CPPRT_ROOT_PATH}/src)
set(CPPRT_INCLUDE_PATH ${CPPRT_ROOT_PATH}/include)

file(GLOB_RECURSE CPPRT_SOURCES
	${CPPRT_SOURCES_PATH}/*.h
	${CPPRT_SOURCES_PATH}/*.cpp
)

file(GLOB_RECURSE CPPRT_HEADERS
	${CPPRT_INCLUDE_PATH}/*.h
)

include_directories(${CPPRT_INCLUDE_PATH})
add_library(cpprt STATIC ${CPPRT_SOURCES} ${CPPRT_HEADERS})

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Global examples setup
#
set(EXAMPLE_HIERARCHIES_ROOT ${CPPRT_ROOT_PATH}/examples/__example_hierarchies__)

file(GLOB_RECURSE EXAMPLE_HIERARCHY_PATHES
	${EXAMPLE_HIERARCHIES_ROOT}/*.h
	${EXAMPLE_HIERARCHIES_ROOT}/*.cpp
)

#-----------------------------------------------------------------------------------------------
### - Tools
#
if(BUILD_TOOLS)
	set(TOOLS_ROOT ${CPPRT_ROOT_PATH}/tools)

	#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	### - Console project
	set(CONSOLE_ROOT ${TOOLS_ROOT}/console)

	if (CONSOLE_WITH_EXAMPLE)
		add_executable(cpprt_console		
			${CONSOLE_ROOT}/CPPRTConsole.cpp
			${EXAMPLE_HIERARCHY_PATHES}
		)
		target_include_directories(cpprt_console
			PUBLIC
			${EXAMPLE_HIERARCHIES_ROOT}
		)
		target_link_libraries(cpprt_console cpprt)
		
	else(CONSOLE_WITH_EXAMPLE)
		add_executable(cpprt_console		
			${CONSOLE_ROOT}/CPPRTConsole.cpp
		)
		target_link_libraries(cpprt_console cpprt)
		
	endif(CONSOLE_WITH_EXAMPLE)
	
endif(BUILD_TOOLS)

#-----------------------------------------------------------------------------------------------
###- Examples
#
if(BUILD_EXAMPLES)

	#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	### - Simple examples
	set(SIMPLE_EXAMPLE_ROOT examples/simple_examples)
	
	include_directories(${CPPRT_INCLUDE_PATH})
	add_executable(simple_examples
		${SIMPLE_EXAMPLE_ROOT}/SimpleExamples.cpp
		${CPPRT_SOURCES}
	)
	target_link_libraries(simple_examples cpprt)
endif(BUILD_EXAMPLES)
#===============================================================================================