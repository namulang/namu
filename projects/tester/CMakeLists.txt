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
set(dependencies "searcher")
foreach(e ${dependencies})
    set(libraries "${libraries} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${e}.${WORLD_LIBRARY_EXTENSION}")
    message("\t\tlinking ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib${e}.${WORLD_LIBRARY_EXTENSION}")
endforeach(e)
string(STRIP ${libraries} libraries) # remove trailing whitespace

add_executable(tester ${sources})
target_link_libraries(tester ${libraries})
add_dependencies(tester ${dependencies})