#include <iostream>
#include <boost/integer_traits.hpp>
#include <boost/cstdint.hpp> // 标准整形类，基于1999年的C语言标准
#include <boost/integer.hpp>

#include <boost/type_index.hpp> // typeindex
#include <boost/format.hpp>

template <typename T>
std::string type_name()
{
    return boost::typeindex::type_id<T>().pretty_name();
}

int main(int argc, char *argv[])
{
    {
        // #line 200 "main.cpp"
        // #error "this is error"
        char s[15] = "my"; // 必须大于实际的输出
        std::cout << tmpnam(s) << std::endl;
        //tmpfile()
        // 整数特征integer_traits
        std::cout << boost::integer_traits<int>::const_max << std::endl;
        std::cout << boost::integer_traits<long>::const_max << std::endl;
        std::cout << boost::integer_traits<long>::is_signed << std::endl;
    }

    {
        // 标准类型的类型
        uint8_t u8 = 255;
        int_fast16_t i16 = 32000;
        int_least32_t i32 = 32000;
        uintmax_t um = 64000;

        // 输出各整数的大小和值
        std::cout << "u8    :" << sizeof(u8) << "  v = " << (short)u8 << "\tMAX: " << (short)std::numeric_limits<uint8_t>::max() << std::endl; // 需要转换一下，不然输出的是ASCII
        std::cout << "i16    :" << sizeof(i16) << "  v = " << i16 << "\tMAX: " << std::numeric_limits<int_fast16_t>::max() << std::endl;
        std::cout << "i32    :" << sizeof(i32) << "  v = " << i32 << "\tMAX: " << std::numeric_limits<int_least32_t>::max() << std::endl;
        std::cout << "um    :" << sizeof(um) << "  v = " << um << "\tMAX: " << std::numeric_limits<uintmax_t>::max() << std::endl;
    }

    {
        boost::format fmt("size: %s, size=%dbit.\n");
        typedef boost::uint_t<15>::fast u15; // 需要容纳15bit的最快整数，实际上分配16bit
        std::cout << fmt % type_name<u15>() % (sizeof(u15) * 8);

        typedef boost::int_max_value_t<32700>::fast i32700; // 需要容纳32700的最快整数，实际上分配16bit
        std::cout << fmt % type_name<i32700>() % (sizeof(i32700) * 8);

        typedef boost::int_min_value_t<-33000>::fast i33000; // 需要容纳-33000的最快整数，实际上分配32bit
        std::cout << fmt % type_name<i33000>() % (sizeof(i33000) * 8);

        typedef boost::uint_value_t<33000>::fast u33000; // 需要容纳33000的最快整数，实际上分配16bit
        std::cout << fmt % type_name<u33000>() % (sizeof(u33000) * 8);
    }
}
