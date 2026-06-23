import random

N = 100

V = list(range(1, N + 1))
random.shuffle(V)

Qs = []

for a in range(1, N + 1):
    for b in range(1, N + 1):
        Qs.append((a, b))

print(N, len(Qs))
print(*V)
for (a, b) in Qs:
    print(a, b)
