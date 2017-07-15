CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding file-manipulator...")

file(GLOB_RECURSE sources
    "*.hpp"
    "*.h"
    "*.c"
    "*.inl"
    "*.cpp"
)

add_definitions(-DBUILD_TARGET_FILE_MANIPULATOR)

foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)

add_library(file-manipulator SHARED ${sources})
set_target_properties(file-manipulator PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")