#include <stdio.h>

int integer_operations();
double floating_point_operations();
void multithreading_operations();

int main() {
    printf("Running CPU benchmarks...\n");

    // 整型运算测试
    integer_operations();

    // 浮点型运算测试
    floating_point_operations();

    // 多线程测试
    multithreading_operations();

    printf("CPU benchmarks completed.\n");
    return 0;
}