add_executable(package
    main.cpp
    app.cpp
    app.h
)

target_include_directories(package PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(package PRIVATE xfc)
