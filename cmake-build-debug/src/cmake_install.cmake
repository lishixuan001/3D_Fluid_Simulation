# Install script for directory: /Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/clothsim")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project" TYPE EXECUTABLE FILES "/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/cmake-build-debug/clothsim")
  if(EXISTS "$ENV{DESTDIR}/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/clothsim" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/clothsim")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/cmake-build-debug/ext/nanogui"
      "$ENV{DESTDIR}/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/clothsim")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" "$ENV{DESTDIR}/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/clothsim")
    endif()
  endif()
endif()

