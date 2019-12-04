#include <module/module.hpp>

namespace module {

namespace {
    constexpr int calculateRequiredFuelImpl(int accumulator, int module_mass) {
        const auto fuel = module_mass / 3 - 2;
        return fuel > 0
            ? calculateRequiredFuelImpl(accumulator+fuel, fuel)
            : accumulator;
    }
}

int calculateRequiredFuel(int module_mass) {
    return calculateRequiredFuelImpl(0, module_mass);
}

}
