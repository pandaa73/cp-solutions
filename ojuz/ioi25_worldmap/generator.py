import random

N = 15
M = 50

edges = [(i, j) for i in range(1, N + 1) for j in range(i + 1, N + 1)]

random.shuffle(edges)

edges = edges[:M]

print(1)
print(N, M)

for u, v in edges:
    if random.getrandbits(1) == 1:
        u, v = v, u
    print(u, v)
