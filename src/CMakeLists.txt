add_library(module SHARED
    module.cpp
)

add_executable(fuel-calculator
    fuel_calculator.cpp
)

target_link_libraries(fuel-calculator
    module
)

add_executable(gravity-assist
    gravity_assist.cpp
)

target_link_libraries(gravity-assist
    intcode
)

add_executable(test-module
    module.test.cpp
)

target_link_libraries(test-module
    module
    Catch2::Catch2
)

add_test(ModuleTests test-module)


add_subdirectory(intcode)
