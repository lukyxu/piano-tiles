# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/lib/clion-2018.2.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/lib/clion-2018.2.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/yiz18/Lab/PianoTiles

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/yiz18/Lab/PianoTiles/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PianoTiles.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PianoTiles.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PianoTiles.dir/flags.make

CMakeFiles/PianoTiles.dir/main.c.o: CMakeFiles/PianoTiles.dir/flags.make
CMakeFiles/PianoTiles.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/yiz18/Lab/PianoTiles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PianoTiles.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PianoTiles.dir/main.c.o   -c /homes/yiz18/Lab/PianoTiles/main.c

CMakeFiles/PianoTiles.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PianoTiles.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/yiz18/Lab/PianoTiles/main.c > CMakeFiles/PianoTiles.dir/main.c.i

CMakeFiles/PianoTiles.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PianoTiles.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/yiz18/Lab/PianoTiles/main.c -o CMakeFiles/PianoTiles.dir/main.c.s

CMakeFiles/PianoTiles.dir/utilities.c.o: CMakeFiles/PianoTiles.dir/flags.make
CMakeFiles/PianoTiles.dir/utilities.c.o: ../utilities.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/yiz18/Lab/PianoTiles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PianoTiles.dir/utilities.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PianoTiles.dir/utilities.c.o   -c /homes/yiz18/Lab/PianoTiles/utilities.c

CMakeFiles/PianoTiles.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PianoTiles.dir/utilities.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/yiz18/Lab/PianoTiles/utilities.c > CMakeFiles/PianoTiles.dir/utilities.c.i

CMakeFiles/PianoTiles.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PianoTiles.dir/utilities.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/yiz18/Lab/PianoTiles/utilities.c -o CMakeFiles/PianoTiles.dir/utilities.c.s

CMakeFiles/PianoTiles.dir/beatmap.c.o: CMakeFiles/PianoTiles.dir/flags.make
CMakeFiles/PianoTiles.dir/beatmap.c.o: ../beatmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/yiz18/Lab/PianoTiles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/PianoTiles.dir/beatmap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/PianoTiles.dir/beatmap.c.o   -c /homes/yiz18/Lab/PianoTiles/beatmap.c

CMakeFiles/PianoTiles.dir/beatmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PianoTiles.dir/beatmap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /homes/yiz18/Lab/PianoTiles/beatmap.c > CMakeFiles/PianoTiles.dir/beatmap.c.i

CMakeFiles/PianoTiles.dir/beatmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PianoTiles.dir/beatmap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /homes/yiz18/Lab/PianoTiles/beatmap.c -o CMakeFiles/PianoTiles.dir/beatmap.c.s

# Object files for target PianoTiles
PianoTiles_OBJECTS = \
"CMakeFiles/PianoTiles.dir/main.c.o" \
"CMakeFiles/PianoTiles.dir/utilities.c.o" \
"CMakeFiles/PianoTiles.dir/beatmap.c.o"

# External object files for target PianoTiles
PianoTiles_EXTERNAL_OBJECTS =

PianoTiles: CMakeFiles/PianoTiles.dir/main.c.o
PianoTiles: CMakeFiles/PianoTiles.dir/utilities.c.o
PianoTiles: CMakeFiles/PianoTiles.dir/beatmap.c.o
PianoTiles: CMakeFiles/PianoTiles.dir/build.make
PianoTiles: CMakeFiles/PianoTiles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/yiz18/Lab/PianoTiles/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable PianoTiles"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PianoTiles.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PianoTiles.dir/build: PianoTiles

.PHONY : CMakeFiles/PianoTiles.dir/build

CMakeFiles/PianoTiles.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PianoTiles.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PianoTiles.dir/clean

CMakeFiles/PianoTiles.dir/depend:
	cd /homes/yiz18/Lab/PianoTiles/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/yiz18/Lab/PianoTiles /homes/yiz18/Lab/PianoTiles /homes/yiz18/Lab/PianoTiles/cmake-build-debug /homes/yiz18/Lab/PianoTiles/cmake-build-debug /homes/yiz18/Lab/PianoTiles/cmake-build-debug/CMakeFiles/PianoTiles.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PianoTiles.dir/depend

