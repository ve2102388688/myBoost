#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>     // test的头文件
#include <boost/smart_ptr.hpp>

// 测试套件的开始
BOOST_AUTO_TEST_SUITE(s_smart_ptr)

// 测试用例1
BOOST_AUTO_TEST_CASE(t_scoped_ptr)      // 测试用例1 t_scoped_ptr
{
    boost::scoped_ptr<int> p(new int(874));
    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(*p, 874);
}

// 测试用例2
BOOST_AUTO_TEST_CASE(t_shared_ptr)      // 测试用例2 t_shared_ptr
{
    boost::shared_ptr<int> p(new int(100));

    BOOST_CHECK(p);
    BOOST_CHECK_EQUAL(*p, 100);
    BOOST_CHECK_EQUAL(p.use_count(), 1);

    boost::shared_ptr<int> p2 = p;
    BOOST_CHECK_EQUAL(p2, p);
    BOOST_CHECK_EQUAL(p.use_count(), 3);    // 预设一个错误
}

BOOST_AUTO_TEST_SUITE_END()