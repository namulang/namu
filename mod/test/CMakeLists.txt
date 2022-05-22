CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(moduleName "test")
set(dependencies ${dependencies} indep clog memlite meta wrd swrd dl ${pathGtest})

message("building ${moduleName}...")

set(defCandidates "WRD_TAG=\"${moduleName}\"")
foreach(def ${defCandidates})
    message("\tadd define ${def}")
    set(defines ${defines} -D${def})
endforeach(def)
add_definitions(${defines})

find_library(pathGtest
    NAMES gtest
    REQUIRED)
foreach(d ${dependencies})
    set(libraries ${libraries} PUBLIC ${d})
endforeach(d)

message("\tbuilding ${moduleName} dependents to ${dependencies}")

#      define sources:
file(GLOB_RECURSE sources
    "*.cc"
)
#          logging sources:
foreach(e ${sources})
    message("\tembeding ${e}")
endforeach(e)
foreach(e ${dependencies})
    message("\tlinking ${e}")
endforeach(e)

add_executable(${moduleName} ${sources})

find_package(Threads REQUIRED)
target_link_libraries(${moduleName} ${libraries}
    PRIVATE Threads::Threads)

add_subdirectory(bundle)
