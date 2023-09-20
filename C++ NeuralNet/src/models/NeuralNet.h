/*
 * NeuralNet.h
 *
 *  Created on: Aug 16, 2023
 *      Author: steven
 */

#ifndef MODELS_NEURALNET_H_
#define MODELS_NEURALNET_H_

#include "Layer.h"

#include <vector>
#include <string>
using namespace std;

namespace model {

class NeuralNet { // TODO: Add file save and file loading
public:
	NeuralNet(double alpha);
	virtual ~NeuralNet();

	void addLayer(Layer layer);

	void initialize();

	void forward(int *x);
	void backward(int *y);

	void train(int *x, int *y, int epochs);
	void predict(int *x); // TODO: Make return prediction array

	void print() {
		cout << "Neural network summary:\n";
		cout << "	Layer count (including input and output): ";
		cout << this->layers.size() << "\n" << endl;

		for (vector<Layer>::size_type i = 0; i < this->layers.size(); i++) {
			cout << "Layer ";
			cout << i;
			cout << ":\n";
			this->layers[i].print();
			cout << "\n";
		}
	}
private:
	bool initialized;

	double alpha;

	vector<Layer> layers;
};

} /* namespace model */

#endif /* MODELS_NEURALNET_H_ */
