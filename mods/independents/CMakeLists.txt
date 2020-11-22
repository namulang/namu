CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding independents...")
message("\t\tconfigure_files...")
#  expanding:
set(configures
	"def/BuildInformation.hpp.in"
)
foreach(e ${configures})
    #  extract output filepath:
    string(FIND ${e} ".in" n REVERSE)
    string(SUBSTRING ${e} 0 ${n} output_path)
	message("\t\texpanding ${CMAKE_CURRENT_SOURCE_DIR}/${output_path}")
	configure_file(${e} ${CMAKE_CURRENT_SOURCE_DIR}/${output_path})
endforeach(e)
#  defines:
#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
    "*.cc"
)
#          logging sources:
foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)
#      define predefinitions:
add_definitions(-DBUILD_TARGET_INDEPENDENTOR)


#  execute:
add_library(independents SHARED ${sources})
set_target_properties(independents PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
