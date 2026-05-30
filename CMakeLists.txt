cmake_minimum_required(VERSION 3.16)

# Project name
PROJECT( kchmviewer )

# Init cmake
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Necessary packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network PrintSupport DBus WebEngineWidgets Xml)
FIND_PACKAGE( Libchm REQUIRED)

# libzip
FIND_PATH(LIBZIP_INCLUDE_DIR zip.h)
FIND_LIBRARY(LIBZIP_LIBRARY NAMES zip)

IF (LIBZIP_INCLUDE_DIR AND LIBZIP_LIBRARY)
	MESSAGE(STATUS "Found libzip: ${LIBZIP_LIBRARY}")
ELSE ()
	MESSAGE(FATAL_ERROR "Could not find libzip. Please install libzip and libzip-devel packages")
ENDIF ()

# Set compilation params
INCLUDE_DIRECTORIES(
		${CMAKE_SOURCE_DIR}/src
		${CMAKE_SOURCE_DIR}/lib/libebook )

if(NOT DEFINED LOCALE_INSTALL_DIR)
	set(LOCALE_INSTALL_DIR share/locale)
endif()

# Run in those subdirectories
ADD_SUBDIRECTORY( lib/libebook )
ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( po )
ADD_SUBDIRECTORY( packages )
