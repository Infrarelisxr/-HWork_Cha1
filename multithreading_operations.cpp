#include <iostream>
#include<chrono>
#include <thread>
#include <vector>
using namespace std;
using namespace std::chrono;
void thread_function() {
    const long long numIterations = 1000000000;
    volatile int result = 1;
    for (long long i = 1; i < numIterations; i++) {
        result *= i % 5 + 1;
    }
}
void multithreading_operations() {
    vector<thread> threads;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 14; i++) { // ����������14��CPU��
        threads.push_back(thread(thread_function));
    }
    for (auto& t : threads) {
        t.join();
    }
    // ��¼����ʱ��
    auto stop = high_resolution_clock::now();
    // �������ʱ��
    auto duration = duration_cast<milliseconds>(stop - start);
    // ���ִ��ʱ��
    cout << "���̲߳���ִ��ʱ��: "
        << duration.count() << " ms" << endl;
}