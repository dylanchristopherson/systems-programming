#include <cstdlib>
#include <vector>
#include <iostream>
#include <thread>
#include <string>

#include <chrono>

using namespace std;
using namespace std::chrono;


const unsigned long long int Dim = 1000;

vector<vector<double>> matrixA;
vector<vector<double>> matrixB;
vector<vector<double>> matrixC;

void matrices_mult(int index, int upperbound) {
	// Matrix calculation help from below link
	// https://stackoverflow.com/questions/41018065/multiplying-3x3-matrices-in-c

	for (int i = index; i < upperbound; i++ ) {
		for (int j = 0; j < Dim; j++) {
			for (int u = 0; u < Dim; u++) {
				matrixC[i][j] += matrixA[i][u] * matrixB[u][j];
			}			
			
		}
	}

}

void threaded_mult() {
	thread thread1(matrices_mult, 0, 250);
	thread thread2(matrices_mult, 250, 500);
	thread thread3(matrices_mult, 500, 750);
	thread thread4(matrices_mult, 750, 1000);
 
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
}

void sequential_mult() {
	for (int i = 0; i < Dim; i++ ) {
		for (int j = 0; j < Dim; j++) {
			for (int u = 0; u < Dim; u++) {
				matrixC[i][j] += matrixA[i][u] * matrixB[u][j];
			}			
			
		}
	}
}

void data_check() {
	// Simple data output	
	cout << endl;	
	
	cout << "Matrix A: " << matrixA[0][0] << endl;
	cout << "Matrix B: " << matrixB[0][0] << endl;
	cout << "Matrix C: " << matrixC[0][0] << endl << endl;

	cout << "Matrix A: " << matrixA[500][500] << endl;
	cout << "Matrix B: " << matrixB[500][500] << endl;
	cout << "Matrix C: " << matrixC[500][500] << endl << endl;

	cout << "Matrix A: " << matrixA[900][900] << endl;
	cout << "Matrix B: " << matrixB[900][900] << endl;
	cout << "Matrix C: " << matrixC[900][900] << endl << endl;

}

int main(int argc, const char* argv[]) {

	if (argc >= 2) {
		
		if(string(argv[1]) == "s") {
			// Generates data for vectors	
			cout << "Building test vectors" << endl;
			for (int g = 0; g < Dim; g++) {
			    matrixA.push_back(vector<double>(Dim)); //Add an empty row
			    matrixB.push_back(vector<double>(Dim)); //Add an empty row
			    matrixC.push_back(vector<double>(Dim)); //Add an empty row
			}

			for (int i = 0; i < Dim; i++) {
			    for (int j = 0; j < Dim; j++) {
				matrixA[i][j] = rand() % 100000;
				matrixB[i][j] = rand() % 100000;
				
			    }
			}

			// Matrices addition
			cout << "Start Sequential Operation " << endl;
			auto start = high_resolution_clock::now();
			
			sequential_mult();
			
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			cout << "Multiplication time: " << duration.count() << " milliseconds" << endl;
			data_check();
		}
		else if (string(argv[1]) == "t") {
			// Generates data for vectors	
			cout << "Building test vectors" << endl;
			for (int g = 0; g < Dim; g++) {
			    matrixA.push_back(vector<double>(Dim)); //Add an empty row
			    matrixB.push_back(vector<double>(Dim)); //Add an empty row
			    matrixC.push_back(vector<double>(Dim)); //Add an empty row
			}

			for (int i = 0; i < Dim; i++) {
			    for (int j = 0; j < Dim; j++) {
				matrixA[i][j] = rand() % 1000000;
				matrixB[i][j] = rand() % 1000000;
				
			    }
			}
			// Matrices addition
			cout << "Start Threaded Operation " << endl;
			auto start = high_resolution_clock::now();

			threaded_mult();
			
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<milliseconds>(stop - start);

			cout << "Multiplication time: " << duration.count() << " milliseconds" << endl;
			data_check();

		}
	}
	else {
		cout << "This program uses flags to specify if it should run sequentially\n";
		cout << "or if it should run threaded. See below\n";
		cout << "./file s (Will run sequentially)\n";
		cout << "./file t (Will run threaded)\n";
	}


	cout << endl;
}
