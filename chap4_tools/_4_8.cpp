#include <iostream>
#include <vector>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>   // 生成算法
#include <boost/uuid/uuid_io.hpp>

// 增强型UUID
class MyUuid : public boost::uuids::uuid
{
private:
    static boost::uuids::random_generator& rand_uuid() {        // 随机数生成器
        static boost::uuids::random_generator gen;
        return gen;
    }
    static boost::uuids::string_generator& string_uuid() {        // 字符串生成器
        static boost::uuids::string_generator gen;
        return gen;
    }

public:
    MyUuid() : boost::uuids::uuid(rand_uuid()()){}                  // 默认构造，生成随机UUID
    MyUuid(int) : boost::uuids::uuid(boost::uuids::nil_uuid()){}    // 生成UUID--0
    MyUuid(const char *str) : boost::uuids::uuid(string_uuid()(str)) {} // 字符串构造函数
    // 名字生成器构造函数，在字符串基础上得来的
    MyUuid(const boost::uuids::uuid &u, const char *str) : boost::uuids::uuid(boost::uuids::name_generator(u)(str)) {}
    explicit MyUuid(const boost::uuids::uuid &u) : boost::uuids::uuid(u) {} // 拷贝构造函数
    
    // 转换成uuid
    operator boost::uuids::uuid(){
        return static_cast<boost::uuids::uuid &>(*this);
    }
    operator boost::uuids::uuid() const{
        return static_cast<const boost::uuids::uuid &>(*this);
    }
};


int main(int argc, char *argv[])
{
    using namespace boost::uuids;

    {
        uuid u;
        assert(u.size() == 16);

        std::vector<unsigned char> v(16, 7);
        std::copy(v.begin(), v.end(), u.begin());
        std::cout << u << std::endl;

        std::fill_n(u.data + 10, 6, 8);
        std::cout << u << std::endl;

        assert(u.variant() == u.variant_ncs);       // NCS backward compatibiliity
        assert(u.version() == u.version_unknown);   // 生成的算法未知

        std::memset(u.data, 0, 16);
        assert(u.is_nil());                         // uuid的判空
    }

    {
        // 比较操作是字典顺序
        uuid u1;
        uuid u2;

        std::fill_n(u1.data, 16, 0xab);
        std::fill_n(u2.data, 16, 0x10);
        assert(u1 > u2 && u1 != u2);
    }

    {
        // Nil只能生成空
        uuid u = nil_generator()();
        assert(u.is_nil());                         // uuid的判空
        uuid u1 = nil_uuid();
        assert(u1.is_nil());                         // uuid的判空
    }

    {
        // string_generator
        string_generator sgen;
        uuid u1 = sgen("0123456789abcdef0123456789abcdef");
        std::cout << u1 << std::endl;

        uuid u2 = sgen("01234567-89ab-cdef-0123-456789abcdef");
        std::cout << u2 << std::endl;

        std::cout << boost::uuids::to_string(u2) << std::endl;

        uuid u3 = sgen(L"{01234567-89ab-cdef-0123-456789abcdef}");
        std::cout << u3 << std::endl;
    }

    {
        // name_generator,基于SHA1算法，需要提前给定基准uuid
        string_generator sgen;
        uuid name_gener = sgen("0123456789abcdef0123456789abcdef");

        name_generator ngen(name_gener);
        uuid u1 = ngen("mario");        // 为名字mario生成uuid
        assert(!u1.is_nil() && u1.version() == uuid::version_name_based_sha1);
    }

    {
        random_generator rgen;      // 随机生成器
        uuid u1 = rgen();
        assert(u1.version() == uuid::version_random_number_based);
    }

    {
        // 自定义生成器
        std::cout << "*********" << std::endl;
        MyUuid u0 = 0;                                          // 为0
        assert(u0.is_nil());

        MyUuid u1, u2;                                          // 两个随机UUID
        std::cout << u1 << std::endl;
        std::cout << u2 << std::endl;

        MyUuid u3("01234567-89ab-cdef-0123-456789abcdef");      // 字符串生成
        std::cout << u3 << std::endl;

        std::cout << MyUuid(u3, "my test") << std::endl;        // 名字生成

    }
}
