#include <cstdlib>
#include <vector>
#include <iostream>

#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {

	const unsigned long long int Dim = 10000;

	vector<vector<double>> matrixA;
	vector<vector<double>> matrixB;
	vector<vector<double>> matrixC;

	for (int g = 0; g < Dim; g++) {
	    matrixA.push_back(vector<double>(Dim)); //Add an empty row
	    matrixB.push_back(vector<double>(Dim)); //Add an empty row
	    matrixC.push_back(vector<double>(Dim)); //Add an empty row
	}

	for (int i = 0; i < Dim; i++) {
	    for (int j = 0; j < Dim; j++) {
		matrixA[i][j] = rand() % 10000;
		matrixB[i][j] = rand() % 10000;
		
	    }
	}

	// Matrices addition
	cout << "Start Sequential Operation " << endl;
	auto start = high_resolution_clock::now();

	for (int i = 0; i < Dim; i++) {
		for (int j = 0; j < Dim; j++) {
			matrixC[i][j] = matrixA[i][j] * matrixB[i][j];
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "Addition time: " << duration.count() << " milliseconds" << endl;
	
	cout << "Matrix A: " << matrixA[0][0] << endl;
	cout << "Matrix B: " << matrixB[0][0] << endl;
	cout << "Matrix C: " << matrixC[0][0] << endl << endl;

	cout << "Matrix A: " << matrixA[500][500] << endl;
	cout << "Matrix B: " << matrixB[500][500] << endl;
	cout << "Matrix C: " << matrixC[500][500] << endl << endl;

	cout << "Matrix A: " << matrixA[900][900] << endl;
	cout << "Matrix B: " << matrixB[900][900] << endl;
	cout << "Matrix C: " << matrixC[900][900] << endl << endl;

	cout << endl;
}
