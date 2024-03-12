#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <time.h>
#include<chrono>
#include <fstream> 
using namespace std;
using std::cout;
using std::endl;
using namespace std::chrono;
void complex()
{
    volatile size_t i = 0; // 要求编译器每次都直接读取原始内存地址，防止编译器对循环做优化
    int sizt_t = 100000000;
    vector<double> vdouble(sizt_t, 0.0);
    vector<int> vint(sizt_t, 0);
    for (i=0; i < sizt_t; ++i) {
        vdouble[i] = (double)sizt_t + 0.1234567;
        vint[i] = sizt_t+1234567;
    }
    auto start = high_resolution_clock::now();
	for (i = 0; i < sizt_t; ++i) {
		vint[i] = cos(vint[i]);
		vint[i] = sin(vint[i]);
	}
    auto stop1 = high_resolution_clock::now();
	for (i = 0; i < sizt_t; ++i) {
		vdouble[i] = cos(vdouble[i]);
		vdouble[i] = sin(vdouble[i]);
	}
    auto stop2 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start);
    auto duration2 = duration_cast<milliseconds>(stop2 - stop1);
	cout << "int cos and sin time: " << duration1.count() << " ms" << endl;
	cout << "double cos and sin time: "<< duration2.count() << " ms" << endl;
}
void ReadWrite()
{
	int loop_size = 1000000;
	int data_int = 1;
	double data_double = 0.1018;
	auto s1 = high_resolution_clock::now();
	ofstream fout_int("d:\\inttest.txt");
	for (int i = 0; i < loop_size; i++) {
		fout_int << data_int << endl;
	}
	fout_int.close();
	auto s2 = high_resolution_clock::now();
	ifstream fin_int("d:\\inttest.txt");
	for (int i = 0; i < loop_size; i++) {
		fin_int >> data_int;
	}
	fin_int.close();
	auto s3 = high_resolution_clock::now();
	ofstream fout_double("d:\\doubletest.txt");
	fout_double.setf(std::ios::fixed);
	fout_double.precision(14);
	for (int i = 0; i < loop_size; i++) {
		fout_double << data_double << endl;
	}
	fout_double.close();
	auto s4 = high_resolution_clock::now();
	ifstream fin_double("d:\\doubletest.txt");
	for (int i = 0; i < loop_size; i++) {
		fin_double >> data_double;
	}
	fin_double.close();
	auto s5 = high_resolution_clock::now();
	auto duration1 = duration_cast<milliseconds>(s2 - s1);
	auto duration2 = duration_cast<milliseconds>(s3 - s2);
	auto duration3 = duration_cast<milliseconds>(s4 - s3);
	auto duration4 = duration_cast<milliseconds>(s5 - s4);
	cout << "int write time: "<< duration1.count() << " ms" << endl;
	cout << "int read time: "<< duration2.count() << " ms" << endl;
	cout << "double write time: "<< duration3.count() << " ms" << endl;
	cout << "double read time: "<< duration4.count() << " ms" << endl;
}
int main()
{
	cout << "Testing the performance of complex fuction operations..." << endl;
	complex();
	cout << "Testing the performance of reading and writing hard disk..." << endl;
	ReadWrite();
	return 0;
}


