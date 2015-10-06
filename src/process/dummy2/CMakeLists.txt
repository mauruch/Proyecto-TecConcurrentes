
include_directories(.
../../lib
)

add_executable(dummy2 dummy2.cpp)

add_dependencies(dummy2 lib)

target_link_libraries(dummy2 lib)