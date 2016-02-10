#include <iostream>
#include <tuple>
#include <utility>

// pretty-print a tuple (from http://stackoverflow.com/a/6245777/273767)

template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl( std::basic_ostream<Ch,Tr> & os,
                      const Tuple & t, std::index_sequence<Is...>) {
    using swallow = int[]; // guaranties left to right order
    (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
}

template<class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}
