CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding filesystem...")

file(GLOB_RECURSE sources
    "*.hpp"
    "*.h"
    "*.c"
    "*.inl"
    "*.cpp"
)

add_definitions(-DBUILD_TARGET_FILESYSTEM)

foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)

add_library(filesystem SHARED ${sources})