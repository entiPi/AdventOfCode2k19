#include <intersect/intersect.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <locale>
#include <algorithm>

using namespace std;
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

}


int main() {
    auto wire1 = read_wire(cin, "Enter first wire");
    auto wire2 = read_wire(cin, "Enter second wire");

    vector<point> crossings = intersections(wire1, wire2);

    vector<int> distances;
    auto path_length = [&](point const& p){ return *wire1.distance_to(p) + *wire2.distance_to(p); };
    transform(begin(crossings), end(crossings), back_inserter(distances), path_length);
    sort(begin(distances), end(distances));
    cout << distances[1] << '\n';
}
