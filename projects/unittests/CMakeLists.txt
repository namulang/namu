CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding unittests...")
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
add_definitions(-DBUILD_TARGET_TESTER)
add_definitions(-DWRD_TAG="unittests")
#       define libraries:
set(dependencies independentor file-manipulator logger preferencer world)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_executable(unittests ${sources})
target_link_libraries(unittests ${dependencies})
add_dependencies(unittests ${dependencies})
