CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\n\tbuilding ${moduleName}...")

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
#       define libraries:
set(dependencies indep)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#   execute:
add_library(${moduleName} SHARED ${sources})
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${WRD_LIBRARY_EXTENSION}")
target_link_libraries(${moduleName} ${dependencies})
