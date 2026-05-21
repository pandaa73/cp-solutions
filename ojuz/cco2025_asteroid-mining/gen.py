import random

N = 8
WEIGHTS = [1, 2, 4]

MAXV = 20
MAXM = 32

M = random.randint(1, MAXM)

print(N, M)

for _ in range(N):
    v = random.randint(1, MAXV)
    w = random.choice(WEIGHTS)

    print(v, w)
