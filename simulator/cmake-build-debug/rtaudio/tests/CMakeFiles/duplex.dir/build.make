# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\ctag-tbd\simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\ctag-tbd\simulator\cmake-build-debug

# Include any dependencies generated for this target.
include rtaudio/tests/CMakeFiles/duplex.dir/depend.make

# Include the progress variables for this target.
include rtaudio/tests/CMakeFiles/duplex.dir/progress.make

# Include the compile flags for this target's objects.
include rtaudio/tests/CMakeFiles/duplex.dir/flags.make

rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.obj: rtaudio/tests/CMakeFiles/duplex.dir/flags.make
rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.obj: rtaudio/tests/CMakeFiles/duplex.dir/includes_CXX.rsp
rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.obj: ../rtaudio/tests/duplex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\ctag-tbd\simulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.obj"
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests && C:\MinGW\mingw32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\duplex.dir\duplex.cpp.obj -c C:\ctag-tbd\simulator\rtaudio\tests\duplex.cpp

rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/duplex.dir/duplex.cpp.i"
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests && C:\MinGW\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\ctag-tbd\simulator\rtaudio\tests\duplex.cpp > CMakeFiles\duplex.dir\duplex.cpp.i

rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/duplex.dir/duplex.cpp.s"
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests && C:\MinGW\mingw32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\ctag-tbd\simulator\rtaudio\tests\duplex.cpp -o CMakeFiles\duplex.dir\duplex.cpp.s

# Object files for target duplex
duplex_OBJECTS = \
"CMakeFiles/duplex.dir/duplex.cpp.obj"

# External object files for target duplex
duplex_EXTERNAL_OBJECTS =

rtaudio/tests/duplex.exe: rtaudio/tests/CMakeFiles/duplex.dir/duplex.cpp.obj
rtaudio/tests/duplex.exe: rtaudio/tests/CMakeFiles/duplex.dir/build.make
rtaudio/tests/duplex.exe: rtaudio/librtaudiod.a
rtaudio/tests/duplex.exe: rtaudio/tests/CMakeFiles/duplex.dir/linklibs.rsp
rtaudio/tests/duplex.exe: rtaudio/tests/CMakeFiles/duplex.dir/objects1.rsp
rtaudio/tests/duplex.exe: rtaudio/tests/CMakeFiles/duplex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\ctag-tbd\simulator\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable duplex.exe"
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\duplex.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
rtaudio/tests/CMakeFiles/duplex.dir/build: rtaudio/tests/duplex.exe

.PHONY : rtaudio/tests/CMakeFiles/duplex.dir/build

rtaudio/tests/CMakeFiles/duplex.dir/clean:
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests && $(CMAKE_COMMAND) -P CMakeFiles\duplex.dir\cmake_clean.cmake
.PHONY : rtaudio/tests/CMakeFiles/duplex.dir/clean

rtaudio/tests/CMakeFiles/duplex.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ctag-tbd\simulator C:\ctag-tbd\simulator\rtaudio\tests C:\ctag-tbd\simulator\cmake-build-debug C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\tests\CMakeFiles\duplex.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : rtaudio/tests/CMakeFiles/duplex.dir/depend

