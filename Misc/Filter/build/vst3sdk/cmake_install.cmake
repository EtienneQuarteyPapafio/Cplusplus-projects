# Install script for directory: C:/Users/Etienne Quartey-Papa/Downloads/vst-sdk_3.7.9_build-61_2023-10-09/VST_SDK/vst3sdk

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Filter")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/pluginterfaces/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/base/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/public.sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/public.sdk/source/vst/interappaudio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/public.sdk/samples/vst-hosting/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/public.sdk/samples/vst-utilities/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/public.sdk/samples/vst/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Etienne Quartey-Papa/Desktop/Lectures/AP2/Uni_Ap2_Work/Filter/build/vst3sdk/public.sdk/source/vst/auv3wrapper/cmake_install.cmake")
endif()

