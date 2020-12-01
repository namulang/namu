CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding ${moduleName}...")
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
)
#          logging sources:
foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)
#      define predefinitions:
add_definitions(-DBUILD_TARGET_INDEPENDENTOR)


#  execute:
add_library(${moduleName} SHARED ${sources})
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
