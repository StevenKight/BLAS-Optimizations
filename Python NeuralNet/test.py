import numpy as np

x = np.array([ [ 2, 1, 1 ],
            [ 2, 2, 2 ]])

y = np.array([ [ 1, 2, 1 ],
            [ 2, 2, 2 ]])

z = np.array([ [ 2, 2, 2 ] ])

print(x * z)
print(np.multiply(x, z))
print(x * y)
print(np.multiply(x, y))
# print(np.matmul(x, y.T))