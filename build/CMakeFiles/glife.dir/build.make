# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/cmake-3.13.3-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /usr/cmake-3.13.3-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xaninho/Documentos/ProjectLife

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xaninho/Documentos/ProjectLife/build

# Include any dependencies generated for this target.
include CMakeFiles/glife.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glife.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glife.dir/flags.make

CMakeFiles/glife.dir/src/lodepng.cpp.o: CMakeFiles/glife.dir/flags.make
CMakeFiles/glife.dir/src/lodepng.cpp.o: ../src/lodepng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xaninho/Documentos/ProjectLife/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/glife.dir/src/lodepng.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glife.dir/src/lodepng.cpp.o -c /home/xaninho/Documentos/ProjectLife/src/lodepng.cpp

CMakeFiles/glife.dir/src/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glife.dir/src/lodepng.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xaninho/Documentos/ProjectLife/src/lodepng.cpp > CMakeFiles/glife.dir/src/lodepng.cpp.i

CMakeFiles/glife.dir/src/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glife.dir/src/lodepng.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xaninho/Documentos/ProjectLife/src/lodepng.cpp -o CMakeFiles/glife.dir/src/lodepng.cpp.s

CMakeFiles/glife.dir/src/main.cpp.o: CMakeFiles/glife.dir/flags.make
CMakeFiles/glife.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xaninho/Documentos/ProjectLife/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/glife.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glife.dir/src/main.cpp.o -c /home/xaninho/Documentos/ProjectLife/src/main.cpp

CMakeFiles/glife.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glife.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xaninho/Documentos/ProjectLife/src/main.cpp > CMakeFiles/glife.dir/src/main.cpp.i

CMakeFiles/glife.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glife.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xaninho/Documentos/ProjectLife/src/main.cpp -o CMakeFiles/glife.dir/src/main.cpp.s

# Object files for target glife
glife_OBJECTS = \
"CMakeFiles/glife.dir/src/lodepng.cpp.o" \
"CMakeFiles/glife.dir/src/main.cpp.o"

# External object files for target glife
glife_EXTERNAL_OBJECTS =

glife: CMakeFiles/glife.dir/src/lodepng.cpp.o
glife: CMakeFiles/glife.dir/src/main.cpp.o
glife: CMakeFiles/glife.dir/build.make
glife: CMakeFiles/glife.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xaninho/Documentos/ProjectLife/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable glife"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glife.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glife.dir/build: glife

.PHONY : CMakeFiles/glife.dir/build

CMakeFiles/glife.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glife.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glife.dir/clean

CMakeFiles/glife.dir/depend:
	cd /home/xaninho/Documentos/ProjectLife/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xaninho/Documentos/ProjectLife /home/xaninho/Documentos/ProjectLife /home/xaninho/Documentos/ProjectLife/build /home/xaninho/Documentos/ProjectLife/build /home/xaninho/Documentos/ProjectLife/build/CMakeFiles/glife.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glife.dir/depend

