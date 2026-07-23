add_executable(package
    main.cpp
    app.cpp
    app.h
    package.cpp
    package.h
    path.cpp
    path.h
)

target_include_directories(package PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(package PRIVATE
    xfc
    lz4
    fnv
)
