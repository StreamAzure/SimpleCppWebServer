# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stream/SimpleCppServer/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stream/SimpleCppServer/src/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/Acceptor.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Acceptor.cpp.o: ../Acceptor.cpp
CMakeFiles/server.dir/Acceptor.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/Acceptor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Acceptor.cpp.o -MF CMakeFiles/server.dir/Acceptor.cpp.o.d -o CMakeFiles/server.dir/Acceptor.cpp.o -c /home/stream/SimpleCppServer/src/Acceptor.cpp

CMakeFiles/server.dir/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Acceptor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Acceptor.cpp > CMakeFiles/server.dir/Acceptor.cpp.i

CMakeFiles/server.dir/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Acceptor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Acceptor.cpp -o CMakeFiles/server.dir/Acceptor.cpp.s

CMakeFiles/server.dir/Buffer.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Buffer.cpp.o: ../Buffer.cpp
CMakeFiles/server.dir/Buffer.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/Buffer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Buffer.cpp.o -MF CMakeFiles/server.dir/Buffer.cpp.o.d -o CMakeFiles/server.dir/Buffer.cpp.o -c /home/stream/SimpleCppServer/src/Buffer.cpp

CMakeFiles/server.dir/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Buffer.cpp > CMakeFiles/server.dir/Buffer.cpp.i

CMakeFiles/server.dir/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Buffer.cpp -o CMakeFiles/server.dir/Buffer.cpp.s

CMakeFiles/server.dir/Channel.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Channel.cpp.o: ../Channel.cpp
CMakeFiles/server.dir/Channel.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/Channel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Channel.cpp.o -MF CMakeFiles/server.dir/Channel.cpp.o.d -o CMakeFiles/server.dir/Channel.cpp.o -c /home/stream/SimpleCppServer/src/Channel.cpp

CMakeFiles/server.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Channel.cpp > CMakeFiles/server.dir/Channel.cpp.i

CMakeFiles/server.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Channel.cpp -o CMakeFiles/server.dir/Channel.cpp.s

CMakeFiles/server.dir/Connection.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Connection.cpp.o: ../Connection.cpp
CMakeFiles/server.dir/Connection.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/Connection.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Connection.cpp.o -MF CMakeFiles/server.dir/Connection.cpp.o.d -o CMakeFiles/server.dir/Connection.cpp.o -c /home/stream/SimpleCppServer/src/Connection.cpp

CMakeFiles/server.dir/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Connection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Connection.cpp > CMakeFiles/server.dir/Connection.cpp.i

CMakeFiles/server.dir/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Connection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Connection.cpp -o CMakeFiles/server.dir/Connection.cpp.s

CMakeFiles/server.dir/Epoll.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Epoll.cpp.o: ../Epoll.cpp
CMakeFiles/server.dir/Epoll.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/Epoll.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Epoll.cpp.o -MF CMakeFiles/server.dir/Epoll.cpp.o.d -o CMakeFiles/server.dir/Epoll.cpp.o -c /home/stream/SimpleCppServer/src/Epoll.cpp

CMakeFiles/server.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Epoll.cpp > CMakeFiles/server.dir/Epoll.cpp.i

CMakeFiles/server.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Epoll.cpp -o CMakeFiles/server.dir/Epoll.cpp.s

CMakeFiles/server.dir/EventLoop.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/EventLoop.cpp.o: ../EventLoop.cpp
CMakeFiles/server.dir/EventLoop.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/EventLoop.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/EventLoop.cpp.o -MF CMakeFiles/server.dir/EventLoop.cpp.o.d -o CMakeFiles/server.dir/EventLoop.cpp.o -c /home/stream/SimpleCppServer/src/EventLoop.cpp

CMakeFiles/server.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/EventLoop.cpp > CMakeFiles/server.dir/EventLoop.cpp.i

CMakeFiles/server.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/EventLoop.cpp -o CMakeFiles/server.dir/EventLoop.cpp.s

