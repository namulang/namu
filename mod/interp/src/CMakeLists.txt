CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding ${moduleName}...")
message("\t\tconfigure_files...")

find_package(BISON)
find_package(FLEX)

bison_target(wrdParser parser/wrdParser.y ${CMAKE_CURRENT_SOURCE_DIR}/parser/wrdParser.cpp COMPILE_FLAGS "-l")
flex_target(wrdScanner parser/wrdScanner.l ${CMAKE_CURRENT_SOURCE_DIR}/parser/wrdScanner.cpp COMPILE_FLAGS "-L")
add_flex_bison_dependency(wrdScanner wrdParser)

#  defines:
#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)
foreach(file ${BISON_wrdParser_OUTPUTS})
    list(APPEND sources ${file})
endforeach(file)

foreach(file ${FLEX_wrdScanner_OUTPUTS})
    list(APPEND sources ${file})
endforeach(file)

#          logging sources:
foreach(e ${sources})
    message("\t\tembeding ${e}")
endforeach(e)
set(dependencies indep clog memlite meta swrd dl)
foreach(e ${dependencies})
    message("\t\tlinking ${e}")
endforeach(e)


#  execute:
add_library(${moduleName} SHARED ${sources})
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${WRD_LIBRARY_EXTENSION}")
target_link_libraries(${moduleName} ${dependencies})
