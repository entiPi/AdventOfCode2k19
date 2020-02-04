#include <catch2/catch.hpp>
#include <intersect/intersect.hpp>


using namespace intersect;

TEST_CASE("line intersection") {
    using P = point;
    using L = line;
    using Vec = std::vector<point>;
    using Catch::Matchers::UnorderedEquals;

    SECTION("parallel lines") {

        SECTION("offset to the side") {

            SECTION("horizontal offset") {
                REQUIRE(intersection(L{P{0,0}, P{0,3}}, L{P{1,0}, P{1,3}}).empty());
                REQUIRE(intersection(L{P{0,3}, P{0,0}}, L{P{1,0}, P{1,3}}).empty());
            }

            SECTION("vertical offset") {
                REQUIRE(intersection(L{P{0,0}, P{3,0}}, L{P{0,1}, P{3,1}}).empty());
                REQUIRE(intersection(L{P{3,0}, P{0,0}}, L{P{0,1}, P{3,1}}).empty());
            }
        }

        SECTION("in one line") {

            SECTION("with gap") {
                REQUIRE(intersection(L{P{0,0}, P{1,0}}, L{P{0,2}, P{0,4}}).empty());
                REQUIRE(intersection(L{P{0,0}, P{0,1}}, L{P{2,0}, P{4,0}}).empty());
            }

            SECTION("touching") {
                REQUIRE_THAT(intersection(L{P{0,0}, P{1,0}}, L{P{1,0}, P{4,0}}), UnorderedEquals(Vec{{1,0}}));
                REQUIRE_THAT(intersection(L{P{0,0}, P{0,1}}, L{P{0,1}, P{0,4}}), UnorderedEquals(Vec{{0,1}}));
            }

            SECTION("overlaping") {
                REQUIRE_THAT(intersection(L{P{0,0}, P{2,0}}, L{P{1,0}, P{4,0}}), UnorderedEquals(Vec{{1,0}, {2,0}}));
                REQUIRE_THAT(intersection(L{P{0,0}, P{0,2}}, L{P{0,1}, P{0,4}}), UnorderedEquals(Vec{{0,1}, {0,2}}));
            }

            SECTION("enclosed") {
                REQUIRE_THAT(intersection(L{P{0,0}, P{4,0}}, L{P{1,0}, P{2,0}}), UnorderedEquals(Vec{{1,0}, {2,0}}));
                REQUIRE_THAT(intersection(L{P{0,0}, P{0,4}}, L{P{0,1}, P{0,2}}), UnorderedEquals(Vec{{0,1}, {0,2}}));
            }
        }
    }

    SECTION("orthogonal lines") {

        SECTION("with gap") {
            REQUIRE(intersection(L{P{0,0}, P{3,0}}, L{P{1,1}, P{1,3}}).empty());
        }

        SECTION("touching") {

            SECTION("at corner") {
                REQUIRE_THAT(intersection(L{P{0,0}, P{3,0}}, L{P{3,0}, P{3,2}}), UnorderedEquals(Vec{{3,0}}));
                REQUIRE_THAT(intersection(L{P{3,0}, P{0,0}}, L{P{3,2}, P{3,0}}), UnorderedEquals(Vec{{3,0}}));
            }

            SECTION("in the middle") {
                REQUIRE_THAT(intersection(L{P{0,0}, P{3,0}}, L{P{2,0}, P{2,1}}), UnorderedEquals(Vec{{2,0}}));
                REQUIRE_THAT(intersection(L{P{0,1}, P{3,1}}, L{P{3,4}, P{3,0}}), UnorderedEquals(Vec{{3,1}}));
                REQUIRE_THAT(intersection(L{P{1,3}, P{1,5}}, L{P{0,5}, P{3,5}}), UnorderedEquals(Vec{{1,5}}));
            }
        }

        SECTION("overlaping") {
            REQUIRE_THAT(intersection(L{P{0,1}, P{3,1}}, L{P{2,0}, P{2,2}}), UnorderedEquals(Vec{{2,1}}));
            REQUIRE_THAT(intersection(L{P{1,0}, P{1,3}}, L{P{0,2}, P{2,2}}), UnorderedEquals(Vec{{1,2}}));
        }
    }
}


TEST_CASE("path intersections") {
    using Catch::Matchers::Equals;
    using Catch::Matchers::UnorderedEquals;
    using Vec = std::vector<point>;

    SECTION("no intersection") {
        auto first_leg = path{point{1,0}}.then(move{"U3"});
        auto second_leg = path{point{-1,0}}.then(move{"D3"});
        REQUIRE(intersections(first_leg, second_leg).empty());
    }

    SECTION("single intersection") {
        auto first_leg = path{point{2,0}}.then(move{"U3"});
        auto second_leg = path{point{0,2}}.then(move{"R3"});
        auto expected = Vec{point{2,2}};
        REQUIRE_THAT(intersections(first_leg, second_leg), UnorderedEquals(expected));
    }

    SECTION("origin is included") {
        point origin{0,0};
        auto first_leg = path{origin}.then(move{"U1"});
        auto second_leg = path{origin}.then(move{"R1"});
        auto expected = Vec{origin};
        REQUIRE_THAT(intersections(first_leg, second_leg), Equals(expected));
    }

    SECTION("goal is included") {
        auto first_leg = path{point{0,1}}.then(move{"R1"});
        auto second_leg = path{point{1,0}}.then(move{"U1"});
        auto expected = Vec{point{1,1}};
        REQUIRE_THAT(intersections(first_leg, second_leg), Equals(expected));
    }

    SECTION("multiple intersections") {
        point origin{0,0};
        auto first_leg = path{origin}.then(move{"R8"}).then(move{"U5"}).then(move{"L5"}).then(move{"D3"});
        auto second_leg = path{origin}.then(move{"U7"}).then(move{"R6"}).then(move{"D4"}).then(move{"L4"});
        auto expected = Vec{origin, point{3,3}, point{6,5}};
        REQUIRE_THAT(intersections(first_leg, second_leg), UnorderedEquals(expected));
    }

    SECTION("intersecting with itself doesn't count") {
        point origin{0,0};
        auto first_leg = path{origin}.then(move{"U2"}).then(move{"R1"}).then(move{"D1"}).then(move{"L1"});
        auto second_leg = path{origin}.then(move{"D3"});
        auto expected = Vec{origin};
        REQUIRE_THAT(intersections(first_leg, second_leg), UnorderedEquals(expected));
    }
}
