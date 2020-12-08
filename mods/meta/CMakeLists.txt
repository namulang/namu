CMAKE_MINIMUM_REQUIRED(VERSION 2.6)


set(moduleName "meta")
message("building ${CMAKE_CURRENT_SOURCE_DIR}...")

#   In fact, this lists shows like REVERSED stack diagram.
#   it depicts the exactly dependencies for which program should be come first.
#   The faster, The lower on Stack diagram.
add_subdirectory(src)
add_subdirectory(test)
