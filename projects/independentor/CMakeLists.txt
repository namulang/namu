CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding independentor...")
message("\t\tconfigure_files...")
#   expanding:
file(GLOB_RECURSE configures "*.in")
foreach(e ${configures})
    #   extract output filepath:
    string(FIND ${e} ".in" n REVERSE)
    string(SUBSTRING ${e} 0 ${n} output_path)
    message("\t\texpanding ${output_path}")
    configure_file(${e} ${output_path})
endforeach(e)
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
add_definitions(-DBUILD_TARGET_INDEPENDENTOR)


#   execute:
add_library(independentor SHARED ${sources})
set_target_properties(independentor PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")