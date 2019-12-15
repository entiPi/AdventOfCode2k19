find_package(Boost 1.59 REQUIRED COMPONENTS coroutine)

add_library(algorithm INTERFACE)

target_include_directories(algorithm
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(algorithm
    INTERFACE
        cxx_std_14
)

target_link_libraries(algorithm
    INTERFACE
        Boost::coroutine  # actually coroutine2 but it's the same target
)

add_executable(test-algorithm
    src/cartesian_product.test.cpp
)

target_compile_features(test-algorithm
    PRIVATE
        cxx_std_17
)

target_compile_options(test-algorithm
    PRIVATE
        -pedantic-errors
        -Wall
        -Wextra
)

target_link_libraries(test-algorithm
    PRIVATE
        algorithm
        Catch2::Catch2
)

add_test(AlgorithmTest test-algorithm)
