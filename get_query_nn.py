import numpy as np
from sklearn.neighbors import NearestNeighbors
import struct

f_in = open('/ann/cm/data/deep10M/deep10M_query', 'rb')
f_in.seek(4 + 4)
dim = 96
q = np.fromfile(f_in, np.float32, (dim * 4 * 10000))
q = q.reshape(-1, 96)

print(f'{q}, shape: {q.shape} ')

# print(f'Example {q[0]}, q[0].shape: {q[0].shape}')


for i in [0, 2346, 5421, 8797]:
    for j in [1, 3, 5, 10, 25, 50, 100, 300, 500]:
        neigh = NearestNeighbors(n_neighbors=j, radius=1)
        neigh.fit(q)
        nn = neigh.kneighbors(q[i].reshape(1, dim), j, return_distance=True)

        print(f'{nn[1].flatten()} ')#, nn_0.shape: {nn_0.shape}')

        f_out = open(f'/ann/cm/data/deep10M/query_nn/deep10M_query_{i}_nn_{j}', 'wb')
        f_out.write(int(j).to_bytes(4, byteorder='little'))
        f_out.write(int(96).to_bytes(4, byteorder='little'))
        # f_out.write(q[nn[1].flatten()[0]].tobytes())
        for k in range(0, j):
            f_out.write(q[nn[1].flatten()[k]].tobytes())
        f_out.close()



