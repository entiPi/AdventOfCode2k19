#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <tuple>
#include <array>
#include <algorithm/cartesian_product.hpp>
#include <intcode/intcode.hpp>

static const intcode::program original_prog{
    1,0,0,3,      1,1,2,3,      1,3,4,3,      1,5,0,3,      2,6,1,19,
    2,19,9,23,    1,23,5,27,    2,6,27,31,    1,31,5,35,    1,35,5,39,
    2,39,6,43,    2,43,10,47,   1,47,6,51,    1,51,6,55,    2,55,6,59,
    1,10,59,63,   1,5,63,67,    2,10,67,71,   1,6,71,75,    1,5,75,79,
    1,10,79,83,   2,83,10,87,   1,87,9,91,    1,91,10,95,   2,6,95,99,
    1,5,99,103,   1,103,13,107, 1,107,10,111, 2,9,111,115,  1,115,6,119,
    2,13,119,123, 1,123,6,127,  1,5,127,131,  2,6,131,135,  2,6,135,139,
    1,139,5,143,  1,143,10,147, 1,147,2,151,  1,151,13,0,   99,2,0,14,
    0
};

int main() {
    using namespace std;
    using range_type = array<int,100>;
    range_type number_range{};
    iota(begin(number_range), end(number_range), 0);

    auto const [noun, verb] = [&] {
      for (auto number_seq = cartesian_product(
              begin(number_range), end(number_range),
              begin(number_range), end(number_range))
          ; number_seq
          ; ++number_seq) {
          auto const& [noun, verb] = *number_seq;
          auto fixed_prog{original_prog};
          fixed_prog[1] = *noun;
          fixed_prog[2] = *verb;
          if (19690720 == intcode::compute(fixed_prog)[0])
              return tie(*noun, *verb);
      }
      throw runtime_error{"verb, noun not found"};
    }();

    auto const result = 100 * noun + verb;
    cout << result << '\n';
}
