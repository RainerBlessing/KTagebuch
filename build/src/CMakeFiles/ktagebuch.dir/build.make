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

# Include any dependencies generated for this target.
include src/CMakeFiles/ktagebuch.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/ktagebuch.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/ktagebuch.dir/flags.make

src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o: src/CMakeFiles/ktagebuch.dir/flags.make
src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o: src/ktagebuch_automoc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o -c /home/rainer/projects/KTagebuch/build/src/ktagebuch_automoc.cpp

src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ktagebuch.dir/ktagebuch_automoc.i"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rainer/projects/KTagebuch/build/src/ktagebuch_automoc.cpp > CMakeFiles/ktagebuch.dir/ktagebuch_automoc.i

src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ktagebuch.dir/ktagebuch_automoc.s"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rainer/projects/KTagebuch/build/src/ktagebuch_automoc.cpp -o CMakeFiles/ktagebuch.dir/ktagebuch_automoc.s

src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.requires:
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.requires

src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.provides: src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.requires
	$(MAKE) -f src/CMakeFiles/ktagebuch.dir/build.make src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.provides.build
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.provides

src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.provides.build: src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.provides.build

src/CMakeFiles/ktagebuch.dir/ktagebuch.o: src/CMakeFiles/ktagebuch.dir/flags.make
src/CMakeFiles/ktagebuch.dir/ktagebuch.o: ../src/ktagebuch.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ktagebuch.dir/ktagebuch.o"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ktagebuch.dir/ktagebuch.o -c /home/rainer/projects/KTagebuch/src/ktagebuch.cpp

src/CMakeFiles/ktagebuch.dir/ktagebuch.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ktagebuch.dir/ktagebuch.i"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rainer/projects/KTagebuch/src/ktagebuch.cpp > CMakeFiles/ktagebuch.dir/ktagebuch.i

src/CMakeFiles/ktagebuch.dir/ktagebuch.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ktagebuch.dir/ktagebuch.s"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rainer/projects/KTagebuch/src/ktagebuch.cpp -o CMakeFiles/ktagebuch.dir/ktagebuch.s

src/CMakeFiles/ktagebuch.dir/ktagebuch.o.requires:
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuch.o.requires

src/CMakeFiles/ktagebuch.dir/ktagebuch.o.provides: src/CMakeFiles/ktagebuch.dir/ktagebuch.o.requires
	$(MAKE) -f src/CMakeFiles/ktagebuch.dir/build.make src/CMakeFiles/ktagebuch.dir/ktagebuch.o.provides.build
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuch.o.provides

src/CMakeFiles/ktagebuch.dir/ktagebuch.o.provides.build: src/CMakeFiles/ktagebuch.dir/ktagebuch.o
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuch.o.provides.build

src/CMakeFiles/ktagebuch.dir/main.o: src/CMakeFiles/ktagebuch.dir/flags.make
src/CMakeFiles/ktagebuch.dir/main.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ktagebuch.dir/main.o"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ktagebuch.dir/main.o -c /home/rainer/projects/KTagebuch/src/main.cpp

src/CMakeFiles/ktagebuch.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ktagebuch.dir/main.i"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rainer/projects/KTagebuch/src/main.cpp > CMakeFiles/ktagebuch.dir/main.i

src/CMakeFiles/ktagebuch.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ktagebuch.dir/main.s"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rainer/projects/KTagebuch/src/main.cpp -o CMakeFiles/ktagebuch.dir/main.s

src/CMakeFiles/ktagebuch.dir/main.o.requires:
.PHONY : src/CMakeFiles/ktagebuch.dir/main.o.requires

src/CMakeFiles/ktagebuch.dir/main.o.provides: src/CMakeFiles/ktagebuch.dir/main.o.requires
	$(MAKE) -f src/CMakeFiles/ktagebuch.dir/build.make src/CMakeFiles/ktagebuch.dir/main.o.provides.build
.PHONY : src/CMakeFiles/ktagebuch.dir/main.o.provides

src/CMakeFiles/ktagebuch.dir/main.o.provides.build: src/CMakeFiles/ktagebuch.dir/main.o
.PHONY : src/CMakeFiles/ktagebuch.dir/main.o.provides.build

