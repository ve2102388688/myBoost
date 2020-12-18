// #define BOOST_TEST_MAIN                 // 必须定义主测试套件，必须位于头文件之前
#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>
#include <boost/smart_ptr.hpp>

BOOST_AUTO_TEST_SUITE(s_decorator, *boost::unit_test::label("decorator"))

BOOST_AUTO_TEST_CASE(t_case1, *boost::unit_test::label("low") *boost::unit_test::description("a normal test case"))
{
    
}

BOOST_AUTO_TEST_CASE(t_case2, *boost::unit_test::label("low"))
{

}

// 允许1个断言失败
BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES(t_case3, 1)

BOOST_TEST_DECORATOR(*boost::unit_test::label("high"))
BOOST_AUTO_TEST_CASE(t_case3)
{
    boost::scoped_ptr<int> p(new int(874));
    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(*p, 875);    
}

BOOST_AUTO_TEST_SUITE_END()
