/*
 * NeuralNet.cpp
 *
 *  Created on: Aug 16, 2023
 *      Author: steven
 */

#include <NeuralNet.h>

namespace model {

NeuralNet::NeuralNet(double alpha) {
	this->initialized = false;
	this->alpha = alpha;
}

NeuralNet::~NeuralNet() { // TODO: Implement network de-constructor
}

void NeuralNet::addLayer(Layer layer) {
	this->layers.push_back(layer);
}

void NeuralNet::initialize() {
	for (vector<Layer>::size_type i = 0; i < this->layers.size(); i++) {
		if (i == 0) {
			cout << "Input layer\n" << endl;
			continue;
		}

		this->layers[i].initialize(this->layers[i-1], this->alpha);
	}

	this->initialized = true;
}

void NeuralNet::forward(int *x) {
	cout << "Not yet implemented!" << endl; // TODO: Implement network forward propagation
	return;
}
void NeuralNet::backward(int *y) {
	cout << "Not yet implemented!" << endl; // TODO: Implement network back propagation
	return;
}

void NeuralNet::train(int *x, int *y, int epochs) {
	cout << "Not yet implemented!" << endl; // TODO: Implement network training
	return;
}
void NeuralNet::predict(int *x) {
	cout << "Not yet implemented!" << endl; // TODO: Implement network predictions
	return ;
}

} /* namespace model */
