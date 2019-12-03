#include <vector>
#include <stdexcept>

namespace intcode {

using value_type = int;
using program = std::vector<value_type>;
using output = std::vector<value_type>;

output compute(program);

namespace detail {
enum class opcode_t : value_type;
}

struct invalid_opcode : std::out_of_range {

    invalid_opcode(value_type op)
        : std::out_of_range{"invalid opcode " + std::to_string(op)} {
    }

    invalid_opcode(detail::opcode_t op)
        : invalid_opcode{static_cast<value_type>(op)} {
    }
};

}
