cmake_minimum_required (VERSION 2.6)
project (SpaceRank)

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.5")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pg")

set(PROJECT_SOURCE_DIR src)
set(PROJECT_BINARY_DIR bin)

# Add version info. to src/Config.h
set (SpaceRank_VERSION_MAJOR 0)
set (SpaceRank_VERSION_MINOR 1)
configure_file (
    "${PROJECT_SOURCE_DIR}/Config.h.in"
    "${PROJECT_BINARY_DIR}/Config.h"
    )
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
file(GLOB_RECURSE SpaceRank_SOURCES "src/*.cpp")
file(GLOB_RECURSE SpaceRank_HEADERS "src/*.h")

set (SpaceRank_INCLUDE_DIRS "")
foreach (_headerFile ${SpaceRank_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND SpaceRank_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES SpaceRank_INCLUDE_DIRS)

include_directories(${SpaceRank_INCLUDE_DIRS})

set (EXECUTABLE_NAME "spacerank")
add_executable(spacerank ${SpaceRank_SOURCES})


# Find and add libraries
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# Find any version 2.X of SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
# Find Box2D
find_package(Box2D REQUIRED)
if(BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${SpaceRank_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SpaceRank_VERSION_MINOR}")
include (CPack)
