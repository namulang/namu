CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding preferencer...")

#   generate parser:
set(javacc "java")
set(javacc_output "${CMAKE_CURRENT_SOURCE_DIR}/parser/generated")
set(javacc_flags "-classpath ${CMAKE_BINARY_DIR}/javacc.jar javacc -OUTPUT_DIRECTORY:${javacc_output}")
message("\t\tgenerating preferencer.jjt")
exec_program(${javacc} 
    ARGS ${javacc_flags} ${CMAKE_CURRENT_SOURCE_DIR}/parser/preferencer.jjt
)

#   defines:
#       define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
    "*.cc"
)
#           logging sources:
foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)
#       define predefinitions:
add_definitions(-DBUILD_TARGET_PREFERENCER)
add_definitions(-DWRD_TAG="preferencer")
#       define libraries:
set(dependencies independentor file-manipulator logger)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_library(preferencer SHARED ${sources})
target_link_libraries(preferencer ${dependencies})
set_target_properties(preferencer PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
