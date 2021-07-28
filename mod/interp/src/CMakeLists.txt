CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding ${moduleName}...")
message("\t\tconfigure_files...")

find_package(BISON)
find_package(FLEX)

set(PARSER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/parser)
set(BISON_COMPILE_FLAGS "-l")

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(BISON_REPORT_FILENAME "bisonReport")
    set(BISON_COMPILE_FLAGS "${BISON_COMPILE_FLAGS} --graph=${PARSER_SRC_DIR}/${BISON_REPORT_FILENAME}.gv")
endif (${CMAKE_BUILD_TYPE} STREQUAL Debug)

message("\t\tbison ${BISON_COMPILE_FLAGS}")

bison_target(wrdParser parser/wrdParser.y ${PARSER_SRC_DIR}/wrdParser.cpp COMPILE_FLAGS ${BISON_COMPILE_FLAGS})
flex_target(wrdScanner parser/wrdScanner.l ${PARSER_SRC_DIR}/wrdScanner.cpp COMPILE_FLAGS "-L --header-file=${PARSER_SRC_DIR}/wrdScanner.hpp")
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

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_custom_command(
        TARGET ${moduleName}
        POST_BUILD
        COMMENT "bison will generate a report for generated parser by bison."
        COMMAND dot -Tjpg ${PARSER_SRC_DIR}/${BISON_REPORT_FILENAME}.gv
            -o ${PARSER_SRC_DIR}/${BISON_REPORT_FILENAME}.jpg
            DEPENDS ${PARSER_SRC_DIR}/${BISON_REPORT_FILENAME}.gv
        VERBATIM)
endif (${CMAKE_BUILD_TYPE} STREQUAL Debug)
