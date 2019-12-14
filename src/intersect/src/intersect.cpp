#include <intersect/intersect.hpp>
#include <cassert>
#include <sstream>


namespace intersect {

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

move::move(std::string_view movestr) : move(std::cbegin(movestr), std::cend(movestr)) {}

move::move(std::string_view::const_iterator current, std::string_view::const_iterator last) {
    assert(current != last);
    auto direction = *current++;
    auto distance = [&] {
      std::string distance;
      while (current != last) {
          if (!is_number(*current))
              throw invalid_distance{*current};
          distance += *current++;
      }
      return std::stoi(distance);
    }();

    direction_ = parse_direction(direction);
    switch (direction_) {
        case direction::UP: y = distance; break;
        case direction::DOWN: y = -distance; break;
        case direction::RIGHT: x = distance; break;
        case direction::LEFT: x = -distance; break;
    }
}

direction move::dir() const {
    return direction_;
}

point::point(int x_, int y_) : x{x_}, y{y_} {}

std::string point::str() const {
    std::stringstream ss;
    ss << '{' << x << ',' << y << '}';
    return ss.str();
}

line point::move_towards(point const& destination) {
    auto direction = [&] {
        const auto difference_in_x{destination.x - x};
        const auto difference_in_y{destination.y - y};
        if (difference_in_x > 0)
            return direction::RIGHT;
        else if (difference_in_x < 0)
            return direction::LEFT;
        else if (difference_in_y > 0)
            return direction::UP;
        else if (difference_in_y < 0)
            return direction::DOWN;
        else
            throw invalid_direction{'?'};
    }();
    return line{*this, direction};
}

constexpr direction parse_direction(char d) {
    switch(d) {
        case 'U': return direction::UP;
        case 'D': return direction::DOWN;
        case 'R': return direction::RIGHT;
        case 'L': return direction::LEFT;
        default: throw invalid_direction{d};
    }
}

line::line(point start, direction d)
: pt{start}
, dir{d} {
    set_step_forward();
}

line::line(line const& other) noexcept
: line(other.pt, other.dir) {
}

line& line::operator=(line other) noexcept {
    swap(*this, other);
    return *this;
}

line::line(line&& other) noexcept
: pt{std::move(other.pt)}
, dir{std::move(other.dir)} {
    set_step_forward();
}

path::path(point origin)
: current_point{origin} {
}

path& path::then(move next) {
    upcoming_moves.push_back(std::move(next));
    return *this;
}

line& line::operator++() {
    one_step_forward();
    return *this;
}

line line::operator++(int) {
    line tmp{*this};
    one_step_forward();
    return tmp;
}

point& line::operator*() {
    return pt;
}

point* line::operator->() {
    return &pt;
}

bool line::operator==(line const& other) const {
    return pt == other.pt;
}

bool line::operator!=(line const& other) const {
    return pt != other.pt;
}

void line::set_step_forward() {
    switch(dir) {
        case direction::UP: one_step_forward = [&]{ ++ pt.y; }; break;
        case direction::DOWN: one_step_forward = [&]{ -- pt.y; }; break;
        case direction::RIGHT: one_step_forward = [&]{ ++ pt.x; }; break;
        case direction::LEFT: one_step_forward = [&]{ -- pt.x; }; break;
    }
}

std::string to_string(direction d) {
    switch(d) {
        case direction::UP: return "UP";
        case direction::DOWN: return "DOWN";
        case direction::LEFT: return "LEFT";
        case direction::RIGHT: return "RIGHT";
    }
}

path& path::operator++() {
    if (!next_stopover) {
        auto const& next_move = upcoming_moves[0];
        current_step = line{current_point, next_move.dir()};
        next_stopover = current_point + next_move;
    }
    else if (current_point == next_stopover) {
        if (current_move_index < upcoming_moves.size())
            ++current_move_index;
        auto const& next_move = upcoming_moves[current_move_index];
        current_step = line{current_point, next_move.dir()};
        next_stopover = current_point + next_move;
    }

    current_point = *++current_step;
    return *this;
}

path path::operator++(int) {
    path tmp{*this};
    ++*this;
    return tmp;
}

point& path::operator*() {
    return current_point;
}

point* path::operator->() {
    return &current_point;
}

bool path::operator==(path const& other) const {
    return current_step == other.current_step
        && current_move_index == other.current_move_index
        && next_stopover == other.next_stopover
        && upcoming_moves == other.upcoming_moves;
}

bool path::operator!=(path const& other) const {
    return !(*this == other);
}

bool move::operator==(move const& other) const {
    return x == other.x && y == other.y;
}

bool move::operator!=(move const& other) const {
    return !(*this == other);
}

bool operator==(point const& lhs, point const& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(point const& lhs, point const& rhs) {
    return !(lhs == rhs);
}

point& point::operator+=(move const& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

std::string point::print() const {
    return '(' + std::to_string(x) + ',' + std::to_string(y) + ')';
}

point operator+(point const& p, move const& m) {
    return point{p.x + m.x, p.y + m.y};
}

point operator+(point&& p, move const& m) {
    p.x += m.x;
    p.y += m.y;
    return std::move(p);
}

void swap(line &lhs, line& rhs) noexcept {
    using std::swap;
    swap(lhs.pt, rhs.pt);
    swap(lhs.dir, rhs.dir);
    lhs.set_step_forward();
    rhs.set_step_forward();
}

}
