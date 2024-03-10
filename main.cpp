#include <stdio.h>

int integer_operations();
double floating_point_operations();
void multithreading_operations();

int main() {
    printf("Running CPU benchmarks...\n");

    // �����������
    integer_operations();

    // �������������
    floating_point_operations();

    // ���̲߳���
    multithreading_operations();

    printf("CPU benchmarks completed.\n");
    return 0;
}