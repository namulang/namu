CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(moduleName "core")
message("building ${moduleName}...")

message("\tconfigure_files...")
set(defCandidates "__${moduleName}=1")
foreach(def ${defCandidates})
    message("\tadd define ${def}")
    set(defines ${defines} -D${def})
endforeach(def)
add_definitions(${defines})

find_package(BISON)
find_package(FLEX)

set(PARSER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/worker/bison)
set(BISON_COMPILE_FLAGS "-l --feature=diagnostics-show-caret --warnings --color")
set(FLEX_COMPILE_FLAGS "-L --header-file=${PARSER_SRC_DIR}/lowscanner.hpp")

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(BISON_REPORT_FILENAME "bisonReport")
    set(BISON_COMPILE_FLAGS "${BISON_COMPILE_FLAGS} --verbose --report=all --debug --graph=${PARSER_SRC_DIR}/${BISON_REPORT_FILENAME}.gv")
endif (${CMAKE_BUILD_TYPE} STREQUAL Debug)

message("\tbison ${BISON_COMPILE_FLAGS}")

bison_target(lowparser ${PARSER_SRC_DIR}/lowparser.y ${PARSER_SRC_DIR}/lowparser.cpp COMPILE_FLAGS ${BISON_COMPILE_FLAGS})
flex_target(lowscanner ${PARSER_SRC_DIR}/lowscanner.l ${PARSER_SRC_DIR}/lowscanner.cpp COMPILE_FLAGS ${FLEX_COMPILE_FLAGS})
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
    message("\tembeding ${e}")
endforeach(e)
set(dependencies ${dependencies} seedling)
IF(NOT CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(dependencies ${dependencies} dl) # dynamic linking lib of posix compatiables.
ENDIF(NOT CMAKE_SYSTEM_NAME STREQUAL Windows)
foreach(e ${dependencies})
    message("\tlinking ${e}")
endforeach(e)


#  execute:
IF(EMSCRIPTEN)
    add_library(${moduleName} ${sources})
ELSE(EMSCRIPTEN)
    add_library(${moduleName} SHARED ${sources})
    install(TARGETS ${moduleName} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib PERMISSIONS
        OWNER_WRITE OWNER_READ OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE)
ENDIF(EMSCRIPTEN)
set_target_properties(${moduleName} PROPERTIES SUFFIX ".${NM_LIBRARY_EXTENSION}")
target_link_libraries(${moduleName} ${dependencies})

#       let MSVC follow macro expansion of standard:
if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))
    target_compile_options(${moduleName} PUBLIC "/Zc:preprocessor")
endif()
