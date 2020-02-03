#include <intersect/point.hpp>
#include <sstream>

namespace intersect {

point::point(point::value_type x, point::value_type y) : x_{x}, y_{y} {}

point::distance_type point::distance_to(point const& other) const {
    return abs(x_ - other.x_) + abs(y_ - other.y_);
}

point::value_type point::x() const { return x_; }
point::value_type point::y() const { return y_; }

point::value_type get_x(point const& p) { return p.x(); }
point::value_type get_y(point const& p) { return p.y(); }

point rotate(point const& p) {
    return point{p.y(), p.x()};
}

std::string to_string(point const& p) {
    std::stringstream ss;
    ss << p;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, point const& p) {
    return os << '(' << p.x() << ',' << p.y() << ')';
}

bool operator==(point const& lhs, point const& rhs) {
    return lhs.x() == rhs.x()
        && lhs.y() == rhs.y();
}

bool operator!=(point const& lhs, point const& rhs) {
    return !(lhs == rhs);
}

}
