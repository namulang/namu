CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding logger...")
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
add_definitions(-DBUILD_TARGET_LOGGER)
#       define libraries:
set(dependencies independentor file-manipulator)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_library(logger SHARED ${sources})
set_target_properties(logger PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
target_link_libraries(logger ${dependencies})