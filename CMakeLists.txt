cmake_minimum_required(VERSION 3.5)
project( ShapeRecog )

# Set the C++ standard (optional)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable debugging for Valgrind
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Function to enable warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC/Clang warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion) 
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # MSVC warnings
    add_compile_options(/W4)
endif()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( shapeRecogCMake Main.cpp Parser.cpp Parser.h SpecFinder.cpp SpecFinder.h Specification.cpp Specification.h)
target_link_libraries( shapeRecogCMake ${OpenCV_LIBS} )
