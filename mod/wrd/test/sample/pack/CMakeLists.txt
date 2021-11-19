CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(packName "samplePack")
set(packOutDir "${WRD_PACK_OUTPUT_DIRECTORY}/${packName}")
set(dependencies ${dependencies} ${moduleName} ${pathGtest})

foreach(d ${dependencies})
    set(libraries ${libraries} PUBLIC ${d})
endforeach(d)

configure_file("manifest.swrd" "${packOutDir}/manifest.swrd")

#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)

message("put module to ${WRD_PACK_OUTPUT_DIRECTORY}")

add_library(${packName} SHARED ${sources})
set_target_properties(${packName} PROPERTIES SUFFIX ".${WRD_PACK_EXTENSION}")
set_target_properties(${packName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${packOutDir}")
target_link_libraries(${packName} ${dependencies})

add_dependencies(${packName} ${moduleName})
