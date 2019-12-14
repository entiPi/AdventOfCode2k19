#include <iterator>
#include <tuple>

template<typename First1, typename Last1, typename First2, typename Last2>
struct cartesian_product_iterator
    : std::iterator<std::forward_iterator_tag, std::tuple<First1, First2>> {

    using value_type = std::tuple<First1, First2>;

    cartesian_product_iterator(First1 first1, Last1 last1, First2 first2, Last2 last2)
        : f1{first1}, l1{last1}
        , f2{first2}, l2{last2}
        , c1{first1}, c2{first2} {
    }

    value_type operator*() const { return std::make_tuple(c1, c2); }

    operator bool() const { return c2 < l2; }

    value_type operator++() {
        ++c1;
        if (c1 == l1) {
            c1 = f1;
            ++c2;
        }
        return std::make_tuple(c1, c2);
    }

    value_type operator++(int) {
        auto tmp{*this};
        ++*this;
        return *tmp;
    }

    private:
    const First1 f1;
    const Last1 l1;
    const First2 f2;
    const Last2 l2;
    First1 c1;
    First2 c2;
};

template<typename F1, typename L1, typename F2, typename L2>
auto cartesian_product(F1 f1, L1 l1, F2 f2, L2 l2) {
    return cartesian_product_iterator<F1,L1,F2,L2>{f1, l1, f2, l2};
}
