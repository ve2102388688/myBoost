#include <iostream>
#include <vector>
#include <boost/optional.hpp>

boost::optional<double> reciprocal(int x)
{
    return boost::optional<double>(x != 0, 1.0 / x); // 满足不为0，则求倒数
}

int main(int argc, char *argv[])
{
    // 创建空对象的两种方式
    boost::optional<int> op0;
    boost::optional<int> op1(boost::none);
    assert(op0 == op1 && !op0);

    // 给它默认值，如果未初始化就是默认值，否则是初始化值
    assert(op1.value_or(255) == 255); // 显然op1没有初始化，所以和默认值相等
    // 未初始化，返回f()，即value_or_eval(f())
    std::cout << op1.value_or_eval([]() { return 80; }) << std::endl; // 显然op1没有初始化，所以调用f()

    // 初始化
    boost::optional<std::string> ops("test");
    std::cout << *ops << std::endl;
    std::cout << ops.get() << std::endl;

    // 就地创建一个字符串，这里只用前三个构造
    ops.emplace("monado", 3);
    assert(*ops == "mon");

    // 复杂类型放进optional
    std::vector<int> v(10);
    boost::optional<std::vector<int> &> opv(v);
    assert(opv); // bool转型
    opv->push_back(5);
    assert(opv->size() == 11); // 箭头直接访问

    // 置为未初始化状态
    opv = boost::none;
    assert(!opv);

    // 按条件初始化
    {
        boost::optional<double> d = reciprocal(2);
        if (d)
        {
            std::cout << *d << std::endl;
        }

        boost::optional<double> d1 = reciprocal(0);
        if (!d1)
        {
            std::cout << "no result" << std::endl;
        }
    }

    // make_optional自动创建optional类型
    auto x = boost::make_optional(5);
    assert(*x == 5);
    auto y = boost::make_optional<double>((*x > 10), 1.0);
}