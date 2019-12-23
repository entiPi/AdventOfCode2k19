#pragma once
#include <intersect/point.hpp>
#include <intersect/line.hpp>
#include <intersect/path.hpp>
#include <vector>


namespace intersect {

std::vector<point> intersection(line const& a, line const& b);
std::vector<point> intersections(path const& p1, path const& p2);

}

