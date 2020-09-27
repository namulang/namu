CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding world...")
#   defines:
#       define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)
#           logging sources:
foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)
#       define predefinitions:
add_definitions(-DBUILD_TARGET_WORLD)
add_definitions(-DWRD_TAG="world")
#       define libraries:
set(dependencies independentor file-manipulator logger preferencer)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_library(world SHARED ${sources})
target_link_libraries(world ${dependencies})
set_target_properties(world PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
