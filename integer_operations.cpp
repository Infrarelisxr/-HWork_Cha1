#include <iostream>
#include<chrono>
using namespace std;
using namespace std::chrono;
//int main()
//{
//    auto start = high_resolution_clock::now();
//    const long long numIterations = 100000000; // 运算重复次数
//    volatile int result=1; // 使用volatile防止编译器优化
//    for (long long i = 0; i < numIterations; ++i) {
//        result += i;  // 加法
//        result -= i;  // 减法
//        result *= i;  // 乘法
//        result /= (i > 1 ? i : 1); // 除法，避免除以零
//    }
//    // 记录结束时间
//    auto stop = high_resolution_clock::now();
//
//    // 计算持续时间
//    auto duration = duration_cast<milliseconds>(stop - start);
//
//    // 输出执行时间
//    cout << "\n程序执行时间: "
//        << duration.count() << " ms" << endl;
//    return 0;
//}
int integer_operations() {
    auto start = high_resolution_clock::now();
    const long long numIterations = 1000000000; // 运算重复次数
    volatile int result=1; // 使用volatile防止编译器优化
    for (long long i = 0; i < numIterations; ++i) {
        result += i;  // 加法
        result -= i;  // 减法
        result *= i;  // 乘法
        result /= (i > 1 ? i : 1); // 除法，避免除以零
    }
    // 记录结束时间
    auto stop = high_resolution_clock::now();
    // 计算持续时间
    auto duration = duration_cast<milliseconds>(stop - start);
    // 输出执行时间
    cout << "整型运算测试执行时间: "
        << duration.count() << " ms" << endl;
    return result;
}
