add_library(intcode SHARED
    intcode.cpp
)

target_include_directories(intcode
    PUBLIC .
)

target_compile_features(intcode
    PUBLIC cxx_std_11
    PRIVATE cxx_std_17
)

add_executable(test-intcode
    intcode.test.cpp
)

target_link_libraries(test-intcode
    intcode
    Catch2::Catch2
)

add_test(IntcodeTests test-intcode)
