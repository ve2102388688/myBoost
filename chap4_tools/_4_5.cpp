#include <iostream>
#include <cassert>
#include <boost/logic/tribool.hpp>

BOOST_TRIBOOL_THIRD_STATE(unknow);

int main(int argc, char *argv[])
{
    boost::tribool tb();

    boost::tribool tb2(unknow);
    assert(unknow(tb2));
}