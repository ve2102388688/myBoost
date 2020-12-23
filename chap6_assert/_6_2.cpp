#include <iostream>
#include <boost/static_assert.hpp>

template <typename T>
T my_min(T a, T b)
{
    BOOST_STATIC_ASSERT_MSG(sizeof(T) < sizeof(int), "only short or char");
    return a < b ? a : b;
}

namespace my_space{
    class empty_class{
        BOOST_STATIC_ASSERT_MSG(sizeof(int) >= 4, "for 32 bit");
    };
    BOOST_STATIC_ASSERT_MSG(sizeof(empty_class) == 1);
} // namespace my_space


int main(int argc, char* argv[])
{
    {
        // BOOST_STATIC_ASSERT_MSG(16 == 0x10, "not equal");
        std::cout << my_min((short)1, (short)3) << std::endl;
        std::cout << my_min((long)1, (long)3) << std::endl;
    }
}