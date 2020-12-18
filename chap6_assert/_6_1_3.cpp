#define BOOST_ENABLE_ASSERT_HANDLER
#include <iostream>
#include <boost/assert.hpp>
#include <boost/format.hpp>

namespace boost{
    void assertion_failed(char const * expr, char const * function, char const * file, long line)  // user defined
    {
        boost::format fmt("Assertion failed!\nExpression: %s\n"
                    "Function: %s\nFile: %s\nLine: %ld\n\n");
        fmt % expr % function % file % line;
        std::cout << fmt;
    }
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line) // user defined
    {
        boost::format fmt("Assertion failed!\nExpression: %s\n"
                          "Function: %s\nFile: %s\nLine: %ld\n"
                          "Msg: %s\n\n");
        fmt % expr % function % file % line % msg;
        std::cout << fmt;
    }
}

double fun(int x)
{
    // 使用宏失效
    BOOST_ASSERT(x != 0);
    return 1.0 / x;
}


int main(int argc, char* argv[])
{
    {
        BOOST_ASSERT(16 == 0x10);
        fun(0);
    }
}