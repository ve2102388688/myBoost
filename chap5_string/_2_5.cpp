#include <iostream>
#include <boost/format.hpp>
#include <iomanip>

int main(int argc, char* argv[])
{
    {
        std::cout << boost::format("%s: %d+%d=%d\n") % "sum" % 1 % 2 % (1 + 2);

        boost::format fmt("(%1% + %2%) * %2% = %3%\n");
        fmt %2 %5;
        fmt %((2+5)*5);
        std::cout << fmt.str();
    }

    {
        boost::format fmt("%|05d|\t%-8.3f\t%10s\t%03X\n");
        std::cout << fmt % 62 % 2.2306 % "123456789" % 48;
    }

    {
        using boost::io::group;

        boost::format fmt("%1% %2% %3% %2% %1% \n");
        std::cout << fmt % 5 % 6 % 7;

        fmt.bind_arg(2, 10);        // 第二个参数10
        std::cout << fmt % 1 % 2;   // 跳过第二号！！！

        fmt.clear();                // 绑定的不发生改变
        std::cout << fmt % group(std::showbase, std::oct, 111) % 333;

        fmt.clear_binds();          // 清除所有的绑定
        fmt.modify_item(1, group(std::showbase,std::hex,std::right,std::setw(8),std::setfill('*')));    // 不足用*填充
        std::cout << fmt % 49 % 20 % 100;   // ****0x31 20 100 20 49
    }
}