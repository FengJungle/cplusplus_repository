# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

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
$$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = E:\CMake\bin\cmake.exe

# The command to remove a file.
RM = E:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build

# Include any dependencies generated for this target.
include common/CMakeFiles/common.dir/depend.make

# Include the progress variables for this target.
include common/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include common/CMakeFiles/common.dir/flags.make

common/CMakeFiles/common.dir/common.cpp.obj: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/common.cpp.obj: ../common/common.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object common/CMakeFiles/common.dir/common.cpp.obj"
	cd /d F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common && E:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\common.dir\common.cpp.obj -c F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\common\common.cpp

common/CMakeFiles/common.dir/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/common.dir/common.cpp.i"
	cd /d F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common && E:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\common\common.cpp > CMakeFiles\common.dir\common.cpp.i

common/CMakeFiles/common.dir/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/common.dir/common.cpp.s"
	cd /d F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common && E:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\common\common.cpp -o CMakeFiles\common.dir\common.cpp.s

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/common.cpp.obj"

# External object files for target common
common_EXTERNAL_OBJECTS =

common/libcommon.a: common/CMakeFiles/common.dir/common.cpp.obj
common/libcommon.a: common/CMakeFiles/common.dir/build.make
common/libcommon.a: common/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcommon.a"
	cd /d F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common && $(CMAKE_COMMAND) -P CMakeFiles\common.dir\cmake_clean_target.cmake
	cd /d F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\common.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/CMakeFiles/common.dir/build: common/libcommon.a

.PHONY : common/CMakeFiles/common.dir/build

common/CMakeFiles/common.dir/clean:
	cd /d F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common && $(CMAKE_COMMAND) -P CMakeFiles\common.dir\cmake_clean.cmake
.PHONY : common/CMakeFiles/common.dir/clean

common/CMakeFiles/common.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2 F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\common F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common F:\Jungle\1.Program\4.C++\0.Study\1.VsCode_compile_multiple_files\2.CMakeLists\Demo2\build\common\CMakeFiles\common.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : common/CMakeFiles/common.dir/depend

