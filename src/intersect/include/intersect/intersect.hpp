#include <string_view>
#include <iterator>
#include <ostream>
#include <functional>
#include <optional>
#include <vector>
#include <stdexcept>


namespace intersect {

struct move;
struct line;

struct point {
    point(int x, int y);

    line move_towards(point const& destination);
    int distance_to(point const& other) const;

    point& operator+=(move const& rhs);

    private:
    int x, y;

    friend bool operator==(point const&, point const&);
    friend point operator+(point const&, move const&);
    friend point operator+(point&&, move const&);
    friend std::ostream& operator<<(std::ostream&, point const&);
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

struct end_of_path {};

struct path {
    path(point origin);
    path& then(move next);

    void shrink(int scale);
    using section_iterator = std::vector<move>::iterator;
    using const_section_iterator = std::vector<move>::const_iterator;
    std::tuple<const_section_iterator, const_section_iterator> sections() const;

    path& operator++();
    path operator++(int);
    point& operator*();
    point* operator->();
    bool operator==(path const& other) const;
    bool operator!=(path const& other) const;
    bool operator==(end_of_path) const;
    bool operator!=(end_of_path) const;
    path& operator+(move next);

    path& begin();
    end_of_path end();
    path const& begin() const;
    end_of_path end() const;

    private:
    point current_point;
    std::optional<point> next_stopover;
    size_t current_move_index{0};
    std::vector<move> moves;
    line current_step{current_point, direction::UP};
};

using namespace std::string_literals;

struct invalid_direction : std::runtime_error {
    invalid_direction(char d) : std::runtime_error{"invalid direction: "s + d} {};
};

struct invalid_distance : std::runtime_error {
    invalid_distance(char d) : std::runtime_error{"invalid distance: "s + d} {};
};

std::vector<point> intersections(path const& p1, path const& p2);

std::ostream& operator<<(std::ostream&, point const&);

bool operator==(point const& lhs, point const& rhs);
bool operator!=(point const& lhs, point const& rhs);

point operator+(point const& p, move const& m);
point operator+(point&& p, move const& m);

path& begin(path&);
end_of_path end(path&);
path const& begin(path const&);
end_of_path end(path&);
end_of_path end(path const&);

bool operator==(end_of_path, path const& rhs);
bool operator!=(end_of_path, path const& rhs);

void swap(line &lhs, line& rhs) noexcept;

}

