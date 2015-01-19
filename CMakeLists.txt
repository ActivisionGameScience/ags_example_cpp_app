cmake_minimum_required(VERSION  2.8.11)


############################
#
#  make sure RPATH is relative (as it should be, damnit)
#
#############################

set (CMAKE_BUILD_WITH_INSTALL_RPATH  TRUE)
set (CMAKE_INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")


###########################
#
#  set preprocessor defines
#
###########################

if (UNIX)
  add_definitions(-DUNIX)
endif ()

if (WIN32)
  add_definitions(-DBOOST_ALL_NO_LIB)  # disable Boost autolinking
  add_definitions(-DBOOST_ALL_DYN_LINK)  # enable link to Boost DLLs
endif ()


#############################
# import Third-party dependencies (using cmake "Find" modules)
# NOTE: several of the "official" Find modules are either (1) missing, or (2) don't work very well
#       hence most of these are home-brewed
#############################
set(CMAKE_MODULE_PATH  "${CMAKE_SOURCE_DIR}/cmake/Modules/"  ${CMAKE_MODULE_PATH})


# find ags_example_cpp_lib (set hint AGS_EXAMPLE_CPP_LIB_ROOT)
find_package(AGS_EXAMPLE_CPP_LIB  REQUIRED)
include_directories(${AGS_EXAMPLE_CPP_LIB_INCLUDE_DIR})
message (STATUS  "CBLOSC DLLS: ${AGS_EXAMPLE_CPP_LIB_DLLS}")
message (STATUS  "CBLOSC SHARED LIB: ${AGS_EXAMPLE_CPP_LIB_LIBRARIES}")
set (DLLS_to_install  ${DLLS_to_install}  ${AGS_EXAMPLE_CPP_LIB_DLLS})


# find c-blosc (set hint CBLOSC_ROOT)
find_package(CBLOSC  REQUIRED)
include_directories(${CBLOSC_INCLUDE_DIR})
message (STATUS  "CBLOSC DLLS: ${CBLOSC_DLLS}")
message (STATUS  "CBLOSC SHARED LIB: ${CBLOSC_LIBRARIES}")
set (DLLS_to_install  ${DLLS_to_install}  ${CBLOSC_DLLS})


# find Boost (set hint BOOST_ROOT)
set (Boost_USE_STATIC_LIBS  OFF)
set (Boost_USE_STATIC_RUNTIME  OFF)  # this should always be set to OFF
set (Boost_NO_BOOST_CMAKE  ON)  # this should always be set to ON
set (Boost_COMPONENTS  timer thread chrono date_time filesystem system)
find_package (Boost  COMPONENTS  ${Boost_COMPONENTS}  REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
message (STATUS  "Boost DLLS: ${Boost_DLLS}")
set (DLLS_to_install  ${DLLS_to_install}  ${Boost_DLLS})


###########################
#
#  ags_blosc_compress target
#  THIS IS AN EXECUTABLE TARGET
#
###########################

# add includes for current target
set (WORKING_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ags_blosc_compress)
include_directories(${WORKING_SOURCE_DIR}/inc)

# add .cpp, .c, .hpp, .h files
file (GLOB_RECURSE  WORKING_HPP_SOURCES  ${WORKING_SOURCE_DIR}/inc/*.hpp)
file (GLOB_RECURSE  WORKING_H_SOURCES  ${WORKING_SOURCE_DIR}/inc/*.h)
file (GLOB_RECURSE  WORKING_CPP_SOURCES  ${WORKING_SOURCE_DIR}/src/*.cpp)
file (GLOB_RECURSE  WORKING_C_SOURCES  ${WORKING_SOURCE_DIR}/src/*.c)
set (WORKING_SOURCES  ${WORKING_HPP_SOURCES}  ${WORKING_H_SOURCES}  ${WORKING_CPP_SOURCES}  ${WORKING_C_SOURCES})

# create the target
add_executable (ags_blosc_compress ${WORKING_SOURCES})
target_link_libraries (ags_blosc_compress  ${AGS_EXAMPLE_CPP_LIB_LIBRARIES} ${CBLOSC_LIBRARIES} 
                                           ${Boost_LIBRARIES} )

# install the target
install (TARGETS  ags_blosc_compress  
         DESTINATION  bin
         PERMISSIONS  OWNER_EXECUTE  OWNER_READ  OWNER_WRITE)


###########################
#
#  ags_blosc_decompress target
#  THIS IS AN EXECUTABLE TARGET
#
###########################

# add includes for current target
set (WORKING_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ags_blosc_decompress)
include_directories(${WORKING_SOURCE_DIR}/inc)

# add .cpp, .c, .hpp, .h files
file (GLOB_RECURSE  WORKING_HPP_SOURCES  ${WORKING_SOURCE_DIR}/inc/*.hpp)
file (GLOB_RECURSE  WORKING_H_SOURCES  ${WORKING_SOURCE_DIR}/inc/*.h)
file (GLOB_RECURSE  WORKING_CPP_SOURCES  ${WORKING_SOURCE_DIR}/src/*.cpp)
file (GLOB_RECURSE  WORKING_C_SOURCES  ${WORKING_SOURCE_DIR}/src/*.c)
set (WORKING_SOURCES  ${WORKING_HPP_SOURCES}  ${WORKING_H_SOURCES}  ${WORKING_CPP_SOURCES}  ${WORKING_C_SOURCES})

# create the target
add_executable (ags_blosc_decompress ${WORKING_SOURCES})
target_link_libraries (ags_blosc_decompress  ${AGS_EXAMPLE_CPP_LIB_LIBRARIES} ${CBLOSC_LIBRARIES} 
                                           ${Boost_LIBRARIES} )

# install the target
install (TARGETS  ags_blosc_decompress  
         DESTINATION  bin
         PERMISSIONS  OWNER_EXECUTE  OWNER_READ  OWNER_WRITE)
