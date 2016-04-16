--- Introduction ---

CPP Runtime (cpprt) is a small library, that provides possibility to bind metadata for C++ classes and then use this data in different ways.

Brief overview of the library features:
1. Creating objects of registered classes by string name of classes.
2. Observing inheritance hierarchies of registered classes.
3. Access for class metadata from class objects.


--- Overview of this repository structure ---

- Documentation block:
readme.md - this file. It contains brief information about cpprt project.
README.cmake - instructions how to build cpprt library and other projects.
\docs - library documentation.

- Library files:
\include - library interface API (headers).
\src - library source code.

- Additional projects:
\examples - source code files for project examples.
\tools - source code files for library tools.

- Build system:
\build - empty folder, recommended to keep for building needs.
CMakeLists.txt - file with CMake configuration.

- Miscellaneous:
LICENCE.txt - project licence text (MIT).
copying.txt - file with licence header template.
