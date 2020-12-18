#include <iostream>
#include <type_traits>
#include <boost/core/lightweight_test_trait.hpp>

int main(int argc, char* argv[])
{
    using namespace boost;
    // 测试元编程
    BOOST_TEST_TRAIT_TRUE((is_integral<int>));
    //BOOST_TEST_TRAIT_FALSE((boost::is_function<int>));

    return boost::report_errors();
}