CMakeFiles/server.dir/InetAddress.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/InetAddress.cpp.o: ../InetAddress.cpp
CMakeFiles/server.dir/InetAddress.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/InetAddress.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/InetAddress.cpp.o -MF CMakeFiles/server.dir/InetAddress.cpp.o.d -o CMakeFiles/server.dir/InetAddress.cpp.o -c /home/stream/SimpleCppServer/src/InetAddress.cpp

CMakeFiles/server.dir/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/InetAddress.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/InetAddress.cpp > CMakeFiles/server.dir/InetAddress.cpp.i

CMakeFiles/server.dir/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/InetAddress.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/InetAddress.cpp -o CMakeFiles/server.dir/InetAddress.cpp.s

CMakeFiles/server.dir/Server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Server.cpp.o: ../Server.cpp
CMakeFiles/server.dir/Server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/Server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Server.cpp.o -MF CMakeFiles/server.dir/Server.cpp.o.d -o CMakeFiles/server.dir/Server.cpp.o -c /home/stream/SimpleCppServer/src/Server.cpp

CMakeFiles/server.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Server.cpp > CMakeFiles/server.dir/Server.cpp.i

CMakeFiles/server.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Server.cpp -o CMakeFiles/server.dir/Server.cpp.s

CMakeFiles/server.dir/Socket.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/Socket.cpp.o: ../Socket.cpp
CMakeFiles/server.dir/Socket.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/server.dir/Socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/Socket.cpp.o -MF CMakeFiles/server.dir/Socket.cpp.o.d -o CMakeFiles/server.dir/Socket.cpp.o -c /home/stream/SimpleCppServer/src/Socket.cpp

CMakeFiles/server.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/Socket.cpp > CMakeFiles/server.dir/Socket.cpp.i

CMakeFiles/server.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/Socket.cpp -o CMakeFiles/server.dir/Socket.cpp.s

CMakeFiles/server.dir/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.cpp.o: ../server.cpp
CMakeFiles/server.dir/server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/server.dir/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/server.cpp.o -MF CMakeFiles/server.dir/server.cpp.o.d -o CMakeFiles/server.dir/server.cpp.o -c /home/stream/SimpleCppServer/src/server.cpp

CMakeFiles/server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/server.cpp > CMakeFiles/server.dir/server.cpp.i

CMakeFiles/server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/server.cpp -o CMakeFiles/server.dir/server.cpp.s

CMakeFiles/server.dir/util.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/util.cpp.o: ../util.cpp
CMakeFiles/server.dir/util.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/server.dir/util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/util.cpp.o -MF CMakeFiles/server.dir/util.cpp.o.d -o CMakeFiles/server.dir/util.cpp.o -c /home/stream/SimpleCppServer/src/util.cpp

CMakeFiles/server.dir/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stream/SimpleCppServer/src/util.cpp > CMakeFiles/server.dir/util.cpp.i

CMakeFiles/server.dir/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stream/SimpleCppServer/src/util.cpp -o CMakeFiles/server.dir/util.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/Acceptor.cpp.o" \
"CMakeFiles/server.dir/Buffer.cpp.o" \
"CMakeFiles/server.dir/Channel.cpp.o" \
"CMakeFiles/server.dir/Connection.cpp.o" \
"CMakeFiles/server.dir/Epoll.cpp.o" \
"CMakeFiles/server.dir/EventLoop.cpp.o" \
"CMakeFiles/server.dir/InetAddress.cpp.o" \
"CMakeFiles/server.dir/Server.cpp.o" \
"CMakeFiles/server.dir/Socket.cpp.o" \
"CMakeFiles/server.dir/server.cpp.o" \
"CMakeFiles/server.dir/util.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Acceptor.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Buffer.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Channel.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Connection.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Epoll.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/EventLoop.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/InetAddress.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Server.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/Socket.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/server.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/util.cpp.o
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/build.make
/home/stream/SimpleCppServer/server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stream/SimpleCppServer/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable /home/stream/SimpleCppServer/server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: /home/stream/SimpleCppServer/server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/stream/SimpleCppServer/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stream/SimpleCppServer/src /home/stream/SimpleCppServer/src /home/stream/SimpleCppServer/src/build /home/stream/SimpleCppServer/src/build /home/stream/SimpleCppServer/src/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

