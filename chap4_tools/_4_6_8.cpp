#include <iostream>
#include <cassert>
#include <boost/operators.hpp>
#include <boost/core/explicit_operator_bool.hpp>    // BOOST_EXPLICIT_OPERATOR_BOOL

struct DemoA
{
    BOOST_EXPLICIT_OPERATOR_BOOL()
    bool operator!() const{
        return false;
    }
};

struct DemoB
{
    BOOST_EXPLICIT_OPERATOR_BOOL()

    bool operator!() const{
        return true;
    }
};

int main(int argc, char *argv[])
{
    DemoA a;
    DemoB b;

    assert(a && !b);
    //a > b;
}