#pragma once
#include <stdexcept>
#include <string>

namespace {
static char const* up_str = "UP";
static char const* down_str = "DOWN";
static char const* left_str = "LEFT";
static char const* right_str = "RIGHT";
}


namespace intersect {

struct invalid_direction : std::runtime_error {
    invalid_direction(char d);
};

enum class dir { UP, DOWN, RIGHT, LEFT };

constexpr dir parse_direction(char d) {
    switch(d) {
        case 'U': return dir::UP;
        case 'D': return dir::DOWN;
        case 'R': return dir::RIGHT;
        case 'L': return dir::LEFT;
        default: throw invalid_direction{d};
    }
}

constexpr char const* to_string(dir d) {
    switch(d) {
        case dir::UP: return up_str;
        case dir::DOWN: return down_str;
        case dir::LEFT: return left_str;
        case dir::RIGHT: return right_str;
        default: throw invalid_direction{static_cast<char>(d)};
    }
}

}
