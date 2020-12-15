#include <iostream>
#include <boost/pool/pool.hpp>

int main(int argc, char *argv[])
{
    boost::pool<> p(sizeof(double));          // 分配一个可以装下int的内存池
    int *p1 = static_cast<int *>(p.malloc()); // 必须将void*转换成所需类型，才能使用

    *p1 = 100; // 直接使用，不用考虑释放问题
    std::cout << *p1 << std::endl;
    std::cout << "get_requested_size(): " << p.get_requested_size() << std::endl;

    p.free(p1);
    for (int i = 0; i < 10; ++i)
        p.ordered_malloc(10); // 连续分配

    return 0;
}