
include_directories(.
../../lib
)

add_executable(dummy dummy.cpp)

add_dependencies(dummy lib)

target_link_libraries(dummy lib)
