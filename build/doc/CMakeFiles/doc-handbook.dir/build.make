# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rainer/projects/KTagebuch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rainer/projects/KTagebuch/build

# Utility rule file for doc-handbook.

doc/CMakeFiles/doc-handbook: doc/index.cache.bz2

doc/index.cache.bz2: ../doc/index.docbook
doc/index.cache.bz2: /usr/share/kde4/apps/ksgmltools2/customization/kde-chunk.xsl
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating index.cache.bz2"
	cd /home/rainer/projects/KTagebuch/doc && /usr/bin/meinproc4 --check --cache /home/rainer/projects/KTagebuch/build/doc/index.cache.bz2 /home/rainer/projects/KTagebuch/doc/index.docbook

doc-handbook: doc/CMakeFiles/doc-handbook
doc-handbook: doc/index.cache.bz2
doc-handbook: doc/CMakeFiles/doc-handbook.dir/build.make
.PHONY : doc-handbook

# Rule to build all files generated by this target.
doc/CMakeFiles/doc-handbook.dir/build: doc-handbook
.PHONY : doc/CMakeFiles/doc-handbook.dir/build

doc/CMakeFiles/doc-handbook.dir/clean:
	cd /home/rainer/projects/KTagebuch/build/doc && $(CMAKE_COMMAND) -P CMakeFiles/doc-handbook.dir/cmake_clean.cmake
.PHONY : doc/CMakeFiles/doc-handbook.dir/clean

doc/CMakeFiles/doc-handbook.dir/depend:
	cd /home/rainer/projects/KTagebuch/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rainer/projects/KTagebuch /home/rainer/projects/KTagebuch/doc /home/rainer/projects/KTagebuch/build /home/rainer/projects/KTagebuch/build/doc /home/rainer/projects/KTagebuch/build/doc/CMakeFiles/doc-handbook.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/doc-handbook.dir/depend
