#include <catch2/catch.hpp>
#include <intersect/point.hpp>

using namespace intersect;

TEST_CASE("point") {
    SECTION("compare equal") {
        REQUIRE(point{0,0} == point{0,0});
        REQUIRE(point{1,0} == point{1,0});
        REQUIRE(point{-1,0} == point{-1,0});
        REQUIRE(point{0,1} == point{0,1});
        REQUIRE(point{0,-1} == point{0,-1});
        REQUIRE(point{2,-3} == point{2,-3});
        REQUIRE_FALSE(point{1,0} == point{0,1});
    }

    SECTION("compare not-equal") {
        REQUIRE(point{0,0} != point{0,1});
        REQUIRE(point{0,0} != point{1,0});
        REQUIRE(point{1,0} != point{0,1});
        REQUIRE(point{2,0} != point{3,0});
    }

    SECTION("calculating distance") {
        REQUIRE(point{0,0}.distance_to({1,0}) == 1);
        REQUIRE(point{0,0}.distance_to({0,1}) == 1);
        REQUIRE(point{0,0}.distance_to({1,1}) == 2);
        REQUIRE(point{1,1}.distance_to({2,1}) == 1);
        REQUIRE(point{1,1}.distance_to({2,2}) == 2);
        REQUIRE(point{2,2}.distance_to({1,1}) == 2);
    }
}

