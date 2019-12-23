#include <intersect/line.hpp>
#include <cassert>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace std::string_literals;

namespace {

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

}

namespace intersect {

move::move(string_view movestr)
: move(cbegin(movestr) , cend(movestr)) {
}

move::move(string_view::const_iterator current, string_view::const_iterator last) {
    assert(current != last);
    direction_ = parse_direction(*current++);
    length_ = [&] {
      string length_str;
      while (current != last) {
          if (!is_number(*current))
              throw invalid_distance{*current};
          length_str += *current++;
      }
      return stoi(length_str);
    }();
}

dir move::direction() const {
    return direction_;
}

int move::length() const {
    return length_;
}

line::line(point const& start, point const& stop)
: start_{start}
, stop_{stop} {
    if (start_.x() != stop_.x() && start_.y() != stop_.y())
        throw multiple_dimensions{start_, stop_};
    if (start_ == stop_)
        throw invalid_distance{'0'};
}

line::line(point const& start, move const& mv)
: start_{start}
, stop_{start+mv} {
}

dir line::direction() const {
    if (length_in_y() > 0)
        return dir::UP;
    else if (length_in_y() < 0)
        return dir::DOWN;
    else if (length_in_x() > 0)
        return dir::RIGHT;
    else if (length_in_x() < 0)
        return dir::LEFT;
    else
        throw invalid_distance{'0'};
}

int line::length() const {
    return abs(length_in_x() + length_in_y());
}

int line::length_in_x() const {
    return stop_.x() - start_.x();
}

int line::length_in_y() const {
    return stop_.y() - start_.y();
}

invalid_distance::invalid_distance(char d)
: std::runtime_error{"invalid distance: "s + d} {
}

multiple_dimensions::multiple_dimensions()
: std::runtime_error{"multiple dimensions"} {
}

multiple_dimensions::multiple_dimensions(point const& a, point const& b)
: std::runtime_error{"a: "s + to_string(a) + " b: " + to_string(b)} {
}

point operator+(point const& lhs, move const& rhs) {
    auto const move_direction = rhs.direction();
    if (move_direction == dir::LEFT)
        return point{
            lhs.x() - rhs.length(),
            lhs.y()};
    else if (move_direction == dir::RIGHT)
        return point{
            lhs.x() + rhs.length(),
            lhs.y()};
    else if (move_direction == dir::UP )
        return point{
            lhs.x(),
            lhs.y() + rhs.length()};
    else
        return point{
            lhs.x(),
            lhs.y() - rhs.length()};
}

bool operator==(line const& lhs, line const& rhs) {
    return lhs.start() == rhs.start()
        && lhs.stop() == rhs.stop();
}

bool operator!=(line const& lhs, line const& rhs) {
    return !(lhs == rhs);
}

bool operator==(line const& lhs, move const& rhs) {
    return lhs.direction() == rhs.direction()
        && lhs.length() == rhs.length();
}

bool operator!=(line const& lhs, move const& rhs) {
    return !(lhs == rhs);
}

bool operator==(move const& lhs, line const& rhs) {
    return rhs == lhs;
}

bool operator!=(move const& lhs, line const& rhs) {
    return !(rhs == lhs);
}

std::string to_string(line const& l) {
    std::stringstream ss;
    ss << l;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, line const& l) {
    return os << "<Line from=" << l.start() << " to=" << l.stop() << '>';
}

}
