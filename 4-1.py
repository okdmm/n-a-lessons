import numpy as np
# n = 5
Hilebert = np.array([[ 1.0/(i + j - 1) for i in range(1,6)] for j in range(1,6) ])
print(Hilebert)
print(np.linalg.inv(Hilebert))
# n = 10 
Hilebert = np.array([[ 1.0/(i + j - 1) for i in range(1,11)] for j in range(1,11) ])
print(Hilebert)
print(np.linalg.inv(Hilebert))

# n = 15 
Hilebert = np.array([[ 1.0/(i + j - 1) for i in range(1,15)] for j in range(1,15) ])
print(Hilebert)
print(np.linalg.inv(Hilebert))

