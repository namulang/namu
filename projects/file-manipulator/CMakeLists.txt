CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding file-manipulator...")
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
add_definitions(-DBUILD_TARGET_FILE_MANIPULATOR)
#       define libraries:
set(dependencies independentor)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_library(file-manipulator SHARED ${sources})
target_link_libraries(file-manipulator ${dependencies})
set_target_properties(file-manipulator PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")