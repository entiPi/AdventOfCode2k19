#pragma once
#include <ostream>
#include <string>


namespace intersect {

struct point {
    using value_type = int;
    using distance_type = unsigned;

    point(value_type x, value_type y);

    distance_type distance_to(point const& other) const;

    value_type x() const;
    value_type y() const;

    private:
    value_type x_, y_;
};

std::string to_string(point const& p);
std::ostream& operator<<(std::ostream&, point const&);
bool operator==(point const& lhs, point const& rhs);
bool operator!=(point const& lhs, point const& rhs);

}
