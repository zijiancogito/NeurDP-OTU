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
include data/CMakeFiles/Aarch64Asm.dir/depend.make

# Include the progress variables for this target.
include data/CMakeFiles/Aarch64Asm.dir/progress.make

# Include the compile flags for this target's objects.
include data/CMakeFiles/Aarch64Asm.dir/flags.make

data/CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.o: data/CMakeFiles/Aarch64Asm.dir/flags.make
data/CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.o: ../data/aarch64Asm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/caoy/proj/tools/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object data/CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.o"
	cd /home/caoy/proj/tools/code/build/data && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.o -c /home/caoy/proj/tools/code/data/aarch64Asm.cpp

data/CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.i"
	cd /home/caoy/proj/tools/code/build/data && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/caoy/proj/tools/code/data/aarch64Asm.cpp > CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.i

data/CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.s"
	cd /home/caoy/proj/tools/code/build/data && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/caoy/proj/tools/code/data/aarch64Asm.cpp -o CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.s

# Object files for target Aarch64Asm
Aarch64Asm_OBJECTS = \
"CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.o"

# External object files for target Aarch64Asm
Aarch64Asm_EXTERNAL_OBJECTS =

data/libAarch64Asm.a: data/CMakeFiles/Aarch64Asm.dir/aarch64Asm.cpp.o
data/libAarch64Asm.a: data/CMakeFiles/Aarch64Asm.dir/build.make
data/libAarch64Asm.a: data/CMakeFiles/Aarch64Asm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/caoy/proj/tools/code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libAarch64Asm.a"
	cd /home/caoy/proj/tools/code/build/data && $(CMAKE_COMMAND) -P CMakeFiles/Aarch64Asm.dir/cmake_clean_target.cmake
	cd /home/caoy/proj/tools/code/build/data && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Aarch64Asm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
data/CMakeFiles/Aarch64Asm.dir/build: data/libAarch64Asm.a

.PHONY : data/CMakeFiles/Aarch64Asm.dir/build

data/CMakeFiles/Aarch64Asm.dir/clean:
	cd /home/caoy/proj/tools/code/build/data && $(CMAKE_COMMAND) -P CMakeFiles/Aarch64Asm.dir/cmake_clean.cmake
.PHONY : data/CMakeFiles/Aarch64Asm.dir/clean

data/CMakeFiles/Aarch64Asm.dir/depend:
	cd /home/caoy/proj/tools/code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/caoy/proj/tools/code /home/caoy/proj/tools/code/data /home/caoy/proj/tools/code/build /home/caoy/proj/tools/code/build/data /home/caoy/proj/tools/code/build/data/CMakeFiles/Aarch64Asm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : data/CMakeFiles/Aarch64Asm.dir/depend

