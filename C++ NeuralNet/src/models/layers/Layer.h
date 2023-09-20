/*
 * Layer.h
 *
 *  Created on: Aug 16, 2023
 *      Author: steven
 */

#ifndef MODELS_LAYERS_LAYER_H_
#define MODELS_LAYERS_LAYER_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "utils.h"

namespace model {

class Layer {
public:
	Layer(int size);
	virtual ~Layer();

	int getSize() {
		return this->size;
	};

	void virtual initialize(Layer prev, double alpha);

	void virtual forward(double* x);
	void virtual backward(double* y);

	void print() {
		if (!this->initialized) {
			cout << "Input layer with ";
			cout << this->size;
			cout << " nodes\n" << endl;
		}


		cout << "Non-input layer:\n";
		for (int i = 0; i < this->size; i++) {
			cout << "Node ";
			cout << i;
			cout << "\n	Bias: ";
			cout << this->bias[i];
			cout << " :: Weights: ";

			for (vector<vector<double>>::size_type j = 0; j < this->weights->at(i).size(); j++) {
				cout << this->weights->at(i).at(j);
				cout << " | ";
			}
			cout << endl;
		}
		cout << endl;
	}
private:
	bool initialized;

	int size;
	double alpha;

	double *activations;
	vector<vector<double>> *weights;
	double *bias;

	void virtual weightMultiplier(double* x);
};

} /* namespace models */

#endif /* MODELS_LAYERS_LAYER_H_ */
