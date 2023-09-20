import pickle

import pandas as pd
import numpy as np
np.random.seed(0)

from Network import Network
from Layer import Layer
import Activation
import Loss

DATA_DIR = "../Test Data/"

HEADER = ["0","1","2","3","4","5","6","7","8","9","10","11",
            "12","13","14","15","16","17","18","19","20","21","22",
            "23","24","25","26","27","28","29","30","31","32","33",
            "34","35","36","37","38","39","40","41","42","43","44",
            "45","46","47","48","49","50","51","52","53","54","55",
            "56","57","58","59","60","61","62","63","64","65","66",
            "67","68","69","70","71","72","73","74","75","76","77",
            "78","79","80","81","82","83","84","85","86","87","88",
            "89","90","91","92","93","94","95","96","97","98","99",
            "100","101","102","103","104","105","106","107","108",
            "109","110","111","112","113","114","115","116","117",
            "118","119","120","121","122","123","124","125","126",
            "127", "Name"]


def get_csv_info():
    """
    Get the information from the csv.
    """

    dataframe = pd.read_csv(DATA_DIR + "data.csv",
        names=HEADER)

    return dataframe


def get_names_info(data):
    """
    Gets the names of all people in the dataset
    """

    labels = data.pop('Name')
    labels.pop(0)
    labels = np.array(labels.values.tolist())
    unique = np.unique(labels)

    return labels, unique


def get_known_info():
    """
    Imports known encodings and names.

    ### Return
        A list of all encodings and a dictionary with names as keys and encodings as values.
    """

    dataframe = get_csv_info()

    labels, uniques = get_names_info(dataframe)

    binary_labels = []
    for person in labels:
        zeros = np.zeros(len(uniques), dtype=int)
        index = np.where(uniques == person)[0][0]
        zeros[index] = 1
        binary_labels.append(zeros)

    HEADER.pop(len(HEADER)-1)
    numeric_features = dataframe[HEADER]
    numeric_features = numeric_features.iloc[1: , :]
    numeric_features = numeric_features.values.tolist()

    return numeric_features, binary_labels, uniques


def load_test_data():
    """
    Loads the test data from the txt file
    stored as a pickle.dump.
    """

    with open(DATA_DIR + "test_encoding.txt", "rb") as f:
        data = pickle.load(f)

    return data


# Get data
x, y, unique_names = get_known_info()
x = np.array(x)
y = np.array(y)

# Split data
max_samples = 500
train_split = 0.8
train_size = int(max_samples * train_split)

idx = np.random.choice(np.arange(len(x)), max_samples, replace=False)
x = x[idx]
y = y[idx]

idx = np.random.choice(np.arange(len(x)), train_size, replace=False)
x_train = x[idx]
y_train = y[idx]

x_test = np.delete(x, idx, axis=0)
y_test = np.delete(y, idx, axis=0)

# Get sizes
size_x = len(x_train[0])
size_y = len(y_train[0])

# Create network
network = Network()

# Add layers
network.add_layer(Layer(size_x, activation=Activation.tanh))
network.add_layer(Layer(len(unique_names), activation=Activation.softmax))

# Generate connections
network.compile(loss=Loss.cross_entropy)

# Run training
epochs = 5
network.train(x_train, y_train, x_test, y_test, epochs)
