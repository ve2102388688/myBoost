#include <iostream>
#include <vector>
#include <cassert>
#include <boost/operators.hpp>
#include <boost/assign.hpp>

class Point : private boost::less_than_comparable<Point>
{
private:
    int m_a, m_b, m_c;

public:
    explicit Point(int a = 0, int b = 0, int c = 0) : m_a(a), m_b(b), m_c(c){};

    // >、>=、<=自动实现
    friend bool operator<(const Point &lhs, const Point &rhs)
    {
        return (lhs.m_a * lhs.m_a + lhs.m_b * lhs.m_b + lhs.m_c * lhs.m_c <
                rhs.m_a * rhs.m_a + rhs.m_b * rhs.m_b + rhs.m_c * rhs.m_c);
    }
};


// -----------------------------------------------Point2 和 Point3功能一致-----------------------------------------------
// 基类链方式--将多重继承改成单重继承，改变多重继承的不确定性
class Point2 : private 
        boost::less_than_comparable<Point2,         // 小于操作，需要实现<，自动实现>、>=、<=
        boost::equality_comparable<Point2,          // 等于操作，需要实现==，自动实现!=
        boost::addable<Point2,                      // 加法操作，需要实现+=，自动实现+
        boost::subtractable<Point2                  // 减法操作，需要实现-=，自动实现-
        >>>>
{
private:
    int m_a, m_b, m_c;

public:
    explicit Point2(int a = 0, int b = 0, int c = 0) : m_a(a), m_b(b), m_c(c){};

    // >、>=、<=自动实现
    friend bool operator<(const Point2 &lhs, const Point2 &rhs)
    {
        return (lhs.m_a * lhs.m_a + lhs.m_b * lhs.m_b + lhs.m_c * lhs.m_c <
                rhs.m_a * rhs.m_a + rhs.m_b * rhs.m_b + rhs.m_c * rhs.m_c);
    }

    // !=自动实现
    friend bool operator==(const Point2 &lhs, const Point2 &rhs)
    {
        return lhs.m_a == rhs.m_a && lhs.m_b == rhs.m_b && lhs.m_c == rhs.m_c;
    }

    // +自动实现
    Point2 operator+=(const Point2 &rhs)
    {
        m_a += rhs.m_a;
        m_b += rhs.m_b;
        m_c += rhs.m_c;
        return *this;
    }
    // -自动实现
    Point2 operator-=(const Point2 &rhs)
    {
        m_a -= rhs.m_a;
        m_b -= rhs.m_b;
        m_c -= rhs.m_c;
        return *this;
    }

    void print() const{
        std::cout << m_a << ", " << m_b << ", " << m_c << std::endl;
    }
};


class Point3 : private 
    boost::totally_ordered<Point3,  // 全序比较，less_than_comparable + equality_comparable
    boost::additive<Point3           // 可加减，addable + subtractable
    >>
{
private:
    int m_a, m_b, m_c;

public:
    explicit Point3(int a = 0, int b = 0, int c = 0) : m_a(a), m_b(b), m_c(c){};

    // >、>=、<=自动实现
    friend bool operator<(const Point3 &lhs, const Point3 &rhs)
    {
        return (lhs.m_a * lhs.m_a + lhs.m_b * lhs.m_b + lhs.m_c * lhs.m_c <
                rhs.m_a * rhs.m_a + rhs.m_b * rhs.m_b + rhs.m_c * rhs.m_c);
    }

    // !=自动实现
    friend bool operator==(const Point3 &lhs, const Point3 &rhs)
    {
        return lhs.m_a == rhs.m_a && lhs.m_b == rhs.m_b && lhs.m_c == rhs.m_c;
    }

    // +自动实现
    Point3& operator+=(const Point3 &rhs)
    {
        m_a += rhs.m_a;
        m_b += rhs.m_b;
        m_c += rhs.m_c;
        return *this;
    }
    // -自动实现
    Point3& operator-=(const Point3 &rhs)
    {
        m_a -= rhs.m_a;
        m_b -= rhs.m_b;
        m_c -= rhs.m_c;
        return *this;
    }

    void print() const{
        std::cout << m_a << ", " << m_b << ", " << m_c << std::endl;
    }
};

class Point4 : private 
    boost::totally_ordered<Point4,  // 全序比较，less_than_comparable + equality_comparable
    boost::addable1<Point4,         
    boost::addable2<Point4, int
    >>>
{
private:
    int m_a, m_b, m_c;

public:
    explicit Point4(int a = 0, int b = 0, int c = 0) : m_a(a), m_b(b), m_c(c){};
    
    
    // >、>=、<=自动实现
    friend bool operator<(const Point4 &lhs, const Point4 &rhs)
    {
        return (lhs.m_a * lhs.m_a + lhs.m_b * lhs.m_b + lhs.m_c * lhs.m_c <
                rhs.m_a * rhs.m_a + rhs.m_b * rhs.m_b + rhs.m_c * rhs.m_c);
    }

    // !=自动实现
    friend bool operator==(const Point4 &lhs, const Point4 &rhs)
    {
        return lhs.m_a == rhs.m_a && lhs.m_b == rhs.m_b && lhs.m_c == rhs.m_c;
    }

    // +自动实现
    Point4& operator+=(const Point4 &rhs)
    {
        m_a += rhs.m_a;
        m_b += rhs.m_b;
        m_c += rhs.m_c;
        return *this;
    }

    // +自动实现,这里是两种类型
    Point4& operator+=(const int &rhs)
    {
        m_a += rhs;
        m_b += rhs;
        m_c += rhs;
        return *this;
    }

    void print() const{
        std::cout << m_a << ", " << m_b << ", " << m_c << std::endl;
    }
};

int main(int argc, char *argv[])
{
    // test1
    Point p1(8, 4, 3), p2(2, 5, 7);
    assert(p1 > p2);

    // test2
    {
        Point3 p0, p1(8, 4, 3), p2(2, 5, 7);
        (p1 + p2).print();                  // operator+
        (p1 - p2).print();                  // operator+
        assert((p1 - p1) == p0);            // operator==
        
        std::vector<Point3> v = (boost::assign::list_of(p0), p1, p2);
        auto pos = std::find(v.begin(), v.end(), p2);       // operator==
        pos->print();
    }

    {
        // 相加的类型不一致
        Point4 p1(8, 4, 3);
        (p1 + 5).print();
    }
}