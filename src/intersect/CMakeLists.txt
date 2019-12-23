add_library(intersect SHARED
    src/direction.cpp
    src/point.cpp
    src/line.cpp
    src/path.cpp
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
        -Werror
        -pedantic
        -Wall
        -Wextra
)

target_compile_features(intersect
    PUBLIC cxx_std_17
)

target_link_libraries(intersect
    PUBLIC
        algorithm
)

add_executable(test-intersect
    src/main.test.cpp
    src/point.test.cpp
    src/line.test.cpp
    src/path.test.cpp
    src/intersect.test.cpp
)

target_link_libraries(test-intersect
    intersect
    Catch2::Catch2
)

add_test(intersectTests test-intersect)
