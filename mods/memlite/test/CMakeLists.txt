CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(testName ${moduleName}Test)
find_library(pathGtest
    NAMES libgtest.a
    REQUIRED)
set(dependencies ${moduleName} ${pathGtest})

message("test ${testName}... dependents to ${dependencies}")

#      define sources:
file(GLOB_RECURSE sources
    "*.cc"
)

add_executable(${testName} ${sources})
target_link_libraries(${testName} ${dependencies})
add_dependencies(${testName} ${moduleName})
