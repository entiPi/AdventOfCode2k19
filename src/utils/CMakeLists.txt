add_library(utils STATIC
    src/timer.cpp
)

target_include_directories(utils
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(utils
    PRIVATE
        -Werror
        -pedantic
        -Wall
        -Wextra
)

target_compile_features(utils
    PUBLIC cxx_std_17
)

