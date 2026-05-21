import random

T = 500

N = 1000
M = 100000
K = 7000

print(T, N, M, K)
for _ in range(T):
    A = [random.randint(1, M) for _ in range(N)]
    B = [random.randint(1, M) for _ in range(N)]

    print(*A)
    print(*B)
