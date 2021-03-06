#include <intersect/intersect.hpp>
#include <intersect/direction.hpp>
#include <algorithm/cartesian_product.hpp>
#include <algorithm>
#include <iterator>
#include <tuple>


using namespace std;

namespace intersect {

namespace {

bool is_parallel(line const& l1, line const& l2) {
    return (is_vertical(l1) && is_vertical(l2))
        || (is_horizontal(l1) && is_horizontal(l2));
}

bool has_parallel_offset(point::value_type(x_or_y)(point const&), line const& l1, line const& l2) {
    return x_or_y(l1.start()) - x_or_y(l2.start()) != 0;
}

bool is_between(int val, int low, int high) {
    return low <= val && val <= high;
}

function<function<point()>(point::value_type)> horizontal(point::value_type y) {
    return [=](point::value_type x) {
        return [x, y]() mutable {
            return point{x++, y};
        };
    };
}

function<function<point()>(point::value_type)> vertical(point::value_type x) {
    return [=](point::value_type y) {
        return [x, y]() mutable {
            return point{x, y++};
        };
    };
}

template<typename Generator>
vector<point> generate_point_sequence(point::value_type from, point::value_type to, Generator generate_points) {
    auto const distance = 1 + to-from;  // add point because 'to' is inclusive
    vector<point> vec{};
    vec.reserve(distance);
    generate_n(back_inserter(vec), distance, generate_points(from));
    return vec;
}

}

vector<point> intersection(line const& a, line const& b) {
    if (is_parallel(a, b)) {
        auto const [flipped,fa] = make_horizontal(a);
        auto const fb = get<1>(make_horizontal(b));
        if (!has_parallel_offset(get_y, fa, fb)) {
            auto const y = get_y(a.start());
            auto [a1,a2] = get_sorted(get_x, fa);
            auto [b1,b2] = get_sorted(get_x, fb);
            if (is_between(b1, a1, a2)) {
                if (b2 < a2)
                    return generate_point_sequence(b1, b2, flipped ? vertical(y) : horizontal(y));
                else
                    return generate_point_sequence(b1, a2, flipped ? vertical(y) : horizontal(y));
            }
            else if (is_between(a1, b1, b2)) {
                if (a2 < b2)
                    return generate_point_sequence(a1, a2, flipped ? vertical(y) : horizontal(y));
                else
                    return generate_point_sequence(a1, b2, flipped ? vertical(y) : horizontal(y));
            }
            else
                return {};
        }
    }
    else {  // !is_parallel
        auto const x = get_x(is_vertical(a) ? a.start() : b.start());
        auto const y = get_y(is_horizontal(a) ? a.start() : b.start());
        auto const [x1,x2] = get_sorted(get_x, is_horizontal(a) ? a : b);
        auto const [y1,y2] = get_sorted(get_y, is_vertical(a) ? a : b);
        if (is_between(x, x1, x2) && is_between(y, y1, y2)) {
            return {{x,y}};
        }
    }

    return {};
}

vector<point> intersections(path const& p1, path const& p2) {
    using namespace std;
    vector<point> intersections{};
    for (auto const& [line1, line2] : cartesian_product(
                begin(p1), end(p1),
                begin(p2), end(p2))) {
        if (auto const x = intersection(*line1, *line2); !x.empty())
            copy(begin(x), end(x), back_inserter(intersections));
    }
    return intersections;
}

}
