CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

message("\tcopy .namu tc files into ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
file(COPY example DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(pack)
