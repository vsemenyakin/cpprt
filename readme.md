####--- Introduction ---

CPP Runtime (cpprt) is a small library, that provides possibility to bind metadata for C++ classes and then use this data in different ways.

Brief overview of the library features:<br/>
1. Creating objects of registered classes by string name of classes.<br/>
2. Observing inheritance hierarchies of registered classes.<br/>
3. Access for class metadata from class objects.<br/>


####--- Overview of this repository structure ---

- Documentation block:<br/>
**readme.md** - this file. It contains brief information about cpprt project.<br/>
**README.cmake** - instructions how to build cpprt library and other projects using CMake.<br/>
**\docs** - library documentation.<br/>

- Library files:<br/>
**\include** - library interface API (headers).<br/>
**\src** - library source code.<br/>

- Additional projects:<br/>
**\examples** - source code files for project examples.<br/>
**\tools** - source code files for library tools.<br/>

- Build system:<br/>
**\build** - folder with configurations to build repo build targets with some common toolchains and IDE<br/>
**CMakeLists.txt** - file with CMake configuration.<br/>

- Miscellaneous:<br/>
**LICENCE.txt** - project licence text (MIT).<br/>
**copying.txt** - file with licence header template.<br/>
