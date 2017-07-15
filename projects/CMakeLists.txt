CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("building ${CMAKE_CURRENT_SOURCE_DIR}...")
add_subdirectory(macro)
add_subdirectory(file-manipulator)
add_subdirectory(tester)