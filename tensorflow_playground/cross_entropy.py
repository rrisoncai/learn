import numpy as np

y = np.array([1, 0, 0])
pred = np.array([0.5, 0.4, 0.1])

cross_entropy = np.sum(- y * np.log(pred))

print(cross_entropy)
