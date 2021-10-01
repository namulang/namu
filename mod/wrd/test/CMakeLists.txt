CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

set(testName ${moduleName}Test)
find_library(pathGtest
    NAMES libgtest.a
    REQUIRED)
set(dependencies ${dependencies} ${moduleName} ${pathGtest})
foreach(d ${dependencies})
    set(libraries ${libraries} PUBLIC ${d})
endforeach(d)

message("\ttest ${testName}... dependents to ${dependencies}")

#      define sources:
file(GLOB_RECURSE sources
    "*.cc"
)

add_executable(${testName} ${sources})

find_package(Threads REQUIRED)
target_link_libraries(${testName} ${libraries}
    PRIVATE Threads::Threads)

add_dependencies(${testName} ${moduleName})

add_subdirectory(samplePack)
