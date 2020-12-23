#include <iostream>
#include <boost/crc.hpp>

int main(int argc, char* argv[])
{
    boost::crc_32_type crc32;
    std::cout << crc32.checksum() << std::endl;                 // 空的也可以计算，值为0

    crc32.process_byte('a');
    std::cout << std::hex << crc32.checksum() << std::endl;     // 计算一个字节

    crc32.process_bytes("1234567890", 10);
    std::cout << crc32.checksum() << std::endl;                 // 计算10个字节

    char str[] = "1234567890";
    crc32.reset();                                              // 重置结果，计算结果为0
    crc32.process_block(str, str + 10);                         // 通过区间方式输入数据
    std::cout << crc32.checksum() << std::endl;

    // 重载operator()
    std::cout << crc32() << std::endl;
    {
        crc32.reset();                                              // 重置结果，计算结果为0
        std::string str2 = "1234567890";
        std::cout << std::for_each(str2.begin(), str2.end(), crc32)() << std::endl; // 这里会建立一个临时对象
        std::cout << crc32() << std::endl;                          // 注意这个是0
    }
}
