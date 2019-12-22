add_subdirectory(module)
add_subdirectory(intcode)
add_subdirectory(intersect)
add_subdirectory(algorithm)
add_subdirectory(utils)

add_executable(fuel-calculator
    fuel_calculator.cpp
)

target_link_libraries(fuel-calculator
    module
)

add_executable(gravity-assist
    gravity_assist.cpp
)

target_compile_options(gravity-assist
    PRIVATE
        -pedantic
        -Wall
        -Wextra
)

target_compile_features(gravity-assist
    PRIVATE
        cxx_std_17
)

target_link_libraries(gravity-assist
    intcode
    algorithm
)

