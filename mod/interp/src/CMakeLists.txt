CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding ${moduleName}...")
message("\t\tconfigure_files...")

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
set(dependencies indep clog memlite meta)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#  execute:
add_library(${moduleName} SHARED ${sources})
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
target_link_libraries(${moduleName} ${dependencies})
