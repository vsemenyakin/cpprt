--- Commands to generate build configuration ---

1. Move to folder, that is recommended for building execution:
> cd {ccprt-clone-path}/build

2. Call CMake configuration generation, providing it with the options to select what exactly you want to build
> cmake -G "{generator-name}" {options} ../

{generator-name} - name of generator, that is used for creating the build configuration for your toolchain (please, see https://cmake.org/cmake/help/v3.0/manual/cmake-generators.7.html for details)
{options} - list of option defenitions, to provide configuration generation details. The details about possibly to select options are presented below.

3. Perform a build using your toolchain by providing a build configuration generated after step 2 into this toolchain.


--- Build configuration generation options ---

There is always at least one build target to be built - a static library cpprt. If you want to examine possibility of library, you may build tools or examples, that goes with this repository. To set up generating of configuration to build them, you could use the next options (default value of each option is provided first):

-DBUILD_ALL={OFF/ON} - setting this option ON, you make CMake to generate the build configurations for all targets. However, you may disable generation of a build configuration for some targets by setting their build option to OFF value.

-DBUILD_TOOLS={OFF/ON} - if value of this option is ON, the build configurations for all tools will be generated.

-DBUILD_EXAMPLES={OFF/ON} - if value of this option is ON, the build configurations for all examples will be generated.

Extra settings
-DCONSOLE_WITH_EXAMPLE={ON/OFF} - if selected to ON, a console tool build target will be confugurated to build with the test class hierarchies.


--- CMake call examples ---

As mentioned above, the build configuration for cpprt static library build target always generates. So, to generate build configuration for cpprt static library target only you may use the next command:
> cmake ../

Next cmake call example presents how to generate mingw32-make build configuration (the make files) for building static library and build tools:
> cmake -G "MinGW Makefiles" -DBUILD_TOOLS=ON ../

One more example for mingw32-make build configuration generating. Generating configuration for all targets, but the build tools:
> cmake -G "MinGW Makefiles" -DBUILD_ALL=ON -DBUILD_TOOLS=OFF ../

Generating Visual Studio solution for building library and examples:
> cmake -G "Visual Studio 14 2015" -DBUILD_EXAMPLES=ON ../

Generating build configurations using default generator for all targets, but set up building console without example class hierarchies:
> cmake -G -DBUILD_ALL=ON -DCONSOLE_WITH_EXAMPLE=OFF ../
