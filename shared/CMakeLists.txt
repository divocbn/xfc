add_library(xfc STATIC
    src/app.cpp
    src/filesystem.cpp
    src/timer.cpp

    include/xfc/app.h
    include/xfc/filesystem.h
    include/xfc/log.h
    include/xfc/numeric.h
    include/xfc/ptr.h
    include/xfc/timer.h
)

target_include_directories(xfc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(xfc PUBLIC fmt::fmt)

target_compile_features(xfc PUBLIC cxx_std_23)
