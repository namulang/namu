CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(testName ${moduleName}Test)
find_library(dependencies
    NAMES libgtest.a
    REQUIRED)


message("test ${testName}...")

#      define sources:
file(GLOB_RECURSE sources
    "*.cc"
)

add_executable(${testName} ${sources})
target_link_libraries(${testName} ${dependencies})

add_dependencies(${testName} ${moduleName})
