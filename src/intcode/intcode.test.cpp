#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "intcode.hpp"

using namespace std;
using namespace intcode;


TEST_CASE("intcode") {
    REQUIRE(compute(program{1,0,0,0,99}) == output{2,0,0,0,99});
    REQUIRE(compute(program{2,3,0,3,99}) == output{2,3,0,6,99});
    REQUIRE(compute(program{2,4,4,5,99,0}) == output{2,4,4,5,99,9801});
    REQUIRE(compute(program{1,1,1,4,99,5,6,0,99}) == output{30,1,1,4,2,5,6,0,99});
    REQUIRE(compute(program{1,9,10,3,2,3,11,0,99,30,40,50}) == output{3500,9,10,70,2,3,11,0,99,30,40,50});
}
