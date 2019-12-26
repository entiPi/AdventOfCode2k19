#include <intersect/intersect.hpp>
#include <utils/timer.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <locale>
#include <algorithm>
#include <chrono>
#include <type_traits>

using namespace std;
using namespace std::chrono;
using namespace intersect;


namespace {

// see https://en.cppreference.com/w/cpp/locale/ctype_char Example
struct csv_whitespace : ctype<char> {
    static const mask* make_table() {
        static vector<mask> v(classic_table(), classic_table() + table_size);
        v[','] |= space;
        v[' '] |= space;
        return &v[0];
    }

    csv_whitespace(std::size_t refs = 0) : ctype(make_table(), false, refs) {}
};

path read_wire(std::istream& is, std::string user_query) {
    path p{point{0,0}};

    cout << user_query << ": ";
    string line;
    if (getline(is, line)) {
        stringstream ss{line};
        ss.imbue(std::locale(ss.getloc(), new csv_whitespace));
        string move_token;
        while (ss >> move_token) {
            p.then(intersect::move{move_token});
        }
    }
    return p;
}

template<typename T>
struct is_duration : std::false_type {};

template<typename Rep, typename Period>
struct is_duration<duration<Rep, Period>> : std::true_type {};

template<typename duration, typename = std::enable_if_t<is_duration<duration>::value>>
std::ostream& operator<<(std::ostream& os, duration d) {
    return os << '[' << d.count() << ']';
}

}


int main() {

    utils::timer t;
    using dt = milliseconds;

    auto wire1 = read_wire(cin, "Enter first wire");
    auto wire2 = read_wire(cin, "Enter second wire");
    clog << '\n';

    clog << duration_cast<dt>(t.this_lap()) << ": parsed input\n";

    auto length = [](path p) {
        size_t count{0};
        for (auto it = begin(p)
            ; it != end(p)
            ; ++it, ++count);
        return count;
    };
    clog << duration_cast<dt>(t.this_lap()) << " length: wire1=" << length(wire1) << " wire2=" << length(wire2) << '\n';

    vector<point> crossings = intersections(wire1, wire2);

    clog << duration_cast<dt>(t.this_lap()) << ": crossings [" << crossings.size() << "]\n";
    vector<int> distances;
    auto distance_to_origin = [](point const& p){ return p.distance_to(point{0,0}); };
    transform(begin(crossings), end(crossings), back_inserter(distances), distance_to_origin);
    clog << duration_cast<dt>(t.this_lap()) << ": calc distance to origin\n";
    sort(begin(distances), end(distances));
    clog << duration_cast<dt>(t.this_lap()) << ": sort distances\n";
    cout << distances[1] << '\n';
}
