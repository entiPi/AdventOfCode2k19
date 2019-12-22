#include <chrono>
#include <vector>

namespace utils {

template<typename Clock = std::chrono::high_resolution_clock>
struct timer {
    using clock_type = Clock;
    using time_point = std::chrono::time_point<clock_type>;
    using duration = typename clock_type::duration;

    duration this_lap() {
        laps.push_back(clock_type::now());
        return laps.back() - *(laps.rbegin() + 1);
    }

    duration since_start() {
        laps.push_back(clock_type::now());
        return laps.back() - laps.front();
    }

    std::vector<time_point>& all_laps() const { return laps; }

    private:
    std::vector<time_point> laps{clock_type::now()};
};

}
