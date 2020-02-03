#include <intersect/path.hpp>


namespace intersect {

path::path(point origin)
: origin_{origin} {
}

path::path(std::initializer_list<line> ls)
: origin_{ls.begin()->start()} {
    for (auto& l : ls)
        lines.push_back(std::move(l));
}

path& path::then(line next) {
    lines.push_back(std::move(next));
    return *this;
}

path& path::then(move next) {
    point const& last_point = [&] {
        if (lines.empty())
            return origin_;
        return lines.back().stop();
    }();
    lines.emplace_back(last_point, next);
    return *this;
}

path::iterator path::begin() noexcept {
    return lines.begin();
}

path::const_iterator path::begin() const noexcept {
    return lines.begin();
}

path::const_iterator path::cbegin() const noexcept {
    return lines.cbegin();
}

path::iterator path::end() noexcept {
    return lines.end();
}

path::const_iterator path::end() const noexcept {
    return lines.end();
}

path::const_iterator path::cend() const noexcept {
    return lines.cend();
}

std::optional<path::distance_type> path::distance_to(point const& p) const {
    distance_type acc{};
    for (auto& l : *this) {
        if (auto dp = l.distance_to(p); dp)
            return {acc + *dp};
        else
            acc += l.length();
    }
    return {};
}

}
