#include <string_view>
#include <string>
#include <iterator>
#include <functional>
#include <optional>
#include <vector>
#include <stdexcept>


namespace intersect {

struct move;
struct line;

struct point {
    point(int x, int y);

    std::string str() const;
    line move_towards(point const& destination);

    point& operator+=(move const& rhs);
    std::string print() const;

    private:
    int x, y;

    friend bool operator==(point const&, point const&);
    friend point operator+(point const&, move const&);
    friend point operator+(point&&, move const&);
    friend struct line;
};

enum class direction { UP, DOWN, RIGHT, LEFT };
constexpr direction parse_direction(char d);

struct line : std::iterator<std::forward_iterator_tag, point> {
    line(point start, direction d);
    line(line const& other) noexcept;
    line& operator=(line other) noexcept;
    line(line&& other) noexcept;
    friend void swap(line &lhs, line& rhs) noexcept;

    line& operator++();
    line operator++(int);
    point& operator*();
    point* operator->();
    bool operator==(line const& other) const;
    bool operator!=(line const& other) const;

    private:
    point pt;
    direction dir;
    std::function<void(void)> one_step_forward;

    void set_step_forward();
};

struct move {
    move(std::string_view movestr);
    move(std::string_view::const_iterator first, std::string_view::const_iterator last);
    direction dir() const;

    bool operator==(move const& other) const;
    bool operator!=(move const& other) const;

    private:
    int x{0}, y{0};
    direction direction_;

    friend point operator+(point const&, move const&);
    friend point operator+(point&&, move const&);
    friend point& point::operator+=(move const&);
};

struct path {
    path(point origin);
    path& then(move next);

    path& operator++();
    path operator++(int);
    point& operator*();
    point* operator->();
    bool operator==(path const& other) const;
    bool operator!=(path const& other) const;

    private:
    point current_point;
    std::optional<point> next_stopover;
    size_t current_move_index{0};
    std::vector<move> upcoming_moves;
    line current_step{current_point, direction::UP};
};

struct invalid_direction : std::runtime_error {
    invalid_direction(char d) : std::runtime_error{"invalid direction: " + d} {};
};

struct invalid_distance : std::runtime_error {
    invalid_distance(char d) : std::runtime_error{"invalid distance: " + d} {};
};

bool operator==(point const& lhs, point const& rhs);
bool operator!=(point const& lhs, point const& rhs);

point operator+(point const& p, move const& m);
point operator+(point&& p, move const& m);

void swap(line &lhs, line& rhs) noexcept;

}

