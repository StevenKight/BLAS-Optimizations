# FIXME: Add docstrings and standardize the documentation

import numpy as np

def tanh(x: np.array) -> np.array:
    '''
    Hyperbolic tangent function:
        y = (e^x - e^-x) / (e^x + e^-x)

    Args:
        `x`: The input of the function
    '''
    return np.tanh(x)

def sigmoid(x: np.array) -> np.array:
    '''
    Sigmoid function:
        y = 1 / (1 + e^-x)

    Args:
        `x`: The input of the function
    '''
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x: np.array) -> np.array:
    '''
    Derivative of the sigmoid function:
        y = sigmoid(x) * (1 - sigmoid(x))

    Args:
        `x`: The input of the function
    '''
    return sigmoid(x) * (1 - sigmoid(x))

def relu(x: np.array) -> np.array:
    '''
    ReLU function:
        y = max(0, x)

    Args:
        `x`: The input of the function
    '''
    return np.maximum(0, x)

def softmax(x: np.array) -> np.array:
    '''
    Softmax function:
        y = e^x / ∑(e^x)

    Args:
        `x`: The input of the function
    '''
    return np.exp(x) / np.sum(np.exp(x), axis=0)
