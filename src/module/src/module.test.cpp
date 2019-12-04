#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <module/module.hpp>

TEST_CASE("calculation of required fuel works", "[module], [fuel]") {
    using module::calculateRequiredFuel;
    REQUIRE(calculateRequiredFuel(12) == 2);
    REQUIRE(calculateRequiredFuel(14) == 2);
    REQUIRE(calculateRequiredFuel(1969) == 966);
    REQUIRE(calculateRequiredFuel(100756) == 50346);
}

TEST_CASE("fuel calculation is capped at zero", "[module], [fuel]") {
    using module::calculateRequiredFuel;
    REQUIRE(calculateRequiredFuel(0) == 0);
    REQUIRE(calculateRequiredFuel(2) == 0);
    REQUIRE(calculateRequiredFuel(-2) == 0);
}
