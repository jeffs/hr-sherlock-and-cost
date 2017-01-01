#include <iostream>
#include <vector>

#ifdef NDEBUG
#   define DUMP(X)
#else
#   include <json.hpp>
#   define DUMP(x) std::clog << nlohmann::json(x) << '\n';
#endif

namespace {

using value_type = int;
using array_type = std::vector<value_type>;
using index_type = array_type::size_type;

struct node {
    value_type value;
    index_type index;
};

template <class T>
T read()
{
    T r;
    if (std::cin >> r)
        return r;
    throw "expected value";
}

value_type solve(array_type const& b)
{
    return {};  // TODO
}

}

int main()
{
    for (int t = read<int>(); t--;) {
        array_type b(read<index_type>());
        std::generate(b.begin(), b.end(), read<value_type>);
        DUMP(b);
        solve(b);
    }
}
