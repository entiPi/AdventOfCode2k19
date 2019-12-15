#include <iterator>
#include <tuple>
#include <boost/coroutine2/coroutine.hpp>

template<typename F1, typename L1, typename F2, typename L2>
auto cartesian_product(F1 f1, L1 l1, F2 f2, L2 l2) {
    using coroutine = typename boost::coroutines2::coroutine<std::tuple<F1,F2>>;
    return typename coroutine::pull_type{
        [=](typename coroutine::push_type& yield) {
            F2 c2{f2};
            for (F1 c1{f1}; c1 != l1 ; ++c1, c2 = f2)
                for (; c2 != l2; ++c2)
                    yield(std::make_tuple(c1, c2));
        }
    };
}
