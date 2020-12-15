#include <iostream>
#include <boost/lexical_cast.hpp>

template <typename T>
bool num_vaild(const char* str)
{
    T tmp;
    boost::conversion::try_lexical_convert(str, tmp);
}
int main(int argc, char* argv[])
{
    {
        // 字符串到数字
        int x = boost::lexical_cast<int>("100");
        float y = boost::lexical_cast<float>("3.14159E5");
        double z = boost::lexical_cast<double>("3.1414,z",5);
        std::cout << x << " " << y << " " << z << std::endl;
    }

    {
        // 数字到字符串
        std::string str = boost::lexical_cast<std::string>(456);
        std::string str1 = boost::lexical_cast<std::string>(0.618);
        std::cout << str << " " << str1 << std::endl;

        std::cout << boost::lexical_cast<bool>("1") << std::endl;
    }

    {
        // 验证失败
        assert(!num_vaild<double>("hello"));
    }
}



