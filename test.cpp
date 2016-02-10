#include <iostream>
#include <string>
#include <tuple>

#include "tuple.hpp"

int main() {
    std::tuple< int, std::string, std::string, double > tpl{ -1, "abc", "xyz", .5 }, tpl3;
    std::tuple< int, std::string, std::string > tpl1;
    std::tuple< std::string, double > tpl2;
    tail( tpl3) = tpl;
    head( tpl1) = tpl;
    tail( tpl2) = tpl;
    std::cout << " tpl: " << tpl << std::endl;
    std::cout << " tpl1: " << tpl1 << std::endl;
    std::cout << " tpl2: " << tpl2 << std::endl;
    std::cout << " tpl3: " << tpl3 << std::endl;
    return 0;
}
