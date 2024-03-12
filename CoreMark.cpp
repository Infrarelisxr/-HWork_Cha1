/*The purpose of this test is to bench mark a computer's ability to complete
matrix multiplication in interger and floating point.

We initialy sample the cpu to figure out the maximum amount of thread that is supported
thereafter we will split the matrix multiplication equaly between the threads.

This program will multiply square matrixes (where colsize = rowsize), only to simplify
the programm (as we are only interested in the calculation time)

The multiplication of the matrices wil be evenly distributed to the max number of thread
the computer supports;

For exemple an 8 threaded computer which does a 1000x1000 matrix multiplication will
have thread running 125 lines each.
*/

#include <iostream>
#include <cstdlib>
#include <vector> //using vector because stack size cannot hold such large 2d arrays (<1mb)
#include <thread>
#include <time.h>
#include <fstream> //to pull linux pc data
#include <sstream>
#include <string>
#include<functional>
#include<chrono>
#include<random>
#define type int //for easy type switching

using namespace std;

const int colSize = 1600;
const int rowSize = 1600;

class timer; //prototyping to permit vector creation before class declaration

vector<vector<type>> result; //keeping it as a global because we need to give concurent access to threads
vector<vector<float>> f_result; //for floating point test

vector<timer> threadTime; //we need to keep all the thread seperate time to sum them later
vector<timer> fthreadTime; //same, for floating point


class timer { //used to time processes
public:
	chrono::high_resolution_clock::time_point start, end;

	void begin() {
		start = chrono::high_resolution_clock::now();
	}

	void stop() {
		end = chrono::high_resolution_clock::now();
	}

	void runtime() {
		auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
		cout << "Runtime: " << duration / 1e9 << " seconds" << endl;
	}

	static void threadRuntime(const vector<timer>& timings, short threads) {
		double runtime = 0;
		for (const auto& t : timings) {
			auto duration = chrono::duration_cast<chrono::nanoseconds>(t.end - t.start).count();
			runtime += duration;
		}
		cout << "Runtime: " << runtime / 1e9 / threads << " seconds" << endl;
	}
};



//-------------------------------------Interger methods--------------------------------------//

vector<vector<type>> initiateMatrix() {
	vector<vector<type>> temp;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 9);
	for (int i = 0; i < rowSize; i++) {
		vector<type> row;
		for (int j = 0; j < colSize; j++) {
			row.push_back(dis(gen));
		}
		temp.push_back(row);
	}
	return temp;
}
void multiply(int low, int high, vector<vector<type>> A, vector<vector<type>> B)
{
	//we will always consider AxB as we only want to calculate computation time
	for (int i = low; i < high; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			int total = 0;
			for (int h = 0; h < colSize; h++)
			{
				total += (A[i][h] * B[h][j]);
			}
			result[i][j] = total;
		}
	}
}


//We need a seperate function to use for the timer threads
void t_multiply(int low, int high, vector<vector<type>> A, vector<vector<type>> B)
{
	timer temp;
	temp.begin();
	//we will always consider AxB as we only want to calculate computation time
	for (int i = low; i < high; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			int total = 0;
			for (int h = 0; h < colSize; h++)
			{
				total += (A[i][h] * B[h][j]);
			}
			result[i][j] = total;
		}
	}
	temp.stop();
	threadTime.push_back(temp);
}


//-------------------------------------Floating point methods--------------------------------//
//vector<vector<float>> finiateMatrix()
//{
//	vector<vector<float>> temp;
//	for (int i = 0; i < rowSize; i++)
//	{
//		vector<float> row;
//		for (int j = 0; j < colSize; j++)
//		{
//			row.push_back((float)(rand() % 10) / 4.2);
//		}
//		temp.push_back(row);
//	}
//	return temp;
//}
vector<vector<float>> finitiateMatrix() {
	vector<vector<float>> temp;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dis(0, 2.5);
	for (int i = 0; i < rowSize; i++) {
		vector<float> row;
		for (int j = 0; j < colSize; j++) {
			row.push_back(dis(gen));
		}
		temp.push_back(row);
	}
	return temp;
}
void fmultiply(int low, int high, vector<vector<float>> A, vector<vector<float>> B)
{
	//we will always consider AxB as we only want to calculate computation time
	for (int i = low; i < high; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			float total = 0;
			for (int h = 0; h < colSize; h++)
			{
				total += (A[i][h] * B[h][j]);
			}
			f_result[i][j] = total;
		}
	}
}

