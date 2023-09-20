/*
 * Layer.cpp
 *
 *  Created on: Aug 16, 2023
 *      Author: steven
 */

#include "Layer.h"

namespace model {

Layer::Layer(int size) {
	this->initialized = false;

	this->size = size;
	this->alpha = 0.01;

	this->bias = new double[this->size];
	this->activations = new double[this->size];
}

Layer::~Layer() { // TODO: Implement layer de-constructor

}

void Layer::initialize(Layer prev, double alpha) {
	this->alpha = alpha;

	int innerSize = prev.getSize();
	this->weights = new vector<vector<double>>(this->size, vector<double>(innerSize, 0));

	for (int i = 0; i < this->size; i++) {
		this->bias[i] = randomDouble(-1, 1);
		this->activations[i] = 0;

		for (int j = 0; j < innerSize; j++) {
			double randomWeight = randomDouble(-1, 1);

			this->weights->at(i).at(j) = randomWeight;
		}
	}

	this->initialized = true;
}

void Layer::forward(double* x){
	cout << "Not yet implemented!" << endl; // TODO: Implement layer forward propagation
	if (this->weights->size() == 0) {
		this->activations = x;
	}

//	double* weightMatrix = this->weightMultiplier(x);
//	double* z = weightMatrix + this->bias;
//	double* a = z; // FIXME: Add activation function
}

void Layer::backward(double* y){
	cout << "Not yet implemented!" << endl; // TODO: Implement layer back propagation
	return;
}

void Layer::weightMultiplier(double* x) {
	cout << "Not yet implemented!" << endl; // TODO: Implement this
	return;
}

} /* namespace models */
