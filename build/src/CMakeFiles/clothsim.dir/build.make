# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/user/CS184/test/Apr22/CS_184_Final_Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/user/CS184/test/Apr22/CS_184_Final_Project/build

# Include any dependencies generated for this target.
include src/CMakeFiles/clothsim.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/clothsim.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/clothsim.dir/flags.make

src/CMakeFiles/clothsim.dir/particles.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/particles.cpp.o: ../src/particles.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/clothsim.dir/particles.cpp.o"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/particles.cpp.o -c /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/particles.cpp

src/CMakeFiles/clothsim.dir/particles.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/particles.cpp.i"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/particles.cpp > CMakeFiles/clothsim.dir/particles.cpp.i

src/CMakeFiles/clothsim.dir/particles.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/particles.cpp.s"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/particles.cpp -o CMakeFiles/clothsim.dir/particles.cpp.s

src/CMakeFiles/clothsim.dir/particles.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/particles.cpp.o.requires

src/CMakeFiles/clothsim.dir/particles.cpp.o.provides: src/CMakeFiles/clothsim.dir/particles.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/particles.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/particles.cpp.o.provides

src/CMakeFiles/clothsim.dir/particles.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/particles.cpp.o


src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o: ../src/collision/sphere.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/collision/sphere.cpp.o -c /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/collision/sphere.cpp

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/collision/sphere.cpp.i"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/collision/sphere.cpp > CMakeFiles/clothsim.dir/collision/sphere.cpp.i

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/collision/sphere.cpp.s"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/collision/sphere.cpp -o CMakeFiles/clothsim.dir/collision/sphere.cpp.s

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides

src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o


src/CMakeFiles/clothsim.dir/main.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/clothsim.dir/main.cpp.o"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/main.cpp.o -c /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/main.cpp

src/CMakeFiles/clothsim.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/main.cpp.i"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/main.cpp > CMakeFiles/clothsim.dir/main.cpp.i

src/CMakeFiles/clothsim.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/main.cpp.s"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/main.cpp -o CMakeFiles/clothsim.dir/main.cpp.s

src/CMakeFiles/clothsim.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/main.cpp.o.requires

src/CMakeFiles/clothsim.dir/main.cpp.o.provides: src/CMakeFiles/clothsim.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/main.cpp.o.provides

src/CMakeFiles/clothsim.dir/main.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/main.cpp.o


src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o: ../src/ParticleSimulator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o -c /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/ParticleSimulator.cpp

src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/ParticleSimulator.cpp.i"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/ParticleSimulator.cpp > CMakeFiles/clothsim.dir/ParticleSimulator.cpp.i

src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/ParticleSimulator.cpp.s"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/ParticleSimulator.cpp -o CMakeFiles/clothsim.dir/ParticleSimulator.cpp.s

src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.requires

src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.provides: src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.provides

src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o


src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o: ../src/misc/sphere_drawing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o -c /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/misc/sphere_drawing.cpp

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/misc/sphere_drawing.cpp > CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.i

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/misc/sphere_drawing.cpp -o CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.s

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides

src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o


src/CMakeFiles/clothsim.dir/camera.cpp.o: src/CMakeFiles/clothsim.dir/flags.make
src/CMakeFiles/clothsim.dir/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/clothsim.dir/camera.cpp.o"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clothsim.dir/camera.cpp.o -c /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/camera.cpp

src/CMakeFiles/clothsim.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clothsim.dir/camera.cpp.i"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/camera.cpp > CMakeFiles/clothsim.dir/camera.cpp.i

src/CMakeFiles/clothsim.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clothsim.dir/camera.cpp.s"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/user/CS184/test/Apr22/CS_184_Final_Project/src/camera.cpp -o CMakeFiles/clothsim.dir/camera.cpp.s

src/CMakeFiles/clothsim.dir/camera.cpp.o.requires:

.PHONY : src/CMakeFiles/clothsim.dir/camera.cpp.o.requires

src/CMakeFiles/clothsim.dir/camera.cpp.o.provides: src/CMakeFiles/clothsim.dir/camera.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/clothsim.dir/build.make src/CMakeFiles/clothsim.dir/camera.cpp.o.provides.build
.PHONY : src/CMakeFiles/clothsim.dir/camera.cpp.o.provides

src/CMakeFiles/clothsim.dir/camera.cpp.o.provides.build: src/CMakeFiles/clothsim.dir/camera.cpp.o


# Object files for target clothsim
clothsim_OBJECTS = \
"CMakeFiles/clothsim.dir/particles.cpp.o" \
"CMakeFiles/clothsim.dir/collision/sphere.cpp.o" \
"CMakeFiles/clothsim.dir/main.cpp.o" \
"CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o" \
"CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o" \
"CMakeFiles/clothsim.dir/camera.cpp.o"

# External object files for target clothsim
clothsim_EXTERNAL_OBJECTS =

clothsim: src/CMakeFiles/clothsim.dir/particles.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/main.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/camera.cpp.o
clothsim: src/CMakeFiles/clothsim.dir/build.make
clothsim: CGL/src/libCGL.a
clothsim: ext/nanogui/libnanogui.dylib
clothsim: /usr/local/lib/libfreetype.dylib
clothsim: src/CMakeFiles/clothsim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../clothsim"
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clothsim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/clothsim.dir/build: clothsim

.PHONY : src/CMakeFiles/clothsim.dir/build

src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/particles.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/collision/sphere.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/main.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/ParticleSimulator.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/misc/sphere_drawing.cpp.o.requires
src/CMakeFiles/clothsim.dir/requires: src/CMakeFiles/clothsim.dir/camera.cpp.o.requires

.PHONY : src/CMakeFiles/clothsim.dir/requires

src/CMakeFiles/clothsim.dir/clean:
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src && $(CMAKE_COMMAND) -P CMakeFiles/clothsim.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/clothsim.dir/clean

src/CMakeFiles/clothsim.dir/depend:
	cd /Users/user/CS184/test/Apr22/CS_184_Final_Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/user/CS184/test/Apr22/CS_184_Final_Project /Users/user/CS184/test/Apr22/CS_184_Final_Project/src /Users/user/CS184/test/Apr22/CS_184_Final_Project/build /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src /Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src/CMakeFiles/clothsim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/clothsim.dir/depend

