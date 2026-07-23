add_subdirectory(fmt EXCLUDE_FROM_ALL)
add_subdirectory(lz4/build/cmake lz4 EXCLUDE_FROM_ALL)

add_library(fnv INTERFACE)

target_include_directories(fnv INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/fnv
)
