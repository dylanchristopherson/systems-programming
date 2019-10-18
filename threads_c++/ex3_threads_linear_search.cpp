//#include <iomanip>
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <ctime>    
#include <chrono>  // measure the tile via using some functions included here
#include <vector>
using namespace std;
using namespace std::chrono; // for the   high_resolution_clock
vector<unsigned long long int> matrixA;
bool foundByThread = false;
void fillVecotr(unsigned long long int upperBound);
//--------------------------------------------
bool sequential_Search(unsigned long long int key, unsigned long long int upperBound);
bool parallel_Search(unsigned long long int key, unsigned long long int from, unsigned long long int to);
const unsigned long long int Dim = 300000;//--------------------------------------------
int main()
{<!-- -->
	bool found = false;
	unsigned long long int key = 77771777777;
	//auto vars need to be initialized.	
	fillVecotr(Dim);
	auto start = high_resolution_clock::now();
	found = sequential_Search(key, Dim); // looking for the key sequentially
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	string result = found ? "Found" : "Not Found";

	cout << result << ", took sequentail time: " << duration.count() << " microseconds" << endl;

	//Parallel.  Multithreaded:
	//************************************
	int from = 0;
	int to = 0;
	int workload = Dim / 4;
	int dim1 = workload;
	int dim2 = workload * 2;
	int dim3 = workload * 3;
	int dim4 = Dim - 1;
	start = high_resolution_clock::now();

	std::thread th1(parallel_Search,key, 0, dim1);
	std::thread th2(parallel_Search,key, (dim1 + 1), dim2);
	std::thread th3(parallel_Search,key, (dim2 + 1), dim3);
	std::thread th4(parallel_Search,key, (dim3 + 1), dim4);
	stop = high_resolution_clock::now();
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	
	duration = duration_cast<microseconds>(stop - start);
string result_threaded = foundByThread ? "Found" : "Not Found";
cout << result_threaded << ", took parallel time: " << duration.count() << " microseconds" << endl;

} // end of main function
//-------------------------
bool sequential_Search(unsigned long long int key, unsigned long long int upperBound) {<!-- -->
	for (int index = 0; index < matrixA.size(); ++index)
		if (matrixA[index] == key)
			return true;
	return false;
}// end of sequential_Matrix_Update functionfunction
//------------------------------------
bool parallel_Search(unsigned long long int key, unsigned long long int from, unsigned long long int to) {<!-- -->
	for (int index = from; (index <= to && foundByThread==false); ++index)
		if (matrixA[index] == key) //found
		{<!-- -->
			foundByThread = true; //let others know
			return true;
		}
	return false; //not found
}
//------------------------------------
void fillVecotr(unsigned long long int upperBound) {<!-- -->
	unsigned long long int count;
	for (count = 0; count < upperBound; ++count)
		matrixA.push_back((rand() % 100000000));
	matrixA[upperBound - 1] = 7777777777;
}
