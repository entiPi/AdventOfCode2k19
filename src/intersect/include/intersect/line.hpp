#pragma once
#include <intersect/point.hpp>
#include <intersect/direction.hpp>
#include <ostream>
#include <string>
#include <string_view>
#include <stdexcept>


namespace intersect {

struct move {
    explicit move(std::string_view movestr);
    explicit move(std::string_view::const_iterator current, std::string_view::const_iterator last);

    dir direction() const;
    int length() const;

    private:
    dir direction_;
    int length_;
};

struct line {
    line(point const& start, point const& stop);
    line(point const& start, move const& mv);

    constexpr point const& start() const { return start_; }
    constexpr point const& stop() const { return stop_; }

    dir direction() const;
    int length() const;

    private:
    point start_, stop_;
    int length_in_x() const;
    int length_in_y() const;
};

struct invalid_distance : std::runtime_error {
    invalid_distance(char d);
};

struct multiple_dimensions : std::runtime_error {
    multiple_dimensions();
    multiple_dimensions(point const& a, point const& b);
};

point operator+(point const& lhs, move const& rhs);

bool operator==(line const& lhs, line const& rhs);
bool operator!=(line const& lhs, line const& rhs);

bool operator==(line const& lhs, move const& rhs);
bool operator!=(line const& lhs, move const& rhs);

bool operator==(move const& lhs, line const& rhs);
bool operator!=(move const& lhs, line const& rhs);

std::string to_string(line const&);
std::ostream& operator<<(std::ostream&, line const&);

}
