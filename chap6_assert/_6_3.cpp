#include <iostream>
#include <boost/core/lightweight_test.hpp>
#include <boost/smart_ptr.hpp>

int main(int argc, char* argv[])
{
    {
        // 一个简单的测试用例
        boost::shared_ptr<int> p = boost::make_shared<int>(10);

        BOOST_TEST(*p == 10);
        BOOST_TEST(p.unique());
        BOOST_TEST_NOT(!p);
        BOOST_TEST_EQ(p.use_count(), 1);
        BOOST_TEST_NE(*p, 20);

        p.reset();
        //BOOST_TEST_THROWS(p, std::logic_error);
        //BOOST_ERROR("ERROR ACCURED!!!");
    }
    //boost::report_errors();
    return 0;
}