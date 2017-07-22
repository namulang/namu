CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding tester...")
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
add_definitions(-DNE_TAG="tester")
#       define libraries:
set(dependencies independentor file-manipulator logger)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_executable(tester ${sources})
target_link_libraries(tester ${dependencies})
add_dependencies(tester ${dependencies})