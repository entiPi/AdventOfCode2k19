add_library(module SHARED
    src/module.cpp
)

target_include_directories(module
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(module
    PRIVATE
        -pedantic-errors
        -Wall
        -Wextra
)

target_compile_features(module
    PRIVATE
      cxx_std_14
)

add_executable(test-module
    src/module.test.cpp
)

target_link_libraries(test-module
    module
    Catch2::Catch2
)

add_test(ModuleTests test-module)
