#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "module.hpp"

TEST_CASE("calculation of required fuel works", "[module,fuel]") {
    using module::calculateRequiredFuel;
    REQUIRE(calculateRequiredFuel(12) == 2);
    REQUIRE(calculateRequiredFuel(14) == 2);
    REQUIRE(calculateRequiredFuel(1969) == 654);
    REQUIRE(calculateRequiredFuel(100756) == 33583);
}
