CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding ${moduleName}...")
message("\t\tconfigure_files...")

find_package(BISON)
find_package(FLEX)

bison_target(swrdParser parser/swrd.y parser/swrdParser.cpp COMPILE_FLAGS "-l")
flex_target(swrdScanner parser/swrd.l parser/swrdScanner.cpp COMPILE_FLAGS "-L")
add_flex_bison_dependency(swrdScanner swrdParser)

#  defines:
#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)

foreach(file ${BISON_swrdParser_OUTPUTS})
    list(APPEND sources ${file})
endforeach(file)

foreach(file ${FLEX_swrdScanner_OUTPUTS})
    list(APPEND sources ${file})
endforeach(file)

#          logging sources:
foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)
set(dependencies memlite)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)

#  execute:
add_library(${moduleName} SHARED ${sources})
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${WORLD_LIBRARY_EXTENSION}")
target_link_libraries(${moduleName} ${dependencies})
