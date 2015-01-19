# - Find ags_example_cpp_library
#
# Pass in the following variables
#
#  AGS_EXAMPLE_CPP_LIB_ROOT             - a hint where to find c-blosc (can be an ENV var)
#
# Once done this will define

#  AGS_EXAMPLE_CPP_LIB_FOUND          - True if found.
#  AGS_EXAMPLE_CPP_LIB_INCLUDE_DIRS   - where to find includes
#  AGS_EXAMPLE_CPP_LIB_STATIC_LIBRARIES      - List of static libraries to link against
#  AGS_EXAMPLE_CPP_LIB_LIBRARIES      - List of shared libraries to link against
#  AGS_EXAMPLE_CPP_LIB_DLLS           - DLLs/shared libs required at runtime
#
#=============================================================================
# Copyright 2015 Spencer Stirling
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

if (NOT AGS_EXAMPLE_CPP_LIB_ROOT)
    set (AGS_EXAMPLE_CPP_LIB_ROOT  $ENV{AGS_EXAMPLE_CPP_LIB_ROOT})
endif ()

# find include dir
find_path(AGS_EXAMPLE_CPP_LIB_INCLUDE_DIR 
          NAMES activision_game_science/ags_blosc_wrapper.h
          HINTS
          "${AGS_EXAMPLE_CPP_LIB_ROOT}"
          PATH_SUFFIXES include)

# find library to link against
if (WIN32)
# FIXME
  if (ZLIB_USE_STATIC_LIBS)
    find_library(ZLIB_LIBRARY  
                 NAMES  zlibstatic  ${ZLIB_NAMES}
                 HINTS  
                 "${ZLIB_ROOT}"
                 "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
                 "$ENV{PROGRAMFILES}/zlib"          
                 PATH_SUFFIXES  lib)
  else ()
    find_library(ZLIB_LIBRARY  
                 NAMES  ${ZLIB_NAMES} 
                 HINTS  
                 "${ZLIB_ROOT}"
                 "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
                 "$ENV{PROGRAMFILES}/zlib"          
                 PATH_SUFFIXES  lib)
  endif ()

else ()

  # find static lib first
  set (CMAKE_FIND_LIBRARY_SUFFIXES_KEEP  ${CMAKE_FIND_LIBRARY_SUFFIXES})
  set (CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  find_library(AGS_EXAMPLE_CPP_LIB_STATIC_LIBRARY  
               NAMES  ags_blosc_wrapper_static
               HINTS
               "${AGS_EXAMPLE_CPP_LIB_ROOT}"
               PATH_SUFFIXES  lib)
  set (CMAKE_FIND_LIBRARY_SUFFIXES  ${CMAKE_FIND_LIBRARY_SUFFIXES_KEEP})

  # now find shared lib
  find_library(AGS_EXAMPLE_CPP_LIB_LIBRARY  
               NAMES  ags_blosc_wrapper
               HINTS
               "${AGS_EXAMPLE_CPP_LIB_ROOT}"
               PATH_SUFFIXES  lib)

endif ()


mark_as_advanced(AGS_EXAMPLE_CPP_LIB_STATIC_LIBRARY AGS_EXAMPLE_CPP_LIB_LIBRARY AGS_EXAMPLE_CPP_LIB_INCLUDE_DIR)


# handle the QUIETLY and REQUIRED arguments and set AGS_EXAMPLE_CPP_LIB_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AGS_EXAMPLE_CPP_LIB REQUIRED_VARS AGS_EXAMPLE_CPP_LIB_STATIC_LIBRARY AGS_EXAMPLE_CPP_LIB_LIBRARY AGS_EXAMPLE_CPP_LIB_INCLUDE_DIR)


if(AGS_EXAMPLE_CPP_LIB_FOUND)
    set(AGS_EXAMPLE_CPP_LIB_INCLUDE_DIRS ${AGS_EXAMPLE_CPP_LIB_INCLUDE_DIR})
    set(AGS_EXAMPLE_CPP_LIB_STATIC_LIBRARIES ${AGS_EXAMPLE_CPP_LIB_STATIC_LIBRARY})
    set(AGS_EXAMPLE_CPP_LIB_LIBRARIES ${AGS_EXAMPLE_CPP_LIB_LIBRARY})
    # find DLLS, if necessary
    if (WIN32)
        #FIXME
        find_file(ZLIB_DLLS
                  NAMES  zlib.dll
                  PATHS
                  "${ZLIB_ROOT}"
                  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
                  "$ENV{PROGRAMFILES}/zlib"          
                  PATH_SUFFIXES  bin  lib)
    else ()
        set (AGS_EXAMPLE_CPP_LIB_DLLS  ${AGS_EXAMPLE_CPP_LIB_LIBRARIES})
    endif ()
endif()

