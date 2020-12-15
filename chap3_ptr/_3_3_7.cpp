#include <iostream>
#include <stdio.h>
#include <boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>

// 接口类-纯抽象基类
class Abstruct
{
public:
    virtual void f() = 0;
    virtual void g() = 0;

protected:
    virtual ~Abstruct() = default; // 只有自己及其子类才有权力析构，其他对象都无权析构
};

class Imp1 : public Abstruct
{
public:
    virtual void f()
    {
        std::cout << "Class imp1 f" << std::endl;
    }
    virtual void g()
    {
        std::cout << "Class imp1 g" << std::endl;
    }

public:
    Imp1() = default;
    virtual ~Imp1() = default;
};

// 工厂函数
boost::shared_ptr<Abstruct> create()
{
    return boost::make_shared<Imp1>();
}
int main(int argc, char *argv[])
{
    {
        auto p = create();
        p->f();
        p->g();

        // Abstruct *q = p.get();
        // delete q;       // 编译错误，析构在protected中
    }

    {
        boost::shared_ptr<FILE> fp(fopen("/home/topeet/myBoost/chap3_ptr/text1.txt", "r"), fclose);
        int i = 0;
    }
    {
        // class socket_t
        // {
        // };
        // socket_t *open_socket()
        // {
        //     std::cout << "open_socket" << std::endl;
        //     return new socket_t;
        // }
        // void close_socket(socket_t * s)
        // {
        //     std::cout << "close_socket" << std::endl;
        //     delete s;
        // }

        // socket_t *s = open_socket();
        // if (s != nullptr)
        //     boost::shared_ptr<socket_t> p(s, close_socket);
        // else
        //     return -1;
        delete nullptr;
    }
}

// struct Base1
// {
//     int base1 = 0;
//     ~Base1() { std::cout << "Base1" << std::endl; }
// };
// struct Base2
// {
//     int base2 = 0;
//     ~Base2() { std::cout << "Base2" << std::endl; }
// };
// struct A : Base1, Base2
// {
// };

// int main()
// {
//     // 不得不遇到不同接口的智能指针指向同一个对象了
//     auto ptr = new A;

//     {
//         boost::shared_ptr<Base1> ptr1((Base1 *)ptr);
//         //boost::shared_ptr<int> ptr1(new int);
//         std::cout << ptr1.use_count() << std::endl;

//         {
//             boost::shared_ptr<Base2> ptr2(ptr1, (Base2 *)(ptr));
//             std::cout << ptr2.use_count() << std::endl;
//         }
//         int i = 0;
//     }

//     {
//         auto p1 = boost::make_shared<std::pair<int, int>>(0, 1);

//         boost::shared_ptr<int> p2(p1, &p1->second);

//         assert(p1.use_count() == p2.use_count() && p1.use_count() == 2);
//     }

//     // boost::shared_ptr<Base2> ptr2((Base2 *)ptr);
//     //boost::shared_ptr<int> ptr2(ptr1);

//     //内存泄漏,ptr2已经被释放:-572662307end crash

//     //化名,ptr2未被释放:0end

//     //ptr1.reset();

//     //std::cout << ptr2->base2;

//     // std::cout << "end";

//     return 0;
// }