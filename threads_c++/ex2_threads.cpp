#include <iostream>       
#include <thread>         
#include <ctime>          
#include <vector>
#include <chrono>  // measure the time 
using namespace std;
using namespace std::chrono; // for the   high_resolution_clock
vector<unsigned long long int> matrixA;
void fillVecotr(unsigned long long int upperBound);
bool sequential_Search(unsigned long long int key, unsigned long long int upperBound);
const unsigned long long int Dim = 300000;
int main()
{
	bool found = false;
	unsigned long long int key = 7777777777;
	fillVecotr(Dim);
	auto start = high_resolution_clock::now(); //auto vars need to be initialized.
	found = sequential_Search(key, Dim); // looking for the key sequentially
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	string result = found ? "Found" : "Not Found";
	cout << result << ", took sequentail time: " << duration.count() << " microseconds" << endl;
} // end of main function
bool sequential_Search(unsigned long long int key, unsigned long long int upperBound) {
	for (int index = 0; index < matrixA.size(); ++index)
		if (matrixA[index] == key)
			return true;
	return false;
}// end of sequential_Matrix_Update function
//------------------------------------
void fillVecotr(unsigned long long int upperBound) {
	unsigned long long int count;
	for (count = 0; count < upperBound; ++count)
		matrixA.push_back((rand() % 100000000));

	matrixA[upperBound - 1] = 7777777777;
	//update the last vector element to create the worst case.

}
