# FIXME: Add docstrings and standardize the documentation

import numpy as np

def mean_absolute_error(y_true: np.array, y_pred: np.array):
    '''     
    Mean Absolute Error (L1 Loss):
        y = 1/m * ∑(|y_true - y_pred|)
    
    Args:
        `y_true`: The expected values\n
        `y_pred`: The predicted values
    '''

    return (1/len(y_true)) * np.sum(np.abs(y_true - y_pred))


def mean_squared_error(y_true: np.array, y_pred: np.array):
    '''
    Mean Squared Error (L2 Loss):
        y = 1/m * ∑((y_true - y_pred)^2)
    
    Args:
        `y_true`: The expected values\n
        `y_pred`: The predicted values
    '''

    return (1/len(y_true)) * np.sum(np.square(y_true - y_pred))


def huber_loss(y_true: np.array, y_pred: np.array, delta=1.0):
    '''
    Huber Loss:
        y = 1/m * ∑(0.5 * (y_true - y_pred)^2) if |y_true - y_pred| < delta\n
        y = 1/m * ∑(delta * (|y_true - y_pred| - 0.5 * delta)) otherwise

    Args:
        `y_true`: The expected values\n
        `y_pred`: The predicted values\n
        `delta`: The threshold for the loss
    '''

    def less_than_delta():
        return 0.5 * np.square(y_true - y_pred)
    
    def greater_than_delta():
        return delta * (np.abs(y_true - y_pred) - 0.5 * delta)

    return np.where(np.abs(y_true - y_pred) < delta, less_than_delta(), greater_than_delta())


def cross_entropy(y_true: np.array, y_pred: np.array):
    '''
    Cross-Entropy(a.k.a Log loss)
    '''

    return -np.sum(y_true * np.log(y_pred))

def relative_entropy(y_true: np.array, y_pred: np.array):
    '''
    Relative Entropy(a.k.a Kullback-Leibler divergence)
    '''

    # TODO: Implement this
    raise NotImplementedError

def squared_hinge(y_true: np.array, y_pred: np.array):
    '''
    Squared Hinge
    '''

    # TODO: Implement this
    raise NotImplementedError
