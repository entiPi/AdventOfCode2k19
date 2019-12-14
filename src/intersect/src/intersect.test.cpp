#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <intersect/intersect.hpp>


using namespace intersect;

namespace intersect {

std::ostream& operator<<(std::ostream& os, point const& p) {
    return os << p.str();
}

}


TEST_CASE("move") {
    SECTION("valid") {
        REQUIRE_NOTHROW(move{"U0"});
        REQUIRE_NOTHROW(move{"D0"});
        REQUIRE_NOTHROW(move{"L0"});
        REQUIRE_NOTHROW(move{"R0"});
    }

    SECTION("invalid") {
        REQUIRE_THROWS_AS(move{"X0"}, invalid_direction);
        REQUIRE_THROWS_AS(move{"U-1"}, invalid_distance);
        REQUIRE_THROWS_AS(move{"U1x"}, invalid_distance);
        REQUIRE_THROWS(move{"xU1"});
    }
}

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

        SECTION("operator +=") {
            point pt{0,0};
            pt += move("U2");
            REQUIRE(point{0,2} == pt);
        }
    }
}

TEST_CASE("lines") {
    using Catch::Matchers::Equals;

    SECTION("from ctor") {
        line step{point{1,1}, direction::LEFT};
        REQUIRE(point{1,1} == *step++);
        REQUIRE(point{0,1} == *step++);
        REQUIRE(point{-1,1} == *step);
    }

    SECTION("up") {
        auto step = point{0,0}.move_towards(point{0,1});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{0,1} == *step);
    }

    SECTION("down") {
        auto step = point{0,0}.move_towards(point{0,-1});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{0,-1} == *step);
    }

    SECTION("right") {
        auto step = point{0,0}.move_towards(point{1,0});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{1,0} == *step);
    }

    SECTION("left") {
        auto step = point{0,0}.move_towards(point{-1,0});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{-1,0} == *step);
    }

    SECTION("long line") {
        auto step = point{1,1}.move_towards(point{1,-5});
        REQUIRE(point{1,1} == *step++);
        REQUIRE(point{1,0} == *step++);
        REQUIRE(point{1,-1} == *step++);
        REQUIRE(point{1,-2} == *step++);
        REQUIRE(point{1,-3} == *step++);
        REQUIRE(point{1,-4} == *step++);
        REQUIRE(point{1,-5} == *step);
    }
}

TEST_CASE("paths") {
    SECTION("straight path") {
        auto step = path{point{0,0}}.then(move{"D1"});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{0,-1} == *step);
    }

    SECTION("around a corner") {
        auto step = path{point{0,0}}.then(move{"U1"}).then(move{"R1"});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{0,1} == *step++);
        REQUIRE(point{1,1} == *step);
    }

    SECTION("move-ctor") {
        auto step = path{point{0,0}}.then(move{"U1"}).then(move{"D1"});
        REQUIRE(point{0,0} == *step++);
        REQUIRE(point{0,1} == *step++);
        REQUIRE(point{0,0} == *step);
    }
}

