#include <iostream>
#include <boost/noncopyable.hpp> // First tool
// #include <boost/blank.hpp>
#include <boost/core/ignore_unused.hpp> // Second tool

// First tool  --->noncopyable
class DoNotCopy : boost::noncopyable
{
};

// Second tool  --->ignore_unused
// Method 1
int func(int x, int y) //warning: unused parameter ‘x’ [-Wunused-parameter]
{
    int i; // warning: unused variable ‘i’ [-Wunused-variable]

    //boost::ignore_unused(x, i); // 让编译器忽略，不用的参数x,i
    return y;
}
// Method 2
void func2()
{
    typedef int result_type; // warning: typedef ‘result_type’ locally defined but not used [-Wunused-local-typedefs]
    boost::ignore_unused<result_type>();
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    // First tool  --->noncopyable
    DoNotCopy d1;
    // DoNotCopy d2(d1);        // 拷贝，error

    DoNotCopy d2;
    // d2 = d1;                 // 赋值，error

    // Second tool  --->ignore_unused
}