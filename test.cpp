// #include <boost/version.hpp>
// #include <boost/config.hpp>
// #include <iostream>

// // int main(int argc, char *argv[])
// // {
// //     std::cout << BOOST_VERSION << std::endl;     // Boost版本号
// //     std::cout << BOOST_LIB_VERSION << std::endl; // Boost版本号
// //     std::cout << BOOST_PLATFORM << std::endl;    // 操作系统
// //     std::cout << BOOST_COMPILER << std::endl;    // 编译器
// //     std::cout << BOOST_STDLIB << std::endl;      // 标准库

// //     // int(*a)[3] = new int[2][3];
// //     // if (a == nullptr)
// //     //     return 0;

// //     // if (a == nullptr)
// //     //     delete[] a;

// //     auto array = new double[3][5];

// //     delete[] array;
// // }
// using namespace std;

// int main()
// {
//     char buffer[512]; //chunk of memory内存池
//     int *p1, *p2, *p3, *p4;
//     //常规new:
//     p1 = new int[10];
//     //定位new:
//     p2 = new (buffer) int[10];
//     for (int i = 0; i < 10; ++i)
//         p1[i] = p2[i] = 20 - i;
//     cout << "p1 = " << p1 << endl;                 //常规new指向的地址
//     cout << "buffer = " << (void *)buffer << endl; //内存池地址
//     cout << "p2 = " << p2 << endl;                 //定位new指向的地址
//     cout << "p2[0] = " << p2[0] << endl;
//     delete[] p1;
//     p3 = new (buffer) int;
//     *p3 = 1;
//     cout << "p3 = " << p3 << endl;
//     cout << "p3[0] = " << *p3 << endl;
//     p4 = new (buffer + 10 * sizeof(int)) int;
//     cout << "p4 = " << p4 << endl;
//     return 0;
// }

// #include <iostream>

// struct c
// {
//     int a;
//     int b;
// } c;
// typedef struct c Data;

// int main()
// {
//     const Data a1[3] = {{1, 2}, {3, 4}, {5, 6}};
//     return 0;
// }

#include <stdio.h>
#include <math.h>
#include <time.h>

#define MYREPLACE(dir) #dir "/%s"        // # 替换
#define MYCONCAT(x,y) x ## y ## l        // ## 连接

int main()
{
    {
        printf("%s\n", MYREPLACE(/usr/local));
        printf("%d\n", MYCONCAT(1, 2));
        printf("%c\n", '??=');                  // 三字符序列，一共9个
    }

    {
        char s[30];
        printf("%s\n", tmpnam(s));                        // 生成临时文件名
    }

    {
        time_t t = time(0);
        printf("%s\n", ctime(&t));                      // 输出当前时间，注意，已经localtime了
    }
#line 100 "main.cpp"    //指定当前行是100，更改文件名为main.cpp，用于调试，之前的行号没有影响
// #error "This is a fatal error, complier termination"    // 终止编译
    {
        perror("This is a error");                      // 输出错误
        printf("ERROR information, File: %s, Line: %d, Date: %s, Time: %s\n", __FILE__, __LINE__, __DATE__, __TIME__);
        printf("%d\n", __STDC__);                       // 输出1 准寻标准
    }

    printf("%f\n", fmod(3.0,2.0));                      // 求解3.0/2.0的余数，答案是1.0

    {
        double integer;
        double decimal = modf(3.5, &integer);           // 3.5 = 3 + 0.5(3.5 = integer+decimal)
        printf("%f, %f\n", integer, decimal);
    }

    {
        printf("%f\n", ldexp(1.5, 3));                  // 计算y = x*2^exp
    }
    
    {
        double y = 12.0;
        int exp;
        double x = frexp(y, &exp);
        printf("%f, %d\n", x, exp);                     // y = x*2^exp,已知y求解x和exp,其中x只能在[0.5,1]
    }

    {
        div_t res;
        res = div(3,2);
        printf("%d, %d\n", res.quot, res.rem);          // 5/3的商和余数
    }

    {
        system("ls");                                   // 执行命令
        printf("envirnoment: %s\n", getenv("PATH"));    // 获得环境变量的值
    }
}