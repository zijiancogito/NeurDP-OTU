# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/caoy/proj/tools/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/caoy/proj/tools/code/build

# Include any dependencies generated for this target.
include CMakeFiles/opsequence.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opsequence.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opsequence.dir/flags.make

CMakeFiles/opsequence.dir/opsequence.cpp.o: CMakeFiles/opsequence.dir/flags.make
CMakeFiles/opsequence.dir/opsequence.cpp.o: ../opsequence.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/caoy/proj/tools/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opsequence.dir/opsequence.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opsequence.dir/opsequence.cpp.o -c /home/caoy/proj/tools/code/opsequence.cpp

CMakeFiles/opsequence.dir/opsequence.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opsequence.dir/opsequence.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/caoy/proj/tools/code/opsequence.cpp > CMakeFiles/opsequence.dir/opsequence.cpp.i

CMakeFiles/opsequence.dir/opsequence.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opsequence.dir/opsequence.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/caoy/proj/tools/code/opsequence.cpp -o CMakeFiles/opsequence.dir/opsequence.cpp.s

# Object files for target opsequence
opsequence_OBJECTS = \
"CMakeFiles/opsequence.dir/opsequence.cpp.o"

# External object files for target opsequence
opsequence_EXTERNAL_OBJECTS =

opsequence: CMakeFiles/opsequence.dir/opsequence.cpp.o
opsequence: CMakeFiles/opsequence.dir/build.make
opsequence: data/libAarch64Asm.a
opsequence: data/libIr.a
opsequence: data/libCode.a
opsequence: CMakeFiles/opsequence.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/caoy/proj/tools/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable opsequence"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opsequence.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opsequence.dir/build: opsequence

.PHONY : CMakeFiles/opsequence.dir/build

CMakeFiles/opsequence.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opsequence.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opsequence.dir/clean

CMakeFiles/opsequence.dir/depend:
	cd /home/caoy/proj/tools/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/caoy/proj/tools/code /home/caoy/proj/tools/code /home/caoy/proj/tools/code/build /home/caoy/proj/tools/code/build /home/caoy/proj/tools/code/build/CMakeFiles/opsequence.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opsequence.dir/depend

