import time
import csv
import os

import numpy as np

def test_single_array(array, times_list):
    start = time.time()

    array.T # Transpose the array

    end = time.time()
    times_list.append(("Transpose (sec)", end-start))
    start = time.time()

    array.shape # Read the shape of the array

    end = time.time()
    times_list.append(("Shape (sec)", end-start))

    start = time.time()

    np.sum(array) # Sum the array

    end = time.time()
    times_list.append(("Sum (sec)", end-start))

    start = time.time()

    np.mean(array) # Calculate the mean of the array

    end = time.time()
    times_list.append(("Mean (sec)", end-start))

    start = time.time()

    np.argmax(array) # Find the index of the maximum value in the array

    end = time.time()
    times_list.append(("Argmax (sec)", end-start))

    copy = array.copy()

    start = time.time()

    array = array + copy # Add the array to itself

    end = time.time()
    times_list.append(("Add same size (sec)", end-start))

    start = time.time()

    array = array - copy # Subtract the array to itself

    end = time.time()
    times_list.append(("Substract same size (sec)", end-start))

    start = time.time()

    array = array * copy # Multiply the array to itself

    end = time.time()
    times_list.append(("Multiply same size (sec)", end-start))

    start = time.time()

    array = array / copy # Divide the array to itself

    end = time.time()
    times_list.append(("Divide same size (sec)", end-start))


epochs_small_times = []
epochs_big_times = []
for i in range(15):
    small_times = []
    big_times = []

    start = time.time()

    small = np.array([[1],[2],[3]]) # Create a small array

    end = time.time()
    small_times.append(("Initialize (sec)", end-start))
    test_single_array(small, small_times)

    start = time.time()

    big = np.ones((10, 90)) # Create a big array TODO: Make bigger

    end = time.time()
    big_times.append(("Initialize (sec)", end-start))
    test_single_array(big, big_times)

    start = time.time()

    small = np.zeros(small.shape) # Create a small array

    end = time.time()
    small_times.append(("Initialize zeros (sec)", end-start))

    epochs_small_times.append(small_times)

    start = time.time()

    big = np.zeros(big.shape) # Create a big array

    end = time.time()
    big_times.append(("Initialize zeros (sec)", end-start))

    epochs_big_times.append(big_times)


headers = ['Array size']
mean_small_times = [small.shape]
mean_big_times = [big.shape]
# Calculate the mean of each column in the arrays
for i in range(len(epochs_small_times[0])):
    small_times = []
    big_times = []

    for j in range(len(epochs_small_times)):
        small_times.append((epochs_small_times[j][i][1]))
        big_times.append((epochs_big_times[j][i][1]))

    label = epochs_small_times[0][i][0]

    headers.append(label)
    mean_small_times.append(np.mean(small_times))
    mean_big_times.append(np.mean(big_times))

# Join the arrays
times_data = []
times_data.append(headers)
times_data.append(mean_small_times)
times_data.append(mean_big_times)

# Write to csv file
try:
    os.remove('numpy_times.csv')
except OSError:
    pass

with open("numpy_times.csv", "w") as file:
    writer = csv.writer(file)
    writer.writerows(times_data)

start = time.time()

end = time.time()
print("Time retrieval time: ", end-start)