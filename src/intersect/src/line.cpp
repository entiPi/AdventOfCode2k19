#include <intersect/line.hpp>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace std::string_literals;

namespace {

using namespace intersect;

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

bool is_between(int val, int low, int high) {
    return low <= val && val <= high;
}

bool is_on_line(line const& l, point const& p) {
    auto const [flipped, lh] = make_horizontal(l);
    auto const fp = flipped ? rotate(p) : p;
    if (get_y(lh.start()) == fp.y()) {
        auto const [x1, x2] = get_sorted(get_x, lh);
        return is_between(fp.x(), x1, x2);
    }
    return false;
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

std::optional<line::distance_type> line::distance_to(point const& p) const {
    if (is_on_line(*this, p))
        return {line{start(), p}.length()};
    return {};
}

line::line(point const& start, point const& stop)
: start_{start}
, stop_{stop} {
    if (start_.x() != stop_.x() && start_.y() != stop_.y())
        throw multiple_dimensions{start_, stop_};
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

bool is_vertical(line const& l) {
    return l.direction() == dir::UP || l.direction() == dir::DOWN;
}

bool is_horizontal(line const& l) {
    return l.direction() == dir::LEFT || l.direction() == dir::RIGHT;
}

line rotate(line const& l) {
    return line{rotate(l.start()), rotate(l.stop())};
}

tuple<bool,line> make_horizontal(line const& l) {
    if (is_vertical(l))
        return make_tuple(true, rotate(l));
    return make_tuple(false, l);
}

pair<point::value_type, point::value_type> get_sorted(point::value_type(x_or_y)(point const&), line const& l) {
    return minmax(x_or_y(l.start()), x_or_y(l.stop()));
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
