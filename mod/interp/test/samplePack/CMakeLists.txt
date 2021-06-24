CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(packName "samplePack")
foreach(d ${dependencies})
	set(libraries ${libraries} PUBLIC ${d})
endforeach(d)

message("\tmake ${packName}... dependents to ${dependencies}")

#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)

message("put module to ${WRD_PACK_OUTPUT_DIRECTORY}")

add_library(${packName} SHARED ${sources})
set_target_properties(${packName} PROPERTIES SUFFIX ".${WRD_PACK_EXTENSION}")
set_target_properties(${packName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${WRD_PACK_OUTPUT_DIRECTORY}")
target_link_libraries(${packName} ${dependencies})

add_dependencies(${packName} ${moduleName})
