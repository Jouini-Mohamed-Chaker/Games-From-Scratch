cmake_minimum_required(VERSION 3.10)
project(Game)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to Raylib installation directory
# Assuming Raylib is installed in a directory named 'raylib' in the root of your project
set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/includes/raylib-5.0_linux_amd64")

# Add Raylib headers
include_directories(${RAYLIB_DIR}/include)

# Add your GameIncludes directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/includes/GameIncludes)

# Add Raylib static library
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES
    IMPORTED_LOCATION ${RAYLIB_DIR}/lib/libraylib.a
)

# Add the executable
add_executable(Game src/main.cpp)

# Link Raylib library statically and also add required system libraries
target_link_libraries(Game raylib GL m pthread dl rt X11)
