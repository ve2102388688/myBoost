#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <boost/operators.hpp>

// dereferenceable
// 模板参数一定要MySmartPtr<T>
template <typename T>
class MySmartPtr : public boost::dereferenceable<MySmartPtr<T>, T*>     // 必须公共继承
{
private:
    T *m_p;

public:
    MySmartPtr(T* p) : m_p(p) {}
    ~MySmartPtr() { delete m_p; }

    // 实现operator*，operator->也可以用了
    T& operator*() const{
        return *m_p;
    }
};

// indexable
template <typename T>
class MySmartArray : public boost::indexable<MySmartArray<T>, int, T&>
{
private:
    T *m_p;

public:
    typedef MySmartArray<T> this_type;
    typedef T*              iter_type;

    MySmartArray(T* p) : m_p(p) {}
    ~MySmartArray() { delete[] m_p; }

    // 必须提前实现operator+
    friend iter_type operator+(const this_type& a, int n){
        return a.m_p + n;
    }
};


int main(int argc, char *argv[])
{
    // ->
    MySmartPtr<std::string> p(new std::string("123"));
    assert(p->size() == 3);

    // []
    MySmartArray<double> ma(new double[10]);
    ma[0] = 10;
    *(ma + 1) = 5;
    std::cout << ma[0] << ", " << ma[1] << std::endl;
}