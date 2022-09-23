
# f_in = open('/ann/cm/data/bigann10M/bigann.base.10M.u8bin', 'rb')
# f_out = open('/ann/cm/data/bigann10M/bigann.slice.1M.u8bin', 'wb')

# f_in = open('/ann/hax/spacev1B.i8bin', 'rb')
# f_out = open('/ann/cm/data/spacev/spacev.slice.10M.i8bin', 'wb')


# f_in = open('/ann/cm/data/deep10M/deep10M_query', 'rb')
# f_out = open('/ann/cm/data/deep10M/deep10M_query100', 'wb')

f_in = open('/home/cm/projects/ann/exp_result/spann_cmp/query_0_50.bin', 'rb')

# num_points = 100
# dim = 96
# every_dim = 4
# needed_size = num_points * dim * every_dim
import numpy as np
a = np.fromfile(f_in, np.int32, 2)
c = []
for i in range(a[0]):
    b = np.fromfile(f_in, np.float32, 96)
    c.append(b)
    # a = np.frombuffer(a, dtype=np.float32)
print(np.array(c).shape)
# f_in.seek(4 + 4)
# f_out.write(int(num_points).to_bytes(4, byteorder='little'))
# f_out.write(int(dim).to_bytes(4, byteorder='little'))
# in_bytes = f_in.read(needed_size)
# f_out.write(in_bytes)
# f_in.close()
# f_out.close()