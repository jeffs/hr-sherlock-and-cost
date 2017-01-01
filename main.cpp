#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>

#ifndef DEBUG
#   define DUMP(X)
#else
#   include <json.hpp>
#   define DUMP(x) std::clog << #x " = " << nlohmann::json(x) << '\n'
#endif

namespace {

using value_type = int;
using array_type = std::vector<value_type>;
using iterator = array_type::const_iterator;

using std::next;

struct node {
    iterator position;
    value_type value;

    value_type cost(node target) const {
        return std::abs(target.value - value);
    }
};

bool operator<(node a, node b) {
    return a.position < b.position
        || (a.position == b.position && a.value < b.value);
}

template <class T>
T read()
{
    T r;
    if (std::cin >> r)
        return r;
    throw "expected value";
}

value_type from_node(
        node source,
        iterator e,
        std::map<node, value_type>& memo)
{
    if (!memo.count(source)) {
        auto from_edge = [source, e, &memo](node target) {
            return source.cost(target) + from_node(target, e, memo);
        };
        auto q = next(source.position);
        auto r = q == e ? 0 : std::max(from_edge({q, 1}), from_edge({q, *q}));
        memo.emplace(source, r);
    }
    return memo[source];
}

value_type max_cost(array_type const& values)
{
    return values.size() < 2 ? 0 : [&values] {
        iterator b = begin(values), e = end(values);
        std::map<node, value_type> memo;
        return std::max(
                from_node({b, 1}, e, memo),
                from_node({b, *b}, e, memo));
    }();
}

}

int main()
{
    for (int t = read<int>(); t--;) {
        DUMP(t);
        array_type b(read<array_type::size_type>());
        std::generate(begin(b), end(b), read<value_type>);
        DUMP(b);
        std::cout << max_cost(b) << '\n';
    }
}
