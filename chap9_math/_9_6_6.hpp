#ifndef TURE_RANDOM_H_
#define TURE_RANDOM_H_
#include <boost/random.hpp>
#include <iostream>
#include <boost/nondet_random.hpp>

// boost::random_device的真正的实现
class boost::random_device::impl
{
private:
    boost::mt19937 m_rng;       // 这里用的是mt19937，可以换成rand48等

public:
    impl() : m_rng(time(0)) { std::cout << "random_device::impl ctor.\n"; }  // 用时间初始化
    ~impl() { std::cout << "random_device::impl dtor.\n"; }

    unsigned int operator()(){
        return m_rng();
    }
};

// 定义boost::random_device下未声明的五个函数，这里只定义4个
boost::random_device::random_device() : pimpl(new impl) {}

boost::random_device::~random_device() { delete pimpl; }        // 原来用的原始指针，这里必须手动删除

double boost::random_device::entropy() const { return 10.0; }

unsigned int boost::random_device::operator()() { return (*pimpl)(); }


#endif