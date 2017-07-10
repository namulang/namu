CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding tester...")

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

#find_library(libsearcher
    #NAME libsearcher
    #HINT "${CMAKE_BINARY_DIR}/build/projects/searcher")
set(LIBRARIES "${CMAKE_BINARY_DIR}/projects/searcher/libsearcher.dll")
message("\n\t\tlibraries are ${LIBRARIES}")

add_executable(tester ${sources})
target_link_libraries(tester ${LIBRARIES})