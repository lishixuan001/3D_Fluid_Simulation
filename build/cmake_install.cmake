<<<<<<< HEAD
# Install script for directory: /Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/")
=======
# Install script for directory: /Users/user/CS184/test/Apr22/CS_184_Final_Project

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/user/CS184/test/Apr22/CS_184_Final_Project/")
>>>>>>> 37df4d8225864e7081fb0b6aa0d5396c70cc4439
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
  include("/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/build/ext/nanogui/cmake_install.cmake")
  include("/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/build/CGL/cmake_install.cmake")
  include("/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/build/src/cmake_install.cmake")
=======
  include("/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/ext/nanogui/cmake_install.cmake")
  include("/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/CGL/cmake_install.cmake")
  include("/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/src/cmake_install.cmake")
>>>>>>> 37df4d8225864e7081fb0b6aa0d5396c70cc4439

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/Users/lishixuan/Documents/Classes/CS 184/Projects/CS_184_Final_Project/build/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/Users/user/CS184/test/Apr22/CS_184_Final_Project/build/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 37df4d8225864e7081fb0b6aa0d5396c70cc4439
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
