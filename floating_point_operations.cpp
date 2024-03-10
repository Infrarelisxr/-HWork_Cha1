#include <iostream>
#include<chrono>
using namespace std;
using namespace std::chrono; 
double floating_point_operations() {
    volatile double result = 1.0;
    const long long numIterations = 1000000000; // �����ظ�����
    auto start = high_resolution_clock::now();
    for (long long i = 0; i < numIterations; ++i) {
        result /= (double)i / 5.0 + 1.0;
    }
    // ��¼����ʱ��
    auto stop = high_resolution_clock::now();
    // �������ʱ��
    auto duration = duration_cast<milliseconds>(stop - start);
    // ���ִ��ʱ��
    cout << "�������������ִ��ʱ��: "
        << duration.count() << " ms" << endl;
    return result;
}