// MultithreadedMatrixAddition.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

// CS442_threads_MatrixAddition.cpp : Defines the entry point for the console application.
//By Dr. Alnaeli
//copyrights
//Please never shared with the public.
//this program is written for educational purposes only

#include <iomanip>
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <ctime>    
#include <chrono>  // measure the tile via using some functions included here
#include <vector>
#include <omp.h>  //openMP
#include <ctime>
using namespace std;
using namespace std::chrono; // for the   high_resolution_clock
mutex mtx;           // mutex for critical section

const unsigned long long int Dim = 1000;
vector<vector<unsigned long long int>> matrixA;
vector<vector<unsigned long long int>> matrixB;
vector<vector<unsigned long long int>> matrixC; //calculated sequentially
vector<vector<unsigned long long int>> matrixD; //calculated in parallel using std::thread
vector<vector<unsigned long long int>> matrixE; // calculated parallel using openMP
//-------------------------

void sequential_Matrix_Addition();
////------------------------
//-------------------------
void parallel_Matrix_Addition(int from, int to);
////-----------------------

void openMP_Matrix_Addition();
//--------------------------------------------
//------------------------
void print10X10(vector<vector<unsigned long long int>> vec);
//-----------------------------------------------
void constructMatrices();
//-----------------------------------------------
int main()
{
	srand(time(nullptr));
	constructMatrices();
	//initiializing vectors
	int count = 0;
	for (int i = 0; i < Dim; i++)
		for (int j = 0; j < Dim; j++)
		{ // just arbitrary numbers
			matrixA[i][j] = rand()%50001;
			matrixB[i][j] = rand() % 50001;
			matrixC[i][j] = 0;
			matrixD[i][j] = 0;
			matrixE[i][j] = 0;
		}
	//print the first 3 vectors for testing
	print10X10(matrixA);
	print10X10(matrixB);
	print10X10(matrixC);
	//sequential matrix mulitplication
	cout << "Start Sequential Operation " << endl;
	auto start = high_resolution_clock::now();
	sequential_Matrix_Addition();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Sequential time: " << duration.count() << endl;

	//Parallelmatrix Addition

	int from = 0;
	int to = 0;
	int workload = Dim / 4;
	int dim1 = workload;
	int dim2 = workload * 2;
	int dim3 = workload * 3;
	int dim4 = Dim - 1;
	/*	cout << workload << endl;
	cout << dim1 << endl;
	cout << dim2 << endl;
	cout << dim3 << endl;
	cout << dim4 << endl;*/

	cout << "Start Parallel Operation Using std::theard" << endl;
	start = high_resolution_clock::now();
	//creating threads and dividing the workload
	std::thread th1(parallel_Matrix_Addition, 0, dim1);
	std::thread th2(parallel_Matrix_Addition, (dim1 + 1), dim2);
	std::thread th3(parallel_Matrix_Addition, (dim2 + 1), dim3);
	std::thread th4(parallel_Matrix_Addition, (dim3 + 1), dim4);

	th1.join();
	th2.join();
	th3.join();
	th4.join();

	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Parallel time in microseconds: " << duration.count() << endl;


	//openmp**********************************
	cout << "Start Parallel Operation Using openMP" << endl;
	start = high_resolution_clock::now();
	openMP_Matrix_Addition();

	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Parallel time in microseconds with openMP: " << duration.count() << endl;
	//****************************************

	print10X10(matrixC);
	print10X10(matrixD);

	/* testing the total of the items MatrixC , D, and E
	//unsigned long long int sum1 = 0, sum2 = 0, sum3 = 0;
	//for (int i = 0; i < Dim; i++)
	//	for (int j = 0; j < Dim; j++)
	//	{
	//		sum1 = sum1 + matrixC[i][j];
	//		sum2 = sum2 + matrixD[i][j];
	//		sum3 = sum3 + matrixE[i][j];
	//	}
	//cout << "Sum to the sequentially resulted matrix: " << sum1 << endl;
	//cout << "Sum to the Paralllely resulted matrix: " << sum2 << endl;
	//cout << "Sum to the Paralllely resulted matrix openMP: " << sum3 << endl;
	*/
	return 0;
}

// function implementations******************************************************************

void sequential_Matrix_Addition() {
	//preconditions: matrixA, matrixB, and matrixC are not null and all have the same size
	for (int draw = 0; draw < matrixD.size(); ++draw) {
		for (int dcolumn = 0; dcolumn < matrixD.size(); ++dcolumn) {

			matrixC[draw][dcolumn] = (matrixA[draw][dcolumn] + matrixB[draw][dcolumn]);

		}
	}
}// end of sequential_Matrix_Addition function
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 //-------------------------
void parallel_Matrix_Addition(int from, int to) {
	//preconditions: matrixA, matrixB, and matrixD are not null and all have the same size
	for (int draw = from; draw <= to; ++draw) {
		for (int dcolumn = 0; dcolumn < matrixD.size(); ++dcolumn) {

			matrixD[draw][dcolumn] = (matrixA[draw][dcolumn] + matrixB[draw][dcolumn]);

		}
	}
}// end of parallel_Matrix_Addition function
 //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

void openMP_Matrix_Addition() {
	//preconditions: matrixA, matrixB, and matrixE are not null and all have the same size
	omp_set_dynamic(0);
	omp_set_num_threads(8);
#pragma omp parallel for
	for (int draw = 0; draw < matrixD.size(); ++draw) {
		for (int dcolumn = 0; dcolumn < matrixD.size(); ++dcolumn) {

			matrixE[draw][dcolumn] = (matrixA[draw][dcolumn] + matrixB[draw][dcolumn]);

		}
	}
}// end of openMP_Matrix_Addition function
 //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void print10X10(vector<vector<unsigned long long int>> vec) {
	//this function prints the first and last 10 rows and columns.
	//precondition: need to make sure that the vectors have at least 10X10 rows and columns.
	unsigned long long int count;
	if (vec.size() > 10) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
			{
				cout << setw(7) << vec[i][j] << " ";

			}
			cout << endl;
		}

		cout << "--------------------------------" << endl;
	}
	else
	{////printing vectors
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < vec.size(); j++)
			{
				cout << setw(7) << vec[i][j] << " ";

			}
			cout << endl;
		}

		cout << "--------------------------------" << endl;

	}
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
void constructMatrices() {
	//pre conditions: all matrices are declared as vector of vectors: vector<vector<unsigned long long int>> 
	for (int i = 0; i < Dim; i++) {
		matrixA.push_back(vector<unsigned long long int>(Dim)); // Add an empty row
		matrixB.push_back(vector<unsigned long long int>(Dim)); // Add an empty row
		matrixC.push_back(vector<unsigned long long int>(Dim)); // Add an empty row
		matrixD.push_back(vector<unsigned long long int>(Dim)); // Add an empty row
		matrixE.push_back(vector<unsigned long long int>(Dim)); // Add an empty row
	}
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
