/*
 * Matrix.h
 *
 *  Created on: Aug 21, 2023
 *      Author: steven
 */

#ifndef UTILS_MATRIX_H_
#define UTILS_MATRIX_H_

#include <algorithm>
#include <numeric>
#include <iterator>
#include <limits.h>
#include <float.h>
#include <iostream>
using namespace std;

namespace model {

template <typename type>
class Matrix {
private:
	vector<vector<type>> matrix;

	vector<int> shapeVector;

	inline
	void shapeCheck(Matrix matrix) {
		vector<int> otherShape = matrix.shape();
		if (this->shapeVector[0] != otherShape[0] || this->shapeVector[1] != otherShape[1]) {
			cerr << "Matrices of different shapes cannot be cast together." << endl;
			throw;
		}
	}

	inline
	void mulitiplySameShape(Matrix matrix) {
		this->shapeCheck(matrix);

		vector<type> flattenedOther = matrix.flatten();
		vector<type*> flattenedThis = this->flattenPtr();
		for (int i = 0; i < (this->shapeVector[0] * this->shapeVector[1]); i++) {
			*flattenedThis[i] *= flattenedOther[i];
		}
	}

	inline
	void divideSameShape(Matrix matrix) {
		this->shapeCheck(matrix);

		vector<type> flattenedOther = matrix.flatten();
		vector<type*> flattenedThis = this->flattenPtr();
		for (int i = 0; i < (this->shapeVector[0] * this->shapeVector[1]); i++) {
			*flattenedThis[i] /= flattenedOther[i];
		}
	}
public:
	Matrix(vector<vector<type>> vectors) : Matrix(new int[2]{vectors.size(), vectors[0].size()}) { // FIXME: "new int[2]..." in the call to other constructor leads to memory leaks
		this->matrix = vectors;
	}

	Matrix(int* shape, int size=2) { // ONLY WORKS FOR 1D AND 2D MATRICES CURRENTLY AND DO NOT ALLOW OTHERS TO ADJUST BOOL
		if (size != 2) {
			cerr << "Size must be 2D." << endl;
		}

		this->shapeVector.resize(size);
		this->shapeVector[0] = shape[0];
		this->shapeVector[1] = shape[1];

		this->matrix.resize(this->shapeVector[0]);

		for (auto & vec : this->matrix) {
			vec.resize(this->shapeVector[1] == 0 ? 1 : this->shapeVector[1], 0);
		}
	}

	virtual ~Matrix() { }

	vector<int> shape() {
		return this->shapeVector;
	}

	int size() {
		return this->shapeVector[0] * this->shapeVector[1];
	}

	Matrix* fillRandom() {
		for (auto &i : this->matrix)
			std::fill(i.begin(), i.end(), randomDouble(-1.0, 1.0));

		return this;
	}

	Matrix* T() {

		std::reverse(this->shapeVector.begin(), this->shapeVector.end());

		vector<vector<type>> newMatrix;
		newMatrix.resize(this->shapeVector[0]);
		for (int i = 0; i < this->shapeVector[0]; i++) {
			newMatrix[i].resize(this->shapeVector[1] == 0 ? 1 : this->shapeVector[1]);
			for (int j = 0; j < this->shapeVector[1]; j++) {
				newMatrix[i][j] = this->matrix[j][i];
			}
		}

		this->matrix = newMatrix;
		return this;
	}

	Matrix* reshape(int* shape, int size = 2) {
		if (size != 2) {
			cerr << "Size must be 2D." << endl;
			throw;
		}
		if (this->shapeVector[0] * this->shapeVector[1] != shape[0] * shape[1]){
			cerr << "Cannot reshape array of size " << this->shapeVector[0] * this->shapeVector[1];
			cerr << " into shape (" << shape[0] << ", " << shape[1] << ")." << endl;
			throw;
		}

		this->shapeVector[0] = shape[0];
		this->shapeVector[1] = shape[1];

		vector<vector<type>> newMatrix;
		newMatrix.resize(this->shapeVector[0]);
		for (auto & vec : newMatrix) {
			vec.resize(this->shapeVector[1] == 0 ? 1 : this->shapeVector[1], 0);
		}
	}

	vector<type> flatten() {
		vector<type> flattenedMatrix;

		for (auto const &v: this->matrix) {
			flattenedMatrix.insert(flattenedMatrix.end(), v.begin(), v.end());
		}

		return flattenedMatrix;
	}

	vector<type*> flattenPtr() {
		vector<type*> flattenedMatrix;
		int size = this->shapeVector[0] * this->shapeVector[1];
		flattenedMatrix.resize(size);

//		for (int i = 0; i < (this->shapeVector[0] == 0 ? 1 : this->shapeVector[0]); i++) { TODO: Test if I need this
//			for (int j = 0; j < (this->shapeVector[1] == 0 ? 1 : this->shapeVector[1]); j++) {
//				flattenedMatrix[i * this->shapeVector[1] + j] = &this->matrix[i][j];
//			}
//		}

		for (int i = 0; i < size; i++) {
			int row = i / this->shapeVector[1];
			int col = i % this->shapeVector[1];

			flattenedMatrix[i] = &this->matrix[row][col];
		}

		return flattenedMatrix;
	}

