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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/maria/Documents/UNIVERSITY/algorithms/kdz

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/kdz.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kdz.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kdz.dir/flags.make

CMakeFiles/kdz.dir/main.cpp.o: CMakeFiles/kdz.dir/flags.make
CMakeFiles/kdz.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/kdz.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kdz.dir/main.cpp.o -c /Users/maria/Documents/UNIVERSITY/algorithms/kdz/main.cpp

CMakeFiles/kdz.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kdz.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/Documents/UNIVERSITY/algorithms/kdz/main.cpp > CMakeFiles/kdz.dir/main.cpp.i

CMakeFiles/kdz.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kdz.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/Documents/UNIVERSITY/algorithms/kdz/main.cpp -o CMakeFiles/kdz.dir/main.cpp.s

CMakeFiles/kdz.dir/huffman.cpp.o: CMakeFiles/kdz.dir/flags.make
CMakeFiles/kdz.dir/huffman.cpp.o: ../huffman.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/kdz.dir/huffman.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kdz.dir/huffman.cpp.o -c /Users/maria/Documents/UNIVERSITY/algorithms/kdz/huffman.cpp

CMakeFiles/kdz.dir/huffman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kdz.dir/huffman.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/Documents/UNIVERSITY/algorithms/kdz/huffman.cpp > CMakeFiles/kdz.dir/huffman.cpp.i

CMakeFiles/kdz.dir/huffman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kdz.dir/huffman.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/Documents/UNIVERSITY/algorithms/kdz/huffman.cpp -o CMakeFiles/kdz.dir/huffman.cpp.s

CMakeFiles/kdz.dir/lz77.cpp.o: CMakeFiles/kdz.dir/flags.make
CMakeFiles/kdz.dir/lz77.cpp.o: ../lz77.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/kdz.dir/lz77.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kdz.dir/lz77.cpp.o -c /Users/maria/Documents/UNIVERSITY/algorithms/kdz/lz77.cpp

CMakeFiles/kdz.dir/lz77.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kdz.dir/lz77.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/maria/Documents/UNIVERSITY/algorithms/kdz/lz77.cpp > CMakeFiles/kdz.dir/lz77.cpp.i

CMakeFiles/kdz.dir/lz77.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kdz.dir/lz77.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/maria/Documents/UNIVERSITY/algorithms/kdz/lz77.cpp -o CMakeFiles/kdz.dir/lz77.cpp.s

# Object files for target kdz
kdz_OBJECTS = \
"CMakeFiles/kdz.dir/main.cpp.o" \
"CMakeFiles/kdz.dir/huffman.cpp.o" \
"CMakeFiles/kdz.dir/lz77.cpp.o"

# External object files for target kdz
kdz_EXTERNAL_OBJECTS =

kdz: CMakeFiles/kdz.dir/main.cpp.o
kdz: CMakeFiles/kdz.dir/huffman.cpp.o
kdz: CMakeFiles/kdz.dir/lz77.cpp.o
kdz: CMakeFiles/kdz.dir/build.make
kdz: CMakeFiles/kdz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable kdz"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kdz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kdz.dir/build: kdz

.PHONY : CMakeFiles/kdz.dir/build

CMakeFiles/kdz.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kdz.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kdz.dir/clean

CMakeFiles/kdz.dir/depend:
	cd /Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/maria/Documents/UNIVERSITY/algorithms/kdz /Users/maria/Documents/UNIVERSITY/algorithms/kdz /Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release /Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release /Users/maria/Documents/UNIVERSITY/algorithms/kdz/cmake-build-release/CMakeFiles/kdz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kdz.dir/depend

