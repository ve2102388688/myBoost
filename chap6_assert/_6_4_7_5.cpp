// #define BOOST_TEST_MAIN                 // 必须定义主测试套件，必须位于头文件之前
#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/mpl/list.hpp>

BOOST_AUTO_TEST_SUITE(s_lexical_cast)

typedef boost::mpl::list<short, int, long> types;

BOOST_AUTO_TEST_CASE_TEMPLATE(T_lexical_cast, T, types)
{
    T n(20);
    BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(n), "20");
}

BOOST_AUTO_TEST_SUITE_END()