	double mean() {
		type sum = this->sum();
		int size = this->shapeVector[0] * this->shapeVector[1];

		return sum / size;
	}

	vector<int> argmax(int axis=INT_MIN) {
		if ((axis < -1 || axis > 1) && axis != INT_MIN) {
			cerr << "Axis " << axis << " is out of bounds (-1 : 1)." << endl;
			throw;
		}

		if (axis == -1) {
			axis = this->shapeVector.size() - 1;
		}

		vector<int> maxValues;
		maxValues.resize(2);
		vector<type> flattendMatrix = this->flatten();
		auto maxElement = max_element(flattendMatrix.begin(), flattendMatrix.end());

		int dist = distance(flattendMatrix.begin(), maxElement);
		maxValues[0] = dist / this->shapeVector[1];
		maxValues[1] = dist % this->shapeVector[1];
		return maxValues;
	}

	type sum() {
		double sum;

		vector<type> flat = this->flatten();
		for (type value : flat) {
			sum += value;
		}

		return sum;
	}

	Matrix* operator+(Matrix matrix) { // FIXME: Add in place
		this->shapeCheck(matrix);

		vector<type> flattenedOther = matrix.flatten();
		vector<type*> flattenedThis = this->flattenPtr();
		for (int i = 0; i < (this->shapeVector[0] * this->shapeVector[1]); i++) {
			*flattenedThis[i] += flattenedOther[i];
		}

		return this;
	}

	Matrix* operator-(Matrix matrix) { // FIXME: Add in place
		this->shapeCheck(matrix);

		vector<type> flattenedOther = matrix.flatten();
		vector<type*> flattenedThis = this->flattenPtr();
		for (int i = 0; i < (this->shapeVector[0] * this->shapeVector[1]); i++) {
			*flattenedThis[i] -= flattenedOther[i];
		}

		return this;
	}

	Matrix* operator*(Matrix matrix) { // FIXME: Add in place
		vector<int> otherShape = matrix.shape();

		bool rowOneDCheck = this->shapeVector[1] == otherShape[1] && (this->shapeVector[0] == 1 || otherShape[0] == 1);
		bool colOneDCheck = this->shapeVector[0] == otherShape[0] && (this->shapeVector[1] == 1 || otherShape[1] == 1);
		bool OneDAxisCheck = rowOneDCheck || colOneDCheck;
		bool fullShapeCheck = this->shapeVector[0] == otherShape[0] && this->shapeVector[1] == otherShape[1];

		if (!OneDAxisCheck && !fullShapeCheck) {
			cerr << "Cannot multiply shapes of ";

			cerr << "(" << this->shapeVector[0] << ", " << this->shapeVector[1] << ") and ";
			cerr << "(" << otherShape[0] << ", " << otherShape[1] << ")" << endl;
			throw;
		}

		if (fullShapeCheck) {
			this->mulitiplySameShape(matrix);
		}
		else {
			cout << "1D matrix to multiply" << endl;
		}

		return this;
	}

	Matrix* operator/(Matrix matrix) { // FIXME: Add in place
		vector<int> otherShape = matrix.shape();

		bool rowOneDCheck = this->shapeVector[1] == otherShape[1] && (this->shapeVector[0] == 1 || otherShape[0] == 1);
		bool colOneDCheck = this->shapeVector[0] == otherShape[0] && (this->shapeVector[1] == 1 || otherShape[1] == 1);
		bool OneDAxisCheck = rowOneDCheck || colOneDCheck;
		bool fullShapeCheck = this->shapeVector[0] == otherShape[0] && this->shapeVector[1] == otherShape[1];

		if (!OneDAxisCheck && !fullShapeCheck) {
			cerr << "Cannot divide shapes of ";

			cerr << "(" << this->shapeVector[0] << ", " << this->shapeVector[1] << ") and ";
			cerr << "(" << otherShape[0] << ", " << otherShape[1] << ")" << endl;
			throw;
		}

		if (fullShapeCheck) {
			this->divideSameShape(matrix);
		}
		else {
			cout << "1D matrix to multiply" << endl;
		}

		return this;
	}

	vector<type>& operator[](size_t n) { return this->matrix[n]; }
	const vector<type>& operator[](size_t n) const { return this->matrix[n]; }

	void print() {
		for (int i = 0; i < (this->shapeVector[0] == 0 ? 1 : this->shapeVector[0]); i++) {
			for (int j = 0; j < (this->shapeVector[1] == 0 ? 1 : this->shapeVector[1]); j++) {
				cout << i << ":" << j << " = " << this->matrix[i][j];
				if (j != (this->shapeVector[1] == 0 ? 1 : this->shapeVector[1]) - 1) {
					cout << " - ";
				}
			}
			cout  << endl;
		}
	}
};

} /* namespace model */

#endif /* UTILS_MATRIX_H_ */
