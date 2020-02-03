#include <catch2/catch.hpp>
#include <intersect/path.hpp>


using namespace intersect;

TEST_CASE("paths") {

    SECTION("ordering stays the same") {

        SECTION("from moves") {
            move first{"U10"}, second{"R5"}, third{"D3"}, fourth{"D8"};
            auto const p = path{point{0,0}}
                  .then(first)
                  .then(second)
                  .then(third)
                  .then(fourth);
            auto line_it = p.begin();
            REQUIRE(*line_it == first);
            REQUIRE(*++line_it == second);
            REQUIRE(*++line_it == third);
            REQUIRE(*++line_it == fourth);
        }

        SECTION("from lines") {
            line first{{0,0}, {1,0}},
                 second{{1,0}, {1,-3}},
                 third{{1,-3}, {1,-5}},
                 fourth{{1,-5}, {4,-5}};
            auto const p = path{point{0,0}}
                  .then(first)
                  .then(second)
                  .then(third)
                  .then(fourth);
            auto line_it = p.begin();
            REQUIRE(*line_it == first);
            REQUIRE(*++line_it == second);
            REQUIRE(*++line_it == third);
            REQUIRE(*++line_it == fourth);
        }

        SECTION("from initializer_list") {
            line first{{0,0}, {1,0}},
                 second{{1,0}, {1,-3}},
                 third{{1,-3}, {1,-5}},
                 fourth{{1,-5}, {4,-5}};
            path const p{first, second, third, fourth};
            auto line_it = p.cbegin();
            REQUIRE(*line_it == first);
            REQUIRE(*++line_it == second);
            REQUIRE(*++line_it == third);
            REQUIRE(*++line_it == fourth);
        }
    }

    SECTION("distance on path") {

        move const first{"U10"}, second{"R5"}, third{"D3"}, fourth{"L7"};
        auto const p = path{point{0,0}}
              .then(first)
              .then(second)
              .then(third)
              .then(fourth);

        SECTION("part of path") {
            REQUIRE(p.distance_to(point{0,0}).value() == 0);
            REQUIRE(p.distance_to(point{0,10}).value() == 10);
            REQUIRE(p.distance_to(point{5,10}).value() == 15);
        }

        SECTION("point not on path yields empty result") {
            REQUIRE(!p.distance_to(point{1,0}).has_value());
        }
    }

    SECTION("iterators") {
        using namespace std;
        line const l{{0,0}, {3,0}};
        path p{l};

        SECTION("begin") {

            SECTION("member fn") {
                path::iterator it = p.begin();
                path::const_iterator cit = p.begin();
                path::const_iterator cit2 = p.cbegin();
                REQUIRE(*it == l);
                REQUIRE(*cit == l);
                REQUIRE(*cit2 == l);
            }

            SECTION("free fn") {
                path::iterator it = begin(p);
                path::const_iterator cit = begin(p);
                path::const_iterator cit2 = cbegin(p);
                REQUIRE(*it == l);
                REQUIRE(*cit == l);
                REQUIRE(*cit2 == l);
            }
        }

        SECTION("end") {

            SECTION("member fn") {
                path::iterator it = p.end();
                path::const_iterator cit = p.end();
                path::const_iterator cit2 = p.cend();
                REQUIRE(*--it == l);
                REQUIRE(*--cit == l);
                REQUIRE(*--cit2 == l);
            }

            SECTION("free fn") {
                path::iterator it = end(p);
                path::const_iterator cit = end(p);
                path::const_iterator cit2 = cend(p);
                REQUIRE(*--it == l);
                REQUIRE(*--cit == l);
                REQUIRE(*--cit2 == l);
            }
        }
    }
}