src/CMakeFiles/ktagebuch.dir/ktagebuchview.o: src/CMakeFiles/ktagebuch.dir/flags.make
src/CMakeFiles/ktagebuch.dir/ktagebuchview.o: ../src/ktagebuchview.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ktagebuch.dir/ktagebuchview.o"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ktagebuch.dir/ktagebuchview.o -c /home/rainer/projects/KTagebuch/src/ktagebuchview.cpp

src/CMakeFiles/ktagebuch.dir/ktagebuchview.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ktagebuch.dir/ktagebuchview.i"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rainer/projects/KTagebuch/src/ktagebuchview.cpp > CMakeFiles/ktagebuch.dir/ktagebuchview.i

src/CMakeFiles/ktagebuch.dir/ktagebuchview.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ktagebuch.dir/ktagebuchview.s"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rainer/projects/KTagebuch/src/ktagebuchview.cpp -o CMakeFiles/ktagebuch.dir/ktagebuchview.s

src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.requires:
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.requires

src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.provides: src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.requires
	$(MAKE) -f src/CMakeFiles/ktagebuch.dir/build.make src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.provides.build
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.provides

src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.provides.build: src/CMakeFiles/ktagebuch.dir/ktagebuchview.o
.PHONY : src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.provides.build

src/CMakeFiles/ktagebuch.dir/settings.o: src/CMakeFiles/ktagebuch.dir/flags.make
src/CMakeFiles/ktagebuch.dir/settings.o: src/settings.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/ktagebuch.dir/settings.o"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ktagebuch.dir/settings.o -c /home/rainer/projects/KTagebuch/build/src/settings.cpp

src/CMakeFiles/ktagebuch.dir/settings.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ktagebuch.dir/settings.i"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rainer/projects/KTagebuch/build/src/settings.cpp > CMakeFiles/ktagebuch.dir/settings.i

src/CMakeFiles/ktagebuch.dir/settings.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ktagebuch.dir/settings.s"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rainer/projects/KTagebuch/build/src/settings.cpp -o CMakeFiles/ktagebuch.dir/settings.s

src/CMakeFiles/ktagebuch.dir/settings.o.requires:
.PHONY : src/CMakeFiles/ktagebuch.dir/settings.o.requires

src/CMakeFiles/ktagebuch.dir/settings.o.provides: src/CMakeFiles/ktagebuch.dir/settings.o.requires
	$(MAKE) -f src/CMakeFiles/ktagebuch.dir/build.make src/CMakeFiles/ktagebuch.dir/settings.o.provides.build
.PHONY : src/CMakeFiles/ktagebuch.dir/settings.o.provides

src/CMakeFiles/ktagebuch.dir/settings.o.provides.build: src/CMakeFiles/ktagebuch.dir/settings.o
.PHONY : src/CMakeFiles/ktagebuch.dir/settings.o.provides.build

src/ui_ktagebuchview_base.h: ../src/ktagebuchview_base.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_ktagebuchview_base.h"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/cmake -DKDE4_HEADER:BOOL=ON -DKDE_UIC_EXECUTABLE:FILEPATH=/usr/bin/uic-qt4 -DKDE_UIC_FILE:FILEPATH=/home/rainer/projects/KTagebuch/src/ktagebuchview_base.ui -DKDE_UIC_H_FILE:FILEPATH=/home/rainer/projects/KTagebuch/build/src/ui_ktagebuchview_base.h -DKDE_UIC_BASENAME:STRING=ktagebuchview_base -P /usr/share/kde4/apps/cmake/modules/kde4uic.cmake

src/ui_prefs_base.h: ../src/prefs_base.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_prefs_base.h"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/cmake -DKDE4_HEADER:BOOL=ON -DKDE_UIC_EXECUTABLE:FILEPATH=/usr/bin/uic-qt4 -DKDE_UIC_FILE:FILEPATH=/home/rainer/projects/KTagebuch/src/prefs_base.ui -DKDE_UIC_H_FILE:FILEPATH=/home/rainer/projects/KTagebuch/build/src/ui_prefs_base.h -DKDE_UIC_BASENAME:STRING=prefs_base -P /usr/share/kde4/apps/cmake/modules/kde4uic.cmake

