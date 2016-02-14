#include <cassert>
#include <iostream>
#include <string>
#include <tuple>

#include "tuple.hpp"

class X {
public:
    bool    state;
    int     value;

    X() :
        state( false),
        value( -1) {
    }

    X( int v) :
        state( true),
        value( v) {
    }

    X( X && other) :
        state( other.state),
        value( other.value) {
        other.state = false;
        other.value = -1;
    }

    X & operator=( X && other) {
        if ( this == & other) return * this;
        state = other.state;
        value = other.value;
        other.state = false;
        other.value = -1;
        return * this;
    }

    X( X const& other) = delete;
    X & operator=( X const& other) = delete;
};

template< typename Ch, typename Tr >
decltype(auto) operator<<( std::basic_ostream< Ch, Tr > & os, X const& x) {
    os << "(";
    os << std::boolalpha << x.state << " ";
    os << x.value;
    return os << ")";
}

int main() {
    {
        int i = -1;
        double j = .5;
        std::string str1("abc"), str2("xyz");
        std::tuple< int, std::string, std::string, double > tpl{ i, str1, str2, j };
        std::tuple< int, std::string, std::string > tpl1;
        std::tuple< std::string, double > tpl2;
        head( tpl1) = tpl;
        tail( tpl2) = tpl;
        assert( i == std::get<0>(tpl1) );
        assert( str1 == std::get<1>(tpl1) );
        assert( str2 == std::get<2>(tpl1) );
        assert( str2 == std::get<0>(tpl2) );
        assert( j == std::get<1>(tpl2) );
    }
    {
        int i = -1, j = 1;
        X x( 3);
        std::tuple< int, X, int > tpl{ i, std::move( x), j };
        std::tuple< int, X > tpl1;
        std::tuple< X, int > tpl2;
        head( tpl1) = std::move( tpl);
        tail( tpl2) = std::move( tpl);
        assert( i == std::get<0>(tpl1) );
        assert( 3 == std::get<1>(tpl1).value );
        assert( std::get<1>(tpl1).state );
        assert( -1 == std::get<0>(tpl2).value );
        assert( ! std::get<0>(tpl2).state );
        assert( j == std::get<1>(tpl2) );
    }
    {
        int _i = 1, _j = 2, _k = 0;
        int & i = _i, & j = _j, k = _k;
        std::string _str1("abc"), _str2("xyz");
        std::string & str1 = _str1, & str2 = _str2;
        std::tuple< int &, std::string &, int & > tpl{ i, str1, j };
        std::tuple< int &, std::string & > tpl1{ k, str2 };
        std::tuple< std::string &, int & > tpl2{ str2, k };
        head( tpl1) = tpl;
        int & r1 = std::get<0>(tpl1);
        std::string & r2 = std::get<1>(tpl1);
        assert( r1 == i);
        assert( r2 == str1);
        tail( tpl2) = tpl;
        r1 = std::get<0>(tpl1);
        r2 = std::get<1>(tpl1);
        assert( r1 == i);
        assert( r2 == str1);
        std::string & r3 = std::get<0>(tpl2);
        int & r4 = std::get<1>(tpl2);
        assert( r3 == str2);
        assert( r4 == j);
    }
    {
        int i = 1, j = 2, k = 0;
        std::string str1("abc"), str2("xyz");
        std::tuple< int *, std::string *, int * > tpl{ & i, & str1, & j };
        std::tuple< int *, std::string * > tpl1{ & k, & str2 };
        std::tuple< std::string *, int * > tpl2{ & str2, & k };
        head( tpl1) = tpl;
        assert( & i == std::get<0>(tpl1) );
        assert( & k == std::get<1>(tpl2) );
        tail( tpl2) = tpl;
        assert( & i == std::get<0>(tpl1) );
        assert( & j == std::get<1>(tpl2) );
    }
    return 0;
}
