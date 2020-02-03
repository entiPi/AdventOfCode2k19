#include <catch2/catch.hpp>
#include <intersect/line.hpp>


using namespace intersect;

TEST_CASE("move") {

    SECTION("parsing") {

        SECTION("valid") {

            SECTION("nothrow") {
                REQUIRE_NOTHROW(move{"U0"});
                REQUIRE_NOTHROW(move{"D0"});
                REQUIRE_NOTHROW(move{"L0"});
                REQUIRE_NOTHROW(move{"R0"});
            }

            SECTION("parse direction") {
                REQUIRE(move{"U0"}.direction() == dir::UP);
                REQUIRE(move{"D0"}.direction() == dir::DOWN);
                REQUIRE(move{"L0"}.direction() == dir::LEFT);
                REQUIRE(move{"R0"}.direction() == dir::RIGHT);
            }

            SECTION("parse length") {
                REQUIRE(move{"U0"}.length() == 0);
                REQUIRE(move{"U1"}.length() == 1);
                REQUIRE(move{"U20"}.length() == 20);
                REQUIRE(move{"U123"}.length() == 123);
                REQUIRE(move{"D1"}.length() == 1);
                REQUIRE(move{"L1"}.length() == 1);
                REQUIRE(move{"R1"}.length() == 1);
            }
        }

        SECTION("invalid") {
            REQUIRE_THROWS_AS(move{"X0"}, invalid_direction);
            REQUIRE_THROWS_AS(move{"U-1"}, invalid_distance);
            REQUIRE_THROWS_AS(move{"U1x"}, invalid_distance);
            REQUIRE_THROWS(move{"xU1"});
        }
    }

    SECTION("moving points") {

        SECTION("operator +") {
            REQUIRE(point{0,0} + move{"U0"} == point{0,0});
            REQUIRE(point{0,0} + move{"D0"} == point{0,0});
            REQUIRE(point{0,0} + move{"L0"} == point{0,0});
            REQUIRE(point{0,0} + move{"R0"} == point{0,0});
            REQUIRE(point{0,0} + move{"U1"} == point{0,1});
            REQUIRE(point{0,0} + move{"D1"} == point{0,-1});
            REQUIRE(point{0,0} + move{"L1"} == point{-1,0});
            REQUIRE(point{0,0} + move{"R1"} == point{1,0});
            REQUIRE(point{1,1} + move{"U1"} == point{1,2});
            REQUIRE(point{1,1} + move{"D1"} == point{1,0});
            REQUIRE(point{1,1} + move{"L1"} == point{0,1});
            REQUIRE(point{1,1} + move{"R1"} == point{2,1});
            REQUIRE(point{0,1} + move{"U10"} == point{0,11});
            REQUIRE(point{0,1} + move{"D10"} == point{0,-9});
            REQUIRE(point{1,0} + move{"L10"} == point{-9,0});
            REQUIRE(point{1,0} + move{"R10"} == point{11,0});
        }
    }
}

TEST_CASE("line") {

    SECTION("construction") {

        SECTION("restricted to one dimension") {
            point a{0,0}, b{1,1};
            REQUIRE_THROWS_AS(line(a, b), multiple_dimensions);
        }
    }

    SECTION("can query length") {

        SECTION("from points") {
            REQUIRE(line{{0,0}, point{0,0}}.length() == 0);
            REQUIRE(line{{0,0}, {1,0}}.length() == 1);
            REQUIRE(line{{0,0}, {0,1}}.length() == 1);
            REQUIRE(line{{0,0}, {2,0}}.length() == 2);
            REQUIRE(line{{0,0}, {-1,0}}.length() == 1);
            REQUIRE(line{{0,0}, {0,-1}}.length() == 1);
        }

        SECTION("from move") {
            REQUIRE(line{{0,0}, move{"U0"}}.length() == 0);
            REQUIRE(line{{0,0}, move{"U1"}}.length() == 1);
            REQUIRE(line{{0,0}, move{"D2"}}.length() == 2);
        }
    }

    SECTION("can query direction") {

        SECTION("from points") {
            REQUIRE(line{{0,0}, {1,0}}.direction() == dir::RIGHT);
            REQUIRE(line{{0,0}, {0,1}}.direction() == dir::UP);
            REQUIRE(line{{0,0}, {-1,0}}.direction() == dir::LEFT);
            REQUIRE(line{{0,0}, {0,-1}}.direction() == dir::DOWN);
            REQUIRE(line{{0,0}, {2,0}}.direction() == dir::RIGHT);
            REQUIRE(line{{0,0}, {0,-2}}.direction() == dir::DOWN);
            REQUIRE(line{{1,1}, {1,0}}.direction() == dir::DOWN);
            REQUIRE(line{{1,1}, {0,1}}.direction() == dir::LEFT);
            REQUIRE(line{{1,1}, {2,1}}.direction() == dir::RIGHT);
            REQUIRE(line{{1,1}, {1,2}}.direction() == dir::UP);
        }

        SECTION("from move") {
            REQUIRE(line{{0,0}, move{"U7"}}.direction() == dir::UP);
            REQUIRE(line{{0,0}, move{"D1"}}.direction() == dir::DOWN);
            REQUIRE(line{{0,0}, move{"L2"}}.direction() == dir::LEFT);
            REQUIRE(line{{0,0}, move{"R2"}}.direction() == dir::RIGHT);
        }
    }

    SECTION("can measure distance to point") {

        line const l{{0,0}, {0,10}};

        SECTION("part of line") {
            REQUIRE(l.distance_to(point{0,0}).value() == 0);
            REQUIRE(l.distance_to(point{0,1}).value() == 1);
            REQUIRE(!l.distance_to(point{1,10}).has_value());
        }
    }

}
