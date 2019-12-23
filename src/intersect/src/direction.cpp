#include <intersect/direction.hpp>
#include <string>

using namespace std::string_literals;

namespace intersect {

invalid_direction::invalid_direction(char d)
: std::runtime_error{"invalid direction: "s + d} {
}

}
