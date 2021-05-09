CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("building ${CMAKE_CURRENT_SOURCE_DIR}...")

set(moduleName "swrd")
set(defCandidates "WRD_TAG=\"${moduleName}\"")
foreach(def ${defCandidates})
    message("\tadd define ${def}")
    set(defines ${defines} -D${def})
endforeach(def)
add_definitions(${defines})

#   In fact, this lists shows like REVERSED stack diagram.
#   it depicts the exactly dependencies for which program should be come first.
#   The faster, The lower on Stack diagram.
add_subdirectory(src)
add_subdirectory(test)
