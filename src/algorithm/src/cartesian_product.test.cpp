#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <algorithm/cartesian_product.hpp>
#include <vector>

TEST_CASE("cartesian product") {
    using namespace std;
    using Catch::Matchers::UnorderedEquals;

    int pos[] = {1, 2, 3, 4};
    int neg[] = {-1, -2, -3};
    char chars[] {'a', 'b'};

    SECTION("same set") {
        vector<tuple<int,int>> result;
        for (auto [a, b] : cartesian_product(begin(pos), end(pos), begin(pos), end(pos))) {
            result.emplace_back(*a, *b);
        }

        vector<tuple<int,int>> expected{
            make_tuple(1,1), make_tuple(1,2), make_tuple(1,3), make_tuple(1,4),
            make_tuple(2,1), make_tuple(2,2), make_tuple(2,3), make_tuple(2,4),
            make_tuple(3,1), make_tuple(3,2), make_tuple(3,3), make_tuple(3,4),
            make_tuple(4,1), make_tuple(4,2), make_tuple(4,3), make_tuple(4,4)};

        REQUIRE_THAT(result, UnorderedEquals(expected));
    }

    SECTION("same types") {
        vector<tuple<int,int>> result;
        for (auto [a, b] : cartesian_product(begin(pos), end(pos), begin(neg), end(neg))) {
            result.emplace_back(*a, *b);
        }

        vector<tuple<int,int>> expected{
            make_tuple(1,-1), make_tuple(1,-2), make_tuple(1,-3),
            make_tuple(2,-1), make_tuple(2,-2), make_tuple(2,-3),
            make_tuple(3,-1), make_tuple(3,-2), make_tuple(3,-3),
            make_tuple(4,-1), make_tuple(4,-2), make_tuple(4,-3)};

        REQUIRE_THAT(result, UnorderedEquals(expected));
    }

    SECTION("different types") {
        vector<tuple<char,int>> result;
        for (auto [a, b] : cartesian_product(begin(chars), end(chars), begin(pos), end(pos))) {
            result.emplace_back(*a, *b);
        }

        vector<tuple<char,int>> expected{
            make_tuple('a',1), make_tuple('a',2), make_tuple('a',3), make_tuple('a',4),
            make_tuple('b',1), make_tuple('b',2), make_tuple('b',3), make_tuple('b',4)};

        REQUIRE_THAT(result, UnorderedEquals(expected));
    }
}
