CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

message("building ${CMAKE_CURRENT_SOURCE_DIR}...")

#   In fact, this lists shows like REVERSED stack diagram.
#   it depicts the exactly dependencies for which program should be come first.
#   The faster, The lower on Stack diagram.
add_subdirectory(independentor)
add_subdirectory(file-manipulator)
add_subdirectory(logger)
add_subdirectory(tester)