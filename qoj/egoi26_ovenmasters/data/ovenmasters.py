N, M = map(int, input().split())

b = [[] for _ in range(M)]
for i in range(M):
    row = list(map(int, input().split()))
    T = row[0]
    b[i] = row[1:1 + T]

a = [0] * N

possible = False

if not possible:
    print("NO")
else:
    print("YES")
    print(*a)
