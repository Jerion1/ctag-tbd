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

# Utility rule file for NightlyTest.

# Include the progress variables for this target.
include rtaudio/CMakeFiles/NightlyTest.dir/progress.make

rtaudio/CMakeFiles/NightlyTest:
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio && "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\ctest.exe" -D NightlyTest

NightlyTest: rtaudio/CMakeFiles/NightlyTest
NightlyTest: rtaudio/CMakeFiles/NightlyTest.dir/build.make

.PHONY : NightlyTest

# Rule to build all files generated by this target.
rtaudio/CMakeFiles/NightlyTest.dir/build: NightlyTest

.PHONY : rtaudio/CMakeFiles/NightlyTest.dir/build

rtaudio/CMakeFiles/NightlyTest.dir/clean:
	cd /d C:\ctag-tbd\simulator\cmake-build-debug\rtaudio && $(CMAKE_COMMAND) -P CMakeFiles\NightlyTest.dir\cmake_clean.cmake
.PHONY : rtaudio/CMakeFiles/NightlyTest.dir/clean

rtaudio/CMakeFiles/NightlyTest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\ctag-tbd\simulator C:\ctag-tbd\simulator\rtaudio C:\ctag-tbd\simulator\cmake-build-debug C:\ctag-tbd\simulator\cmake-build-debug\rtaudio C:\ctag-tbd\simulator\cmake-build-debug\rtaudio\CMakeFiles\NightlyTest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : rtaudio/CMakeFiles/NightlyTest.dir/depend

