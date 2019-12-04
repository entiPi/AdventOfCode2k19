#include <intcode/intcode.hpp>
#include <iterator>
#include <functional>
#include <type_traits>


namespace intcode {
namespace detail {

enum class opcode_t : value_type {
    add = 1,
    mul = 2,
    end = 99,
};

bool operator==(opcode_t lhs, value_type rhs) {
    const auto lhs_ = static_cast<value_type>(lhs);
    return lhs_ == rhs;
}

bool operator==(value_type lhs, opcode_t rhs) {
    const auto rhs_ = static_cast<value_type>(rhs);
    return lhs == rhs_;
}

bool operator!=(opcode_t lhs, value_type rhs) { return not(lhs == rhs); }
bool operator!=(value_type lhs, opcode_t rhs) { return not(lhs == rhs); }

opcode_t make_opcode(value_type candidate) {
        if (candidate == opcode_t::add) return opcode_t::add;
        if (candidate == opcode_t::mul) return opcode_t::mul;
        if (candidate == opcode_t::end) return opcode_t::end;
        throw invalid_opcode{candidate};
}

using operation = std::function<value_type(value_type,value_type)>;
operation eval(value_type opcode)  {
    if (opcode == opcode_t::add) return std::plus<>{};
    if (opcode == opcode_t::mul) return std::multiplies<>{};
    throw invalid_opcode{opcode};
}

template<typename Distance, typename Iter>
void advance_all(Distance n, Iter& it) {
    std::advance(it, n);
}

template<typename Distance, typename Iter, typename... Iters>
void advance_all(Distance n, Iter& head, Iters&... tail) {
    std::advance(head, n);
    advance_all(n, tail...);
}

}

output compute(program prog) {
  using namespace detail;

  auto [opcode, lhs, rhs, result] = [&] {
    auto first{std::begin(prog)};
    return std::make_tuple<>(first, first+1, first+2, first+3);
  }();

  while (*opcode != opcode_t::end) {
      prog[*result] = eval(*opcode)(prog[*lhs], prog[*rhs]);
      advance_all(4, opcode, lhs, rhs, result);
  }
  return prog;
}

}
