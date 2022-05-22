CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("building ${moduleName}...")
set(moduleName "swrd")
set(defCandidates "WRD_TAG=\"${moduleName}\"")
foreach(def ${defCandidates})
    message("\tadd define ${def}")
    set(defines ${defines} -D${def})
endforeach(def)
add_definitions(${defines})

message("\tconfigure_files...")

find_package(BISON)
find_package(FLEX)

bison_target(swrdParser parser/swrdParser.y ${CMAKE_CURRENT_SOURCE_DIR}/parser/swrdParser.cpp COMPILE_FLAGS "-l")
flex_target(swrdScanner parser/swrdScanner.l ${CMAKE_CURRENT_SOURCE_DIR}/parser/swrdScanner.cpp COMPILE_FLAGS "-L")
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
    message("\tembeding ${e}")
endforeach(e)
set(dependencies ${dependencies} memlite)
foreach(e ${dependencies})
    message("\tlinking ${e}")
endforeach(e)

#  execute:
add_library(${moduleName} SHARED ${sources})
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${WRD_LIBRARY_EXTENSION}")
target_link_libraries(${moduleName} ${dependencies})
