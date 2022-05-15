CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(moduleName "cli")
set(dependencies indep clog memlite meta wrd swrd dl)

message("building ${moduleName}...")

set(defCandidates "WRD_TAG=\"${moduleName}\"")
foreach(def ${defCandidates})
    message("\tadd define ${def}")
    set(defines ${defines} -D${def})
endforeach(def)
add_definitions(${defines})

foreach(d ${dependencies})
    set(libraries ${libraries} PUBLIC ${d})
endforeach(d)

message("\tbuilding ${moduleName} dependents to ${dependencies}")

#      define sources:
file(GLOB_RECURSE sources
    "*.c"
    "*.cpp"
)
#          logging sources:
foreach(e ${sources})
    message("\tembeding ${e}")
endforeach(e)
foreach(e ${dependencies})
    message("\tlinking ${e}")
endforeach(e)

add_executable(${moduleName} ${sources})
target_link_libraries(${moduleName} ${libraries})
