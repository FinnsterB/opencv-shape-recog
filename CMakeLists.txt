cmake_minimum_required(VERSION 3.5)
project( ShapeRecog )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( shapeRecogCMake Main.cpp Parser.cpp Parser.h SpecFinder.cpp SpecFinder.h Specification.cpp Specification.h)
target_link_libraries( shapeRecogCMake ${OpenCV_LIBS} )
