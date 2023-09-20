# FIXME: Add docstrings and standardize the documentation

import numpy as np

import Activation

class Layer:
    '''
    A layer of a neural network.
    '''
    
    def __init__(self, size, activation=Activation.sigmoid) -> None:
        self.size = size
        self.alpha = 0.01

        self.activation_func = activation

        self.weights = np.array([])
        self.bias = np.random.randn(self.size, 1)

        self.activation = np.zeros((self.size, 1))

    def initialize(self, prev: 'Layer') -> None:
        '''
        Initialize the weights and bias of the layer
        NOTE: This method will change depending on the type of layer (this is a dense layer)

        Args:
            `prev`: The previous layer
            `alpha`: The learning rate
        '''
        self.weights = np.random.randn(self.size, prev.size) * np.sqrt(1./prev.size)
        self.bias = np.random.randn(self.size, 1) * np.sqrt(1./prev.size)

    def multiply_weights(self, x: np.array) -> np.array:
        '''
        Multiply the weights by the input

        Args:
            `x`: The input of the network
        '''

        weights = []
        for weight in self.weights:
            if len(weight) != len(x):
                raise Exception("The length of the weights and the input must be the same")
            
            new_weight = []
            for i in range(len(weight)):
                new_weight.append(weight[i] * x[i])

            weights.append(np.sum(new_weight))

        return np.asarray(weights).reshape(self.size, 1) #  # THIS FLATTENS weights to (size, 1)

    def forward(self, x: np.array) -> np.array:
        '''
        Forward path:
            `Z = W * x + b`\n
            `A = g(Z)`
        
        Symbol:
            A = Activation of layer
            W = Weights of layer
            b = Bias of layer
            g = Activation function
            x = Input of layer

        Args:
            `x`: The input of the network
        '''

        if self.weights.size == 0:
            self.activation = x
            return x

        weight_matrix = self.multiply_weights(x)
        z = weight_matrix + self.bias
        a = self.activation_func(z)

        self.activation = a

        return self.activation
    
    def backward(self, y: np.array) -> None:
        '''
        Backward path:
            `W' = W - α * ((1/m) * ∇z * y.T)`\n
            `b' = b - α * ((1/m) * sum(∇z))`\n
            `∇z = A - y`

        Symbol:
            A = Activation of layer
            W = Weights of layer
            b = Bias of layer
            w' = New weights of layer
            b' = New bias of layer
            y = Expected output of layer
            α = Learning rate
        
        Args:
            `y`: The expected output of the network for the given input
        '''

        if self.weights.size == 0:
            return

        m = 1 # TODO: Change this to the number of training examples

        dZ = self.activation - y.reshape(self.activation.shape) # THIS FLATTENS y to (size, 1)
        dW = (1./m) * np.multiply(dZ, self.activation)
        db = (1./m) * np.sum(dZ, axis=1, keepdims=True)

        self.weights = self.weights - self.alpha * dW
        self.bias = self.bias - self.alpha * db

        self.activation = np.matmul(self.weights.T, dZ)
