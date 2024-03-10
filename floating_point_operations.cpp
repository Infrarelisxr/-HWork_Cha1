#include <iostream>
#include<chrono>
using namespace std;
using namespace std::chrono; 
double floating_point_operations() {
    volatile double result = 1.0;
    const long long numIterations = 1000000000; // 运算重复次数
    auto start = high_resolution_clock::now();
    for (long long i = 0; i < numIterations; ++i) {
        result /= (double)i / 5.0 + 1.0;
    }
    // 记录结束时间
    auto stop = high_resolution_clock::now();
    // 计算持续时间
    auto duration = duration_cast<milliseconds>(stop - start);
    // 输出执行时间
    cout << "浮点型运算测试执行时间: "
        << duration.count() << " ms" << endl;
    return result;
}