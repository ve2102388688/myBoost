#include <iostream>
#include <cassert>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

int main(int argc, char* argv[])
{
    std::cout << std::setprecision(64);

    auto my_area = boost::math::float_constants::pi * 2 * 2;
    std::cout << "area: " << my_area << std::endl;

    using namespace boost::math::double_constants;
    auto x = root_two * root_three;
    std::cout << "root 2*3 = " << x << std::endl;
    std::cout << "root pi = " << root_pi << std::endl;
    std::cout << "pi power e = " << pi_pow_e << std::endl;

    {
        using namespace boost::math::constants;
        assert(pi<float>() == boost::math::float_constants::pi);
        assert(pi<double>() == boost::math::double_constants::pi);
    }

    {
        // 高精度100位，注意需要头文件<boost/multiprecision/cpp_dec_float.hpp>
        using namespace boost::math::constants;
        typedef boost::multiprecision::cpp_dec_float_100 float_100;             // 设置精度是100位小数
        std::cout << std::setprecision(100) << pi<float_100>() << std::endl;
    }
}
