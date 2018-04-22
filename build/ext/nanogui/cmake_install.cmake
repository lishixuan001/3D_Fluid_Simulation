<<<<<<< HEAD
# Install script for directory: /Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/ext/nanogui
=======
# Install script for directory: /Users/user/CS184/test/Apr22/CS_184_Final_Project/ext/nanogui
>>>>>>> 37df4d8225864e7081fb0b6aa0d5396c70cc4439

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
<<<<<<< HEAD
  include("/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/build/ext/nanogui/ext_build/glfw/cmake_install.cmake")
=======
  include("/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/ext/nanogui/ext_build/glfw/cmake_install.cmake")
>>>>>>> 37df4d8225864e7081fb0b6aa0d5396c70cc4439

endif()

