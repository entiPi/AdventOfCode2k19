add_library(intersect SHARED
    src/intersect.cpp
)

target_include_directories(intersect
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(intersect
    PRIVATE
        -pedantic-errors
        -Wall
        -Wextra
)

target_compile_features(intersect
    PUBLIC cxx_std_17
)

add_executable(test-intersect
    src/intersect.test.cpp
)

target_link_libraries(test-intersect
    intersect
    Catch2::Catch2
)

add_test(intersectTests test-intersect)
