//============================================================================
// Name        : Testing.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

#include "Matrix.h"
using namespace model;

void testMatrixTiming(Matrix<double> matrixOne, Matrix<double> matrixTwo, ofstream &logFile) {

	chrono::_V2::system_clock::time_point start;
	chrono::_V2::system_clock::time_point end;

	start = chrono::high_resolution_clock::now();

	matrixOne.T();

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";
	matrixOne.T(); // invert transpose

	start = chrono::high_resolution_clock::now();

	matrixOne.shape(); // Read the shape of the array

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne.sum(); // Sum the array

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne.mean(); // Calculate the mean of the array

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne.argmax(); // Find the index of the maximum value in the array (flatten mode) TODO: Measure non flatten mode

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne + matrixTwo; // Add the arrays

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne - matrixTwo; // Subtract the arrays

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne * matrixTwo; // Multiply the arrays

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	start = chrono::high_resolution_clock::now();

	matrixOne / matrixTwo; // Divide the arrays

	end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << endl;
}

void testSmallMatrix(ofstream &logFile) {
	int *smallSize = new int[2]{3,1};
	vector<vector<double>> smallVectorSet = {{1},{2},{3}};

	chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();

	Matrix<double> testSmallZeros(smallSize);

	chrono::_V2::system_clock::time_point end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	Matrix<double> testSmallMatrix(smallVectorSet);
	Matrix<double> testSmallMatrixTwo(smallVectorSet);

	testMatrixTiming(testSmallMatrix, testSmallMatrixTwo, logFile);

	delete[] smallSize;
}

void testLargeMatrix(ofstream &logFile) {
	int *bigSize = new int[2]{10, 90};

	chrono::_V2::system_clock::time_point start = chrono::high_resolution_clock::now();

	Matrix<double> testBigZeros(bigSize);

	chrono::_V2::system_clock::time_point end = chrono::high_resolution_clock::now();
	logFile << chrono::duration< double >( end - start ).count( ) << ",";

	Matrix<double> testBigMatrix(bigSize);
	testBigMatrix.fillRandom();

	Matrix<double> testBigMatrixTwo(bigSize);
	testBigMatrixTwo.fillRandom();

	testMatrixTiming(testBigMatrix, testBigMatrixTwo, logFile);

	delete[] bigSize;
}

int timeMatrix() {
	ofstream cppTimeFile;
	cppTimeFile.open("cpp_times.csv");

	int iterations = 15;
	cppTimeFile << "Small matrix:" << endl;
	for (int i = 0; i < iterations; i++) {
		testSmallMatrix(cppTimeFile);
	}
	cppTimeFile << "Big matrix:" << endl;
	for (int i = 0; i < iterations; i++) {
		testLargeMatrix(cppTimeFile);
	}

	cppTimeFile.close();

	return 0;
}
