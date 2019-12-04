add_library(intcode SHARED
    src/intcode.cpp
)

target_include_directories(intcode
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(intcode
    PRIVATE
        -pedantic-errors
        -Wall
        -Wextra
)

target_compile_features(intcode
    PUBLIC cxx_std_11
    PRIVATE cxx_std_17
)

add_executable(test-intcode
    src/intcode.test.cpp
)

target_link_libraries(test-intcode
    intcode
    Catch2::Catch2
)

add_test(IntcodeTests test-intcode)
