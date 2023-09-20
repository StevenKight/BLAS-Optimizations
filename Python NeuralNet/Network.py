# FIXME: Add docstrings and standardize the documentation

import time

import numpy as np

from Layer import Layer
import Loss

class Network():
    '''
    A neural base network.
    '''
    
    def __init__(self, alpha = 0.01) -> None:
        self.layers = []
        self.alpha = alpha

        self.loss = None

    def add_layer(self, layer: Layer) -> None:
        '''
        Add a layer to the network

        Args:
            `layer`: The layer to be added
        '''
        self.layers.append(layer)

    def compile(self, loss = Loss.cross_entropy) -> None: # TODO: Add optimizer and metrics
        '''
        Initialize all parameters of the network.
        '''

        self.loss = loss
        
        for i in range(len(self.layers)):
            if i == 0:
                continue

            self.layers[i].initialize(self.layers[i-1])
            self.layers[i].alpha = self.alpha

    def forward(self, x: np.array) -> None:
        '''
        Forward path:
            `A^[i] = g(w^[i] * A^[i-1] + b^[i])`
        
        Symbol:
            A^[i] = Activation of layer i
            w^[i] = Weights from layer i-1 to layer i
            b^[i] = Bias from layer i-1 to layer i
            g = Activation function

        Args:
            `x`: The input of the network
        '''
        
        for i in range(len(self.layers)):
            if i == 0:
                self.layers[i].forward(x)
            else:
                self.layers[i].forward(self.layers[i-1].activation)

    def backward(self, y: np.array) -> None:
        '''
        Backward path:
            `w'^[i] = w^[i] - α * ((1/m) * ∇z^[i] * A^[i-1].T)`\n
            `b'^[i] = b^[i] - α * ((1/m) * ∇z^[i] * 1)`\n
            `∇z^[i] = A^[i] - A^[i+1]`
        
        Args:
            `y`: The expected output of the network for the given input
        '''
        
        for i in range(len(self.layers)-1, -1, -1):
            if i == len(self.layers)-1:
                self.layers[i].backward(y)
            else:
                self.layers[i].backward(self.layers[i+1].activation)

    def accuracy(self, y: np.array, output: np.array) -> float:
        '''
        Calculate the accuracy of the network

        Args:
            `y`: The expected output of the network for the given input\n
            `output`: The output of the network for the given input
        '''

        return np.mean(np.argmax(y, axis=-1) == np.argmax(output, axis=-1))

    def train(self, x_train: list[np.array], y_train: list[np.array], x_test: list[np.array], y_test: list[np.array], epochs: int) -> None:
        '''
        Train the network.

        Args:
            `x_train`: The inputs of the network\n
            `y_train`: The expected output of the network for the given input\n
            `epochs`: The number of epochs to train
        '''

        if len(x_train) != len(y_train):
            raise Exception("Training x and y must have the same amount of samples")
        
        if len(x_test) != len(y_test):
            raise Exception("Testing x and y must have the same amount of samples")
        
        template = "Epoch {}: {:.2f}s, train acc={:.2f}, train loss={:.2f}, test acc={:.2f}, test loss={:.2f}"

        for i in range(epochs):
            start_time = time.time()
            # Train network on all given training samples
            for j in range(len(x_train)):
                self.forward(x_train[j])    
                self.backward(y_train[j])
                # TODO: Add optimizer

            # Evaluate performance
            # Training data
            output = self.predict(x_train)
            train_acc = self.accuracy(y_train, output)
            train_loss = self.loss(y_train, output)
            # Test data
            output = self.predict(x_test)
            test_acc = self.accuracy(y_test, output)
            test_loss = self.loss(y_test, output)
            print(template.format(i+1, time.time()-start_time, train_acc, train_loss, test_acc, test_loss))

    def predict(self, x: np.array) -> np.array:
        '''
        Predict the output of the network for the given input

        Args:
            `x`: The input of the network
        '''


        if (len(x.shape) != 1):
            predictions = []
            for i in range(len(x)):
                self.forward(x[i])
                y = self.layers[-1].activation
                y = y.flatten()
                predictions.append(y)

            return np.array(predictions)
        
        self.forward(x)
        return self.layers[-1].activation
