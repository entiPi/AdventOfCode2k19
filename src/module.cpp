#include "module.hpp"

namespace module {

int calculateRequiredFuel(int module_mass) {
    return module_mass / 3 - 2;
}

}