//We need a seperate function to use for the timer threads
void t_fmultiply(int low, int high, vector<vector<float>> A, vector<vector<float>> B)
{
	timer temp;
	temp.begin();
	//we will always consider AxB as we only want to calculate computation time
	for (int i = low; i < high; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			float total = 0;
			for (int h = 0; h < colSize; h++)
			{
				total += (A[i][h] * B[h][j]);
			}
			f_result[i][j] = total;
		}
	}
	temp.stop();
	fthreadTime.push_back(temp);
}

//for debug purposes only
void fprint(vector<vector<float>> matrix)
{
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	//srand(42); //since we want to keep the same data set everytime
	timer stopwatch; //for single thread applications
	vector<thread> pool;
	//initializnig thread count after pulling PC data
	short threads = thread::hardware_concurrency();
	short offset = colSize / threads;
	//------------interger test---------------------------------------------//
	cout << "=========INTERGER TEST=========" << endl;


	vector<vector<type>> A;
	vector<vector<type>> B;

	//setup	
	cout << "A generating...";
	A = initiateMatrix();
	cout << "[SUCCESS]" << endl;

	cout << "B generating...";
	B = initiateMatrix();
	cout << "[SUCCESS]" << endl;

	result = initiateMatrix(); //filling the matrix with random data, simply to iniate proper size


	//--------------Threadless------------//


	cout << "[SINGLE THREAD]Begin AxB ...";
	stopwatch.begin();
	for (int i = 0; i < rowSize; i++) //for(int i = 0; i < 8; i++)    for(int i = 0; i < threads; i++)
	{
		multiply((i * 1), ((i + 1) * 1), A, B);

	}
	stopwatch.stop();
	cout << "[SUCCESS]" << endl;

	cout << "Done Non-Threaded Interger Test, "; stopwatch.runtime();


	//--------------Multithreaded----------//


	/*NOTE: we do not start/stop the timer in the main thread, we let
	each thread count it's own time. The class timer is only invoked to
	call threadRunTime*/


	cout << "[MULTI THREAD]Begin AxB ...";
	for (int i = 0; i < threads; i++)
	{
		pool.push_back(thread(bind(t_multiply, (i * offset), ((i + 1) * offset), A, B)));
	}

	for (int i = 0; i < threads; i++)
	{
		pool[i].join();
	}
	cout << "[SUCCESS]" << endl;

	cout << "Done Threaded Interger Test, "; stopwatch.threadRuntime(threadTime, threads); cout << endl << endl;

	//free up some space on the heap
	A.clear();
	B.clear();
	result.clear();
	pool.clear();

	//------------floating point test---------------------------------------//
	cout << "======FLOATING POINT TEST======" << endl;

	vector<vector<float>> C;
	vector<vector<float>> D;

	//setup	
	cout << "C generating...";
	C = finitiateMatrix();
	cout << "[SUCCESS]" << endl;
	cout << "D generating...";
	D = finitiateMatrix();
	cout << "[SUCCESS]" << endl;

	f_result = finitiateMatrix(); //filling the matrix with random data, simply to iniate proper size


	//--------------Threadless------------//

	cout << "[SINGLE THREAD]Begin CxD ...";
	stopwatch.begin();
	for (int i = 0; i < rowSize; i++) //for(int i = 0; i < 8; i++)    for(int i = 0; i < threads; i++)
	{
		fmultiply((i * 1), ((i + 1) * 1), C, D);

	}
	stopwatch.stop();
	cout << "[SUCCESS]" << endl;

	cout << "Done Non-Threaded Floating Point Test, "; stopwatch.runtime(); cout << endl;

	//--------------Multithreaded----------//

	cout << "[MULTI THREAD]Begin CxD...";
	for (int i = 0; i < threads; i++)
	{
		pool.push_back(thread(bind(t_fmultiply, (i * offset), ((i + 1) * offset), C, D)));

	}

	for (int i = 0; i < threads; i++)
	{
		pool[i].join();
	}
	cout << "[SUCCESS]" << endl;

	cout << "Done Threaded Floating Point Test, "; stopwatch.threadRuntime(fthreadTime, threads); cout << endl << endl;

	C.clear();
	D.clear();
	f_result.clear();
	pool.clear();

	cout << "[BENCHMARK COMPLETE]" << endl;
	return 0;
}