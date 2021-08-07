CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("\tbuilding ${moduleName}...")
message("\t\tconfigure_files...")

find_package(BISON)
find_package(FLEX)

set(PARSER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/parser)
set(BISON_COMPILE_FLAGS "-l --feature=diagnostics-show-caret --warnings --color")

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(BISON_REPORT_FILENAME "bisonReport")
    set(BISON_COMPILE_FLAGS "${BISON_COMPILE_FLAGS} --verbose --report=all --debug --graph=${PARSER_SRC_DIR}/${BISON_REPORT_FILENAME}.gv")
endif (${CMAKE_BUILD_TYPE} STREQUAL Debug)

message("\t\tbison ${BISON_COMPILE_FLAGS}")

bison_target(lowparser parser/lowparser.y ${PARSER_SRC_DIR}/lowparser.cpp COMPILE_FLAGS ${BISON_COMPILE_FLAGS})
flex_target(lowscanner parser/lowscanner.l ${PARSER_SRC_DIR}/lowscanner.cpp COMPILE_FLAGS "-L --header-file=${PARSER_SRC_DIR}/lowscanner.hpp")
add_flex_bison_dependency(lowscanner lowparser)

#  defines:
#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)
foreach(file ${BISON_lowparser_OUTPUTS})
    list(APPEND sources ${file})
endforeach(file)

foreach(file ${FLEX_lowscanner_OUTPUTS})
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