src/settings.h: ../src/ktagebuch.kcfg
src/settings.h: ../src/settings.kcfgc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rainer/projects/KTagebuch/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating settings.h, settings.cpp"
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/kconfig_compiler /home/rainer/projects/KTagebuch/src/ktagebuch.kcfg /home/rainer/projects/KTagebuch/src/settings.kcfgc -d /home/rainer/projects/KTagebuch/build/src

src/settings.cpp: src/settings.h

# Object files for target ktagebuch
ktagebuch_OBJECTS = \
"CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o" \
"CMakeFiles/ktagebuch.dir/ktagebuch.o" \
"CMakeFiles/ktagebuch.dir/main.o" \
"CMakeFiles/ktagebuch.dir/ktagebuchview.o" \
"CMakeFiles/ktagebuch.dir/settings.o"

# External object files for target ktagebuch
ktagebuch_EXTERNAL_OBJECTS =

src/ktagebuch: src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o
src/ktagebuch: src/CMakeFiles/ktagebuch.dir/ktagebuch.o
src/ktagebuch: src/CMakeFiles/ktagebuch.dir/main.o
src/ktagebuch: src/CMakeFiles/ktagebuch.dir/ktagebuchview.o
src/ktagebuch: src/CMakeFiles/ktagebuch.dir/settings.o
src/ktagebuch: /usr/lib/libkdeui.so.5.3.0
src/ktagebuch: /usr/lib/libkdecore.so.5.3.0
src/ktagebuch: /usr/lib/libQtDBus.so
src/ktagebuch: /usr/lib/libQtCore.so
src/ktagebuch: /usr/lib/libQtSvg.so
src/ktagebuch: /usr/lib/libQtGui.so
src/ktagebuch: src/CMakeFiles/ktagebuch.dir/build.make
src/ktagebuch: src/CMakeFiles/ktagebuch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ktagebuch"
	cd /home/rainer/projects/KTagebuch/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ktagebuch.dir/link.txt --verbose=$(VERBOSE)
	cd /home/rainer/projects/KTagebuch/build/src && /usr/bin/cmake -D_filename=/home/rainer/projects/KTagebuch/build/src/ktagebuch.shell -D_library_path_variable=LD_LIBRARY_PATH -D_ld_library_path="/home/rainer/projects/KTagebuch/build/lib/./:/lib:/usr/lib:/usr/lib" -D_executable=/home/rainer/projects/KTagebuch/build/src/ktagebuch -P /usr/share/kde4/apps/cmake/modules/kde4_exec_via_sh.cmake

# Rule to build all files generated by this target.
src/CMakeFiles/ktagebuch.dir/build: src/ktagebuch
.PHONY : src/CMakeFiles/ktagebuch.dir/build

src/CMakeFiles/ktagebuch.dir/requires: src/CMakeFiles/ktagebuch.dir/ktagebuch_automoc.o.requires
src/CMakeFiles/ktagebuch.dir/requires: src/CMakeFiles/ktagebuch.dir/ktagebuch.o.requires
src/CMakeFiles/ktagebuch.dir/requires: src/CMakeFiles/ktagebuch.dir/main.o.requires
src/CMakeFiles/ktagebuch.dir/requires: src/CMakeFiles/ktagebuch.dir/ktagebuchview.o.requires
src/CMakeFiles/ktagebuch.dir/requires: src/CMakeFiles/ktagebuch.dir/settings.o.requires
.PHONY : src/CMakeFiles/ktagebuch.dir/requires

src/CMakeFiles/ktagebuch.dir/clean:
	cd /home/rainer/projects/KTagebuch/build/src && $(CMAKE_COMMAND) -P CMakeFiles/ktagebuch.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/ktagebuch.dir/clean

src/CMakeFiles/ktagebuch.dir/depend: src/ui_ktagebuchview_base.h
src/CMakeFiles/ktagebuch.dir/depend: src/ui_prefs_base.h
src/CMakeFiles/ktagebuch.dir/depend: src/settings.h
src/CMakeFiles/ktagebuch.dir/depend: src/settings.cpp
	cd /home/rainer/projects/KTagebuch/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rainer/projects/KTagebuch /home/rainer/projects/KTagebuch/src /home/rainer/projects/KTagebuch/build /home/rainer/projects/KTagebuch/build/src /home/rainer/projects/KTagebuch/build/src/CMakeFiles/ktagebuch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/ktagebuch.dir/depend

