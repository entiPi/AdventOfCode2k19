#pragma once
#include <intersect/line.hpp>
#include <intersect/point.hpp>
#include <initializer_list>
#include <vector>


namespace intersect {

struct path {
    using iterator = std::vector<line>::iterator;
    using const_iterator = std::vector<line>::const_iterator;

    path(point origin);
    path(std::initializer_list<line> lines);

    path& then(line next);
    path& then(move next);
    path& operator+(line next);

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    private:
    point const origin_;
    size_t current_line_index{0};
    std::vector<line> lines;
};

}
